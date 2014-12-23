#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::LoadContent(const char* entityName)//,  std::pair<float, float> p )//std::vector<std::string> attributes, std::vector<std::string> contents);//change this
{
    //position = pos;
    //entityName = name;
    LoadEntity(entityName);
    pos.first = pos.first * 70 ;
    pos.second  = pos.second * 70;

    if(type == OBJECT && imageName != "")
    {
        image = al_load_bitmap(imageName.c_str());
        animation.LoadContent(image, "", pos);
    }

    //image = al_load_bitmap(ImageName.c_str());


    std::cout<<"creating Entity..."<< entityName <<std::endl;

    std::cout<<"TextBox Text: "<< textBoxText <<std::endl;
    std::cout<<"Dialog Text: "<< dialogText <<std::endl;
    std::cout<<"Type: "<< type <<std::endl;
    //std::cout<<"Color: "<< r << " " << g << " " << b <<std::endl;
    std::cout<<"Image Name Text: "<< imageName <<std::endl;
    std::cout<<"Yes Text: "<< yesText <<std::endl;
    std::cout<<"No Text: "<< noText <<std::endl;
    std::cout<<"X: "<< pos.first <<std::endl;
    std::cout<<"Y: "<< pos.second <<std::endl;
    std::cout<<"SizeW: "<<  sizeWidth <<std::endl;
    std::cout<<"SizeH: "<<  sizeHeight <<std::endl;
}

void Entity::UnloadContent()
{
    //al_destroy_bitmap(image);//may need to delete/change
    //animation.UnloadContent();
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
    //al_destroy_color(color);
    //std::cout<<"destroying Entity..."<< entityName <<std::endl;

}

void Entity::Update(ALLEGRO_EVENT ev, InputManager inputManager)
{
    prevPosition = pos;

}

void Entity::Draw(ALLEGRO_DISPLAY *display)
{
    //animation.Draw(display) ;
    //al_init_primitives_addon;
    if(type == OBJECT)
    {
        animation.Draw(display);
    }
    else if (type == CHARACTER)
    {
        al_draw_filled_rectangle(pos.first-sizeWidth, pos.second-sizeHeight, pos.first, pos.second, color) ;
    }//al_map_rgb(44, 117, 255)
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
                continue; //skips the rest of the loop and goes back to the top of the loop.
            }
            else if(line.find("[Size]") != std::string::npos)
            {
                state = SIZE;
                continue; //skips the rest of the loop and goes back to the top of the loop.
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
                    //ileSpriteSheet = al_load_bitmap(line.c_str());
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
                    //ileSpriteSheet = al_load_bitmap(line.c_str());
                break;
            case IMAGENAME:
                //std::stringstream str (line);
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
                //std::stringstream str (line);
                //std::vector<int> tempVector;
                if(line.length() > 0)
                    textBoxText = line;//.c_str();
                //while(!str.eof())
                //{
                    //std::getline(str, value, ' ');
                    //if(value.length() > 0)
                        //tempVector.push_back(atoi(value.c_str()));
                //}
                //worldMap.push_back(tempVector);
                break;
            case TEXT:
                //std::stringstream str (line);
                //std::vector<int> tempVector;
                if(line.length() > 0)
                    dialogText = line;//.c_str();
                //while(!str.eof())
                //{
                    //std::getline(str, value, ' ');
                    //if(value.length() > 0)
                        //tempVector.push_back(atoi(value.c_str()));
                //}
                //worldMap.push_back(tempVector);
                break;
            case YES:
                //std::stringstream str (line);
                if(line.length() > 0)
                    yesText = line;

                break;
            case NO:
                //std::stringstream str (line);
                if(line.length() > 0)
                    noText = line;

                break;
            }

        //mapSizeY = loadCounterY ;
        }
       // return ary ;
    }
    else
    {

        std::cout<<"Failed to open entity file."<<std::endl;
    }
}


