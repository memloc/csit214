#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "../include/Compiler.h"

using namespace std;

#define MAX_PROGRAM_SIZE 1024

string extractFileContents(ifstream&);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Missing file name\n";
		exit(1);
	}

	string filePath = argv[1];
	ifstream fileStream;

	fileStream.open(filePath);
	if (fileStream.fail()) {
		cout << filePath << ": No such file or directory\n";
		exit(1);
	}

	string sourceCode = extractFileContents(fileStream);
	sourceCode.pop_back();
	fileStream.close();

	cout << sourceCode << endl;

	vector<Bytecode::Instruction>* program = Compiler::compile(sourceCode);

	return 0;
}

// extract the contents of file to a string, fail if the file exceeds max size
string extractFileContents(ifstream& fileStream) {
	char contents[MAX_PROGRAM_SIZE];

	size_t size = 0;
	while (!fileStream.eof()) {
		fileStream.get(contents[size++]);

		if (size == MAX_PROGRAM_SIZE) {
			cout << "File exceeds the maximum size\n";
			fileStream.close();
			exit(1);
		}
	}

	return (const char*)contents;
}
