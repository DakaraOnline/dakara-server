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



#ifndef VB6COMPAT_H
#define VB6COMPAT_H

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/date_time/time.hpp>
#include <boost/date_time/time_clock.hpp>
#include <boost/date_time/time_duration.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#define vbGreen 0x0000ff00
#define vbWhite 0x00ffffff
#define vbRed 0x00ff0000
#define vbBlue 0x0000ff
#define vbCyan 0x0000ffff
#define vbYellow 0x00ffff00
#define vbCrLf "\r\n"

void dakara_print_backtrace();

namespace vb6 {

template <typename T>
class array {
public:

	typedef typename std::vector<T>::iterator iterator;

	array() : lbound_(0), ubound_(0) {

	}

	T& operator[](std::size_t idx) {
		if (idx < lbound_ || idx > ubound_) {
			dakara_print_backtrace();
			throw std::runtime_error("out of bounds: " + std::to_string(idx));
		}
		return data_[idx - lbound_];
	}

	const T& operator[](std::size_t idx) const {
		if (idx < lbound_ || idx > ubound_) {
			dakara_print_backtrace();
			throw std::runtime_error("out of bounds: " + std::to_string(idx));
		}
		return data_[idx - lbound_];
	}

	/** Empty the container.
	 *
	 */
	void redim() {
		data_.resize(0);
		lbound_ = 1;
		ubound_ = 0;
	}

	void redim(std::size_t ubound) {
		data_.resize(ubound + 1);
		lbound_ = 0;
		ubound_ = ubound;
	}

	void redim(std::size_t lbound, std::size_t ubound) {
		data_.resize(ubound - lbound + 1);
		lbound_ = lbound;
		ubound_ = ubound;
	}

	std::size_t lbound() const {
		return lbound_;
	}

	std::size_t ubound() const {
		return ubound_;
	}

	iterator begin() {
		return data_.begin();
	}

	iterator end() {
		return data_.end();
	}

	std::vector<T>& data() {
		return data_;
	}

private:
	std::vector<T> data_;
	std::size_t lbound_;
	std::size_t ubound_;
};

struct Variant {};
struct Object {};
typedef std::size_t Date;

/*
struct Collection {
	int Count() { return 0; }
	void Remove(int i) {}
	int Item(int i) { return 0; }
};
*/

struct Err_t {
	static Err_t Instance;
	int Number;
	std::string description;
};

inline Err_t & Err() {
	return Err_t::Instance;
}

/*
struct App_t {
	static App_t Instance;
	std::string Path2;
};

inline App_t & App() {
	return App_t::Instance;
}
*/

/*
 *
 */

std::string string_format(const std::string fmt_str, ...);

/*
 *
 */

void InitializeTickCount();

std::size_t GetTickCount();

void Name(std::string oldName, std::string newName);

void Kill(std::string FileName);

void FileCopy(std::string oldfile, std::string newfile);

inline bool IsNumeric(std::string str) {
	if (str.size() == 0)
		return false;
	for (auto c : str) {
		if (!::isdigit(c))
			return false;
	}
	return true;
}

template <typename T>
inline T string_to(const std::string& e) {
	std::stringstream ss;
	ss << e;
	T n;
	if (ss >> n) {
		return n;
	}
	throw std::runtime_error(std::string("Invalid Format: ") + e);
}

template <typename T>
inline int Sgn(T n) {
	return (n > 0) ? 1 : ((n == 0) ? 0 : -1);
}

template <typename T>
inline std::string CStr(T n) {
	return std::to_string(n);
}

template <>
inline std::string CStr<std::string>(std::string n) {
	return (n);
}

template <>
inline std::string CStr<bool>(bool n) {
	return (n) ? "true" : "false";
}

template <>
inline std::string CStr<const char*>(const char* n) {
	return std::string(n);
}

template <typename T>
inline std::string Format(T n, std::string fmt) {
	/* FIXME: Borrar esto */
	(void)fmt;
	return CStr(n);
}

template <typename T>
inline std::string str(T n) {
	return std::to_string(n);
}

template <typename T>
inline double Sqr(T n) {
	return std::sqrt(n);
}

inline double Rnd() {
	return (std::rand() * 1.0) / RAND_MAX;
}

template <typename T>
inline int Fix(T n) {
	return (int)n;
}

template <typename T>
inline int Round(T n) {
	return std::round(n);
}

template <typename T>
inline int Round(T n, int decimal_places) {
	return std::round(n * std::pow(10, decimal_places)) / std::pow(10, decimal_places);
}

inline int RGBtoInt(int r, int g, int b) {
	return (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff); 
}

template <typename T>
inline bool CBool(const T& e) {
	return static_cast<bool>(e);
}

template <typename T>
inline int CByte(const T& e) {
	return static_cast<int>(e);
}

template <>
inline int CByte<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<int>(e);
}

