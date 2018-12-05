//
//Created by Rainey and Jonathon on December 1st, 2018
//

#ifndef CHEATERSLAB_HASHTABLE_H
#define CHEATERSLAB_HASHTABLE_H

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

const int prime = 31;

using namespace std;

struct keyNode{
    int fileIndex;
    keyNode* next;
};

struct Cheaters{
    int collisions;
    int cheater1;
    int cheater2;
};

int hashFunction(const string &cleanChunk, int hashTableSize);
string cleanTheChunk(const string &uncleanChunk);


int hashFunction(const string &cleanChunk, int hashTableSize){
    double value = 0;
    int hashIndex = 0;
    for(int i = 0; i < sizeof(cleanChunk); i++){
        value += (cleanChunk[i]*pow(23, i));
    }
    hashIndex = fmod(value, hashTableSize);
    //always return positive value index
    if(hashIndex < 0){
        hashIndex = (-1*hashIndex);
    }
    return hashIndex;
}

string cleanTheChunk(const string &uncleanChunk){
    string cleanChunk = "";
    for(int i = 0; i < uncleanChunk.size(); i++){
        if(uncleanChunk[i] >= 65 && uncleanChunk[i] <= 90) {
            cleanChunk += uncleanChunk[i] + 32;
        } else if((uncleanChunk[i] >= 48 && uncleanChunk[i] <= 57) || (uncleanChunk[i] >= 97 && uncleanChunk[i] <= 122)){
            cleanChunk += uncleanChunk[i];
        }
    }
    return cleanChunk;
}



//reads and stores file names from a directory
//code used from EE312 website
int getdir(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;

    //opens directory
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    //read each file from the directory
    while ((dirp = readdir(dp)) != NULL) {
        if(string(dirp->d_name) != "." && string(dirp->d_name) != "..")
        files.push_back(string(dirp->d_name));
    }
    //close directory
    closedir(dp);
    return 0;
}









#endif
