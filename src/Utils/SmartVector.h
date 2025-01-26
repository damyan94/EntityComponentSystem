#pragma once

////////////////////////////////////////////////////////////////////////////////
template <typename T>
class SmartVector
{
public:
	static constexpr size_t InvalidIndex = -1;

public:
	SmartVector() = default;
	~SmartVector() = default;

	size_t Add(const T& item);
	void Remove(size_t index);

	T Get(size_t index) const;
	T& GetMutable(size_t index);

	void Resize(size_t size);
	void Reserve(size_t size);

	bool IsIndexValid(size_t index) const;

private:
	bool HasFreeIndex() const;

	size_t PopFreeIndex();
	void AddFreeIndex(size_t index);

private:
	std::vector<T> m_Data;
	std::deque<size_t> m_FreeIndeces;
};

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline size_t SmartVector<T>::Add(const T& item)
{
	size_t index = PopFreeIndex();

	if (IsIndexValid(index))
	{
		m_Data[index] = item;
	}
	else
	{
		m_Data.emplace_back(item);
		index = m_Data.size() - 1;
	}

	return index;
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void SmartVector<T>::Remove(size_t index)
{
	AssertReturnIf(!IsIndexValid(index));

	m_Data[index] = T();
	AddFreeIndex(index);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T SmartVector<T>::Get(size_t index) const
{
	AssertReturnIf(!IsIndexValid(index), T());

	return m_Data[index];
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline T& SmartVector<T>::GetMutable(size_t index)
{
	AssertReturnIf(!IsIndexValid(index), T());

	return m_Data[index];
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void SmartVector<T>::Resize(size_t size)
{
	m_Data.resize(size);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void SmartVector<T>::Reserve(size_t size)
{
	m_Data.reserve(size);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool SmartVector<T>::IsIndexValid(size_t index) const
{
	return index >= 0 && index < m_Data.size();
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool SmartVector<T>::HasFreeIndex() const
{
	return !m_FreeIndeces.empty();
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline size_t SmartVector<T>::PopFreeIndex()
{
	ReturnIf(!HasFreeIndex(), InvalidIndex);

	const auto result = m_FreeIndeces.front();
	m_FreeIndeces.pop_front();

	return result;
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline void SmartVector<T>::AddFreeIndex(size_t index)
{
	m_FreeIndeces.emplace_back(index);
}