#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::LoadContent(const char* entityN)
{
    entityName = entityN;
    LoadEntity(entityName);
    pos.first = pos.first * 70 ;
    pos.second  = pos.second * 70;
    isNear = false;
    isActionComplete = false;

    if(type == OBJECT && imageName != "")
    {
        image = al_load_bitmap(imageName.c_str());
        animation.LoadContent(image, "", pos);
    }
    std::cout<<"creating Entity..."<< entityName <<std::endl;
}

void Entity::UnloadContent()
{
    if(type == OBJECT)
    {
        al_destroy_bitmap(image);
    }
    pos = std::pair<float, float>(0, 0);
    textBoxText = "" ;
    dialogText = "" ;
    yesText = "" ;
    noText = "" ;
    imageName = "" ;
    sizeWidth = NULL ;
    sizeHeight = NULL ;
    activateGravity = false;
    frame = 0;
    timer = 0;
}

void Entity::Update(ALLEGRO_EVENT ev, InputManager input,Player* player)
{
    input.Update();

    if(isNear && !isActionComplete)
    {
        if(input.IsKeyDown(ALLEGRO_KEY_SPACE))
        {

            if(std::strcmp(entityName, "entity_lotto.txt") == 0)
            {
                NoAction();
                int money = player->GetMoney();
                if(money>0)
                {
                    player->SetMoney(money-5);
                }
            }
            else if(std::strcmp(entityName, "entity_wallet_guy.txt") == 0)
            {
                player->SetKarmaLevel(player->GetKarmaLevel()-1);
                YesAction();

            }
            else if(std::strcmp(entityName, "entity_warning_sign.txt") == 0)
            {
                player->SetKarmaLevel(player->GetKarmaLevel()+1);
                NoAction();

            }
        }
        else if(input.IsKeyDown(ALLEGRO_KEY_UP))
        {
            if(std::strcmp(entityName, "entity_cat_girl.txt") == 0)
            {
                player->SetKarmaLevel(player->GetKarmaLevel()-1);
                YesAction();
            }
            if(std::strcmp(entityName, "entity_cat.txt") == 0)
            {
                pos.second += 140;
                YesAction();
            }
        }
        else if(input.IsKeyDown(ALLEGRO_KEY_ENTER))
        {
            if(std::strcmp(entityName, "entity_wallet_guy.txt") == 0)
            {
                player->SetMoney(60);
                player->SetKarmaLevel(player->GetKarmaLevel()+1);
                NoAction();
            }
        }

        if(std::strcmp(entityName, "entity_blocks.txt") == 0)
        {
            int posY = animation.position.second;

            if(!isActionComplete && player->GetPosition().first >  (animation.position.first + 100)  )
            {
                if(animation.position.second <= 420)
                {
                    animation.position.second = animation.position.second + 5;
                }
            }

            if(animation.position.second >= 420 && !isActionComplete)
            {
                isActionComplete = true;
            }
        }
    }
}

void Entity::YesAction()
{
        dialogText = yesText;
        isActionComplete = true;
}

void Entity::NoAction()
{
        dialogText = noText;
        isActionComplete = true;
}

void Entity::Draw(ALLEGRO_DISPLAY *display)
{
    timer++;
    if(timer >= 60)
    {
       timer = 0;
    }
    if(type == OBJECT)
    {
        if(std::strcmp(entityName, "entity_cat.txt") == 0)
        {
            if(timer % 7 == 0)
            {

                int width = al_get_bitmap_width(image);
                frame +=  width / 8;
                    if(frame >= width)
                    {
                        frame = 0 ;
                    }
            }
            al_draw_bitmap_region(image, frame, 0, 75, 75, pos.first, pos.second, NULL);
        }
        else
            animation.Draw(display);
    }
    else if (type == CHARACTER)
    {
        al_draw_filled_rectangle(pos.first-sizeWidth, pos.second-sizeHeight, pos.first, pos.second, color) ;
    }
}

