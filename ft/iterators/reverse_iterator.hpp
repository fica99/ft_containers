/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:00:48 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/29 09:41:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template < class Iter >
class reverse_iterator
{
public:
    typedef Iter iterator_type;
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;

    reverse_iterator() : current() { }
    explicit reverse_iterator(iterator_type x) : current(x) { }
    template <class U>
    reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) { }
    template <class U>
    reverse_iterator& operator=(const reverse_iterator<U>& other)
    {
        if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&other))
        {
            return (*this);
        }
        current = other.base();
        return *this;
    }
    iterator_type base(void) const { return current; }
    reference operator*(void) const { return (--iterator_type(current)).operator*(); }
    pointer operator->(void) const { return &operator*(); }
    reference operator[](difference_type n) const { return base()[-n - 1]; }
    reverse_iterator& operator++(void)
    {
        current.operator--();
        return *this;
    }
    reverse_iterator operator++(int)
    {
        return reverse_iterator(current.operator--(0));
    }
    reverse_iterator& operator--(void)
    {
        ++current;
        return *this;
    }
    reverse_iterator operator--(int)
    {
        return reverse_iterator(current.operator++(0));
    }

    template <class U>
    difference_type operator-(const reverse_iterator<U> &u)
    {
        return u.base() - current;
    };
    reverse_iterator& operator+=(difference_type diff)
    {
        current -=  diff;
        return *this;
    }
    reverse_iterator operator+(difference_type diff) const { return reverse_iterator(current.operator-(diff)); }

    reverse_iterator& operator-=(difference_type diff)
    {
        current += diff;
        return *this;
    }
    reverse_iterator operator-(difference_type diff) const { return reverse_iterator(current.operator+(diff)); }
    
    template <class U>
    bool operator==(const reverse_iterator<U> &rhs) const { return current == rhs.base(); };
    template <class U>
    bool operator!=(const reverse_iterator<U> &rhs) const { return current != rhs.base(); };
    template <class U>
    bool operator<(const reverse_iterator<U> &rhs) const { return current > rhs.base(); };
    template <class U>
    bool operator<=(const reverse_iterator<U> &rhs) const { return current >= rhs.base(); };
    template <class U>
    bool operator>(const reverse_iterator<U> &rhs) const { return current < rhs.base(); };
    template <class U>
    bool operator>=(const reverse_iterator<U> &rhs) const { return current <= rhs.base(); };

    friend reverse_iterator operator+(difference_type n, const reverse_iterator &rhs)
    {
        return rhs.operator+(n);
    };

protected:
    iterator_type current;
};

}
#endif // REVERSE_ITERATOR_HPP
