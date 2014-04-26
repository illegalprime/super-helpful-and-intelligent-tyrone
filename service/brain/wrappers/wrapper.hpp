#include <string>

class Wrapper {
public:
	virtual bool handleCommand(std::string&) = 0;
};