#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include "variable.hpp"
using namespace std;
int loadCounterX = 0, loadCounterY = 0, mapSizeX, mapSizeY;
int map[1000][1000];
void loadMap(const char *filename)
{
  ifstream openfile(filename);
  if (openfile.is_open())
  {
    // openfile >> mapSizeX >> mapSizeY;
    string line;
    getline(openfile, line);
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    cout << line << endl;
    mapSizeX = line.length();
    cout << "MapSizeX " << mapSizeX << ", "
         << "MapSizeY " << mapSizeY << endl;
    openfile.seekg(0, ios::beg);

    while (!openfile.eof())
    {
      // leggo dal file la posizione lcx e lcy
      openfile >> map[loadCounterX][loadCounterY];
      // cout << map[loadCounterX][loadCounterY] << " ";
      loadCounterX++;
      // incremento solo la x,
      // quando arriva al bordo la porto a 0
      // e scendo di una riga
      if (loadCounterX >= mapSizeX)
      {
        loadCounterX = 0;
        loadCounterY++;
        // cout << endl;
      }
    }
    mapSizeY = loadCounterY;
    cout << "MapSizeX " << mapSizeX << ", "
         << "MapSizeY " << mapSizeY << endl;
  }
  else
  {
    cerr << "Can't load map file" << endl;
  }
}

