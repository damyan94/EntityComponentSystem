#pragma once

////////////////////////////////////////////////////////////////////////////////
class Logger
{
public:
	Logger() = delete;
	~Logger() = default;

	static void Log(const std::string& text);
	static void Log(const std::string& text, ETextColor textColor);
	static void Log(const std::string& text, ETextColor textColor, ETextStyle textStyle);

	static void LogError(const std::string& text);
	static void LogWarning(const std::string& text);
	static void LogInfo(const std::string& text);

	static void SetLogLevel(ELogLevel logLevel);
	static ELogLevel GetLogLevel();

	static void TestLogging();

private:
	static void PrintLineToConsole(const std::string& text, ETextColor textColor, ETextStyle textStyle, EMessageType messageType);
	static void LogErrorToFile(const std::string& text);

private:
	static ELogLevel		m_LogLevel;
	static ETextColor		m_DefaultTextColor;
	static ETextStyle		m_DefaultTextStyle;

private:
	static const std::string_view m_TextColorsDatabase[(size_t)ETextColor::Count];
	static const std::string_view m_TextStylesDatabase[(size_t)ETextStyle::Count];
};