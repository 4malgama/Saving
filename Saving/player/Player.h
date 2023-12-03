#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "../inventory/Weapon.h"
#include "../inventory/Armor.h"

class Player
{
	std::string m_Username;
	mutable std::list<InventoryItem> m_Inventory;
	int m_Level;
	uint64_t m_Expirience;
	bool bot;

public:
	Player();
	Player(const std::string& nick);
	const std::string& getName() const;
	int getLevel() const;
	uint64_t getExp() const;
	void addItem(const InventoryItem& item);
	const InventoryItem& getItem(const std::string& name) const;
	const std::list<InventoryItem>& getItems() const;
	int itemCount() const;
};

#endif // !PLAYER_H