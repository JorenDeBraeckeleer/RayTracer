#pragma once
#include <vector>
#include "Material.h"

class MaterialManager final
{
public:
	MaterialManager();
	//Rule of five
	~MaterialManager();
	MaterialManager(const MaterialManager& materialManager) = delete;
	MaterialManager(MaterialManager&& materialManager) = delete;
	MaterialManager& operator=(const MaterialManager& materialManager) = delete;
	MaterialManager& operator=(MaterialManager&& materialManager) = delete;

	//Singleton
	static MaterialManager* GetInstance();
	void Cleanup();

	//Functions
	Material* AddMaterial(Material* pMaterial);

private:
	//Variables
	std::vector<Material*> m_pMaterials;

	//Singleton
	static MaterialManager* m_pMaterialManager;
};