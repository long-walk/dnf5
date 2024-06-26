/*
Copyright Contributors to the libdnf project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef LIBDNF5_LOGGER_GLOBAL_LOGGER_HPP
#define LIBDNF5_LOGGER_GLOBAL_LOGGER_HPP

#include "logger.hpp"


namespace libdnf5 {

/// GlobalLogger contains methods for setting the target (logger) for global messages - messages that are
/// generated by libraries (eg librepo) without binding to the Base object.
class LIBDNF_API GlobalLogger {
public:
    explicit GlobalLogger();
    ~GlobalLogger();

    GlobalLogger(const GlobalLogger &) = delete;
    GlobalLogger(GlobalLogger &&) = delete;
    GlobalLogger & operator=(const GlobalLogger &) = delete;
    GlobalLogger & operator=(GlobalLogger &&) = delete;

    static void set(Logger & destination, Logger::Level verbosity);
    static void unset() noexcept;
};

}  // namespace libdnf5

#endif
