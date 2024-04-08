#ifndef _ADVANCED_H
#define _ADVANCED_H


#include "vsh.h"


#define SUBITEM_DEFAULT 0

#define SUBITEM_REGION 1
#define SUBITEM_REGION_END 13

#define SUBITEM_USBREADONLY 14
#define SUBITEM_USBREADONLY_END 15

#define SUBITEM_SWAPXO 18
#define SUBITEM_SWAPXO_END 19

#define SUBITEM_PANDORA 39
#define SUBITEM_PANDORA_END 40

#define SUBITEM_UNSUPPORTED 50

#define SUBITEM_USBDEVICE 52
#define SUBITEM_USBDEVICE_END 55

#define SUBITEM_NONE 56

#define SUBITEM_COLOR 57
#define SUBITEM_COLOR_END 85


enum {
	SUBMENU_USB_DEVICE,
	SUBMENU_USB_READONLY,
	SUBMENU_UMD_VIDEO,
	SUBMENU_FG_COLORS,
	SUBMENU_BG_COLORS,
	SUBMENU_FONT,
	SUBMENU_MENU_DESIGN,
	SUBMENU_MAIN_MENU,
	SUBMENU_CONVERT_BATTERY,
	SUBMENU_SWAP_XO_BUTTONS,
	SUBMENU_REGION_MODE,
	SUBMENU_UMD_REGION_MODE,
	SUBMENU_IMPORT_CLASSIC_PLUGINS,
	SUBMENU_ACTIVATE_FLASH_WMA,
	SUBMENU_DELETE_HIBERNATION,
	SUBMENU_RANDOM_GAME,
	SUBMENU_GO_BACK,
	SUBMENU_MAX
};


int submenu_draw(void);
int submenu_find_longest_string(void);
int submenu_setup(void);
int submenu_ctrl(u32 button_on);
void subbutton_func(vsh_Menu *vsh);


#endif