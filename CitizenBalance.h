#ifndef _CITIZEN_BALANCE_H_
#define _CITIZEN_BALANCE_H_

#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <memory.h>
#include <iostream>
#include <fcntl.h>
#include <cstdlib>
#include <sys/stat.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
class CitizenBalance{
	int fd;

	char in_buff[26];

	int set_interface_attribs (int fd, int speed, int parity);
	void set_blocking(int fd, int should_block);
	std::string readline();
public:
	CitizenBalance(std::string tty);
	double get_mass();
	void tare();
	std::string get_mass_string();
	int testcommand();
};



#endif
