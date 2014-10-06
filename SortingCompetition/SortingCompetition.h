#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

class SortingCompetition
{
private:
    //private data members
    ifstream fin;
    ofstream fout;
    int setDataSize; //for switching algorithms based on size
    vector<char*> words;
    char** words2;
    int wordCount;

    //setter,getters
    void  setSetDataSize(int newSize);
    int getSetDataSize();
    vector<char*>  getWords(void);
    char**  getWords2(void);
    void  setWords2(char** newWords2);
    void  setWordCount(int count);
    int  getWordCount(void);


    //helper functions
    int compareWords(char* one, char* str2);

    //sorting functions
    void bubbleSort(void);
    void quicksort(char**& wordArr, int start, int end);
    void merge(int low, int middle, int high);
    void mergeSort(int left, int right);


public:
    SortingCompetition(const string& inputFileName);
    ~SortingCompetition();
    void setFileName(const string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void outputData(const string& outputFileName);
};


#endif // SORTINGCOMPETITION_H
