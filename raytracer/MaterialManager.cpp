#include "MaterialManager.h"

//Singleton
MaterialManager* MaterialManager::m_pMaterialManager{ nullptr };

//Constructor
MaterialManager::MaterialManager()
	: m_pMaterials{}
{
}

//Destructor
MaterialManager::~MaterialManager()
{
	//Loop over materials
	for (Material* pMaterials : m_pMaterials)
	{
		//Delete materials
		delete pMaterials;
		pMaterials = nullptr;
	}
}

//Singleton
MaterialManager* MaterialManager::GetInstance()
{
	//If no materialmanager has been made yet, make a materialmanager
	if (m_pMaterialManager == nullptr)
	{
		m_pMaterialManager = new MaterialManager();
	}
	return m_pMaterialManager;
}

//Singleton
void MaterialManager::Cleanup()
{
	//Delete materialmanager
	delete m_pMaterialManager;
	m_pMaterialManager = nullptr;
}

//Add material
Material* MaterialManager::AddMaterial(Material* pMaterial)
{
	m_pMaterials.push_back(pMaterial);
	return m_pMaterials.back();
}