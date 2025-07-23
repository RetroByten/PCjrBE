#ifndef __c_halt__
#define __c_halt__
#include "a_component.hpp"
class c_halt : public a_component {
	public:
		void install(sysplanar*);
		void tick(sysplanar*);
		void remove(sysplanar*);

};
#endif