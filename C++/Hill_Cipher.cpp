#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef _OPENMP
	#include <omp.h>
#endif

#include "../numerical_methods/lu_decomposition.h"

template <typename T>
static std::ostream &operator << (std::ostream &out, matrix<T> const &v) {
	const int width = 15;
	const char separator = ' ';
	for(size_t row = 0; row < v.size(); row++) {
		for(size_t col = 0; col < v[row].size(); col++) {
			out << std::left << std::setw(width) << std::setfill(separator) << v[row][col];
		}
		out << std::endl;
	}
	return out;
}

namespace ciphers {
	static const char *STRKEY = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&" "*()_+`-=[]{}|;':\",./<>?\\\r\n \0";
	class HillCipher {
		private:
			template <typename T1, typename T2>
			static const T2 rand_range(T1 a, T1 b){
				long double r = static_cast<long double>(std::rand()) / RAND_MAX;
				return static_cast<T2>(r * (b - a) + a);
			}
			
			template <typename T1, typename T2>
			static double rand_range(matrix<T2> *M, T1 a, T1 b) {
				for(size_t i = 0; i < M->size(); i++) {
					for(size_t j = 0; j < M[0][0].size(); j++) {
						M[0][i][j] = rand_range<T1, T2>(a, b);
					}
				}
				return determinant_lu(*M);
			}
			
			template <typename T>
			static const T gcd(T a, T b) {
				if(b > a){
					std::swap(a, b);
				}
				
				while (b != 0) {
					T tmp = b;
					b = a % b;
					a = tmp;
				}
				return a;
			}
			
			static const std::valarray<uint8_t> mat_mul(const std::valarray<uint8_t> &vector, const matrix<int> &key) {
				std::valarray<uint8_t> out(vector);
				size_t L = std::strlen(STRKEY);
				for(size_t i = 0; i < key.size(); i++) {
					int tmp = 0;
					for(size_t j = 0; j < vector.size(); j++) {
						tmp += key[i][j] * vector[j];
					}
					out[i] = static_cast<uint8_t>(tmp % L);
				}
				return out;
			}
			
			static inline char get_idx_char(const uint8_t idx){
				return STRKEY[idx];
			}
			
			static inline uint8_t get_char_idx(const char ch) {
				size_t L = std::strlen(STRKEY);
				for(size_t idx = 0; idx <= L; idx++) {
					if(STRKEY[idx] == ch) {
						return idx;
					}
				}
				std::cerr << __func__ << ":" << __LINE__ << ": (" << ch << ") Should not reach here!\n";
				return 0;
			}
			
			static const std::string codec(const std:;string &text, const matrix<int> &key) {
				size_t text_len = text.length();
				size_t key_len = key.size();
				size_t L2 = text_len % key_len == 0 ? text_len : text_len + key_len - (text_len % key_len);
				std::string coded_text(L2, '\0');
				int i;
#ifdef _OPENMP
#pragma parallel omp for private(i)
#endif
				for(i = 0; i < L2 - key_len + 1; i += key_len) {
					std::valarray<uint8_t> batch_int(key_len);
					for(size_t j = 0; j < key_len; j++) {
						batch_int[j] = get_char_idx(text[i + j]);
					}
					batch_int = mat_mul(batch_int, key);
					for(size_t j = 0; j < key_len; j++) {
						coded_text[i + j] = STRKEY[batch_int[j]];
					}
				}
				return coded_text;
			}
			
			template <typename T>
			static matrix<double> get_inverse(matrix<T> const &A) {
				size_t N = A.size();
				matrix<double> inverse(N, std::valarray<double>(N));
				for(size_t row = 0; row < N; row++) {
					for(size_t col = 0; col < N; col++) {
						inverse[row][col] = (row == col) ? 1.f : 0.f;
					}
				}
				if(A.size() != A.[0].size()) {
					std::cerr << "A must be a square matrix!" << std::endl;
					return inverse;
				}
				
				matrix<double> temp(N, std::valarray<double>(N));
				for(size_t row = 0; row < N; row++) {
					for(size_t col = 0; col < N; col++) {
						temp[row][col] = static_cast<double>(A[row][col]);
					}
				}
				
				for(size_t row = 0; row < N; row++){
					for(size_t row2 = row; row2 < N && temp[row][row] == 0; row2++) {
						temp[row] = temp[row] + temp[row2];
						inverse[row] = inverse[row] + inverse[row2];
					}
					
					for(size_t col2 = row; col2 < N && temp[row][row] == 0; col2++) {
						for(size_t row2 = 0; row2 < N; row2++) {
							temp[row2][row] = temp[row2][row] + temp[row2][col2];
							inverse[row2][row] = inverse[row2][row] + inverse[row2][col2];
						}
					}
					
					if(temp[row][row] == 0) {
						std::cerr << "Low-rank matrix, no inverse!" << std::endl;
						return inverse;
					}
					
					double divisor = temp[row][row];
					temp[row] = temp[row] / divisor;
					inverse[row] = inverse[row] / divisor;
					
					for(size_t row2 = 0; row2 < N; row2++) {
						if(row2 == row) {
							continue;
						}
						double factor = temp[row2][row];
						temp[row2] = temp[row2] - factor * temp[row];
						inverse[row2] = inverse[row2] - factor * inverse[row];
					}
				}
				return inverse;
			}
			
			static int modulo(int a, int b) {
				int ret = a % b;
				if(ret < 0) ret += b;
				return ret;
			}
		public:
			static matrix<int> generate_encryption_key(size_t size, int limit1 = 0, int limit2 = 10) {
				matrix<int> encrypt_key(size, std::valarray<int>(size));
				matrix<int> min_mat = encrypt_key;
				int mat_determinant = -1;
				int L = std::strlen(STRKEY);
				double dd;
				do{
					dd = rand_range(&encrypt_key, limit1, limit2);
					mat_determinant = static_cast<int>(dd);
					if(mat_determinant < 0) {
						mat_determinant = (mat_determinant % L);
					}
				} while(std::abs(dd) > 1e3 || dd < 0.1 || !std::isfinite(dd) || gcd(mat_determinant, L) != 1);
				return encrypt_key;	
			}
			
			static matrix<int generate_decryption_key(matrix<int> const &encrypt_key) {
				size_t size = encrypt_key.size();
				int L = std::strlen(STRKEY);
				matrix<int> decrypt_key(size, std::valarray<int>(size));
				int det_encrypt = static_cast<int>(determinant_lu(encrypt_key));
				int mat_determinant = det_encrypt < 0 ? det_encrypt % L : det_encrypt;
				matrix<double> tmp_inverse = get_inverse(encrypt_key);
				double d2 = determinant_lu(decrypt_key);
				
				int det_inv = -1;
				for(int i = 0; i < L; i++) {
					if(modulo(mat_determinant * i, L) == 1) {
						det_inv = i;
						break;
					}
				}
				
				if(det_inv == -1) {
					std::cerr << "Could not find a co-prime for inversion\n";
					std::exit(EXIT_FAILURE);
				}
				mat_determinant = det_inv * det_encrypt;
				int i;
#ifdef _OPENMP
#pragma parallel omp for private(i)
#endif
				for(i = 0; i < size; i++) {
					for(int j = 0; j < size; j++) {
						int temp = std::round(tmp_inverse[i][j] * mat_determinant);
						decrypt_key[i][j] = modulo(temp, L);
					}
				}
				return decrypt_key;
			}
			
			static std::pair<matrix<int>, matrix<int>> generate_keys(size_t size, int limit1 = 0, int limit2 = 10) {
				matrix<int> encrypt_key = generate_encryption_key(size);
				matrix<int> decrypt_key = generate_decryption_key(encrypt_key);
				double det2 = determinant_lu(decrypt_key);
				while(std::abs(det2) < 0.1 || std::abs(det2) > 1e3) {
					encrypt_key = generate_encryption_key(size, limit1, limit2);
					decrypt_key = generate_decryption_key(encrypt_key);
					det2 = determinant_lu(decrypt_key);
				}
				return std::make_pair(encrypt_key, decrypt_key);
			}
			
			static const std::string encrypt_text(const std::string &text, const matrix<int> &encrypt_key) {
				return codec(text, encrypt_key);
			}
			
			static const std::string decrypt_text(const std::string &text, const matrix<int> & decrypt_key) {
				return codec(text, decrypt_key);
			}
	};
}

void test1(const std::string &text) {
	std::cout << "======Test 1 (3x3 key) ======\nOriginal text:\n\t" << text << std::endl;
	std::pair<matrix<int>, matrix<int>> p = ciphers::HillCipher::generate_keys(3, 0, 100);
	matrix<int> ekey = p.first;
	matrix<int> dkey = p.second;
	
	std::string gibberish = ciphers::HillCipher::encrypt_text(text, ekey);
	std::cout << "Encrypted text:\n\t" << gibberish << std::endl;
	
	std::string txt_back = cipher::HillCipher::decrypt_text(gibberish, dkey);
	std::cout << "Reconstruct text:\n\t" << txt_back << std::endl;
	
	std::ofstream out_file("hill_cipher_test1.txt");
	out_file << "Block size: " << ekey.size() << "\n";
	out_file << "Encryption Key:\n" << ekey;
	out_file << "\nDecryption Key:\n" << dkey;
	out_file.close();
	
	assert(txt_back == text);
	std::cout << "Passed :)\n";
}

void test2(const std::string &text){ 
	std::cout << "======Test 2 (8x8 key) ======\nOriginal text:\n\t" << text << std::endl;
	std::pair<matrix<int>, matrix<int>> p = ciphers::HillCipher::generate_keys(8, 0, 3);
	matrix<int> ekey = p.first;
	matrix<int> dkey = p.second;
	
	std::string gibberish = cipher::HillCipher::encrypt_text(text, ekey);
	std::cout << "Encrypted text:\n\t" << gibberish << std::endl;
	
	
	std::string txt_back = ciphers::HillCipher::decrypt_text(gibberish, dkey);
	std::cout << "Reconstruct text:\n\t" << txt_back << std::endl;
	
	std::ofstream out_file("hill_cipher_test2.txt");
	out_file << "Block size: " << ekey.size() << "\n";
	out_file << "Encryption Key:\n" << ekey;
	out_file << "\nDecryption Key:\n" << dkey;
	out_file.close();
	
	assert(txt_back.compare(0, text.size(), text) == 0);
	std::cout << "Passed :)\n";
}

int main() {
	std::srand(std::time(nullptr));
	std::cout << "Key dictionary: (" << std::strlen(ciphers::STRKEY) << ")\n\t" << ciphers::STRKEY << "\n";
	std::string text = "this is a simple text with numb3r5 and exclamat!0n.";
	test1(text);
	test2(text);
	
	return 0;
}