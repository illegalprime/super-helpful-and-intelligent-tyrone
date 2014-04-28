#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "wrappers/pandora.hpp"

#define PORT 8489
using boost::asio::ip::tcp;
typedef std::string String;

std::string makeDaytimeString();
std::string handleRequest(std::string& request);

const String header = "This is an automated response from the server.\n";
PandoraRadio radio;

int main(int argc, char* argv[]) {
	using namespace std;

	try {
		boost::asio::io_service   ioServ;
		boost::system::error_code unimportantError;

		tcp::acceptor acceptor(ioServ, tcp::endpoint(tcp::v4(), PORT));

		cout << "Bound to port " << PORT << "\n";

		while (true) {
			boost::asio::streambuf requestBuffer;
			tcp::socket socket(ioServ);
			acceptor.accept(socket);
			cout << "Created connection, ";
			cout << "read " << boost::asio::read_until(socket, requestBuffer, '\n', unimportantError)
				 << " bytes." << endl;

			String  request, response;
			istream requestStream(&requestBuffer);
			getline(requestStream, request);
			
			response = handleRequest(request) + "\n";

			boost::asio::write(socket, boost::asio::buffer(response), unimportantError);
			cout << "Request:  " << request  << endl
				 << "Response: " << response << endl;
			socket.close();
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

std::string handleRequest(std::string& request) {
	std::size_t delimPos = request.find(":");
	std::string error = "OK";

	if (delimPos != std::string::npos) 
	{
		std::string program = request.substr(0, delimPos);
		std::string command = request.substr(delimPos + 1);

		if (program.compare(radio.ID) == 0) 
		{
			radio.handleCommand(command, error);
			return error;
		}
		else
		{
			return "Command not found: " + program;
		}
	}
	else
	{
		if (request.compare("TYRONE-BROADCAST") == 0) 
		{
			return "ALIVE";
		}
		else if (request.compare("TEST") == 0) 
		{
			return header + "Client Request:  " + request + "\n" + 
						  + "Server Response: " + makeDaytimeString();
		}
		else 
		{
			return "Server command not found: '" + request + "'";
		}
	}
}