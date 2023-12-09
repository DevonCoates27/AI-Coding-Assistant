compile: 
	make libAPI
	make mainCompile

libAPI:
	clang++ -shared -g -std=c++14 ./Code/JobSystemCode/*.cpp -o ./Code/lib/libJobSystemAPI.so -fPIC -Wall

mainCompile:
	clang++ -g -std=c++14 -o app ./Code/*.cpp -L./Code/lib -lJobSystemAPI -Wall -Wl,-rpath,./Code/lib

compileCode:
	clang++ -g -std=c++14 -o exec ./Code/JobSystemCode/CodeToTest/file1.cpp -Wall

