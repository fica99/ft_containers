/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runner.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:40:11 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/20 19:54:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_RUNNER_HPP
# define TEST_RUNNER_HPP

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

namespace TestRunnerPrivate {
    template <
        typename K,
        typename V,
        template <typename, typename> class Map
    >
    std::ostream& PrintMap(std::ostream& os, const Map<K, V>& m) {
        os << "{";
        bool first = true;
        for (typename Map<K, V>::const_iterator it = m.begin(); it != m.end(); ++it) {
            if (!first) {
                os << ", ";
            }
            first = false;
            os << it->first << ": " << it->second;
        }
        return os << "}";
    }
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s) {
    os << "{";
    bool first = true;
    for (typename std::__1::vector<T>::const_iterator it = s.begin(); it != s.end(); ++it) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << *it;
    }
    return os << "}";
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
    os << "{";
    bool first = true;
    for (typename std::__1::set<T>::const_iterator it = s.begin(); it != s.end(); ++it) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << *it;
    }
    return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
    return TestRunnerPrivate::PrintMap(os, m);
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::unordered_map<K, V>& m) {
    return TestRunnerPrivate::PrintMap(os, m);
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = "") {
    if (!(t == u)) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
             os << " hint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    TestRunner() : fail_count(0) {}
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::exception& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        } catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }

    ~TestRunner() {
        std::cerr.flush();
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count;
};

#ifndef FILE_NAME
#define FILE_NAME __FILE__
#endif

#define ASSERT_EQUAL(x, y) {                          \
    std::ostringstream __assert_equal_private_os;       \
    __assert_equal_private_os                           \
        << #x << " != " << #y << ", "                     \
        << FILE_NAME << ":" << __LINE__;                  \
    AssertEqual(x, y, __assert_equal_private_os.str()); \
}

#define ASSERT(x) {                           \
    std::ostringstream __assert_private_os;     \
    __assert_private_os << #x << " is false, "  \
        << FILE_NAME << ":" << __LINE__;          \
    Assert(x, __assert_private_os.str());       \
}

#define RUN_TEST(tr, func) \
    tr.RunTest(func, #func)

#endif // TEST_RUNNER_HPP
