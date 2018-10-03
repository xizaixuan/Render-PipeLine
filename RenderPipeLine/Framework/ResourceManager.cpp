#include "ResourceManager.h"

ResourceManager::ResourceManager(void)
{

}

ResourceManager::~ResourceManager(void)
{
}

void ResourceManager::AddTexture(string name, Texture* texture)
{
	if (m_Textures.find(name) == m_Textures.end())
	{
		m_Textures.insert(make_pair(name, texture));
	}
}

void ResourceManager::AddMaterial(string name, Material* material)
{
	if (m_Materials.find(name) == m_Materials.end())
	{
		m_Materials.insert(make_pair(name, material));
	}
}
