#include <pebble.h>
#include "select.h"
#include "common.h"

static void update_text(void);

/* sets the initial value on the player select screen.
if there was persistent saved data, this will be the initial value.
otherwise, the main program sets a default value. */
void initialize_player_count(int default_val) {
	player_count = default_val;
	update_text();
}

/* when the up button is pressed, the player count will be incremented. 
-1 will be returned if the player count exceeds the max. */
int increment_player_count(void) {
	if(player_count >= PLAYER_COUNT_MAX)
		return -1;
	
	player_count++;
	update_text();
	return 0;
}

/* when the down button is pressed, the player count will be decremented.
-1 will be returned if the player count would be below the minimum. */
int decrement_player_count(void) {
	if(player_count <= PLAYER_COUNT_MIN)
		return -1;
	
	player_count--;
	update_text();
	return 0;
}

static void update_text(void) {
	static char player_count_text[3]; // maximum of 2 digits
	snprintf(player_count_text, 3, "%02d\n", player_count);
	text_layer_set_text(player_count_text_layer, player_count_text);
}

void save_player_count(void) {
	persist_write_int(PLAYER_PERSIST, player_count);
}