#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "resource_ids.auto.h"

#define MY_UUID { 0x69, 0x7B, 0x8D, 0x19, 0xB5, 0xC5, 0x4B, 0x14, 0xBE, 0x8A, 0x9A, 0xBD, 0x52, 0x62, 0x95, 0x56 }
PBL_APP_INFO(MY_UUID, "Space Invaders", "KIXEYE", 0x5, 0x0, RESOURCE_ID_IMAGE_MENU_ICON, APP_INFO_WATCH_FACE);


Window window;
Layer layer;
TextLayer text_date_layer;
TextLayer text_second_layer;
TextLayer text_h1_layer;
TextLayer text_h2_layer;
TextLayer text_h3_layer;
TextLayer text_h4_layer;
TextLayer text_h5_layer;
TextLayer text_h6_layer;
TextLayer text_h7_layer;
TextLayer text_h8_layer;
TextLayer text_h9_layer;
TextLayer text_h10_layer;
TextLayer text_h11_layer;
TextLayer text_h12_layer;
TextLayer text_m1_layer;
TextLayer text_m2_layer;
TextLayer text_m3_layer;
TextLayer text_m4_layer;
int hx1 = 38;
int hx2 = 73;
int hx3 = 108;
int hx4 = 59;
int dir = 0;
int dir2 = 1;
int init = 1;
char a[15][6]= {"%     ","+     ","'     ","(     ",")     ","*     ","+     ",",     ","-     ",".     ","/     ",":     ",";     ","=     ","?     "};

void layer_update_callback(Layer *me, GContext* ctx) {
  (void)me;
  (void)ctx;

}

