#include <iostream>
#include <stdio.h>
#include <allegro.h>
#include <allegro_native_dialog.h>
#include <allegro_ttf.h>
#include <allegro_font.h>
#include <allegro_primitives.h>
#include <allegro_image.h>
#include <allegro_audio.h>
#include <allegro_acodec.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>


#include <cmath>

using namespace std;

#include "main.h"

#define ScreenWidth 800
#define ScreenHeight 500
#define FPS 60
#define frameFPS 9
#define BlockSize 70

//#define fade 25

int fade = 35, loadCounterX = 0, loadCounterY = 0, mapSizeX, mapSizeY ;
//int map ;

enum LoadState { TileSet, Map} ;

int state = NULL;

ALLEGRO_BITMAP *tileset;

struct Player//change to character????
{
    float x, y;
    int dir, sourceX, sourceY;
    bool active;
};

struct Camera
{
    float x, y, fade;
    ALLEGRO_TRANSFORM transform;
};

void LoadMap(const char *filename, std::vector< std::vector<int> > &worldMap);

bool Collision(float playerX, float playerY, float eX, float eY, int playerWidth, int playerHeight, int eWidth, int eHeight)
{
    if(playerX + playerWidth < eX || playerX > eX + eWidth || playerY + playerHeight < eY || playerY > eY + eHeight)
    {
        //No Collision
        return false ;
    }

    return true ;
}

void CameraUpdate(float *cameraPosition, float x, float y, int width, int height)
{
    cameraPosition[0] = -(ScreenWidth / 2) + (x + width / 2);
    cameraPosition[1] = -(ScreenWidth / 2) + (y + height / 2);

    if(cameraPosition[0] < 0)
    {
        cameraPosition[0] = 0 ;
    }
    if(cameraPosition[1] < 0)
    {
        cameraPosition[1] = 0 ;
    }

}


void DrawMap(std::vector< std::vector<int> > worldMap);