void Entity::LoadEntity(const char *filename)
{
    std::ifstream openfile(filename) ;
    if(openfile.is_open())
    {
        std::string line, value ;
        int state = NULL;
        enum LoadState { POSITION, TYPE, COLOR, IMAGENAME, SIZE, TEXTBOX, TEXT, YES, NO} ;

        while(!openfile.eof())
        {
            std::getline(openfile, line);

            if(line.find("[Position]") != std::string::npos)
            {
                state = POSITION;
                continue; //skips the rest of the loop and goes back to the top of the loop.
            }
            else if (line.find("[Type]") != std::string::npos)
            {
                state = TYPE;
                continue;
            }
            else if (line.find("[Color]") != std::string::npos)
            {
                state = COLOR;
                continue;
            }
            else if(line.find("[ImageName]") != std::string::npos)
            {
                state = IMAGENAME;
                continue;
            }
            else if(line.find("[Size]") != std::string::npos)
            {
                state = SIZE;
                continue;
            }
            else if (line.find("[TextBox]") != std::string::npos)
            {
                state = TEXTBOX;
                continue;
            }
            else if (line.find("[Text]") != std::string::npos)
            {
                state = TEXT;
                continue;
            }
            else if (line.find("[Yes]") != std::string::npos)
            {
                state = YES;
                continue;
            }
            else if (line.find("[No]") != std::string::npos)
            {
                state = NO;
                continue;
            }

            switch(state)
            {
            case POSITION:
                if(line.length() > 0)
                {
                    std::stringstream str (line);
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {
                        pos.first = atoi(value.c_str());
                    }
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {
                        pos.second = atoi(value.c_str());
                    }
                }
                break;
            case TYPE:
                if(line.length() > 0)
                {
                    std::stringstream str (line);
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {
                        if(atoi(value.c_str()) == 1)
                            type = OBJECT;
                        else
                            type = CHARACTER;
                    }
                }
                break;
            case COLOR:
                if(line.length() > 0)
                {
                    int r, g, b;
                    std::stringstream str (line);
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {
                        r = atoi(value.c_str());
                    }
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {
                        g = atoi(value.c_str());
                    }
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {
                        b = atoi(value.c_str());
                    }
                    color = al_map_rgb(r,g,b);
                }
                break;
            case IMAGENAME:
                if(line.length() > 0)
                    imageName = line;

                break;
            case SIZE:
                if(line.length() > 0)
                {
                    std::stringstream str (line);
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {
                        sizeWidth = atoi(value.c_str());
                    }
                    std::getline(str, value, ' ');
                    if(value.length() > 0)
                    {
                        sizeHeight = atoi(value.c_str());
                    }
                }

                break;
            case TEXTBOX:
                if(line.length() > 0)
                {
                    std::string str2 = line;
                    textBoxText  = new char[str2.size() + 1];
                    std::copy(str2.begin(), str2.end(), textBoxText);
                    textBoxText[str2.size()] = '\0';
                }
                break;
            case TEXT:
                if(line.length() > 0)
                {
                    std::string str2 = line;
                    dialogText  = new char[str2.size() + 1];
                    std::copy(str2.begin(), str2.end(), dialogText);
                    dialogText[str2.size()] = '\0';
                }
                break;
            case YES:
                if(line.length() > 0)
                {
                    std::string str2 = line;
                    yesText  = new char[str2.size() + 1];
                    std::copy(str2.begin(), str2.end(), yesText);
                    yesText[str2.size()] = '\0';
                }

                break;
            case NO:
                if(line.length() > 0)
                {
                 std::string str2 = line;
                    noText  = new char[str2.size() + 1];
                    std::copy(str2.begin(), str2.end(), noText);
                    noText[str2.size()] = '\0';
                }
                break;
            }
        }
    }
    else
    {
        std::cout<<"Failed to open entity file."<<std::endl;
    }
}
