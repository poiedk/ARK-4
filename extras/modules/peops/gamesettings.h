#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include "common.h"

typedef struct{ /* PEOPS SPU configuration */
    int enablepeopsspu;
    int volume;
    int reverb;
    int interpolation;
    int enablexaplaying;
    int changexapitch;
    int spuirqwait;
    int spuupdatemode;
    int sputhreadpriority;
} PeopsConfig;

enum ReverbType{
    REVERB_OFF = 0x0000,
    REVERB_ROOM = 0x007D,
    REVERB_STUDIO_SMALL = 0x0033,
    REVERB_STUDIO_MEDIUM = 0x00B1,
    REVERB_STUDIO_LARGE = 0x00E3,
    REVERB_HALL = 0x01A5,
    REVERB_SPACE_ECHO = 0x033D,
    REVERB_ECHO_DELAY = 0x0001,
    REVERB_HALF_ECHO = 0x0017,
};

enum SPU_UpdateMode{
    SPU_WAITVBLANK = 0,
    SPU_DELAY2 = 1,
    SPU_DELAY20 = 2,
};

enum SPU_Priorities{
    SPU_PRIORITY_VERY_LOW = 0,
    SPU_PRIORITY_LOW = 1,
    SPU_PRIORITY_MEDIUM = 2,
    SPU_PRIORITY_HIGH = 3,
    SPU_PRIORITY_VERY_HIGH = 4,
};

void loadGameSettings(char* gameid, PeopsConfig* conf);

#endif
