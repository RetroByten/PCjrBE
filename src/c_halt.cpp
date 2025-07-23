#include <iostream>
#include <vector>

#include "c_halt.hpp"
#include "c_clock.hpp"
#include "sysplanar.hpp"

void c_halt::install(sysplanar* my_sysplanar){
	std::cerr << "c_halt::install()" << std::endl;
	system_clock_halt_ticks = 24;
	type_id = CE_SYSTEM_HALT;
}
void c_halt::tick(sysplanar* my_sysplanar){
	std::cerr << "c_halt::tick()" << std::endl;
	std::vector<a_component*>::iterator it;
	for (it = my_sysplanar->components.begin(); it != my_sysplanar->components.end(); ++it){
		if ( ((*it)->type_id) = CE_SYSTEM_CLOCK ){
			if ( system_clock_halt_ticks == (((c_clock*)(*it))->system_clock) ){
				my_sysplanar->halt = true;
			}
		}
	}
}
void c_halt::remove(sysplanar* my_sysplanar){
	std::cerr << "c_halt::remove()" << std::endl;
}
