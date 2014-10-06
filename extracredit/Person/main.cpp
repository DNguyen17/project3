#include <iostream>
#include <person.h>
#include <ctime>
#include <chrono>
#include <climits>

using namespace std;

void passValue(Person p)
{
    int x = p.getAge();
    int y = x + 4;
}

void passRef(Person& p)
{
    int x = p.getAge();
    int y = x + 4;
}


int main()
{
    Person one("Brendan","Dan","Bobby", 20);
//    for(int Dan = 0; Dan <20;Dan++){


    for(int i = 0;i<2;i++){

        double sumRuntime = 0;
        for(int j = 0;j<30;j++){

            //declare 2 time points
            std::chrono::time_point<std::chrono::system_clock> start, end;

            //store time (now()) in start
            start = std::chrono::system_clock::now();

            for(int j = 0;j<150000000;j++)
            {
                if( i == 0)
                {
                    passValue(one);
                }
                else
                {
                     passRef(one);
                }

            }
                //store time(now()) in end
                end = std::chrono::system_clock::now();

                //get No. of seconds elapsed & output duration
                //need to do this multiple times & get average
                std::chrono::duration<double> elapsed_seconds = end-start;
                std::time_t end_time = std::chrono::system_clock::to_time_t(end);

                cout<<"Method used was "<<(i==0?"Passed By Value":"Passsed By Reference")<<endl;
                cout << "finished computation at " << std::ctime(&end_time)
                     << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

                sumRuntime += elapsed_seconds.count();
        }


        //find average runtime
        double average = sumRuntime/30;

        //output to file the average run time and size
        cout<<fixed<<setprecision(9)<<average<<", ";


        cout<<"Method used was "<<(i==0?"Passed By Value":"Passsed By Reference")<<endl;
        cout << "finished computation at " << std::ctime(&end_time)
             << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    }


    return 0;
}



