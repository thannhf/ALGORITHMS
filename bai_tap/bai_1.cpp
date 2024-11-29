// Xây dựng chương trình quản lý điểm học sinh:
//  Các lớp cần có: các lớp Person, Student, Teacher, 
// Subject, BKClass
//  Xây dựng mô hình kiến trúc của bài toán thoả mãn các
// yêu cầu sau:
//  Nhập được các thông số của học sinh, giáo viên dạy các
// môn học và điểm cho các môn
//  Nhập danh sách một lớp BKclass theo quy đinh có 40 
// sinh viên
//  Thực hiện chương trình và vẽ sơ đồ mô tả kiến trúc của
// lớp: quan hệ kết tập, quan hệ kế thừa, v.v.
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Person {
protected:
    std::string name;
    int age;

public:
    Person(std::string name, int age) : name(name), age(age) {}
    virtual ~Person() {}

    std::string getName() const { return name; }
    int getAge() const { return age; }
};

class Student : public Person {
private:
    std::map<std::string, float> grades; 

public:
    Student(std::string name, int age) : Person(name, age) {}

    void setGrade(const std::string& subject, float grade) {
        grades[subject] = grade;
    }

    float getGrade(const std::string& subject) const {
        if (grades.find(subject) != grades.end()) {
            return grades.at(subject);
        }
        return -1; 
    }
};

class Teacher : public Person {
private:
    std::string subject;

public:
    Teacher(std::string name, int age, std::string subject) : Person(name, age), subject(subject) {}
    std::string getSubject() const { 
        return subject; 
    }
};

class Subject {
private:
    std::string name;
    Teacher* teacher;

public:
    Subject(std::string name, Teacher* teacher) : name(name), teacher(teacher) {}

    std::string getName() const { return name; }
    Teacher* getTeacher() const { return teacher; }
};

class BKClass {
private:
    std::vector<Student> students;
    std::vector<Subject> subjects;

public:
    BKClass() {}

    void addStudent(const Student& student) {
        if (students.size() < 40) {
            students.push_back(student);
        }
    }

    void addSubject(const Subject& subject) {
        subjects.push_back(subject);
    }

    void printClassInfo() const {
        std::cout << "Class Information:\n";
        for (const auto& student : students) {
            std::cout << "Student: " << student.getName() << ", Age: " << student.getAge() << "\n";
        }
        std::cout << "\nSubjects:\n";
        for (const auto& subject : subjects) {
            std::cout << "Subject: " << subject.getName() 
                      << ", Teacher: " << subject.getTeacher()->getName() << "\n";
        }
    }
};

int main() {
    // Tạo giáo viên
    Teacher teacher1("Mr. A", 35, "Math");
    Teacher teacher2("Ms. B", 40, "Physics");

    // Tạo môn học với giáo viên phụ trách
    Subject math("Math", &teacher1);
    Subject physics("Physics", &teacher2);

    // Tạo lớp học và thêm môn học
    BKClass bkclass;
    bkclass.addSubject(math);
    bkclass.addSubject(physics);

    // Thêm 40 học sinh và đặt điểm
    for (int i = 0; i < 40; i++) {
        Student student("Student" + std::to_string(i + 1), 18);
        student.setGrade("Math", 8.5 + i * 0.1);  // Điểm ví dụ
        student.setGrade("Physics", 7.5 + i * 0.1);
        bkclass.addStudent(student);
    }

    // In thông tin lớp học
    bkclass.printClassInfo();
    return 0;
}