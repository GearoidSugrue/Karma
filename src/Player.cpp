#include "Player.h"

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::LoadContent()
{
    playerImage = al_load_bitmap("PlayerImage.png");
    position[0] = 50 ;
    position[1] = 400;
    moveSpeed = 0;
    karmaLevel = 0 ;//change back to 10

    playerAnimation.LoadContent(playerImage, "", position);

    std::cout<<"creating EndScreen..."<<std::endl;
}

void Player::UnloadContent()
{
    al_destroy_bitmap(playerImage);
    position[0] = position[1] = 0;
    moveSpeed = 0;
    playerAnimation.UnloadContent();
}
void Player::Update(ALLEGRO_EVENT ev)//, InputManager input)
{
    spriteAnimation.Update(playerAnimation);
    playerAnimation.CurrentFrame() = std::pair<int, int>(karmaLevel, 0);

}
void Player::Draw(ALLEGRO_DISPLAY *display)
{
    //spriteAnimation.
    playerAnimation.Draw(display);

    //al_draw_bitmap_region(playerImage, karmaLevel * 80, 0, 80, 120, position[0], position[1], NULL);
    //al_draw_bitmap_region(cat, sourceX, 0, 75, 75, 530, 190, NULL);
}

void Player::SetKarmaLevel(int newLevel)
{
    karmaLevel = newLevel;
}

int Player::GetKarmaLevel()
{
    return karmaLevel;
}


