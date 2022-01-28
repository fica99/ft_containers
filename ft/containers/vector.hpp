/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:10:21 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/28 21:58:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cstddef>
#include <stdexcept>

#include "../iterators/random_access_iterator.hpp"
#include "../iterators/iterator.hpp"
#include "../strings/string.hpp"
#include "../algorithms/algorithm.hpp"

namespace ft
{

template<
    class T,
    class Allocator = std::allocator<T>
> class vector
{
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef random_access_iterator<value_type> iterator;
    typedef random_access_iterator<const value_type> const_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;

    explicit vector(const allocator_type& allocator = allocator_type()) : m_Arr(NULL)
                                                                        , m_Size(0)
                                                                        , m_Capacity(0)
                                                                        , m_Allocator(allocator)
    {}
    explicit vector(size_type count,
                    const_reference value = value_type(),
                    const allocator_type& allocator = allocator_type()) : m_Arr(NULL)
                                                                        , m_Size(count)
                                                                        , m_Capacity(count)
                                                                        , m_Allocator(allocator)
    {
        m_Arr = m_Allocator.allocate(count);
        for (size_type i = 0; i < count; ++i)
        {
            m_Allocator.construct(m_Arr + i, value);
        }
    }
    template <class InputIt>
    vector(InputIt first, InputIt last,
                    const allocator_type& allocator = allocator_type()) : m_Arr(NULL)
                                                                        , m_Size(0)
                                                                        , m_Capacity(0)
                                                                        , m_Allocator(allocator)
    {
        assign(first, last);
    }
    vector(const vector& other) : m_Arr(NULL)
                                , m_Size(0)
                                , m_Capacity(0)
                                , m_Allocator(other.m_Allocator)
    {
        assign(other.begin(), other.end());
    }
    ~vector()
    {
        clear();
        m_Allocator.deallocate(m_Arr, m_Capacity);
    }
    vector& operator=(const vector& other)
    {
        if (this != other)
        {
            m_Allocator = other.m_Allocator;
            assign(other.begin(), other.end());
        }
        return *this;
    }
    void assign(size_type count, const value_type &value)
    {
        clear();
        reserve(count);
        for (size_type i = 0; i < count; ++i)
        {
            m_Allocator.construct(m_Arr + i, value);
        }
    }
    template <class InputIt>
    void assign(InputIt first, InputIt last)
    {
        difference_type diff = distance(first, last);
        clear();
        reserve(static_cast<size_type>(diff));
        for (size_t i = 0; first != last; ++first, ++i)
        {
            m_Allocator.construct(m_Arr + i, *first);
        }
    }
    allocator_type get_allocator() const { return m_Allocator; }
    reference at(size_type pos)
    {
        range_check(pos);
        return m_Arr[pos];
    }
    const_reference at(size_type pos) const
    {
        range_check(pos);
        return m_Arr[pos];
    }
    reference operator[](size_type n) { return m_Arr[n]; }
    const_reference operator[](size_type n) const { return m_Arr[n]; }
    reference front() { return m_Arr[0]; }
    const_reference front() const { return m_Arr[0]; }
    reference back() { return m_Arr[m_Size - 1]; }
    const_reference back() const { return m_Arr[m_Size - 1]; }
    T* data() { return m_Arr; }
    const T* data() const { return m_Arr; }
    iterator begin() { return iterator(m_Arr); }
    const_iterator begin() const { return iterator(m_Arr); }
    iterator end() { return iterator(m_Arr + m_Size); }
    const_iterator end() const { return iterator(m_Arr + m_Size); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return reverse_iterator(begin()); }
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
                pointer new_arr = m_Allocator.allocate(new_cap);
                size_type size = m_Size;
                for (size_type i = 0; i < m_Size; ++i)
                {
                    m_Allocator.construct(new_arr + i, m_Arr[i]);
                }
                clear();
                if (m_Arr)
                {
                    m_Allocator.deallocate(m_Arr, m_Capacity);
                }
                m_Arr = new_arr;
                m_Capacity = new_cap;
                m_Size = size;
            }
        }
    }
    size_type capacity(void) const { return m_Capacity; }
    void clear(void)
    {
        for (size_type i = 0; i < m_Size; ++i)
        {
            m_Allocator.destroy(m_Arr + i);
        }
        m_Size = 0;
    }
    iterator insert(iterator pos, const T &value)
    {
        difference_type pos_i = &*pos - m_Arr;
        insert(pos, 1, value);
        return iterator(m_Arr + pos_i);
    }
    void insert(iterator pos, size_type count, const T &value)
    {
        if (count != 0)
        {
            difference_type pos_i = &*pos - m_Arr;
            if (m_Capacity < m_Size + count)
            {
                size_type new_capacity = ((m_Capacity > 0) ? (m_Capacity * 2) : 1);
                while (new_capacity < m_Size + count)
                {
                    new_capacity *= 2;
                }
                pointer new_arr = m_Allocator.allocate(new_capacity);
                for (size_type i = 0; i < static_cast<size_type>(pos_i); ++i)
                {
                    m_Allocator.construct(new_arr + i, m_Arr[i]);
                }
                for (size_type i = 0; i < count; ++i)
                {
                    m_Allocator.construct(new_arr + pos_i + i, value);
                }
                for (size_type i = 0; i < m_Size - static_cast<size_type>(pos_i); ++i)
                {
                    m_Allocator.construct(new_arr + (m_Size - i) + count, m_Arr[m_Size - (i + 1)]);
                }
                size_type size = m_Size + count;
                clear();
                if (m_Arr)
                {
                    m_Allocator.deallocate(m_Arr, m_Capacity);
                }
                m_Size = size;
                m_Capacity = new_capacity;
                m_Arr = new_arr;
            }
            else
            {
                for (size_type i = 0; i < m_Size - static_cast<size_type>(pos_i); ++i)
                {
                    m_Allocator.construct(m_Arr + (m_Size - i) + count, m_Arr[m_Size - (i + 1)]);
                }
                for (size_type i = 0; i < count; ++i)
                {
                    m_Allocator.destroy(m_Arr + pos_i + i);
                    m_Allocator.construct(m_Arr + pos_i + i, value);
                }
                m_Size += count;
            }
        }
    }
    template <class InputIt>
    void insert(iterator pos, InputIt first, InputIt last)
    {
        difference_type count = distance(first, last);
        if (count != 0)
        {
            difference_type pos_i = &*pos - m_Arr;
            if (m_Capacity < m_Size + static_cast<size_type>(count))
            {
                size_type new_capacity = ((m_Capacity > 0) ? (m_Capacity * 2) : 1);
                while (new_capacity < m_Size + count)
                {
                    new_capacity *= 2;
                }
                pointer new_arr = m_Allocator.allocate(new_capacity);
                for (size_type i = 0; i < static_cast<size_type>(pos_i); ++i)
                {
                    m_Allocator.construct(new_arr + i, m_Arr[i]);
                }
                for (size_type i = 0; i < static_cast<size_type>(count); ++i, ++first)
                {
                    m_Allocator.construct(new_arr + pos_i + i, *first);
                }
                for (size_type i = 0; i < m_Size - static_cast<size_type>(pos_i); ++i)
                {
                    m_Allocator.construct(new_arr + (m_Size - i) + static_cast<size_type>(count), m_Arr[m_Size - (i + 1)]);
                }
                size_type size = m_Size + static_cast<size_type>(count);
                clear();
                if (m_Arr)
                {
                    m_Allocator.deallocate(m_Arr, m_Capacity);
                }
                m_Size = size;
                m_Capacity = new_capacity;
                m_Arr = new_arr;
            }
            else
            {
                for (size_type i = 0; i < m_Size - static_cast<size_type>(pos_i); ++i)
                {
                    m_Allocator.construct(m_Arr + (m_Size - i) + static_cast<size_type>(count), m_Arr[m_Size - (i + 1)]);
                }
                for (size_type i = 0; i < static_cast<size_type>(count); ++i, ++first)
                {
                    m_Allocator.destroy(m_Arr + pos_i + i);
                    m_Allocator.construct(m_Arr + pos_i + i, *first);
                }
                m_Size += static_cast<size_type>(count);
            }
        }
    }
    iterator erase(iterator pos)
    {
        return erase(pos, pos + 1);
    }
    iterator erase(iterator first, iterator last)
    {
        difference_type count = distance(first, last);
        difference_type pos_i = first.base() - m_Arr;
        for (size_t i = 0; i < static_cast<size_type>(count); ++i)
        {
            m_Allocator.destroy(m_Arr + pos_i + i);
        }
        for (size_type i = 0; i < m_Size - static_cast<size_type>(pos_i + count); ++i)
        {
            m_Allocator.construct(m_Arr + pos_i + i, m_Arr[static_cast<size_type>(pos_i + count) + i]);
        }
        m_Size -= static_cast<size_type>(count);
    }
    void push_back(const T& value)
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
                pop_back();
            }
        }
        else
        {
            insert(end(), count - m_Size, value);
        }
    }
    void swap(vector &other)
    {
        if (this != &other)
        {
            pointer ptr_copy = m_Arr;
            size_type size_copy = m_Size;
            size_type capacity_copy = m_Capacity;
            allocator_type allocator_copy = m_Allocator;

            m_Arr = other.m_Arr;
            m_Size = other.m_Size;
            m_Capacity = other.m_Capacity;
            m_Allocator = other.m_Allocator;

            other.m_Arr = ptr_copy;
            other.m_Size = size_copy;
            other.m_Capacity = capacity_copy;
            other.m_Allocator = allocator_copy;
        }
    }

private:
    void range_check(size_type pos) const
    {
        if (pos >= m_Size)
        {
            throw std::out_of_range("vector::range_check: pos (which is " +
                                    to_string(pos) + ") >= this->size() (which is " + to_string(m_Size) + ")");
        }
    }

    pointer m_Arr;
    size_type m_Size;
    size_type m_Capacity;
    allocator_type m_Allocator;
};

template < class T, class Alloc >
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }
    return equal(lhs.begin(), lhs.end(), rhs.begin());
}

template < class T, class Alloc >
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return !(lhs == rhs);
}

template < class T, class Alloc >
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template < class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return !(rhs < lhs);
}

template < class T, class Alloc >
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return rhs < lhs;
}

template < class T, class Alloc >
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return !(lhs < rhs);
}

template < class T, class Alloc >
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
    lhs.swap(rhs);
}

}

#endif // VECTOR_HPP
