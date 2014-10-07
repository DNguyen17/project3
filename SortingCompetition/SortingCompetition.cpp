#include "SortingCompetition.h"

//Constructor and Destructor
SortingCompetition::SortingCompetition(const string &inputFileName){

    setFileName(inputFileName);

    //initialize private data members
    words2 = NULL;
    setDataSize = 0;
    wordCount = 0;
}

SortingCompetition::~SortingCompetition(){
    //deletes dynamically allocated memory

    for (int i = 0; i < getWordCount(); i++)
    {
        delete[] words2[i];
    }
    delete[] words2;

    for(size_t i = 0; i < words.size(); i++)
    {
        delete[] words.at(i);
    }
    words.clear();
}

//setters and getters

//Will close current ifstream member object in case still open
//and sets object to open new input specified
void SortingCompetition::setFileName(const string& inputFileName){

    fin.close();
    fin.open(inputFileName.c_str(), ios::in);
    if (!fin){
        cerr << "file could not be opened" << endl;
    }
}
void SortingCompetition::setSetDataSize(int newSize){

    setDataSize = newSize;
}

int SortingCompetition::getSetDataSize(){

    return setDataSize;

}

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


// function will process all words in input file and put them in vector sequentially
bool SortingCompetition::readData(){

    bool x = false;

    //clear all existing words in the vector
    for (size_t i = 0; i < words.size(); i++){
        delete[] words.at(i);
    }
    words.clear();


    //collect and store words from input file
    string buffer;
    while(!fin.eof()){
        fin >> buffer;
        //cout<<buffer<<endl;
        words.push_back(new char[buffer.length()+1]);
        strcpy(words.at(words.size()-1),buffer.c_str());
    }


    fin.close();

    //function complete so return true as success
    x = true;
    return x;
}

//function copies values stored in the vector into an array of length-prefixed char*
bool SortingCompetition::prepareData(){

    bool x = false;
    //clear contents of words2 to prevent overlap later
    for(int i = 0; i < getWordCount(); i++){
        delete[] words2[i];
    }
    if (getWordCount() > 0)
        delete[] words2;

    setWordCount(words.size());

    // Loop first finds the length of the word, and then
    //creates length prefixed strings

    try{
    words2 = new char*[getWordCount()];
    }
    catch(std::bad_alloc&)
    {
        cout<<"BAD ALLOC"<<endl;
    }

    for(int i = 0; i < getWordCount(); i++){
        //determine length of string and store as ASCII character
        char length = strlen(words.at(i));

        //new string is 2 elements longer than original
        //for the length prefix and /0
        char* newString = new char[length+2];
        newString[0] = length;
        strcpy(&(newString[1]),words[i]);

        //add new length prefixed string to end of words2
        words2[i] = newString;

    }

    //if no errors occured return true
    x = true;

    return x;
}

//sort the data by length, then alphabetized
void SortingCompetition::sortData(){

    quicksort(words2, 0, getWordCount()-1);
    //mergeSort(0,getWordCount()-1);
}

void SortingCompetition::outputData(const string& outputFileName){

    //output sorted data (in words2)
    fout.open(outputFileName.c_str(), ios::out);
    if(!fout.good()){
        cerr << "file could not be opened" << endl;
    }

    for(int i = 0; i < getWordCount(); i++){
        fout << &(words2[i][1])<<endl;
    }
    fout.close();

}

//new comparison method
int SortingCompetition::compareWords(char* str1, char* str2){

    //if string is longer
    if (str1[0] > str2[0]){
        return 1;
    }

    else if(str1[0] < str2[0]){
        return -1;
    }

    //if string is same size, use strcmp
    else{
        return strcmp(&(str1[1]), &(str2[1]));
    }
    return 0;
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

void SortingCompetition::bubbleSort(){

    //move greatest values to the end of array
    for(int j = 0; j<getWordCount();j++){
        for(int y = 0; y < (getWordCount()-1); y++){
            if (compareWords(words2[y],words2[y+1])>= 1){
                char* temp1 = words2[y+1];
                words2[y+1] = words2[y];
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
       for(kk = rightCounter; kk<=high; kk++){
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
