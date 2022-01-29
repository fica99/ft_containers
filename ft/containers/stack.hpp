/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:51:51 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/29 00:54:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template <class T, class Container = vector<T> >
class stack
{
public:
    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
    explicit stack(const container_type &cont = container_type()) : c(cont) {}
    stack(const stack& other) : c(other.c) {}
    ~stack(void) {}
    stack& operator=(const stack& other)
    {
        if (this != &other)
        {
            c = other.c;
        }
        return *this;
    }
    reference top(void) { return c.back(); }
    const_reference top(void) const { return c.back(); }
    bool empty(void) const { return c.empty(); }
    size_type size(void) const { return c.size(); }
    void push(const value_type& value) { c.push_back(value); }
    void pop(void) { c.pop_back(); }
    template <class U, class Cont>
    friend bool operator==(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
    template <class U, class Cont>
    friend bool operator!=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
    template <class U, class Cont>
    friend bool operator<(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
    template <class U, class Cont>
    friend bool operator<=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
    template <class U, class Cont>
    friend bool operator>(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
    template <class U, class Cont>
    friend bool operator>=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
protected:
    container_type c;
};

template < class U, class Cont >
bool operator==(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
{
    return lhs.c == rhs.c;
}

template < class U, class Cont >
bool operator!=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
{
    return lhs.c != rhs.c;
}

template < class U, class Cont >
bool operator<(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
{
    return lhs.c < rhs.c;
}

template <class U, class Cont>
bool operator<=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
{
    return lhs.c <= rhs.c;
}

template < class U, class Cont >
bool operator>(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
{
    return lhs.c > rhs.c;
}

template < class U, class Cont >
bool operator>=(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs)
{
    return lhs.c >= rhs.c;
}

}

#endif // STACK_HPP
