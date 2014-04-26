#include <iostream>
#include <string>
#include <boost/asio.hpp>

#define BUF_LEN 50
#define PORT    8489

using boost::asio::ip::tcp;

int main() {
	using namespace std;
	std::string header = "This is a relay message from the server, which was sent: '";
	int bytesRead;
	//char buf[BUF_LEN];
	std::string buf = "";
	buf.resize(BUF_LEN);
	std::string finalMsg = "";

	try {
		boost::asio::io_service   ioServ;
		boost::system::error_code unimportantError;

		tcp::acceptor acceptor(ioServ, tcp::endpoint(tcp::v4(), PORT));

		cout << "Bound to port " << PORT << "\n";

		while (true) {
			tcp::socket socket(ioServ);
			acceptor.accept(socket);
			cout << "Created connection.\n";

			finalMsg = "";
			buf.empty();
			
			do {
				bytesRead = boost::asio::read(socket, boost::asio::buffer(buf), buf.length());
				finalMsg.append(buf);
			}
			while (bytesRead != 0);

			boost::asio::write(socket, boost::asio::buffer(header + finalMsg + "'\n"), unimportantError);
			cout << "Sent response.\n";
		}
	}
	catch (std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}