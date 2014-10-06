#include <iostream>
#include<string.h>
using namespace std;

int main()
{
    char myWord[] = "Hey Dawg";
    int length = strlen(myWord);
    char  number = 99;
    cout<<"length = "<<length<<" char = "<<number<<endl;

    char* newString = new char[length+1];
    newString[0] = number;

    strcpy(&(newString[1]),myWord);

    cout<<newString<<endl;
    char number2 = 124;
    cout<<number2<<endl;

}

