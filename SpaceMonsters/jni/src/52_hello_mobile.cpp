
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and, strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include <sstream>


class number
{
public:

    void render (int x, int y, int width, int height,  std::string number);

private:




};

//The actual hardware texture
SDL_Texture* Map[4];
SDL_Texture* rocket;
SDL_Texture* numbers [10];
SDL_Texture* rock;
SDL_Texture* PauseButton;
SDL_Texture* MiniMenu;





class maps
{
public:
    void ScrollingMaps (void);
    void SpaceShipRender (void);
    bool collision (void);

private:
    int YScroll=0;
    void render (int x, int y, int width, int height,  int MapNumber);
    int random=1;
    int Last=1;
    int speed=0;

};
int MapW=0;
int MapH=0;
int RocketW=0;
int RocketH=0;
int NumberW=0;
int NumberH=0;

class buttons
{

public:
    void render (void);
    bool ClickedPause (int xcoordinate, int ycoordinate);


private:




};
//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();



    bool loadMedia(void);
    SDL_Texture* loadFromFile( std::string path, int width, int height );


    //Deallocates texture
    void free();



    //Renders texture at given point
    void render( int x, int y, SDL_Texture* Texture,int width,int height,  SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );



    //Gets image dimensions
    int getWidth();
    int getHeight();




private:
    //The actual hardware texture
    SDL_Texture* mTexture;


};
class rocks
{
public:
    void render(void);
    bool collisions (int RockNum);

private:

    int RockX[10]= {50,0,500,100,600,60,90,200,300,400};
    int RockY[10]= {0,0,0,0,0,0,0,0,0,0};
    bool WallCollision[10]= {0,0,0,0,0,0,0,0,0,0};
    int RockIncreaseX[10]= {20,10,5,2,10,20,15,16,1,3};
    int RockIncreaseY[10]= {20,10,5,2,10,8,2,4,5,8};
};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_Surface *screen =NULL;
LTexture gSplashTexture;

//Screen dimensions
SDL_Rect gScreenRect = { 0, 0, 320, 240 };
int RocketXDifference=0;
int RocketYDifference=0;
int RocketX=0;
int RocketY=0;

void buttons::render(void)
{
    gSplashTexture.render(gScreenRect.w-100,0,PauseButton, 100, 100);
}
bool buttons::ClickedPause (int xcoordinate, int ycoordinate)
{
    if (xcoordinate>=gScreenRect.w-100 and ycoordinate<=100)
    {
        return true;
    }
    return false;
}
void rocks::render (void)
{
    int max;
    max = 8;
    int random;
    for (int i=0; i<=4; i++)
    {
        random=(rand () % max + -2);
        for (int t=1; t<=RockIncreaseX[i]+random; t++)
        {


            if (RockX[i]>=gScreenRect.w-100)WallCollision[i]=true;
            else if (RockX[i]<=0)WallCollision[i]=false;
            if (WallCollision[i]!=true)
                RockX[i]+=1;
            else
                RockX [i]-=1;
            RockY[i]+=1;
            if (RockY[i]>=gScreenRect.h)RockY[i]=0;
            collisions(i);

        }
        gSplashTexture.render(RockX[i],RockY[i],rock, 100, 100);
    }
}
bool rocks::collisions(int RockNum)
{

        if (RockX[RockNum]+100>=RocketX and RockX[RockNum]<=RocketX+gScreenRect.w/10 and RockY[RockNum]>=RocketY and RockY[RockNum]<=RocketY+ gScreenRect.h/5)
        {
            SDL_Delay (10000);
            close();
            return true;
        }
}
LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;

}
bool maps::collision(void)
{

}
std::string IntToString (int integer)
{


    std::stringstream convert;   // stream used for the conversion

    convert << integer;      // insert the textual representation of 'Number' in the characters in the stream

    return convert.str();
}
char IntToChar (int integer)
{
    return (integer+48);
}
void maps::ScrollingMaps (void)
{


    int max;
    max = 4;

    if (YScroll>=gScreenRect.h)
    {
        Last=random;
        YScroll=0;
        srand(time(0)); //gets randomnum num using time
        random= (rand () % max + 1) ;
    }



    render (0,YScroll,gScreenRect.w, gScreenRect.h,Last);


    if (random<=2)
        render (0,YScroll-gScreenRect.h,gScreenRect.w, gScreenRect.h,random);
    else
        render (0,YScroll-gScreenRect.h,gScreenRect.w, gScreenRect.h,random);
    YScroll+=1+speed;

    if (speed!=20)
        speed+=1;

    return;
}
void maps::SpaceShipRender (void)
{
    RocketX=gScreenRect.w/2+RocketXDifference;
    RocketY=gScreenRect.h-gScreenRect.h/4-gScreenRect.h/10 +RocketYDifference;

    if (RocketY+gScreenRect.h/5>gScreenRect.h)
    {
        for (int i=1; RocketY+gScreenRect.h/5!=gScreenRect.h; i++)
        {
            RocketY-=1;
        }
    }
    else if (RocketY<0)
    {
        RocketY=0;
    }
    if (RocketX<0)
    {
        RocketX=0;
    }
    else if (RocketX+RocketW>=gScreenRect.w)
    {
        RocketX=gScreenRect.w-RocketW;
    }


    //Render splash
    gSplashTexture.render(RocketX, RocketY,rocket, RocketW,RocketH);
}
void maps::render (int x, int y, int width, int height,  int MapNumber)
{



    //Render splash
    gSplashTexture.render(x, y,Map[MapNumber-1],MapW, MapH);
}
void number::render (int x, int y, int width, int height,  std::string number)
{


    for (int i=0; i<number.length(); i++)
    {

        //Render splash
        gSplashTexture.render(x,y, numbers [(int)number [i]-48], NumberW, NumberH );
        x+=width;
    }
}
LTexture::~LTexture()
{
    //Deallocate
    free();
}

