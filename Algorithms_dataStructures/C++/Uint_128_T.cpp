#include <algorithm>
#include <ostream>
#include <string>
#include <utility>

#ifdef _MSC_VER
#include <intrin.h>
#endif

#ifndef CIPHERS_UINT128_T_HPP_
#define CIPHERS_UINT128_T_HPP_
class uint128_t;

template <> struct std::is_integral<uint128_t> : std::true_type{};
template <> struct std::is_arithmetic<uint128_t> : std::true_type{};
template <> struct std::is_unsigned<uint128_t> : std::true_type{};

std::string add(const std::string &first, const std::string &second) {
	std::string third;
	int16_t sum = 0, carry = 0;
	for(int32_t i = static_cast<int32_t>(first.size()) -1, j = static_cast<int32_t>(second.size()) - 1; i >= 0 || j >= 0; --i, --j) {
		sum = ((i >= 0 ? first[i] - '0' : 0) + (j >= 0 ? second[j] - '0' : 0) + carry);
		carry = sum / 10;
		sum %= 10;
		third.push_back(sum + '0');
	}
	if(carry) {
		third.push_back('1');
	}
	std::reverse(third.begin(), third.end());
	return third;
}

class uint128_t {
	uint64_t f{}, s{};
	
	void __get_integer_from_string(const std::string &str) {
		this->f = this->s = 0;
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
		uint128_t() = default;
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		explicit uint128_t(T low) : s(low) {}
		explicit uint128_t(const std::string &str) {
			__get_integer_from_string(str);
		}
		
		uint128_t(const uint64_t high, const uint64_t low) : f(high), s(low) {}
		uint128_t(const uint128_t &num) = default;
		uint128_t(uint128_t &&num) noexcept : f(num.f), s(num.s) {}
		~uint128_t() = default;
		inline uint32_t _lez() {
#ifndef _MSC_VER
			if(f) {
				return __builtin_clzll(f);
			}
			return 64 + __builtin_clzll(s);
#else
			unsigned long r = 0;
			_BitScanForward64(&r, f);
			if(r == 64) {
				unsigned long l = 0;
				_BitScanForward64(&l, s);
				return 64 + l;
			}
			return r;
#endif
		}
		
		inline uint32_t _trz() {
#ifndef _MSC_VER
			if(f) {
				return __builtin_ctzll(f);
			}
			return 64 + __builtin_ctzll(s);
#else
			unsigned long r = 0;
			_BitScanReverse64(&r, s);
			if(r == 64) {
				unsigned long l = 0;
				_BitScanReverse64(&l, f);
				return 64 + l;
			}
			return r;
#endif
		}
		
		inline explicit operator bool() const {
			return (f || s);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline explicit operator T() const {
			return static_cast<T>(s);
		}
		inline uint64_t lower() const {
			return s;
		}
		inline uint64_t upper() const {
			return f;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t &operator = (const T &p) {
			this->s = p;
			return *this;
		}
		inline uint128_t &operator = (const std::string &p) {
			this->__get_integer_from_string(p);
			return *this;
		}
		inline uint128_t &operator = (const uint128_t &p) = default;
		inline uint128_t &operator = (uint128_t &&p) = default;
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t operator+(const T p) {
			return uint128_t(f + (p + s < s), p + s);
		}
		inline uint128_t operator+(const uint128_t &p) {
			return uint128_t(f + (p.s + s < s) + p.f, p.s + s);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t &operator+=(const T p) {
			bool app = p + s < s;
			this->f += app;
			this->s += p;
			return *this;
		}
		uint128_t &operator+=(const uint128_t &p) {
			bool app = p.s + s < s;
			f = f + app + p.f;
			s = p.s + s;
			return *this;
		}
		inline uint128_t &operator++() {
			*this += 1;
			return *this;
		}
		inline uint128_t operator++(int) {
			++*this;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t operator-(const T &p) {
			bool app = p > s;
			return uint128_t(f - app, s - p);
		}
		inline uint128_t operator-(const uint128_t &p) {
			bool app = p.s > s;
			return uint128_t(f - p.f - app, s - p.s);
		}
		inline uint128_t operator-() {
			return ~*this + uint128_t(1);
		}
		inline uint128_t &operator--() {
			*this -= 1;
			return *this;
		}
		inline uint128_t operator--(int p) {
			--*this;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint128_t &operator-=(const T &p) {
			bool app = p > s;
			f -= app;
			s -= p;
			return *this;
		}
		uint128_t &operator-=(const uint128_t &p) {
			bool app = p.s > s;
			f = f - p.f - app;
			s = s - p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t operator*(const T p) {
			return *this * uint128_t(p);
		}
		uint128_t operator*(const uint128_t &p) {
			uint64_t f_first = s >> 32,
				f_second = s & 0xFFFFFFFF,
				s_first = p.s >> 32,
				s_second = p.s & 0xFFFFFfFF;
			uint64_t fi = f_first * s_first,
				se = f_first * s_second,
				th = s_first * f_second,
				fo = s_second * f_second;
			uint64_t tmp = ((se & 0xFFFFFFFF) << 32), 
				tmp2 = (th & 0xFFFFFFFF) << 32;
			int cc = (tmp + tmp2 < tmp);
			tmp += tmp2;
			cc += (tmp + fo < tmp);
			uint64_t carry = fi + (se >> 32) + (th >> 32);
			return uint128_t(this->f * p.s + this->s * p.f + carry + cc, tmp + fo);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t &operator*=(const T p) {
			*this *= uint128_t(p);
			return *this;
		}
		uint128_t &operator*=(const uint128_t &p) {
			uint64_t f_first = s >> 32,
				f_second = s & 0xFFFFFFFF,
				f_first = p.s >> 32,
				f_second = p.s & 0xFFFFFFFF;
			uint64_t fi = f_first * s_first,
				se = f_first * s_second,
				th = s_first * s_second,
				fo = s_second * f_second;
			uint64_t tmp = (se << 32), tmp2 = (th << 32);
			int cc = (tmp + tmp2 < tmp);
			tmp += tmp2;
			cc += (tmp + fo < tmp);
			uint64_t carry = fi + (se >> 32) + (th >> 32);
			f = this->f * p.s + this->s * p.f + carry + cc;
			s = tmp + fo;
			return *this;
		}
		std::pair<uint128_t, uint128_t> divide(const uint128_t &p) {
			if(*this < p) {
				return {uint128_t(0), *this};
			} else if(*this == p) {
				return {uint128_t(1), uint128_t(0)};
			}
			uint128_t tmp = p, tmp2 = *this;
			uint16_t left = tmp._lez() - _lez();
			tmp <<= left;
			uint128_t quotient(0);
			uint128_t zero(0);
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
		inline uint128_t operator/(const uint128_t &p) {
			return divide(p).first;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t operator/(const T p) {
			uint128_t tmp = *this;
			tmp /= uint128_t(0, p);
			return tmp;
		}
		inline uint128_t &operator/=(const uint128_t &p) {
			*this = divide(p).first;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t &operator/=(const T p) {
			*this /= uint128_t(0, p);
			return *this;
		}
		inline uint128_t operator%(const uint128_t &p) {
			return divide(p).second;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t operator%(const T &p) {
			return *this % uint128_t(p);
		}
		inline uint128_t &operator%=(const uint128_t &p) {
			*this = divide(p).second;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t &operator%=(const T &p) {
			*this %= uint128_t(p);
			return *this;
		}
		inline bool operator<(const uint128_t &other) {
			return f < other.f || (f == other.f && s < other.s);
		}
		inline bool operator<=(const uint128_t &other) {
			return f < other.f || (f == other.f && s <= other.s);
		}
		inline bool operator>(const uint128_t &other) {
			return f > other.f || (f == other.f && s > other.s);
		}
		inline bool operator>=(const uint128_t &other) {
			return (f > other.f) || (f == other.f && s >= other.s);
		}
		inline bool operator==(const uint128_t &other) {
			return f == other.f && s == other.s;
		}
		inline bool operator!=(const uint128_t &other) {
			return f != other.f || s != other.s;
		}
		inline bool operator!(){
			return !f && !s;
		}
		inline bool operator&&(const uint128_t &b) {
			return (s || f) && (b.s || b.f);
		}
		inline bool operator||(const uint128_t &b) {
			return (s || f) || (b.s || b.f);
		}
		inline bool operator()() {
			return s || f;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator<(const T other) {
			return *this < uint128_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator<=(const T other) {
			return *this <= uint128_t(other);
		}
		template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator>(const T other) {
			return *this > uint128_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator>=(const T other) {
			return *this >= uint128_t(other);
		}
		
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator==(const T other) {
			return *this == uint128_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator!=(const T other) {
			return *this != uint128_t(other);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator&&(const T b) {
			return (f || s) && b;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline bool operator||(const T b) {
			return (f || s) || b;
		}
		uint128_t operator~() {
			return uint128_t(~this->f, ~this->s);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint128_t operator<<(const T p) {
			if(!p) {
				return uint128_t(f, s);
			} else if(p >= 64 && p <= 128) {
				return uint128_t((this->s << (p = 64)), 0);
			}else if(p < 64 && p > 0) {
				return uint128_t((this->f << p) + ((this->s >> (64 - p))), this->s << p);
			}
			return uint128_t(0);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint128_t &operator<<=(const T p) {
			if(p) {
				if(p >= 64 && p <= 128) {
					this->f = (this->s << (p - 64));
					this->s = 0;
				} else {
					f = ((this->f << p) + (this->s >> (64 - p)));
					s = (this->s << p);
				}
			}
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint128_t operator>>(const T p) {
			if(!p) {
				return uint128_t(this->f, this->s);
			} else if(p >= 64 && p <= 128) {
				return uint128_t(0, (this->f >> (p - 64)));
			} else if(p < 64 && p > 0) {
				return uint128_t((this->f >> p), (this->s >> p) + (this->f << (64 - p)));
			}
			return uint128_t(0);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint128_t &operator>>=(const T p) {
			if(p) {
				if(p >= 64) {
					f = 0;
					s = (this->f >> (p - 64));
				} else {
					s = (this->s >> p) + (this->f << (64 - p));
					f = (this->f >> p);
				}
			}
			return *this;
		}
		inline uint128_t operator&(const uint128_t &p) {
			return uint128_t(this->f & p.f, this->s & p.s);
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint128_t operator&(const T p) {
			uint128_t tmp = *this;
			return tmp & uint128_t(p);
		}
		uint128_t &operator&=(const uint128_t &p) {
			this->f &= p.f;
			this->s &= p.s;
			return *this;
		} 
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		uint128_t &operator&=(const T p) {
			*this &= uint128_t(p);
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t operator|(const T p) {
			return uint128_t(p | s);
		}
		inline uint128_t operator|(const uint128_t &p) {
			return uint128_t(this->f | p.f, this->s | p.s);
		}
		uint128_t &operator|=(const uint128_t &p) {
			f |= p.f;
			s |= p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t &operator|=(const T p) {
			s |= p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t operator^(const T p) {
			return uint128_t(this->f, this->s ^ p);
		}
		inline uint128_t operator^(const uint128_t &p) {
			return uint128_t(this->f ^ p.f, this->s ^ p.s);
		}
		uint128_t &operator^=(const uint128_t &p) {
			f ^= p.f;
			s ^= p.s;
			return *this;
		}
		template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		inline uint128_t &operator^=(const T &p) {
			s ^= p;
			return *this;
		}
		friend std::ostream &operator<<(std::ostream &op, const uint128_t &p) {
			if(!p.f) {
				op << p.s;
			} else {
				std::string out = "0", p_2 = "1";
				for(int i = 0; i < 64; ++i) {
					if(p.s & (1LL << i)) {
						out = add(out, p_2);
					}
					p_2 = add(p_2, p_2);
				}
				for(int i = 0; i < 64; ++i) {
					if(p.f & (1LL << i)) {
						out = add(out, p_2);
					}
					p_2 = add(p_2, p_2);
				}
				op << out;
			}
			return op;
		}
			
};

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint128_t operator+(const T &p, const uint128_t &q) {
	return uint128_t(p) + q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint128_t operator-(const T p, const uint128_t &q) {
	return uint128_t(p) - q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint128_t operator*(const T p, const uint128_t &q) {
	return uint128_t(p) * q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint128_t operator/(const T p, const uint128_t &q) {
	return uint128_t(p) / q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint128_t operator%(const T p, const uint128_t &q) {
	return uint128_t(p) % q;
}

//bitwise operators
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint128_t operator&(const T &p, const uint128_t &q) {
	return uint128_t(p) & q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint128_t operator|(const T p, const uint128_t &q) {
	return uint128_t(p) | q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline uint128_t operator^(const T p, const uint128_t &q) {
	return uint128_t(p) ^ q;
}

//boolean operators
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline bool operator&&(const T p, const uint128_t &q) {
	return uint128_t(p) && q;
}
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline bool operator||(const T p, const uint128_t &q) {
	return uint128_t(p) || q;
}

//comparison operators
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
inline bool operator==(const T p, const uint128_t &q) {
	return uint128_t(p) == q;
}
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator!=(const T p, const uint128_t &q) {
    return uint128_t(p) != q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<(const T p, const uint128_t &q) {
    return uint128_t(p) < q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator<=(const T p, const uint128_t &q) {
    return uint128_t(p) <= q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>(const T p, const uint128_t &q) {
    return uint128_t(p) > q;
}

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, T>::type>
inline bool operator>=(const T p, const uint128_t &q) {
    return uint128_t(p) >= q;
}
#endif