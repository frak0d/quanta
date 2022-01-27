#include <cmath>
#include <cstdio>
#include <thread>
#include <string>
#include <cstdint>

#include <fftw3.h>

using std::sin, std::cos, std::tan,
      std::log, std::exp, std::abs,
      std::pow, std::sqrt;

int main()
{
	int srate   = 32000;
	int samples = 100;
	int bin_sz  = srate/samples;
	
	float input[samples] = {};

	// Creating Sample Data
	for (int i=0 ; i < samples ; ++i)
	{
		input[i] += sin(i)    * 10.f;
		input[i] += sin(i+69) * 20.f;
	}
	
	fftwf_complex input_fft[samples] = {};
	
	fftwf_import_wisdom_from_filename("assets/fftw_wisdom");
	auto plan = fftwf_plan_dft_r2c_1d(samples, input, input_fft, FFTW_EXHAUSTIVE);
	fftwf_execute(plan); fftwf_destroy_plan(plan);
	
	// FFTs have midpoint symmetry
	// so only first half is useful
	float output[samples/2] = {};
	float maxout = 0;
	
	for (int i=0 ; i < samples/2 ; ++i)
	{
		// Magnitude of Complex FFT
		output[i] = sqrt(pow(input_fft[i][0], 2)
						+pow(input_fft[i][1], 2));

		// Needed later for normalizing
		if (output[i] > maxout) maxout = output[i];
	}

	float fak = 1/maxout; // mult is faster than div
	
	for (int i=0 ; i < samples/2 ; ++i)
	{
		// Normalize from 0 to 1
		output[i] = output[i] * fak;

		// Print Out
		printf("(%dhz - %dhz) => %f\n", bin_sz*i, bin_sz*(i+1), output[i]);
	}
}

// Learn about FFTs at :-
// https://stackoverflow.com/a/54007677/14976549
