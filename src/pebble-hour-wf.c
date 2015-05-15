#include <pebble.h>

static Window *s_main_window;
static Layer *s_canvas_layer;
static TextLayer *s_time_layer;

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

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);
  // Get the center of the screen (non full-screen)
  // GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));

  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  int minute = tick_time->tm_min;

  if (minute == 0) { graphics_context_set_fill_color(ctx, GColorBlack); }
  if (minute == 1) { graphics_context_set_fill_color(ctx, GColorOxfordBlue); }
  if (minute == 2) { graphics_context_set_fill_color(ctx, GColorDukeBlue); }
  if (minute == 3) { graphics_context_set_fill_color(ctx, GColorBlue); }
  if (minute == 4) { graphics_context_set_fill_color(ctx, GColorDarkGreen); }
  if (minute == 5) { graphics_context_set_fill_color(ctx, GColorMidnightGreen); }
  if (minute == 6) { graphics_context_set_fill_color(ctx, GColorCobaltBlue); }
  if (minute == 7) { graphics_context_set_fill_color(ctx, GColorBlueMoon); }
  if (minute == 8) { graphics_context_set_fill_color(ctx, GColorIslamicGreen); }
  if (minute == 9) { graphics_context_set_fill_color(ctx, GColorJaegerGreen); }
  if (minute == 10) { graphics_context_set_fill_color(ctx, GColorTiffanyBlue); }
  if (minute == 11) { graphics_context_set_fill_color(ctx, GColorVividCerulean); }
  if (minute == 12) { graphics_context_set_fill_color(ctx, GColorGreen); }
  if (minute == 13) { graphics_context_set_fill_color(ctx, GColorMalachite); }
  if (minute == 14) { graphics_context_set_fill_color(ctx, GColorMediumSpringGreen); }
  if (minute == 15) { graphics_context_set_fill_color(ctx, GColorCyan); }
  if (minute == 16) { graphics_context_set_fill_color(ctx, GColorBulgarianRose); }
  if (minute == 17) { graphics_context_set_fill_color(ctx, GColorImperialPurple); }
  if (minute == 18) { graphics_context_set_fill_color(ctx, GColorIndigo); }
  if (minute == 19) { graphics_context_set_fill_color(ctx, GColorElectricUltramarine); }
  if (minute == 20) { graphics_context_set_fill_color(ctx, GColorArmyGreen); }
  if (minute == 21) { graphics_context_set_fill_color(ctx, GColorDarkGray); }
  if (minute == 22) { graphics_context_set_fill_color(ctx, GColorLiberty); }
  if (minute == 23) { graphics_context_set_fill_color(ctx, GColorVeryLightBlue); }
  if (minute == 24) { graphics_context_set_fill_color(ctx, GColorKellyGreen); }
  if (minute == 25) { graphics_context_set_fill_color(ctx, GColorMayGreen); }
  if (minute == 26) { graphics_context_set_fill_color(ctx, GColorCadetBlue); }
  if (minute == 27) { graphics_context_set_fill_color(ctx, GColorPictonBlue); }
  if (minute == 28) { graphics_context_set_fill_color(ctx, GColorBrightGreen); }
  if (minute == 29) { graphics_context_set_fill_color(ctx, GColorScreaminGreen); }
  if (minute == 30) { graphics_context_set_fill_color(ctx, GColorMediumAquamarine); }
  if (minute == 31) { graphics_context_set_fill_color(ctx, GColorElectricBlue); }
  if (minute == 32) { graphics_context_set_fill_color(ctx, GColorDarkCandyAppleRed); }
  if (minute == 33) { graphics_context_set_fill_color(ctx, GColorJazzberryJam); }
  if (minute == 34) { graphics_context_set_fill_color(ctx, GColorPurple); }
  if (minute == 35) { graphics_context_set_fill_color(ctx, GColorVividViolet); }
  if (minute == 36) { graphics_context_set_fill_color(ctx, GColorWindsorTan); }
  if (minute == 37) { graphics_context_set_fill_color(ctx, GColorRoseVale); }
  if (minute == 38) { graphics_context_set_fill_color(ctx, GColorPurpureus); }
  if (minute == 39) { graphics_context_set_fill_color(ctx, GColorLavenderIndigo); }
  if (minute == 40) { graphics_context_set_fill_color(ctx, GColorLimerick); }
  if (minute == 41) { graphics_context_set_fill_color(ctx, GColorBrass); }
  if (minute == 42) { graphics_context_set_fill_color(ctx, GColorLightGray); }
  if (minute == 43) { graphics_context_set_fill_color(ctx, GColorBabyBlueEyes); }
  if (minute == 44) { graphics_context_set_fill_color(ctx, GColorSpringBud); }
  if (minute == 45) { graphics_context_set_fill_color(ctx, GColorInchworm); }
  if (minute == 46) { graphics_context_set_fill_color(ctx, GColorMintGreen); }
  if (minute == 47) { graphics_context_set_fill_color(ctx, GColorCeleste); }
  if (minute == 48) { graphics_context_set_fill_color(ctx, GColorRed); }
  if (minute == 49) { graphics_context_set_fill_color(ctx, GColorFolly); }
  if (minute == 50) { graphics_context_set_fill_color(ctx, GColorFashionMagenta); }
  if (minute == 51) { graphics_context_set_fill_color(ctx, GColorMagenta); }
  if (minute == 52) { graphics_context_set_fill_color(ctx, GColorOrange); }
  if (minute == 53) { graphics_context_set_fill_color(ctx, GColorSunsetOrange); }
  if (minute == 54) { graphics_context_set_fill_color(ctx, GColorBrilliantRose); }
  if (minute == 55) { graphics_context_set_fill_color(ctx, GColorShockingPink); }
  if (minute == 56) { graphics_context_set_fill_color(ctx, GColorChromeYellow); }
  if (minute == 57) { graphics_context_set_fill_color(ctx, GColorRajah); }
  if (minute == 58) { graphics_context_set_fill_color(ctx, GColorMelon); }
  if (minute == 59) { graphics_context_set_fill_color(ctx, GColorRichBrilliantLavender); }

  // Draw a circle
  // graphics_context_set_fill_color(ctx, GColorFromRGB(0, 0, minute*3));
  // graphics_context_set_fill_color(ctx, colour);
  // graphics_fill_circle(ctx, center, 70);
  graphics_fill_rect(ctx, GRect(0, 0, bounds.size.w/60*minute, bounds.size.h), 0, GCornerNone);
  // GRect(xstart, ystart, xsize, ysize)
}

static void main_window_load(Window *window) {
  // Get the root layer
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create Layer
  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, s_canvas_layer);

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

  // Register with TickTimerService, only update when the minute changes
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
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
