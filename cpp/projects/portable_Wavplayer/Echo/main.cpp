#include "audiobase.h"
#include "master.h"
#include "sample.h"
#include "echo.h"


int main() {
	allegro_init();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 240, 0, 0);
	install_keyboard();
	install_sound(DIGI_AUTODETECT, 0, 0);
	
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

	Sampler smp;
	smp.Load("welcome.wav");
	
	Echo echo;
	echo.Connect(&smp);
	
	Master master;
	master.Connect(&echo);

	while (!key[KEY_ESC]) {
		while (keypressed()) {
			int c = readkey()>>8;
			
			switch (c) {
				case KEY_SPACE:		smp.Play();		break;
			}
		}
		
		master.Process();
	}

	destroy_bitmap(buffer);
	
	return 0;
}
END_OF_MAIN()