SDL_Texture* LTexture::loadFromFile( std::string path, int width, int height )
{


    //The final texture
    SDL_Texture* newTexture = IMG_LoadTexture(gRenderer,path.c_str());




    if( newTexture == NULL )
    {
        printf( "Unable to create texture from %s! SDL Error:%s\n", path.c_str(), SDL_GetError() );
    }




    return newTexture;
}




void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;


    }
    for (int i=0; i<=3; i++)
    {
        if (Map [i]!=NULL)
        {
            SDL_DestroyTexture(Map [i] );
            Map[i] = NULL;
        }
        if (numbers [i]!=NULL)
        {
            SDL_DestroyTexture( numbers [i] );
            numbers [i] = NULL;
        }

    }
    for (int i=4; i<=9; i++)
    {
        if (numbers [i]!=NULL)
        {
            SDL_DestroyTexture( numbers [i] );
            numbers [i] = NULL;
        }
    }

    if (rocket!=NULL)
    {
        SDL_DestroyTexture( rocket );
        rocket = NULL;
    }
    if (rock!=NULL)
    {
        SDL_DestroyTexture( rock);
        rock = NULL;
    }
    if (PauseButton!=NULL)
    {
        SDL_DestroyTexture( PauseButton);
        PauseButton = NULL;
    }
}





void LTexture::render( int x, int y, SDL_Texture* Texture ,int width,int height, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width, height };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, Texture, clip, &renderQuad, angle, center, flip );
}






bool init()
{
    //Initialization flag
    bool success = true;




    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {

        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            SDL_Log( "Warning: Linear texture filtering not enabled!" );
        }

        //Get device display mode
        SDL_DisplayMode displayMode;
        if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
        {
            gScreenRect.w = displayMode.w;
            gScreenRect.h = displayMode.h;

        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN);
        if( gWindow == NULL )
        {
            SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        }
    }

    return success;
}

