#include <allegro5/allegro.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

int main(int argc, char **argv)
{
  al_init();
  al_install_keyboard();
  al_init_image_addon();

  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *queue;
  ALLEGRO_TIMER *timer;
  ALLEGRO_BITMAP *bitmap = NULL;

  display = al_create_display(512, 512);
  queue = al_create_event_queue();
  timer = al_create_timer(1.0 / 60);

  bitmap = al_load_bitmap("../assets/img/image512x512.png");
  assert(bitmap != NULL); // fermati se bitmap è NULL

  bool running = true;
  float x = 0;
  int width = al_get_display_width(display);
  // int height = al_get_display_height(display);

  // aggiunge la tastiera ai dispositivi da monitorare (i cui eventi vanno in coda)
  al_register_event_source(queue, al_get_keyboard_event_source());
  // aggiunge lo schermo ai dispositivi da monitorare (i cui eventi vanno in coda)
  al_register_event_source(queue, al_get_display_event_source(display));
  // aggiunge il timer ai dispositivi da monitorare (i cui eventi vanno in coda)
  // il timer emette un evento ogni x secondi, con x il valore passato alla funzione al_create_timer(x)
  al_register_event_source(queue, al_get_timer_event_source(timer));

  al_start_timer(timer);

  // game loop
  while (running)
  {
    // write every frame
    // al_flip_display();

    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);

    // Esco se premo un qualunque tasto della tastiera o se chiudo la finestra con la (X)
    if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      running = false;
    }

    // Flippo il display ogni 1/60 sec (ottengo un FPS a 60)
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
      al_clear_to_color(al_map_rgba(1, 1, 1, 1));
      al_draw_bitmap(bitmap, x += 10, 0, 0);
      al_flip_display();
    }

    if (x > width)
    {
      x = -al_get_bitmap_width(bitmap);
    }
  }

  // Avoid memory leaks
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_bitmap(bitmap);
  al_uninstall_keyboard();

  return 0;
}