#include "stdafx.h"
#include "ApplicationHelpers.h"

namespace commonStd {

static std::wstring g_applicationFolderPath;
static std::wstring g_applicationFolderPathWithSeparator;
static std::mutex _applicationFolderPathMutex;

std::wstring GetApplicationFolderPath(bool withSeparator)
{
	const std::lock_guard<std::mutex> lock(_applicationFolderPathMutex);
	if ( g_applicationFolderPath.empty())
	{
		wchar_t moduleName[_MAX_PATH];
		GetModuleFileNameW( nullptr, moduleName, _MAX_PATH);
		const std::wstring exePath(moduleName);
		const size_t lastBackslash =  exePath.find_last_of(SeparatorW());
		g_applicationFolderPath = exePath.substr( 0, lastBackslash);
		g_applicationFolderPathWithSeparator = exePath.substr( 0, lastBackslash) + SeparatorW();
	}

	if ( withSeparator) return g_applicationFolderPathWithSeparator;
	return 	g_applicationFolderPath;
}


bool GetProductAndVersion(std::wstring& productName, std::wstring& productVersion)
{
    // get the filename of the executable containing the version resource
    TCHAR szFilename[MAX_PATH + 1] = {0};
    if (GetModuleFileName(nullptr, szFilename, MAX_PATH) == 0)
    {
        //TRACE("GetModuleFileName failed with error %d\n", GetLastError());
        return false;
    }

    // allocate a block of memory for the version info
    DWORD dummy;
    DWORD dwSize = GetFileVersionInfoSize(szFilename, &dummy);
    if (dwSize == 0)
    {
        //TRACE("GetFileVersionInfoSize failed with error %d\n", GetLastError());
        return false;
    }
    std::vector<BYTE> data(dwSize);

    // load the version info
    if (!GetFileVersionInfo(szFilename, NULL, dwSize, &data[0]))
    {
        //TRACE("GetFileVersionInfo failed with error %d\n", GetLastError());
        return false;
    }

    // get the name and version strings
    LPVOID pvProductName = nullptr;
    unsigned int iProductNameLen = 0;
    LPVOID pvProductVersion = nullptr;
    unsigned int iProductVersionLen = 0;

    // replace "040904e4" with the language ID of your resources
    if (!VerQueryValue(&data[0], L"\\StringFileInfo\\040904b0\\ProductName", &pvProductName, &iProductNameLen) ||
        !VerQueryValue(&data[0], L"\\StringFileInfo\\040904b0\\ProductVersion", &pvProductVersion, &iProductVersionLen))
    {
        //TRACE("Can't obtain ProductName and ProductVersion from resources\n");
        return false;
    }

    productName = LPWSTR(pvProductName);
    productVersion = LPWSTR(pvProductVersion);
    return true;
}

} //namespace common