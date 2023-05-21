#include <iostream>
#include <memory>
#include "Account.h"
#include "Checking_Account.h"
#include "Savings_Account.h"
#include "Trust_Account.h"
#include "Account_Util.h"

using namespace std;

int main() {
    // test your code here
	try{
		Checking_Account frank{ "Frank", 100 };
		std::cout << frank << std::endl;
		frank.withdraw(200);

	}
	catch (const IllegalBalanceException& ex){
		std::cerr << ex.what() << std::endl;

	}
	catch (const InsuficientFundsException& ex){
		std::cerr << ex.what() << std::endl;
	}

    std::cout << "Program completed successfully" << std::endl;
    return 0;
}

