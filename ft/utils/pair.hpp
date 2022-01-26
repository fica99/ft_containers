/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:41:55 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/26 20:17:03 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{

template < class T1, class T2 >
struct pair
{
public:
    typedef T1 first_type;
    typedef T2 second_type;
    T1 first;
    T2 second;
    pair(void) : first(), second() { }
    pair(const first_type& x, const second_type& y) : first(x), second(y) { }
    template <class U1, class U2>
    pair(const pair<U1, U2>& other) : first(other.first), second(other.second) { }
    pair& operator=(const pair& other)
    {
        if (this != &other)
        {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
};

template < class T1, class T2 >
pair<T1, T2> make_pair(T1 t, T2 u)
{
    return pair<T1, T2>(t, u);
}

template < class T1, class T2 >
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template < class T1, class T2 >
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs == rhs);
}

template < class T1, class T2 >
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    if (lhs.first < rhs.first)
    {
        return true;
    }
    else if (rhs.first < lhs.first)
    {
        return false;
    }
    else
    {
        if (lhs.second < rhs.second)
        {
            return true;
        }
    }
    return false;
}

template < class T1, class T2 >
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(rhs < lhs);
}

template < class T1, class T2 >
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return rhs < lhs;
}
template < class T1, class T2 >
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs < rhs);
}

}

#endif // PAIR_HPP
