#include "misc.h"
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
    TIMER   timer;
    int     flash = 0;
    int     sync;
    int     rate;
    int     frame;

    Audio_Init();

    rate = System_Init();
    sync = rate > TICKRATE;
    Timer_Set(&timer, TICKRATE, rate);
    if (timer.rate < 1)
    {
        timer.rate = 1;
        timer.remainder = 0;
    }
    frame = timer.rate;

    while (gameRunning)
    {
        Action();

        while (System_PollKeys(&gameInput))
        {
            Responder();
        }

        System_LockTexture();
        Ticker();
        Drawer();
        System_UnlockTexture();

        flash++;
        if (flash == 20)
        {
            flash = 0;
            videoFlash = 1 - videoFlash;
        }

        if (--frame > 0)
        {
            continue;
        }

        frame = Timer_Update(&timer);

        videoSync = 0;
        do
        {
            System_Delay();
        }
        while (!videoSync && sync);

        System_VideoUpdate();
    }

    System_Quit();

    return 0;
}
