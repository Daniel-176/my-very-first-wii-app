/*===========================================
        GRRLIB (GX Version)
        - Template Code -
 
        Minimum Code To Use GRRLIB
============================================*/
#include <grrlib.h>
 
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <ogc/tpl.h>

#include "textures_tpl.h"
#include "textures.h"
 
int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();
 
    // Initialise the Wiimotes
    WPAD_Init();
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
    
    //Texture
    GRRLIB_texImg *myTplTexture;
    // Arguments: (raw_tpl_array_pointer, texture_id_inside_tpl)
    myTplTexture = GRRLIB_LoadTextureTPL(textures_tpl, 0);

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
        GRRLIB_FillScreen(0x000000FF);
        if(ir.valid) {
            // Draw a basic crosshair if a valid IR signal is detected
            GRRLIB_DrawImg(ir.sx, ir.sy, myTplTexture, 0, 1, 1, 0xFFFFFFFF);
            
        }
        else
        {
            GRRLIB_Line(0, 0, 640, 480, 0xFFFFFFFF, true);
            GRRLIB_Line(640, 0, 0, 480, 0xFFFFFFFF, true);
        }

        GRRLIB_Render();  // Render the frame buffer to the TV
    }
 
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
 
    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}