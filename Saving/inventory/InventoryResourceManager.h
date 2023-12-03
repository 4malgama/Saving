#pragma once
#ifndef INVENTORYRESOURCEMANAGER_H
#define INVENTORYRESOURCEMANAGER_H

#include "InventoryItem.h"
#include <memory>

class InventoryResourceManager;

typedef std::shared_ptr<InventoryResourceManager> InventoryResourceManagerPtr;

class InventoryResourceManager
{
	static InventoryResourceManagerPtr instance;
	std::map<std::string, InventoryItem> m_Items;

public:
	static InventoryResourceManagerPtr getInstance();
	void registerItem(const InventoryItem& item);
	const InventoryItem& getItem(const std::string& name) const;
};

#endif // !INVENTORYRESOURCEMANAGER_H
