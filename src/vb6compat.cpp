/******************************************************************************
    Copyright (C) 2002-2015 Argentum Online & Dakara Online Developers

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


#include <stdarg.h>
#include <memory>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <boost/version.hpp>

/* FIXME: This is broken. See boost issue #10038 */

#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SCOPED_ENUMS

#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "vb6compat.h"

namespace {
	boost::posix_time::ptime tickCountStart;
}

namespace vb6 {

//App_t App_t::Instance;
Err_t Err_t::Instance;

std::string string_format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* reserve 2 times as much as the length of the fmt_str */
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

void InitializeTickCount() {
	tickCountStart = boost::posix_time::second_clock::local_time();
}

std::size_t GetTickCount() {
	boost::posix_time::time_duration diff = boost::posix_time::second_clock::local_time() - tickCountStart;
	return diff.total_milliseconds();
}

void Name(std::string oldName, std::string newName) {
	// Rename a file
	// throw std::runtime_error("Name not implemented");
	// boost::system::error_code ec;
	boost::filesystem::rename(oldName, newName);
}

void Kill(std::string FileName) {
	// Delete a file
	// throw std::runtime_error("Kill not implemented");
	boost::filesystem::remove(FileName);
}

void FileCopy(std::string oldfile, std::string newfile) {
	// throw std::runtime_error("FileCopy not implemented");
	// boost::system::error_code ec;
	boost::filesystem::copy_file(oldfile, newfile, boost::filesystem::copy_option::overwrite_if_exists);
}


}

