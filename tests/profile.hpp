/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:53:30 by aashara-          #+#    #+#             */
/*   Updated: 2022/01/20 19:59:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROFILE_HPP
# define PROFILE_HPP

#include <sys/time.h>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>

class LogDuration {
public:
    explicit LogDuration(const std::string& msg = "")
    : message(msg + ": ")
    {
        struct timeval start;
        gettimeofday(&start, NULL);
        start_ms = start.tv_sec * 1000 + start.tv_usec / 1000;
    }

    ~LogDuration() {
        struct timeval finish;
        gettimeofday(&finish, NULL);
        std::ostringstream os;
        long int finish_ms = finish.tv_sec * 1000 + finish.tv_usec / 1000;
        os << message
            << finish_ms - start_ms
            << " ms" << std::endl;
        std::cerr << os.str();
    }
private:
    std::string message;
    long int start_ms;
};

#ifndef UNIQ_ID
    #define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
    #define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#endif

#define LOG_DURATION(message) \
    LogDuration UNIQ_ID(__LINE__)(message);

#endif // PROFILE_HPP
