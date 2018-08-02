#ifndef		AUDIOBASE_H
#define		AUDIOBASE_H

#include <allegro.h>
#include <string.h>
#include <vector>

// Number of samples in each buffer. A larger buffer will cause more
// latency, but a too small buffer can cause the sound to stutter. At
// 22kHz a 1k buffer corresponds to ~46 ms.
#define BUFFER_SIZE 1024

// Sampling freaquency for our audio stream. 
#define SAMPLING_FREQUENCY 22050

// Base class for all audio modules. All processing and mixing is done
// in floating point accuracy, with signed values for samples. Each
// machine can have an arbitrary number of inputs and can connect to
// an arbitrary number of outputs. When connecting machines, special
// care should be taken to avoid making closed loops.
class Machine {
	protected:
		// output buffer - machines to which this machine connects
		// will read their input data from this buffer; only applicable
		// for machines that actually produce output
		float *out;
	
		// input buffer - outputs from all input machines will be mixed
		// into this buffer, processed and written to the output buffer;
		// only applicable for machines that have input
		float *in;
	
		// an array of input machines for this machine
		std::vector<Machine *> inputs;
	
		// clears the input buffer
		void ClearInputBuffer();
	
	public:
		Machine();
		virtual ~Machine();
	
		// mix sound data into the input buffer
		void Input(float *in);
	
		// process input sound
		virtual void Process();		
	
		// return output sound
		float *Output();
	
		// connect an input machine
		void Connect(Machine *m);
};


// base class for all generators
class Generator : public Machine {
	protected:
		bool playing;
	
	public:
		Generator();
		~Generator();
	
		virtual void Play();
		virtual void Stop();
};


// base class for all effects - nothing special so far
class Effect : public Machine {
	public:
		Effect();
		~Effect();
};

 
#endif		//AUDIOBASE_H
