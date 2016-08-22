#include <pebble.h>
#include "timer.h"
#include "common.h"


static int get_hostages() {
	if(player_count >= 6 && player_count <= 10)
		return hostage_array[0][round_count];
	else if(player_count <= 13)
		return hostage_array[1][round_count];
	else if(player_count <= 17)
		return hostage_array[2][round_count];
	else if(player_count <= 21)
		return hostage_array[3][round_count];
	else 
		return hostage_array[4][round_count];
}

void set_timer() {
	timer_seconds = 60 * round_count--; // set the time and decrement the round count
	hostages = get_hostages();
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