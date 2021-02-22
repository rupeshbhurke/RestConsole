#pragma once

namespace commonStd {

class ILogger
{
public:
	virtual ~ILogger() = default;
	virtual void Log(const std::wstring& str) const = 0;
	virtual void Commit() const = 0;
};
} // namespace commonStd
