//The whole header (.h) file (this file) will only be loaded once, and can be used many times
#pragma once

//Including things we need
//Eigen Methods
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
//Standart Library <Console Input/Output and some other stuff>
#include <iostream>
//List/Vector Library
#include <vector>
//String Library <Easier to handle>
#include <string>
//StringStream Library <Piece of shit, but the only way to convert the MatrixType into a string
#include <sstream>
//FileStream Header/Library so that we have access to the Methods declared in FileStream.h
#include "FileStream.h"

//Basically Ignoring the Namespace "Eigen"
using namespace Eigen;

//Defining a class
class Application {
//Making methods available
public:
	//Defining methods (Same as in the .cpp)
	bool processInput(int argc, char** argv);
	bool loadFile();
	bool modify();
	bool writeFile();
private:
	//Defining things wich cant be accessed by other files
	//Making the FileStream class useable
	FileStream fileStream;
	//Defining some Buffers
	const char* path;
	std::string result;
	std::vector<char*>* lines;
	std::string* buffer = new std::string;
};