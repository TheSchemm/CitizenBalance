all: CitizenBalance

CitizenBalance: main.cpp CitizenBalance.cpp
	g++ -std=c++11 -o CitizenBalance main.cpp CitizenBalance.cpp -lX11 -I.
