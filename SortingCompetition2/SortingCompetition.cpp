#include<iomanip>
#include <chrono>
#include <ctime>
#include "SortingCompetition.h"
#include<iostream>

//Constructor and Destructor
SortingCompetition::SortingCompetition(const string &inputFileName)
{
    setFileName(inputFileName);
   //initialize private data members
    words2 = NULL;
    //Don't need to initialize the vector???
    setDataSize = 0;
    wordCount = 0;
    inputSize = 0;
//    previousWordCount = 0;


}
//need destructor
SortingCompetition::~SortingCompetition(){
    //deletes dynamically allocated memory
    //**********//
}

//setters and getters

//Will close current ifstream member object incase still open
//and sets object to open new input specified
void SortingCompetition::setFileName(const string& inputFileName)
{
    fin.close();
    fin.open(inputFileName.c_str(), ios::in);
    if (!fin.good())
    {
        cerr << "file could not be opened" << endl;
    }
}
void SortingCompetition::setSetDataSize(int newSize){
    setDataSize = newSize;
}

int SortingCompetition::getSetDataSize(){
    return setDataSize;

}

//getter for storage containers
vector<char*> SortingCompetition::getWords(void){
   return words;
}

char** SortingCompetition::getWords2(void){
    return words2;
}

void SortingCompetition::setWords2(char** newWords2){
    words2 = newWords2;
}

void SortingCompetition::setWordCount(int count){
    wordCount = count;

}

int SortingCompetition::getWordCount(void){
    return wordRandCount;
}

void SortingCompetition::setWordRandCount(int count){
    wordRandCount = count;
}

/*
void SortingCompetition::setPreviousWordCount(int count){
    previousWordCount = count;
}

int SortingCompetition::getPreviousWordCount(void){
    return previousWordCount;
}
*/

/* function will process all words in input file and put them
 * sequentially in a vector in the order they were in in the input file
 * */

bool SortingCompetition::readData(){
    //free memory from older copy of data
    for(size_t i = 0; i < words.size(); i++)
    {
        delete[] words2[i];
    }
    delete[] words2;

/*   //store off the size of the previous wordCount
    setPreviousWordCount(words.size());*/

    //clear all existing words in the vector in order that
    //if readData run multiple times that words are not just concatenated
    //onto the end of the existed vector from a previous run
    for (size_t i = 0; i < words.size(); i++)
    {
        delete[] words.at(i);
    }
    words.clear();


    //collect and store words from input file
    string buffer;
    while(!fin.eof())
    {
        fin >> buffer;
        //store pointer to a dynamically allocated
        //char* at end of vector
        words.push_back(new char[buffer.length()+1]);
        //copy word into chra* pointer
        strcpy(words.at(words.size()-1),buffer.c_str());
    }
    setWordCount(words.size());

    //close input file
    fin.close();
    //function complete so return true as success
    return true;
}

//function copies values stored in the vector into an array of char*
//The char* are length prefixed in order to eliminate the need
//to used strlen when sorting. The copy of the words list is first
//cleared to prevent any overlap from one run to the next
bool SortingCompetition::prepareData(){

    bool x = false;


    //copy data from original data structure over
    /* Loop first finds the length of the word, and then
     * creates length prefixed strings
     * */

    //create initialized char** that will hold the copied data
    //words2 = new char*[10];
    //initialize elements of words2
/*    for(int k = 0;k<10;k++){
        words2[k] = NULL;
    }
*/
    //counter to help with resizing
//    int count = 0;

    words2 = new char*[words.size()];

    for(size_t i = 0; i < wordsRand.size(); i++)
    {
        //determine length of string and store as character
        char length = strlen(wordsRand.at(i));
        //store the length of the string as an ascii character

        //need new string with 2 elements longer than length of word
        //for null termination and the length prefix
        char* newString = new char[length+2];
        //store length of word as fist character as char
        newString[0] = length;
        //add prefix to beginning of word
        strcpy(&(newString[1]),wordsRand[i]);
        /*char* dummy = newString;
        cout<<newString<<endl;
        cout<<newString[0]<<endl;
        cout<<"length of string "<<strlen(newString)<<endl;
        cout<<&(newString[1])<<endl;*/
        //add new length prefixed string to end of words2
        words2[i] = newString;
/*
        count++;
        //resize if list is full
        if(count>=10){
            resize(i);
            count = 0;
        }
*/
    }

    //if no errors occured return true
    x = true;

    return x;
}

