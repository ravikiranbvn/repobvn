#include "master.h"

Master::Master() : Machine() {
	// Start playing an audiostream. 8 bit, 22kHz, mono for sake of
	// simplicity. Should be 16 bit, 44kHz, stereo in the final product.
	stream = play_audio_stream(BUFFER_SIZE, 8, FALSE, SAMPLING_FREQUENCY, 255, 128);
}


Master::~Master() {
	stop_audio_stream(stream);
}


// This should be called at regular intervals. Queries whether the underlying
// audiostream requires its buffer to be updated and if it does, it updates
// it by mixing in the outputs from all the input machines.
void Master::Process() {
	// does audiostream need its buffer updated with new data?
	unsigned char *buf = (unsigned char *)get_audio_stream_buffer(stream);

	if (buf) {
		// process all input machines
		Machine::Process();
		
		// clear the audiostream buffer (unsinged values, 128 is 0 DC)
		memset(buf, 128, BUFFER_SIZE);

		// copy the input buffer over to the audiostream buffer, converting
		// the data to the appropriate format along at the same time
		for (int i=0; i<BUFFER_SIZE; i++) {
			// each sample is converted to unsigned format and clipped to [0,255]
			buf[i] = MID(0, (int)in[i]+0x7f, 0xff);
		}

		// let the audiostream know it got new data to play
		free_audio_stream_buffer(stream);
		
		// clear the input buffer to prepare for the next "frame"
		ClearInputBuffer();
	}
}
