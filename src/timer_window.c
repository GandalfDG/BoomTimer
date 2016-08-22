#include <pebble.h>
#include "timer.h"
#include "common.h"


void timer_window_init(Window *window) {
	// get a GRect "bounds" that is a bounding box for the window
	Layer *window_layer = window_get_root_layer(timer_window);
	GRect bounds = layer_get_bounds(window_layer);
	
	// load the custom fonts
	boom_font_60 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_BOOM_FONT_60));
	boom_font_40 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_BOOM_FONT_40));
	
	// initialize the background bitmap
	timer_background_bitmap = gbitmap_create_with_resource(TIMER_BITMAP_ID); // change this in timer.h
	timer_bitmap_layer = bitmap_layer_create(bounds);
	bitmap_layer_set_bitmap(timer_bitmap_layer, timer_background_bitmap);
	
	// initialize timer text layer
	timer_text = text_layer_create(GRect(0, TIMER_VERTICAL_POS, 
																										bounds.size.w, TIMER_TEXT_HEIGHT));
	text_layer_set_background_color(timer_text, GColorClear);
	text_layer_set_text_color(timer_text, GColorWhite);
	text_layer_set_font(timer_text, *boom_font_60);
	text_layer_set_text_alignment(timer_text, GTextAlignmentCenter);
	// for testing
	text_layer_set_text(timer_text, "04:59\n");
	
	
	
}

void timer_window_deinit(Window *window) {
	text_layer_destroy(timer_text);
	bitmap_layer_destroy(timer_bitmap_layer);
	gbitmap_destroy(timer_background_bitmap);
  window_destroy(timer_window);
}

void player_window_draw(void) {
	player_select_window = window_create();
	window_set_window_handlers(player_select_window,
			(WindowHandlers) {.load = timer_window_init,
												.unload = timer_window_deinit});
		
	// display the window
  window_stack_push(player_select_window, true);
}
