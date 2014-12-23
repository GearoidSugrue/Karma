#include "EndScreen.h"

EndScreen::EndScreen()
{
    //ctor
}

EndScreen::~EndScreen()
{
    //dtor
}

void EndScreen::LoadContent()
{
    font = al_load_font("slkscr.ttf", 22, NULL);
    logo = al_load_bitmap("Karma_Logo.png");
    std::cout<<"creating EndScreen..."<<std::endl;

}

void EndScreen::UnloadContent()
{
    al_destroy_font(font) ;
    al_destroy_bitmap(logo) ;
    std::cout<<"destroying EndScreen..."<<std::endl;

}

void EndScreen::Update(ALLEGRO_EVENT ev)
{
    if(input.IsKeyPressed(ev, ALLEGRO_KEY_ENTER))
    {
        ScreenManager::GetInstance().AddScreen(new GameplayScreen);
        //create new game screen?
    }
}

void EndScreen::Draw(ALLEGRO_DISPLAY *display)
{
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(logo, (al_get_display_width(display)/2) - (al_get_bitmap_width(logo)/2), (al_get_display_height(display)/10), NULL);//put karma logo here
    al_draw_text(font, al_map_rgb(150, 150, 150), (al_get_display_width(display)/2) - 375, al_get_display_height(display)*0.9f, NULL, "Game Over. Press 'Enter' to start again or 'ESC' to quit.");
    //al_clear_to_color(al_map_rgb(0,0,0));
    //al_draw_text(font, al_map_rgb(255, 255, 255), 50, 100, NULL, "KARMA");
}
