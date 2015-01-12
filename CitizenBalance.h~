#ifndef _CITIZEN_BALANCE_H_
#define _CITIZEN_BALANCE_H_
#include <boost/asio/serial_port.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/char_traits.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <ctype.h>               
#include <cstdio>

#include "serial_port_device.hpp"
using namespace std;
using namespace boost;


struct alphabetic_input_filter {
	typedef char                         char_type;
	typedef iostreams::input_filter_tag  category;

	template<typename Source>
	int get(Source& src)
	{
		int c = boost::iostreams::get(src);
		
		bool rm_esc = true;

		while(c == '\e'){
			while (rm_esc){
				switch(c){
					case '.':
						rm_esc = false;
						break;
					case iostreams::WOULD_BLOCK:
						return iostreams::WOULD_BLOCK;
					case EOF:
						return EOF;
					default:
						break;
				}
				c = boost::iostreams::get(src);
			}
		}
		return c;
	}
};


class CitizenBalance{
	asio::io_service io;
	asio::serial_port  port;
	serial_port_device port_dev;
	boost::iostreams::filtering_istream is;
	
	
	int getch();
	
public:
	std::string readline();
	CitizenBalance(std::string tty);
	double get_mass();
	void tare();
	std::string get_mass_string();
	int testcommand();
	
	~CitizenBalance();

};



#endif
