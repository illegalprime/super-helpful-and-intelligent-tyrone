#include <string>

class Wrapper {
public:
	virtual void handleCommand(std::string&, std::string&) = 0;
	const char* ID;
};