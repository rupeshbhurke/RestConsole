#include "stdafx.h"

#include "CommaSeparatedString.h"
namespace common {

CommaSeparatedString::CommaSeparatedString(const std::wstring& string)
{
	_string = string;
}

CommaSeparatedString& CommaSeparatedString::operator=(const std::wstring& string)
{
	_string = string;
	return *this;
}

void CommaSeparatedString::append(const std::wstring& string)
{
	if ( !_string.empty())
		_string += L",";
	_string += string;
}

CommaSeparatedString & CommaSeparatedString::operator+=(const std::wstring& string)
{
	this->append(string);
	return *this;
}

const wchar_t* CommaSeparatedString::c_str() const
{
	return _string.c_str();
}

} // namespace common


