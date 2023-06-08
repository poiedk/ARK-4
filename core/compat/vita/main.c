/*
 * This file is part of PRO CFW.

 * PRO CFW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRO CFW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRO CFW. If not, see <http://www.gnu.org/licenses/ .
 */

#include <pspsdk.h>
#include <pspsysmem_kernel.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <systemctrl_private.h>
#include <globals.h>
#include "functions.h"
#include "macros.h"
#include "exitgame.h"
#include "libs/graphics/graphics.h"

#include "core/compat/vita/rebootex/payload.h"

PSP_MODULE_INFO("ARKCompatLayer", 0x3007, 1, 0);

ARKConfig* ark_config = NULL;
SEConfig* se_config = NULL;

// Previous Module Start Handler
STMOD_HANDLER previous = NULL;

extern void ARKVitaOnModuleStart(SceModule2 * mod);

// Flush Instruction and Data Cache
void flushCache()
{
    // Flush Instruction Cache
    sceKernelIcacheInvalidateAll();
    
    // Flush Data Cache
    sceKernelDcacheWritebackInvalidateAll();
}

static void processArkConfig(){
    se_config = sctrlSEGetConfig(NULL);
    ark_config = sctrlHENGetArkConfig(NULL);
    if (ark_config->exec_mode == DEV_UNK){
        ark_config->exec_mode = PS_VITA; // assume running on PS Vita
    }
    if (ark_config->launcher[0] == '\0'){
        strcpy(ark_config->launcher, ARK_MENU);
    }
}

// Boot Time Entry Point
int module_start(SceSize args, void * argp)
{

    // set rebootex for Vita
    sctrlHENSetRebootexOverride(rebootbuffer_vita);

    // copy configuration
    processArkConfig();
    
    // Vita patches
    PROVitaSysPatch();
    
    // Register Module Start Handler
    previous = sctrlHENSetStartModuleHandler(ARKVitaOnModuleStart);
   
    flushCache();
    
    // Return Success
    return 0;
}

int module_stop(SceSize args, void *argp)
{
    spuShutdown();
    return 0;
}
