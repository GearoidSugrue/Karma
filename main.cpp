#include <iostream>
#include <stdio.h>
#include <allegro.h>
#include <allegro_native_dialog.h>
#include <allegro_ttf.h>
#include <allegro_font.h>
#include <allegro_primitives.h>

#include "main.h"

#define ScreenWidth 800
#define ScreenHeight 500
#define FPS 60

int main(int argc, char **argv){

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_KEYBOARD_STATE keyState;

   if(!al_init()) { //can't initialize anything before this
      fprintf(stderr, "failed to initialize allegro!\n");
      al_show_native_message_box(NULL,"Karma","Error","Allegro failed to initialize!",NULL,ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
   }
    //Addons + installs
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();

    enum Direction {UP, DOWN, LEFT, RIGHT} ;

    //Colors
    ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 255);

   //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_NOFRAME) ; //comment this in later
   display = al_create_display(ScreenWidth, ScreenHeight);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_show_native_message_box(display,"Karma","Error","Display window was not created sucessfully!",NULL,ALLEGRO_MESSAGEBOX_ERROR);

      return -1;
   }

   event_queue = al_create_event_queue();
   if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_show_native_message_box(display,"Karma","Error","Failed to create event_queue!",NULL,ALLEGRO_MESSAGEBOX_ERROR);

      al_destroy_display(display);
      return -1;
   }

    font = al_load_font("slkscr.ttf", 22, NULL);
    if (!font){
      fprintf(stderr, "Could not load 'slkscr.ttf'.\n");
      al_show_native_message_box(display,"Karma","Error","Could not load 'slkscr.ttf'",NULL,ALLEGRO_MESSAGEBOX_ERROR);

      return -1;
    }

    timer = al_create_timer(1.0 / FPS);

    //Event register
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_hide_mouse_cursor(display);//Hides the mouse cursor so we can use our own cursor

    int x = 100 ;
    int moveSpeed = 5;
    bool done = false;
    bool redraw = true;
    int dir = NULL;
    int mX = NULL;
    int mY = NULL;
    bool playerClickedLeft = false;
    bool playerClickedRight = false;


    al_start_timer(timer);

    //Game loop
    while(!done)
    {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);

    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        done = true;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_ESCAPE:
            done = true;
        }
    }
    else if(ev.type == ALLEGRO_EVENT_TIMER)
    {
        al_get_keyboard_state(&keyState);
        if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
            x += moveSpeed;
        else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT))
            x -= moveSpeed;

        redraw = true;
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mX = ev.mouse.x;
        mY = ev.mouse.y;
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(ev.mouse.button & 1)
            playerClickedLeft = true;
            //do something here
        else if(ev.mouse.button & 2)
            playerClickedRight = true;
            //do something here
    }
           // al_is_event_queue_empty(event_queue)
    if(redraw)
    {
        al_clear_to_color(al_map_rgb(255,255,255));

        al_draw_text(font, electricBlue, 40, 25, NULL, "This is sample text");
        al_draw_filled_rectangle(x, 350, x + 80, 470, electricBlue) ; //player
        al_draw_filled_triangle( mX,mY ,mX+17,mY, mX,mY+17,electricBlue) ; //mouse cursor
            //dir = NULL;

        al_flip_display();
        redraw = false;
        playerClickedLeft = false;
        playerClickedRight = false;
    }

   }

    //al_rest(7.0);

    //Destroy + end game
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
   return 0;
}
