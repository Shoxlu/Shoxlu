#include <stdio.h>
#include <Windows.h>
#include <cstdint>
#include <string>


int find(std::string path, const char* s, size_t s_len)
{
	int len = path.length();
	for (int i = 0; i < len; i++)
	{
		int j = 0;
		while(j < s_len && s[j] == path[j+i])
		{
			j++;
		}
		if(j == s_len)
		{
			return i;
		}
	}
	return -1;
}


wchar_t *utf8_to_wchar(const char *utf8)
{
    int size = MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8,
        -1,
        NULL,
        0
    );

    if (size == 0)
        return NULL;

    wchar_t *result = (wchar_t*)malloc(size * sizeof(wchar_t));
    if (!result)
        return NULL;

    MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8,
        -1,
        result,
        size
    );

    return result;
}
