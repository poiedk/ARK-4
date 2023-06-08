#ifndef UMD_H
#define UMD_H

#include <pspumd.h>
#include "entry.h"
#include "gfx.h"

#define UMD_ICON0_PATH "disc0:/PSP_GAME/ICON0.PNG"
#define UMD_ICON1_PATH "disc0:/PSP_GAME/ICON1.PMF"
#define UMD_PIC0_PATH "disc0:/PSP_GAME/PIC0.PNG"
#define UMD_PIC1_PATH "disc0:/PSP_GAME/PIC1.PNG"
#define UMD_SND0_PATH "disc0:/PSP_GAME/SND0.AT3"
#define UMD_EBOOT_BIN "disc0:/PSP_GAME/SYSDIR/EBOOT.BIN"
#define UMD_EBOOT_OLD "disc0:/PSP_GAME/SYSDIR/EBOOT.OLD"
#define UMD_SFO_PATH "disc0:/PSP_GAME/PARAM.SFO"
#define UMD_APITYPE 0x120

using namespace std;

class UMD : public Entry{

    private:
        string umdname;

    public:
    
        UMD();
        ~UMD();
    
        string getName();
        
        void loadIcon();
        void getTempData1();
        void getTempData2();
        SfoInfo getSfoInfo();

        void doExecute();
        
        char* getType();
        char* getSubtype();
        
        static bool isUMD();
};

#endif
