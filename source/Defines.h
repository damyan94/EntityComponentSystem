#pragma once

#include <cstdint>
#include "Utils/Logging.h"

typedef void(*VoidFunction)();
typedef int32_t ComponentId;

#define MAX_ENTITIES						1000
#define MAX_COMPONENTS						1000
#define INITIAL_ENTITIES					100
#define INVALID_COMPONENT_ID				-1

#define FileAndLineInfo						"[FILE] " __FILE__ " [LINE] " _STRINGIZE(__LINE__)

#define LogError(Text)						Utils::LogConsole("[ERROR] " Text)
#define LogWarning(Text)					Utils::LogConsole("[WARNING] " Text)
#define Log(Text)							Utils::LogConsole(Text)

#define Assert(Text)						Utils::Assert(Text)
#define AssertIf(Condition, Text)			if(Condition) Utils::Assert(Text)

#define ReturnIf(Condition, ...)			if(Condition) return __VA_ARGS__
#define ContinueIf(Condition, ...)			if(Condition) continue __VA_ARGS__
#define BreakIf(Condition, ...)				if(Condition) break __VA_ARGS__

#define AssertReturnIf(Condition, ...)		do { if(Condition) { Assert(FileAndLineInfo ": " #Condition); return __VA_ARGS__; }} while(false)
#define AssertContinueIf(Condition, ...)	do { if(Condition) { Assert(FileAndLineInfo ": " #Condition); continue __VA_ARGS__; }} while(false)
#define AssertBreakIf(Condition, ...)		do { if(Condition) { Assert(FileAndLineInfo ": " #Condition); break __VA_ARGS__; }} while(false)

#define SafeDelete(Pointer)					do { if(Pointer) { delete Pointer; Pointer = nullptr; }} while(false)
#define SafeDeleteArray(Pointer)			do { if(Pointer) { delete[] Pointer; Pointer = nullptr; }} while(false)