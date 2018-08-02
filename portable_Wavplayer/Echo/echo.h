#ifndef		ECHO_H
#define		ECHO_H

#include "audiobase.h"

// A simple echo (or delay) class. Stores just enough history data
// and mixes it with the input. History data is amplified with values
// less than 1 to produce echoes.
class Echo : public Effect {
	private:
		float *history;	// history buffer
		int pos;		// current position in history buffer
		int amp;		// amplification of echoes (0-256)
		int delay;		// delay in number of samples
		int ms;			// delay in miliseconds
	
		float f_amp;	// amplification (0-1)
	
	public:
		Echo();
		~Echo();
		
		void SetDelay(int ms);
		void SetAmp(int amp);
		int GetDelay();
		int GetAmp();
		void Process();
};


#endif		//ECHO_H
