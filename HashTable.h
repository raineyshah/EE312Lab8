//
//Created by Rainey and Jonathon on December 1st, 2018
//

#ifndef CHEATERSLAB_HASHTABLE_H
#define CHEATERSLAB_HASHTABLE_H

class HashTable{
public:
    void getChunks()

private:


};






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
        files.push_back(string(dirp->d_name));
    }
    //close directory
    closedir(dp);
    return 0;
}









#endif
