#include <pebble.h>
#include "timer.h"

void set_timer() {
	timer_seconds = 60 * round_count--; // set the time and decrement the round count
}

void start_timer() {
	timer_running = true;
}

void stop_timer() {
	timer_running = false;
}

// refresh the time text
void update_timer_text() {
	int minutes = timer_seconds / 60;
	int seconds = timer_seconds % 60;
	static char time[6];
	
	snprintf(time, 6, "%02d:%02d", minutes, seconds);
	
	text_layer_set_text(timer_text, time);
}

// if the timer is running decrement, if the timer runs out -1 is returned
int time_tick() {
	if(timer_running) {
		timer_seconds--;
		update_timer_text();
		if(timer_seconds <= 0) {
			stop_timer();
			return -1; // the time has run out	
		}
	}
	return 0;
}