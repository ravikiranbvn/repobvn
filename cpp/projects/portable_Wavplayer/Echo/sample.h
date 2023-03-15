#ifndef		SAMPLE_H
#define		SAMPLE_H

#include "audiobase.h"

// A simple sampler module. Just loads one sample and plays it on demand.
// Assumes the sample is 8 bit, mono and sampled at the same sampling rate
// as the output sampling rate. A real-life application would either convert
// all loaded samples to the same uniform format or perform the necessary
// conversions on the fly.
class Sampler : public Generator {
	private:
		SAMPLE *smp;
		int pos;
	
	public:
		Sampler();
		~Sampler();
		
		void Load(const char *filename);
		void Play();
		void Stop();
		void Process();
};


#endif		//SAMPLE_H
