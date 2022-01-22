/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:10:21 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/22 01:47:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstddef>
#include <memory>

namespace ft
{

template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    // iterator;
    // const_iterator;
    // reverse_iterator;
    // const_reverse_iterator;

    explicit vector(const allocator_type& allocator = allocator_type()) : 
        m_Arr(NULL), 
        m_Size(0), 
        m_Capacity(0), 
        m_Allocator(allocator) 
    {
    }
    explicit vector(size_type count, const_reference value = value_type(), const allocator_type& allocator = allocator_type()) :
        m_Arr(NULL), 
        m_Size(count), 
        m_Capacity(count), 
        m_Allocator(allocator)
    {
        m_Arr = m_Allocator.allocate(count);
        for (size_type i = 0; i < count; ++i)
            m_Allocator.construct(m_Arr + i, value);
    }

    bool empty(void) const { return m_Size == 0; }
    size_type size(void) const { return m_Size; }
    size_type max_size(void) const { return m_Allocator.max_size(); }
    size_type capacity(void) const { return m_Capacity; }

    reference operator[](size_type n) { return m_Arr[n]; }
    const_reference operator[](size_type n) const { return m_Arr[n]; }

private:
    pointer m_Arr;
    size_type m_Size;
    size_type m_Capacity;
    allocator_type m_Allocator;
};

}

#endif // VECTOR_HPP