/* function resizes the dynamically created copy of the words
 * list */

/*
void SortingCompetition::resize(int currentSize){
   //dynammically create new list for words2
    char** tempWords2 = new char*[currentSize+1+10];

    //cycle through and copy the old pointers to new list

    for(int i = 0;i<getWordCount();i++){
      tempWords2[i] = words2[i];
    }

    //initialize the additional spaces of longer list
    for(int j = getWordCount();j<getWordCount()+10;j++){
        tempWords2[j] = NULL;
    }

    //free memory from old list
    delete[] words2;

    //reassign lists to temporary list created
    words2 = tempWords2;

}
*/

/*
bool SortingCompetition::prepareData()
{
    bool x = false;


    for(size_t i = 0; i < words2.size(); i++)
    {
        delete[] words2.at(i);
    }
    words2.clear();

    //copy data from original data structure over
    for(size_t i = 0; i < words.size(); i++)
    {
        words2.push_back(new char[strlen(words.at(i))+1]);
        strcpy(words2.at(i), words.at(i));
    }
    x = true;

    return x;
}
*/
void SortingCompetition::sortData()
{
    //bubbleSort();
    mergeSort(0,getWordCount()-1);
}

void SortingCompetition::outputData(const string& outputFileName)
{
    //output sorted data (in words2)
    fout.open(outputFileName.c_str(), ios::out);
    if(!fout.good())
    {
        cerr << "file could not be opened" << endl;
    }

    for(size_t i = 0; i < wordCount; i++)
    {
        fout << &(words2[i][1])<<endl;
    }
    fout.close();

}

//PRIVATE FUNCTIONS IMPLEMENTATION

int SortingCompetition::compareWords(char* str1, char* str2)
{
    //char dummy1 = str1[0];
    //char dummy2 = str2[0];
    //cout<<dummy1<<" "<<dummy2<<endl;
    //cout<<(str1[0] > str2[0]?"True greater":"False less than")<<endl;


    if (str1[0] > str2[0])
    {
        return 1;
    }

    else if(str1[0] < str2[0])
    {
        return -1;
    }
    else
    {
        return strcmp(&(str1[1]), &(str2[1]));
    }
    return 0;
}

/*void quicksort(vector<char*>& wordArr, size_t start, size_t end)
{

}*/

void SortingCompetition::bubbleSort(){
    for(int j = 0; j<getWordCount();j++){
        for(int y = 0;y<(getWordCount()-1);y++){
            if (compareWords(words2[y],words2[y+1])== 1){
                char* temp1 =words2[y+1];
                words2[y+1]=words2[y];
                words2[y] = temp1;

            }
        }

    }
}
void SortingCompetition::merge(int low, int middle, int high){

    char** temp = new char*[high+1];

    int kk;
    int leftCounter = low;
    int rightCounter = middle+1;
    int tempCounter = low;

    //put values into temporary array where comparing values in right and left
    //array and then populating temporary array according to lowest value
    while((leftCounter<=middle)&&(rightCounter<=high)){
        //would need overloaded compare
        if(compareWords(words2[leftCounter],words2[rightCounter])!=1){
           temp[tempCounter] = words2[leftCounter];
           leftCounter++;
        }
        else{
            temp[tempCounter] = words2[rightCounter];
            rightCounter++;
        }
        tempCounter++;
    }
    //fill rest of array with remainder of values from left or right array
    //that has not been fully iterated through yet
    if(leftCounter>middle){
       for(kk = rightCounter;kk<=high;kk++){
           temp[tempCounter] = words2[kk];
           tempCounter++;
       }
    }

    else{
        for(kk=leftCounter;kk<=middle;kk++){
            temp[tempCounter] = words2[kk];
            tempCounter++;
        }
    }

    //reassign passed array to the now ordered elements in temp
    for(int m = low;m<=high;m++){
        words2[m] = temp[m];
    }

    //free memory
    delete[] temp;

}

