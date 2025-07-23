#ifndef __a_component__
#define __a_component__

class sysplanar; // Forward declare the sysplanar class

enum { // Type IDs
	CE_SYSTEM_CLOCK = 0,
	CE_SYSTEM_HALT
};
class a_component {
	public:
		int type_id;
		virtual void install(sysplanar*) = 0;
		virtual void tick(sysplanar*) = 0;
		virtual void remove(sysplanar*) = 0;
};
#endif