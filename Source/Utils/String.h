#pragma once

using Hash32 = uint32_t;
using Hash64 = uint64_t;

namespace Utils
{
// Jenkins One At A Time hashing algorithm
template <typename T>
T Hash(const char* str);
} // !namespace Utils


////////////////////////////////////////////////////////////////////////////////
class String
	: public std::string
{
public:
	String();
	String(const char* str);
	String(const std::string& other);
	String(std::string&& other) noexcept;

	String(const String& other);
	String(String&& other) noexcept;

	~String() = default;

	void Rehash();

	operator std::string() const;

	// Comparison operators using hash
	bool operator==(const String& other) const;
	bool operator==(const std::string& other) const;
	bool operator==(const char* other) const;
	bool operator!=(const String& other) const;
	bool operator!=(const std::string& other) const;
	bool operator!=(const char* other) const;

	// Concatenation operator
	String operator+(const String& other) const;

	// Subtraction operator (removes occurrences of the second string)
	String operator-(const String& other) const;

	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;

	Hash64 GetHash() const;

private:
	Hash64 m_Hash;
};

using Lines = std::vector<String>;