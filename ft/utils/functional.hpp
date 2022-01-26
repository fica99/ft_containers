/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:58:08 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/26 20:18:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

namespace ft
{

template < class Arg1, class Arg2, class Result >
struct binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template < class T >
struct less : public binary_function<T, T, bool>
{
    bool operator()(const T &lhs, const T &rhs) const { return (lhs < rhs); }
};

}

#endif // FUNCTIONAL_HPP
