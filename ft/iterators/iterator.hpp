/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:46:01 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/24 21:09:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft
{

template<class Iterator>
typename iterator_traits<Iterator>::difference_type do_distance(Iterator first, Iterator last, input_iterator_tag)
{
    typename iterator_traits<Iterator>::difference_type result = 0;
    while (first != last) {
        ++first;
        ++result;
    }
    return result;
}
 
template<class Iterator>
typename iterator_traits<Iterator>::difference_type do_distance(Iterator first, Iterator last, random_access_iterator_tag)
{
    return last - first;
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last)
{
    return do_distance(first, last, iterator_traits<Iterator>::iterator_category);
}

}

#endif // ITERATOR_HPP
