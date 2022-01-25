/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:51:51 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/25 17:46:05 by aashara-         ###   ########.fr       */
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
        // Member types
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        // Member functions
        explicit stack(const container_type &cont = Container()) : c(cont) {}
        stack(const stack &other) : c(other.c) {}
        ~stack(void) {}
        stack &operator=(const stack &other)
        {
            if (this != &other)
            {
                c = other.c;
            }
            return *this;
        }

        // Element access
        reference top(void) { return c.back(); }
        const_reference top(void) const { return c.back(); }

        // Capacity
        bool empty(void) const { return c.empty(); }
        size_type size(void) const { return c.size(); }

        // Modifiers
        void push(const value_type &value) { c.push_back(value); }
        void pop(void) { c.pop_back(); }

        // Non-member functions
        template <class T, class Container>
        friend bool operator==(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
        template <class T, class Container>
        friend bool operator!=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
        template <class T, class Container>
        friend bool operator<(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
        template <class T, class Container>
        friend bool operator<=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
        template <class T, class Container>
        friend bool operator>(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);
        template <class T, class Container>
        friend bool operator>=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs);

    protected:
        // Member objects
        container_type c;
    };

    // Non-member functions
    template <class T, class Container>
    bool operator==(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs)
    {
        return lhs.c == rhs.c;
    }

    template <class T, class Container>
    bool operator!=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs)
    {
        return lhs.c != rhs.c;
    }

    template <class T, class Container>
    bool operator<(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs)
    {
        return lhs.c < rhs.c;
    }

    template <class T, class Container>
    bool operator<=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs)
    {
        return lhs.c <= rhs.c;
    }

    template <class T, class Container>
    bool operator>(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs)
    {
        return lhs.c > rhs.c;
    }

    template <class T, class Container>
    bool operator>=(const std::stack<T, Container> &lhs, const std::stack<T, Container> &rhs)
    {
        return lhs.c >= rhs.c;
    }

}

#endif // STACK_HPP
