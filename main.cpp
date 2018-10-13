#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "variable.hpp"
using namespace std;

int main(int argc, char **argv)
{
  al_init();
  al_install_keyboard();
  al_install_mouse();
  al_init_image_addon();

  const ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
  const ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
  const ALLEGRO_COLOR green = al_map_rgb(51, 222, 162);
  const ALLEGRO_COLOR blue = al_map_rgb(76, 51, 222);
  const ALLEGRO_COLOR red = al_map_rgb(222, 51, 111);
  const ALLEGRO_COLOR yellow = al_map_rgb(196, 222, 51);

  ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);
  // ALLEGRO_BITMAP *ico = al_load_bitmap("../assets/img/image64x64.png");
  ALLEGRO_BITMAP *pg = al_load_bitmap("../assets/img/image64x64.png");
  ALLEGRO_BITMAP **frame = new ALLEGRO_BITMAP *[10];
  for (int i = 0; i < 10; i++)
  {
    string path;
    if (i < 8)
      path = "../assets/img/mariobros_0" + to_string(i + 2) + ".gif";
    else
      path = "../assets/img/mariobros_" + to_string(i + 2) + ".gif";
    cout << path << endl;
    frame[i] = al_load_bitmap(path.c_str());
  }
  // al_set_display_icon(display, ico);
  ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  // al_register_event_source(queue, al_get_timer_event_source(leg));
  al_hide_mouse_cursor(display);
  bool draw = false;
  bool running = true;
  float x = SCREEN_W / 2;
  float y = SCREEN_H / 2;
  float asse = 0;
  int start_x = 96;
  int start_y = 0;
  int delta_x = 16;
  al_start_timer(timer);
  bool active = false;
  bool flip = false;
  int pos = 0;
  while (running)
  {
    active = false;
    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);
    // Keyboard and multiple ket press at sime time
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);
    // Esco se chiudo la finestra con la (X) o con ESC
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
    {
      running = false;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
    {
      x = (x + PASSO > SCREEN_W ? 0 : x + PASSO);
      pos = (pos == 1 ? 2 : 1);
      active = true;
      flip = false;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
    {
      x = (x - PASSO + al_get_bitmap_width(pg) > 0 ? x - PASSO : SCREEN_W);
      pos = (pos == 1 ? 2 : 1);
      active = true;
      flip = true;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
    {
      pos = 5;
      active = true;
    }
    if (!active)
      pos = 1;
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
      // for (int i = 0; i < 10; i++)
      //   al_draw_bitmap(frame[i], x += 32, y += 32, 0);
      // al_draw_bitmap(pg, x, y, 0);
      al_draw_bitmap(frame[pos], x, y, flip);
      // al_draw_bitmap_region(spritesheet, start_x + delta_x * pos, start_y, 16, 32, x, y, NULL);
      al_flip_display();
      al_clear_to_color(blue);
    }
  }

  for (int i = 0; i < 10; i++)
  {
    al_destroy_bitmap(frame[i]);
  }

  // al_stop_timer(timer);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  // al_destroy_bitmap(spritesheet);
  // al_destroy_bitmap(ico);
  al_destroy_display(display);
  al_uninstall_keyboard();
  al_uninstall_mouse();
  return 0;
}
