#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
	string filePath;
	ifstream inF;
	inF.open(filePath);
	if (inF.fail()) exit(1);
	do {
		char c;
		inF.get(c);
#if 0
		if (c belongs to instruction) {
			// do this
		}
		else {
			// do this
		}
#endif // 0

		cout << c;
	} while (!inF.eof());
	return 0;
}