#include <pebble.h>
#include "select.h"
#include "common.h"

TextLayer *label_text;
static void update_round(void) {
	static char round[2];
	snprintf(round, 2, "%d\n", round_count);
	text_layer_set_text(round_number_text_layer, round);
}

// click handler callbacks
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	// increment the player count if setting player count
	if(!layer_get_hidden(text_layer_get_layer(player_count_text_layer)))
		increment_player_count();
	else {
		round_count = 5;
		update_round();
	}
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	if(!layer_get_hidden(text_layer_get_layer(player_count_text_layer)))
		decrement_player_count();
	else {
		round_count = 3;
		update_round();
	}
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	// when setting players, if 6-10 advance to timer and rounds = 3
	if(player_count >= 6 && player_count <= 10) {
		round_count = 3;
		// draw timer window
	}
	// otherwise advance from players to rounds
	else if(!layer_get_hidden(text_layer_get_layer(player_count_text_layer))) {
		layer_set_hidden(text_layer_get_layer(player_count_text_layer), true);
		layer_set_hidden(text_layer_get_layer(round_number_text_layer), false);
		text_layer_set_text(label_text, "Rounds:\n");
	}
	// else draw timer window
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
	// if setting rounds, go back to setting players
	if(!layer_get_hidden(text_layer_get_layer(round_number_text_layer))) {
		layer_set_hidden(text_layer_get_layer(player_count_text_layer), false);
		layer_set_hidden(text_layer_get_layer(round_number_text_layer), true);
		text_layer_set_text(label_text, "Players:\n");
	}
	// otherwise exit the app
	else
		window_stack_remove(player_select_window, true);	
}

// button click configuration
static void config_provider(Window *window) {
	window_single_repeating_click_subscribe(BUTTON_ID_UP, CLICK_REPEAT_DELAY, up_click_handler);
	window_single_repeating_click_subscribe(BUTTON_ID_DOWN, CLICK_REPEAT_DELAY, down_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);
}

void player_select_init(Window *window) {
	// get a GRect "bounds" that is a bounding box for the window
	Layer *window_layer = window_get_root_layer(player_select_window);
	GRect bounds = layer_get_bounds(window_layer);
	
	// load the custom font
	boom_font_60 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_BOOM_FONT_60));
	
	// initialize the background bitmap
	player_count_background_bitmap = gbitmap_create_with_resource(PLAYER_BITMAP_ID); // change this in player_select.h
	player_count_bitmap_layer = bitmap_layer_create(bounds);
	bitmap_layer_set_bitmap(player_count_bitmap_layer, player_count_background_bitmap);
	
	// initialize the label text layer
	label_text = text_layer_create(GRect(0, LABEL_TEXT_VERTICAL_POS,
																			bounds.size.w, LABEL_TEXT_HEIGHT));
	text_layer_set_background_color(label_text, GColorClear);
	text_layer_set_text_color(label_text, GColorBlack);
	text_layer_set_text_alignment(label_text, GTextAlignmentCenter);
	text_layer_set_font(label_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text(label_text, "Players:\n");

	// initialize the player number text layer
  player_count_text_layer = text_layer_create(GRect(0, PLAYER_COUNT_VERTICAL_POS, 
																										bounds.size.w, PLAYER_COUNT_TEXT_HEIGHT)); // these are adjusted in player_select.h
	text_layer_set_background_color(player_count_text_layer, GColorClear);
	text_layer_set_text_color(player_count_text_layer, GColorBlack);
	text_layer_set_text_alignment(player_count_text_layer, GTextAlignmentCenter);
	text_layer_set_font(player_count_text_layer, boom_font_60);
	
	// initialize the round number text layer
	round_count = 3;
	round_number_text_layer = text_layer_create(GRect(0, PLAYER_COUNT_VERTICAL_POS, 
																										bounds.size.w, PLAYER_COUNT_TEXT_HEIGHT)); // these are adjusted in player_select.h
	text_layer_set_background_color(round_number_text_layer, GColorClear);
	text_layer_set_text_color(round_number_text_layer, GColorWhite);
	text_layer_set_text_alignment(round_number_text_layer, GTextAlignmentCenter);
	text_layer_set_text(round_number_text_layer, "3\n");
	layer_set_hidden(text_layer_get_layer(round_number_text_layer), true);
	
	// set up click handler for changing number of players
	window_set_click_config_provider(player_select_window, (ClickConfigProvider) config_provider);
	
	// construct layer heirarchy
	layer_add_child(window_layer, bitmap_layer_get_layer(player_count_bitmap_layer));
	layer_add_child(window_layer, text_layer_get_layer(player_count_text_layer));
	layer_add_child(window_layer, text_layer_get_layer(round_number_text_layer));
	layer_add_child(window_layer, text_layer_get_layer(label_text));
}

void player_select_deinit(Window *window) {
	text_layer_destroy(label_text);
	text_layer_destroy(round_number_text_layer);
  text_layer_destroy(player_count_text_layer);
	bitmap_layer_destroy(player_count_bitmap_layer);
	gbitmap_destroy(player_count_background_bitmap);
  window_destroy(player_select_window);
	save_player_count();
}

void player_window_draw(void) {
	player_select_window = window_create();
	window_set_window_handlers(player_select_window,
			(WindowHandlers) {.load = player_select_init,
												.unload = player_select_deinit});
		
	// display the window
  window_stack_push(player_select_window, true);
}
