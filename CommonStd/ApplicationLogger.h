#pragma once

#include "ILogger.h"

namespace commonStd {

template<intmax_t WriteStep, bool truncate>
class FileLogger;

/// ApplicationLogger is a thread safe implementation of ILogger interface.
// Timestamp, ThreadID, 
class ApplicationLogger : public ILogger
{
public:
	static std::shared_ptr<ApplicationLogger> MakePtr(const std::wstring& filePath);

	void Log(const std::wstring& str) const override;
	void Commit() const override;

protected:
	explicit ApplicationLogger(const std::wstring& filePath);

private:
	std::shared_ptr<FileLogger<100, false> > _log;
	mutable std::mutex _logMutex;
};


void Log(std::shared_ptr<ILogger> logger, std::wstring str, bool commit = true);

} // namespace commonStd