void drawMap(int x, int &y, float *cameraPosition);
void cameraUpdate(float *cameraPosition, float x, float y, int width, int heigth)
{
  cameraPosition[0] = -(SCREEN_W / 2) + (x + width / 2);
  cameraPosition[1] = -(SCREEN_H / 2) + (y + heigth / 2);

  if (cameraPosition[0] < 0)
    cameraPosition[0] = 0;
  if (cameraPosition[1] < 0)
    cameraPosition[1] = 0;
}
int main(int argc, char **argv)
{
  float cameraPosition[2] = {0, 0};
  //////////////////////////////////////////////////////////////
  ////////////////////// INIT //////////////////////////////////
  //////////////////////////////////////////////////////////////
  al_init();
  al_install_audio();
  al_install_keyboard();
  al_install_mouse();
  al_init_image_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_acodec_addon();
  al_init_primitives_addon();

  const ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
  const ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
  const ALLEGRO_COLOR green = al_map_rgb(51, 222, 162);
  const ALLEGRO_COLOR sky = al_map_rgb(102, 153, 255);
  const ALLEGRO_COLOR red = al_map_rgb(222, 51, 111);
  const ALLEGRO_COLOR yellow = al_map_rgb(196, 222, 51);
  al_set_new_display_flags(ALLEGRO_RESIZABLE);
  // display = al_create_display(800, 600);
  ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);
  // ALLEGRO_BITMAP *ico = al_load_bitmap("../assets/img/image64x64.png");
  ALLEGRO_BITMAP *pg = al_load_bitmap("../assets/img/image64x64.png");
  al_reserve_samples(2);
  ALLEGRO_SAMPLE *step = al_load_sample("../assets/snd/step.wav");
  ALLEGRO_SAMPLE *jump = al_load_sample("../assets/snd/jump.wav");
  ALLEGRO_BITMAP **frame = new ALLEGRO_BITMAP *[18];
  for (int i = 0; i < 17; i++)
  {
    string path;
    if (i < 8)
      path = "../assets/img/mariobros_0" + to_string(i + 2) + ".gif";
    else
      path = "../assets/img/mariobros_" + to_string(i + 2) + ".gif";
    // cout << path << endl;
    frame[i] = al_load_bitmap(path.c_str());
  }
  // al_set_display_icon(display, ico);
  ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_FONT *font = al_load_ttf_font("../assets/fnt/font.ttf", 120, 0);
  ALLEGRO_FONT *fontSmall = al_load_ttf_font("../assets/fnt/font.ttf", 20, 0);
  ALLEGRO_TRANSFORM camera;
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));
  // al_set_new_display_flags(ALLEGRO_RESIZABLE);
  al_set_window_title(display, TITLE_all.c_str());
  // al_hide_mouse_cursor(display);
  bool draw = false;
  bool running = true;
  float x = SCREEN_W / 4;
  float y = 32;
  float velx, vely;
  // velx, vely = 0;
  bool jumping = false;
  float jumpSpeed = 10;
  const float gravity = 1;

  float asse = 0;
  int start_x = 96;
  int start_y = 0;
  int delta_x = 16;
  int direction = 0;
  al_start_timer(timer);
  bool active = false;
  bool flip = false;
  int pos = 0;
  bool once = true;
  loadMap("../assets/map/block");
  al_clear_to_color(sky);
  al_draw_text(font, white, SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTRE, TITLE_line01.c_str());
  al_draw_text(font, white, SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTRE, TITLE_line02.c_str());
  // al_draw_text(fontSmall, white, SCREEN_W / 2, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_CENTRE, TITLE_line03.c_str());
  al_flip_display();
  al_clear_to_color(sky);
  al_rest(2);
  int floor = -1;
  int marioX, marioY = 0;
  // int scrollx = 0;
  ALLEGRO_KEYBOARD_STATE keyState;
  al_get_keyboard_state(&keyState);

  while (running)
  {
    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    drawMap(x, floor, cameraPosition);
    // cout << floor << "\n";
    // y = BLOCK_SIZE * floor - BLOCK_SIZE;
    if (!jumping)
    {
      vely += gravity;
    }
    else
    {
      vely = 0;
    }

    // x = (x + velx > SCREEN_W ? 0 : (x + velx < 0 ? SCREEN_W : x + velx));
    x += velx;
    y += vely;
    jumping = (y + BLOCK_SIZE >= BLOCK_SIZE * floor);
    if (jumping)
      y = BLOCK_SIZE * floor - BLOCK_SIZE;
    // active = false;
    if (!active && jumping)
      pos = 1;
    if (y + BLOCK_SIZE >= SCREEN_H)
    {
      // cout << "Game OVER!" << endl;
      al_show_native_message_box(al_get_current_display(),
                                 "Game Over!",
                                 "",
                                 "AHAHAHAH.. Sei scemo!",
                                 NULL, ALLEGRO_MESSAGEBOX_WARN);
      running = false;
    }
    //////////////////////////////////////////////////////////////
    // Keyboard and multiple ket press at sime time
    // Esco se chiudo la finestra con la (X) o con ESC
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
      running = false;

    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
    {
      // x = (x + PASSO > SCREEN_W ? 0 : x + PASSO);
      velx = PASSO;
      pos = (pos == 1 ? 2 : 1);
      active = true;
      flip = false;
      direction = 1;
      if (!jumping)
        al_play_sample(step, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
    else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
    {
      velx = -PASSO;
      pos = (pos == 1 ? 2 : 1);
      active = true;
      flip = true;
      direction = -1;
      if (!jumping)
        al_play_sample(step, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      // if (x + velx > SCREEN_W)
      //   scrollx++;
    }
    else
    {
      velx = 0;
      active = false;
    }
    //////////////////////////////////////////////////////////////
    if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
    {
      pos = 5;
      active = true;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && jumping)
    {
      pos = 4;
      // active = false;
      // y -= BLOCK_SIZE + 1;
      vely = -jumpSpeed;
      jumping = false;
      al_play_sample(jump, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_B))
    {
      pos = 16;
      active = true;
    }
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /////////////////////// TIMER ////////////////////////////////
    //////////////////////////////////////////////////////////////
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
      // al_draw_text(font, white, SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTRE, TITLE_line01.c_str());
      // al_draw_text(font, white, SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTRE, TITLE_line02.c_str());
      cameraUpdate(cameraPosition, x, y, 32, 32);
      al_identity_transform(&camera);
      al_translate_transform(&camera, -cameraPosition[0], 0);
      al_use_transform(&camera);
      // for (int i = 0; i < 10; i++)
      //   al_draw_bitmap(frame[i], x += 32, y += 32, 0);
      // al_draw_bitmap(pg, x, y, 0);
      al_draw_bitmap(frame[pos], x, y, flip);
      // al_draw_bitmap_region(spritesheet, start_x + delta_x * pos, start_y, 16, 32, x, y, NULL);
      al_flip_display();
      al_clear_to_color(sky);
    }
  }

  //////////////////////////////////////////////////////////////
  ////////////////////// DESTROY ///////////////////////////////
  //////////////////////////////////////////////////////////////
  for (int i = 0; i < 17; i++)
  {
    al_destroy_bitmap(frame[i]);
  }
  // al_stop_timer(timer);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  // al_destroy_bitmap(spritesheet);
  // al_destroy_bitmap(ico);
  al_destroy_font(font);
  al_destroy_font(fontSmall);
  al_destroy_display(display);
  al_uninstall_keyboard();
  al_uninstall_mouse();
  al_destroy_sample(step);
  al_destroy_sample(jump);
  al_uninstall_audio();
  al_shutdown_font_addon();
  al_shutdown_image_addon();
  al_shutdown_ttf_addon();
  al_shutdown_primitives_addon();
  return 0;
}

void drawMap(int col, int &floor, float *cameraPosition)
{
  col = static_cast<int>(ceil(col / BLOCK_SIZE));
  int startx = cameraPosition[0] / BLOCK_SIZE;
  int stopx = cameraPosition[0] / BLOCK_SIZE + (SCREEN_W / BLOCK_SIZE);
  int starty = 0;
  int stopy = SCREEN_W / BLOCK_SIZE;
  // cout << "Colonna" << col << endl;
  bool ground = false;
  for (int i = startx; i < stopx; i++)
  {

    for (int j = starty; j < stopy; j++)
    {
      if (map[i][j] == 0)
      {
        al_draw_filled_rectangle(
            i * BLOCK_SIZE,
            j * BLOCK_SIZE,
            i * BLOCK_SIZE + BLOCK_SIZE,
            j * BLOCK_SIZE + BLOCK_SIZE,
            al_map_rgb(102, 153, 255));
      }
      else if (map[i][j] == 2)
      {
        al_draw_filled_rectangle(
            i * BLOCK_SIZE,
            j * BLOCK_SIZE,
            i * BLOCK_SIZE + BLOCK_SIZE,
            j * BLOCK_SIZE + BLOCK_SIZE,
            al_map_rgb(255, 255, 255));
      }
      else if (map[i][j] == 1)
      {
        if (i == col && !ground)
        {
          floor = j;
          ground = true;
        }
        al_draw_filled_rectangle(
            i * BLOCK_SIZE,
            j * BLOCK_SIZE,
            i * BLOCK_SIZE + BLOCK_SIZE,
            j * BLOCK_SIZE + BLOCK_SIZE,
            al_map_rgb(153, 102, 51));
      }
    }
    if (!ground)
      floor = 30;
  }
}