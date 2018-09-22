#include "FbxLoader.h"
#include <fbxsdk/core/fbxmanager.h>
#include <fbxsdk/core/math/fbxvector4.h>
#include <fbxsdk/core/math/fbxaffinematrix.h>
#include <fbxsdk/scene/geometry/fbxnode.h>
#include "../RenderPipeLine/Mathematics/MathUtil.h"

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(FbxLoader::getSingletonPtr()->m_pFbxManager->GetIOSettings()))
#endif

FbxLoader::FbxLoader()
	: m_pFbxManager(nullptr)
	, m_pFbxScene(nullptr)
{
	Initialize();
}

FbxLoader::~FbxLoader()
{
}

void FbxLoader::Initialize()
{
	//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
	m_pFbxManager = FbxManager::Create();
	if (m_pFbxManager == nullptr)
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}
	else
	{
		FBXSDK_printf("Autodesk FBX SDK version %s\n", m_pFbxManager->GetVersion());
	}

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	m_pFbxManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	m_pFbxManager->LoadPluginsDirectory(lPath.Buffer());

	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "My Scene");
	if (!m_pFbxScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		exit(1);
	}
}

void FbxLoader::Finalize()
{
}

bool FbxLoader::LoadScene(const char * pFilename, vector<RenderBuffer>& renderBuffer)
{
	int lFileMajor, lFileMinor, lFileRevision;
	int lSDKMajor, lSDKMinor, lSDKRevision;

	//int lFileFormat = -1;
	int i, lAnimStackCount;
	bool lStatus;
	char lPassword[1024];

	// Get the file version number generate by the FBX SDK.
	FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

	// Create an importer.
	FbxImporter* lImporter = FbxImporter::Create(m_pFbxManager, "");

	// Initialize the importer by providing a filename.
	const bool lImportStatus = lImporter->Initialize(pFilename, -1, m_pFbxManager->GetIOSettings());
	lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

	if (!lImportStatus)
	{
		FbxString error = lImporter->GetStatus().GetErrorString();
		FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
		FBXSDK_printf("Error returned: %s\n\n", error.Buffer());

		if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
		{
			FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
			FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
		}

		return false;
	}

	FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

	if (lImporter->IsFBX())
	{
		FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

		// From this point, it is possible to access animation stack information without
		// the expense of loading the entire file.

		FBXSDK_printf("Animation Stack Information\n");

		lAnimStackCount = lImporter->GetAnimStackCount();

		FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
		FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
		FBXSDK_printf("\n");

		for (i = 0; i < lAnimStackCount; i++)
		{
			FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

			FBXSDK_printf("    Animation Stack %d\n", i);
			FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
			FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

			// Change the value of the import name if the animation stack should be imported 
			// under a different name.
			FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

			// Set the value of the import state to false if the animation stack should be not
			// be imported. 
			FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
			FBXSDK_printf("\n");
		}

		// Set the import states. By default, the import states are always set to 
		// true. The code below shows how to change these states.
		IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
		IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
		IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
		IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
		IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
		IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
		IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
	}

	// Import the scene.
	lStatus = lImporter->Import(m_pFbxScene);

	if (lStatus)
	{
		ProcessContent(m_pFbxScene, renderBuffer);
	}

	if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
	{
		FBXSDK_printf("Please enter password: ");

		lPassword[0] = '\0';

		FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
			scanf("%s", lPassword);
		FBXSDK_CRT_SECURE_NO_WARNING_END

			FbxString lString(lPassword);

		IOS_REF.SetStringProp(IMP_FBX_PASSWORD, lString);
		IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

		lStatus = lImporter->Import(m_pFbxScene);

		if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
		{
			FBXSDK_printf("\nPassword is wrong, import aborted.\n");
		}
	}

	// Destroy the importer.
	lImporter->Destroy();

	return lStatus;
}

void FbxLoader::ProcessContent(FbxScene* pScene, vector<RenderBuffer>& renderBuffer)
{
	FbxNode* lNode = pScene->GetRootNode();

	if (lNode != nullptr)
	{
		for (int i = 0; i < lNode->GetChildCount(); i++)
		{
			ProcessContent(lNode->GetChild(i), renderBuffer);
		}
	}
}

