#include <iostream>
#include <HashTable.h>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <queue>

using namespace std;

//reads and stores file names from a directory
//code used from EE312 website
int getdir(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;

    //opens directory
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << 1 << ") opening " << dir << endl;
        return 1;
    }
    //read each file from the directory
    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    //close directory
    closedir(dp);
    return 0;
}



int main() {

    string dir = string("sm_doc_set");
    vector<string> files;         //holds name of files within a directory

    int testCode;
    testCode = getdir(dir, files);
    if(testCode ==1) {
        std::cout << "File did not open." << std::endl;
    }



    return 0;
}




