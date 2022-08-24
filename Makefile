fastvc: fastvc.h fastvc.cpp
	g++ fastvc.cpp -O3 -o fastvc

debug: fastvc.h fastvc.cpp
	g++ fastvc.cpp -g -o debug
	