void FbxLoader::ProcessContent(FbxNode* pNode, vector<RenderBuffer>& renderBuffer)
{
	if (pNode->GetNodeAttribute() == nullptr)
	{
		FBXSDK_printf("NULL Node Attribute\n\n");
	}
	else
	{
		FbxNodeAttribute::EType lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

		switch (lAttributeType)
		{
		case FbxNodeAttribute::eMesh:
			vector<float3> vertices;
			vector<int> indices;
			vector<float3> normals;
			vector<float4> colors;
			vector<float2> uvs;
			vector<int> matertialRefs;
			vector<Material> materials;
			ProcessMesh(pNode, vertices, indices, normals, colors, uvs, matertialRefs, materials);
			renderBuffer.push_back({ vertices, normals, indices, colors, uvs, matertialRefs, materials });
			break;
		}
	}

	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
		ProcessContent(pNode->GetChild(i), renderBuffer);
	}
}

void FbxLoader::ProcessMesh(FbxNode* pNode, vector<float3>& vertices, vector<int>& indices, vector<float3>& normals, vector<float4>& colors, vector<float2>& uvs, vector<int>& matertialRefs, vector<Material>& materials)
{
	FbxMesh* lMesh = (FbxMesh*)pNode->GetNodeAttribute();

	auto position = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	auto rotation = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	auto scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

	auto geometricTransform = FbxAMatrix(position, rotation, scale);
	auto globalTransform = pNode->EvaluateGlobalTransform(0.0f);
	auto tranformMat = geometricTransform * globalTransform;

	ProcessVertex(lMesh, vertices, tranformMat);		
	ProcessIndex(lMesh, indices);
	ProcessNormals(lMesh, normals, tranformMat);
	ProcessVertexColor(lMesh, colors);
	ProcessUV(lMesh, uvs);
	ProcessMaterialConnection(lMesh, matertialRefs);
	ProcessMaterial(lMesh, materials);
}

void FbxLoader::ProcessVertex(FbxMesh* pMesh, vector<float3>& vertices, FbxAMatrix mat)
{
	int lControlPointsCount = pMesh->GetControlPointsCount();
	FbxVector4* lControlPoints = pMesh->GetControlPoints();

	for (int i = 0; i < lControlPointsCount; i++)
	{
		auto newVertex = mat.MultT(lControlPoints[i]);
		vertices.push_back(float3(newVertex.mData[0], newVertex.mData[1], newVertex.mData[2]));
	}
}

void FbxLoader::ProcessIndex(FbxMesh* pMesh, vector<int>& indices)
{
	int lPolygonCount = pMesh->GetPolygonCount();
	
	for (int i = 0; i < lPolygonCount; i++)
	{
		int lPolygonSize = pMesh->GetPolygonSize(i);

		for (int j=0;j< lPolygonSize; j++)
		{
			indices.push_back(pMesh->GetPolygonVertex(i, j));
		}
	}
}

void FbxLoader::ProcessNormals(FbxMesh* pMesh, vector<float3>& normals, FbxAMatrix mat)
{
	FbxGeometryElementNormal* lNormalElement = pMesh->GetElementNormal();
	if (lNormalElement)
	{
		if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			for (int lVertexIndex = 0; lVertexIndex < pMesh->GetControlPointsCount(); lVertexIndex++)
			{
				int lNormalIndex = 0;
				if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
					lNormalIndex = lVertexIndex;

				if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
					lNormalIndex = lNormalElement->GetIndexArray().GetAt(lVertexIndex);

				FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
				auto newNormal = mat.MultT(lNormal);
				normals.push_back(float3(newNormal.mData[0], newNormal.mData[1], newNormal.mData[2]));
			}
		}

		else if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			int lIndexByPolygonVertex = 0;

			vector<vector<float3>> normalArray;
			for (int i=0;i<pMesh->GetControlPointsCount();i++)
			{
				vector<float3> array;
				normalArray.push_back(array);
			}

			for (int lPolygonIndex = 0; lPolygonIndex < pMesh->GetPolygonCount(); lPolygonIndex++)
			{
				int lPolygonSize = pMesh->GetPolygonSize(lPolygonIndex);

				for (int i = 0; i < lPolygonSize; i++)
				{
					int lControlPointIndex = pMesh->GetPolygonVertex(lPolygonIndex, i);

					int lNormalIndex = 0;

					if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						lNormalIndex = lIndexByPolygonVertex;

					if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						lNormalIndex = lNormalElement->GetIndexArray().GetAt(lIndexByPolygonVertex);

					FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
					auto newNormal = mat.MultT(lNormal);
					normalArray[lControlPointIndex].push_back(float3(newNormal.mData[0], newNormal.mData[1], newNormal.mData[2]));

					lIndexByPolygonVertex++;
				}
			}

			for (int i = 0; i < pMesh->GetControlPointsCount(); i++)
			{
				float3 normal(0.0f, 0.0f, 0.0);
				for (auto n : normalArray[i])
				{
					normal = normal + n;
				}

				normals.push_back(MathUtil::Normalize(normal));
			}
		}
	}
}

