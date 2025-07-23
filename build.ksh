if [[ ! -d ./bin ]]; then
	mkdir ./bin;
fi
g++ -std=c++98 \
	src/main.cpp \
	src/c_halt.cpp \
	src/c_clock.cpp \
	-o bin/jrbe
