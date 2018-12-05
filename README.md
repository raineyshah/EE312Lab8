# EE312Lab8
# Written by Rainey Shah and Jonathan Walsh


What does plagiarismCatcher do? 

This program takes three inputs: a path to a directory of files (likely is simply the name of the directory listed in the same directory as the program), a word length, and a threshhold. The path to a directory of files will allow the program to analyze all contained files against each other to determine the level of plagiarism that occurs. 


How to run plagiarismCatcher:
				
Step 1: type "make" into the command line to compile the program
Step 2: Enter this format to run program "./plagiarismCatcher path/to/files int1 int2"

Note: "int1" is the word length of the collisions that will be compared across files. "int2" is a cutoff of collisions that must occur between two files in order to be displayed as suspicious.
