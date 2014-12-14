#include <iostream>
#include <conio.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

class Calendar {
public:
        unsigned int day;
        unsigned int month;
        unsigned int year;
        Calendar(const unsigned int d = 0,const unsigned int m = 0,const unsigned int y = 0):day(d), month(m), year(y) {
        }

        Calendar(const Calendar& d) {
                day = d.day;
                month = d.month;
                year = d.year;
        }
        ~Calendar(){
        //cout<< "Destructor!" << endl;
        }
        int operator==(const Calendar& d) {
                return day == d.day && month == d.month && year == d.year;
        }

        Calendar& operator=(const Calendar& d) {
                if(this != &d) {
                        day = d.day;
                        month = d.month;
                        year = d.year;
                }
                return *this;
        }

        virtual unsigned int getDay() {
                return day;
        }
        virtual void setDay(const unsigned int d) {
                day = d;
        }
        virtual unsigned int getMonth() {
                return month;
        }
        virtual void setMonth(const unsigned int m) {
                month = m;
        }
        virtual unsigned int getYear() {
                return year;
        }
        virtual void setYear(const unsigned int y) {
                year = y;
        }
};
class Student : public Calendar{
public:
    string name;
    string facNumber;
    float avScore;
    int potok;
    unsigned int day;
    unsigned int month;
    unsigned int year;
    int age;
public:
    Student(string, string, int, int, int, float, int, int);
    Student();
    ~Student(){
        //cout<<"\nDestructing object!\n";
    }
    void setName(string n){name = n;}
    string getName(){return name;}

    void setFacNumber(string id){facNumber = id;}
    string getFacNumber(){return facNumber;}

    void setAvScore(float s){avScore = s;}
    float getAvScore(){return avScore;}

    void setPotok(int p){potok = p;}
    int getPotok(){return potok;}

    virtual unsigned int getDay() {
            return day;
    }
    virtual void setDay(const unsigned int d) {
            day = d;
    }
    virtual unsigned int getMonth() {
            return month;
    }
    virtual void setMonth(const unsigned int m) {
            month = m;
    }
    virtual unsigned int getYear() {
            return year;
    }
    virtual void setYear(const unsigned int y) {
            year = y;
    }


    int setCurrentAge(int year, int month, int date) {
        time_t t = time(0);
        struct tm * now = localtime( & t );

        int ny = now->tm_year;
        int nm = now->tm_mon+1;
        int nd = now->tm_mday;
        int a;
        int ye = getYear();
        int mo = getMonth();
        int da = getDay();

        if (nm > mo){
            a = ny - ye;
            //cout<< "1 if";
            age = a;
            }
        else if(nm == mo && nd < da){
            a = ny - ye - 1;
            //cout<< "2 if";
            age = a;
        }
        else if (nm < mo){
            a = ny - ye - 1;
            //cout<< "3 if";
            age = a;
        }
        else {
            a = ny - ye;
            cout<< "else";
            age = a;
        }
    }
    int getCurrentAge(){
        return age;
    }
    void show(){
    cout<< getName() << " " << getFacNumber() << " " << getDay() <<"/"<< getMonth() << "/" << getYear() << " " << getCurrentAge() << " " << getAvScore() << " " << getPotok()<<endl;
    }
    friend ostream& operator << (ostream& os, const Student& student)
    {
            os << "Name: "<< student.name << "  Fac. Number:  "<< student.facNumber
            << "  Student's age:  " << student.age << " Student's average grade score: "
            << student.avScore << "Student's group: " << student.potok <<endl;
            return os;
    }
};

bool sortByPotok(const Student &lhs, const Student &rhs) { return lhs.potok < rhs.potok; }

Student::Student(){}
//string n, string id, int d, int m, int y, float s, int p): name(n), facNumber(id), day(d), month(m), year(y) ,avScore(s), potok(p){}

int main(){
    string n;
    string id;
    int d;
    int m;
    int y;
    float s;
    int p;
    int unsigned numberOfPeople;
    int gr;
    float sum = 0;
    float result;
    int counter = 0;
//    Student s1("Ivan", "121212115", 12, 04, 93, 5.254, 5);
//    s1.show();
//    Student s2("Elena", "121212185",12, 05, 94, 4.454, 5);
//    s2.show();
//    time_t t = time(0);   // get time now
//    struct tm * now = localtime( & t );
    ofstream fout;
    fout.open("Students.txt",ios::app);

    cout << "Welcome to the student system!\n" << endl;
    cout << "-------------------------------------" << endl;
    cout << "| How many students will be entered? |" << endl;
    cout << "-------------------------------------\n" << endl;
    cin>> numberOfPeople;
    vector<Student> student(numberOfPeople);
    for (vector<Student>::size_type i = 0; i != numberOfPeople; ++i)
    {
        cout << "Student #" << i + 1 << "Enter name: \t";
        cin >> n;
        student[i].setName(n);

        cout << "Student #" << i + 1 << "Enter faculty number: \t";
        cin >> id;
        student[i].setFacNumber(id);

        cout << "Student #" << i + 1 << "Enter day of birth: \t";
        cin >> d;
        student[i].setDay(d);

        cout << "Student #" << i + 1 << "Enter month of birth: \t";
        cin >> m;
        student[i].setMonth(m);

        cout << "Student #" << i + 1 << "Enter year of birth: \t";
        cin >> y;
        student[i].setYear(y);

        cout << "Student #" << i + 1 << "Enter average grade score: \t";
        cin >> s;
        student[i].setAvScore(s);

        cout << "Student #" << i + 1 << "Enter the group of the student: \t";
        cin >> p;
        student[i].setPotok(p);
        student[i].setCurrentAge(y, m, d);
        student[i].show();
    }

    sort(student.begin(), student.end(), sortByPotok);
    cout<< "Enter the group you want to know the average grade score: ";
    cin >> gr;

    for (Student &n : student){
        int ager = n.age;
            if ((ager > 17 && ager < 27)&& (n.potok == gr)) {
                fout << n;
        }
    }
        fout.close();
    for (Student &n : student)
        if (n.potok == gr) {
                sum += n.avScore;
                counter += 1;
            }
    result = sum / counter;
    cout<< "The average grade score of the group is: " << result<< endl;

    return 0;
}

