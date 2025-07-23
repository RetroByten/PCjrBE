#ifndef __c_clock__
#define __c_clock__
#include "a_component.hpp"
class c_clock : public a_component {
	public:
		int system_clock; // 14MHz clock
		int cpu_clock; // system_clock/3 CPU clock
		int pit_clock; // system_clock/12 Programmable Interrupt Timer clock
		void install(sysplanar*);
		void tick(sysplanar*);
		void remove(sysplanar*);

};
#endif