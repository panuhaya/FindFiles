FindFiles
Jul 2016

This file is just to explain the usage of FindFiles C++ project:
It was Implemented with boost and take advantage of recursive_directory_iterator in order to scan all the directories and subdirectories.

Firstly is validated all the files repeated consider the name of the file and the size thereof.
The files are sorted according to the directory to which belong.
The names of the files are put together to be written in the file filesRepited.txt
There is not leak of memory, but definitely in big directories is a little bit slow.

Tested in Apple, and Windows as well.  

Contains 
	FindFiles/src/FindFiles.cpp
	this file readme.txt



Execute command with 
	g++ -std=c++11
