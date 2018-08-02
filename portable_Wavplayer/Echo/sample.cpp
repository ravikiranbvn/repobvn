#include "sample.h"


Sampler::Sampler() : Generator() {
	smp = NULL;
	pos = 0;
}


Sampler::~Sampler() {
	if (smp) {
		destroy_sample(smp);
		smp = NULL;
	}
}


void Sampler::Load(const char *filename) {
	if (smp) {
		destroy_sample(smp);
		smp = NULL;
	}
	
	smp = load_sample(filename);
}


void Sampler::Play() {
	Generator::Play();
	pos = 0;
}


void Sampler::Stop() {
	Generator::Stop();
	pos = 0;
}


void Sampler::Process() {
	Generator::Process();

	// copy the next chunk of sample data to the output buffer
	if (playing && smp) {
		int len = smp->len - pos;
		len = MIN(len, BUFFER_SIZE);
		int i;
		
		for (i=0; i<len; i++, pos++) {
			// sample data needs to be converted from unsinged 8 bit format
			// signed floating point format - in an actual application this
			// step would have been performed at sample load time
			out[i] = (float)(((unsigned char *)smp->data)[pos] - 128);
		}
		
		// clear the rest of the buffer to 0
		for (; i<BUFFER_SIZE; i++) {
			out[i] = 0.0f;
		}

		if (pos >= smp->len) {
			Stop();
		}
	}
	// there's nothing to play -> clear the output buffer to 0
	else {
		for (int i=0; i<BUFFER_SIZE; i++) {
			out[i] = 0.0f;
		}
	}
}
