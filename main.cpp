#include <iostream>
#include <stdio.h>
#include <allegro.h>
#include <allegro_native_dialog.h>

#include "ScreenManager.h"
#include "InputManager.h"
#include "EndScreen.h"

#include "main.h"

#define ScreenWidth 1190
#define ScreenHeight 700

int main(int argc, char **argv)
{
    const float FPS = 60.0f;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      al_show_native_message_box(NULL,"Karma","Error","Allegro failed to initialize!",NULL,ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
   }
    //Addons + installs
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();

   //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_NOFRAME); //Uncomment for Fullscreen
   //al_set_new_display_flags(ALLEGRO_NOFRAME);
   display = al_create_display(ScreenWidth, ScreenHeight);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_show_native_message_box(display,"Karma","Error","Display window was not created sucessfully!",NULL,ALLEGRO_MESSAGEBOX_ERROR);

      return -1;
   }
    al_set_window_position(display, 25, 25);

   event_queue = al_create_event_queue();//Creates Event Queue
   if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_show_native_message_box(display,"Karma","Error","Failed to create event_queue!",NULL,ALLEGRO_MESSAGEBOX_ERROR);

      al_destroy_display(display);
      return -1;
   }

    timer = al_create_timer(1.0f / FPS);

    //Event register
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_hide_mouse_cursor(display);//Hides the mouse cursor

    bool done = false, redraw = true;

    al_set_target_backbuffer(display);

    InputManager input;

    ScreenManager::GetInstance().Initialize();
    ScreenManager::GetInstance().LoadContent();

    //Game loop
    al_start_timer(timer);
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if(ev.timer.source == timer)
            {
                ScreenManager::GetInstance().Update(ev);
            }
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            ScreenManager::GetInstance().Update(ev);
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || input.IsKeyReleased(ev, ALLEGRO_KEY_ESCAPE))
        { //Exits the game if the user hits the close button or ESC key.
            ScreenManager::GetInstance().UnloadContent();
            done = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if(input.IsKeyReleased(ev, ALLEGRO_KEY_END))//Skips to the end screen
            {
                ScreenManager::GetInstance().AddScreen(new EndScreen);
            }
            redraw = true;
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {//Draws 60 FPS
            redraw = false;
            ScreenManager::GetInstance().Draw(display);
        }
    }

    ScreenManager::GetInstance().UnloadContent();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
   return 0;
}
