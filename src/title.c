#include "common.h"
#include "video.h"
#include "audio.h"
#include "game.h"
#include "system.h"

int     titleJSW[] =
{
    100, 101, 102, 104, 105, 106, 108, 109, 110, 113, 114, 115, 117, 118, 119, 121, 122, 123,
    133, 136, 141, 145, 149, 154,
    165, 168, 169, 170, 173, 177, 178, 179, 181, 182, 183, 186,
    197, 200, 205, 211, 213, 218,
    228, 229, 232, 233, 234, 237, 241, 242, 243, 245, 246, 247, 250,
    326, 330, 332, 334, 338, 341, 345,
    358, 362, 364, 366, 370, 373, 377,
    390, 392, 394, 396, 398, 402, 405, 406, 407, 408, 409,
    422, 424, 426, 428, 430, 434, 439,
    454, 455, 456, 457, 458, 460, 462, 463, 464, 466, 467, 468, 471
};

char    textJSW[6] = "\x1\x2\x2\xb\x14";

char    textTicker[] = "      Press ENTER to Start                                JET-SET WILLY by Matthew Smith   1984 SOFTWARE PROJECTS Ltd                                Guide Willy to collect all the items around the house before Midnight so Maria will let you get to your bed                                Press ENTER to Start      ";

int     textPos, textEnd = (int)sizeof(textTicker) - 33;
int     textFrame;
BYTE    colourCycle;
int     colourCycleAdj[6] = {1, 2, 3, 4, 5, 1};
int     titleFlash = 0;

void GameStart( void )
{
    Video_PixelFill(128 * WIDTH, 64 * WIDTH);

    Game_GameReset();
    Game_DrawStatus();

    gameLevel = THEBATHROOM;
    itemCount = Level_ItemCount();
    Level_RestoreItems();

    Miner_Init(); // start position

    if (cheatEnabled)
    {
        Robots_DrawCheat();
    }

    gameMode = GM_NORMAL;
    gamePaused = 0;

    Game_Action();
}

void DoTitleTicker( void )
{
    char    swap;

    if (audioMusicPlaying)
    {
        if (titleFlash != videoFlash)
        {
            swap = textJSW[3];
            textJSW[3] = textJSW[1];
            textJSW[1] = swap;
            titleFlash = videoFlash;
        }

        return;
    }

    colourCycle = colourCycleAdj[colourCycle];

    if (textPos < textEnd)
    {
        if (textFrame < 6)
        {
            textFrame += 2;
            return;
        }
        textPos++;
        textFrame = 0;

        return;
    }

    Action = Title_Action;
}

void DoTitleDrawer( void )
{
    int tile, *pos = &titleJSW[0];

    if (audioMusicPlaying)
    {
        for (tile = 0; tile < 100; tile++, pos++)
        {
            Video_Write(TILE2PIXEL(*pos), textJSW);
        }

        return;
    }

    if (colourCycle == 1)
    {
        Video_CycleColours(0);
    }

    Video_WriteLarge(0, 0, "\x1\x1\x2\x7");
    Video_WriteLarge(-(textFrame & 6), 19 * 8, textTicker + textPos);
}

void DoTitleResponder( void )
{
    if (gameInput == KEY_ENTER)
    {
        Action = GameStart;
    }
    else if (gameInput == KEY_ESCAPE)
    {
        DoQuit();
    }
}

void DoTitleInit( void )
{
    System_Border(0x0);
    Video_PixelFill(0, WIDTH * HEIGHT);

    Video_Write(16 * WIDTH + 144, "\x1\x0\x2\x5\x10\x11\x12\x13");
    Video_Write(24 * WIDTH + 128, "\x10\x14\x1\x5\x14\x14\x2\x9\x10\x14");
    Video_Write(32 * WIDTH + 112, "\x1\x0\x2\x5\x10\x11\x1\x5\x14\x14\x2\x9\x10\x11\x1\x9\x14\x14");
    Video_Write(40 * WIDTH + 96, "\x1\x0\x2\x5\x10\x14\x1\x5\x14\x14\x2\x9\x10\x14\x1\x9\x14\x14\x14\x14");
    Video_Write(48 * WIDTH + 80, "\x1\x0\x2\x5\x10\x11\x1\x5\x14\x14\x2\x9\x10\x11\x1\x9\x14\x14\x2\x1\x10\x14\x14\x14");
    Video_Write(56 * WIDTH + 64, "\x1\x0\x2\x5\x14\x14\x1\x5\x14\x14\x2\x9\x10\x14\x1\x9\x14\x14\x2\x0\x10\x14\x1\x1\x14\x14\x1\x9\x14\x14");
    Video_Write(64 * WIDTH + 64, "\x1\x5\x2\x1\x12\x13\x14\x14\x1\x9\x2\x5\x12\x13\x2\x0\x10\x11\x1\x0\x14\x14\x1\x1\x14\x14\x1\x9\x14\x14");
    Video_Write(72 * WIDTH + 64, "\x1\x1\x14\x14\x1\x5\x2\x1\x12\x13\x14\x14\x1\x0\x2\x5\x12\x13\x14\x14\x1\x1\x14\x14\x1\x9\x14\x14");
    Video_Write(80 * WIDTH + 64, "\x1\x1\x2\x0\x12\x13\x14\x14\x1\x5\x2\x1\x14\x13\x14\x14\x1\x0\x2\x5\x12\x13\x1\x1\x14\x14\x1\x9\x14\x14");
    Video_Write(88 * WIDTH + 80, "\x1\x1\x2\x0\x14\x13\x14\x14\x1\x5\x2\x1\x14\x13\x14\x14\x1\x1\x14\x14\x1\x9\x14\x14");
    Video_Write(96 * WIDTH + 96, "\x1\x1\x2\x0\x14\x13\x14\x14\x1\x5\x2\x1\x12\x13\x1\x1\x14\x14\x1\x9\x14\x14");
    Video_Write(104 * WIDTH + 112, "\x1\x1\x2\x0\x14\x13\x14\x14\x14\x14\x1\x9\x14\x14");
    Video_Write(112 * WIDTH + 128, "\x1\x1\x14\x13\x14\x14\x1\x9\x14\x14");
    Video_Write(120 * WIDTH + 144, "\x1\x1\x12\x13\x1\x9\x10\x11");

    Video_WriteLarge(0, 0, "\x1\x0\x2\x4");
    Video_WriteLarge(0, 19 * 8, textTicker);

    textPos = 0;
    textFrame = -1;
    colourCycle = 1;

    Audio_Music(MUS_TITLE, MUS_PLAY);

    Ticker = DoTitleTicker;
}

void Title_Action( void )
{
    Responder = DoTitleResponder;
    Ticker = DoTitleInit;
    Drawer = DoTitleDrawer;

    Action = DoNothing;
}
