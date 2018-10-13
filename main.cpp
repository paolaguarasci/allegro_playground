#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, char **argv)
{
  al_init();
  al_install_keyboard();
  al_install_mouse();
  al_init_image_addon();
  al_init_primitives_addon();

  float points[8] = {0.00f, 0.00f, 100.00f, 100.00f, 200.00f, 100.00f, 640.00f, 150.00f};
  float polygon[8] = {640.00f, 100.00f, 640.00f, 300.00f, 300.00f, 350.00f, 200.00f, 200.00f};

  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *queue;
  ALLEGRO_TIMER *timer;
  ALLEGRO_BITMAP *bitmap = NULL;

  display = al_create_display(800, 600);
  queue = al_create_event_queue();
  timer = al_create_timer(1.0 / 60);

  bitmap = al_load_bitmap("../assets/img/image64x64.png");
  assert(bitmap != NULL); // fermati se bitmap è NULL

  bool running = true;
  float x = 0, y = 0;
  int width = al_get_display_width(display);
  // int height = al_get_display_height(display);

  // aggiunge la tastiera ai dispositivi da monitorare (i cui eventi vanno in coda)
  al_register_event_source(queue, al_get_keyboard_event_source());
  // aggiunge lo schermo ai dispositivi da monitorare (i cui eventi vanno in coda)
  al_register_event_source(queue, al_get_display_event_source(display));
  // aggiunge il timer ai dispositivi da monitorare (i cui eventi vanno in coda)
  // il timer emette un evento ogni x secondi, con x il valore passato alla funzione al_create_timer(x)
  al_register_event_source(queue, al_get_timer_event_source(timer));
  // aggiungo il mouse ai dispositivi da monitorare (i cui eventi vanno in coda)
  al_register_event_source(queue, al_get_mouse_event_source());

  al_start_timer(timer);

  // game loop
  while (running)
  {
    // write every frame
    // al_flip_display();

    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);

    // Esco se chiudo la finestra con la (X)
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      running = false;
    }

    // mouse
    // if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    // {
    //   x = event.mouse.x;
    //   y = event.mouse.y;
    // }
    // if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    // {
    //   x = y = 0;
    //   al_set_mouse_xy(display, 0, 0);
    // }

    //Keyboard and multiple ket press at same time
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);
    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
    {
      if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
      {
        x += 10;
        // std::cout  << "Win" << std::endl;
      }
      else
      {
        x += 1;
      }
    }

    // Flippo il display ogni 1/60 sec (ottengo un FPS a 60)
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
      // disegno una linea rossa dall'angolo superiore sx all'angolo inferiore destro
      al_draw_line(0, 0, al_get_display_width(display), al_get_display_height(display), al_map_rgb(255, 0, 0), 5);
      al_draw_rectangle(100, 100, 300, 300, al_map_rgb(0, 255, 0), 5);
      al_draw_spline(points, al_map_rgb(128, 255, 130), 10);
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
  al_uninstall_mouse();

  return 0;
}