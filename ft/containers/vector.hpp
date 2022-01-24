/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:10:21 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/24 10:43:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>

#include "../iterators/iterator.hpp"

namespace ft
{

template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
// Member types
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef typename iterator_traits<iterator>::difference_type difference_type; 
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef random_access_iterator<value_type> iterator;
    typedef random_access_iterator<const value_type> const_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;

// Member functions
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
        {
            m_Allocator.construct(m_Arr + i, value);
        }
    }
    // constructor iterators
    vector(const vector& other) :
        m_Arr(NULL),
        m_Size(0),
        m_Capacity(0),
        m_Allocator(other.m_Allocator)
    {
        // insert values
    }
    ~vector()
    {
        //clear();
        m_Allocator.deallocate(m_Arr, m_Capacity);
    }
    vector &operator=(const vector& x)
    {
        if (&x != this)
        {
            //clear();
            //insert(this->end(), x.begin(), x.end());
        }
        return *this;
    }
    allocator_type get_allocator() const { return m_Allocator; }

// Element access
    reference at(size_type pos)
    {
        range_check(pos);
        return operator[][pos];
    }
    const_reference at(size_type pos) const
    {
        range_check(pos);
        return operator[][pos];
    }
    reference operator[](size_type n) { return m_Arr[n]; }
    const_reference operator[](size_type n) const { return m_Arr[n]; }
    reference front() { return m_Arr[0]; }
    const_reference front() const { return m_Arr[0]; }
    reference back() { return m_Arr[m_Size - 1]; }
    const_reference back() const { return m_Arr[m_Size - 1]; }
    pointer data() { return m_Arr; }
    const_pointer data() const { return m_Arr; }

// Iterators

// Capacity
    bool empty(void) const { return m_Size == 0; }
    size_type size(void) const { return m_Size; }
    size_type max_size(void) const { return m_Allocator.max_size(); }
    void reserve(size_type new_cap)
    {
        if (new_cap > m_Capacity)
        {
            if (new_cap > max_size())
            {
                throw std::length_error("vector::reserve");
            }
            else
            {
                pointer prev_arr = m_Arr;
                size_type prev_capacity = m_Capacity;
                m_Arr = m_Allocator.allocate(new_cap);
                m_Capacity = new_cap;
                for (size_type i = 0; i < m_Size; ++i)
                {
                    m_Allocator.construct(m_Arr + i, prev_arr[i]);
                }
                m_Allocator.deallocate(prev_arr, prev_capacity);
            }
        }
    }
    size_type capacity(void) const { return m_Capacity; }

// Modifiers
    void clear(void)
    {
        for (size_type i = 0; i < m_Size; ++i)
        {
            m_Allocator.destroy(m_Arr + i);
        }
        m_Size = 0;
    }
    void push_back(const_reference value)
    {
        if (m_Size == m_Capacity)
        {
            size_type new_capacity = ((m_Capacity > 0) ? (m_Capacity * 2) : 1);
            reserve(new_capacity);
        }
        m_Allocator.construct(m_Arr + m_Size, value);
        ++m_Size;
    }
    void pop_back(void)
    {
        --m_Size;
        m_Allocator.destroy(m_Arr + m_Size);
    }
    void resize(size_type count, value_type value = value_type())
    {
        if (count < m_Size)
        {
            for (; m_Size > count;)
            {
                --m_Size;
                m_Allocator.destroy(m_Arr + m_Size));
            }
        }
        else
        {
            if (count > max_size())
            {
                throw std::length_error("vector::resize");
            }
            else
            {
                // insert
            }
        }
    }
    void swap(vector& other)
    {
        if (this == &x)
        {
            return;
        }
        arr_copy = m_Arr;
        size_copy = m_Size;
        capacity_copy = m_Capacity;
        allocator_copy = m_Allocator;

        m_Arr = other.m_Arr;
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        m_Allocator = other.m_Allocator;

        other.m_Arr = arr_copy;
        other.m_Size = size_copy;
        other.m_Capacity = capacity_copy;
        other.m_Allocator = allocator_copy;
    }


private:
    void range_check(size_type pos) const
    {
        if (!(pos < m_Size))
        {
            throw std::out_of_range("vector::range_check: pos (which is " +
                std::to_string(pos) + ") >= this->size() (which is " + ft::to_string(m_Size) + ")");
        }
	}
private:
    pointer m_Arr;
    size_type m_Size;
    size_type m_Capacity;
    allocator_type m_Allocator;
};

















template< class T, class Alloc >
bool operator==(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs)
{
    
}

template< class T, class Alloc >
bool operator!=(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs)
{
    return !(lhs == rhs);
}

template< class T, class Alloc >
bool operator<(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs)
{
    
}

template< class T, class Alloc >
bool operator<=(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs)
{
    
}

template< class T, class Alloc >
bool operator>(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs)
{
    
}

template< class T, class Alloc >
bool operator>=(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs)
{

}

template< class T, class Alloc >
void swap(std::vector<T,Alloc>& lhs, std::vector<T,Alloc>& rhs)
{
    lhs.swap(rhs);
}

}

#endif // VECTOR_HPP
