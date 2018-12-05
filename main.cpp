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
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << " " << files[i] << endl;
    }

    vector<string> chunkIn;
// int chunkSize = atoi(argv[2]);
    int chunkSize = 6;
    keyNode* hashTable [largePrimeSize];
    int hashIndex = 0;

    int numFiles = files.size();

    int collisionChart[numFiles][numFiles];

    for(int r = 0; r < numFiles; r++)
        for(int c = 0; c < numFiles; c++)
            collisionChart[r][c] = 0;

    for(int z = 0; z < largePrimeSize; z++) hashTable[z] = NULL;

    for (int i = 0; i < files.size(); i++) {
        //CHANGE TO argv[1]
        string fileName = "sm_doc_set/";
        fileName += files[i];
        ifstream fin(fileName);

        string word;
        string uncleanChunk;
        string cleanChunk;

        while(fin >> word) {
            while (chunkIn.size() != chunkSize) {
                fin >> word;
                chunkIn.push_back(word);
            }
            uncleanChunk = "";
            for(int x = 0; x < chunkSize; x++) {
                uncleanChunk += chunkIn[x];
            }

            cout << uncleanChunk << endl;

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
    }

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
int y = 0;


    //increment 2-D array respectively, as we traverse down the hash table
    //put into a vector of strings if more than argv[3] and sort and print out

    return 0;
}
