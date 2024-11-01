// đây là một chương trình mã hóa và giải mã chuỗi văn bản sử dụng thuật toán XOR
//đoạn mã này gồm hai hàm encrypt và decrypt nằm trong namespace(không gian tên) sử dụng các phép toán XOR giữa các ký tự trong chuỗi đầu vào và một khóa (key) để mã hóa và giải mã văn bản
#include <iostream>
#include <string>
#include <cassert>
//vì phép toán XOR này chỉ đơn giản là phép toán giữa mỗi ký tự và key nên phương pháp này rất dễ cài đặt nhanh chóng
//đi kèm với sự tiện lợi về cài đặt đó là sự không an toàn cho các ứng dụng yêu cầu bảo mật cao, vì một khóa ngắn và đơn giản có thể dễ dàng bị bẻ khóa.
namespace ciphers{
	namespace XOR{
		//hàm này lặp qua duyệt từng ký tự c trong chuỗi text thực hiện phép toán XOR giữa ký tự c và key sau đó chuyển về kiểu char
		//sau khi đã mã hóa thì thêm ký tự đã mã hóa vào encrypted_text và trả về chuỗi đã mã hóa.
		std::string encrypt (const std::string &text, const int &key) {
			std::string encrypted_text = "";
			for(auto &c : text) {
				char encrypted_char = char(c ^ key);
				encrypted_text += encrypted_char;
			}
			return encrypted_text;
		}
		//hàm decrypt thực hiện các bước tương tự như mã hóa nhưng thay vì mã hóa nó dùng XOR để giải mã vì phép toán XOR nghịch đảo chính nó sử dụng cùng một khóa key để XOR nó lại một lần nữa sẽ trả lại bản rõ
		//vòng lặp duyệt qua từng ký tự c trong chuỗi mã hóa text thực hiện XOR giữa ký tự đã mã hóa và key, lấy lại ký tự ban đầu
		//thêm ký tự đã giải mã vào decrypted_text và trả về chuỗi bản rõ.
		std::string decrypt (const std::string &text, const int &key) {
			std::string decrypted_text = "";
			for(auto &c : text) {
				char decrypted_char = char(c ^ key);
				decrypted_text += decrypted_char;
			}
			return decrypted_text;
		}
	}
}
//test thuật toán
void test() {
	//test 1
	std::string text1 = "Whipalsh! : Do watch this movie...";
	std::string encrypted1 = ciphers::XOR::encrypt(text1, 17);
	std::string decrypted1 = ciphers::XOR::decrypt(encrypted1, 17);
	assert(text1 == decrypted1);
	
	std::cout << "Original text: " << text1;
	std::cout << " , Encrypted text (with key = 17): " << encrypted1;
	std::cout << " , Decrypted text: " << decrypted1 << std::endl;
	
	//test 2
	std::string text2 = "->Valar M0rghulis<-";
	std::string encrypted2 = ciphers::XOR::encrypt(text2, 29);
	std::string decrypted2 = ciphers::XOR::decrypt(encrypted2, 29);
	assert(text2 == decrypted2);
	
	std::cout << "Original text: " << text2;
	std::cout << " , Encrypted text (with key = 29): " << encrypted2;
	std::cout << " , Decrypted text: " << decrypted2 << std::endl;
}

int main() {
	test();
	return 0;
}
