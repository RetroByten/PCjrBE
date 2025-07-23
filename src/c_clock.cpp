#include <iostream>
#include <vector>

#include "c_clock.hpp"
#include "sysplanar.hpp"
#include "utils.hpp"

void c_clock::install(sysplanar* my_sysplanar){
	std::cerr << "c_clock::install()" << std::endl;
	system_clock = 0;
	cpu_clock = 0;
	pit_clock = 0;
	type_id = CE_SYSTEM_CLOCK;
}
void c_clock::tick(sysplanar* my_sysplanar){
	std::cerr << "c_clock::tick(";
	
	system_clock++;
	if ( system_clock % 3 == 0 ){ cpu_clock++; }
	if ( system_clock % 12 == 0 ){ pit_clock++; }
	if ( system_clock % (12 * 2048) == 0 ){ // Roll over the clocks at a convienant multiple
		system_clock = 0;
		cpu_clock = 0;
		pit_clock = 0;
	} 

	std::cerr << 
		util_to_string(system_clock) << "," <<
		util_to_string(cpu_clock) << "," <<
		util_to_string(pit_clock) << 		
	")" << std::endl;
}
void c_clock::remove(sysplanar* my_sysplanar){
	std::cerr << "c_clock::remove()" << std::endl;
}
