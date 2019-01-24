default:
	@g++ -std=c++14 -I include src/* -o dist/main

run:
	@./dist/main

