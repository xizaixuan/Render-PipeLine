#include "FbxLoader.h"
#include <fbxsdk/core/fbxmanager.h>
#include <fbxsdk/core/math/fbxvector4.h>
#include <fbxsdk/scene/geometry/fbxmesh.h>

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

bool FbxLoader::LoadScene(const char * pFilename, vector<float3>& vertices, vector<int>& indices)
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
		ProcessContent(m_pFbxScene, vertices, indices);
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

void FbxLoader::ProcessContent(FbxScene* pScene, vector<float3>& vertices, vector<int>& indices)
{
	FbxNode* lNode = pScene->GetRootNode();

	if (lNode != nullptr)
	{
		for (int i = 0; i < lNode->GetChildCount(); i++)
		{
			ProcessContent(lNode->GetChild(i), vertices, indices);
		}
	}
}

void FbxLoader::ProcessContent(FbxNode* pNode, vector<float3>& vertices, vector<int>& indices)
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
		default:
			break;

// 		case FbxNodeAttribute::eSkeleton:
// 			ProcessSkeleton(pNode);
// 			break;

		case FbxNodeAttribute::eMesh:
			ProcessMesh(pNode, vertices, indices);
			break;
		}
	}

	for (int i = 0; i < pNode->GetChildCount(); i++)
	{
		ProcessContent(pNode->GetChild(i), vertices, indices);
	}
}

void FbxLoader::ProcessMesh(FbxNode* pNode, vector<float3>& vertices, vector<int>& indices)
{
	FbxMesh* lMesh = (FbxMesh*)pNode->GetNodeAttribute();

	ProcessControlsPoints(lMesh, vertices);	// vertices			
	ProcessPolygons(lMesh, indices);		// indices

}

void FbxLoader::ProcessControlsPoints(FbxMesh* pMesh, vector<float3>& vertices)
{
	int lControlPointsCount = pMesh->GetControlPointsCount();
	FbxVector4* lControlPoints = pMesh->GetControlPoints();
	for (int i = 0; i < lControlPointsCount; i++)
	{
		vertices.push_back(float3(lControlPoints[i].mData[0], lControlPoints[i].mData[1], lControlPoints[i].mData[2]));
	}
}

void FbxLoader::ProcessPolygons(FbxMesh* pMesh, vector<int>& indices)
{
	int lPolygonCount = pMesh->GetPolygonCount();

	for (int i = 0; i < lPolygonCount; i++)
	{
		indices.push_back(pMesh->GetPolygonVertex(i, 0));
		indices.push_back(pMesh->GetPolygonVertex(i, 1));
		indices.push_back(pMesh->GetPolygonVertex(i, 2));

		indices.push_back(pMesh->GetPolygonVertex(i, 0));
		indices.push_back(pMesh->GetPolygonVertex(i, 2));
		indices.push_back(pMesh->GetPolygonVertex(i, 3));
	} // for polygonCount
}
