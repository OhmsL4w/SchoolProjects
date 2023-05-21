#include "I_Printable.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const I_Printable& obj){
	// TODO: insert return statement here
	obj.print(os);
	return os;
}

