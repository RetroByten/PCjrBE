#ifndef __component__
#define __component__
#include "abstract.hpp"
class component : public abstract {
	public:
		component(std::string);
		void update();
};
#endif