void FbxLoader::ProcessVertexColor(FbxMesh* pMesh, vector<float4>& colors)
{
	auto vertexCount = pMesh->GetControlPointsCount();
	for (int lVertexIndex = 0; lVertexIndex < vertexCount; lVertexIndex++)
	{
		FbxGeometryElementVertexColor* leVtxc = pMesh->GetElementVertexColor(0);

		if (leVtxc != nullptr)
		{
			int lColorlIndex = 0;
			if (leVtxc->GetReferenceMode() == FbxGeometryElement::eDirect)
				lColorlIndex = lVertexIndex;

			if (leVtxc->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
				lColorlIndex = leVtxc->GetIndexArray().GetAt(lVertexIndex);

			auto color = leVtxc->GetDirectArray().GetAt(lColorlIndex);

			colors.push_back(float4(color.mRed, color.mGreen, color.mBlue, color.mAlpha));
		}
	}
}

void FbxLoader::ProcessUV(FbxMesh * pMesh, vector<float2>& uvs)
{
	int lPolygonCount = pMesh->GetPolygonCount();

	int vertexId = 0;
	for (int i = 0; i < lPolygonCount; i++)
	{
		int lPolygonSize = pMesh->GetPolygonSize(i);

		for (int j = 0; j < lPolygonSize; j++)
		{
			int lControlPointIndex = pMesh->GetPolygonVertex(i, j);

			for (int l = 0; l < pMesh->GetElementUVCount(); ++l)
			{
				FbxGeometryElementUV* leUV = pMesh->GetElementUV(l);

				switch (leUV->GetMappingMode())
				{
				default:
					break;
				case FbxGeometryElement::eByControlPoint:
					switch (leUV->GetReferenceMode())
					{
					case FbxGeometryElement::eDirect:
					{
						auto uv = leUV->GetDirectArray().GetAt(lControlPointIndex);
						uvs.push_back(float2(uv.mData[0], uv.mData[1]));
					}
						break;
					case FbxGeometryElement::eIndexToDirect:
					{
						
						int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
						auto uv = leUV->GetDirectArray().GetAt(id);
						uvs.push_back(float2(uv.mData[0], uv.mData[1]));
					}
					break;
					default:
						break; // other reference modes not shown here!
					}
					break;

				case FbxGeometryElement::eByPolygonVertex:
				{
					int lTextureUVIndex = pMesh->GetTextureUVIndex(i, j);
					switch (leUV->GetReferenceMode())
					{
					case FbxGeometryElement::eDirect:
					case FbxGeometryElement::eIndexToDirect:
					{
						auto uv = leUV->GetDirectArray().GetAt(lTextureUVIndex);
						uvs.push_back(float2(uv.mData[0], uv.mData[1]));
					}
					break;
					}
				}
				break;
				}
			}
			vertexId++;
		}
	}
}

void FbxLoader::ProcessMaterialConnection(FbxMesh * pMesh, vector<int>& matertialRefs)
{
	int lPolygonCount = pMesh->GetPolygonCount();

	auto pMaterialIndices = &pMesh->GetElementMaterial()->GetIndexArray();

	for (int triangleIndex = 0; triangleIndex < lPolygonCount; triangleIndex++)
	{
		matertialRefs.push_back(pMaterialIndices->GetAt(triangleIndex));
	}
}

void FbxLoader::ProcessMaterial(FbxMesh * pMesh, vector<Material>& materials)
{
	int materialCount;

	if (pMesh && pMesh->GetNode())
	{
		FbxNode* pNode = pMesh->GetNode();
		int materialCount = pNode->GetMaterialCount();

		for (int materialIndex = 0; materialIndex < materialCount; materialIndex++)
		{
			FbxSurfaceMaterial* pSurfaceMaterial = pNode->GetMaterial(materialIndex);
			materials.push_back(Material{ pSurfaceMaterial->GetName() });
		}
	}
}