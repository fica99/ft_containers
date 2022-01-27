/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:43:39 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/27 15:38:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
#define BST_HPP

#include <cstddef>
#include <memory>

#include "../iterators/iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils/utility.hpp"

namespace ft
{

template <typename T>
struct bst_node
{
public:
    typedef T value_type;
    bst_node(bst_node* parent = NULL, bst_node* left = NULL,
            bst_node* right = NULL) : m_Value()
                                    , m_Parent(parent)
                                    , m_Left(left)
                                    , m_Right(right)
    { }
    bst_node(const bst_node& other) : m_Value(other.m_Value)
                                    , m_Parent(other.m_Parent)
                                    , m_Left(other.m_Left)
                                    , m_Right(other.m_Right)
    { }
    virtual ~bst_node() {}
    bst_node& operator=(const bst_node& other)
    {
        if (this != &other)
        {
            m_Value = other.m_Value;
            m_Parent = other.m_Parent;
            m_Left = other.m_Left;
            m_Right = other.m_Right;
        }
        return *this;
    }
    bool operator==(const bst_node& other)
    {
        return m_Value == other.m_Value;
    }
    const value_type& get_value(void) const { return m_Value; }
    void set_value(const value_type& value) { m_Value = value; }
    const bst_node* get_parent(void) const { return m_Parent; }
    const bst_node* get_left(void) const { return m_Left; }
    const bst_node* get_right(void) const { return m_Right; }
private: 
    value_type m_Value;
    bst_node* m_Parent;
    bst_node* m_Left;
    bst_node* m_Right;
};

template <typename T, class Compare>
class bst_iterator : iterator<bidirectional_iterator_tag, bst_node<T> >
{
public:
    typedef typename iterator<bidirectional_iterator_tag, bst_node<T> >::iterator_category iterator_category;
    typedef typename iterator<random_access_iterator_tag, bst_node<T> >::value_type value_type;
    typedef typename iterator<bidirectional_iterator_tag, bst_node<T> >::difference_type difference_type;
    typedef typename iterator<bidirectional_iterator_tag, bst_node<T> >::pointer pointer;
    typedef typename iterator<bidirectional_iterator_tag, bst_node<T> >::reference reference;
    explicit bst_iterator(pointer node = NULL, pointer end = NULL,
        const Compare& comp = Compare()) : m_Node(node)
                                         , m_End(end)
                                         , m_Comp(comp)
    { }
    bst_iterator(const bst_iterator& other) : m_Node(other.m_Node)
                                            , m_End(other.m_End)
                                            , m_Comp(other.m_Comp)
    { }
    virtual ~bst_iterator() {}
    bst_iterator& operator=(const bst_iterator& other)
    {
        if (this != &other)
        {
            m_Node = other.m_Node;
            m_End = other.m_End;
            m_Comp = other.m_Comp;
        }
        return (*this);
    }
    bool operator==(const bst_iterator& other)
    {
        return m_Node == other.m_Node;
    }
    bool operator!=(const bst_iterator& other)
    {
        return m_Node != other.m_Node;
    }
    reference operator*() const
    {
        return m_Node->value;
    }
    pointer operator->() const
    {
        return &m_Node->value;
    }
    bst_iterator& operator++(void)
    {
        pointer current = m_Node;
        if (current->get_right() == m_End)
        {
            current = m_Node->get_parent();
            while (current != m_End && m_Comp(current->get_value(), m_Node->get_value())) //write comp
            {
                current = current->get_parent();
            }
            m_Node = current;
        }
        else if (current == m_End)
        {
            m_Node = current->get_left();
        }
        else
        {
            current = m_Node->get_left();
            if (current == m_End->get_parent() && current->get_left() == m_End)
            ;
            else
            {
                while (current->get_right() != m_End)
                {
                    current = current->get_right();
                }
            }
            m_Node = current;
        }
        return *this;
    }
    bst_iterator operator++(int)
    {
        bst_iterator tmp(*this);
        operator++();
        return (tmp);
    }
    bst_iterator &operator--(void)
    {
        pointer current = m_Node;
        if (current->get_left() == m_End)
        {
            current = m_Node->get_parent();
            while (current != m_End && !m_Comp(current->get_value(), m_Node->get_value())) //write comp
            {
                current = current->get_parent();
            }
            m_Node = current;
        }
        else if (current == m_End)
        {
            m_Node = current->get_right();
        }
        else
        {
            current = m_Node->get_right();
            if (current == m_End->get_parent() && current->get_right() == m_End)
            ;
            else
            {
                while (current->get_left() != m_End)
                {
                    current = current->get_left();
                }
            }
            m_Node = current;
        }
        return *this;
    }
    bst_iterator operator--(int)
    {
        bst_iterator tmp(*this);
        operator--();
        return (tmp);
    }
private:
    pointer m_Node;
    pointer m_End;
    Compare m_Comp;
};

template <
    typename T,
    typename Compare,
    typename Allocator
> class bst
{
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef bst_node<T> node_type;
    typedef Compare key_compare;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef bst_iterator<value_type, Compare> iterator;
    typedef bst_iterator<const value_type, Compare> const_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;
public:
    bst(const Compare& comp = Compare(),
        const allocator_type& allocator = allocator_type()) : m_End(NULL)
                                                            , m_Size(0)
                                                            , m_Comp(comp)
                                                            , m_Allocator(allocator)
    {
        m_End = m_Allocator.allocate(1);
        m_Allocator.construct(m_End, Node(m_End, m_End, m_End));
    }
    virtual ~bst()
    {
        m_Allocator.destroy(m_End);
        m_Allocator.deallocate(m_End, 1);	
    }
    iterator searchByKey(const value_type& value)
    {
        node_type* node = m_End->get_parent();
        while (node != m_End)
        {
            if (m_Comp(value, node->get_value()))
            {
                node = node->get_left();
            }
            else if (m_Comp(node->get_value(), value))
            {
                node = node->get_right();
            }
            else
            {
                break;
            }
        }
        return iterator(node, m_End);
    }
    // pair<Node*, bool> insertPair(value_type to_insert)
	// 		{
	// 			Node * new_node = _node_alloc.allocate(1);
	// 			Node * prev_node = _last_node;
	// 			Node * start_node = _last_node->parent;

	// 			// side == false = left; side == true = right;
	// 			bool side = true;

	// 			while (start_node != _last_node)
	// 			{
	// 				int curkey = start_node->value.first;
	// 				if (curkey == to_insert.first)
	// 					return (ft::make_pair(iterator(start_node, _last_node), false));
	// 				prev_node = start_node;
	// 				if (to_insert.first > curkey)
	// 				{
	// 					side = true;
	// 					start_node = start_node->right;
	// 				}
	// 				else
	// 				{
	// 					side = false;
	// 					start_node = start_node->left;
	// 				}
	// 			}
	// 			_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));
				
	// 			if (prev_node == _last_node)
	// 				_last_node->parent = new_node;
	// 			else if (side == true)
	// 				prev_node->right = new_node;
	// 			else
	// 				prev_node->left = new_node;
				
	// 			_last_node->left = _BST_get_lower_node(_last_node->parent);
	// 			_last_node->right = _BST_get_higher_node(_last_node->parent);
	// 			_last_node->value.first += 1;
	// 			return (ft::make_pair(iterator(new_node, _last_node), true));
	// 		}
private:
    node_type* m_End;
    size_type m_Size;
    Compare m_Comp;
    Allocator m_Allocator;
};


}

#endif // BST_HPP
