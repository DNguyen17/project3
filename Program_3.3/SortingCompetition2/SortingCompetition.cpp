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
    passOff = 0;

}
//need destructor
SortingCompetition::~SortingCompetition(){
    //deletes dynamically allocated memory
    //**********//

    for(size_t i = 0; i < (wordsRand.size()); i++)
    {
        delete[] words2[i];
    }
    delete[] words2;

/*   //store off the size of the previous wordCount
    setPreviousWordCount(words.size());*/

    //clear all existing words in the vector in order that
    //if readData run multiple times that words are not just concatenated
    //onto the end of the existed vector from a pr

    for (size_t i = 0; i < wordsRand.size(); i++)
    {
        delete[] wordsRand.at(i);
    }
    wordsRand.clear();
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
    //delete[] words2;

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

    words2 = new char*[wordsRand.size()];

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

void SortingCompetition::sortData()
{
    //bubbleSort();
    mergeSort(0,wordsRand.size()-1);
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
    for(int j = 0; j<wordsRand.size();j++){
        for(int y = 0;y<(wordsRand.size()-1);y++){
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
    /***********Change N and Sorting Count**********/
   int A = 1;
   int stepSize = 100000;

   int max = 300001;
   //number of sorting methods implemented
   int sortingCount = 10;
   //setting number of words in RandomInput.txt
   this->inputSize = A*stepSize;

   //*******Change names of Each Sorting Algorithm********/
   //output header to file for output
   ofstream output("SortingAnalysis.txt");
   output<<"N,";
   for(int y = 0;y<sortingCount+1;y++){
       if(y == 0){
           output<<"quicksort2,";
       }

       output<<"multisort ("<<y*10<<"),";
   }


   output<<endl;
   //close output file temporarily while make the randomInput file
   output.close();

   while(A*stepSize<max){
       //processing now done on
       setFileName("RandomInput.txt");

       output.open("SortingAnalysis.txt",std::fstream::app);
       output << A*stepSize << ", ";
       output.close();

       double* sumRuntime = new double[sortingCount];
       //initalize values
       for(int k = 0;k<sortingCount;k++){
           sumRuntime[k] = 0;
       }

       //find average of all sorting methods for this specific
       //input size
       for(int j = 0; j<31+1; j++){

           //function call to make random input file from the words collected from input.txt
           unsigned int seed = static_cast<unsigned int>(time(0));

           //make random file with same seed so same random file for all tests
           makeRandomFile(A*stepSize,"RandomInput.txt",seed);
           for(int i = 0;i<sortingCount;i++){

               //prepare words2 with RandomInput file instead
                readRandomData(stepSize);
                prepareData();
               //declare 2 time points
                if(j == 0){
                    continue;
                }
                std::chrono::time_point<std::chrono::system_clock> start, end;

                //store current time (now()) in start
                start = std::chrono::system_clock::now();

                //******Loop for different sortin algorithms being called***********
                //decide which sorting method to use
                if(i == 0){
                    quicksort2(0,wordsRand.size()-1);
                }
                else{
                    passOff = i*10;
                    multisort(0,wordsRand.size()-1);
                }
                //store time(now()) in end
                end = std::chrono::system_clock::now();

                //get No. of seconds elapsed & output duration
                //need to do this multiple times & get average
                std::chrono::duration<double> elapsed_seconds = end-start;
                cout<<elapsed_seconds.count()<<"  ";
                if(j != 0){

                sumRuntime[i] += elapsed_seconds.count();
                }
           }//end of all sorting methods for that random input

           cout << endl;
       }//processed all sorting algorithms

       //find average runtime
       //calculate average
       double* average = new double[sortingCount];
       for(int m = 0; m<sortingCount; m++){
           average[m] = sumRuntime[m]/30;
       }

       output.open("SortingAnalysis.txt",std::fstream::app);
       if(!output){
           cout<<"output file not opened"<<endl;
           exit(1);
       }
       //output to file the average run time and size

       for(int m = 0;m<sortingCount;m++){
            output<<fixed<<setprecision(9)<<average[m]<<", ";
       }
       output<<endl;
       output.close();

       //increment input size
       A +=1;

       this->inputSize = A*stepSize;

       //free dynamic memory
       delete[] sumRuntime;
       delete[] average;
    }
}


//making random file filled with specified length by pulling form
//the list of words collected from input.txt
void SortingCompetition::makeRandomFile(int size,char* name, unsigned int seed){
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
    for(int i = 0; i < (inputSize - stepSize); i++)
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
    fin.open("RandomInput.txt");
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


//Source: http://www.sourcetricks.com/2011/06/what-is-quick-sort-algorithm-how-to.html#.VDix3vldWuM
//Brendan's Quicksort

//quick sort function
void SortingCompetition::bcQuickSort(int start,int end){
    if(start<end){

        int pivot = (start+end)/2;
        //save off beginning and end
        int i = start;
        int j = end;

        char* temp;

        //while left indicator is less than right indicator
        while(start<end){
            //move left indicator until value pointed to
            //is greater than or equal to the pivot
            while(compareWords(words2[start],words2[pivot])<= -1){
                 start++;
            }
            while(compareWords(words2[end],words2[pivot])>= 1){
                 end--;
            }
            if(words2[start] == words2[end]){
                start++;
            }
            else if(start<end){
                temp = words2[end];
                words2[end] = words2[start];
                words2[start] = temp;

                if(start == pivot){ //if pivot was swapped with j
                    pivot =  end;
                }
                else if (end == pivot){ //if pivot was swapped with i
                    pivot = start;
                }
                start++;
                end--;


            }
        }

    bcQuickSort(i,end-1);
    bcQuickSort(end + 1,j);
    }
}


//Quicksort help from http://www.algolist.net/Algorithms/Sorting/Quicksort
void SortingCompetition::quicksort(char**& wordArr, int start, int end){

    int pivot = (start+end)/2;
    //char* pivot = new char[wordArr[med][0]+1];
    //strcpy(pivot,wordArr[med]);
    int i = start;
    int j = end;
    char* temp;

    //move values greater than pivot to right
    //& less than pivot to left
    while(i <= j){
        while(compareWords(wordArr[i],wordArr[pivot]) <= -1){
            i++;
        }

        while(compareWords(wordArr[j],wordArr[pivot]) >= 1){
            j--;
        }

        if (i <= j){
            temp = wordArr[i];
            wordArr[i] = wordArr[j];
            wordArr[j] = temp;

            if(i == pivot){ //if pivot was swapped with j
                pivot = j;
            }
            else if (j == pivot){ //if pivot was swapped with i
                pivot = i;
            }
            i++;
            j--;
        }

    }

    //recursive call for left of pivot & right of pivot
    if(start < j){
        quicksort(wordArr, start, j);
    }
    if(i < end){
        quicksort(wordArr, i, end);
    }

}

//insertion sort with quick sort method

/*void SortingCompetition::bcQuickSortWithInsertion(int start,int end){
    if(start<end){

        int pivot = (start+end)/2;
        //save off beginning and end
        int i = start;
        int j = end;

        char* temp;

        //while left indicator is less than right indicator
        while(start<end){
            //move left indicator until value pointed to
            //is greater than or equal to the pivot
            while(compareWords(words2[start],words2[pivot])<= -1){
                 start++;
            }
            while(compareWords(words2[end],words2[pivot])>= 1){
                 end--;
            }
            if(words2[start] == words2[end]){
                start++;
            }
            else if(start<end){
                temp = words2[end];
                words2[end] = words2[start];
                words2[start] = temp;

                if(start == pivot){ //if pivot was swapped with j
                    pivot =  end;
                }
                else if (end == pivot){ //if pivot was swapped with i
                    pivot = start;
                }
                start++;
                end--;


            }
        }

    bcQuickSort(i,end-1);
    bcQuickSort(end + 1,j);
    }
}
*/

//Quicksort help from http://www.algolist.net/Algorithms/Sorting/Quicksort
void SortingCompetition::quicksort2WithInsert(int start, int end){

    srand(static_cast<unsigned int>(time(0)));
    int pivot = rand()%(end-start)+start;
    int i = start;
    int j = end;
    char* temp;

    //move values greater than pivot to right
    //& less than pivot to left
    while(i <= j){
        while(compareWords(words2[i],words2[pivot]) <= -1){
            i++;
        }

        while(compareWords(words2[j],words2[pivot]) >= 1){
            j--;
        }

        if (i <= j){
            temp = words2[i];
            words2[i] = words2[j];
            words2[j] = temp;

            if(i == pivot){ //if pivot was swapped with j
                pivot = j;
            }
            else if (j == pivot){ //if pivot was swapped with i
                pivot = i;
            }
            i++;
            j--;
        }

    }

    //recursive call for left of pivot & right of pivot
    if(start < j){
        if((j-start+1)>passOff ){
            quicksort2(start, j);
        }
        else{
            insertion_sort(start,j);
        }
    }
    if(i < end){
        if((end-i+1)>passOff){
            quicksort2(i, end);
        }
        else{
            insertion_sort(i,end);
        }
    }
}


//http://mycodinglab.com/insertion-sort-algorithm/
void SortingCompetition::insertion_sort(int start,int end){
     int i, j;
     char* temp;
     int length = end - start + 1;

     for (i = start + 1; i < start + length; i++) {
         j = i;
         while (j > start && (compareWords(words2[j-1],words2[j])>= 1)){
             temp = words2[j];
             words2[j] = words2[j - 1];
             words2[j - 1] = temp;
             j--;
         }//end of while loop

    }

}

void SortingCompetition::quicksort2(int start, int end){

    int pivot = (start+end)/2;
    //char* pivot = new char[wordArr[med][0]+1];
    //strcpy(pivot,wordArr[med]);
    int i = start;
    int j = end;
    char* temp;

    //move values greater than pivot to right
    //& less than pivot to left
    while(i <= j){
        while(compareWords(words2[i],words2[pivot]) <= -1){
            i++;
        }

        while(compareWords(words2[j],words2[pivot]) >= 1){
            j--;
        }

        if (i <= j){
            temp = words2[i];
            words2[i] = words2[j];
            words2[j] = temp;

            if(i == pivot){ //if pivot was swapped with j
                pivot = j;
            }
            else if (j == pivot){ //if pivot was swapped with i
                pivot = i;
            }
            i++;
            j--;
        }

    }

    //recursive call for left of pivot & right of pivot
    if(start < j){
        quicksort2(start, j);
    }
    if(i < end){
        quicksort2(i, end);
    }

}

void SortingCompetition::multisort(int start, int end){

    int pivot = rand()%(end-start)+start;
    int i = start;
    int j = end;
    char* temp;

    //move values greater than pivot to right
    //& less than pivot to left
    while(i <= j){
        while(compareWords(words2[i],words2[pivot]) <= -1){
            i++;
        }

        while(compareWords(words2[j],words2[pivot]) >= 1){
            j--;
        }

        if (i <= j){
            temp = words2[i];
            words2[i] = words2[j];
            words2[j] = temp;

            if(i == pivot){ //if pivot was swapped with j
                pivot = j;
            }
            else if (j == pivot){ //if pivot was swapped with i
                pivot = i;
            }
            i++;
            j--;
        }

    }

    //recursive call for left of pivot & right of pivot
    //or switch to insertion sort
    if (((j-start+1) > passOff) || ((end-i+1) > passOff))
    {
        if (start < j){
            quicksort2(start, j);
        }

        if (i < end){
            quicksort2(i, end);
        }
    }

    else
    {
        #pragma omp parallel num_threads(2)
        {
            int thread = omp_get_thread_num();
            if(thread == 0){
                insertion_sort(start, j);
            }

            else{
                insertion_sort(i,end);
            }
        }
    }

}
