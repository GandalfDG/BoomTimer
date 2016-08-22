#include <pebble.h>

#define PLAYER_COUNT_DEFAULT 10

// the number of player, input on the player_select screen
int player_count;
int hostages;

// the number of hostages, based on current round and number of players
int hostage_array[5][5] = {
	{1, 1, 1, 0, 0},
	{1, 1, 2, 2, 2},
	{1, 1, 2, 2, 3},
	{1, 1, 2, 3, 4},
	{1, 2, 3, 4, 5}
};
		

// the number of rounds (either 3 or 5)
int round_count;
int rounds_left;

// persistance key enumeration
enum persist_keys {PLAYER_PERSIST, TIME_PERSIST};