#include <pebble.h>

#define PLAYER_COUNT_DEFAULT 10

// the number of player, input on the player_select screen
int player_count;

// the number of rounds (either 3 or 5)
int round_count;
int rounds_left;

// persistance key enumeration
enum persist_keys {PLAYER_PERSIST, TIME_PERSIST};