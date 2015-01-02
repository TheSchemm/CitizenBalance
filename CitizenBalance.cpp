#include "CitizenBalance.h"

//#define CIT_DEBUG 

CitizenBalance::CitizenBalance(std::string tty){
	const char *portname = tty.c_str();

	fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0)
	{
		cerr << "error " << errno << " opening "<< portname << ": "<< strerror (errno) << endl;
		return;
	}

	if(!isatty(fd)){
		cerr << "error " << tty << " is not a terminal" << endl;
	}
		
	delay_ms = 0;
	ibaud = 0;
	set_interface_attribs (fd, B9600, 0);
	set_blocking (fd, 1);
	

}

double CitizenBalance::get_mass(){
	write (fd, "[W]", 3);          	
	usleep ((26 + 3) * 10000);
		                   
	
	int n = read (fd, in_buff, 26);
	int sign = (in_buff[4] == '-'? -1 : 1);
	double val = strtod(&in_buff[5], NULL);
	val *= sign;
	return val;
}

unsigned int CitizenBalance::div_round_up(unsigned int n, unsigned int d){
	return (n + (d/2))/d;
}

string CitizenBalance::readline(){
	string s = "";
	
	
	
	return s;	
}

std::string CitizenBalance::get_mass_string(){
	write (fd, "[W]", 3);          	
	usleep ((26 + 3) * 10000);
		                   
	
	int n = read (fd, in_buff, 26);
	
	return std::string(in_buff, 24);
}


void CitizenBalance::tare(){
	write (fd, "[T]", 3);          	
	usleep ((3) * 10000);
}
int CitizenBalance::set_interface_attribs (int fd, int speed, int parity)
{
        
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                cerr << "error "<< errno << " from tggetattr" << endl;
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                cerr << "error "<< errno << " from tcsetattr" << endl;
                return -1;
        }
        return 0;
}

int CitizenBalance::set_baud(speed_t s){
	switch(s){
		case B9600:
			ibaud = 9600;
			break;

		default:
		return 1;
	}
	
	

	return 0;
}


void CitizenBalance::set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                cerr << "error "<< errno << " from tggetattr" << endl;
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                cerr << "error "<< errno << " from tcsetattr" << endl;
}

#ifdef CIT_DEBUG

int main(int argc, char *argv[]){
	CitizenBalance cb("/dev/ttyS0");
	//cout << cb.get_mass_string() << endl;
	cout << "w to get weight" << endl << "t to tare" << endl << "q to quit" << endl;

	char in;
	do{
		std::cin >> in;
		if(in == 'w'){
			cout << cb.get_mass() << endl;
		}else if(in == 't'){
			cb.tare();
		}
	}while(in != 'q');
	

	return 0;
}


#endif


