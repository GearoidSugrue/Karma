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
    //position[0] = 50 ;
   // position[1] = 400;
    position.first = 50 ;
    position.second = 350;
    vel.first = 0;
    vel.second = 0;
    moveSpeed = 5;
    jumpspeed = 15;
    cashAmount = 30;
    gravity = 1;
    karmaLevel = 0 ;//change back to 10
    direction = RIGHT;
    activateGravity = true;

    playerAnimation.LoadContent(playerImage, "", position);

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
        direction = RIGHT;
        //position.first += moveSpeed;
        vel.first = moveSpeed;
    }
    else if(input.IsKeyDown(ALLEGRO_KEY_LEFT))
    {
        direction = LEFT;
        //position.first -= moveSpeed;

        vel.first = -moveSpeed;
    }
    else if(input.IsKeyDown(ALLEGRO_KEY_UP) && !activateGravity)
    {
        direction = UP;
        vel.second = -jumpspeed;
        activateGravity = true;
        //put jump code here
    }
    else if(input.IsKeyDown(ALLEGRO_KEY_SPACE))
    {
       //do action here...interact


    }
    else
    {
        vel.first = 0;
        playerAnimation.IsActive() = false;
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
        if(position.second >= 460)
        {
            position.second = 460;
            activateGravity = false;
        }
        if(position.first < 0)
        {
            position.first = 0;
        }
        playerAnimation.Position() = position;
        playerAnimation.CurrentFrame() = std::pair<int, int>(karmaLevel, 0);

    //spriteAnimation.Update(playerAnimation);//not needed for the player character


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


