#include "common.h"
#include "system.h"
#include "video.h"
#include "audio.h"

EVENT   Action = Loader_Action;
EVENT   Responder = DoNothing;
EVENT   Ticker = DoNothing;
EVENT   Drawer = DoNothing;

int     gameRunning = 1, gameInput;

int     videoFlash = 0;
int     videoSync = 0;

void DoNothing()
{
}

void DoQuit()
{
    gameRunning = 0;
    Drawer = DoNothing;
    Ticker = DoNothing;
}

int main()
{
    int flash = 0;

    Audio_Init();
    System_Init();

    while (gameRunning)
    {
        Action();

        while (System_PollKeys(&gameInput))
        {
            Responder();
        }

        Ticker();
        Drawer();

        Video_Draw();
        System_VideoUpdate();

        do
        {
            System_Delay();
        }
        while (!videoSync);
        videoSync = 0;

        flash++;
        if (flash == 20)
        {
            flash = 0;
            videoFlash = 1 - videoFlash;
        }
    }

    System_Quit();

    return 0;
}
