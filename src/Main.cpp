#include <iostream>
#include <string>
#include "JobShop.h"
#include "Parse.h"

void parseFile(std::string);
JobShop shoppie(0);

int main(int argc, char **argv)
{

	if (argc == 2)
		// parseFile(argv[1]);
		std::cout << "woowie" << '\n';
	else
		std::cout << "invalid amount of arguments. " << '\n';

	Parse peter(0);
	peter.parseFile(argv[1], shoppie);
	return 0;
}
