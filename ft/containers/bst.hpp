/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:43:39 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/28 16:19:01 by aashara-         ###   ########.fr       */
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
            bst_node* right = NULL) : value()
                                    , parent(parent)
                                    , left(left)
                                    , right(right)
    { }
    bst_node(const value_type& value, bst_node* parent = NULL, bst_node* left = NULL,
            bst_node* right = NULL) : value(value)
                                    , parent(parent)
                                    , left(left)
                                    , right(right)
    { }
    bst_node(const bst_node& other) : value(other.value)
                                    , parent(other.parent)
                                    , left(other.left)
                                    , right(other.right)
    { }
    virtual ~bst_node() {}
    bst_node& operator=(const bst_node& other)
    {
        if (this != &other)
        {
            value = other.value;
            parent = other.parent;
            left = other.left;
            right = other.right;
        }
        return *this;
    }
    bool operator==(const bst_node& other)
    {
        return value == other.value;
    }
    value_type value;
    bst_node* parent;
    bst_node* left;
    bst_node* right;
};

template <typename T, class Compare>
class bst_const_iterator;

template <typename T, class Compare>
class bst_iterator : iterator<bidirectional_iterator_tag, T>
{
public:
    friend class bst_const_iterator<T, Compare>;

    typedef typename T::value_type value_type;
    typedef typename iterator<bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
    typedef typename iterator<bidirectional_iterator_tag, value_type>::difference_type difference_type;
    typedef typename iterator<bidirectional_iterator_tag, value_type>::pointer pointer;
    typedef typename iterator<bidirectional_iterator_tag, value_type>::reference reference;
    bst_iterator(T* node = NULL, T* end = NULL,
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
        T* current = m_Node;
        if (current->right == m_End)
        {
            current = m_Node->parent;
            while (current != m_End && m_Comp(current->value.first, m_Node->value.first))
            {
                current = current->parent;
            }
        }
        else if (current == m_End)
        {
            current = current->left;
        }
        else
        {
            current = m_Node->right;
            while (current->left != m_End)
            {
                current = current->left;
            }
        }
        m_Node = current;
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
        T* current = m_Node;
        if (current->left == m_End)
        {
            current = m_Node->parent;
            while (current != m_End && !m_Comp(current->value.first, m_Node->value.first))
            {
                current = current->parent;
            }
        }
        else if (current == m_End)
        {
            current = current->right;
        }
        else
        {
            current = m_Node->left;
            while (current->right != m_End)
            {
                current = current->right;
            }
        }
        m_Node = current;
        return *this;
    }
    bst_iterator operator--(int)
    {
        bst_iterator tmp(*this);
        operator--();
        return (tmp);
    }
private:
    T* m_Node;
    T* m_End;
    Compare m_Comp;
};

