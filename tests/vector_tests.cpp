/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:20:58 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/22 12:13:29 by aashara-         ###   ########.fr       */
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
#include <stdlib.h>
#include <time.h>

template <typename T>
static void test_default_constructor(void)
{
    ft::vector<T> v;

    ASSERT_EQUAL(v.size(), static_cast<size_t>(0));
    ASSERT_EQUAL(v.empty(), true);
    ASSERT_EQUAL(v.capacity(), static_cast<size_t>(0));
}

static void test_default_constructors(TestRunner& tr)
{
    LOG_DURATION("test_default_constructors")
    RUN_TEST(tr, test_default_constructor<int>);
    RUN_TEST(tr, test_default_constructor<char>);
    RUN_TEST(tr, test_default_constructor<void*>);
    RUN_TEST(tr, test_default_constructor<float>);
    RUN_TEST(tr, test_default_constructor<std::string>);
}

static size_t g_test_constructor_lenght;

template <typename T>
static void test_count_constructor()
{
    ft::vector<T> v(g_test_constructor_lenght);

    ASSERT_EQUAL(v.size(), g_test_constructor_lenght);
    ASSERT_EQUAL(v.empty(), false);
    ASSERT_EQUAL(v.capacity(), g_test_constructor_lenght);
    for (size_t i = 0; i < g_test_constructor_lenght; ++i)
    {
        ASSERT_EQUAL(v[i], T());
    }
}

static void test_count_constructors(TestRunner& tr)
{
    LOG_DURATION("test_count_constructors")
    for (g_test_constructor_lenght = 1; g_test_constructor_lenght < 10000; g_test_constructor_lenght += 100)
    {
        RUN_TEST(tr, test_count_constructor<int>);
        RUN_TEST(tr, test_count_constructor<char>);
        RUN_TEST(tr, test_count_constructor<void*>);
        RUN_TEST(tr, test_count_constructor<float>);
        RUN_TEST(tr, test_count_constructor<std::string>);
    }
}

template <typename T>
static void test_count_value_constructor(void)
{
    T random_value = static_cast<T>(rand());
    ft::vector<T> v(g_test_constructor_lenght, random_value);

    ASSERT_EQUAL(v.size(), g_test_constructor_lenght);
    ASSERT_EQUAL(v.empty(), false);
    ASSERT_EQUAL(v.capacity(), g_test_constructor_lenght);
    for (size_t i = 0; i < g_test_constructor_lenght; ++i)
    {
        ASSERT_EQUAL(v[i], random_value);
    }
}

static void test_count_value_constructor_string(void)
{
    std::string random_value = "HelloWorld";
    ft::vector<std::string> v(g_test_constructor_lenght, random_value);

    ASSERT_EQUAL(v.size(), g_test_constructor_lenght);
    ASSERT_EQUAL(v.empty(), false);
    ASSERT_EQUAL(v.capacity(), g_test_constructor_lenght);
    for (size_t i = 0; i < g_test_constructor_lenght; ++i)
    {
        ASSERT_EQUAL(v[i], random_value);
    }
}

static void test_count_value_constructor_ptr(void)
{
    int a;
    void* random_value = &a;
    ft::vector<void*> v(g_test_constructor_lenght, random_value);

    ASSERT_EQUAL(v.size(), g_test_constructor_lenght);
    ASSERT_EQUAL(v.empty(), false);
    ASSERT_EQUAL(v.capacity(), g_test_constructor_lenght);
    for (size_t i = 0; i < g_test_constructor_lenght; ++i)
    {
        ASSERT_EQUAL(v[i], random_value);
    }
}

static void test_count_value_constructors(TestRunner& tr)
{
    LOG_DURATION("test_count_value_constructors")
    srand(time(NULL));
    for (g_test_constructor_lenght = 1; g_test_constructor_lenght < 10000; g_test_constructor_lenght += 100)
    {
        RUN_TEST(tr, test_count_value_constructor<int>);
        RUN_TEST(tr, test_count_value_constructor<char>);
        RUN_TEST(tr, test_count_value_constructor_ptr);
        RUN_TEST(tr, test_count_value_constructor<float>);
        RUN_TEST(tr, test_count_value_constructor_string);
    }
}

int main(void)
{
    TestRunner tr;

    test_default_constructors(tr);
    test_count_constructors(tr);
    test_count_value_constructors(tr);
    return (0);
}