int main(int argc, char **argv){

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *catTimer = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_TRANSFORM camera ;


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
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();



    ALLEGRO_SAMPLE *soundEffect = al_load_sample("MenuEffect1.wav"); //Menu sound effect
    al_reserve_samples(1); //How many sounds will you be playing similtansly


    enum Direction {UP, DOWN, LEFT, RIGHT} ;

    //Colors
    ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 255);

   //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_NOFRAME); //must be before display is created
   display = al_create_display(ScreenWidth, ScreenHeight);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_show_native_message_box(display,"Karma","Error","Display window was not created sucessfully!",NULL,ALLEGRO_MESSAGEBOX_ERROR);

      return -1;
   }

   event_queue = al_create_event_queue();//Creates Event Queue
   if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_show_native_message_box(display,"Karma","Error","Failed to create event_queue!",NULL,ALLEGRO_MESSAGEBOX_ERROR);

      al_destroy_display(display);
      return -1;
   }

    font = al_load_font("slkscr.ttf", 22, NULL); //Loads font
    if (!font){
        fprintf(stderr, "Could not load 'slkscr.ttf'.\n");
        al_show_native_message_box(display,"Karma","Error","Could not load 'slkscr.ttf'",NULL,ALLEGRO_MESSAGEBOX_ERROR);

        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    catTimer = al_create_timer(1.0 / frameFPS);

    //Event register
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(catTimer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_NOFRAME) ; //comment this in later
    al_hide_mouse_cursor(display);//Hides the mouse cursor so we can use our own cursor

    float x = 100, y = 300, moveSpeed = 5, mX = NULL, mY = NULL, velX = 0, velY = 0, jumpSpeed = 15;
    float cameraPos[2] = {0, 0} ;
    bool done = false, redraw = true, playSound = false;
    bool jump = false, playerClickedLeft = false, playerClickedRight = false, active = false;
    int dir = NULL, sourceX = 0, sourceY = 0 ;

    const float gravity = 1;

    Player _player;
    Camera _camera;

    _player.x = x;
    _player.y = y;
    _camera.fade = fade ;

    //BITMAPS
    ALLEGRO_BITMAP *cat = al_load_bitmap("Cat3.png");
    ALLEGRO_BITMAP *clonedBitmap = al_clone_bitmap(cat);//Clones a bitmap
    ALLEGRO_BITMAP *blackFader = al_load_bitmap("BlackFade.png");

    std::vector< std::vector<int> > worldMap;

    LoadMap("Map1.txt", worldMap); //int* worldMap = LoadMap("Map1.txt");//Reads in from the map txt file

    //Game loop
    al_start_timer(timer);
    al_start_timer(catTimer);
    while(!done)
    {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);

    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //If the user hits the close button
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
    else if(ev.type == ALLEGRO_EVENT_TIMER)//Timer that runs 60 times a second
    {
        if(ev.timer.source == timer)
        {
            //x = _player.x;
            //y = _player.y;

            //fade = _camera.fade;

            _player.active = true ;
            al_get_keyboard_state(&keyState);
            if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
            {
                //_player.x += moveSpeed;
                velX = moveSpeed;

                //Put proper collision checker here
                if(Collision(_player.x, _player.y, 400, 400, 80, 120, 75, al_get_bitmap_height(cat)))
                    playSound = true ;
            }
            else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT))
            {
                if(_player.x > 0)  //Stops the player going left
                    //_player.x -= moveSpeed;
                    velX = -moveSpeed;

                //Put proper collision checker here
                if(Collision(_player.x, _player.y, 400, 400, 80, 120, 75, al_get_bitmap_height(cat)))
                    playSound = true ;
            }
            else
            {
                velX = 0;
               _player.active = false; //nothing happened(e.g. No key presses)
            }

            if(al_key_down(&keyState, ALLEGRO_KEY_UP) && jump)
            {
                velY = -jumpSpeed;
                jump = false;
            }
            else if(al_key_down(&keyState, ALLEGRO_KEY_L)) //Reloads the map. Used to helps create the map.
            {
                worldMap.clear();
                LoadMap("Map1.txt", worldMap);
            }

            if(!jump)
                velY += gravity;
            else
                velY += 0;

            _player.x += velX;
            _player.y += velY;

            jump = (_player.y >= 300);

            if(jump)
                _player.y = 300;

            //_player.x = x;
            //_player.y = y;
            //_player.active = active


            redraw = true;
            CameraUpdate(cameraPos, _player.x, _player.y, 80, 120); //Scrolls the camera
            al_identity_transform(&camera);
            al_translate_transform(&camera, -cameraPos[0], -cameraPos[1]);
            al_use_transform(&camera);

        }
        else if(ev.timer.source == catTimer) //Timer that moves the cat's tale. Change to frame timer???
        {
                sourceX += al_get_bitmap_width(cat) / 8;

                if(sourceX >=  al_get_bitmap_width(cat)) //resets cat bitmap back to the begining
                {
                    sourceX = 0 ;
                }

        }
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) //Checks for mouse movement
    {
        mX = ev.mouse.x;
        mY = ev.mouse.y;
    }
    else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) //Checks for mouse key presses
    {
        if(ev.mouse.button & 1)
        {
            playerClickedLeft = true;
             fade--;
            //playSound = true ;
            //al_play_sample(soundEffect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            //do something here
        } else if(ev.mouse.button & 2)
        {
            playerClickedRight = true;
             fade++;
            //do something here
        }
    }

           // al_is_event_queue_empty(event_queue)
    if(redraw)
    {
        al_clear_to_color(al_map_rgb(255,255,255));
        DrawMap(worldMap);

                //al_draw_bitmap(cat, mX+20, mY+20, NULL);

        //Draw text function
        //Draw Player function
        //Draw objects and NPCs

        al_draw_text(font, electricBlue, 40, 25, NULL, "This is sample text");
        al_draw_filled_rectangle(_player.x, _player.y, _player.x + 80, _player.y + 120, electricBlue) ; //player
        al_draw_filled_triangle( mX,mY ,mX+17,mY, mX,mY+17,electricBlue) ; //mouse cursor
            //dir = NULL;
        al_draw_bitmap_region(cat, sourceX, 0, 75, 75, 400, 400, NULL);

        //ALLEGRO_BITMAP *subBitMap = al_create_sub_bitmap(clonedBitmap, sourceX, 0, 75, 75 ) ;//Works like region
        //al_draw_tinted_bitmap(subBitMap, al_map_rgb(255, 0, 0), 300, 300, NULL);
        //al_draw_scaled_bitmap(subBitMap,
        //al_draw_bitmap_region(subBitMap, 0, 0, 75, 75, 300, 300, NULL);
        //al_draw_bitmap_region(subBitMap, sourceX, 0, 75, 75, 300, 300, NULL);

        al_draw_tinted_bitmap(blackFader, al_map_rgba(0, 0, 0, fade), 0, 0, NULL); //turns the creen greyer

        al_flip_display();
        redraw = false;
        playerClickedLeft = false;
        playerClickedRight = false;
        //al_destroy_bitmap(subBitMap);
    }
    if(playSound) //do this better
    {
        al_play_sample(soundEffect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

        playSound = false;
    }

   }

    //al_rest(7.0);

    //Destroy + end game

    //delete [] worldMap;

    al_destroy_bitmap(cat);
    al_destroy_bitmap(clonedBitmap);
    al_destroy_bitmap(blackFader);
    al_destroy_sample(soundEffect);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_timer(catTimer);
   return 0;
}

