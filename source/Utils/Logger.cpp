#include "stdafx.h"

#include "Utils/Logger.h"

#include <iostream>
#include <fstream>

ELogLevel		Logger::m_LogLevel			= ELogLevel::LogInfo;
ETextColor		Logger::m_DefaultTextColor	= ETextColor::White;
ETextStyle		Logger::m_DefaultTextStyle	= ETextStyle::Regular;

const std::string_view Logger::m_TextColorsDatabase[(size_t)ETextColor::Count] =
{
	"90m",		// Black
	"91m",		// Red
	"92m",		// Green
	"93m",		// Yellow
	"94m",		// Blue
	"95m",		// Magenta
	"96m",		// Cyan
	"97m"		// White
};

const std::string_view Logger::m_TextStylesDatabase[(size_t)ETextStyle::Count] =
{
	"\033[0;",	// Regular
	"\033[2;",	// Dim
	"\033[3;",	// Italic
	"\033[4;",	// Underlined
	"\033[9;",	// CrossedOut
	"\033[21;"	// DoublyUnderlined
};

////////////////////////////////////////////////////////////////////////////////
void Logger::Log(const std::string& text)
{
	Log(text, m_DefaultTextColor, m_DefaultTextStyle);
}

////////////////////////////////////////////////////////////////////////////////
void Logger::Log(const std::string& text, ETextColor textColor)
{
	Log(text, textColor, m_DefaultTextStyle);
}

////////////////////////////////////////////////////////////////////////////////
void Logger::Log(const std::string& text, ETextColor textColor, ETextStyle textStyle)
{
	ReturnIf(m_LogLevel < ELogLevel::LogText);
	PrintLineToConsole(text, textColor, textStyle, EMessageType::Text);
}

////////////////////////////////////////////////////////////////////////////////
void Logger::LogError(const std::string& text)
{
	ReturnIf(m_LogLevel < ELogLevel::LogError);
	PrintLineToConsole("[ERROR] " + text, ETextColor::Red, ETextStyle::Regular, EMessageType::Error);
}

////////////////////////////////////////////////////////////////////////////////
void Logger::LogWarning(const std::string& text)
{
	ReturnIf(m_LogLevel < ELogLevel::LogWarning);
	PrintLineToConsole("[WARNING] " + text, ETextColor::Yellow, ETextStyle::Regular, EMessageType::Error);
}

////////////////////////////////////////////////////////////////////////////////
void Logger::LogInfo(const std::string& text)
{
	ReturnIf(m_LogLevel < ELogLevel::LogInfo);
	PrintLineToConsole("[INFO] " + text, ETextColor::White, ETextStyle::Regular, EMessageType::Text);
}

////////////////////////////////////////////////////////////////////////////////
void Logger::SetLogLevel(ELogLevel logLevel)
{
	m_LogLevel = logLevel;
}

////////////////////////////////////////////////////////////////////////////////
ELogLevel Logger::GetLogLevel()
{
	return m_LogLevel;
}

////////////////////////////////////////////////////////////////////////////////
void Logger::TestLogging()
{
	const auto previousLogLevel = GetLogLevel();

	Log("----------------------------------------");
	Log("Text, log level = " + std::to_string((int8_t)GetLogLevel()), ETextColor::Blue);
	LogInfo("Info 1");
	LogWarning("Warning 1");
	LogError("Error 1");

	Log("----------------------------------------");
	SetLogLevel(ELogLevel::LogInfo);
	Log("Text, log level = " + std::to_string((int8_t)GetLogLevel()), ETextColor::Cyan, ETextStyle::Italic);
	LogInfo("Info 2");
	LogWarning("Warning 2");
	LogError("Error 2");

	Log("----------------------------------------");
	SetLogLevel(ELogLevel::LogWarning);
	Log("Text, log level = " + std::to_string((int8_t)GetLogLevel()), ETextColor::Green, ETextStyle::CrossedOut);
	LogInfo("Info 3");
	LogWarning("Warning 3");
	LogError("Error 3");

	Log("----------------------------------------");
	SetLogLevel(ELogLevel::LogError);
	Log("Text, log level = " + std::to_string((int8_t)GetLogLevel()), ETextColor::Magenta, ETextStyle::DoublyUnderlined);
	LogInfo("Info 4");
	LogWarning("Warning 4");
	LogError("Error 4");

	Log("----------------------------------------");
	SetLogLevel(ELogLevel::LogText);
	Log("Text, log level = " + std::to_string((int8_t)GetLogLevel()));
	LogInfo("Info 5");
	LogWarning("Warning 5");
	LogError("Error 5");

	Log("----------------------------------------");
	SetLogLevel(ELogLevel::LogNone);
	Log("Text, log level = " + std::to_string((int8_t)GetLogLevel()));
	LogInfo("Info 6");
	LogWarning("Warning 6");
	LogError("Error 6");
	Log("----------------------------------------");

	SetLogLevel(previousLogLevel);
}

////////////////////////////////////////////////////////////////////////////////
void Logger::PrintLineToConsole(const std::string& text,
	ETextColor textColor, ETextStyle textStyle, EMessageType messageType)
{
	AssertReturnIf(!IsEnumValueValid(messageType));
	AssertReturnIf(!IsEnumValueValid(textColor));
	AssertReturnIf(!IsEnumValueValid(textStyle));

	auto print = [&text, &textColor, &textStyle](std::ostream& outStream)
		{
			static const auto& defaultTextColorString = m_TextColorsDatabase[(size_t)m_DefaultTextColor];
			static const auto& defaultTextStyleString = m_TextStylesDatabase[(size_t)m_DefaultTextStyle];

			const auto& textColorString = m_TextColorsDatabase[(size_t)textColor];
			const auto& textStyleString = m_TextStylesDatabase[(size_t)textStyle];

			outStream << textStyleString << textColorString;
			outStream << text << '\n';
			outStream << defaultTextStyleString << defaultTextColorString;
		};

	// Why do I even need different streams?
	switch (messageType)
	{
	case EMessageType::Text:
		print(std::cout);
		break;

	case EMessageType::Error:
		print(std::cerr);
		LogErrorToFile(text);
		break;

	default:
		Assert("Invalid message type.");
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
void Logger::LogErrorToFile(const std::string& text)
{
	static FileIO file(Format("error_{0}.txt",
		Time::GetNow().GetString(ETimeStringFormat::Timestamp)));

	const auto timestamp = Time::GetNow().GetString(ETimeStringFormat::Default);
	file.Write(Format("[{0}] ", timestamp) + text + "\n");
}