#pragma once
#include <string>

namespace common {
class CommaSeparatedString
{
public:

	CommaSeparatedString() = default;

	explicit CommaSeparatedString(const std::wstring& string);

	CommaSeparatedString& operator =(const std::wstring& string);

	void append(const std::wstring& string);

	CommaSeparatedString& operator +=(const std::wstring& string);

	const wchar_t* c_str() const;

private:
	std::wstring _string; 
};

} // namespace common