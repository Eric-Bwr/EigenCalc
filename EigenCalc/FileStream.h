//The whole header (.h) file (this file) will only be loaded once, and can be used many times
#pragma once

//Including things we need
//Standart Library <Console Input/Output and some other stuff>
#include <iostream>
//List/Vector Library
#include <vector>
//String Library <Easier to handle>
#include <string>
//More/Better Type Definitions so that we can handle memory better
#include <cstdint>

//I hate size_t so i call it size
typedef size_t		size;

//Defining a class
class FileStream {
//Making methods available
public:
	//Defining methods (Same as in the .cpp)
	char* readFile(const char* path, const char* mode = "r");
	void writeFile(char* buffer, const char* path, const char* mode = "w");
	std::vector<char*>* FileStream::splitToVector(char* data, char firstCheck, char secondCheck);
};