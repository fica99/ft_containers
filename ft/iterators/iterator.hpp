/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:46:01 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/26 20:20:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template <class It>
typename iterator_traits<It>::difference_type do_distance(It first, It last, input_iterator_tag)
{
    typename iterator_traits<It>::difference_type result = 0;
    while (first != last)
    {
        ++first;
        ++result;
    }
    return result;
}

template <class It>
typename iterator_traits<It>::difference_type do_distance(It first, It last, random_access_iterator_tag)
{
    return last - first;
}

template <class It>
typename iterator_traits<It>::difference_type distance(It first, It last)
{
    return do_distance(first, last, typename iterator_traits<It>::iterator_category());
}

}

#endif // ITERATOR_HPP
