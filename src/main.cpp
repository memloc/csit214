#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX_PROGRAM_SIZE 1024

void extractFileContents(ifstream&, string&);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Missing filename\n";
		exit(1);
	}

	string filePath = argv[1];
	ifstream fileStream;

	fileStream.open(filePath);
	if (fileStream.fail()) {
		cout << filePath << ": No such file or directory\n";
		exit(1);
	}

	string sourceCode;
	extractFileContents(fileStream, sourceCode);
	fileStream.close();

	cout << sourceCode << endl;

	return 0;
}

// extract the contents of file to a string, fail if the file exceeds max size
void extractFileContents(ifstream& fileStream, string& fileContents) {
	char contents[MAX_PROGRAM_SIZE];
	
	size_t size = 0;
	while (!fileStream.eof()) {
		fileStream.get(contents[size++]);

		if (size == MAX_PROGRAM_SIZE) {
			cout << "File exceeds the maximum size\n";
			exit(1);
		}
	}

	fileContents.append((const char*)contents);
}