app:
	g++ *.cpp -I. -std=c++11 -lpthread -o app
run:
	./app
clean:
	rm app
