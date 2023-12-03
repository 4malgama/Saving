#pragma once
#ifndef PROPERTYVALUE_H
#define PROPERTYVALUE_H

#include "../utils/Variant.h"

class PropertyValue : public Variant
{
public:
	PropertyValue();
	PropertyValue(int value);
	PropertyValue(float value);
	PropertyValue(bool value);
	PropertyValue(const std::string& value);
};

#endif // !PROPERTYVALUE_H
