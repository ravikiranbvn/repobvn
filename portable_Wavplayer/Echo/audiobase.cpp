#include "audiobase.h"


Machine::Machine() {
	// create input and output buffers and fill them with zeroes
	out = new float[BUFFER_SIZE];
	in = new float[BUFFER_SIZE];

	for (int i=0; i<BUFFER_SIZE; i++) {
		in[i] = 0.0f;
		out[i] = 0.0f;
	}
}


Machine::~Machine() {
	delete [] out;
	delete [] in;
}


// fills the input buffer with zeroes - called after processing the input
// data to initialize the input buffer for the next time
void Machine::ClearInputBuffer() {
	for (std::vector<Machine *>::iterator i = inputs.begin(); i != inputs.end(); ++i) {
		Machine *m = *i;
		m->ClearInputBuffer();
	}

	for (int i=0; i<BUFFER_SIZE; i++) {
		in[i] = 0.0f;
	}
}


// mixes a buffer of sound with the input buffer - assumes the input
// buffer has been cleared before mixing starts
void Machine::Input(float *in_) {
	for (int i=0; i<BUFFER_SIZE; i++) {
		in[i] += in_[i];
	}
}


// processes the input buffer and stores the results in the output buffer
void Machine::Process() {
	// for each input machine
	for (std::vector<Machine *>::iterator i = inputs.begin(); i != inputs.end(); ++i) {
		Machine *m = *i;
		
		// process the input first
		m->Process();
		
		// mix the input machine's output with the input buffer
		Input(m->Output());
	}
}


float *Machine::Output() {
	return out;
}


void Machine::Connect(Machine *m) {
	inputs.push_back(m);
}


Generator::Generator() : Machine(), playing(false) {
}


Generator::~Generator() {
	Stop();
}


void Generator::Play() {
	playing = true;
}


void Generator::Stop() {
	playing = false;
}


Effect::Effect() : Machine() {
}


Effect::~Effect() {
}
