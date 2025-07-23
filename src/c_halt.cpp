#include <iostream>
#include <vector>

#include "c_halt.hpp"
#include "sysplanar.hpp"

void c_halt::install(sysplanar* my_sysplanar){
	std::cerr << "c_halt::install()" << std::endl;
	type_id = CE_SYSTEM_HALT;
}
void c_halt::tick(sysplanar* my_sysplanar){
	std::cerr << "c_halt::tick()" << std::endl;
	my_sysplanar->halt = true;
}
void c_halt::remove(sysplanar* my_sysplanar){
	std::cerr << "c_halt::remove()" << std::endl;
}
