#pragma once

#include <iterator>
#include <type_traits>

template <typename T>
struct is_random_access_iterator : std::is_same <
    typename std::iterator_traits<T>::iterator_category
    , std::random_access_iterator_tag>
{};

template <typename T>
struct is_bidirectional_iterator : std::is_same <
    typename std::iterator_traits<T>::iterator_category
    , std::bidirectional_iterator_tag>
{};

template <typename T>
struct is_forward_iterator : std::is_same <
    typename std::iterator_traits<T>::iterator_category
    , std::forward_iterator_tag>
{};