template <typename T, class Compare>
class bst_const_iterator : iterator<bidirectional_iterator_tag, T>
{
public:
    typedef typename T::value_type value_type;
    typedef typename iterator<bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
    typedef typename iterator<bidirectional_iterator_tag, value_type>::difference_type difference_type;
    typedef typename iterator<bidirectional_iterator_tag, value_type>::pointer pointer;
    typedef typename iterator<bidirectional_iterator_tag, value_type>::reference reference;
    bst_const_iterator(T* node = NULL, T* end = NULL,
        const Compare& comp = Compare()) : m_Node(node)
                                         , m_End(end)
                                         , m_Comp(comp)
    { }
    bst_const_iterator(const bst_const_iterator& other) : m_Node(other.m_Node)
                                            , m_End(other.m_End)
                                            , m_Comp(other.m_Comp)
    { }
    bst_const_iterator(const bst_iterator<T, Compare>& other) : m_Node(other.m_Node)
                                            , m_End(other.m_End)
                                            , m_Comp(other.m_Comp)
    { }
    virtual ~bst_const_iterator() {}
    bst_const_iterator& operator=(const bst_const_iterator& other)
    {
        if (this != &other)
        {
            m_Node = other.m_Node;
            m_End = other.m_End;
            m_Comp = other.m_Comp;
        }
        return (*this);
    }
    bool operator==(const bst_const_iterator& other)
    {
        return m_Node == other.m_Node;
    }
    bool operator!=(const bst_const_iterator& other)
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
    bst_const_iterator& operator++(void)
    {
        T* current = m_Node;
        if (current->right == m_End)
        {
            current = m_Node->parent;
            while (current != m_End && m_Comp(current->value.first, m_Node->value.first))
            {
                current = current->parent;
            }
        }
        else if (current == m_End)
        {
            current = current->left;
        }
        else
        {
            current = m_Node->right;
            while (current->left != m_End)
            {
                current = current->left;
            }
        }
        m_Node = current;
        return *this;
    }
    bst_const_iterator operator++(int)
    {
        bst_const_iterator tmp(*this);
        operator++();
        return (tmp);
    }
    bst_const_iterator &operator--(void)
    {
        T* current = m_Node;
        if (current->left == m_End)
        {
            current = m_Node->parent;
            while (current != m_End && !m_Comp(current->value.first, m_Node->value.first))
            {
                current = current->parent;
            }
        }
        else if (current == m_End)
        {
            current = current->right;
        }
        else
        {
            current = m_Node->left;
            while (current->right != m_End)
            {
                current = current->right;
            }
        }
        m_Node = current;
        return *this;
    }
    bst_const_iterator operator--(int)
    {
        bst_const_iterator tmp(*this);
        operator--();
        return (tmp);
    }

private:
    T* m_Node;
    T* m_End;
    Compare m_Comp;
};

template <
    typename T,
    typename Compare,
    typename Node = bst_node<T>,
    typename Allocator = std::allocator<Node>