void LoadMap(const char *filename, std::vector< std::vector<int> > &worldMap)
{
    std::ifstream openfile(filename) ;
    if(openfile.is_open())
    {
        std::string line, value ;
        int space;

        //line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        //mapSizeX = line.length();

        //openfile.seekg(0, std::ios::beg);


        //openfile >> mapSizeX >> mapSizeY;
        //int worldMap[mapSizeX][mapSizeY] ;

        //int** ary = new int*[mapSizeY];
        //for(int i = 0; i < mapSizeY; ++i)
        //    ary[i] = new int[mapSizeX];

        //int *ary = new int[mapSizeX*mapSizeY];
        //ary[i*mapSizeY+j] // ary[i][j]

        while(!openfile.eof())
        {
            std::getline(openfile, line);

            if(line.find("[TileSet]") != std::string::npos)
            {
                state = TileSet;
                continue; //skips the rest of the loop and goes back to the top of the loop.
            }
            else if (line.find("[Map]") != std::string::npos)
            {
                state = Map;
                continue;
            }

            switch(state)
            {
            case TileSet:
                if(line.length() > 0)
                    tileset = al_load_bitmap(line.c_str());
                break;
            case Map:
                std::stringstream str (line);
                std::vector<int> tempVector;

                while(!str.eof())
                {
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                        tempVector.push_back(atoi(value.c_str()));
                }
                worldMap.push_back(tempVector);
                break;


            //openfile >> ary[loadCounterX*mapSizeY + loadCounterY] ;//ary[loadCounterX][loadCounterY] ;   //worldMap[loadCounterX][loadCounterY] ;
            //loadCounterX++;
            //if(loadCounterX >= mapSizeX)
            //{
            //    loadCounterX = 0;
            //    loadCounterY++;
            //}
                }
        mapSizeY = loadCounterY ;
        }
       // return ary ;
    }
    else
    {
        //return NULL ;
    }
    //return NULL ;
}

void DrawMap(std::vector< std::vector<int> > worldMap)//int worldMap[])
{
    int value ;

    for(int i = 0; i < worldMap.size(); i++)
    {
        for(int j = 0; j < worldMap[i].size(); j++)
        {
            al_draw_bitmap_region(tileset, worldMap[i][j] * BlockSize, 0,
                BlockSize, BlockSize, j * BlockSize, i * BlockSize, NULL);






            //value = worldMap[i][j];//worldMap[i*mapSizeY+j] ;

            //if(value == 0)
           //     al_draw_filled_rectangle(j * BlockSize, i * BlockSize, j * BlockSize+BlockSize,
            //        i * BlockSize+BlockSize, al_map_rgb(204, 229, 255));
           // else if(value == 1)
           //     al_draw_filled_rectangle(j * BlockSize, i * BlockSize, j * BlockSize+BlockSize,
            //        i * BlockSize+BlockSize, al_map_rgb(0, 153, 0));
        }
    }
}



