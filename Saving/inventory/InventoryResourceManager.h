#pragma once
#ifndef INVENTORYRESOURCEMANAGER_H
#define INVENTORYRESOURCEMANAGER_H

#include "InventoryItem.h"
#include <memory>

class InventoryResourceManager;

typedef std::shared_ptr<InventoryResourceManager> InventoryResourceManagerPtr;

/// <summary>
/// Object of 'Singleton' pattern.
/// </summary>
class InventoryResourceManager
{
	static InventoryResourceManagerPtr instance;
	std::map<std::string, InventoryItem> m_Items;

	InventoryResourceManager();

public:
	InventoryResourceManager(const InventoryResourceManager&) = delete;
	InventoryResourceManager(InventoryResourceManager&&) noexcept = delete;

	static InventoryResourceManagerPtr getInstance();
	void registerItem(const InventoryItem& item);
	const InventoryItem& getItem(const std::string& name) const;

	InventoryResourceManager& operator= (const InventoryResourceManager&) = delete;
	InventoryResourceManager& operator= (InventoryResourceManager&&) noexcept = delete;
};

#endif // !INVENTORYRESOURCEMANAGER_H
