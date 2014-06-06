#include <iostream>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 128

int main() {
	using namespace std;

	FILE* radioProcess = popen("pianobar", "r");
	char buffer[BUF_SIZE];

	while (read(&radioProcess, buffer, BUF_SIZE)) {
		cout << buffer;
	}
	return 0;
}