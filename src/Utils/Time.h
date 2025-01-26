#pragma once

using TimePoint = uint64_t;

////////////////////////////////////////////////////////////////////////////////
enum class EUnitOfTime
	: int8_t
{
	Invalid = -1
	, Nanosecond
	, Microsecond
	, Millisecond
	, Second
	, Minute
	, Hour
	, Day
	, Week
	, Month
	, Year
	, Count
};

////////////////////////////////////////////////////////////////////////////////
enum class ETimeStringFormat
	: int8_t
{
	Invalid = -1
	, Default	// DD.MM.YYYY hh:mm:ss
	, Timestamp	// YYYYMMDDhhmmss
	, TimePoint	// Time point in microseconds since start of epoch
	, Count
};

////////////////////////////////////////////////////////////////////////////////
class Time
{
public:
	Time();
	~Time() = default;

private:
	Time(TimePoint ms);

public:
	bool operator==(const Time other) const;
	bool operator!=(const Time other) const;
	bool operator>(const Time other) const;
	bool operator<(const Time other) const;
	Time operator+(const Time other) const;
	Time operator-(const Time other) const;

	void				SetToNow();

	TimePoint			GetAs(EUnitOfTime unit) const;
	TimePoint			GetElapsedTimeUntilNow(EUnitOfTime unit) const;
	std::string			GetString(ETimeStringFormat format) const;

public:
	//Time since 1.1.1970 00:00:00 in microseconds
	static Time			GetNow();

private:
	TimePoint			m_Microseconds;
};