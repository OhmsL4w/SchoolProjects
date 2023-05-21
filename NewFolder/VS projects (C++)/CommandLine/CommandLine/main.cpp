#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;



int main(int argc, char* argv[]) {
	// validate user input and check thers only 1 param
	// open the file 
	// loop throuhg the file byte by byte and increment counts for each character

	int freq[256] = {};

	if (argc != 2) {
		cout << "incorrect number of arguments";
		return 1;
	}
	std::ifstream ifs;
	ifs.open(argv[1], ifstream::in | ifstream::binary);
	
		if (ifs.good() == false) {
		cout << "Error: could not open the file";
		return 1;
	}
		cout << "file opened successfully" << endl;

	unsigned char byte = ifs.get();
	int totalbytes{};
	while (!ifs.eof())
	{
		totalbytes++;
		freq[byte]++;
		byte = ifs.get();
	}

	for (int i = 0; i < 32; i++){
		cout << setw(3) << i << setw(7) << freq[i] << " || "
		<< setw(3) << i + 32 << setw(7) << freq[i + 32] << " || "
		<< setw(3) << i + 64 << setw(7) << freq[i + 64] << " || "
		<< setw(3) << i + 96 << setw(7) << freq[i + 96] << " || "
		<< setw(3) << i + 128 << setw(7) << freq[i + 128] << " || "
		<< setw(3) << i + 160 << setw(7) << freq[i + 160] << " || "
		<< setw(3) << i + 192 << setw(7) << freq[i + 192] << " || "
		<< setw(3) << i + 224 << setw(7) << freq[i + 224] << endl;
	}
	cout << endl<< "Total bytes read were: " << totalbytes;


}
