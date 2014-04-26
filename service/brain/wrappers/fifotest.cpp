#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
	std::cout << "Opening FIFO.\n";
	std::ofstream pandora("../../../proprietary/Pandora/ctl", std::ofstream::app);

	std::cout << "Writing command.\n";
	std::cin.get();
	pandora << "q";

	std::cout << "Closing.\n";
	pandora.close();

	return 0;
}