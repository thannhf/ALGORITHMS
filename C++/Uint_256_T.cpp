#include <string>
#include <utility>
#include "uint128_t.hpp"

#ifndef CIPHERS_UINT256_T_HPP_
#define CIPHERS_UINT256_T_HPP_

class uint256_t;
template <> struct std::is_integral<uint256_t> : std::true_type{};
template <> struct std::is_arithmetic<uint256_t> : std::true_type{};
template <> struct std::is_unsigned<uint256_t> : std::true_type{};

class uint256_t {
	uint128_t f{}, s{};
	void __get_integer_from_string(const std::string &str) {
		this->f = this->s = uint128_t(0);
		if(str.size() > 1 && str[1] == 'x') {
			for(auto i = 2; i < str.size(); ++i) {
				*this *= 16LL;
				if(str[i] >= '0' && str[i] <= '9') {
					*this += (str[i] - '0');
				} else if(str[i] >= 'A' && str[i] <= 'F') {
					*this += (str[i] - 'A' + 10);
				} else if(str[i] >= 'a' && str[i] <= 'f') {
					*this += (str[i] - 'a' + 10);
				}
			}
		} else {
			for(auto &x : str) {
				*this *= 10LL;
				*this += (x - '0');
			}
		}
	}
	public:
		uint256_t() = default;
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		explicit uint256_t(T low) : s(low), f(0) {}
		explicit uint256_t(const std::string &str) {
			__get_integer_from_string(str);
		}
		uint256_t(const uint256_t &num) = default;
		uint256_t(uint256_t &&num) noexcept : f(std::move(num.f)), s(std::move(num.s)) {}
		uint256_t(uint128_t high, uint128_t low) : f(std::move(high)), s(std::move(low)) {}
		uint256_t(const uint64_t high, const uint64_t low) : f(high), s(low) {}
		~uint256_t() = default;
		inline uint32_t _lez() {
			if(f) {
				return f._lez();
			}
			return 128 + s._lez();
		}
		inline uint32_t _trz() {
			if(s) {
				return s._trz();
			}
			return 128 + f._trz();
		}
		inline explicit operator bool() const {
			return f || s;
		}
		template <typenameT, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline explicit operator T() const {
			return static_cast<T>(s);
		}
		inline explicit operator uint128_t() const {
			return s;
		}
		inline uint128_t lower() const {
			return s;
		}
		inline uint128_t upper() const {
			return f;
		}
		inline uint256_t &operator=(const uint256_t &p) = default;
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t &operator=(const T &p) {
			this->s = p;
			return *this;
		}
		inline uint256_t &operator=(const std::string &p) {
			__get_integer_from_string(p);
			return *this;
		}
		inline uint256_t &operator=(uint256_t &&p) = default;
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator+(const T &p) {
			bool app = s + p < s;
			return uint256_t(f + app, s + p);
		}
		inline uint256_t operator+(const uint256_t &p) {
			bool app = (s + p.s < s);
			return {f + app + p.f, s + p.s};
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t &operator+=(const T &p) {
			bool app = (p + s < s);
			this->f += app;
			this->s += p;
			return *this;
		}
		inline uint256_t &operator+=(const uint256_t &p) {
			bool app = (s + p.s < s);
			f = f + app + p.f;
			s = s + p.s;
			return *this;
		}
		inline uint256_t &operator++() {
			*this += 1;
			return *this;
		}
		inline uint256_t operator++(int) {
			++*this;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator-(const T &p) {
			bool app = (p > s);
			return uint256_t(f - app, s - p);
		}
		inline uint256_t operator-(const uint256_t &p) {
			bool app = s < p.s;
			return {f - p.f - app, s - p.s};
		}
		inline uint256_t operator-() {
			return ~*this + uint256_t(1);
		}
		inline uint256_t &operator--() {
			*this -= 1;
			return *this;
		}
		inline uint256_t operator--(int p) {
			--*this;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator-=(const T p) {
			bool app = (p > s);
			f = f - app;
			s = s - p;
			return *this;
		}
		inline uint256_t &operator-=(const uint256_t &p) {
			bool app = s < p.s;
			f = f - app - p.f;
			s = s - p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator*(const T &p) {
			return *this * uint256_t(p);
		}
		uint256_t operator*(const uint256_t &p) {
			uint128_t f_first(s.upper()), f_second(s.lower()), s_first(p.s.upper()), s_second(p.s.lower());
			uint128_t fi = f_first * s_first, se = f_first * s_second,
				th = s_first * f_second, fo = s_second * f_second;
			uint128_t tmp = se << 64, tmp2 = th << 64;
			int cc = (tmp + tmp2 < tmp);
			tmp += tmp2;
			cc += (tmp + fo < tmp);
			return {f * p.s + s * p.f + fi + se.upper() + th.upper() + cc, tmp + fo};
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t &operator*=(const T &p) {
			return (*this *= uint256_t(p));
		}
		uint256_t &operator*=(const uint256_t &p) {
			uint128_t f_first(s.upper()), f_second(s.lower()), s_first(p.s.upper()), s_second(p.s.lower());
			uint128_t fi = f_first * s_first, se = f_first * s_second,
				th = s_first * f_second, fo = s_second * f_second;
			uint128_t tmp = se << 64, tmp2 = th << 64;
			int cc = (tmp + tmp2 < tmp);
			tmp += tmp2;
			cc += (tmp + fo < tmp);
			f = f * p.s + s * p.f + fi + se.upper() + th.upper() + cc;
			s = tmp + fo;
			return *this;
		}
		std::pair<uint256_t, uint256_t> divide(const uint256_t &p) {
			if(*this < p) {
				return {uint256_t(0), *this};
			} else if(*this == p) {
				return {uint256_t(1), uint256_t(0)};
			}
			uint256_t tmp = p, tmp2 = *this;
			uint16_t left = tmp._lez() - _lez();
			tmp <<= left;
			uint256_t quotient(0);
			uint256_t zero(0);
			while(tmp2 >= p) {
				uint16_t shf = tmp2._lez() - tmp._lez();
				if(shf) {
					tmp >>= shf;
					quotient <<= shf;
					left -= shf;
				}
				if(tmp2 < tmp) {
					tmp >>= 1;
					quotient <<= 1;
					--left;
				}
				tmp2 -= tmp;
				++quotient;
			}
			return {quotient << left, tmp2};
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator/(const T &p) {
			uint256_t tmp = *this;
			tmp /= uint256_t(p);
			return tmp;
		}
		inline uint256_t operator/(const uint256_t &p) {
			return divide(p).first;
		}
		inline uint256_t &operator/=(const uint256_t &p) {
			*this = divide(p).first;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t &operator/=(const T &p) {
			*this /= uint256_t(p);
			return *this;
		}
		inline uint256_t operator%(const uint256_t &p) {
			return divide(p).second;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator%(const T &p) {
			uint256_t tmp = *this;
			tmp %= uint256_t(p);
			return tmp;
		}
		inline uint256_t &operator%=(const uint256_t &p) {
			*this = divide(p).second;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t &operator%=(const T &p) {
			*this %= uint256_t(p);
			return *this;
		}
		inline bool operator<(const uint256_t &other) {
			return f < other.f || (f == other.f && s < other.s);
		}
		inline bool operator<=(const uint256_t &other) {
			return f < other.f || (f == other.f && s <= other.s);
		}
		inline bool operator>(const uint256_t &other) {
			return f > other.f || (f == other.f && s > other.s);
		}
		inline bool operator>=(const uint256_t &other) {
			return (f > other.f) || (f == other.f && s >= other.s);
		}
		inline bool operator==(const uint256_t &other) {
			return f == other.f && s == other.s;
		}
		inline bool operator!=(const uint256_t &other) {
			return !((*this) == other);
		}
		inline bool operator!() {
			return !f && !s;
		}
		inline bool operator&&(const uint256_t &b) {
			return (s || f) && (b.s || b.f);
		}
		inline bool operator||(const uint256_t &b) {
			return (s || f) || (b.s || b.f);
		}
		inline bool operator()(){
			return s || f;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		bool operator<(const T &other){
			return *this < uint256_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		bool operator<=(const T &other) {
			return *this <= uint256_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		bool operator>(const T &other) {
			return *this > uint256_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		bool operator>=(const T &other) {
			return *this >= uint256_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		bool operator==(const T &other) {
			return *this == uint256_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		bool operator!=(const T &other) {
			return *this != uint256_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator&&(const T &b) {
			return (s || f) && (b);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator||(const T &b) {
			return (s || f) || (b);
		}
		inline uint256_t operator~() {
			return {~f, ~s};
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint256_t operator<<(const T &p) {
			if(!p) {
				return {this->f, this->s};
			} else if(p >= 128) {
				return uint256_t((this->s << (p - 128)), uint128_t(0));
			}
			return uint256_t((this->f << p) + (this->s >> (128 - p)), (this->s << p));
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint256_t &operator<<=(const T &p) {
			if(p) {
				if(p >= 120) {
					this->f = (this->s << (p - 128));
					this->s = uint128_t(0);
				} else {
					f = ((this->s >> (128 - p)) + (this->f << p));
					s = (this->s << p);
				}
			}
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint128_t operator>>(const T &p) {
			if(!p) {
				return {this->f, this->s};
			} else if(p >= 128) {
				return uint256_t(uint128_t(0), (this->f >> (p - 128)));
			}
			return uint256_t((this->f >> p), (this->s >> p) + (this->f << (128 - p)));
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint256_t &operator>>=(const T &p) {
			if(p) {
				if(p >= 128) {
					f = uint128_t(0);
					s = (this->f >> (p - 128));
				} else {
					s = (this->s >> p) + (this->f << (128 - p));
					f = (this->f >> p);
				}
			}
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator&(const T &p) {
			return *this & uint256_t(p);
		}
		inline uint256_t operator&(const uint256_t &p) {
			return {f & p.f, s & p.s};
		}
		inline uint256_t &operator&=(const uint256_t &p) {
			f &= p.f;
			s &= p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t &operator&=(const T p) {
			s &= p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator|(const T &p) {
			return *this | uint256_t(p);
		}
		inline uint256_t operator|(const uint256_t &p) {
			return (this->f | p.f, this->s | p.s);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t &operator|=(const T &p) {
			s |= p;
			return *this;
		}
		inline uint256_t &operator|=(const uint256_t &p) {
			f |= p.f;
			s |= p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t operator^(const T &p) {
			return uint256_t(f, s ^ p);
		}
		inline uint256_t operator^(const uint256_t &p) {
			return {this->f ^ p.f, this->s ^ p.s};
		}
		inline uint256_t &operator^=(const uint256_t &p) {
			f ^= p.f;
			s ^= p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint256_t &operator^=(const T &p) {
			s ^= p;
			return *this;
		}
		friend std::ostream &operator<<(std::ostream &op, uint256_t p) {
			if(!p.f) {
				op << p.s;
			} else {
				std::string out = "0", p_2 = "1";
				uint128_t L(1);
				for(uint64_t i = 0; i < 128; ++i) {
					if((p.s & L)) {
						out = add(out, p_2);
					}
					p_2 = add(p_2, p_2);
					L <<= 1;
				}
				L = uint128_t(1);
				for(int i = 0; i < 128; ++i) {
					if((p.f & L)) {
						out = add(out, p_2);
					}
					p_2 = add(p_2, p_2);
					L <<= 1;
				}
				op << out;
			}
			return op;
		}
};

//Artihmetic
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint256_t operator+(const T p, const uint256_t &q) {
	return uint256_t(p) + q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint256_t operator-(const T p, const uint256_t &q) {
	return (uint256_t(p) - q);
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint256_t operator*(const T p, const uint256_t &q) {
	return uint256_t(p) * q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint256_t operator/(const T p, const uint256_t &q) {
	return uint256_t(p) / q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint256_t operator%(const T p, const uint256_t &q) {
    return uint256_t(p) % q;
}
//bitwise operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator&(const T &p, const uint256_t &q) {
    return uint256_t(p) & q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator|(const T p, const uint256_t &q) {
    return uint256_t(p) | q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline uint256_t operator^(const T p, const uint256_t &q) {
    return uint256_t(p) ^ q;
}

// Boolean operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator&&(const T p, const uint256_t &q) {
    return uint256_t(p) && q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator||(const T p, const uint256_t &q) {
    return uint256_t(p) || q;
}

// Comparison operators
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator==(const T p, const uint256_t &q) {
    return uint256_t(p) == q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator!=(const T p, const uint256_t &q) {
    return uint256_t(p) != q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<(const T p, const uint256_t &q) {
    return uint256_t(p) < q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<=(const T p, const uint256_t &q) {
    return uint256_t(p) <= q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>(const T p, const uint256_t &q) {
    return uint256_t(p) > q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>=(const T p, const uint256_t &q) {
    return uint256_t(p) >= q;
}
#endif