/*===========================================
        GRRLIB (GX Version)
        - Template Code -
 
        Minimum Code To Use GRRLIB
============================================*/
#include <grrlib.h>
 
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <ogc/tpl.h>

#include "helo_tpl.h"
#include "lol_tpl.h"
#include "cattie_tpl.h"
 
//Comic Sans
#include "comicsans.h"

int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();
    GRRLIB_ttfFont *comicsans = GRRLIB_LoadTTF(Comic_Sans_MS_ttf, Comic_Sans_MS_ttf_len);
 
    // Initialise the Wiimotes
    WPAD_Init();
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
    
    //Texture
    GRRLIB_texImg *myTplTexture;
    myTplTexture = GRRLIB_LoadTextureTPL(helo_tpl, 0);
    GRRLIB_SetMidHandle(myTplTexture, 1);

    GRRLIB_texImg *lol;
    lol = GRRLIB_LoadTextureTPL(lol_tpl, 0);
    GRRLIB_SetMidHandle(lol, 1);

    GRRLIB_texImg *cattie;
    cattie = GRRLIB_LoadTextureTPL(cattie_tpl, 0);
    GRRLIB_SetMidHandle(cattie, 1);

    bool hasusedirbefore = false;

    // Loop forever
    while(SYS_MainLoop()) {
        WPAD_ScanPads();  // Scan the Wiimotes
 
        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
 

        // Get the IR (infrared) state for the first Wiimote
        ir_t ir;
        WPAD_IR(0, &ir);

        // ---------------------------------------------------------------------
        // Place your drawing code here
        // ---------------------------------------------------------------------
        GRRLIB_FillScreen(0xFFFFFFFF);
        if(ir.valid) {
            int cursorX = (ir.x / 1024.0f) * 640;
            int cursorY = (ir.y / 768.0f) * 480;
            // Draw a basic crosshair if a valid IR signal is detected
            GRRLIB_DrawImg(cursorX, cursorY, myTplTexture, 0, 0.5, 0.5, 0xFFFFFFFF);
            hasusedirbefore = true;
        }
        else
        {
            if(hasusedirbefore) {
                GRRLIB_FillScreen(0xFFFFFFFF);
                GRRLIB_DrawImg(320, 240, lol, 0, 1, 1, 0xFFFFFFFF);
                GRRLIB_PrintfTTFW(160, 240, comicsans, L"HAHH NO IR DETECTED", 16, 0xFF0000FF);
            } else {
                GRRLIB_FillScreen(0xFFFFFFFF);
                GRRLIB_DrawImg(320, 240, cattie, 0, 1, 1, 0xFFFFFFFF);
                GRRLIB_PrintfTTFW(160, 240, comicsans, L"pls sir get your wiimote on screen", 16, 0x0000FFFF);
            }
        }

        GRRLIB_Render();  // Render the frame buffer to the TV
    }
 
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
 
    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}