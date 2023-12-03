#include "InventoryItem.h"

InventoryItem::InventoryItem()
{
	m_Empty = true;
}

InventoryItem::InventoryItem(const std::string& name, const std::string& code)
{
	m_Name = name;
	m_Code = code;
	m_Empty = false;
}

void InventoryItem::addProperty(const std::string& name, const PropertyValue& value)
{
	m_Properties.insert(std::make_pair(name, value));
}

const std::string& InventoryItem::getName() const
{
	return m_Name;
}

const std::string& InventoryItem::getCode() const
{
	return m_Code;
}

const std::list<std::string> InventoryItem::getPropNames() const
{
	std::list<std::string> ret;
	for (auto i = m_Properties.cbegin(); i != m_Properties.cend(); ++i)
		ret.push_back(i->first);
	return ret;
}

const bool InventoryItem::hasProperty(const std::string& name) const
{
	return m_Properties.find(name) != m_Properties.end();
}

const PropertyValue& InventoryItem::propertyValue(const std::string& name) const
{
	if (hasProperty(name))
	{
		return m_Properties.at(name);
	}
	return PropertyValue();
}