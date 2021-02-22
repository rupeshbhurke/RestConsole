#include "stdafx.h"
#include "ApplicationLogger.h"
#include "FileLogger.h"
#include "StringUtilities.h"

namespace commonStd
{
using namespace std;
const wstring pipe = L"|";

ApplicationLogger::ApplicationLogger(const std::wstring& filePath) : _log(  FileLogger<100, false>::MakePtr(filePath))
{}

std::shared_ptr<ApplicationLogger> ApplicationLogger::MakePtr(const std::wstring& filePath)
{
	return std::shared_ptr<ApplicationLogger>(new ApplicationLogger(filePath));
}

void ApplicationLogger::Log(const std::wstring& str) const
{
	const std::wstring output = Stringizing(std::this_thread::get_id(), pipe,
		ToWString(std::chrono::system_clock::now(), DATETIME_FORMAT_IST_MMM), 
		pipe,str);
	{
		std::lock_guard<std::mutex> lock(_logMutex);
		_log->AppendLine(output);
	}
}

void ApplicationLogger::Commit() const
{
	std::lock_guard<std::mutex> lock(_logMutex);
	_log->Commit();
}


void Log(std::shared_ptr<ILogger> logger, std::wstring str, bool commit)
{
	//return;
	if (!logger) return;
	logger->Log(str);
	if (commit)
		logger->Commit();
}

} // namespace commonStd