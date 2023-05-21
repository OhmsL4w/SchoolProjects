//#include<iostream>
//#include<string>
//using namespace std;
//
//int main() {
//
//    string alphabet{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
//    string key{ "XZNLWEBGJHQDYVTKFUOMPCIASRxznlwebgjhqdyvtkfuompciasr" };
//    string user_string{};
//    
//    cout << "Enter the secret messsage: " ;
//    getline(cin, user_string);
//
//    for (size_t i = 0; i < user_string.length(); i++){
//        size_t Encrpswitch = alphabet.find(user_string.at(i));
//        if (Encrpswitch != string::npos) {
//            user_string.at(i) = key.at(Encrpswitch);
//        }
//        
//    }
//    cout << "\nEncrypting Message..........." << endl << endl;
//
//    cout << user_string << endl<< endl;
//
//    cout << "Decrypting message ........" << endl << endl;
//
//    for (size_t i = 0; i < user_string.length(); i++) {
//        size_t decrpswitch = key.find(user_string.at(i));
//        if (decrpswitch != string::npos) {
//            user_string.at(i) = alphabet.at(decrpswitch);
//        }
//
//    }
//    cout << user_string;
//}
//=======================================================================================================================
//										String Section Assignment

#include<iostream>
#include<string>
using namespace std;

int main() {

	string user_string{};

	cout << "Enter you string to be made into a pyramid: ";

	getline(cin, user_string);
	int Position{};
	for (size_t mainloop = 0; mainloop < user_string.length(); mainloop++){
		for (size_t In_Inc_loop = 0; In_Inc_loop <= mainloop; In_Inc_loop++){
			cout << user_string.at(In_Inc_loop);
			Position = In_Inc_loop;
			
		}
		 Position--;
		for (size_t In_Dec_loop = Position; In_Dec_loop < -1  ; In_Dec_loop--){
			cout << user_string.at(In_Dec_loop);
			}		
		cout << endl;
	}

}












