template <typename T>
inline int CInt(const T& e) {
	return static_cast<int>(e);
}

template <typename T>
inline int Int(const T& e) {
	return static_cast<int>(e);
}

template <>
inline int CInt<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<int>(e);
}

template <typename T>
inline int CLng(const T& e) {
	return static_cast<int>(e);
}

template <>
inline int CLng<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<int>(e);
}

template <typename T>
inline double CDbl(const T& e) {
	return static_cast<double>(e);
}

template <>
inline double CDbl<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<double>(e);
}

template <typename T>
inline double CSng(const T& e) {
	return static_cast<double>(e);
}

template <>
inline double CSng<std::string>(const std::string& e) {
	if (e.size() == 0) return 0;
	return string_to<double>(e);
}

inline std::string DateAdd(const std::string &fmt, int cant, boost::posix_time::ptime d) {
	int dias;
	if (fmt == "d")
		dias = cant;
	else {
		if (fmt == "m")
			dias = cant * 30;
		else {
			if (fmt == "a")
				dias = cant * 365;
			else
				throw std::runtime_error("comando invalido en DateAdd");
		}
	}

	boost::gregorian::date_duration dur(dias);
	d += dur;
	return boost::posix_time::to_simple_string(d);
}

inline std::string dateToString(const boost::posix_time::ptime &d){// todas las fechas formato : "2002-01-20 23:59:59.000"
	std::stringstream mes;
	mes << std::setw(2) << std::setfill('0') << d.date().month().as_number();
	std::string res = boost::posix_time::to_simple_string(d);
	res.erase(5,3); // remplazo mes en letras por numeros
	res.insert(5,mes.str());
	return boost::posix_time::to_simple_string(d);
}

inline boost::posix_time::ptime Now() {
	return boost::posix_time::second_clock::local_time();
}

inline boost::posix_time::ptime CDate(const std::string &str) {
	return (boost::posix_time::time_from_string(str));
}


inline int Hour(const boost::posix_time::ptime &t) {
	return t.time_of_day().hours();
}

inline int Minute(boost::posix_time::ptime t) {
	return t.time_of_day().minutes();
}

inline int Second(boost::posix_time::ptime t) {
	return t.time_of_day().seconds();
}

inline int Weekday(boost::posix_time::ptime t) {
	return t.date().day_of_week()+1;
}

inline std::string Replace(const std::string& str, const std::string& strold, const std::string& strnew) {
	std::string res(str);
	std::size_t p = 0;
	for (;;) {
		p = res.find(strold, p);
		if (p == std::string::npos)
			break;
		res.replace(p, strold.size(), strnew);
		p += strnew.size();
	}
	return res;
}

inline std::vector<std::string> Split(const std::string& s, std::string sep) {
	std::vector<std::string> res;

	if (sep.length() > 0) {
		std::size_t ant = 0, pos = s.find(sep);

		while (pos != std::string::npos) {
			res.push_back(s.substr(ant, pos - ant));
			ant = pos + sep.length();
			pos = s.find(sep, ant);
		}

		res.push_back(s.substr(ant));
	} else {
		res.push_back(s);
	}

	return res;
}

inline std::string Space(int n) {
	return std::string(static_cast<std::size_t>(n), ' ');
}

