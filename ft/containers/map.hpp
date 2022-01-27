/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:38:47 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/27 15:41:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <cstddef>
#include <stdexcept>

#include "../utils/functional.hpp"
#include "../utils/utility.hpp"
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
    typedef typename bst<value_type, key_compare, allocator_type>::iterator iterator;
    typedef typename bst<value_type, key_compare, allocator_type>::const_iterator const_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;

    class value_compare : binary_function<value_type, value_type, bool>
    {
    protected:
        Compare comp;
    public:
        value_compare(Compare c) : comp(c) { }
        bool operator()(const value_type& x, const value_type& y) const
        {
            return comp(x.first, y.first);
        }
    };

    explicit map( const Compare& comp = Compare(),
        const Allocator& alloc = Allocator() )  : m_Comp(comp)
                                                , m_Allocator(alloc)
                                                , m_Bst()
    {}
    template< class InputIt >
    map( InputIt first, InputIt last,
         const Compare& comp = Compare(),
         const Allocator& alloc = Allocator() ) : m_Comp(comp)
                                                , m_Allocator(alloc)
                                                , m_Bst()
    {
        insert(first, last);
    }
    map( const map& other ) : m_Comp(other.m_Comp)
                            , m_Allocator(other.m_Allocator)
                            , m_Bst()
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
            throw std::out_of_range("map::at");
        }
        return tmp->second;
    }
    const T& at( const Key& key ) const
    {
        at(key);
    }
    T& operator[]( const Key& key )
    {
        iterator tmp = find(key);
        if (tmp == end())
        {
            insert(make_pair(key, mapped_type()));
        }
        return tmp->second;
    }
    iterator begin(void) { return iterator(m_Bst.m_Roots->left, m_Bst.m_Roots); }
    const_iterator begin(void) const { return const_iterator(m_Bst.m_Roots->left, m_Bst.m_Roots); }
    iterator end(void) { return iterator(m_Bst.m_Roots, m_Bst.m_Roots); }
    const_iterator end(void) const { return const_iterator(m_Bst.m_Roots, m_Bst.m_Roots); }
    reverse_iterator rbegin(void) { return reverse_iterator(end());}
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend(void) { return reverse_iterator(begin()); }
    const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }
    bool empty(void) const { return m_Bst.m_Size == 0; }
    size_t size(void) const { return m_Bst.m_Size; }
    size_type max_size(void) const { return m_Allocator.max_size(); }
    void clear(void)
    {
        //erase(begin(), end());
    }
    pair<iterator, bool> insert(const value_type& value)
    {
       // pair<Node> m_Bst.insertPair(value);
    }
    iterator insert(iterator hint, const value_type& value)
    {
        
    }
    template< class InputIt >
    void insert( InputIt first, InputIt last )
    {
        
    }
    iterator find(const key_type& k)
    {
        return iterator(m_Bst.searchByKey(make_pair(k, mapped_type())));
    }
    const_iterator find(const key_type& k) const
    {
        return const_iterator(m_Bst.searchByKey(make_pair(k, mapped_type())));
    }
private:
    Compare m_Comp;
    Allocator m_Allocator;
    bst<value_type, Compare, Allocator> m_Bst;
};

}

#endif // MAP_HPP
