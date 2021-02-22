#include "stdafx.h"
#include "StringUtilities.h"
#include <algorithm>
#include <comutil.h>
#include <regex>

namespace commonStd {

using namespace std;

const wstring EMPTY_W_STRING;

const string EMPTY_STRING;

const std::string DATETIME_FORMAT_IST_MMM("%d-%b-%Y %H:%M:%S"); // 01-Jan-2021 13:24:56

const std::string DATETIME_FORMAT_DEV("%Y%m%d_%H%M%S"); // 20210101_132456 (YYYYMMDD_HHMMSS)

string ToString(const wstring& ws)
{
	const int size_needed = WideCharToMultiByte(CP_ACP,0,ws.data(),
		static_cast<int>(ws.length()),nullptr,0, nullptr, nullptr);
	if(size_needed == 0 )	return string();
	string destination(size_needed, 0);
	WideCharToMultiByte(CP_ACP,0,ws.data(),static_cast<int>(ws.length()),
		&destination[0], size_needed, nullptr, nullptr);
	return destination;
}

wstring ToWString(const string& cs)
{
	const int size_needed = MultiByteToWideChar(CP_UTF8, 0, &cs[0], 
		static_cast<int>(cs.size()), nullptr, 0);
	wstring destination(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &cs[0], static_cast<int>(cs.size()),
		&destination[0], size_needed);
	return destination;
}

vector<wstring> StringSplitW(const wstring& str, const wstring& token)
{
	
	vector<wstring> strings;
	size_t offset = 0;
	size_t lastOffset = 0;
	while ((offset = str.find_first_of(token, offset)) != string::npos)
	{
		strings.push_back(str.substr(lastOffset, offset - lastOffset));
		lastOffset = offset + token.size();
		offset = lastOffset;
	}
	if (lastOffset != str.size())
	{
		strings.push_back(str.substr(lastOffset));
	}
	return strings;
}

std::vector<std::wstring> tokenize( const std::wstring& str, const std::wregex& re) 
{ 
    std::wsregex_token_iterator it{ str.begin(),  str.end(), re, -1 }; 
    std::vector<std::wstring> tokenized{ it, {} }; 
  
    // Additional check to remove empty strings 
    tokenized.erase( 
        std::remove_if(tokenized.begin(),  
                            tokenized.end(), 
                       [](std::wstring const& s) { 
                           return s.empty(); 
                       }), 
        tokenized.end()); 
  
    return tokenized; 
} 
wstring StringGarbleW(const wstring& str)
{
	
	size_t oneThirdSize = 3;
	while (oneThirdSize > 0)
	{
		if (str.size() > oneThirdSize * 2)
			break;
		--oneThirdSize;
	}
	const wstring filler(str.size() - (oneThirdSize * 2), L'*');
	wstring newStr = str.substr(0, oneThirdSize) + filler + str.substr(str.size() - oneThirdSize);
	return newStr;
}

wstring ToWString(const long long& bits, BitsOrBytes showAs, ShowSpeed speed, bool upper)
{
	
	static const wchar_t lowerSuffixes[] = { L'\0', L'k', L'm', L'g', L't', L'p' };
	int counter = 1;
	long double number = static_cast<long double>( showAs == BOB_BYTES ? bits / 8 : bits) / 1000;
	while (roundl(number) >= 1000 )
	{
		number /= 1000;
		counter++;
	}

	wchar_t suffix = lowerSuffixes[counter];
	if ( showAs == BOB_BYTES || upper)
	{
		suffix = towupper(suffix);
	}

	const wchar_t bitOrByte =  showAs == BOB_BYTES ? L'B' : 'b';
	const wstring speedPart = speed == SS_USE_SLASH_S ? L"/s" : speed == SS_USE_PS_ACRONYM ? L"ps" : L"";

	wstringstream ws;
	ws.precision(2);
	ws << fixed <<  number << L" " << suffix << bitOrByte << speedPart;
	return ws.str();
}

wstring GuidStringW(const GUID& guid)
{
	wchar_t buffer[256] = L"\0";
	swprintf_s( buffer, 256, 
		L"%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", 
		guid.Data1,
		guid.Data2,
		guid.Data3,
		guid.Data4[0],
		guid.Data4[1],
		guid.Data4[2],
		guid.Data4[3],
		guid.Data4[4],
		guid.Data4[5],
		guid.Data4[6],
		guid.Data4[7]);
	wstringstream ws;
	ws << L"{" << buffer << L"}";
	return ws.str();
}

bool Compare(const char& left, const char& right)
{
	return left == right;
}

bool CompareW(const wchar_t& left, const wchar_t& right)
{
	return left == right;
}

bool CompareCaseInsensitive(const char& left, const char& right)
{
	return(towupper(left) == towupper(right));
}

bool CompareCaseInsensitiveW(const wchar_t& left, const wchar_t& right)
{
	return(towupper(left) == towupper(right));
}

bool CompareString(const string& left, const string& right, bool caseInsensitive)
{
	if ( left.size() != right.size()) return false;
	if (caseInsensitive)
	{
		return equal(left.begin(), left.end(), 
			right.begin(), right.end(), 
			CompareCaseInsensitive);
	}
	return equal(left.begin(), left.end(), 
		right.begin(), right.end(), 
		Compare);
}

bool CompareStringW(const wstring & left, const wstring & right, bool caseInsensitive)
{
	if ( left.size() != right.size()) return false;
	if (caseInsensitive)
	{
		return equal(left.begin(), left.end(), 
			right.begin(), right.end(), 
			CompareCaseInsensitiveW);
	}
	return equal(left.begin(), left.end(), 
		right.begin(), right.end(), 
		CompareW);
}

wstring ToWString(int val)
{
	return to_wstring(val);
}

wstring ToWString(long val)
{
	return to_wstring(val);
}

wstring ToWString(long long val)
{
	return to_wstring(val);
}

wstring ToWString(unsigned val)
{
	return to_wstring(val);
}

wstring ToWString(unsigned long val)
{
	return to_wstring(val);
}

wstring ToWString(unsigned long long val)
{
	return to_wstring(val);
}

wstring ToWString(float val)
{
	return to_wstring(val);
}

wstring ToWString(double val)
{
	return to_wstring(val);
}

wstring ToWString(long double val)
{
	return to_wstring(val);
}

int ToInt(string const& cs)
{
	return stoi(cs);
}

int ToInt(wstring const& ws)
{
	return stoi(ws);
}

long ToLong(string const& cs)
{
	return stol(cs);
}

long ToLong(wstring const& ws)
{
	return stol(ws);
}

long long ToLongLong(string const& cs)
{
	return stoll(cs);
}

long long ToLongLong(wstring const& ws)
{
	return stoll(ws);
}

float ToFloat(string const& cs)
{
	return stof(cs);
}

float ToFloat(wstring const& ws)
{
	return stof(ws);
}

double ToDouble(string const& cs)
{
	return stod(cs);
}

double ToDouble(wstring const& ws)
{
	return stod(ws);
}

long double ToLongDouble(string const& cs)
{
	return stold(cs);
}

long double ToLongDouble(wstring const& ws)
{
	return stold(ws);
}

string ToString(int val)
{
	return to_string(val);
}

string ToString(long val)
{
	return to_string(val);
}

string ToString(long long val)
{
	return to_string(val);
}

string ToString(unsigned val)
{
	return to_string(val);
}

string ToString(unsigned long val)
{
	return to_string(val);
}

string ToString(unsigned long long val)
{
	return to_string(val);
}

string ToString(float val)
{
	return to_string(val);
}

string ToString(double val)
{
	return to_string(val);
}

string ToString(long double val)
{
	return to_string(val);
}

string ToString(const chrono::time_point<chrono::system_clock>& tp)
{
	
	time_t time = chrono::system_clock::to_time_t(tp);
	char cs[50];
	ctime_s(cs, sizeof(cs), &time);
	return string(&cs[0]);
}

string ToString(const chrono::time_point<chrono::system_clock>& tp, std::string format)
{
	time_t time = chrono::system_clock::to_time_t(tp);
	tm ltm{};
	localtime_s(&ltm, &time);
	char buff[70];
	strftime(buff, sizeof buff, format.c_str(), &ltm);
	return string(&buff[0]);
}

wstring ToWString(const chrono::time_point<chrono::system_clock>& tp)
{
	time_t time = chrono::system_clock::to_time_t(tp);
	char cs[50];
	ctime_s(cs, sizeof(cs), &time);
	return wstring(&cs[0], &cs[strlen(cs)]);
}

wstring ToWString(const chrono::time_point<chrono::system_clock>& tp, std::string format)
{
	
	time_t time = chrono::system_clock::to_time_t(tp);
	tm ltm{};
	localtime_s(&ltm, &time);
	char buff[70];
	strftime(buff, sizeof buff, format.c_str(), &ltm);
	return wstring(&buff[0], &buff[strlen(buff)]);
}

std::wstring ToBitString(long long bits, bool isSpeed, BitsOrBytes showAs)
{
	return ToWString(bits, showAs, isSpeed ? SS_USE_PS_ACRONYM : SS_NOT_A_SPEED);
}

std::wstring ToByteString(long long bytes, bool isSpeed, BitsOrBytes showAs)
{
	return ToWString(bytes * 8, showAs, isSpeed ? SS_USE_PS_ACRONYM : SS_NOT_A_SPEED);
}

} //namespace commonStd