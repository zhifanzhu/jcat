jcat: main.cpp
	g++ -o jcat main.cpp -std=c++11 -I./include

test: jcat
	./jcat Seq\ input.ipynb

all: jcat test
	@echo "Success"


clean: jcat
	rm jcat
