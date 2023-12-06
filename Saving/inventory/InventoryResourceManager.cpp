#include "InventoryResourceManager.h"

InventoryResourceManagerPtr InventoryResourceManager::instance = nullptr;

InventoryResourceManager::InventoryResourceManager()
{
}

InventoryResourceManagerPtr InventoryResourceManager::getInstance()
{
	if (instance == nullptr)
		instance = std::shared_ptr<InventoryResourceManager>(new InventoryResourceManager());
	return instance;
}

void InventoryResourceManager::registerItem(const InventoryItem& item)
{
	if (m_Items.find(item.getCode()) == m_Items.end())
		m_Items.insert(std::make_pair(item.getCode(), item));
}

const InventoryItem& InventoryResourceManager::getItem(const std::string& name) const
{
	auto ret = m_Items.find(name);
	if (ret != m_Items.end())
		return ret->second;
	return InventoryItem();
}