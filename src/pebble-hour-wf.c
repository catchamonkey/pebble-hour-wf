#include <pebble.h>

#define DEBUG true

static Window *s_main_window;
static Layer *s_canvas_layer;
static TextLayer *s_time_layer;

static GColor get_color_from_minute(uint8_t minute) {
  uint8_t argb = GColorBlackARGB8 + minute + 1;

  if (argb >= GColorDarkGrayARGB8) { argb++; }
  if (argb >= GColorLightGrayARGB8) { argb++; }

  return (GColor8){ .argb = argb };
}

/**
 * Gets colour to use for font, based on the best choice matching the given bgcolor
 * http://stackoverflow.com/questions/946544/good-text-foreground-color-for-a-given-background-color/946734#946734
 *
 * @param  GColor bgcolor
 * @return GColor
 */
static GColor get_fgcolor_for_bgcolor(GColor bgcolor) {
  uint8_t r, g, b;
  r = (bgcolor.argb & 0b110000) >> 4;
  g = (bgcolor.argb & 0b001100) >> 2;
  b = bgcolor.argb & 0b000011;
  uint16_t brightness = r*299 + g*587 + b*114;
  return brightness < 1750 ? GColorWhite : GColorBlack;
}

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00";

  // Write the current hours and minutes into the buffer
  if (clock_is_24h_style()) {
    strftime(buffer, sizeof("00"), "%H", tick_time);
  } else {
    strftime(buffer, sizeof("00"), "%I", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changes) {
  update_time();
  // update_bg();
  // we could actually offer an option so you can choose how minutes are presented
  // either 0-100% BG fill, or a radial 0-360 degrees, same way a minute hand does, but filling colour
}

static GColor8 bgcolor;
static GColor8 fgcolor;

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);
  // Get the center of the screen (non full-screen)
  GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));

  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  uint8_t color_index = DEBUG ? tick_time->tm_sec : tick_time->tm_min;

  bgcolor = get_color_from_minute(color_index);
  graphics_context_set_fill_color(ctx, bgcolor);


  fgcolor = get_fgcolor_for_bgcolor(bgcolor);
  text_layer_set_text_color(s_time_layer, fgcolor);

  // Draw a circle
  // int radius = (bounds.size.w/2/60)*color_index;
  // graphics_fill_circle(ctx, center, radius);

  // Or draw a rect
  int width = (bounds.size.w/60.0) * color_index;
  graphics_fill_rect(ctx, GRect(0, 0, width, bounds.size.h), 0, GCornerNone);

  // Or to make the rect grow from the centre.
  // x offset should be half the screen, minus, half the width of the rect
  // int x_offset = (bounds.size.w/2) - (width/2);


  // Or leave rect as full width, then adjust x offset to move into view until fully in
  // int x_offset = (0 - bounds.size.w) + (bounds.size.w / 60) * color_index;
  // int x_offset = (0 - bounds.size.w) + (bounds.size.w);
  // x_offset = ceil(x_offset);

  // graphics_fill_rect(ctx, GRect(x_offset, 0, bounds.size.w, bounds.size.h), 0, GCornerNone);
}

static void main_window_load(Window *window) {
  // Get the root layer
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create Layer
  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, s_canvas_layer);

  window_set_background_color(s_main_window, GColorDarkGray);

  // Set the update_proc
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);

  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

  update_time();
}

static void main_window_unload(Window *window) {
  // Destroy the text layer
  text_layer_destroy(s_time_layer);
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);

  // Register with TickTimerService, only update when the minute changes (unless debug is enabled)
  TimeUnits update_freq = DEBUG ? SECOND_UNIT : MINUTE_UNIT;
  tick_timer_service_subscribe(update_freq, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
