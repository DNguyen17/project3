#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <omp.h>
using namespace std;

class SortingCompetition
{
private:
    //private data members
    ifstream fin;
    ofstream fout;
    int setDataSize; //for switching algorithms based on size
    vector<char*> words;
    vector<char*> wordsRand;

    char** words2;
    int wordCount;
    int inputSize;
    int wordRandCount;
    int passOff;

    //private functions
        //setter,getters
    void  setSetDataSize(int newSize);
    int getSetDataSize();
    vector<char*>  getWords(void);
    char**  getWords2(void);
    void  setWords2(char** newWords2);
    void  setWordCount(int count);
    int  getWordCount(void);
    int compareWords(char* one, char* str2);

    //sorting functions
    void bubbleSort(void);
    void quicksort(vector<char*>& wordArr, size_t start, size_t end);
    void merge(int low, int middle, int high);
    void mergeSort(int left, int right);
    void bcQuickSort(int start,int end);
    void quicksort(char**& wordArr, int start, int end);
    void insertion_sort(int start,int end);
    void quicksort2WithInsert(int start, int end);
    void quicksort2(int start, int end);
    void multisort(int start, int end);

    //tester functions
    void makeRandomFile(int size,char* name,unsigned int);
    void setWordRandCount(int);
    void readRandomData(int);

public:
    SortingCompetition(const string& inputFileName);
    ~SortingCompetition();
    void setFileName(const string& inputFileName);
    bool readData();
    bool prepareData();
    void sortData();
    void outputData(const string& outputFileName);
    void algorithmTester(void);
};


#endif // SORTINGCOMPETITION_H
