/*
 * libEric
 * Copyright (C) 2022   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#include <iostream>
#include <mutex>
#include <sstream>
#include <source_location>
#include <iomanip>


#ifndef ERIC_LOG_H
#define ERIC_LOG_H

//regelt wieviel platz für die Funktionsnamen gelassen wird
#define NAME_WIDTH 30

#define LOG_COLOR_RESET   "\033[0m"
#define LOG_COLOR_BLACK   "\033[30m"      /* Black */
#define LOG_COLOR_RED     "\033[31m"      /* Red */
#define LOG_COLOR_GREEN   "\033[32m"      /* Green */
#define LOG_COLOR_YELLOW  "\033[33m"      /* Yellow */
#define LOG_COLOR_BLUE    "\033[34m"      /* Blue */
#define LOG_COLOR_MAGENTA "\033[35m"      /* Magenta */
#define LOG_COLOR_CYAN    "\033[36m"      /* Cyan */
#define LOG_COLOR_WHITE   "\033[37m"      /* White */
#define LOG_COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define LOG_COLOR_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define LOG_COLOR_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define LOG_COLOR_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define LOG_COLOR_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define LOG_COLOR_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define LOG_COLOR_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define LOG_COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


namespace LibEric {

    enum LogLevel {
        LOG_NONE = 0,
        LOG_ERROR = 1,
        LOG_WARNING = 2,
        LOG_INFO = 3,
        LOG_DEBUG = 4,
        LOG_VERBOSE = 5
    };

    class Log {
    public:
        template<class... Args>
        void error_log(const std::source_location loc, Args &&... args) {
            if (_LogLevel < LOG_ERROR)
                return;
            static std::mutex myMutex;
            std::ostringstream os;      // used to build the logging message
#ifdef _WIN64
            os << "ERROR  : " << std::setw(NAME_WIDTH) << loc.function_name() << " (" << loc.line()
               << "):" << std::boolalpha;

            ((os << ' ' << args), ...);
            os << std::endl;
#else
            os << LOG_COLOR_BOLDRED << "ERROR  : " << std::setw(NAME_WIDTH) << loc.function_name() << " (" << loc.line()
       << "):" << std::boolalpha;
    // fold expression:
    ((os << ' ' << args), ...); // add all arguments to os
    os << LOG_COLOR_RESET << std::endl;
#endif

            std::lock_guard<std::mutex> lock(myMutex); // use a lock_guard
            std::clog << os.str();                     // and stream
        }

        template<class... Args>
        void warning_log(const std::source_location loc, Args &&... args) {
            if (_LogLevel < LOG_WARNING)
                return;
            static std::mutex myMutex;
            std::ostringstream os;      // used to build the logging message

#ifdef _WIN64
            os << "WARNING: " << std::setw(NAME_WIDTH) << loc.function_name() << " (" << loc.line()
               << "):" << std::boolalpha;

            ((os << ' ' << args), ...);
            os << std::endl;
#else
            os << LOG_COLOR_BOLDYELLOW << "WARNING: " << std::setw(NAME_WIDTH) << loc.function_name() << " ("
               << loc.line() << "):" << std::boolalpha;

            // fold expression:
            ((os << ' ' << args), ...); // add all arguments to os
            os << LOG_COLOR_RESET << std::endl;
#endif
            std::lock_guard<std::mutex> lock(myMutex); // use a lock_guard
            std::clog << os.str();                     // and stream
        }

        template<class... Args>
        void info_log(const std::source_location loc, Args &&... args) {
            if (_LogLevel < LOG_INFO)
                return;
            static std::mutex myMutex;
            std::ostringstream os;      // used to build the logging message

#ifdef _WIN64
            os << "INFO   : " << std::setw(NAME_WIDTH) << loc.function_name() << " (" << loc.line()
               << "):" << std::boolalpha;

            ((os << ' ' << args), ...);
            os << std::endl;
#else
            os << LOG_COLOR_BOLDGREEN << "INFO   : " << std::setw(NAME_WIDTH) << loc.function_name() << " ("
               << loc.line() << "):" << std::boolalpha;

            // fold expression:
            ((os << ' ' << args), ...); // add all arguments to os
            os << LOG_COLOR_RESET << std::endl;
#endif
            std::lock_guard<std::mutex> lock(myMutex); // use a lock_guard
            std::clog << os.str();                     // and stream
        }

        template<class... Args>
        void debug_log(const std::source_location loc, Args &&... args) {
            if (_LogLevel < LOG_DEBUG)
                return;
            static std::mutex myMutex;
            std::ostringstream os;      // used to build the logging message

#ifdef _WIN64
            os << "DEBUG  : " << std::setw(NAME_WIDTH) << loc.function_name() << " (" << loc.line()
               << "):" << std::boolalpha;

            ((os << ' ' << args), ...);
            os << std::endl;
#else
            os << LOG_COLOR_BOLDBLUE << "DEBUG  : " << std::setw(NAME_WIDTH) << loc.function_name() << " ("
               << loc.line() << "):" << std::boolalpha;

            // fold expression:
            ((os << ' ' << args), ...); // add all arguments to os
            os << LOG_COLOR_RESET << std::endl;
#endif
            std::lock_guard<std::mutex> lock(myMutex); // use a lock_guard
            std::clog << os.str();                     // and stream
        }

        template<class... Args>
        void verbose_log(const std::source_location loc, Args &&... args) {
            if (_LogLevel < LOG_VERBOSE)
                return;
            static std::mutex myMutex;
            std::ostringstream os;      // used to build the logging message

#ifdef _WIN64
            os << "VERBOSE  : " << std::setw(NAME_WIDTH) << loc.function_name() << " (" << loc.line()
               << "):" << std::boolalpha;

            ((os << ' ' << args), ...);
            os << std::endl;
#else
            os << LOG_COLOR_BOLDWHITE << "VERBOSE: " << std::setw(NAME_WIDTH) << loc.function_name() << " ("
               << loc.line() << "):" << std::boolalpha;

            // fold expression:
            ((os << ' ' << args), ...); // add all arguments to os
            os << LOG_COLOR_RESET << std::endl;
#endif
            std::lock_guard<std::mutex> lock(myMutex); // use a lock_guard
            std::clog << os.str();                     // and stream
        }

        static Log *Instance();

        void SetLogLevel(int logLevel);

    private:
        Log();

        int _LogLevel;
        static Log *_Instance;
    };


} // LibEric

#define LOGE(...) LibEric::Log::Instance()->error_log(std::source_location::current(), __VA_ARGS__)
#define LOGW(...) LibEric::Log::Instance()->warning_log(std::source_location::current(), __VA_ARGS__)
#define LOGI(...) LibEric::Log::Instance()->info_log(std::source_location::current(), __VA_ARGS__)
#define LOGD(...) LibEric::Log::Instance()->debug_log(std::source_location::current(), __VA_ARGS__)
#define LOGV(...) LibEric::Log::Instance()->verbose_log(std::source_location::current(), __VA_ARGS__)

#endif //ERIC_LOG_H
