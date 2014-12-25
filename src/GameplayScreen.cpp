#include "GameplayScreen.h"


GameplayScreen::GameplayScreen()
{
    //ctor
}

GameplayScreen::~GameplayScreen()
{
    //dtor
}

void GameplayScreen::LoadContent()
{
    player.LoadContent();
    font = al_load_font("Munro.ttf", 24, NULL);
    fontColor = al_map_rgb(150, 150, 150);
    isEndGame = false;
    cameraPosition.first = 0;
    cameraPosition.second = 0;
    entityMan.LoadContent("entities_list.txt");

    LoadMap("Map1.txt");
    HudText = "Use arrow keys to move. \n Space to interact. \n ESC to quit. \n \n Goal: Go to the shop" ;
    std::cout<<"creating GameplayScreen..."<<std::endl;
}

void GameplayScreen::UnloadContent()
{
    al_translate_transform(&camera, cameraPosition.first, cameraPosition.second); //Sets camera back to default
    player.UnloadContent();
    entityMan.UnloadContent();

    cameraPosition.first = 0;
    cameraPosition.second = 0;
    HudText = "";

    worldMap.clear();
    std::vector< std::vector<int> >(worldMap).swap(worldMap);
    al_destroy_bitmap(tileSpriteSheet);
    al_destroy_font(font);
    al_identity_transform(&camera);
    al_use_transform(&camera);
    std::cout<<"destroying GameplayScreen..."<<std::endl;
}

void GameplayScreen::Update(ALLEGRO_EVENT ev)
{
    player.Update(ev, input);
    entityMan.Update(ev, input, &player);

    if(isEndGame)
    {

        ScreenManager::GetInstance().AddScreen(new EndScreen);

    }
}

void GameplayScreen::Draw(ALLEGRO_DISPLAY *display)
{
    al_clear_to_color(al_map_rgb(255,255,255));
    DrawMap();
    entityMan.Draw(display);

    EntitiesInteraction();
    player.Draw(display);
    CameraUpdate(player.GetPosition().first, player.GetPosition().second, 80, 120);

    al_identity_transform(&camera);
    al_translate_transform(&camera, -cameraPosition.first, -cameraPosition.second);
    al_use_transform(&camera);

    DrawHUD(display);
    DrawWrappedText(font, HudText, fontColor, cameraPosition.first + 20, cameraPosition.second + 20, 500, ALLEGRO_ALIGN_LEFT, true);
}

void GameplayScreen::DrawHUD(ALLEGRO_DISPLAY *display)
{//Draws the amount of money the player has to the screen
    std::stringstream convert;
    convert << "Money: " << player.GetMoney() << " Euro";
    std::string cashAmount  = convert.str();
    const char * cash = cashAmount.c_str();
    al_draw_text(font, fontColor, (cameraPosition.first + ScreenWidth) - 200, cameraPosition.second + 20, NULL, cash );
    al_draw_rounded_rectangle((cameraPosition.first + ScreenWidth) - 210, cameraPosition.second + 15, (cameraPosition.first + ScreenWidth) - 45, cameraPosition.second + 45, 5, 5, fontColor, 2) ;
}

void GameplayScreen::EntitiesInteraction()
{
    int sz = entityMan.entities.size();
    for(int i = 0; i < sz; i++)
    {
        Entity *ent = entityMan.entities[i];

        if(IsNearEntity(ent))
        {
            ent->isNear = true;

            if(std::strcmp(ent->textBoxText, "NULL") != 0 )
            {
                HudText = ent->textBoxText;
            }

            if(std::strcmp(ent->dialogText, "NULL") != 0 )
            {
                if(ent->type == ent->CHARACTER)
                {
                    int textBoxHeight = DrawWrappedText(font, ent->dialogText, ent->color, (ent->pos.first -(ent->sizeWidth/2)) - 100, (ent->pos.second - ent->sizeHeight) - (textBoxHeight+15), 200, ALLEGRO_ALIGN_LEFT, false);
                    DrawWrappedText(font, ent->dialogText, ent->color, (ent->pos.first -(ent->sizeWidth/2)) - 100, (ent->pos.second - ent->sizeHeight) - (textBoxHeight+15), 200, ALLEGRO_ALIGN_LEFT, true);
                    al_draw_rounded_rectangle((ent->pos.first -(ent->sizeWidth/2)) - 110, (ent->pos.second - ent->sizeHeight) - (textBoxHeight+20), (ent->pos.first -(ent->sizeWidth/2)) + 110, (ent->pos.second - ent->sizeHeight) - 15, 5, 5, ent->color, 2) ;
                }
                else
                {
                    int textBoxHeight = DrawWrappedText(font, ent->dialogText, ent->color, (ent->pos.first +(ent->sizeWidth/2)) - 100, ent->pos.second - (textBoxHeight+15), 200, ALLEGRO_ALIGN_LEFT, false);
                    DrawWrappedText(font, ent->dialogText, ent->color, (ent->pos.first +(ent->sizeWidth/2)) - 100, ent->pos.second - (textBoxHeight+15), 200, ALLEGRO_ALIGN_LEFT, true);
                    al_draw_rounded_rectangle((ent->pos.first +(ent->sizeWidth/2)) - 110, ent->pos.second - (textBoxHeight+20), (ent->pos.first +(ent->sizeWidth/2)) + 110, ent->pos.second - 15, 5, 5, ent->color, 2) ;
                }
            }
            if(std::strcmp(ent->entityName, "entity_blocks.txt") == 0 )
            {
                if(ent->isActionComplete)
                {
                    isEndGame = true;
                }
            }
        }
        else
        {
            ent->isNear = false;
        }
    }
}