void SortingCompetition::mergeSort(int left, int right){
    int middle;

    if(left<right){
        middle = (left+right)/2;
        //continuatlly divides left side of A into smaller partitions
        mergeSort(left,middle);

        //continuatlly divides right side of A into smaller partitions
        mergeSort(middle+1,right);

        merge(left,middle,right);


    }
}

void SortingCompetition::algorithmTester(void){

   int A = 1;
   int stepSize = 10000;

   int max = 10001;
   //number of sorting methods implemented
   int sortingCount = 1;
   //setting number of words in RandomInput.txt
   this->inputSize = A*stepSize;

   //output header to file for output
   ofstream output("SortingAnalysis.txt");
   output<<"N,";
   for(int y = 0;y<sortingCount;y++){
       switch(y){
        case 0:
           output<<"Bubble Sort,";
        case 1:
           output<<"Merge Sort,";
       }
   }
   output<<endl;
   //close output file temporarily while make the randomInput file
   output.close();

   while(A*stepSize<max){
       //function call to make random input file from the words collected from input.txt
       makeRandomFile(A*stepSize,"RandomInput.txt");
       //processing now done on
       setFileName("RandomInput.txt");

       //prepare words2 with RandomInput file instead
       readRandomData(stepSize);
       prepareData();

       //re-open output file and append to the end
       output.open("SortingAnalysis.txt",std::ios_base::app);

       //output input size to output file
       cout<<A*stepSize<<", ";

       //find average of all sorting methods for this specific
       //input size
       for(int i = 0;i<sortingCount;i++){
           double sumRuntime = 0;
           for(int j = 0;j<30;j++){

                //declare 2 time points
                std::chrono::time_point<std::chrono::system_clock> start, end;

                //store current time (now()) in start
                start = std::chrono::system_clock::now();

                //decide which sorting method to use
               switch(i){
                case 0:
                    bubbleSort();
                case 1:
                    mergeSort(0,getWordCount()-1);
               }

                //store time(now()) in end
                end = std::chrono::system_clock::now();

                //get No. of seconds elapsed & output duration
                //need to do this multiple times & get average
                std::chrono::duration<double> elapsed_seconds = end-start;

                sumRuntime += elapsed_seconds.count();
           }//end of 30 runtimes

           //find average runtime
           double average = sumRuntime/30;

           //output to file the average run time and size
           cout<<fixed<<setprecision(9)<<average<<", ";

       }//processed all sorting algorithms

       //increment input size
       A +=1;

       this->inputSize = A*stepSize;

       cout<<endl;

   }

}
//making random file filled with specified length by pulling form
//the list of words collected from input.txt
void SortingCompetition::makeRandomFile(int size,char* name){
    //seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    //open input file
    ofstream randomFile(name);
    int dummy = getWordCount();
    //populating input file with random words form base input.txt file
    for(int i = 0;i<size;i++){

       int index = rand()%(words.size());
       char* dummyWord = words.at(index);
       //write random word tou randomFile file

       randomFile<<words.at(index)<<" ";

    }

    //close file
    randomFile.close();

}

//will read in words from input file
void SortingCompetition::readRandomData(int stepSize){
    //free memory from older copy of data
    for(size_t i = 0; i < (inputSize - stepSize); i++)
    {
        delete[] words2[i];
    }
    delete[] words2;

/*   //store off the size of the previous wordCount
    setPreviousWordCount(words.size());*/

    //clear all existing words in the vector in order that
    //if readData run multiple times that words are not just concatenated
    //onto the end of the existed vector from a previous run


    for (size_t i = 0; i < wordsRand.size(); i++)
    {
        delete[] wordsRand.at(i);
    }
    wordsRand.clear();


    //collect and store words from input file
    string buffer;
    for(int i = 0;i<inputSize;i++)
    {
        fin >> buffer;
        //store pointer to a dynamically allocated
        //char* at end of vector
        wordsRand.push_back(new char[buffer.length()+1]);
        //copy word into chra* pointer
        strcpy(wordsRand.at(wordsRand.size()-1),buffer.c_str());
    }
    setWordRandCount(wordsRand.size());

    //close input file
    fin.close();
}
