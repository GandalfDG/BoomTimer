#pragma once

#define PLAYER_COUNT_VERTICAL_POS 60 // for vertical placement of the player count on the background
#define PLAYER_COUNT_TEXT_HEIGHT 30 // for height of the text layer
#define PLAYER_BITMAP_ID RESOURCE_ID_TIMER_BACKGROUND

#define LABEL_TEXT_VERTICAL_POS 30
#define LABEL_TEXT_HEIGHT 50

#define CLICK_REPEAT_DELAY 150 // repeat delay in milliseconds
#define PLAYER_COUNT_MAX 99
#define PLAYER_COUNT_MIN 6

// window layer definitions
Window *player_select_window;
GBitmap *player_count_background_bitmap;
BitmapLayer *player_count_bitmap_layer;
TextLayer *player_count_text_layer;

TextLayer *round_number_text_layer;

void player_window_draw(void);

void initialize_player_count(int default_val);
int increment_player_count(void);
int decrement_player_count(void);
void save_player_count(void);
