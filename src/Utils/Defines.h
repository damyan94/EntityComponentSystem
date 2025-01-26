#pragma once

typedef void(*VoidFunction)();
typedef int32_t ComponentId;

#define MAX_ENTITIES						100000
#define INITIAL_ENTITIES					100
#define INVALID_COMPONENT_ID				-1

#define _Stringify_(X) #X
#define _Stringify(X) _Stringify_(X)

#ifdef _MSC_VER
#define _DebugBreak __debugbreak()
#else
#define _DebugBreak
#endif

#define _DebugBreakInfo(_Reason)\
"Reason: " _Stringify(_Reason) \
", File: " __FILE__ \
", Line: " _Stringify(__LINE__)

#define _DebugBreakInfoMsgBox(_Reason)\
"Reason: " _Stringify(_Reason) \
"\nFile: " __FILE__ \
"\nLine: " _Stringify(__LINE__)

#define _MessageBoxError(_Text)\
UI::ShowMessageBoxOK("Error!", _Text, UI::EMessageBoxIcon::Error)

#define Assert(...)\
Logger::LogError(_DebugBreakInfo(__VA_ARGS__));\
_MessageBoxError(_DebugBreakInfoMsgBox(__VA_ARGS__));\
_DebugBreak

#define Format(_Text, ...)			std::format(_Text, __VA_ARGS__)

#define ReturnIf(_Condition, ...)	if (_Condition) return __VA_ARGS__
#define BreakIf(_Condition)			if (_Condition) break
#define ContinueIf(_Condition)		if (_Condition) continue

#define AssertReturnIf(_Condition, ...)		do { if (_Condition) { Assert(_Condition); return __VA_ARGS__; }} while(false)
#define AssertBreakIf(_Condition)			do { if (_Condition) { Assert(_Condition); break; }} while(false)
#define AssertContinueIf(_Condition)		do { if (_Condition) { Assert(_Condition); continue; }} while(false)

#define SafeDelete(_Pointer)				do { if (_Pointer) { delete _Pointer; _Pointer = nullptr; }} while(false)
#define SafeDeleteArray(_Pointer)			do { if (_Pointer) { delete[] _Pointer; _Pointer = nullptr; }} while(false)

////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool IsEnumValueValid(const T value)
{
	return value > T::Invalid && value < T::Count;
}

////////////////////////////////////////////////////////////////////////////////
enum class ELogLevel
	: int8_t
{
	Invalid = -1
	, LogNone		// Log nothing
	, LogText		// Log text
	, LogError		// Log text and errors
	, LogWarning	// Log text, errors and warnings
	, LogInfo		// Log everything
	, Count
};

////////////////////////////////////////////////////////////////////////////////
enum class ETextColor
	: int8_t
{
	Invalid = -1
	, Black
	, Red
	, Green
	, Yellow
	, Blue
	, Magenta
	, Cyan
	, White
	, Count
};

////////////////////////////////////////////////////////////////////////////////
enum class ETextStyle
	: int8_t
{
	Invalid = -1
	, Regular
	, Dim
	, Italic
	, Underlined
	, CrossedOut
	, DoublyUnderlined
	, Count
};

////////////////////////////////////////////////////////////////////////////////
enum class EMessageType
	: int8_t
{
	Invalid = -1
	, Text
	, Error
	, Count
};