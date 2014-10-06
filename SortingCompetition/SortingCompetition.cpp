#include "SortingCompetition.h"
#include <algorithm>
#include <ctime>

//Constructor and Destructor
SortingCompetition::SortingCompetition(const string &inputFileName){
    setFileName(inputFileName);
   //initialize private data members
    words2 = NULL;
    //Don't need to initialize the vector???
    setDataSize = 0;
    wordCount = 0;
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
void SortingCompetition::setFileName(const string& inputFileName){
    fin.close();
    fin.open(inputFileName.c_str(), ios::in);
    if (!fin.good()){
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
    return wordCount;
}


/* function will process all words in input file and put them
 * sequentially in a vector in the order they were in in the input file
 * */

bool SortingCompetition::readData(){
    //clear contents of words2
    for(int i = 0; i < getWordCount(); i++){
        delete[] words2[i];
    }
    delete[] words2;

/*   //store off the size of the previous wordCount
    setPreviousWordCount(words.size());*/

    //clear all existing words in the vector in order that
    //if readData run multiple times that words are not just concatenated
    //onto the end of the existed vector from a previous run
    for (size_t i = 0; i < words.size(); i++){
        delete[] words.at(i);
    }
    words.clear();


    //collect and store words from input file
    string buffer;
    while(!fin.eof()){
        fin >> buffer;
        //store pointer to a dynamically allocated
        //char* at end of vector
        words.push_back(new char[buffer.length()+1]);
        //copy word into char* pointer
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


    words2 = new char*[words.size()];

    for(size_t i = 0; i < words.size(); i++){
        //determine length of string and store as character
        char length = strlen(words.at(i));
        //store the length of the string as an ascii character

        //need new string with 2 elements longer than length of word
        //for null termination and the length prefix
        char* newString = new char[length+2];
        //store length of word as fist character as char
        newString[0] = length;
        //add prefix to beginning of word
        strcpy(&(newString[1]),words[i]);

        //add new length prefixed string to end of words2
        words2[i] = newString;

    }

    //if no errors occured return true
    x = true;

    return x;
}

void SortingCompetition::sortData(){
    //bubbleSort();
    //mergeSort(0,getWordCount()-1);
    //std::sort(words.begin(), words.end());
    quicksort(words2, 0, getWordCount()-1);
}

void SortingCompetition::outputData(const string& outputFileName){
    //output sorted data (in words2)
    fout.open(outputFileName.c_str(), ios::out);
    if(!fout.good()){
        cerr << "file could not be opened" << endl;
    }

    for(int i = 0; i < wordCount; i++){
        fout << &(words2[i][1])<<endl;
    }
    fout.close();

}

//PRIVATE FUNCTIONS IMPLEMENTATION

int SortingCompetition::compareWords(char* str1, char* str2){
    //char dummy1 = str1[0];
    //char dummy2 = str2[0];
    //cout<<dummy1<<" "<<dummy2<<endl;
    //cout<<(str1[0] > str2[0]?"True greater":"False less than")<<endl;


    if (str1[0] > str2[0]){
        return 1;
    }

    else if(str1[0] < str2[0]){
        return -1;
    }
    else{
        return strcmp(&(str1[1]), &(str2[1]));
    }
    return 0;
}

//Quicksort from http://www.algolist.net/Algorithms/Sorting/Quicksort
void SortingCompetition::quicksort(char**& wordArr, int start, int end){

    int med = (start+end)/2;
    //srand(time(0));
    //int med = rand()%(getWordCount()-1);
    char* pivot = new char[wordArr[med][0]+1];
    strcpy(pivot,wordArr[med]);

    int i = start;
    int j = end;
    char* temp;
    while(i <= j){
        while(compareWords(wordArr[i],pivot) <= -1){
            i++;
        }

        while(compareWords(wordArr[j],pivot) >= 1){
            j--;
        }

        if (i <= j){
            temp = wordArr[i];
            wordArr[i] = wordArr[j];
            wordArr[j] = temp;
            i++;
            j--;
        }

    }

    //recursion
    if(start < j){
        quicksort(wordArr, start, j);
    }

    if(i < end){
        quicksort(wordArr, i, end);
    }
}

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

void SortingCompetition::algorithmTester(void){/*
   int A = 1;
   int stepSize = 1;
   int max = 10;
   int sortingCount = 2;
   while(A*stepSize<max){
       makeRandomFile(A*stepSize,"RandomInput.txt");
       for(int i = 0;i<sortingCount;i++){
           int sumRuntime = 0;
           for(int j = 0;j<30;j++){

                //declare 2 time points
                std::chrono::time_point<std::chrono::system_clock> start, end;

                //store current time (now()) in start
                start = std::chrono::system_clock::now();

                //decide which sorting method to use
                switch(i){
                    case 0:
                        //bubbleSort(1)
                }

                //store time(now()) in end
                end = std::chrono::system_clock::now();

                //get No. of seconds elapsed & output duration
                //need to do this multiple times & get average
                std::chrono::duration<double> elapsed_seconds = end-start;
                std::time_t end_time = std::chrono::system_clock::to_time_t(end);

                std::time_t elapsed = elapsed_seconds.count();
           }
       }

   }

*/}

void SortingCompetition::makingRandomFile(int size,char* name){

}
