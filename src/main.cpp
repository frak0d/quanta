#include <cmath>
#include <chrono>
#include <cstdio>
#include <thread>
#include <string>
#include <cstdint>
#include <csignal>
#include <iostream>
#include <unistd.h>

#include "Visualizer.cpp"
#include <IXWebSocketServer.h>

// SIGNAL HANDLERS //

void interrupt_handler(int signal)
{
	std::puts("\x1b[0m\x1b[H\x1b[2J\x1b[3J");
	std::puts("\n\x1b[31;1m => Interrrupt Recieved, Exiting...\x1b[0m\n");
	std::exit(-1);
}

void segfault_handler(int signal)
{
	std::puts("\x1b[0m\x1b[H\x1b[2J\x1b[3J");
	std::puts("\n\x1b[31;1m => Segmentation Fault, Exiting...\x1b[0m\n");
	std::exit(-4);
}

int main()
{
	std::signal(SIGINT, interrupt_handler);
	std::signal(SIGSEGV, segfault_handler);
	
	int srate   = 32000;
	int samples = 132;
	
	float* input = new float[samples]();
	Visualizer myViz(srate, samples, 10);
	
	int k = 1000;
	while (--k)
	{
		for (int i=0 ; i < samples ; ++i)
		{
			input[i] += std::cos(i)   * i;
			input[i] += std::sin(i+9) * (samples-k);
			if (k % i == 0) input[i] += k-i;
		}
		usleep(25000);
		std::cout << "\x1b[3J\x1b[4;4H" << myViz.getAscii(input);
	}
	
	delete[] input;
}
