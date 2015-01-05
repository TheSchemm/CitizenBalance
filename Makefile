all: CitizenBalance

CitizenBalance: main.cpp CitizenBalance.cpp
	g++ -std=c++11 -o CitizenBalance main.cpp CitizenBalance.cpp -lboost_system -lboost_regex -lX11 -I.
