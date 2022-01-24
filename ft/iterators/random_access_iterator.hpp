/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:32:59 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/24 11:57:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template <typename T>
class random_access_iterator : public iterator<random_access_iterator_tag, T>
{
public:
// Member types
    typedef typename iterator<random_access_iterator_tag, T>::iterator_category iterator_category;
    typedef typename iterator<random_access_iterator_tag, T>::value_type value_type;
    typedef typename iterator<random_access_iterator_tag, T>::difference_type difference_type;
    typedef T* pointer;
    typedef T& reference;

// Member functions
    random_access_iterator(void) : m_Ptr(NULL) {}
    explicit random_access_iterator(pointer ptr) : m_Ptr(ptr){}
    random_access_iterator(const random_access_iterator& other) : m_Ptr(other.m_Ptr) {}
    random_access_iterator &operator=(const random_access_iterator& other)
    {
        if (&other != this)
        {
            m_Ptr = other.m_Ptr;
        }
        return *this;
    }
    pointer base(void) const { return m_Ptr; }
    reference operator*(void) const { return *m_Ptr; }
    pointer operator->(void) const { return &operator*(); }
    reference operator[](difference_type diff) { return m_Ptr[diff]; }
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
        ++(*this);
        return tmp;
    }
    random_access_iterator operator--(int)
    {
        random_access_iterator tmp = *this; 
        operator--();
        return random_access_iterator(tmp);
    }
    random_access_iterator operator+(difference_type diff) const { return (m_Ptr + diff); }
    random_access_iterator operator-(difference_type diff) const { return (m_Ptr - diff); }
    random_access_iterator& operator+=(difference_type diff)
    {
        m_Ptr = m_Ptr + diff;
        return (*this);
    }
    random_access_iterator& operator-=(difference_type diff)
    {
        m_Ptr = m_Ptr - diff;
        return (*this);
    }
private:
    pointer m_Ptr;
};

// Non-member functions
template<typename T1, typename T2>
bool operator==(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() == rhs.base();
}

template<typename T1, typename T2>
bool operator!=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() != rhs.base();
}

template<typename T1, typename T2>
bool operator<(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() < rhs.base();
}

template<typename T1, typename T2>
bool operator<=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() <= rhs.base();
}

template<typename T1, typename T2>
bool operator>(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
{
    return lhs.base() > rhs.base();
}

template<typename T1, typename T2>
bool operator>=(const random_access_iterator<T1>& lhs,const random_access_iterator<T2>& rhs)
{
    return lhs.base() >= rhs.base();
}

template<typename T>
random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& it)
{
    return random_access_iterator<T>(it.base() + n);
}

template <typename T>
typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
{
    return (lhs.base() - rhs.base());
}

}
#endif // RANDOM_ACCESS_ITERATOR_HPP
