#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class StudentLedger
{
public:
    class Student;

private:
    // private fields
    vector<Student> ledger;
    double average_grade;

public:
    // c-tor
    // StudentLedger();

    // public member functions/methods
    void addStudentToLedger(const Student &obj_inst);
    double calcAverageGrade();
    void printLedgerInfo();

    class Student
    {
    public:
        // c-tor
        Student(string first_name, string last_name, double student_grade);

        // copy c-tor
        Student(const Student &obj_inst);

        // assignment operator overload
        // Student &operator=(const Student &obj_inst);

        // public properties
        string first_name;
        string last_name;
        double student_grade;

        // public member functions/methods
        void printCurrStudInfo();
    };
};

void StudentLedger::addStudentToLedger(const Student &obj_inst)
{
    this->ledger.push_back(obj_inst);
}

// nested class definition/implementation
StudentLedger::Student::Student(string first_name, string last_name, double student_grade)
{
    this->first_name = first_name;
    this->last_name = last_name;
    this->student_grade = student_grade;
}

StudentLedger::Student::Student(const Student &obj_inst)
{
    this->first_name = obj_inst.first_name;
    this->last_name = obj_inst.last_name;
    this->student_grade = obj_inst.student_grade;
}

double StudentLedger::calcAverageGrade()
{
    double average_grade = 0;
    for (const Student &curr_student : this->ledger)
    {
        average_grade += curr_student.student_grade;
    }

    return average_grade / this->ledger.size();
}

void StudentLedger::printLedgerInfo()
{
    for (const Student &curr_stud : this->ledger)
    {
        std::cout << curr_stud.first_name << " " << curr_stud.last_name << " " << curr_stud.student_grade << std::endl;
    }
}

int main()
{
    int inputs_num;
    std::cin >> inputs_num;
    std::cin.ignore();

    if (inputs_num <= 0)
    {
        std::cout << "Invalid input" << std::endl;

        return 0;
    }

    StudentLedger *ptr_ledger = new StudentLedger();

    for (int i = 0; i < inputs_num; i++)
    {
        string first_name;
        string last_name;
        double curr_grade;

        std::cin >> first_name >> last_name >> curr_grade;

        StudentLedger::Student *ptr_student_inst =
            new StudentLedger::Student(first_name, last_name, curr_grade);

        ptr_ledger->addStudentToLedger(*ptr_student_inst);

        delete ptr_student_inst;
        ptr_student_inst = nullptr;
    }

    ptr_ledger->printLedgerInfo();
    const double av_grade = ptr_ledger->calcAverageGrade();
    std::cout << av_grade << std::endl;

    // removing pointers
    delete ptr_ledger;
    ptr_ledger = nullptr;

    return 0;
}