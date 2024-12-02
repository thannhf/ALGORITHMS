#include <cassert>
#include <iostream>
#include "uint256_t.hpp"

namespace ciphers {
	namespace elliptic_curve_key_exchange {
		typedef struct Point {
			uint256_t x, y;
			inline bool operator == (const Point &p){
				return x == p.x && y == p.y;
			}
			friend std::ostream &operator << (std::ostream &op, const Point &p) {
				op << p.x << " " << p.y;
				return op;
			}
		} Point;
		
		uint256_t exp(uint256_t number, uint256_t power, const uint256_t &mod) {
			if(!power) {
				return uint256_t(1);
			}
			uint_t ans(1);
			number = number % mod;
			while(power){
				if((power & 1)) {
					ans = (ans * number) % mod;
				}
				power >>= 1;
				if(power) {
					number = (number * number) % mod;
				}
			}
			return ans;
		}
		
		Point addition(Point a, Point b, const uint256_t &curve_a_coeff, uint256_t mod) {
			uint256_t lambda(0);
			uint256_t zero(0);
			lambda = zero = 0;
			uint256_t inf = ~zero;
			if(a.x != b.x || a.y != b.y) {
				if(b.x == a.x) {
					return {inf, inf};
				}
				uint256_t num = (b.y - a.y + mod), den = (b.x - a.x + mod);
				lambda = (num * (exp(den, mod - 2, mod))) % mod;
			} else {
				if(!a.y) {
					return {inf, inf};
				}
				uint256_t axsq = ((a.x * a.x)) % mod;
				axsq += (axsq << 1);
				axsq %= mod;
				uint256_t a_2 = (a.y << 1);
				lambda = (((axsq + curve_a_coeff) % mod) * exp(a_2, mod - 2, mod)) % mod;
			}
			Point c;
			c.x = ((lambda * lambda) % mod + (mod << 1) - a.x - b.x) % mod;
			c.y = (((lambda * (a.x + mod - c.x)) % mod) + mod - a.y) % mod;
			return c;
		}
		
		Point multiply(const Point &a, const uint256_t &curve_a_coeff, uint256_t p, const uint256_t &mod) {
			Point N = a;
			N.x %= mod;
			N.y %= mod;
			uint256_t inf{};
			inf = ~uint256_t(0);
			Point Q = {inf, inf};
			while(p) {
				if((p & 1)) {
					if(Q.x == inf && Q.y == inf) {
						Q.x = N.x;
						Q.y = N.y;
					} else {
						Q = addition(Q, N, curve_a_coeff, mod);
					}
				}
				p >>= 1;
				if(p) {
					N = addition(N, N, curve_a_coeff, mod);
				}
			}
			return Q;
		}
	}
}

static void uint128_t_tests() {
	//1st test: Operations test
	uint128_t a("122"), b("2312");
	assert(a + b == 2434);
	assert(b - a == 2190);
	assert(a * b == 282064);
	assert(b / a == 18);
	assert(b % a == 116);
	assert((a & b) == 8);
	assert((a | b) == 2426);
	assert((a ^ b) == 2418);
	assert((a << 64) == uint128_t("2250502776992565297152"));
	assert((b >> 7) == 18);
	
	//2nd test: Operations test
	a = uint128_t("12321421424232142122");
    b = uint128_t("23123212");
    assert(a + b == uint128_t("12321421424255265334"));
    assert(a - b == uint128_t("12321421424209018910"));
    assert(a * b == uint128_t("284910839733861759501135864"));
    assert(a / b == 532859423865LL);
    assert(a % b == 3887742);
    assert((a & b) == 18912520);
    assert((a | b) == uint128_t("12321421424236352814"));
    assert((a ^ b) == uint128_t("12321421424217440294"));
    assert((a << 64) == uint128_t("227290107637132170748078080907806769152"));
}

static void uint256_t_tests() {
	// 1st test: Operations test
    uint256_t a("122"), b("2312");
    assert(a + b == 2434);
    assert(b - a == 2190);
    assert(a * b == 282064);
    assert(b / a == 18);
    assert(b % a == 116);
    assert((a & b) == 8);
    assert((a | b) == 2426);
    assert((a ^ b) == 2418);
    assert((a << 64) == uint256_t("2250502776992565297152"));
    assert((b >> 7) == 18);

    // 2nd test: Operations test
    a = uint256_t("12321423124513251424232142122");
    b = uint256_t("23124312431243243215354315132413213212");
    assert(a + b == uint256_t("23124312443564666339867566556645355334"));
    // Since a < b, the value is greater
    assert(a - b == uint256_t("115792089237316195423570985008687907853246860353"
                              "221642219366742944204948568846"));
    assert(a * b == uint256_t("284924437928789743312147393953938013677909398222"
                              "169728183872115864"));
    assert(b / a == uint256_t("1876756621"));
    assert(b % a == uint256_t("2170491202688962563936723450"));
    assert((a & b) == uint256_t("3553901085693256462344"));
    assert((a | b) == uint256_t("23124312443564662785966480863388892990"));
    assert((a ^ b) == uint256_t("23124312443564659232065395170132430646"));
    assert((a << 128) == uint256_t("4192763024643754272961909047609369343091683" "376561852756163540549632"));
}

static void test() {
	uint256_t a("4451685225093714772084598273548424"), b("2061118396808653202902996166388514"), mod("4451685225093714772084598273548427");
        
    ciphers::elliptic_curve_key_exchange::Point ptr = {
        uint256_t("188281465057972534892223778713752"), uint256_t("3419875491033170827167861896082688")
	};
    
    std::cout << "For alice:\n";
    uint256_t alice_private_key("164330438812053169644452143505618");
    ciphers::elliptic_curve_key_exchange::Point alice_public_key = multiply(ptr, a, alice_private_key, mod);
    std::cout << "\tPrivate key: " << alice_private_key << "\n";
    std::cout << "\tPublic Key: " << alice_public_key << std::endl;
    
    std::cout << "For Bob:\n";
    uint256_t bob_private_key("1959473333748537081510525763478373");
    ciphers::elliptic_curve_key_exchange::Point bob_public_key = multiply(ptr, a, bob_private_key, mod);
    std::cout << "\tPrivate key: " << bob_private_key << "\n";
    std::cout << "\tPublic Key: " << bob_public_key << std::endl;
    
    ciphers::elliptic_curve_key_change::Point alice_shared_key = multiply(bob_public_key, a, alice_private_key, mod),
    bob_shared_key = multiply(alice_public_key, a, bob_private_key, mod);
    
    std::cout << "Shared keys: \n";
    std::cout << alice_shared_key << std::endl;
    std::cout << bob_shared_key << std::endl;
    assert(slice_shared_key == bob_shared_key);
}

int main() {
	uint128_t_tests();
	uint256_t_tests();
	test();
	return 0;
}