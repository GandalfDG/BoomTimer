#pragma once

#define TIMER_BITMAP_ID TIMER_BACKGROUND_BITMAP
#define TIMER_VERTICAL_POS 60
#define TIMER_TEXT_HEIGHT 60
#define INFO_VERTICAL_POS 30
#define INFO_TEXT_HEIGHT 40

int timer_seconds;
bool timer_running;

GFont boom_font_60;
GFont boom_font_40;

Window *timer_window;
GBitmap *timer_background_bitmap;
BitmapLayer *timer_bitmap_layer;
TextLayer *timer_text;
TextLayer *round_text;
TextLayer *hostage_text;
