/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:46:01 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/29 01:04:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template <class It>
typename iterator_traits<It>::difference_type distance(It first, It last)
{
    typename iterator_traits<It>::difference_type result = 0;
    while (first != last)
    {
        ++first;
        ++result;
    }
    return result;
}

}

#endif // ITERATOR_HPP
