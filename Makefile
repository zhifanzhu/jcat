jcat: main.cpp
	g++ -o jcat main.cpp -Wall -std=c++11 -I./include

test: jcat
	./jcat Seq\ input.ipynb

all: jcat test


clean: jcat
	rm jcat
