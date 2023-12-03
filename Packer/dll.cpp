#include "dll.h"

#pragma warning( disable : 4244 ) // convertation int64 to size_t
bool pathXor(const char* addr, int offset)
{
	FILE* fp;
	if (fopen_s(&fp, addr, "r+b") == 0)
	{
		/*_fseeki64(fp, 0, SEEK_END);
		size_t pos = _ftelli64(fp);
		rewind(fp);
		for (size_t i = 0; i < pos; i++)
		{
			char c = getc(fp);
			if (c == EOF)
				break;

			_fseeki64(fp, i, SEEK_SET);
			putc(c + 1, fp);
		}*/
		_fseeki64(fp, 0, SEEK_END);
		size_t size = _ftelli64(fp);
		rewind(fp);

		char* buf = new char[size];
		fread(buf, 1, size, fp);

		for (size_t i = 0; i < size; i++)
		{
			_fseeki64(fp, i, SEEK_SET);
			putc(buf[i] ^ offset, fp);
		}

		delete[] buf;
		fclose(fp);
		return true;
	}
	return false;
}