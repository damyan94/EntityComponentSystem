#include "stdafx.h"

#include "Utils/String.h"

////////////////////////////////////////////////////////////////////////////////
namespace Utils
{
// Jenkins One At A Time hashing algorithm
template <typename T>
T Hash(const char* str)
{
    T hash = 0;
    size_t length = strlen(str);

    if (length <= 0)
        return hash;

    for (size_t i = 0; i < length; i++)
    {
        hash += str[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;

    return hash;
}
} // namespace Utils

////////////////////////////////////////////////////////////////////////////////
String::String()
    : std::string()
    , m_Hash(0) 
{
}

////////////////////////////////////////////////////////////////////////////////
String::String(const char* str)
    : std::string(str)
    , m_Hash(0)
{
    Rehash();
}

////////////////////////////////////////////////////////////////////////////////
String::String(const std::string& other) 
    : std::string(other)
    , m_Hash(0)
{
    Rehash();
}

////////////////////////////////////////////////////////////////////////////////
String::String(std::string&& other) noexcept 
    : std::string(std::move(other))
    , m_Hash(0) 
{
    Rehash(); 
}

////////////////////////////////////////////////////////////////////////////////
String::String(const String& other)
    : std::string(other)
    , m_Hash(other.m_Hash)
{
}

////////////////////////////////////////////////////////////////////////////////
String::String(String&& other) noexcept
    : std::string(std::move(other))
    , m_Hash(other.m_Hash)
{
    other.m_Hash = 0;
}

////////////////////////////////////////////////////////////////////////////////
void String::Rehash()
{
    m_Hash = Utils::Hash<Hash64>(c_str());
}

////////////////////////////////////////////////////////////////////////////////
String::operator std::string() const
{ 
    return *this; 
}

////////////////////////////////////////////////////////////////////////////////
bool String::operator==(const String& other) const
{
    return (m_Hash == other.m_Hash) &&
        (static_cast<const std::string&>(*this) == static_cast<const std::string&>(other));
}

////////////////////////////////////////////////////////////////////////////////
bool String::operator==(const std::string& other) const
{
    return m_Hash == Utils::Hash<Hash64>(other.c_str());
}

////////////////////////////////////////////////////////////////////////////////
bool String::operator==(const char* other) const
{
    return m_Hash == Utils::Hash<Hash64>(other);
}

////////////////////////////////////////////////////////////////////////////////
bool String::operator!=(const String& other) const
{
    return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////
bool String::operator!=(const std::string& other) const
{
    return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////
bool String::operator!=(const char* other) const
{
    return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////
String String::operator+(const String& other) const
{
    return String(static_cast<std::string>(*this) + static_cast<std::string>(other));
}

////////////////////////////////////////////////////////////////////////////////
String String::operator-(const String& other) const
{
    std::string copy = *this;
    size_t pos;

    while ((pos = copy.find(other)) != std::string::npos)
    {
        copy.erase(pos, other.length());
    }

    return String(copy);
}

////////////////////////////////////////////////////////////////////////////////
String& String::operator=(const String& other)
{
    if (this != &other)
    {
        std::string::operator=(other);
        m_Hash = other.m_Hash;
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
String& String::operator=(String&& other) noexcept
{
    if (this != &other)
    {
        std::string::operator=(std::move(other));
        m_Hash = other.m_Hash;
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
Hash64 String::GetHash() const
{
    return m_Hash;
}