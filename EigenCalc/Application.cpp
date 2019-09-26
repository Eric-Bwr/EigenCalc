//Specifying that this is a member of the Application class so that we can use the includes/imports/methods from Application.h
#include "Application.h"

//CREATED BY ERIC BOEWER ON 23.09.2019 
//INTERNSHIP 
//FOR GRIMME Landmaschinenfabrik GmbH & Co. KG
//Read the README.md on the Repository on
//https://github.com/Eric-Bwr/EigenCalc

//Method definition, same as in the header (Returns a bool (Value 0 - 1) (TRUE or FALSE))
bool Application::processInput(int argc, char** argv) {
	//Check if Input is correct and settings the path variable to the given Input
	if (argc == 2) {
		path = argv[1];
		return true;
	} else {
		//If Input is incorrect return "incorrectInput"
		std::cout << "incorrectInput";
		return false;
	}
}

//Method definition, same as in the header (Returns a bool (Value 0 - 1) (TRUE or FALSE))
bool Application::loadFile() {
	//Getting the whole content of the file wich is given by specifing path wich we got from processInput
	char* input = fileStream.readFile(path, "r");
	//Checking if input is equal to nullptr thus give us an error wich u can catch by checking for "incorrectInput"
	if (input == nullptr) {
		std::cout << "incorrectInput";
		return false;
	}
	//Getting the split content/list by saying we want to have every single line as one element in a list by seperating each element by \n / \r
	//Putting the content into the "lines" buffer defined in the header file
	lines = fileStream.splitToVector(input, '\n', '\r');
	//Checking if there are any lines to use if not give us an error wich u can catch by checking for "incorrectInput"
	if (lines->size() < 1) {
		std::cout << "incorrectInput";
		return false;
	}
	//Returning TRUE so that we can go the the next function (int main() keep track of that)
	return true;
}

//Method definition, same as in the header (Returns a bool (Value 0 - 1) (TRUE or FALSE))
bool Application::modify() {
	//Looping through each and every line in the file
	for (char* line : *lines) {
		//Splitting the lines again by a tab or space
		std::vector<char*>* elements = fileStream.splitToVector(line, '\t', ' ');
		//If for example the last line (or any) has no content and thus is just a \n skipping the line
		if (elements->empty()) {
			continue;
		}
		//Creating the 3*3 matrix from the content given by the file
		MatrixXd matrix(3, 3);
		matrix(0, 0) = atof(elements->at(1));
		matrix(1, 0) = atof(elements->at(4));
		matrix(2, 0) = atof(elements->at(5));
		matrix(0, 1) = atof(elements->at(4));
		matrix(1, 1) = atof(elements->at(2));
		matrix(2, 1) = atof(elements->at(6));
		matrix(0, 2) = atof(elements->at(5));
		matrix(1, 2) = atof(elements->at(6));
		matrix(2, 2) = atof(elements->at(3));
		//Creating a solver so that we can get the eigenvectors later
		EigenSolver<MatrixXd> solver(matrix, true);
		//Creating a stringstream wich no one wants to do but its sadly the only way
		std::stringstream ss;
		//Putting a TAB in first, then the eigenvalues (only the real content, not the complex numbers), then another TAB and the eigentvectors (Real of cause)
		ss << '\t' << matrix.eigenvalues().real() << '\t' << solver.eigenvectors().real();
		//Creating a buffer so that we can use it later
		std::string* cleanData = new std::string;
		//Putting the id of the solid from the modeling program in first
		cleanData->append(elements->at(0));
		//Delete allocated memory wich we no longer need
		delete elements;
		//Getting the data out of the stringstream wich is horrible
		std::string data(const_cast<char*>(ss.str().c_str()));
		//Looping through the data
		for (int i = 0; i < data.size(); i++) {
			//Getting the current letter
			char letter = data.at(i);
			//Checking if theres a \n so that we can replace it with a space (Format from Eigen(Matrix))
			if (letter == '\n') {
				cleanData->push_back(' ');
				//Skip the push_back(letter) so that the \n is kept out of the file
				continue;
			}
			//If no \n the current letter gets pushed into the buffer and later in the file
			cleanData->push_back(letter);
		}
		//Putting the cleaned up data into the "total" buffer wich will later be written to a file
		buffer->append(cleanData->data());
		//Putting a \n at the end of each line because we dont want the file to be a onliner
		buffer->append("\n");
		//Deleting memory wich is no longer in use
		delete cleanData;
	}
	//Returning true so that we can go to the next function (int main() keeps care of that)
	return true;
}

//Method definition, same as in the header (Returns a bool (Value 0 - 1) (TRUE or FALSE))
bool Application::writeFile() {
	//Converting the const char* the a std::string wich has things like find() and substr()
	std::string* pathName = new std::string(path);
	//Gettings the position (Integer) of gtsMOI
	std::size_t pos = pathName->find("gtsMOI");
	//Checking if the position actually exists
	if (pos == std::string::npos) {
		//If not return "incorrectInput" wich you can catch
		std::cout << "incorrectInput";
	} else {
		//If so remove the "gtsMOI from the path
		*pathName = pathName->substr(0, pos);
		//And put an gtsEIG at the end
		pathName->append("gtsEIG");
	}
	//Write the file with the data given from modify() and the path from the header file wich we extracted in processInput(), "w" to actually write
	fileStream.writeFile(buffer->data(), pathName->c_str(), "w");
	//Deleting allocated memory wich is no longer in use
	delete pathName;
	//Returning TRUE so that we can print out "done" (int main() keeps care of that)
	return true;
}

//Making the Application class accessible to the main function
Application app;

//The main function is the point where it all begins (Executed when clicking on the .exe)
int main(int argc, char** argv){
	//Executes processInput() first
	if(app.processInput(argc, argv))
		//If executed successfully loadFile will be execute and so on
		if(app.loadFile())
			if(app.modify())
				if(app.writeFile())
					//Returning "done" when everything worked out just fine
					std::cout << "done" << std::endl;
	//Returning 0 so that no error is thrown except command line errors wich you can catch (Error would be anything but 0)
	return 0;
}