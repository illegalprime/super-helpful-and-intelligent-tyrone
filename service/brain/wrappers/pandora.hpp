#include <string>
#include <map>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include "./wrapper.hpp"

#define ctlFIFO "../../../proprietary/Pandora/ctl"

class PandoraRadio : public Wrapper {
public:
	bool handleCommand(std::string& comm) {
		if (comm == "START" && radioProcess == NULL) {
			startRadio();
		}
		else if (comm == "QUIT" && radioProcess != NULL) {
			stopRadio();
		}
		else {
			if (comm == "PAUSE" || comm == "PLAY") {
				sendToFIFO('p');
			}
			else if (comm == "LIKE") {
				sendToFIFO('+');
			}
			else if (comm == "DISLIKE") {
				sendToFIFO('-');
			}
			else if (comm == "BOOKMARK") {
				sendToFIFO('b');
			}
			else if (comm == "NEXT") {
				sendToFIFO('n');
			}
		}
		return true;
	}

private:
	std::ofstream pandoraCtl;
	FILE* radioProcess = NULL;

	void startRadio() {
		radioProcess = popen("pianobar", "r");
		pandoraCtl.open(ctlFIFO, std::ofstream::app);
	}

	void stopRadio() {
		sendToFIFO('q');
		pandoraCtl.close();
		pclose(radioProcess);
		radioProcess = NULL;
	}

	void sendToFIFO(char comm) {
		pandoraCtl << comm;
	}
};

/*
int main() {
	PandoraRadio radio;
	std::string comm = "START";

	radio.handleCommand(comm);

	std::cin.get();

	comm = "QUIT";
	radio.handleCommand(comm);

	return 0;
}
*/