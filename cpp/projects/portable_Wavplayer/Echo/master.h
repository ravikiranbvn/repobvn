#ifndef		MASTER_H
#define		MASTER_H

#include "audiobase.h"

// Master audio module for all Allegro AUDIOSTREAM mixing. There should be
// one Master in a program to which all sound generators should be connected
// either directly or through effects. The master writes output to an Allegro
// audiostream which is created in the constructor and destoryed in the
// destructor. The Process method should be called in regular intervals.
class Master : public Machine {
	private:
		AUDIOSTREAM *stream;
	
	public:
		Master();
		~Master();
	
		void Process();
};

#endif		//MASTER_H
