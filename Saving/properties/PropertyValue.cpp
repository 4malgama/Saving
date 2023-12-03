#include "PropertyValue.h"

PropertyValue::PropertyValue()
	: Variant()
{}

PropertyValue::PropertyValue(int value)
	: Variant(value)
{}

PropertyValue::PropertyValue(float value)
	: Variant(value)
{}

PropertyValue::PropertyValue(bool value)
	: Variant(value)
{}

PropertyValue::PropertyValue(const std::string& value)
	: Variant(value)
{}