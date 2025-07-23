#include <iostream>
#include <sstream>
#include <string>

#include <vector>

#include "sysplanar.hpp"
#include "a_component.hpp"

#include "c_halt.hpp"
#include "c_clock.hpp"

sysplanar pcjr;
int main(int argc, char** arv){
	std::cerr << "main::main() - entry" << std::endl;

	pcjr.halt = false;

	c_clock my_clock; pcjr.components.push_back(&my_clock);
	c_halt my_halt; pcjr.components.push_back(&my_halt);

	std::vector<a_component*>::iterator it;
	std::vector<a_component*>::reverse_iterator rit;

	// Install
	for (it = pcjr.components.begin(); it != pcjr.components.end(); ++it){
		(*it)->install(&pcjr);
	}

	// Tick loop
	while ( !pcjr.halt ){
		for (it = pcjr.components.begin(); it != pcjr.components.end(); ++it){
			(*it)->tick(&pcjr);
			if ( pcjr.halt ) { break; }
		}
	}

	// Remove components
	for (rit = pcjr.components.rbegin(); rit != pcjr.components.rend(); ++rit){
		(*rit)->remove(&pcjr);
	}

	std::cerr << "main::main() - end" << std::endl;
	return 0;
}