#include <pebble.h>


/* Check if there is currently a timer running, or if a game is in progress
if so, resume the timer/game. If not, check if there is a player number stored
from a previous game, and if so initialize the player count with that. If not,
launch the player select screen with a default value */

int main(void) {
	// check if a timer is in progress, or if a timer has woken the app
	
	// if not, put the last value of player_count in as the default
	player_window_draw();
	if(persist_exists(PLAYER_PERSIST))
		initialize_player_count(persist_read_int(PLAYER_PERSIST));
	else
		initialize_player_count(PLAYER_COUNT_DEFAULT);
	
	app_event_loop();
	
	return 0;
}