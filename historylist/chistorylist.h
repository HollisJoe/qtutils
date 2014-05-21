#pragma once

#include <deque>
#include <limits>
#include <assert.h>

template <typename T>
class CHistoryList
{
public:
	CHistoryList(): _currentIndex(std::numeric_limits<size_t>::max()) {}

// Access and status
	inline bool empty() const {return _list.empty();}
	inline size_t size() const {return _list.size();}

	inline typename std::deque<T>::const_iterator begin() const {return _list.begin();}
	inline typename std::deque<T>::const_iterator end() const {return _list.end();}

	inline const T& front() const {return _list.front();}
	inline const T& back() const {return _list.back();}

	inline const T& operator[](size_t index) const {return _list[index];}

	inline bool historyLocationSet() const {return _currentIndex <= _list.size();}

	size_t currentIndex() const;
	const T& currentItem() const;

// Actions
	void addLatest(const T& item);
	const T& navigateBack(); 
	const T& navigateForward();

private:
	std::deque<T> _list;
	size_t         _currentIndex;
};

template <typename T>
const T& CHistoryList<T>::navigateForward()
{
	if (_currentIndex < size()-1)
		_currentIndex = currentIndex() + 1;
	return currentItem();
}

template <typename T>
const T& CHistoryList<T>::navigateBack()
{
	if (_currentIndex > 0)
		_currentIndex = currentIndex() - 1;
	return currentItem();
}

template <typename T>
const T& CHistoryList<T>::currentItem() const
{
	if (!empty())
		return _list[currentIndex()];
	else
	{
		static const T blank;
		return blank;
	}
}

template <typename T>
size_t CHistoryList<T>::currentIndex() const
{
	if (empty())
		return std::numeric_limits<size_t>::max();
	else if (_currentIndex < size())
		return _currentIndex;
	else
		return size() - 1;
}

template <typename T>
void CHistoryList<T>::addLatest( const T& item )
{
	const auto currentPosition = std::find(_list.begin(), _list.end(), item);
	if (currentPosition == _list.end())
		_list.push_back(item);
	else if (size() > 1 && currentPosition != _list.end() - 1)
		std::rotate(currentPosition, currentPosition + 1, _list.end());

	assert(!empty());
	if (size() > 1 && _currentIndex <= size()-2) // If we already were at the end of the list, just move the index to the newest element
	{
		// If we were not in the end, move and insert [0; _currentIndex] just before end
		decltype(_list) newList;
		for (size_t i = _currentIndex + 1; i < size() - 1; ++i)
			newList.push_back(_list[i]);
		for (size_t i = 0; i <= _currentIndex; ++i)
			newList.push_back(_list[i]);
		_list = newList;
		_list.emplace_back(item);
	}

	_currentIndex = _list.size()-1;
}