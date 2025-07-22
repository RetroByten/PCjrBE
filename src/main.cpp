#include <iostream>
#include <sstream>
#include <string>

#include "system.hpp"
#include "component.hpp"

int main(int argc, char** arv){
	std::cerr << "main::main() - entry" << std::endl;

	struct system sys;
	component comp1("comp1");
	component comp2("comp2");

	comp1.update();
	comp2.update();

	std::cerr << "main::main() - end" << std::endl;
	return 0;
}