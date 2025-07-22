if [[ ! -d ./bin ]]; then
	mkdir ./bin;
fi
g++ -std=c++98 \
	src/main.cpp \
	src/component.cpp \
	-o bin/jrbe