> class bst
{
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef Compare key_compare;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef bst_iterator<Node, Compare> iterator;
    typedef bst_const_iterator<Node, Compare> const_iterator;
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
    Node* search_by_key(const value_type& value)
    {
        Node* node = m_End->parent;
        while (node != m_End)
        {
            if (m_Comp(value.first, node->value.first))
            {
                node = node->left;
            }
            else if (m_Comp(node->value.first, value.first))
            {
                node = node->right;
            }
            else
            {
                break;
            }
        }
        return node;
    }
    pair<iterator, bool> insert_pair(value_type to_insert)
    {
        Node* new_node = m_Allocator.allocate(1);
        Node* prev_node = m_End;
        Node * start_node = m_End->parent;
        bool side = true;
        while (start_node != m_End)
        {
            prev_node = start_node;
            if (m_Comp(to_insert.first, start_node->value.first))
            {
                side = false;
                start_node = start_node->left;
            }
            else if (m_Comp(start_node->value.first, to_insert.first))
            {
                side = true;
                start_node = start_node->right;
            }
            else
            {
                return make_pair(iterator(start_node, m_End, m_Comp), false);
            }
        }
        m_Allocator.construct(new_node, Node(to_insert, prev_node, m_End, m_End));
        if (prev_node == m_End)
        {
            m_End->parent = new_node;
        }
        else if (side == true)
        {
            prev_node->right = new_node;
        }
        else
        {
            prev_node->left = new_node;
        }
        m_End->left = get_left_node(m_End->parent);
        m_End->right = get_right_node(m_End->parent);
        ++m_Size;
        return make_pair(iterator(new_node, m_End, m_Comp), true);
    }
    void remove_by_key(value_type to_remove)
    {
        remove_by_key_rec(m_End->parent, to_remove);
    }
    size_type size(void) const
    {
        return m_Size;
    }
    Node* begin(void) const
    {
        return m_End->left;
    }
    Node* end(void) const
    {
        return m_End;
    }
    Node* begin(void)
    {
        return m_End->left;
    }
    Node* end(void)
    {
        return m_End;
    }

    void swap(bst& other)
    {
        if (this != &other)
        {
            Node* tmp = m_End;
            size_type tmp_size = m_Size;
            Compare tmp_comp = m_Comp;
            Allocator tmp_allocator = m_Allocator;
            
            m_End = other.m_End;
            m_Size = other.m_Size;
            m_Comp = other.m_Comp;
            m_Allocator = other.m_Allocator;
            
            other.m_End = tmp;
            other.m_Size = tmp_size;
            other.m_Comp = tmp_comp;
            other.m_Allocator = tmp_allocator;
        }
    }
private:
    Node* m_End;
    size_type m_Size;
    Compare m_Comp;
    Allocator m_Allocator;
private:
    Node* get_left_node(Node* root)
    {
        while (root != m_End && root->left != m_End)
        {
            root = root->left;
        }
        return (root);
    }
    Node* get_right_node(Node* root)
    {
        while (root != m_End && root->right != m_End)
        {
            root = root->right;
        }
        return (root);
    }

    void replace_node_in_parent(Node* node, Node* new_node)
    {
        if (node->parent != m_End)
        {
            if (m_End->parent == node)
            {
                m_End->parent = new_node;
            }
            if (node == node->parent->left)
            {
                node->parent->left = new_node;
            }
            else
            {
                node->parent->right = new_node;
            }
        }
        else
        {
            m_End->parent = new_node;
        }
        new_node->parent = node->parent;
        
        m_End->left = get_left_node(m_End->parent);
        m_End->right = get_right_node(m_End->parent);
        
        m_Allocator.destroy(node);
        m_Allocator.deallocate(node, 1);
        --m_Size;
    }

    void replace_double_children(Node*& to_remove, Node* new_node)
    {
        if (new_node->parent != m_End)
        {
            if (new_node->parent != to_remove)
            {
                new_node->parent->left = new_node->right;
            }
        }
        new_node->parent = to_remove->parent;
        if (to_remove->left != new_node)
        {
            new_node->left = to_remove->left;
        }
        if (to_remove->right != new_node)
        {
            new_node->right = to_remove->right;
        }
        if (to_remove->parent != m_End)
        {
            if (to_remove->parent->left == to_remove)
            {
                to_remove->parent->left = new_node;
            }
            else if (to_remove->parent->right == to_remove)
            {
                to_remove->parent->right = new_node;
            }
        }
        else
        {
            m_End->parent = new_node;
        }
        if (to_remove->left != m_End && to_remove->left != new_node)
        {
            to_remove->left->parent = new_node;
        }
        if (to_remove->right != m_End && to_remove->right != new_node)
        {
            to_remove->right->parent = new_node;
        }

        if (to_remove->parent != m_End)
        {
            to_remove->left = m_End;
            to_remove->right = m_End;
            to_remove->parent = new_node;
        }

        m_End->left = get_left_node(m_End->parent);
        m_End->right = get_right_node(m_End->parent);

        m_Allocator.destroy(to_remove);
        m_Allocator.deallocate(to_remove, 1);
        --m_Size;
    }

    void remove_by_key_rec(Node* node, value_type to_remove)
    {
        if (m_Comp(to_remove.first, node->value.first))
        {
            remove_by_key_rec(node->left, to_remove);
            return ;
        }
        if (m_Comp(node->value.first, to_remove.first))
        {
            remove_by_key_rec(node->right, to_remove);
            return ;
        }
        if (node->left != m_End && node->right != m_End)
        {
            Node* successor = get_left_node(node->right);
            replace_double_children(node, successor);
        }
        else if (node->left != m_End)
        {
            replace_node_in_parent(node, node->left);
        }
        else if (node->right != m_End)
        {
            replace_node_in_parent(node, node->right);
        }
        else
        {
            replace_node_in_parent(node, m_End);
        }
    }
};


}

#endif // BST_HPP
