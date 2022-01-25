/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:09:33 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/25 17:46:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstdint>

namespace ft
{

    template <bool B, class T = void>
    struct enable_if
    {
    };

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <bool is_integral, typename T>
    struct is_integral_base
    {
        // Member types
        typedef T type;
        typedef bool value_type;

        // Member constants
        static const value_type value = is_integral;

        // Member functions
        operator bool() const
        {
            return value;
        }
    };

    template <typename>
    struct is_integral_type : public is_integral_base<false, bool>
    {
    };

    template <>
    struct is_integral_type<bool> : public is_integral_base<true, bool>
    {
    };

    template <>
    struct is_integral_type<char> : public is_integral_base<true, char>
    {
    };

    template <>
    struct is_integral_type<unsigned char> : public is_integral_base<true, unsigned char>
    {
    };

    template <>
    struct is_integral_type<signed char> : public is_integral_base<true, signed char>
    {
    };

    template <>
    struct is_integral_type<char16_t> : public is_integral_base<true, char16_t>
    {
    };

    template <>
    struct is_integral_type<char32_t> : public is_integral_base<true, char32_t>
    {
    };

    template <>
    struct is_integral_type<wchar_t> : public is_integral_base<true, wchar_t>
    {
    };

    template <>
    struct is_integral_type<short> : public is_integral_base<true, short>
    {
    };

    template <>
    struct is_integral_type<unsigned short> : public is_integral_base<true, unsigned short>
    {
    };

    template <>
    struct is_integral_type<int> : public is_integral_base<true, int>
    {
    };

    template <>
    struct is_integral_type<unsigned int> : public is_integral_base<true, unsigned int>
    {
    };

    template <>
    struct is_integral_type<long> : public is_integral_base<true, long>
    {
    };

    template <>
    struct is_integral_type<unsigned long> : public is_integral_base<true, unsigned long>
    {
    };

    template <>
    struct is_integral_type<long long> : public is_integral_base<true, long long>
    {
    };

    template <>
    struct is_integral_type<unsigned long long> : public is_integral_base<true, unsigned long long>
    {
    };

    template <typename T>
    struct is_integral : public is_integral_type<T>
    {
    };

}
#endif // TYPE_TRAITS_HPP
