/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:10:21 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/25 17:45:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>

#include "../iterators/iterator.hpp"
#include "../strings/string.hpp"
#include "../algorithms/algorithm.hpp"

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
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef contiguous_iterator<value_type> iterator;
        typedef contiguous_iterator<const value_type> const_iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;

        // Member functions
        explicit vector(const allocator_type &allocator = allocator_type()) : m_Arr(NULL),
                                                                              m_Size(0),
                                                                              m_Capacity(0),
                                                                              m_Allocator(allocator)
        {
        }
        explicit vector(size_type count, const_reference value = value_type(), const allocator_type &allocator = allocator_type()) : m_Arr(NULL),
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
        template <class InputIt>
        vector(InputIt first, InputIt last, const allocator_type &allocator = allocator_type()) : m_Arr(NULL),
                                                                                                  m_Size(0),
                                                                                                  m_Capacity(0),
                                                                                                  m_Allocator(allocator)
        {
            assign(first, last);
        }
        vector(const vector &other) : m_Arr(NULL),
                                      m_Size(0),
                                      m_Capacity(0),
                                      m_Allocator(other.m_Allocator)
        {
            insert(begin(), other.begin(), other.end());
        }
        ~vector()
        {
            clear();
            m_Allocator.deallocate(m_Arr, m_Capacity);
        }
        vector &operator=(const vector &other)
        {
            if (&other != this)
            {
                clear();
                insert(end(), other.begin(), other.end());
            }
            return *this;
        }
        void assign(size_type count, const value_type &value)
        {
            clear();
            if (m_Capacity < count)
            {
                if (m_Arr)
                {
                    m_Allocator.deallocate(m_Arr, m_Capacity);
                }
                m_Arr = m_Allocator.allocate(count);
                m_Size = count;
                m_Capacity = count;
            }
            for (size_type i = 0; i < count; ++i)
            {
                m_Allocator.construct(m_Arr + i, value);
            }
        }
        template <class InputIt>
        void assign(InputIt first, InputIt last)
        {
            clear();
            difference_type diff = distance(first, last);
            if (m_Capacity < diff)
            {
                if (m_Arr)
                {
                    m_Allocator.deallocate(m_Arr, m_Capacity);
                }
                m_Arr = m_Allocator.allocate(diff);
                m_Size = diff;
                m_Capacity = diff;
            }
            for (size_t i = 0; first != last; ++first, ++i)
            {
                m_Allocator.construct(m_Arr + i, *first);
            }
        }
        allocator_type get_allocator() const { return m_Allocator; }

        // Element access
        reference at(size_type pos)
        {
            range_check(pos);
            return (*this)[pos];
        }
        const_reference at(size_type pos) const
        {
            range_check(pos);
            return (*this)[pos];
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
        iterator begin() { return iterator(m_Arr); }
        const_iterator begin() const { return iterator(m_Arr); }
        iterator end() { return iterator(m_Arr + m_Size); }
        const_iterator end() const { return iterator(m_Arr + m_Size); }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return reverse_iterator(begin()); }

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

        // Modifiers
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
            difference_type pos_i = pos.base() - m_Arr;
            insert(pos, 1, value);
            return iterator(m_Arr + pos_i);
        }
        void insert(iterator pos, size_type count, const T &value)
        {
            if (count != 0)
            {
                difference_type pos_i = pos.base() - m_Arr;
                if (m_Capacity < m_Size + count)
                {
                    size_type new_capacity = ((m_Capacity > 0) ? (m_Capacity * 2) : 1);
                    while (new_capacity < m_Size + count)
                    {
                        new_capacity *= 2;
                    }
                    pointer new_arr = m_Allocator.allocate(new_capacity);
                    for (size_type i = 0; i < pos_i; ++i)
                    {
                        m_Allocator.construct(new_arr + i, m_Arr[i]);
                    }
                    for (size_type i = 0; i < count; ++i)
                    {
                        m_Allocator.construct(new_arr + pos_i + i, value);
                    }
                    for (size_type i = 0; i < m_Size - pos_i; ++i)
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
                    for (size_type i = 0; i < m_Size - pos_i; ++i)
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
                difference_type pos_i = pos.base() - m_Arr;
                if (m_Capacity < m_Size + count)
                {
                    size_type new_capacity = ((m_Capacity > 0) ? (m_Capacity * 2) : 1);
                    while (new_capacity < m_Size + count)
                    {
                        new_capacity *= 2;
                    }
                    pointer new_arr = m_Allocator.allocate(new_capacity);
                    for (size_type i = 0; i < pos_i; ++i)
                    {
                        m_Allocator.construct(new_arr + i, m_Arr[i]);
                    }
                    for (size_type i = 0; i < count; ++i, ++first)
                    {
                        m_Allocator.construct(new_arr + pos_i + i, *first);
                    }
                    for (size_type i = 0; i < m_Size - pos_i; ++i)
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
                    for (size_type i = 0; i < m_Size - pos_i; ++i)
                    {
                        m_Allocator.construct(m_Arr + (m_Size - i) + count, m_Arr[m_Size - (i + 1)]);
                    }
                    for (size_type i = 0; i < count; ++i, ++first)
                    {
                        m_Allocator.destroy(m_Arr + pos_i + i);
                        m_Allocator.construct(m_Arr + pos_i + i, *first);
                    }
                    m_Size += count;
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
            for (size_t i = 0; i < count; ++i)
            {
                m_Allocator.destroy(m_Arr + pos_i + i);
            }
            for (size_type i = 0; i < m_Size - (pos_i + count); ++i)
            {
                m_Allocator.construct(m_Arr + pos_i + i, m_Arr[pos_i + count + i]);
            }
            m_Size -= count;
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
                    m_Allocator.destroy(m_Arr + m_Size);
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

    private:
        pointer m_Arr;
        size_type m_Size;
        size_type m_Capacity;
        allocator_type m_Allocator;
    };

    // Non-member functions
    template <class T, class Alloc>
    bool operator==(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        return equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
    bool operator!=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>=(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap(std::vector<T, Alloc> &lhs, std::vector<T, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }

}

#endif // VECTOR_HPP
