#include <iostream>
#include "component.hpp"
component::component(std::string my_name){
	std::cerr << "component::component()" << std::endl;
	name = my_name;
}
void component::update(){
	std::cerr << "component::update()-" << name << std::endl;
}