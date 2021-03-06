#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp> 
#include <iostream>
#include <string>
using namespace std;
using namespace boost;

class serial_port_device{
	
	asio::serial_port & port_;
public:
	typedef char                                          char_type;
	typedef boost::iostreams::bidirectional_device_tag    category;
	

	explicit serial_port_device(asio::serial_port& port): port_(port){

	}

	std::streamsize read(char* s, std::streamsize n) 
        {

		//cout << "Reading: " << n << endl;
		boost::system::error_code ec;

		std::size_t rval = port_.read_some(boost::asio::buffer(s, n), ec);
		if (!ec)
		{
			//cout << "Read: " << rval << endl;
		    return rval;
		}
		else if (ec == boost::asio::error::eof)
		{
		    return -1;
		}
		else
		{
		    throw boost::system::system_error(ec,"read_some");
		}
        }

    	std::streamsize write(const char* s, std::streamsize n)
	{
		// Write up to n characters to the underlying
		// data sink into the buffer s, returning the
		// number of characters written

		boost::system::error_code ec;
		std::size_t rval = port_.write_some(boost::asio::buffer(s, n), ec);
		if (!ec)
		{
			return rval;
		}
		else if (ec == boost::asio::error::eof)
		{
			return -1;
		}
		else
		{
			throw boost::system::system_error(ec,"write_some");
		}

	}

};
