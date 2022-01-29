/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:32:59 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/29 09:08:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template < typename T >
class random_access_iterator
{
public:
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    explicit random_access_iterator(T* ptr = NULL) : m_Ptr(ptr) { }
    random_access_iterator(const random_access_iterator& other) : m_Ptr(other.m_Ptr) { }
    random_access_iterator &operator=(const random_access_iterator& other)
    {
        if (this != &other)
        {
            m_Ptr = other.m_Ptr;
        }
        return *this;
    }
    T* base(void) const { return m_Ptr; }
    T& operator*(void) const { return *m_Ptr; }
    T* operator->(void) const { return &operator*(); }
    T& operator[](difference_type diff) { return m_Ptr[diff]; }
    random_access_iterator& operator++(void)
    {
        ++m_Ptr;
        return *this;
    }
    random_access_iterator& operator--(void)
    {
        --m_Ptr;
        return *this;
    }
    random_access_iterator operator++(int)
    {
        random_access_iterator tmp = *this;
        ++m_Ptr;
        return tmp;
    }
    random_access_iterator operator--(int)
    {
        random_access_iterator tmp = *this;
        --m_Ptr;
        return tmp;
    }
    random_access_iterator operator+(difference_type diff) const { return random_access_iterator(m_Ptr + diff); }
    random_access_iterator operator-(difference_type diff) const { return random_access_iterator(m_Ptr - diff); }
    random_access_iterator& operator+=(difference_type diff)
    {
        m_Ptr += diff;
        return *this;
    }
    random_access_iterator& operator-=(difference_type diff)
    {
        m_Ptr -= diff;
        return (*this);
    }
    operator random_access_iterator<const T>() const { return (random_access_iterator<const T>(m_Ptr)); }
private:
    pointer m_Ptr;
};

template < typename T1, typename T2 >
bool operator==(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() == rhs.base();
}

template < typename T1, typename T2 >
bool operator!=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() != rhs.base();
}

template < typename T1, typename T2 >
bool operator<(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() < rhs.base();
}

template < typename T1, typename T2 >
bool operator<=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() <= rhs.base();
}

template < typename T1, typename T2 >
bool operator>(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() > rhs.base();
}

template < typename T1, typename T2 >
bool operator>=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() >= rhs.base();
}

template < typename T >
random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& it)
{
    return random_access_iterator<T>(it.base() + n);
}

template < typename T >
typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
{
    return (lhs.base() - rhs.base());
}

template < typename T1, typename T2 >
typename random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return (lhs.base() - rhs.base());
}

}
#endif // RANDOM_ACCESS_ITERATOR_HPP
