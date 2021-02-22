#include "stdafx.h"

#include "ChronoHelper.h"
#include "StringUtilities.h"

using namespace std;
using namespace std::chrono;

namespace commonStd {
ChronoHelper::ChronoHelper() :
	m_previousTimePoint(nullptr)
{}

ChronoHelper::~ChronoHelper()
{
	lock_guard<mutex> lock(m_timePointMutex);
}

std::shared_ptr<ChronoHelper> ChronoHelper::MakePtr()
{
	return  std::shared_ptr<ChronoHelper>( new ChronoHelper);
}

std::wstring ChronoHelper::CurrentTimeStamp()
{
    using namespace std::chrono;

    // get current time
    const system_clock::time_point now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    const auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt{};
	localtime_s(&bt, &timer);

    std::wstringstream oss;

    oss << std::put_time(&bt, L"%H:%M:%S"); // HH:MM:SS
    oss << '.' << PadLeftW(ms.count(), L'0', 3);
    return oss.str();
}


ChronoHelper* ChronoHelper::Next()
{
	using namespace std;
	using namespace std::chrono;

	lock_guard<mutex> lock(m_timePointMutex);
	if ( m_previousTimePoint == nullptr )
	{
		m_thisTimePoint = make_shared<time_point<system_clock>>(time_point<system_clock>());
		*m_thisTimePoint = system_clock::now();
		m_previousTimePoint = make_shared<time_point<system_clock>>(time_point<system_clock>());
	}
	(*m_previousTimePoint) = *m_thisTimePoint;
	(*m_thisTimePoint) = system_clock::now();
	return this;
}

milliseconds ChronoHelper::ElapsedMilliseconds()
{
	lock_guard<mutex> lock(m_timePointMutex);
	if ( m_previousTimePoint == nullptr )
	{
		return milliseconds{0};
	}
	const milliseconds elapsed = duration_cast<milliseconds>(*m_thisTimePoint - *m_previousTimePoint);
	return elapsed;
	
}

__int64 ChronoHelper::ElapsedMillisecondsAsInt64()
{
	return static_cast<__int64>(ElapsedMilliseconds().count());
}

seconds ChronoHelper::ElapsedSeconds()
{
	return duration_cast<seconds>(ElapsedMilliseconds());
}

__int64 ChronoHelper::ElapsedSecondsAsInt64()
{
	return static_cast<__int64>(ElapsedSeconds().count());
}


std::wstring ChronoHelper::TimeStamp()
{
	lock_guard<mutex> lock(m_timePointMutex);
    using namespace std::chrono;
    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(m_thisTimePoint->time_since_epoch()) % 1000;
    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(*m_thisTimePoint);
    // convert to broken time
    std::tm bt{};
	localtime_s(&bt, &timer);
    std::wstringstream oss;
    oss << std::put_time(&bt, L"%H:%M:%S"); // HH:MM:SS
    oss << '.' << PadLeftW(ms.count(), L'0', 3);
    return oss.str();
}

} // namespace commonStd