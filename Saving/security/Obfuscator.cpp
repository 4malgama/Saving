#include "Obfuscator.h"
#include <iostream>

Obfuscator::Obfuscator()
{
	handle = LoadLibraryA("Packer.dll");
	if (handle == INVALID_HANDLE_VALUE)
	{
		invalid = true;
		std::cerr << "Error load 'Packer.dll'." << std::endl;
		MessageBoxA(GetConsoleWindow(), "Error load 'Packer.dll'.", "Error obfuscating", MB_OK);
	}
	invalid = false;
}

Obfuscator::~Obfuscator()
{
	if (handle != INVALID_HANDLE_VALUE)
		FreeLibrary(handle);
}

void Obfuscator::fileXor(const char* addr, int key)
{
	if (invalid) return;

	_fXor fXor = (_fXor)GetProcAddress(handle, "pathXor");
	if (fXor != NULL)
	{
		fXor(addr, key);
	}
}