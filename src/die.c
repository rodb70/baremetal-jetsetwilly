#include "common.h"
#include "video.h"
#include "game.h"
#include "audio.h"
#include "system.h"

int dieLevel;

void Die_Drawer( void )
{
    Video_PixelInkFill(0, 128 * WIDTH, dieLevel >> 1);
}

void Die_Ticker( void )
{
    if (dieLevel-- > 0)
    {
        return;
    }

    if (gameLives < 0)
    {
        Action = Gameover_Action;
        return;
    }

    Video_DrawSprite(LIVES + gameLives * 16, minerSprite[8], 0x0, 0x0); // blank frame

    Miner_Restore();

    Audio_ReduceMusicSpeed();

    Action = Game_Action;
}

void Die_Init( void )
{
    gameLives--;

    dieLevel = 15;

    System_Border(0x0);
    Video_PixelPaperFill(0, 128 * WIDTH, 0x0);

    audioPanX = minerWilly.x;
    Audio_Sfx(SFX_DIE);

    Ticker = Die_Ticker;
}

void Die_Action()
{
    Responder = DoNothing;
    Ticker = Die_Init;
    Drawer = Die_Drawer;

    Action = DoNothing;
}
