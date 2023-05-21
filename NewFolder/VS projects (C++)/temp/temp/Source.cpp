#include<iostream>
#include<bitset>
#include<string>
using namespace std;
int main() {
	string temp = {};
	unsigned char c = '#';
	temp = bitset<8>(c).to_string();

}