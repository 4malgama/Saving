#pragma once
#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include "../properties/PropertyValue.h"
#include <list>
#include <map>

class InventoryItem
{
	std::string m_Name;
	std::string m_Code;
	std::map<std::string, PropertyValue> m_Properties;
	bool m_Empty;

public:
	InventoryItem();
	InventoryItem(const std::string& name, const std::string& code);
	void addProperty(const std::string& name, const PropertyValue& value);
	const std::string& getName() const;
	const std::string& getCode() const;
	const std::list<std::string> getPropNames() const;
	const bool hasProperty(const std::string& name) const;
	const PropertyValue& propertyValue(const std::string& name) const;
};

#endif // !INVENTORYITEM_H
