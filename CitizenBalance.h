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
#include <string>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

class CitizenBalance{
	int fd;

	char in_buff[26];

	int set_interface_attribs (int fd, int speed, int parity);
	void set_blocking(int fd, int should_block);

	int delay_ms;

	int ibaud;

	string readline();

	unsigned int div_round_up(unsigned int n, unsigned int d);



	struct termios tty;
public:
	CitizenBalance(std::string tty);
	int set_baud(speed_t s);
	double get_mass();
	void tare();
	std::string get_mass_string();
};



#endif
