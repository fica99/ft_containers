/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:20:58 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/20 20:55:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifdef STD
    #include <vector>
    namespace ft=std;
#else
    #include <vector.hpp>
#endif

#include "test_runner.hpp"
#include "profile.hpp"
#include <string>

class VectorTest
{
};

template <typename T>
static void test_default_constructor(void)
{
    ft::vector<T> v;

    ASSERT_EQUAL(v.size(), static_cast<size_t>(0));
    ASSERT_EQUAL(v.empty(), true);
}

static void test_default_constructors(TestRunner& tr)
{
    LOG_DURATION("test_default_constructors")
    RUN_TEST(tr, test_default_constructor<int>);
    RUN_TEST(tr, test_default_constructor<char>);
    RUN_TEST(tr, test_default_constructor<void*>);
    RUN_TEST(tr, test_default_constructor<float>);
    RUN_TEST(tr, test_default_constructor<std::string>);
    RUN_TEST(tr, test_default_constructor<VectorTest>);
}

int main(void)
{
    TestRunner tr;

    test_default_constructors(tr);
    return (0);
}
