/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:00:48 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/26 20:20:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template < class Iter >
class reverse_iterator : public iterator<
                                      typename iterator_traits<Iter>::iterator_category
                                    , typename iterator_traits<Iter>::value_type
                                    , typename iterator_traits<Iter>::difference_type
                                    , typename iterator_traits<Iter>::pointer
                                    , typename iterator_traits<Iter>::reference
                                        >{
public:
    typedef Iter iterator_type;
    typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    typedef typename iterator_traits<Iter>::value_type value_type;
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::pointer pointer;
    typedef typename iterator_traits<Iter>::reference reference;

    reverse_iterator() { current(); }
    explicit reverse_iterator(iterator_type x) : current(x) { }
    template <class U>
    reverse_iterator(const reverse_iterator<U>& other) : current(other.current) { }
    template <class U>
    reverse_iterator& operator=(const reverse_iterator<U>& other)
    {
        if (this != &other)
        {
            current = other.current;
        }
        return *this;
    }
    iterator_type base(void) const { return current; }
    reference operator*(void) const
    {
        Iter tmp = current;
        return *--tmp;
    }
    pointer operator->(void) const { return &operator*(); }
    reference operator[](difference_type n) const { return base()[-n - 1]; }
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
        current -=  diff;
        return *this;
    }
    reverse_iterator& operator-=(difference_type diff)
    {
        current += diff;
        return *this;
    }
protected:
    iterator_type current;
};

template < class Iterator1, class Iterator2 >
bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() == rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() != rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() > rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() >= rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() < rhs.base();
}

template < class Iterator1, class Iterator2 >
bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() <= rhs.base();
}

template < class Iter >
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
{
    return reverse_iterator<Iter>(it.base() - n);
}
template < class Iter >
typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
    return rhs.base() - lhs.base();
}

}
#endif // REVERSE_ITERATOR_HPP
