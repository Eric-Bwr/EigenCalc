//Just for beauty reasons, not needed (Removes a warning from the console because you SHOULD but CAN use this way of file reading/writing wich is much faster)
#define _CRT_SECURE_NO_WARNINGS
//Specifying that this is a member of the FileStream class so that we can use the includes/imports/methods from FileStream.h
#include "FileStream.h"

//Reads a file with: <PATH->C:/USERS/...> <MODE->"w"-write...>
char* FileStream::readFile(const char *path, const char* mode) {
	//Looks for/Opens file
	FILE* file = fopen(path, mode);
	//Checks if file exists ///Throws fileNonExist if not
	if (file == nullptr) {
		std::cout << "fileNonExist";
		return nullptr;
	}
	//Allocating memory for fast file reading
	fseek(file, 0, SEEK_END);
	size len = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(sizeof(char) * (len + 1));
	//Checking if memory is available ///Throws fileMemAlloc if no Memory available
	if (&buffer == nullptr) {
		fclose(file);
		std::cout << "fileMemAlloc";
		return nullptr;
	}
	//Reads the content and puts it into a buffer (Fancy for String) and returns it
	size bytesRead = fread(buffer, sizeof(char), len, file);
	buffer[bytesRead] = '\0';
	fclose(file);
	return buffer;
}

//Reads a file with: <BUFFER->Content in char* format (C String)> PATH->C:/USERS/...> <MODE->"r"-read...>
void FileStream::writeFile(char *buffer, const char *path, const char *mode) {
	//Looks for/Opens file
	FILE* file = fopen(path, mode);
	//Checks if file exists ///Throws fileNonExist if not
	if (file == nullptr) {
		std::cout << "fileNonExist";
		return;
	}
	//Checking if file can be written and writes the buffer
	if (fprintf(file, buffer) < 0) {
		std::cout << "fileCantWrite";
		return;
	} else if (fprintf(file, "\n") < 0) {
		std::cout << "fileCantWrite";
		return;
	}
	//Cleans up memory
	fflush(file);
	fclose(file);
}

//Splits given content into list (Vector) <DATA->Content in char* format (C String)> <CHECK->Chars to check for / at that letters the content will be split and pushed into list (Vector)
std::vector<char*>* FileStream::splitToVector(char* data, char firstCheck, char secondCheck) {
	//Defining Buffers
	std::vector<char*> splitData;
	std::string _data(data);
	std::string* buffer = new std::string;
	//Going through each letter (char) and checking if any letter is equal to first/secondCheck
	//If so, a new "Sentence" will begin
	for (char letter : _data) {
		if (letter == firstCheck || letter == secondCheck) {
			splitData.push_back(buffer->data());
			buffer = new std::string;
		}
		else buffer->push_back(letter);
	}
	splitData.push_back(buffer->data());
	//Returning the data
	return new std::vector<char*>(splitData);
}