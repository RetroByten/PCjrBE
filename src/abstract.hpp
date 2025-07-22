#ifndef __abstract__
#define __abstract__
#include <string>
class abstract {
	public:
		std::string name;
		virtual void update() = 0;
};
#endif