#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <regex>

namespace commonStd
{
enum BitsOrBytes
{
	BOB_BYTES,
	BOB_BITS
};

enum ShowSpeed
{
	SS_NOT_A_SPEED,
	SS_USE_SLASH_S,
	SS_USE_PS_ACRONYM
};

template< typename ... Args >
std::wstring Stringizing(Args const& ... args)
{
	std::wstringstream stream;
	using List = int[];
	(void)List {
		0, ((void)(stream << args), 0) ...
	};
	return stream.str();
}

extern const std::wstring EMPTY_W_STRING;

extern const std::string EMPTY_STRING;

/// dd-mmm-yyyy hh:mm:ss
extern const std::string DATETIME_FORMAT_IST_MMM;

/// yyyymmdd_hhmmss
extern const std::string DATETIME_FORMAT_DEV;

std::string ToString(const std::wstring& ws);

std::wstring ToWString(const std::string& cs);

std::vector<std::wstring> StringSplitW(const std::wstring& str, const std::wstring& token);

std::vector<std::wstring> tokenize(const std::wstring& str, const std::wregex& re);

std::wstring StringGarbleW(const std::wstring& str);

std::wstring ToWString(const long long& bits, BitsOrBytes showAs, ShowSpeed speed, bool upper = false);

std::wstring GuidStringW(const GUID& guid);

bool CompareCaseInsensitive(const char& left, const char& right);

bool CompareCaseInsensitiveW(const wchar_t& left, const wchar_t& right);

bool CompareString(const std::string& left, const std::string& right, bool caseInsensitive = false);

bool CompareStringW(const std::wstring& left, const std::wstring& right, bool caseInsensitive = false);

std::string ToString(int val);

std::string ToString(long val);

std::string ToString(long long val);

std::string ToString(unsigned val);

std::string ToString(unsigned long val);

std::string ToString(unsigned long long val);

std::string ToString(float val);

std::string ToString(double val);

std::string ToString(long double val);

std::string ToString(const std::chrono::time_point<std::chrono::system_clock>& tp);

std::string ToString(const std::chrono::time_point<std::chrono::system_clock>& tp, std::string format);

std::wstring ToWString(const std::chrono::time_point<std::chrono::system_clock>& tp);

std::wstring ToWString(const std::chrono::time_point<std::chrono::system_clock>& tp, std::string format);

std::wstring ToWString(int val);

std::wstring ToWString(long val);

std::wstring ToWString(long long val);

std::wstring ToWString(unsigned val);

std::wstring ToWString(unsigned long val);

std::wstring ToWString(unsigned long long val);

std::wstring ToWString(float val);

std::wstring ToWString(double val);

std::wstring ToWString(long double val);

int ToInt(std::string const& cs);

int ToInt(std::wstring const& ws);

long ToLong(std::string const& cs);

long ToLong(std::wstring const& ws);

long long ToLongLong(std::string const& cs);

long long ToLongLong(std::wstring const& ws);

float ToFloat(std::string const& cs);

float ToFloat(std::wstring const& ws);

double ToDouble(std::string const& cs);

double ToDouble(std::wstring const& ws);

long double ToLongDouble(std::string const& cs);

long double ToLongDouble(std::wstring const& ws);

//template<typename T, typename TStream> std::wstring PadLeft(T const& t, wchar_t padChar, size_t width);

//template<typename T> std::wstring PadLeftW(T const& t, wchar_t padChar, size_t width);

//template<typename T> std::string PadLeft(T const& t, wchar_t padChar, size_t width);

std::wstring ToBitString(long long bits, bool isSpeed, BitsOrBytes showAs);

std::wstring ToByteString(long long bytes, bool isSpeed, BitsOrBytes showAs);


bool Compare(const char& left, const char& right);

bool CompareW(const wchar_t& left, const wchar_t& right);


template <typename T, typename TStream>
std::wstring PadLeft(T const& t, wchar_t padChar, size_t width)
{
	using namespace std;
	TStream stream;
	stream.width(width);
	stream.fill(padChar);
	stream << t;
	return stream.str();
}

template<typename T>
std::wstring PadLeftW(T const& t, wchar_t padChar, size_t width)
{
	using namespace std;
	wstringstream stream;
	stream.width(width);
	stream.fill(padChar);
	stream << t;
	return stream.str();
}

template<typename T>
std::string PadLeft(T const& t, wchar_t padChar, size_t width)
{
	using namespace std;
	stringstream stream;
	stream.width(width);
	stream.fill(padChar);
	stream << t;
	return stream.str();


}

} // namespace commonStd
