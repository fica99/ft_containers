/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:32:59 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/25 17:46:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTIGUOUS_ITERATOR_HPP
#define CONTIGUOUS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

    template <typename T>
    class contiguous_iterator : public iterator<random_access_iterator_tag, T>
    {
    public:
        // Member types
        typedef typename iterator<random_access_iterator_tag, T>::iterator_category iterator_category;
        typedef typename iterator<random_access_iterator_tag, T>::value_type value_type;
        typedef typename iterator<random_access_iterator_tag, T>::difference_type difference_type;
        typedef T *pointer;
        typedef T &reference;

        // Member functions
        contiguous_iterator(void) : m_Ptr(NULL) {}
        explicit contiguous_iterator(pointer ptr) : m_Ptr(ptr) {}
        contiguous_iterator(const contiguous_iterator &other) : m_Ptr(other.m_Ptr) {}
        contiguous_iterator &operator=(const contiguous_iterator &other)
        {
            if (&other != this)
            {
                m_Ptr = other.m_Ptr;
            }
            return *this;
        }
        pointer base(void) const { return m_Ptr; }
        reference operator*(void) const { return *m_Ptr; }
        pointer operator->(void) const { return &operator*(); }
        reference operator[](difference_type diff) { return m_Ptr[diff]; }
        contiguous_iterator &operator++(void)
        {
            ++m_Ptr;
            return *this;
        }
        contiguous_iterator &operator--(void)
        {
            --m_Ptr;
            return *this;
        }
        contiguous_iterator operator++(int)
        {
            contiguous_iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        contiguous_iterator operator--(int)
        {
            contiguous_iterator tmp = *this;
            operator--();
            return contiguous_iterator(tmp);
        }
        contiguous_iterator operator+(difference_type diff) const { return (m_Ptr + diff); }
        contiguous_iterator operator-(difference_type diff) const { return (m_Ptr - diff); }
        contiguous_iterator &operator+=(difference_type diff)
        {
            m_Ptr = m_Ptr + diff;
            return (*this);
        }
        contiguous_iterator &operator-=(difference_type diff)
        {
            m_Ptr = m_Ptr - diff;
            return (*this);
        }

    private:
        pointer m_Ptr;
    };

    // Non-member functions
    template <typename T1, typename T2>
    bool operator==(const contiguous_iterator<T1> &lhs, const contiguous_iterator<T2> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename T1, typename T2>
    bool operator!=(const contiguous_iterator<T1> &lhs, const contiguous_iterator<T2> &rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename T1, typename T2>
    bool operator<(const contiguous_iterator<T1> &lhs, const contiguous_iterator<T2> &rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename T1, typename T2>
    bool operator<=(const contiguous_iterator<T1> &lhs, const contiguous_iterator<T2> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename T1, typename T2>
    bool operator>(const contiguous_iterator<T1> &lhs, const contiguous_iterator<T2> &rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename T1, typename T2>
    bool operator>=(const contiguous_iterator<T1> &lhs, const contiguous_iterator<T2> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename T>
    contiguous_iterator<T> operator+(typename contiguous_iterator<T>::difference_type n, const contiguous_iterator<T> &it)
    {
        return contiguous_iterator<T>(it.base() + n);
    }

    template <typename T>
    typename contiguous_iterator<T>::difference_type operator-(const contiguous_iterator<T> lhs, const contiguous_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

}
#endif // CONTIGUOUS_ITERATOR_HPP
