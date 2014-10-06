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
    vector<char*> wordsRand;

    char** words2;
//    int previousWordCount;
    int wordCount;
    int inputSize;
    int wordRandCount;


    //vector<char*> words2;

    //private functions
        //setter,getters
    void  setSetDataSize(int newSize);
    int getSetDataSize();
    vector<char*>  getWords(void);
    char**  getWords2(void);
    void  setWords2(char** newWords2);
    void  setWordCount(int count);
    int  getWordCount(void);
//    void  setPreviousWordCount(int count);
//    int  getPreviousWordCount(void);

    //helper functions
//    void  resize(int currentSize);
    int compareWords(char* one, char* str2);

    //sorting functions
    void bubbleSort(void);
    void quicksort(vector<char*>& wordArr, size_t start, size_t end);

    void merge(int low, int middle, int high);
    void mergeSort(int left, int right);

    //tester functions
    void makeRandomFile(int size,char* name);
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
