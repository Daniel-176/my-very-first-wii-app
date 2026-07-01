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
    typedef struct {
        bool isOpened;
        char title[64];
        char message[128];
    } Modal;

    Modal testy = {false, "Test", "coding with loop is pain"};
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
 

        //got these from web
        void DrawModal() {
            if (!testy.isOpened) return;

            GRRLIB_Rectangle(0, 0, 640, 480, 0x000000C8, 1);

            GRRLIB_Rectangle(120, 140, 400, 200, 0xFFFFFFFF, 1);
            GRRLIB_Rectangle(118, 138, 404, 204, 0x000000FF, 0);

            GRRLIB_PrintfTTF(140, 160, comicsans, testy.title, 20, 0x000000FF);
            GRRLIB_PrintfTTF(140, 200, comicsans, testy.message, 16, 0x000000FF);
        }



        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
 

        // Get the IR (infrared) state for the first Wiimote
        ir_t ir;
        WPAD_IR(0, &ir);
        GRRLIB_FillScreen(0xFFFFFFFF);
        
        int cursorX = (ir.x / 1024.0f) * 640;
        int cursorY = (ir.y / 768.0f) * 480;

        void DrawIR() {
            int cursorX = (ir.x / 1024.0f) * 640;
            int cursorY = (ir.y / 768.0f) * 480;
            if(ir.valid) {
                GRRLIB_DrawImg(cursorX, cursorY, myTplTexture, 0, 0.5, 0.5, 0xFFFFFFFF);
                hasusedirbefore = true;
            }
        }

        /// omgg button

        bool mabuttonishover = ((cursorX < 100 && cursorX > 4) && (cursorY > 4 && cursorY < 100));

        GRRLIB_Rectangle(4, 4, 101, 21, 0x000000FF, 0);
        if(mabuttonishover) {
            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A) {
                GRRLIB_Rectangle(5, 5, 100, 20, 0x222222FF, 1);
                testy.isOpened = true;
            } else {
                GRRLIB_Rectangle(5, 5, 100, 20, 0xAAAAAAFF, 1);
            }
        } else {
            GRRLIB_Rectangle(5, 5, 100, 20, 0xFFFFFFFF, 1);
        }
        GRRLIB_PrintfTTFW(4, 4, comicsans, L"wats ts", 16, 0x0000FFFF);

        // ---------------------------------------------------------------------
        // Place your drawing code here
        // ---------------------------------------------------------------------
        if(ir.valid) {
            
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

        DrawModal();
        DrawIR();
        GRRLIB_Render();  // Render the frame buffer to the TV
    }
 
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
 
    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}