bool LTexture::loadMedia(void)
{
//Get rid of preexisting texture
    free();

    Map[0]=loadFromFile("Map/Map1.JPG",gScreenRect.w, gScreenRect.h);
    Map[1]=loadFromFile("Map/Map2.JPG",gScreenRect.w, gScreenRect.h );
    Map[2]=loadFromFile("Map/Map3.JPG",gScreenRect.w, gScreenRect.h);
    Map[3]=loadFromFile("Map/Map4.JPG",gScreenRect.w, gScreenRect.h );
    MapW=gScreenRect.w;
    MapH=gScreenRect.h;
    rocket=loadFromFile("Rocket.JPG", gScreenRect.w/10, gScreenRect.h/5 );
    RocketW=gScreenRect.w/10;
    RocketH=gScreenRect.h/5;
    numbers [0]=loadFromFile("Numbers/0.JPG",100,100);
    numbers [1]=loadFromFile("Numbers/1.JPG",100,100);
    numbers [2]=loadFromFile("Numbers/2.JPG",100,100);
    numbers [3]=loadFromFile("Numbers/3.JPG",100,100);
    numbers [4]=loadFromFile("Numbers/4.JPG",100,100);
    numbers [5]=loadFromFile("Numbers/5.JPG",100,100);
    numbers [6]=loadFromFile("Numbers/6.JPG",100,100);
    numbers [7]=loadFromFile("Numbers/7.JPG",100,100);
    numbers [8]=loadFromFile("Numbers/8.JPG",100,100);
    numbers [9]=loadFromFile("Numbers/9.JPG",100,100);
    NumberW=100;
    NumberH=100;
    rock=loadFromFile("rock.PNG",100,100);
    PauseButton=loadFromFile("PauseButton.JPG",100,100);
    MiniMenu=loadFromFile("MiniMenu.JPG",100,100);



    for (int i=0; i<=3; i++)
    {
        if (Map [i]==NULL)
        {
            SDL_Log( "Map failed to load" );
            SDL_Delay (5000);
            return false;
        }
        if (numbers [i]==NULL)
        {
            return false;
        }

    }
    for (int i=4; i<=9; i++)
    {
        if (numbers [i]==NULL)return false;
    }

    if (rocket==NULL) return false;
    if (rock==NULL) return false;
    if (PauseButton==NULL) return false;

    return true;



}


void close()
{
    //Free loaded images
    gSplashTexture.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    int XNew=0;
    int YNew=0;
    int XOld=0;
    int YOld=0;
    int distance=0;
    bool RocketTouch=false;
    number Num;
    maps Maps;
    rocks Rocks;
    buttons Buttons;
    bool pause=false;
    //Start up SDL and create window
    if( !init())
    {
        SDL_Log( "Failed to initialize!\n" );
    }
    else
    {

        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;
        RocketXDifference=0;
        RocketYDifference=0;
        gSplashTexture.loadMedia();

        //While application is running
        while( !quit )
        {

            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }

                else if( e.type == SDL_WINDOWEVENT )
                {
                    //Window resize/orientation change
                    if( e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
                    {

                        //Get screen dimensions
                        gScreenRect.w = e.window.data1;
                        gScreenRect.h = e.window.data2;

                        gSplashTexture.loadMedia();





                        //Update screenRocketY-gScreenRect.h/5
                        SDL_RenderPresent( gRenderer );
                    }

                }
                //Touch motion
                else if( e.type == SDL_FINGERDOWN )
                {

                    RocketTouch=false;
                    if (Buttons.ClickedPause(e.tfinger.x * gScreenRect.w,e.tfinger.y * gScreenRect.h))
                    {


                        pause=true;

                    }
                    else if (e.tfinger.x * gScreenRect.w>=RocketX and e.tfinger.x * gScreenRect.w<=RocketX + gScreenRect.w/10 and
                             e.tfinger.y * gScreenRect.h>=RocketY and e.tfinger.y * gScreenRect.h<=RocketY + gScreenRect.h/5)
                    {
                        RocketTouch=true;
                    }



                }



                //Touch motion
                else if( e.type == SDL_FINGERMOTION and RocketTouch==true )
                {
                    RocketXDifference = e.tfinger.x * gScreenRect.w-gScreenRect.w/2;
                    RocketYDifference = e.tfinger.y * gScreenRect.h-(gScreenRect.h-gScreenRect.h/4);

                }
                else if( e.type == SDL_FINGERUP)
                {
                    SDL_Log("X ", IntToString(RocketX).c_str(), " Y ", IntToString(RocketY).c_str(), " "  );
                }
            }


            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
            SDL_RenderClear( gRenderer );





            //Maps.collision();



            //Maps.ScrollingMaps();

            Maps.SpaceShipRender();
            Num.render(10,12, 100,100,IntToString(distance));
            distance+=1;
            Rocks.render();
            Buttons.render();
            if (pause==true)
            {

                gSplashTexture.render(( gScreenRect.w - gScreenRect.w/2 ) / 2, ( gScreenRect.h - gScreenRect.h/4 ) / 2 ,MiniMenu, gScreenRect.w/2, gScreenRect.h/4);
            }

            //Update screen
            SDL_RenderPresent( gRenderer );
            if (pause==true)
            {
                SDL_Delay (5000);
                pause=false;

            }
            //Rocks.collisions();
        }
    }


//Free resources and close SDL
    close();

    return 0;
}
