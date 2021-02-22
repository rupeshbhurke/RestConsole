#pragma once
#include <chrono>
#include <string>
#include <mutex>

namespace commonStd
{

class ChronoHelper : public std::enable_shared_from_this<ChronoHelper>
{
public:
	static std::shared_ptr<ChronoHelper> MakePtr();

	static std::wstring CurrentTimeStamp();

	virtual ~ChronoHelper();

	ChronoHelper* Next();

	std::chrono::seconds ElapsedSeconds();

	__int64 ElapsedSecondsAsInt64();

	std::chrono::milliseconds ElapsedMilliseconds();

	__int64 ElapsedMillisecondsAsInt64();

	std::wstring TimeStamp();

protected:
	ChronoHelper();

private:
	std::shared_ptr<std::chrono::time_point<std::chrono::system_clock> > m_previousTimePoint;
	std::shared_ptr<std::chrono::time_point<std::chrono::system_clock> > m_thisTimePoint;
	std::mutex m_timePointMutex;
};

} //namespace commonStd