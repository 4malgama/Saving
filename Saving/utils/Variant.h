#pragma once
#ifndef VARIANT_H
#define VARIANT_H

#include <string>

class Variant
{
	union
	{
		int i;
		float f;
		bool b;
		std::string* s;
	} value;
	bool empty;
	enum
	{
		VARINT,
		VARFLOAT,
		VARBOOL,
		VARSTRING,
		VARNONE
	} type;

public:
	Variant();
	Variant(int v);
	Variant(float v);
	Variant(bool v);
	Variant(const std::string& v);
	~Variant();

	void setValue(int newValue);
	void setValue(float newValue);
	void setValue(bool newValue);
	void setValue(const std::string& newValue);

	int toInt() const;
	float toFloat() const;
	bool toBool() const;
	const std::string& toString() const;
	bool isEmpty() const;
};

#endif