int GameplayScreen::DrawWrappedText(ALLEGRO_FONT *af,char atext[1024],ALLEGRO_COLOR fc, int x1, int y1, int width, int flags,bool draw)
{
     char stext[1024]; // Copy of the passed text.
     char * pch; // A pointer to each word.
     char word[255]; // A string containing the word (for convienence)
     char breakchar[12]; // Contains the break line character "\n "
     char Lines[40][1024]; // A lovely array of strings to hold all the lines (40 max atm)
     char TempLine[1024]; // Holds the string data of the current line only.
     int CurrentLine = 0; // Counts which line we are currently using.
     int q; // Used for loops


     // Setup our strings
     strcpy(stext,atext);
     strcpy(breakchar,"\n ");
     strcpy(TempLine,"");
     for(q = 0;q < 40;q+=1)
     {
          sprintf(Lines[q],"");
     }
     //-------------------- Code Begins

     pch = strtok (stext," ");                               // Get the first word.
     do
     {
          strcpy(word,"");                                  // Truncate the string, to ensure there's no crazy stuff in there from memory.
          sprintf(word,"%s ",pch);
          sprintf(TempLine,"%s%s",TempLine,word);             // Append the word to the end of TempLine
          // This code checks for the new line character.
          if(strcmp(word,breakchar) == 0)
          {
                CurrentLine+=1;                                 // Move down a Line
                strcpy(TempLine,"");                            // Clear the tempstring
          }
          else
          {
                if(al_get_text_width(af,TempLine) >= (width))   // Check if text is larger than the area.
                {
                      strcpy(TempLine,word);                      // clear the templine and add the word to it.
                      CurrentLine+=1;                             // Move to the next line.
                }
                if(CurrentLine < 40)
                {
                      strcat(Lines[CurrentLine],word);                // Append the word to whatever line we are currently on.
                }
          }
          pch = strtok (NULL, " ");                           // Get the next word.
     }while (pch != NULL);
     // ---------------------------------- Time to draw.
     if(draw == true)                                       //Check whether we are actually drawing the text.
     {
          for(q = 0;q <=CurrentLine;q+=1)                     // Move through each line and draw according to the passed flags.
          {
                if(flags == ALLEGRO_ALIGN_LEFT)
                     al_draw_text(af,fc, x1, y1 + (q * al_get_font_line_height(af)), ALLEGRO_ALIGN_LEFT,Lines[q]);
                if(flags == ALLEGRO_ALIGN_CENTRE)
                     al_draw_text(af,fc, x1 + (width/2), y1 + (q * al_get_font_line_height(af)), ALLEGRO_ALIGN_CENTRE,Lines[q]);
                if(flags == ALLEGRO_ALIGN_RIGHT)
                     al_draw_text(af,fc, x1 + width, y1 + (q * al_get_font_line_height(af)), ALLEGRO_ALIGN_RIGHT,Lines[q]);
          }

     }
     return((CurrentLine+1) * al_get_font_line_height(af));  // Return the actual height of the text in pixels.
}

bool GameplayScreen::IsNearEntity(Entity *ent)
{
    float _playerX = player.GetPosition().first;
    float _playerY = player.GetPosition().second;
    float entX = ent->pos.first;
    float entY = ent->pos.second;
    float entWidth = ent->sizeWidth;
    float entHeight = ent->sizeHeight;

    if(ent->type == ent->CHARACTER)
    {
        if(_playerX  < (entX - entWidth) -180 || _playerX > entX + 80 || _playerY  < entY - 240|| _playerY > entY + entHeight + 50)
        {
        return false ;
        }
    }
    else if(ent->type == ent->OBJECT)
    {
        if(_playerX  < entX - 100 || _playerX > (entX + entWidth) + 20 || _playerY  < entY - 20|| _playerY > entY + entHeight+80)
        {
        return false ;
        }
    }

    return true ;
}

void GameplayScreen::DrawMap()
{
    int value ;

    for(int i = 0; i < worldMap.size(); i++)
    {
        for(int j = 0; j < worldMap[i].size(); j++)
        {
            al_draw_bitmap_region(tileSpriteSheet, worldMap[i][j] * BlockSize, 0,
                    BlockSize, BlockSize, j * BlockSize, i * BlockSize, NULL);
        }
    }
}

void GameplayScreen::LoadMap(const char *filename)
{
    std::ifstream openfile(filename) ;
    if(openfile.is_open())
    {
        std::string line, value ;
        int state = NULL;
        enum LoadState { TileSet, Map} ;

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
                    tileSpriteSheet = al_load_bitmap(line.c_str());
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
            }
        }
    }
    else
    {
        std::cout<<"Failed to open map file."<<std::endl;
    }
}

void GameplayScreen::CameraUpdate(float x, float y, int width, int height)
{
    cameraPosition.first = -(ScreenWidth / 2) + (x + width / 2);
    cameraPosition.second = -(ScreenWidth / 2) + (y + height / 2);

    if(cameraPosition.first < 0)
    {
        cameraPosition.first = 0 ;
    }
    if(cameraPosition.second < 0)
    {
        cameraPosition.second = 0 ;
    }
}
