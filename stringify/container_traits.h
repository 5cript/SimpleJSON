#ifndef CONTAINER_TRAITS_H_INCLUDED
#define CONTAINER_TRAITS_H_INCLUDED

// and iterator traits :D

#include <iterator>
#include <type_traits>

template <typename T, template <typename, class = std::allocator <T> > class ContainerT>
struct has_random_access_iterator : std::is_same <
    typename std::iterator_traits<typename ContainerT<T>::iterator>::iterator_category
    , std::random_access_iterator_tag>
{};

template <typename T, template <typename, class = std::allocator <T> > class ContainerT>
struct has_bidirectional_iterator : std::is_same <
    typename std::iterator_traits<typename ContainerT<T>::iterator>::iterator_category
    , std::bidirectional_iterator_tag>
{};

template <typename T, template <typename, class = std::allocator <T> > class ContainerT>
struct has_forward_iterator : std::is_same <
    typename std::iterator_traits<typename ContainerT<T>::iterator>::iterator_category
    , std::forward_iterator_tag>
{};

#endif // CONTAINER_TRAITS_H_INCLUDED
