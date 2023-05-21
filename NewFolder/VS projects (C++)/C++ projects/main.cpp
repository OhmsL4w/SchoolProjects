#include<iostream>
#include<vector>
using namespace std;

int main() {
	char selection{};
	vector <int> list{};

	do {

		cout << "P - Prints numbers" << endl;
		cout << "A - Add a number" << endl;
		cout << "M - Display the mean of the numbers" << endl;
		cout << "S - Display the smallest number " << endl;
		cout << "L - Display the Largest number" << endl;
		cout << "Q - Quit" << endl;

		cout << "\nEnter your choice : ";
		cin >> selection;

		if (selection == 'p' || selection == 'P') {
			cout << "[ ";
			for (auto val : list) {
				cout << val << " ";
			}
			cout << "]" << endl << endl;
		}
		else if (selection == 'a' || selection == 'A') {
			cout << "Enter an integer to be added to the list: ";
			int addtolist{};
			cin >> addtolist;
			list.push_back(addtolist);
			cout << addtolist << " was added to the list" << endl << endl;

		}
		else if (selection == 'm' || selection == 'M') {
			double meanholder{};
			
			for (auto Mselect : list) {
				meanholder += Mselect;
				
			}
			if (meanholder == 0) {
				cout << "Unable to display the mean - no data" << endl << endl;
			}
			else {
				cout << static_cast<double> (meanholder) / list.size() << " is the mean of the numbers in the lsit" << endl << endl;
			}
		}
		else if (selection == 's' || selection == 'S') {
			cout << "The smallest number in the lsit is :";
			int smallestnum{ list.at(0)};
			for (auto snum : list) {
				if (snum < smallestnum) {
					smallestnum = snum;
				}
			}
			cout << smallestnum << endl << endl;
		}
		else if (selection == 'l' || selection == 'L') {
			cout << "The largest number in the list is :";
			int largestnum{ list.at(0) };
			for (auto lnum : list) {
				if (lnum > largestnum) {
					largestnum = lnum;
				}
			}
			cout << largestnum << endl << endl;
		}
		else if (selection == 'q' || selection == 'Q') {
			cout << "GoodBye" << endl << endl;
			break;
		}
		else {
			cout << "Unknown selection try again" << endl << endl;
		}

	} while (selection != 'q' && selection != 'Q');




}

