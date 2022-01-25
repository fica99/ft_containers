/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:17:47 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/25 17:46:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <sstream>

#include "../utils/type_traits.hpp"

namespace ft
{

    template <typename T>
    std::string to_string(T n, typename enable_if<is_integral<T>::value>::type * = NULL)
    {
        std::ostringstream ss;
        ss << n;
        return (ss.str());
    }

}

#endif // STRING_HPP
