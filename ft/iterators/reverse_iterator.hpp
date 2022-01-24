/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:00:48 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/24 21:08:36 by aashara-         ###   ########.fr       */
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
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;

// Member functions
    reverse_iterator() { current(); }
    explicit reverse_iterator(iterator_type x) : current(x) {}
    reverse_iterator(const reverse_iterator& other) : current(other.current) {}
    reverse_iterator& operator=(const reverse_iterator& other)
    {
        if (&other != this)
        {
            current = other.current;
        }
        return *this;
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
    reverse_iterator& operator++(void)
    {
        --current;
        return *this;
    }
    reverse_iterator& operator--(void)
    {
        ++current;
        return *this;
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
    reverse_iterator operator+(difference_type diff) const { return (current - diff); }
    reverse_iterator operator-(difference_type diff) const { return (current + diff); }
    reverse_iterator& operator+=(difference_type diff)
    {
        current = current - diff;
        return *this;
    }
    reverse_iterator& operator-=(difference_type diff)
    {
        current = current + diff;
        return *this;
    }
protected:
// Member objects
    iterator_type     current;
};

// Non-member functions
template<class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() == rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() != rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() > rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() >= rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() < rhs.base();
}

template<class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() <= rhs.base();
}

template<class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
{
    return reverse_iterator<Iterator>(it.base() - n);
}

template<class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

}
#endif // REVERSE_ITERATOR_HPP
