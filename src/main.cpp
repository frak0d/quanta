#include <cmath>
#include <cstdio>
#include <thread>
#include <string>
#include <cstdint>
#include <iostream>

#include "Visualizer.cpp"
#include <IXWebSocketServer.h>

int main()
{
	ix::WebSocketServer server;
	
	int srate   = 32000;
	int samples = 100;
	
	float input[samples] = {};

	// Creating Sample Data
	for (int i=0 ; i < samples ; ++i)
	{
		input[i] += std::cos(i)    * 10.f;
		input[i] += std::sin(i+69) * 20.f;
	}

	Visualizer myViz(srate, samples, 10);
	std::cout << myViz.getAscii(input);
}