void handle_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)t;
  (void)ctx;
  static char date_text[] = "Xxx <00>";
  //static char time_text[] = "xx";
  int ttime;
  int tsec;
  int tmin;
  string_format_time(date_text, sizeof(date_text), "%b<%e>", t->tick_time);
  text_layer_set_text(&text_date_layer, date_text);
  ttime = t->tick_time->tm_hour;
  tsec = t->tick_time->tm_sec;
  tmin = t->tick_time->tm_min;

  if(ttime > 12) {ttime = ttime-12;}
  if(ttime == 0) {ttime = 12;}
  if (hx1 <=12) {dir = 1;}
  if (hx1 >=30) {dir = 0;} 
  if (dir == 1) {
    hx1 = hx1 + 5;
    hx2 = hx2 + 5;
    hx3 = hx3 + 5;
  } else {
    hx1 = hx1 - 5;
    hx2 = hx2 - 5;
    hx3 = hx3 - 5;
  }

  layer_set_frame(&text_h12_layer.layer, GRect(hx3-1, 83, 82, 29));
  layer_set_frame(&text_h11_layer.layer, GRect(hx2-1, 83, 82, 29));
  layer_set_frame(&text_h10_layer.layer, GRect(hx1-1, 83, 82, 29));
  layer_set_frame(&text_h9_layer.layer, GRect(hx3, 60, 82, 29));
  layer_set_frame(&text_h8_layer.layer, GRect(hx2, 60, 82, 29));
  layer_set_frame(&text_h7_layer.layer, GRect(hx1, 60, 82, 29));
  layer_set_frame(&text_h6_layer.layer, GRect(hx3, 37, 82, 29));
  layer_set_frame(&text_h5_layer.layer, GRect(hx2, 37, 82, 29));
  layer_set_frame(&text_h4_layer.layer, GRect(hx1, 37, 82, 29));
  layer_set_frame(&text_h3_layer.layer, GRect(hx3+4, 14, 82, 29));
  layer_set_frame(&text_h2_layer.layer, GRect(hx2+4, 14, 82, 29));
  layer_set_frame(&text_h1_layer.layer, GRect(hx1+4, 14, 82, 29));
  if(dir2 == 1){
    layer_set_frame(&text_second_layer.layer, GRect(tsec*2, 138, 82, 29));
  } else {
    layer_set_frame(&text_second_layer.layer, GRect(120-(tsec*2), 138, 82, 29));
  }
  layer_set_frame(&text_m1_layer.layer, GRect(3, 125, 82, 24));
  layer_set_frame(&text_m2_layer.layer, GRect(39, 125, 82, 24));
  layer_set_frame(&text_m3_layer.layer, GRect(75, 125, 82, 24));
  layer_set_frame(&text_m4_layer.layer, GRect(111, 125, 82, 24));
  if (((t->units_changed & MINUTE_UNIT) != 0)||(init==1))  {
    if (tmin >= 15){
      //put in full block 1
      text_layer_set_text(&text_m1_layer, "?");
      if (tmin >= 30){
        //put in full block 2
        text_layer_set_text(&text_m2_layer, "?");
        if (tmin >= 45){
          //put in full block 3
          text_layer_set_text(&text_m3_layer, "?");
          //block 4 = tmin-45
          text_layer_set_text(&text_m4_layer, a[tmin-45]);
        } else {
          //block 3 = tmin-30
          text_layer_set_text(&text_m3_layer, a[tmin-30]);
        }
      } else {
        //block 2 = tmin-15
        text_layer_set_text(&text_m2_layer, a[tmin-15]);
      }
    } else {
      //block 1 = tmin
      text_layer_set_text(&text_m1_layer, a[tmin]);
    }
  }

  if (((t->units_changed & HOUR_UNIT) != 0)||(init==1)) {
    // Update Hour Layers
    switch(ttime){
      case 12:
        text_layer_set_text(&text_h12_layer, "#");
      case 11:
        text_layer_set_text(&text_h11_layer, "#");
      case 10:
        text_layer_set_text(&text_h10_layer, "#");
      case 9:
        text_layer_set_text(&text_h9_layer, "\"");
      case 8:
        text_layer_set_text(&text_h8_layer, "\"");
      case 7:
        text_layer_set_text(&text_h7_layer, "\"");
      case 6:
        text_layer_set_text(&text_h6_layer, "\"");
      case 5:
        text_layer_set_text(&text_h5_layer, "\"");
      case 4:
        text_layer_set_text(&text_h4_layer, "\"");
      case 3:
        text_layer_set_text(&text_h3_layer, "!");
      case 2:
        text_layer_set_text(&text_h2_layer, "!");
        text_layer_set_text(&text_h1_layer, "!");
      break;
      case 1:
        text_layer_set_text(&text_h2_layer, "");
        text_layer_set_text(&text_h3_layer, "");
        text_layer_set_text(&text_h4_layer, "");
        text_layer_set_text(&text_h5_layer, "");
        text_layer_set_text(&text_h6_layer, "");
        text_layer_set_text(&text_h7_layer, "");
        text_layer_set_text(&text_h8_layer, "");
        text_layer_set_text(&text_h9_layer, "");
        text_layer_set_text(&text_h10_layer, "");
        text_layer_set_text(&text_h11_layer, "");
        text_layer_set_text(&text_h1_layer, "!");
      break;
    }
  }
  if(tsec == 59){
    dir2 ^= 1;
  }
  if(init == 1) {
    init = 0;
  }
  //ttsec = t->tick_time->tm_sec;
  //
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Space Invaders");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);

  resource_init_current_app(&SPACE_INVADERS_RESOURCES);

  GFont sifont = \
    fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SPACEINVADERS_20));

  GFont sifont_s = \
    fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SPACEINVADERS_10));

  GFont sifont_l = \
    fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SPACEINVADERS_30));

  text_layer_init(&text_date_layer, window.layer.frame);
  text_layer_set_text_color(&text_date_layer, GColorWhite);
  text_layer_set_background_color(&text_date_layer, GColorClear);
  layer_set_frame(&text_date_layer.layer, GRect(0, 0, 82, 29));
  text_layer_set_font(&text_date_layer, sifont_s);
  layer_add_child(&window.layer, &text_date_layer.layer);

  text_layer_init(&text_second_layer, window.layer.frame);
  text_layer_set_text_color(&text_second_layer, GColorWhite);
  text_layer_set_background_color(&text_second_layer, GColorClear);
  layer_set_frame(&text_second_layer.layer, GRect(59, 165, 82, 29));
  text_layer_set_font(&text_second_layer, sifont_l);
  layer_add_child(&window.layer, &text_second_layer.layer);
  text_layer_set_text(&text_second_layer, "$");
  
  text_layer_init(&text_h12_layer, window.layer.frame);
  text_layer_set_text_color(&text_h12_layer, GColorWhite);
  text_layer_set_background_color(&text_h12_layer, GColorClear);
  layer_set_frame(&text_h12_layer.layer, GRect(hx3-1, 82, 82, 29));
  text_layer_set_font(&text_h12_layer, sifont_l);
  layer_add_child(&window.layer, &text_h12_layer.layer);
  
  text_layer_init(&text_h11_layer, window.layer.frame);
  text_layer_set_text_color(&text_h11_layer, GColorWhite);
  text_layer_set_background_color(&text_h11_layer, GColorClear);
  layer_set_frame(&text_h11_layer.layer, GRect(hx2-1, 82, 82, 29));
  text_layer_set_font(&text_h11_layer, sifont_l);
  layer_add_child(&window.layer, &text_h11_layer.layer);
  
  text_layer_init(&text_h10_layer, window.layer.frame);
  text_layer_set_text_color(&text_h10_layer, GColorWhite);
  text_layer_set_background_color(&text_h10_layer, GColorClear);
  layer_set_frame(&text_h10_layer.layer, GRect(hx1-1, 82, 82, 29));
  text_layer_set_font(&text_h10_layer, sifont_l);
  layer_add_child(&window.layer, &text_h10_layer.layer);
  
  text_layer_init(&text_h9_layer, window.layer.frame);
  text_layer_set_text_color(&text_h9_layer, GColorWhite);
  text_layer_set_background_color(&text_h9_layer, GColorClear);
  layer_set_frame(&text_h9_layer.layer, GRect(hx3, 61, 82, 29));
  text_layer_set_font(&text_h9_layer, sifont_l);
  layer_add_child(&window.layer, &text_h9_layer.layer);
  
  text_layer_init(&text_h8_layer, window.layer.frame);
  text_layer_set_text_color(&text_h8_layer, GColorWhite);
  text_layer_set_background_color(&text_h8_layer, GColorClear);
  layer_set_frame(&text_h8_layer.layer, GRect(hx2, 61, 82, 29));
  text_layer_set_font(&text_h8_layer, sifont_l);
  layer_add_child(&window.layer, &text_h8_layer.layer);
  
  text_layer_init(&text_h7_layer, window.layer.frame);
  text_layer_set_text_color(&text_h7_layer, GColorWhite);
  text_layer_set_background_color(&text_h7_layer, GColorClear);
  layer_set_frame(&text_h7_layer.layer, GRect(hx1, 61, 82, 29));
  text_layer_set_font(&text_h7_layer, sifont_l);
  layer_add_child(&window.layer, &text_h7_layer.layer);
  
  text_layer_init(&text_h6_layer, window.layer.frame);
  text_layer_set_text_color(&text_h6_layer, GColorWhite);
  text_layer_set_background_color(&text_h6_layer, GColorClear);
  layer_set_frame(&text_h6_layer.layer, GRect(hx3, 40, 82, 29));
  text_layer_set_font(&text_h6_layer, sifont_l);
  layer_add_child(&window.layer, &text_h6_layer.layer);
  
  text_layer_init(&text_h5_layer, window.layer.frame);
  text_layer_set_text_color(&text_h5_layer, GColorWhite);
  text_layer_set_background_color(&text_h5_layer, GColorClear);
  layer_set_frame(&text_h5_layer.layer, GRect(hx2, 40, 82, 29));
  text_layer_set_font(&text_h5_layer, sifont_l);
  layer_add_child(&window.layer, &text_h5_layer.layer);
  
  text_layer_init(&text_h4_layer, window.layer.frame);
  text_layer_set_text_color(&text_h4_layer, GColorWhite);
  text_layer_set_background_color(&text_h4_layer, GColorClear);
  layer_set_frame(&text_h4_layer.layer, GRect(hx1, 40, 82, 29));
  text_layer_set_font(&text_h4_layer, sifont_l);
  layer_add_child(&window.layer, &text_h4_layer.layer);
  
  text_layer_init(&text_h3_layer, window.layer.frame);
  text_layer_set_text_color(&text_h3_layer, GColorWhite);
  text_layer_set_background_color(&text_h3_layer, GColorClear);
  layer_set_frame(&text_h3_layer.layer, GRect(hx2+3, 19, 82, 29));
  text_layer_set_font(&text_h3_layer, sifont_l);
  layer_add_child(&window.layer, &text_h3_layer.layer);
  
  text_layer_init(&text_h2_layer, window.layer.frame);
  text_layer_set_text_color(&text_h2_layer, GColorWhite);
  text_layer_set_background_color(&text_h2_layer, GColorClear);
  layer_set_frame(&text_h2_layer.layer, GRect(hx2+3, 19, 82, 29));
  text_layer_set_font(&text_h2_layer, sifont_l);
  layer_add_child(&window.layer, &text_h2_layer.layer);

  text_layer_init(&text_h1_layer, window.layer.frame);
  text_layer_set_text_color(&text_h1_layer, GColorWhite);
  text_layer_set_background_color(&text_h1_layer, GColorClear);
  layer_set_frame(&text_h1_layer.layer, GRect(hx1+2, 19, 82, 29));
  text_layer_set_font(&text_h1_layer, sifont_l);
  layer_add_child(&window.layer, &text_h1_layer.layer); 

  text_layer_init(&text_m1_layer, window.layer.frame);
  text_layer_set_text_color(&text_m1_layer, GColorWhite);
  text_layer_set_background_color(&text_m1_layer, GColorClear);
  layer_set_frame(&text_m1_layer.layer, GRect(0, 0, 82, 29));
  text_layer_set_font(&text_m1_layer, sifont);
  layer_add_child(&window.layer, &text_m1_layer.layer); 

  text_layer_init(&text_m2_layer, window.layer.frame);
  text_layer_set_text_color(&text_m2_layer, GColorWhite);
  text_layer_set_background_color(&text_m2_layer, GColorClear);
  layer_set_frame(&text_m2_layer.layer, GRect(0, 0, 82, 29));
  text_layer_set_font(&text_m2_layer, sifont);
  layer_add_child(&window.layer, &text_m2_layer.layer); 

  text_layer_init(&text_m3_layer, window.layer.frame);
  text_layer_set_text_color(&text_m3_layer, GColorWhite);
  text_layer_set_background_color(&text_m3_layer, GColorClear);
  layer_set_frame(&text_m3_layer.layer, GRect(0, 0, 82, 29));
  text_layer_set_font(&text_m3_layer, sifont);
  layer_add_child(&window.layer, &text_m3_layer.layer); 

  text_layer_init(&text_m4_layer, window.layer.frame);
  text_layer_set_text_color(&text_m4_layer, GColorWhite);
  text_layer_set_background_color(&text_m4_layer, GColorClear);
  layer_set_frame(&text_m4_layer.layer, GRect(0, 0, 82, 29));
  text_layer_set_font(&text_m4_layer, sifont);
  layer_add_child(&window.layer, &text_m4_layer.layer); 
  
  layer_init(&layer, window.layer.frame);
  layer.update_proc = &layer_update_callback;
  layer_add_child(&window.layer, &layer);

  PblTm tick_time;
  
  get_time(&tick_time);
  
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;

}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units = SECOND_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
