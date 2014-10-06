#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;
class Person
{
private:
    string name;
    string name2;
    string name3;
    int age;

public:
    //constructor with 4 data members
    Person(string name,string name2, string name3, int age)
    {
        this->name2 = name2;
        this->name3 = name3;
        this-> name = name;
        this-> age = age;
    }
    string getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setAge(int age)
    {
        this->age = age;
    }

};

#endif // PERSON_H
