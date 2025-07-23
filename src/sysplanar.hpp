#ifndef __sysplanar__
#define __sysplanar__

#include<vector>

#include "a_component.hpp" // Abstract component

class sysplanar {
	public:
		bool halt; // Global flag to halt the system
		std::vector<a_component*> components; // Pointer array of components
};
#endif