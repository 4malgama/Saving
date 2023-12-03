#include "Player.h"

#pragma warning( disable : 4172 ) //return temporary variable

Player::Player()
{
	m_Level = 1; //synch with Database
	m_Expirience = 0; //synch with Database
	bot = true;
}

Player::Player(const std::string& nick)
{
	m_Username = nick;
	m_Level = 1; //synch with Database
	m_Expirience = 0; //synch with Database
	bot = false;
}

const std::string& Player::getName() const
{
	return m_Username;
}

int Player::getLevel() const
{
	return m_Level;
}

uint64_t Player::getExp() const
{
	return m_Expirience;
}

void Player::addItem(const InventoryItem& item)
{
	m_Inventory.push_back(item);
}

const InventoryItem& Player::getItem(const std::string& name) const
{
	auto res = std::find_if(m_Inventory.cbegin(), m_Inventory.cend(), [&name](const InventoryItem& v) {
		return v.getName() == name;
		});
	if (res != m_Inventory.cend())
		return *res;
	return InventoryItem();
}

const std::list<InventoryItem>& Player::getItems() const
{
	return m_Inventory;
}

int Player::itemCount() const
{
	return m_Inventory.size();
}