/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:10:21 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/29 09:08:57 by aashara-         ###   ########.fr       */
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
                                                                        , m_Size(0)
                                                                        , m_Capacity(0)
                                                                        , m_Allocator(allocator)
    {
        create_data(count, value);
    }
    template <class InputIt>
    vector(typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, InputIt>::type first, InputIt last,
                    const allocator_type& allocator = allocator_type()) : m_Arr(NULL)
                                                                        , m_Size(0)
                                                                        , m_Capacity(0)
                                                                        , m_Allocator(allocator)
    {
        create_data(do_distance(first, last), first, last);
    }
    vector(const vector& other) : m_Arr(NULL)
                                , m_Size(0)
                                , m_Capacity(0)
                                , m_Allocator(other.m_Allocator)
    {
        *this = other;
    }
    ~vector()
    {
        destroy_data();
    }
    vector& operator=(const vector& other)
    {
        if (this != &other)
        {
            const_iterator first = other.begin();
            const_iterator last = other.end();
            typename iterator_traits<const_iterator>::difference_type len = distance(first, last);
            if (static_cast<size_type>(len) > m_Capacity)
            {
                create_data(len, first, last);
            }
            else
            {
                create_data(m_Capacity, first, last);
            }
        }
        return *this;
    }
    void assign(size_type count, const value_type &value)
    {
        if (count > m_Capacity)
        {
            create_data(count, value);
        }
        else
        {
            clear();
            for (size_type i = 0; i < count; ++i, ++m_Size)
            {
                m_Allocator.construct(m_Arr + i, value);
            }
        }
    }
    template <class InputIt>
    void assign(typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, InputIt>::type first, InputIt last)
    {
        difference_type len = do_distance(first, last);
        if (static_cast<size_type>(len) > m_Capacity)
        {
            create_data(len, first, last);
        }
        else
        {
            clear();
            for (; first != last; ++first, ++m_Size)
            {
                m_Allocator.construct(m_Arr + m_Size, *first);
            }
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
                throw std::length_error("vector::reserve(size_type new_cap) 'new_cap' exceeds maximum supported size");
            }
            else
            {
                create_data(new_cap, begin(), end());
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
        typename iterator_traits<iterator>::difference_type pos_i = pos - begin();
        insert(pos, 1, value);
        return iterator(begin() + pos_i);
    }
    void insert(iterator pos, size_type count, const T& value)
    {
        typename iterator_traits<iterator>::difference_type idx = pos - begin();
        typename iterator_traits<iterator>::difference_type old_end_idx = end() - begin();
        iterator old_end = end();
        iterator ends;
        
        resize(m_Size + count);
        ends = end();
        pos = begin() + idx;
        old_end = begin() + old_end_idx;
        for (; old_end != pos; )
        {
            --ends;
            --old_end;
            *ends = *old_end;
        }
        for (size_type i = 0; i < count; ++i, ++pos)
        {
            *pos = value;
        }
    }
    template <class InputIt>
    void insert(iterator pos, InputIt first, typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, InputIt>::type last)
    {
        typename iterator_traits<iterator>::difference_type idx = pos - begin();
        typename iterator_traits<iterator>::difference_type old_end_idx = end() - begin();
        iterator old_end = end();
        iterator ends;
        
        resize(m_Size + do_distance(first, last));
        ends = end();
        pos = begin() + idx;
        old_end = begin() + old_end_idx;
        for (; old_end != pos; )
        {
            --ends;
            --old_end;
            *ends = *old_end;
        }
        for (; first != last; ++first)
        {
            *pos = *first;
            ++pos;
        }
    }
    iterator erase(iterator pos)
    {
        return erase(pos, pos + 1);
    }
    iterator erase(iterator first, iterator last)
    {
        typename iterator_traits<iterator>::difference_type count = distance(first, last);
        iterator tmp = first;
        for (; first != end(); ++first, ++last)
        {
            *first = *last;
        }
        for (size_type i = 0; i < static_cast<size_type>(count); ++i)
        {
            m_Allocator.destroy(m_Arr + (--m_Size));
        }
        return tmp;
    }
    void push_back(const T& value)
    {
        if (m_Size == m_Capacity)
        {
            resize(m_Size + 1, value);
        }
        else
        {
            m_Allocator.construct(m_Arr + m_Size, value);
            ++m_Size;
        }
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
            for (; count < m_Size;)
            {
                --m_Size;
                m_Allocator.destroy(m_Arr + m_Size);
            }
        }
        else
        {
            if (count <= m_Capacity * 2)
            {
                reserve(m_Capacity * 2);
            }
            else
            {
                reserve(count);
            }
            for (; m_Size < count; ++m_Size)
            {
                m_Allocator.construct(m_Arr + m_Size, value);
            }
        }
    }
    void swap(vector &other)
    {
        vector<T, Allocator> tmp;
        tmp.copy_content(other);
        other.copy_content(*this);
        copy_content(tmp);
    }

private:
    template <class InputIt>
    difference_type do_distance(InputIt first, InputIt last)
    {
        difference_type len = 0;
        for (InputIt tmp = first; tmp != last; ++tmp)
        {
            ++len;
        }
        return len;
    }
    void create_data(size_type size, const value_type &val)
    {
        destroy_data();
        m_Arr = m_Allocator.allocate(size);
        for (size_type i = 0; i < size; ++i)
        {
            m_Allocator.construct(m_Arr + i, val);
        }
        m_Size = size;
        m_Capacity = size;
    }
    template <class InputIt>
    void create_data(typename iterator_traits<InputIt>::difference_type capacity, InputIt first, InputIt last)
    {
        vector<T, Allocator> res;
        size_t count = 0;
        for (InputIt tmp = first; tmp != last; ++tmp)
        {
            ++count;
        }
        res.m_Allocator = m_Allocator;
        res.m_Size = count;
        res.m_Capacity = capacity;
        res.m_Arr = res.m_Allocator.allocate(capacity);
        for (size_type i = 0; first != last; ++first, ++i)
        {
            res.m_Allocator.construct(res.m_Arr + i, *first);
        }
        destroy_data();
        copy_content(res);
    }
    void copy_content(vector<T, Allocator>& other) {
        m_Arr = other.m_Arr;
        m_Allocator = other.m_Allocator;
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        other.m_Arr = NULL;
        other.m_Size = 0;
        other.m_Capacity = 0;
    }
    void destroy_data(void)
    {
        if (!m_Arr)
        {
            return;
        }
        clear();
        m_Allocator.deallocate(m_Arr, m_Capacity);
        m_Arr = NULL;
        m_Size = 0;
        m_Capacity = 0;
    }
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
