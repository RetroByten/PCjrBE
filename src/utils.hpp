#ifndef __utils__
#define __utils__
#include <sstream>
#include <string>
template<typename T>
std::string util_to_string(const T & value){
	std::ostringstream output_string_stream;
	output_string_stream << value;
	return output_string_stream.str();
}
#endif