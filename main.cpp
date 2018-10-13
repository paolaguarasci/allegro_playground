#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
int main(int argc, char **argv)
{
  al_init();
  al_install_audio();
  al_init_acodec_addon();

  // ALLEGRO_DISPLAY *display;
  ALLEGRO_SAMPLE *sample = NULL;
  ALLEGRO_SAMPLE_INSTANCE *sampleInstance = NULL;
  al_reserve_samples(1);

  // sample = al_load_sample("../assets/snd/xplosion.wav");
  sampleInstance = al_create_sample_instance(sample);
  al_play_sample(sample, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
  al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());
  al_play_sample_instance(sampleInstance);

  while (al_get_sample_instance_playing(sampleInstance))
  {
  }

  al_destroy_sample_instance(sampleInstance);
  al_destroy_sample(sample);
  al_uninstall_audio();
  return 0;
}