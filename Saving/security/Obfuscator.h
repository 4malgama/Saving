#pragma once
#ifndef OBFUSCATOR_H
#define OBFUSCATOR_H

#include <Windows.h>

class Obfuscator
{
	HMODULE handle;
	bool invalid;
	typedef bool(__cdecl* _fXor) (const char*, int);

public:
	Obfuscator();
	~Obfuscator();
	void fileXor(const char* addr, int key);
};

#endif // !OBFUSCATOR_H
