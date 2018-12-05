#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include "HashTable.h"

using namespace std;
const int largePrimeSize = 100003;


int main(int argc, char *argv[])
{
//***NOTES to make it work on LINUX:
// assuming argv[1] = path to files/directory?
// dir = argv[1] + "/"?
// int chunkSize = atoi(argv[2]);
// int threshold = atoi(argv[3]);

    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();
    getdir(dir,files);

//Output file names and their respective indexes
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << " " << files[i] << endl;
    }

    vector<string> chunkIn;
    int threshold = 40;
    int chunkSize = 6;
    keyNode* hashTable [largePrimeSize];
    int hashIndex = 0;
    int numFiles = files.size();
    int collisionChart[numFiles][numFiles];
    vector<Cheaters> results;

//Initialize collision counters between files to 0
    for(int r = 0; r < numFiles; r++)
        for(int c = 0; c < numFiles; c++)
            collisionChart[r][c] = 0;
//Initialize Hash Table (Array of Linked-List Node Pointers to NULL)
    for(int z = 0; z < largePrimeSize; z++){
        hashTable[z] = NULL;
    }

//Populate Hash Table
    for (int i = 0; i < files.size(); i++) {
        //CHANGE TO argv[1] + "/" + "files[i]"
        string fileName = "sm_doc_set/";
        fileName += files[i];
        ifstream fin(fileName);

        string word;
        string uncleanChunk;
        string cleanChunk;
        vector<string> words;
        //read all words from a file into a vector (implementation requires more memory)
        while(fin >> word){
            words.push_back(word);
        }
        fin.close();
        for(int index1 = 0; index1 < (words.size())-5; index1++){
            uncleanChunk = "";
            for(int jaaa2 = 0; jaaa2 < 6; jaaa2++){
                uncleanChunk += words[index1+jaaa2];
            }
            cleanChunk = cleanTheChunk(uncleanChunk);
            hashIndex = hashFunction(cleanChunk , largePrimeSize);
            if(hashTable[hashIndex] == NULL) {
                hashTable[hashIndex] = new keyNode;
                hashTable[hashIndex]->fileIndex = i;
                hashTable[hashIndex]->next = NULL;
            }
            else if(hashTable[hashIndex]->fileIndex != i){
                keyNode *temp = new keyNode;
                temp->fileIndex = i;
                temp->next = hashTable[hashIndex];
                hashTable[hashIndex] = temp;
            }
        }

/***
        while(fin >> word) {
        //Populate one chunk and store in Hash Table at a time to preserve memory
            while (chunkIn.size() != chunkSize) {
                fin >> word;
                chunkIn.push_back(word);
            }
            uncleanChunk = "";
            for(int x = 0; x < chunkSize; x++) {
                uncleanChunk += chunkIn[x];
            }

            //cout << uncleanChunk << endl;

            //remove punctuation and decapitilize letters
            cleanChunk = cleanTheChunk(uncleanChunk);

            hashIndex = hashFunction(cleanChunk, largePrimeSize);
            if(hashTable[hashIndex] == NULL) {
                hashTable[hashIndex] = new keyNode;
                hashTable[hashIndex]->fileIndex = i;
                hashTable[hashIndex]->next = NULL;
            } else if(hashTable[hashIndex]->fileIndex != i){
                    keyNode *temp = new keyNode;
                    temp->fileIndex = i;
                    temp->next = hashTable[hashIndex];
                    hashTable[hashIndex] = temp;
            }
            chunkIn.erase(chunkIn.begin());
        }
        fin.close();
***/
    }

//Traverse Hash Table and note collisions by incrementing respective (x,y) coords in 2D array of file indexes
    for(int i = 0; i < largePrimeSize; i++){
        int file1 = 0;
        int file2 = 0;
        keyNode* tempPtr = NULL;
        while(hashTable[i] != NULL){
            file1 = hashTable[i]->fileIndex;
            tempPtr = hashTable[i];
            hashTable[i] = hashTable[i]->next;
            delete tempPtr;
            tempPtr = hashTable[i];
            while(tempPtr != NULL){
                file2 = tempPtr->fileIndex;
                collisionChart[file1][file2]++;
                tempPtr = tempPtr->next;
            }
        }
    }
//Resolve output based on 2D array and collision threshold
    //populate vector of Cheaters structs
    for(int i=0;i<numFiles;i++){
        for(int j=0;j<numFiles;j++){
            if(collisionChart[i][j] >= threshold){
                Cheaters temp1;
                temp1.cheater1 = i;
                temp1.cheater2 = j;
                temp1.collisions = collisionChart[i][j];
                results.push_back(temp1);

            }
        }
    }
    //sort in descending order of number of collisions (selection sort)
    for(int i = 0; i<results.size()-1;i++){
        for(int j = i+1; j<results.size();j++){
            if(results[j].collisions > results[i].collisions){
                Cheaters temp2;
                temp2 = results[i];
                results[i] = results[j];
                results[j] = temp2;
            }
        }
    }
    //iterate through array of results and print out the files with collisions
    cout << endl;
    for(int i = 0; i<results.size();i++){
        cout << results[i].collisions << " collisions were found between files: " << files[results[i].cheater1] << " and " << files[results[i].cheater2] << endl;
    }
    return 0;
}