/*
inline void ChDir(const std::string& str) {
	throw std::runtime_error("ChDir not implemented");
}

inline void ChDrive(const std::string& str) {
	throw std::runtime_error("ChDrive not implemented");
}

inline std::string dir(const std::string& str) {
	throw std::runtime_error("dir not implemented");
}
*/


inline std::string Chr(int c) {
	return std::string(&c, &c+1);
}

inline int Asc(std::string c) {
	return *reinterpret_cast<const unsigned char*>(c.c_str());
}

inline void MsgBox(const std::string& str) {
	std::cerr << "MsgBox: " << str << std::endl;
}

//inline bool Eof(int fileNum) {
//	throw std::runtime_error("EOF not implemented");
//}

//inline int FreeFile(int range = 0) {
//	throw std::runtime_error("FreeFile not implemented");
//}

inline std::string RTrim(const std::string& str) {
	if (str.size() == 0)
		return std::string();
	std::size_t k = str.size() - 1;
	// "0123456789"
	// " hola "
	// "  newbi   "
	while (k > 0 && str[k] == ' ') {
		--k;
	}
	if ((k == 0 && str[k] == ' '))
		return std::string();
	return str.substr(0, k + 1);
}

inline std::string LTrim(const std::string& str) {
	if (str.size() == 0)
		return std::string();
	std::size_t i = 0;
	while (i < str.size() && str[i] == ' ') {
		++i;
	}
	return (i > 0) ? str.substr(i, str.size() - i) : str;
}

inline std::string Trim(const std::string& str) {
	if (str.size() == 0)
		return str;
	std::size_t i = 0, k = str.size() - 1;
	while (i < str.size() && str[i] == ' ') {
		++i;
	}
	// "0123456789"
	// " hola "
	// "  newbi   "
	while (k > 0 && str[k] == ' ') {
		--k;
	}
	if ((k == 0 && str[k] == ' ') || ((int)k - (int)i + 1) <= 0)
		return std::string();
	return str.substr(i, k - i + 1);
}

inline double val(const std::string& str) {
    if (str.size() == 0) return 0;
	return string_to<double>(str);
}

inline std::size_t InStr(std::size_t start, const std::string& haystack, const std::string& needle) {
	std::size_t r = haystack.find(needle, start - 1);
	return (r == std::string::npos) ? 0 : (r + 1);
}

inline std::size_t InStr(const std::string& haystack, const std::string& needle) {
	std::size_t r = haystack.find(needle, 0);
	return (r == std::string::npos) ? 0 : (r + 1);
}

inline std::size_t InStrB(std::size_t start, const std::string& haystack, const std::string& needle) {
	return InStr(start, needle, haystack);
}

inline std::size_t InStrB(const std::string& haystack, const std::string& needle) {
	return InStr(1, needle, haystack);
}

inline std::string LCase(const std::string& s) {
	std::string slo(s);
	std::transform(slo.begin(), slo.end(), slo.begin(), ::tolower);
	return slo;
}

inline std::string UCase(const std::string& s) {
	std::string sup(s);
	std::transform(sup.begin(), sup.end(), sup.begin(), ::toupper);
	return sup;
}

inline std::string Right(const std::string& s, int len) {
	return s.substr(s.size() - len, len);
}

inline std::string Left(const std::string& s, int len) {
	return s.substr(0, len);
}

/** substring. starts at 1.
 *
 */
inline std::string Mid(const std::string& s, int start, int len) {
	return s.substr(start - 1, len);
}

template <typename T>
inline T IIf(bool cond, T a, T b) {
	return cond ? a : b;
}

template <typename T>
inline T Abs(const T& x) {
	return std::abs(x);
}

template <typename T>
inline int UBound(const std::vector<T>& v) {
	return (int)v.size() - 1;
}

template <typename T>
inline int LBound(const array<T>& v) {
	return v.lbound();
}

template <typename T>
inline int UBound(const array<T>& v) {
	return v.ubound();
}

inline std::size_t Len(const std::string& v) {
	return v.size();
}

inline std::size_t LenB(const std::string& v) {
	return v.size();
}

template <typename T>
T Constrain(T x, T a, T b) {
	if (x < a) return a;
	if (x > b) return b;
	return x;
}

}

#endif

