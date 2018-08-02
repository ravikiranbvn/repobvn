#include "echo.h"


Echo::Echo() : Effect() {
	history = NULL;
	SetDelay(200);		// default delay is 200ms
	SetAmp(128);		// default amplification is 50%
	pos = 0;
}


Echo::~Echo() {
	delete [] history;
	history = NULL;
}


void Echo::SetDelay(int ms) {
	// calculate number of samples needed for history
	int newDelay = ms * SAMPLING_FREQUENCY / 1000;
	
	// create new history buffer
	float *newHistory = new float[newDelay];
	for (int i=0; i<newDelay; i++) {
		newHistory[i] = 0.0f;
	}

	// if there already is a history buffer, fill the new one with
	// old data (might not work right in all situations)
	if (history) {
		int howMuch = delay-pos;
		howMuch = MIN(howMuch, newDelay);
		for (int i=0, j=pos; i<howMuch; i++, j++) {
			newHistory[i] = history[j];
		}
		if (howMuch < newDelay) {
			int i=howMuch;
			howMuch = newDelay - howMuch;
			howMuch = MIN(howMuch, delay);
			howMuch = MIN(howMuch, pos);
			for (int j=0; j<howMuch; i++, j++) {
				newHistory[i] = history[j];
			}
		}
		delete [] history;
		
	}
	
	// remember new values
	history = newHistory;
	pos = 0;
	delay = newDelay;
	this->ms = ms;
}


// amp is in [0, 256] where 0 means no echoes and 256 means infinite echoes
void Echo::SetAmp(int amp) {
	this->amp = amp;
	f_amp = (float)amp/256.0f;
}


int Echo::GetDelay() {
	return ms;
}


int Echo::GetAmp() {
	return amp;
}


// do the echo effect
void Echo::Process() {
	Effect::Process();
	
	// mix each sample in the input buffer with the appropriately
	// delayed and amplified sample in the history buffer
	float smp;
	for (int i=0; i<BUFFER_SIZE; i++, pos++) {
		// wrap around in the history buffer
		if (pos >= delay) {
			pos = 0;
		}
		
		smp = history[pos];			// read sample from history
		smp *= f_amp;				// amplify
		smp += in[i];				// add to the matching sample from the input buffer
		out[i] = smp;				// write sample to output
		history[pos] = smp;			// write sample to the history buffer
	}
}
