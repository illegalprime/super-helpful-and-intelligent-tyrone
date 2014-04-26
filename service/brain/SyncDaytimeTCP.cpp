#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "wrappers/pandora.hpp"

#define PORT 8489
using boost::asio::ip::tcp;
typedef std::string String;

std::string makeDaytimeString();

int main(int argc, char* argv[]) {
	using namespace std;
	const String header = "This is an automated response from the server.\n";

	PandoraRadio radio;

	try {
		boost::asio::io_service   ioServ;
		boost::system::error_code unimportantError;

		tcp::acceptor acceptor(ioServ, tcp::endpoint(tcp::v4(), PORT));

		cout << "Bound to port " << PORT << "\n";

		while (true) {
			boost::asio::streambuf responseBuffer;
			tcp::socket socket(ioServ);
			acceptor.accept(socket);
			cout << "Created connection." << endl;

			cout << "Read " << boost::asio::read_until(socket, responseBuffer, "\r\n", unimportantError)
				 << " bytes." << endl;

			istream responseStream(&responseBuffer);
			String  response, request;

			getline(responseStream, response);
			response = "Client Request:  " + response     + "\n";
			request  = "Server Response: " + makeDaytimeString();

			std::size_t delimPos = response.find(":");

			if (delimPos != std::string::npos) 
			{
				std::string program = response.substring(0, delimPos);
				std::string command = response.substring(delimPos + 1);

				if (program == "PANDORA") 
				{
					radio.handleCommand(command);
				}
			}

			boost::asio::write(socket, boost::asio::buffer(header + response + request), unimportantError);
			cout << "\t" << header << "\t" << response << "\t" << request 
			     << "Sent time of day." << endl << endl;
		}
	}
	catch (std::exception& err) {
		std::cerr << err.what() << std::endl; 
	}
	return 0;
}

std::string makeDaytimeString()
{
	std::time_t now = std::time(0);
	return std::ctime(&now);
}