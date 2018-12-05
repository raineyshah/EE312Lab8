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
const int largePrimeSize = 400009;


int main(int argc, char *argv[])
{
//***NOTES to make it work on LINUX are by  lines that need changing

    string dir = string("sm_doc_set");     // string dir = argv[1]
    vector<string> files = vector<string>();
    getdir(dir,files);

//Output file names and their respective indexes
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << " " << files[i] << endl;
    }

    vector<string> chunkIn;
    int threshold = 200;     //int chunkSize = atoi(argv[2]);
    int chunkSize = 8;      //int chunkSize = atoi(argv[2]);
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
        string fileName = "sm_doc_set/" + files[i]; //string fileName = argv[1] + "/" + files[i];
        ifstream fin(fileName);

        string word;
        string uncleanChunk;
        string cleanChunk;
        vector<string> words;

        //read all words from a file into a vector (implementation requires more memory)
        while (fin >> word) {
            words.push_back(word);
        }
        fin.close();
        for (int index1 = 0; index1 < words.size() - chunkSize; index1++) {       //Keeps in mind additional chunkSize iteration
            uncleanChunk = "";
            for (int j = 0; j < chunkSize; j++) {
                uncleanChunk += words[index1 + j];
            }
            cleanChunk = cleanTheChunk(uncleanChunk);
            hashIndex = hashFunction(cleanChunk, largePrimeSize);
            if (hashTable[hashIndex] == NULL) {
                hashTable[hashIndex] = new keyNode;
                hashTable[hashIndex]->fileIndex = i;            //starts linked list
                hashTable[hashIndex]->next = NULL;
            }
            else if (hashTable[hashIndex]->fileIndex != i) {
                keyNode *temp = new keyNode;
                temp->fileIndex = i;                    //inserts at head
                temp->next = hashTable[hashIndex];
                hashTable[hashIndex] = temp;
            }
        }
    }

/***            QUEUE IMPLEMENTATION OF GETTING CHUNKS WITH SOME UNIDENTIFIABLE BUG IN IT
        while(fin >> word) {
        //Populate one chunk and store in Hash Table at a time to preserve memory
            while (chunkIn.size() != chunkSize) {
                chunkIn.push_back(word);
                if(fin >> word);
            }
            uncleanChunk = "";
            for(int x = 0; x < chunkSize; x++) {
                uncleanChunk += chunkIn[x];
            }
            cleanChunk = cleanTheChunk(uncleanChunk);
            hashIndex = hashFunction(cleanChunk, largePrimeSize);

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
            chunkIn.erase(chunkIn.begin());
        }
        fin.close();
    }
***/

//Traverse Hash Table and note collisions by incrementing respective (x,y) coords in 2D array of file indexes
    for(int i = 0; i < largePrimeSize; i++){
        int file1 = 0;
        int file2 = 0;
        keyNode* tempPtr = NULL;
        while(hashTable[i] != NULL){
            file1 = hashTable[i]->fileIndex;
            tempPtr = hashTable[i];
            hashTable[i] = hashTable[i]->next;      //deletes current file index and stores that index in file1
            delete tempPtr;
            tempPtr = hashTable[i];
            while(tempPtr != NULL){
                file2 = tempPtr->fileIndex;
                collisionChart[file1][file2]++;     //compares file1 to all other nodes in that linked list if applicable
                tempPtr = tempPtr->next;
            }
        }
    }
    //populate a vector of struct Cheaters if (file1,file2) collisions are above threshold
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
    for(int i = 0; i < results.size(); i++){
        for(int j = i; j < results.size(); j++){
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
        cout << results[i].collisions << " collisions between files: "
        << files[results[i].cheater1] << " and " << files[results[i].cheater2] << endl;
    }
}
