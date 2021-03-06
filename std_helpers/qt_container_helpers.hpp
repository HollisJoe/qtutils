#pragma once

#include <algorithm>
#include <vector>

template <typename T, template<typename> class Container>
std::vector<T> to_vector(const Container<T>& qtContainer)
{
	std::vector<T> v;
	v.reserve((size_t)qtContainer.size());

	std::copy(std::cbegin(qtContainer), std::cend(qtContainer), std::back_inserter(v));
	return v;
}

template <typename T, class Container>
std::vector<T> to_vector(const Container& qtContainer)
{
	std::vector<T> v;
	v.reserve((size_t)qtContainer.size());

	std::copy(std::cbegin(qtContainer), std::cend(qtContainer), std::back_inserter(v));
	return v;
}

template <template <typename> class StdContainer, typename T, template <typename> class QtContainer>
QtContainer<T> from_std_container(const StdContainer<T>& stdContainer)
{
	QtContainer<T> qtContainer;
	std::copy(std::cbegin(stdContainer), std::cend(stdContainer), std::back_inserter(qtContainer));

	return qtContainer;
}
