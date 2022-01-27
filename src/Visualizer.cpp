#pragma once

#include <cmath>
#include <cstdio>
#include <string>
#include <cstdint>
#include <memory>

#include <fftw3.h>

auto __useless__ = fftwf_import_wisdom_from_filename("assets/fftw_wisdom");

class Visualizer
{
private:
	fftwf_plan fft_plan;
	int srate, ssize, average, bins;
	float bin_sz;
	std::unique_ptr<fftwf_complex[]> buf_out;

public:
	std::string getAscii(float* buf_in, bool color=true);
	
	Visualizer(int sr, int ss, int avg):
		srate(sr), ssize(ss), average(avg),
		bins(ss/2), bin_sz((float)sr/ss),
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
	
	float output[bins] = {};
	float maxout = 0;
	
	for (int i=0 ; i < bins ; ++i)
	{
		// Magnitude of Complex FFT
		output[i] = std::sqrt(std::pow(buf_out[i][0], 2)
							 +std::pow(buf_out[i][1], 2));

		// Needed later for normalizing
		if (output[i] > maxout) maxout = output[i];
	}

	float fak = 1/maxout; // mult is faster than div
	
	for (int i=0 ; i < bins ; ++i)
	{
		// Normalize from 0 to 1
		output[i] = output[i] * fak;

		//printf("(%.2fhz) => %f\n", 0.5*(bin_sz*i + bin_sz*(i+1)), output[i]);
	}
	
	// Generating the actual Visualizer //
	
	std::string viz;
	viz.reserve(20*(2*bins+1));

	viz += "-------------------------------\n";
	for (int h=20 ; h > 0 ; --h)
	{
		for (int i=0 ; i < bins ; ++i)
		{
			20*output[i] >= h ? viz += "█"
							  : viz += ' ';
		}
		
		viz += '\n';
	}
	viz += "-------------------------------\n";
	
	return viz;
}
