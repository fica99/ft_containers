/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:00:48 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/23 13:33:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template<class Iter>
class reverse_iterator
{
public:
// Member types
    typedef Iter iterator_type;
    typedef iterator_traits<Iter>::iterator_category iterator_category;
    typedef iterator_traits<Iter>::value_type value_type;
    typedef iterator_traits<Iter>::difference_type difference_type;
    typedef iterator_traits<Iter>::pointer pointer;
    typedef iterator_traits<Iter>::reference reference;

// Member functions
    reverse_iterator()
    {
        current();
    }
    explicit reverse_iterator(iterator_type x) :
        current(x)
    { 
    }
    template<class U>
    reverse_iterator(const reverse_iterator<U>& other) :
        current(other.current)
    {
    }
    template< class U>
    reverse_iterator& operator=(const reverse_iterator<U>& other)
    {
        if (&other == this)
        {
            return;
        }
        current = other.current;
    }
    iterator_type base(void) const { return current; }
    reference operator*(void) const
    {
        iterator_type tmp = current;
        --tmp;
        return *tmp;
    }
    pointer operator->(void) const { return &operator*(); }
    reference operator[](difference_type n) const { return current[-n - 1]; }
    reverse_iterator& operator++()
    {
        --current;
        return *this;
    }
    reverse_iterator& operator--()
    {
        ++current;
        return (*this);
    }
    reverse_iterator operator++(int)
    {
        reverse_iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    reverse_iterator operator--(int)
    {
        reverse_iterator tmp = *this;
        --(*this);
        return tmp;
    }
    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(current - n);
    }
    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(current + n);
    }
    reverse_iterator& operator+=(difference_type n)
    {
        current = current - n;
        return *this;
    }
    reverse_iterator& operator-=(difference_type n)
    {
        current = current + n;
        return *this;
    }
protected:
// Member objects
    iterator_type     current;
};


// Non-member functions
template<class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() == rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() == rhs.base();
}

template<class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() != rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() != rhs.base();
}

template<class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() > rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() > rhs.base();
}

template<class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() >= rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() >= rhs.base();
}

template<class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() < rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() < rhs.base();
}

template<class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() <= rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() <= rhs.base();
}

template< class Iter >
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
{
    return reverse_iterator<Iter>(it.base() - n);
}

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type    operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

}
#endif // REVERSE_ITERATOR_HPP
