#ifndef __AUDIO_H__
#define __AUDIO_H__

#define MUS_STOP    0
#define MUS_PLAY    1

enum
{
    MUS_TITLE,
    MUS_GAME,
    MUS_LOADER
};

enum
{
    SFX_ITEM,
    SFX_DIE,
    SFX_GAMEOVER,
    SFX_ARROW,
    SFX_WILLY,
    SFX_NONE
};

extern int  audioMusicPlaying;
extern int  audioPanX;
#ifndef NO_AUDIO
void Audio_Init(void);
void Audio_Music(int, int);
void Audio_Play(int);
void Audio_WillySfx(int, int);
void Audio_Sfx(int);
void Audio_ReduceMusicSpeed(void);
void Audio_Callback(short *buffer, int length);
#else
#define Audio_Init(...)
#define Audio_Music(...)
#define Audio_Play(...)
#define Audio_WillySfx(...)
#define Audio_Sfx(...)
#define Audio_ReduceMusicSpeed(...)
#define Audio_Callback(...)
#endif

#endif
