/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   资源管理
/// \author  xizaixuan
/// \date    2018-09
/////////////////////////////////////////////////////////////////////////////////
#ifndef _ResourceManager_H_
#define _ResourceManager_H_

#include <string>
#include <vector>
#include <map>
#include "..\Utility\Singleton.h"

using namespace std;

class Texture;
class Material;

class ResourceManager : public Singleton <ResourceManager>
{
	SINGLETON_DEFINE(ResourceManager)
private:
	ResourceManager(void);
	~ResourceManager(void);

public:
	void AddTexture(string name, Texture* texture);
	void AddMaterial(string name, Material* material);

private:
	map<string, Texture*> m_Textures;
	map<string, Material*> m_Materials;
};

#endif