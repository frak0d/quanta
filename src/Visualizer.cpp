#pragma once

#include <cmath>
#include <cstdio>
#include <string>
#include <cstdint>
#include <memory>

#include <fftw3.h>

bool wisdom_imported = fftwf_import_wisdom_from_filename("assets/fftw_wisdom");

inline void addColorCode(std::string& str, uint8_t R, uint8_t G, uint8_t B)
{
	str = str + "\x1b[38;2;"
		+ std::to_string(R) + ';'
		+ std::to_string(G) + ';'
		+ std::to_string(B) + 'm';
}

inline void rstColorCode(std::string& str)
{
	str += "\x1b[0m";
}

class Visualizer
{
private:
	fftwf_plan fft_plan;
	int srate, ssize, average, bins;
	float maxout;
	std::unique_ptr<fftwf_complex[]> buf_out;

public:
	std::string getAscii(float* buf_in, bool color=true);
	
	Visualizer(int sr, int ss, int avg):
		srate(sr), ssize(ss), average(avg), bins(ss/2),
		buf_out(new fftwf_complex[ss]()){};
};

// Learn about FFTs at :-
// https://stackoverflow.com/a/54007677/14976549

std::string Visualizer::getAscii(float* buf_in, bool color)
{
	fft_plan = fftwf_plan_dft_r2c_1d(ssize, buf_in, buf_out.get(), FFTW_EXHAUSTIVE);
	fftwf_execute(fft_plan); fftwf_destroy_plan(fft_plan);
	
	// FFTs have midpoint symmetry
	// so only first half is useful
	// thats why bins = ssize/2
	
	float* output = new float[bins]();
	float maxout_current = 0;
	
	for (int i=0 ; i < bins ; ++i)
	{
		// Magnitude of Complex FFT
		output[i] = std::sqrt(std::pow(buf_out[i][0], 2)
							 +std::pow(buf_out[i][1], 2));

		// Needed later for normalizing
		if (output[i] > maxout_current) maxout = output[i];
	}

	// Normalizing
	maxout = 0.5f * (maxout+maxout_current);
	
	float fak = 1/maxout; // mult is faster than div
	
	for (int i=0 ; i < bins ; ++i)
	{
		// Normalize from 0 to 1
		output[i] = output[i] * fak;
	}
	
	// Generating the actual Visualizer //
	
	std::string viz = "\x1b[s";
	
	for (int i=-2 ; i < bins ; ++i) viz += '-';
	viz += "\x1b[u\x1b[B";
	
	for (int h=20 ; h > 0 ; --h)
	{
		viz += '|';
		
		for (int i=0 ; i < bins ; ++i)
		{
			if (30*output[i] >= h)
			{
				if (color) addColorCode(viz, 5*(20-h), 10*h, 12*(20-h));
				viz += "█";
				if (color) rstColorCode(viz);
			}
			else viz += ' ';
		}
		
		viz += "|\x1b[u\x1b[" + std::to_string(20-h) + "B";
	}
	for (int i=-2 ; i < bins ; ++i) viz += '-';
	
	delete[] output;
	return viz;
}
