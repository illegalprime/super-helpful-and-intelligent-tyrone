#include <string>
#include <map>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include "./wrapper.hpp"

#define ctlFIFO "../../proprietary/Pandora/ctl"

using namespace std;

class PandoraRadio : public Wrapper {
public:
	const char* ID;

	PandoraRadio() {
		ID = "PANDORA";
	}

	void handleCommand(std::string& comm, std::string& output) {
		try {
		if (radioProcess != NULL) {
			if (comm.compare("TOGGLE") == 0) {
				sendToFIFO('p');
			}
			else if (comm.compare("PLAY") == 0) {
				sendToFIFO('P');
			}
			else if (comm.compare("PAUSE") == 0) {
				sendToFIFO('S');
			}
			else if (comm.compare("LIKE") == 0) {
				sendToFIFO('+');
			}
			else if (comm.compare("DISLIKE") == 0) {
				sendToFIFO('-');
			}
			else if (comm.compare("BOOKMARK") == 0) {
				sendToFIFO('b');
			}
			else if (comm.compare("NEXT") == 0) {
				sendToFIFO('n');
			}
			else if (comm.compare("CHANGE_STATION") == 0) {
				sendToFIFO('s');
			}
			else if (comm.compare("VOLUP") == 0) {
				sendToFIFO(')');	
			}
			else if (comm.compare("VOLDOWN") == 0) {
				sendToFIFO('(');
			}
			else if (comm.compare("VOL0") == 0) {
				sendToFIFO('^');
			}
			else if (comm.compare("TIRED") == 0) {
				sendToFIFO('t');
			}
			else if (comm.compare("QUIT") == 0) {
				stopRadio();
			}
			else if (comm.compare("START") == 0) {
				output = "Pandora is already on.";
			}
			else {
				output = "'" + comm + "' is not a command.";
			}
		}
		else {
			if (comm.compare("START") == 0 && radioProcess == NULL) {
				startRadio();
			}
			else {
				output = "Pandora is not on.";
			}
		}
		} catch (std::exception& err) {  
			output = err.what();  
			output = "Error: " + output;
		}
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
		pandoraCtl.flush();
	}
};