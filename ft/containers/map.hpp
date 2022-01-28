/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:38:47 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/28 10:53:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <cstddef>
#include <stdexcept>

#include "../utils/functional.hpp"
#include "../utils/utility.hpp"
#include "../strings/string.hpp"
#include "../algorithms/algorithm.hpp"

#include "bst.hpp"

namespace ft
{

template<
    class Key,
    class T,
    class Compare = less<Key>,
    class Allocator = std::allocator<pair<const Key, T> >
> class map
{
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename bst<value_type, key_compare>::iterator iterator;
    typedef typename bst<value_type, key_compare>::const_iterator const_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;

    class value_compare : binary_function<value_type, value_type, bool>
    {
    protected:
        Compare comp;
        value_compare(Compare c) : comp(c) { }
    public:
        bool operator()(const value_type& x, const value_type& y) const
        {
            return comp(x.first, y.first);
        }
    };

    explicit map( const Compare& comp = Compare(),
        const Allocator& alloc = Allocator() )  : m_Comp(comp)
                                                , m_Allocator(alloc)
                                                , m_Bst(comp, alloc)
    {}
    template< class InputIt >
    map( InputIt first, InputIt last,
         const Compare& comp = Compare(),
         const Allocator& alloc = Allocator() ) : m_Comp(comp)
                                                , m_Allocator(alloc)
                                                , m_Bst(comp, alloc)
    {
        insert(first, last);
    }
    map( const map& other ) : m_Comp(other.m_Comp)
                            , m_Allocator(other.m_Allocator)
                            , m_Bst(other.m_Comp, other.m_Allocator)
    {
        insert(other.begin(), other.end());
    }
    ~map()
    {
        clear();
    }
    map& operator=(const map& other)
    {
        if (this != &other)
        {
            m_Allocator = other.m_Allocator;
            m_Comp = other.m_Comp;
            clear();
            insert(other.begin(), other.end());
        }
        return *this;
    }
    allocator_type get_allocator() const { return m_Allocator; }
    T& at( const Key& key )
    {
        iterator tmp = find(key);
        if (tmp == end())
        {
            throw std::out_of_range("map::at: " + to_string(key) + " key not found");
        }
        return tmp->second;
    }
    const T& at( const Key& key ) const
    {
        return at(key);
    }
    T& operator[]( const Key& key )
    {
        iterator tmp = find(key);
        if (tmp == end())
        {
            return insert(make_pair(key, mapped_type())).first->second;
        }
        return tmp->second;
    }
    iterator begin(void) { return iterator(m_Bst.begin(), m_Bst.end()); }
    const_iterator begin(void) const { return const_iterator(m_Bst.begin(), m_Bst.end()); }
    iterator end(void) { return iterator(m_Bst.end(), m_Bst.end()); }
    const_iterator end(void) const { return const_iterator(m_Bst.end(), m_Bst.end()); }
    reverse_iterator rbegin(void) { return reverse_iterator(end());}
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend(void) { return reverse_iterator(begin()); }
    const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }
    bool empty(void) const { return m_Bst.size() == 0; }
    size_type size(void) const { return m_Bst.size(); }
    size_type max_size(void) const { return m_Allocator.max_size(); }
    void clear(void)
    {
        erase(begin(), end());
    }
    pair<iterator, bool> insert(const value_type& value)
    {
       return m_Bst.insert_pair(value);
    }
    iterator insert(iterator hint, const value_type& value)
    {
        (void)hint;
        return insert(value).first;
    }
    template< class InputIt >
    void insert( InputIt first, InputIt last )
    {
        for (; first != last; ++first)
        {
            insert(*first);
        }
    }
    void erase( iterator pos )
    {
        erase(pos->first);
    }
    void erase( iterator first, iterator last )
    {
        for (; first != last; ++first)
        {
            erase(first->first);
        }
    }
    size_type erase( const Key& key )
    {
        if (find(key) == end())
        {
            return (0);
        }
        m_Bst.remove_by_key(make_pair(key, mapped_type()));
        return (1);
    }
    void swap( map& other )
    {
        m_Bst.swap(other);

        Compare tmp_comp = m_Comp;
        Allocator tmp_allocator = m_Allocator;
        
        m_Comp = other.m_Comp;
        m_Allocator = other.m_Allocator;

        other.m_Comp = tmp_comp;
        other.m_Allocator = tmp_allocator;
    }
    size_type count( const Key& key ) const
    {
        if (find(key) == end())
        {
            return (0);
        }
        return (1);
    }
    iterator find( const Key& key )
    {
        return iterator(m_Bst.search_by_key(make_pair(key, mapped_type())), m_Bst.end());
    }
    const_iterator find( const Key& key ) const
    {
        return const_iterator(m_Bst.search_by_key(make_pair(key, mapped_type())), end());
    }
    pair<iterator,iterator> equal_range( const Key& key )
    {
        return make_pair(lower_bound(key), upper_bound(key));
    }
    pair<const_iterator,const_iterator> equal_range( const Key& key ) const
    {
        return make_pair(lower_bound(key), upper_bound(key));
    }
    iterator lower_bound( const Key& key )
    {
        iterator begin = begin();
        iterator end = end();
        for ( ; begin != end; ++begin)
        {
            if (!m_Comp(begin->first, key))
            {
                break;
            }
        }
        return begin;
    }
    const_iterator lower_bound( const Key& key ) const
    {
        return const_iterator(lower_bound(key));
    }
    iterator upper_bound( const Key& key )
    {
        iterator begin = begin();
        iterator end = end();
        for ( ; begin != end; ++begin)
        {
            if (!m_Comp(key, begin->first))
            {
                break;
            }
        }
        return begin;
    }
    const_iterator upper_bound( const Key& key ) const
    {
        return const_iterator(upper_bound(key));
    }
    key_compare key_comp() const
    {
        return m_Comp;
    }
    value_compare value_comp() const
    {
        return value_compare(m_Comp);
    }

private:
    key_compare m_Comp;
    allocator_type m_Allocator;
    bst<value_type, key_compare> m_Bst;
};

template< class Key, class T, class Compare, class Alloc >
bool operator==( const map<Key,T,Compare,Alloc>& lhs,
                 const map<Key,T,Compare,Alloc>& rhs )
{
    return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
                 const map<Key,T,Compare,Alloc>& rhs )
{
    return !(lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs )
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
                 const map<Key,T,Compare,Alloc>& rhs )
{
    return !(rhs < lhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs )
{
    return rhs < lhs;
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
                 const map<Key,T,Compare,Alloc>& rhs )
{
    return !(lhs < rhs);
}

template< class Key, class T, class Compare, class Alloc >
void swap( map<Key,T,Compare,Alloc>& lhs,
           map<Key,T,Compare,Alloc>& rhs )
{
    lhs.swap(rhs);
}

}

#endif // MAP_HPP
