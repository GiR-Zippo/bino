/*
 * Copyright (C) 2009, 2010, 2011, 2012
 * Martin Lambers <marlam@marlam.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file str.h
 *
 * Tiny tools for strings.
 */

#ifndef STR_H
#define STR_H

#include <string>
#include <vector>
#include <cstdarg>
#include <cerrno>
#include <stdint.h>

#include "exc.h"

#ifdef __GNUC__
# define STR_AFP(a, b) __attribute__ ((format (printf, a, b)))
#else
# define STR_AFP(a, b) /* empty */
#endif

namespace str
{
    /* Sanitize a string (replace control characters with '?') */
    std::string sanitize(const std::string &s);

    /* Trim a string (remove whitespace from both ends) */
    std::string trim(const std::string &s);

    /* Parse a string into tokens separated by one of the characters in 'delimiters'. */
    std::vector<std::string> tokens(const std::string &s, const std::string &delimiters);

    /* Create std::strings from all basic data types */
    std::string from(bool x);
    std::string from(signed char x);
    std::string from(unsigned char x);
    std::string from(short x);
    std::string from(unsigned short x);
    std::string from(int x);
    std::string from(unsigned int x);
    std::string from(long x);
    std::string from(unsigned long x);
    std::string from(long long x);
    std::string from(unsigned long long x);
    std::string from(float x);
    std::string from(double x);
    std::string from(long double x);

    /* Convert a string to one of the basic data types */
    template<typename T> T to(const std::string &s);
    template<> bool to<bool>(const std::string &s);
    template<> signed char to<signed char>(const std::string &s);
    template<> unsigned char to<unsigned char>(const std::string &s);
    template<> short to<short>(const std::string &s);
    template<> unsigned short to<unsigned short>(const std::string &s);
    template<> int to<int>(const std::string &s);
    template<> unsigned int to<unsigned int>(const std::string &s);
    template<> long to<long>(const std::string &s);
    template<> unsigned long to<unsigned long>(const std::string &s);
    template<> long long to<long long>(const std::string &s);
    template<> unsigned long long to<unsigned long long>(const std::string &s);
    template<> float to<float>(const std::string &s);
    template<> double to<double>(const std::string &s);
    template<> long double to<long double>(const std::string &s);
    template<typename T> bool to(const std::string& s, T* x);
    template<> bool to(const std::string& s, bool* x);
    template<> bool to(const std::string& s, signed char* x);
    template<> bool to(const std::string& s, unsigned char* x);
    template<> bool to(const std::string& s, short* x);
    template<> bool to(const std::string& s, unsigned short* x);
    template<> bool to(const std::string& s, int* x);
    template<> bool to(const std::string& s, unsigned int* x);
    template<> bool to(const std::string& s, long* x);
    template<> bool to(const std::string& s, unsigned long* x);
    template<> bool to(const std::string& s, long long* x);
    template<> bool to(const std::string& s, unsigned long long* x);
    template<> bool to(const std::string& s, float* x);
    template<> bool to(const std::string& s, double* x);
    template<> bool to(const std::string& s, long double* x);

    /* Create std::strings printf-like */
    std::string vasprintf(const char *format, va_list args) STR_AFP(1, 0);
    std::string asprintf(const char *format, ...) STR_AFP(1, 2);

    /* Replace all instances of s with r in str */
    std::string &replace(std::string &str, const std::string &s, const std::string &r);

    /* Create a hex string from binary data */
    std::string hex(const std::string &s, bool uppercase = false);
    std::string hex(const void *buf, size_t n, bool uppercase = false);

    /* Convert various values to human readable strings */
    std::string human_readable_memsize(const uintmax_t size);
    std::string human_readable_length(const double length);
    std::string human_readable_geodetic(double lat, double lon, double elev);
    std::string human_readable_time(int64_t microseconds);

    /* Get the name of the user's character set */
    std::string localcharset();

    /* Convert a string from one character set to another */
    std::string convert(const std::string &src, const std::string &from_charset, const std::string &to_charset);

    /* Wide character and display handling */
    std::wstring to_wstr(const std::string& s);
    size_t display_width(const std::wstring& ws);
    size_t display_width(const std::string& s);
}

#endif
