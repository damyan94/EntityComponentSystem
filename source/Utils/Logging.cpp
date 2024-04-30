#include "Utils/Logging.h"

#include <iostream>

#if defined WIN32 || _WIN32
#include <windows.h>
#endif // !(WIN32 || _WIN32)

namespace Utils
{
////////////////////////////////////////////////////////////////////////////////
void LogConsole(const std::string& text)
{
	std::cout << text << '\n';
}

////////////////////////////////////////////////////////////////////////////////
void Assert(const std::string& text)
{
	LogConsole(std::string("[ASSERT] ") + text);

#if defined WIN32 || _WIN32
	if (IsDebuggerPresent())
	{
		DebugBreak();
	}
#endif // !(WIN32 || _WIN32)
}
} // !namespace Utils