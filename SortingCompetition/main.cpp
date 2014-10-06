//Danh Nguyen
//Brendan Celii

#include <iostream>
#include <chrono>
#include <ctime>
#include "SortingCompetition.h"

using namespace std;

int main()
{
    SortingCompetition sorter("input2.txt");
    //store data from input file
    sorter.readData();
    //prepare copy of data to be sorted
    sorter.prepareData();
    //algorithmTester();
    //declare 2 time points
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //store current time (now()) in start
    start = std::chrono::system_clock::now();

    //execute sort on copy of data
    sorter.sortData();

    //store time(now()) in end
    end = std::chrono::system_clock::now();

    //get No. of seconds elapsed & output duration
    //need to do this multiple times & get average
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    cout << "finished computation at " << std::ctime(&end_time)
         << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    //output sorted data to output file
    sorter.outputData("output.txt");
    return 0;
}
