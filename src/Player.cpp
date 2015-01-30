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
    position.first = 50 ;
    position.second = 440;
    vel.first = 0;
    vel.second = 0;
    moveSpeed = 5;
    jumpspeed = 15;
    cashAmount = 30;
    gravity = 1;
    karmaLevel = 3 ;
    activateGravity = true;

    playerAnimation.LoadContent(playerImage, "", position);
    playerAnimation.NumberOfFrames() = std::pair<int, int>(7, 1);
    std::cout<<"creating Player..."<<std::endl;
}

void Player::UnloadContent()
{
    al_destroy_bitmap(playerImage);
    position = std::pair<int, int>(0, 0);
    moveSpeed = 0;
    cashAmount = 0;
    karmaLevel = 0;
    jumpspeed = 0;
    activateGravity = NULL;
    playerAnimation.UnloadContent();
    std::cout<<"destroying Player..."<<std::endl;

}
void Player::Update(ALLEGRO_EVENT ev, InputManager input)
{
    input.Update();
    playerAnimation.IsActive() = true;

    if(input.IsKeyDown(ALLEGRO_KEY_RIGHT))
    {
        vel.first = moveSpeed;
    }
    else if(input.IsKeyDown(ALLEGRO_KEY_LEFT))
    {
        vel.first = -moveSpeed;
    }
    else
    {
        vel.first = 0;
        playerAnimation.IsActive() = false;
    }

    if(input.IsKeyDown(ALLEGRO_KEY_UP) && !activateGravity)
    {
        vel.second = -jumpspeed;
        activateGravity = true;
    }

    if(activateGravity)
    {
        vel.second = vel.second + gravity;
    }
    else
    {
        vel.second = 0;
    }

    position.first = position.first + vel.first;
    position.second = position.second + vel.second;
    if(position.second >= 440)
    {
        position.second = 440;
        activateGravity = false;
    }

    if(position.first < 0)
    {
        position.first = 0;
    }
    playerAnimation.Position() = position;
    playerAnimation.CurrentFrame() = std::pair<int, int>(karmaLevel, 0);
}
void Player::Draw(ALLEGRO_DISPLAY *display)
{
    al_draw_bitmap_region(playerImage, karmaLevel * 80, 0, 80, al_get_bitmap_height(playerImage), position.first, position.second, NULL);
}

void Player::SetKarmaLevel(int newLevel)
{
    karmaLevel = newLevel;
}

int Player::GetKarmaLevel()
{
    return karmaLevel;
}

void Player::SetMoney(int newAmount)
{
    cashAmount = newAmount;
}

int Player::GetMoney()
{
    return cashAmount;
}

std::pair<float, float> Player::GetPosition()
{
    return position;
}
