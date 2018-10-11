
#include "Hashtable.h"
#include <iostream>

int main() {
	Hashtable<std::string, int> ht(10000);
	ht.ins("ABE", 10);
	ht.ins("ABE", 11);
	std::cout << ht.get("ABE");
	return 0;
}