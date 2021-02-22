#pragma once
#include <mutex>

namespace commonStd {

inline char Separator()
{
#if defined _WIN32 || defined __CYGWIN__
    return '\\';
#else
    return '/';
#endif
}

inline wchar_t SeparatorW()
{
#if defined _WIN32 || defined __CYGWIN__
    return L'\\';
#else
    return L'/';
#endif
}

std::wstring GetApplicationFolderPath(bool withSeparator);

bool GetProductAndVersion(std::wstring& productName, std::wstring& productVersion);
} //namespace common