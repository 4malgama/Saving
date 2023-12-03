#include "Variant.h"

#pragma warning( disable : 26495 ) //initialize some fields

Variant::Variant()
{
	empty = true;
	type = VARNONE;
}

Variant::Variant(int v)
{
	value.i = v;
	empty = true;
	type = VARINT;
}

Variant::Variant(float v)
{
	value.f = v;
	empty = true;
	type = VARFLOAT;
}

Variant::Variant(bool v)
{
	value.b = v;
	empty = true;
	type = VARBOOL;
}

Variant::Variant(const std::string& v)
{
	value.s = new std::string(v);
	empty = true;
	type = VARSTRING;
}

Variant::~Variant()
{
	if (value.s != nullptr && type == VARSTRING)
		delete value.s;
}

void Variant::setValue(int newValue)
{
	if (type == VARSTRING) delete value.s;

	value.i = newValue;
	empty = false;
	type = VARINT;
}

void Variant::setValue(float newValue)
{
	if (type == VARSTRING) delete value.s;

	value.f = newValue;
	empty = false;
	type = VARFLOAT;
}

void Variant::setValue(bool newValue)
{
	if (type == VARSTRING) delete value.s;

	value.b = newValue;
	empty = false;
	type = VARBOOL;
}

void Variant::setValue(const std::string& newValue)
{
	if (type == VARSTRING) delete value.s;

	value.s = new std::string(newValue);
	empty = false;
	type = VARSTRING;
}

int Variant::toInt() const
{
	if (type != VARSTRING)
	{
		return value.i;
	}
	return 0;
}

float Variant::toFloat() const
{
	if (type != VARSTRING)
	{
		return value.f;
	}
	return 0;
}

bool Variant::toBool() const
{
	if (type != VARSTRING)
	{
		return value.b;
	}
	return false;
}

const std::string& Variant::toString() const
{
	if (type == VARSTRING)
	{
		return *value.s;
	}
	return "";
}

bool Variant::isEmpty() const
{
	return empty;
}

#pragma warning( default : 26495 )