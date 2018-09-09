/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, xizaixuan. All rights reserved.
/// \brief   Fbx‘ÿ»Î
/// \author  xizaixuan
/// \date    2017-08
/////////////////////////////////////////////////////////////////////////////////
#ifndef FbxLoader_H_
#define FbxLoader_H_

#include <vector>
#include "../RenderPipeLine/Utility/Singleton.h"
#include "fbxsdk.h"
#include "../RenderPipeLine/Mathematics/Float3.h"
#include <fbxsdk/scene/geometry/fbxmesh.h>
#include "../RenderPipeLine/Utility/RenderBuffer.h"
#include <fbxsdk/core/math/fbxaffinematrix.h>
#include "../RenderPipeLine/Mathematics/Float4.h"

using namespace std;

class FbxLoader : public Singleton<FbxLoader>
{
	SINGLETON_DEFINE(FbxLoader)
private:
	FbxLoader();
	~FbxLoader();

	void Initialize();
	void Finalize();

public:
	bool LoadScene(const char* pFilename, vector<RenderBuffer>& renderBuffer);

private:
	void ProcessContent(FbxScene* pScene, vector<RenderBuffer>& renderBuffer);
	void ProcessContent(FbxNode* pNode, vector<RenderBuffer>& renderBuffer);
	void ProcessMesh(FbxNode* pNode, vector<float3>& vertices, vector<int>& indices, vector<float3>& normals, vector<float4>& colors);
	void ProcessVertex(FbxMesh* pMesh, vector<float3>& vertices, FbxAMatrix mat);
	void ProcessIndex(FbxMesh* pMesh, vector<int>& indices);
	void ProcessNormals(FbxMesh* pMesh, vector<float3>& normals, FbxAMatrix mat);
	void ProcessVertexColor(FbxMesh* pMesh, vector<float4>& colors);

public:
	FbxManager* m_pFbxManager;
	FbxScene* m_pFbxScene;
};

#endif