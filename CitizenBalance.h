#ifndef _CITIZEN_BALANCE_H_
#define _CITIZEN_BALANCE_H_
#include <boost/asio/serial_port.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/asio.hpp> 
#include <iostream>
#include <string>
using namespace std;
using namespace boost;

class CitizenBalance{
	asio::io_service io;
	asio::serial_port port;
	boost::iostreams::filtering_istream is;
	
	std::string readline();
public:
	CitizenBalance(std::string tty);
	double get_mass();
	void tare();
	std::string get_mass_string();
	int testcommand();
};



#endif
