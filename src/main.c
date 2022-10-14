#include <stdint.h>
#include <stddef.h>

#define TV_NTSC 1
#include "famitone2.h"
#include "nes.h"
#include "reset.h"
#include "rle.h"

#include "data.h"


typedef enum state {
    STATE_TITLE,
    STATE_SCREEN_TIMELINE,
    STATE_SCREEN_OTHEREXP,
    STATE_SCREEN_CEH,
    STATE_SCREEN_OSCP,
    STATE_SCREEN_CCSSA,
    STATE_SCREEN_ONION,
    STATE_SCREEN_SPEAKING,
    STATE_SCREEN_SPEAKING_2,
    STATE_SCREEN_NESDEV,
    STATE_SCREEN_QR,
    STATE_SCREEN_END,
    STATE_FADE
} state_t;


#pragma bss-name(push, "ZEROPAGE")
uint8_t i;             // loop counter/temp
uint8_t j;             // loop counter/temp
state_t state;
const uint8_t * bg;    // background data
uint8_t pattern_table; // 0 or 1


// used by WritePPU method
uintptr_t       ppu_addr;      // destination PPU address
uint8_t const * ppu_data;      // pointer to data to copy to PPU
uint8_t         ppu_data_size; // # of bytes to copy to PPU
#pragma bss-name(pop)


#pragma bss-name(push, "OAM")
sprite_t text_sprites[1]; // 4x8 grid
#pragma bss-name(pop)


void ResetScroll() {
    PPU_SCROLL = 0x00;
    PPU_SCROLL = 0x00;
}


void EnablePPU() {
    i = PPUCTRL_NAMETABLE_0 | // use nametable 0
        PPUCTRL_NMI_ON      ; // enable NMIs

    if(pattern_table == 0) {
        i |= (PPUCTRL_BPATTERN_0 | PPUCTRL_SPATTERN_0);
    } else {
        i |= (PPUCTRL_BPATTERN_1 | PPUCTRL_SPATTERN_1);
    }

    PPU_CTRL = i;
    PPU_MASK = PPUMASK_COLOR    | // show colors
               PPUMASK_BSHOW    | // show background
               PPUMASK_L8_BSHOW | // show background tiles in leftmost 8px
               PPUMASK_SSHOW    | // show sprites
               PPUMASK_L8_SSHOW ; // show sprites in leftmost 8px
}


void DisablePPU() {
    PPU_CTRL = 0x00;
    PPU_MASK = 0x00;
}


void WritePPU() {
    PPU_ADDRESS = (uint8_t)(ppu_addr >> 8);
    PPU_ADDRESS = (uint8_t)(ppu_addr);
    for ( i = 0; i < ppu_data_size; ++i ) {
        PPU_DATA = ppu_data[i];
    }
}


void DrawBackground() {
    PPU_ADDRESS = (uint8_t)(PPU_NAMETABLE_0 >> 8);
    PPU_ADDRESS = (uint8_t)(PPU_NAMETABLE_0);
    UnRLE(bg);
}


void InitTitle() {
    DisablePPU();

    state = STATE_TITLE;
    pattern_table = 1;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_TITLE;
    ppu_data_size = sizeof(PAL_TITLE);
    WritePPU();

    // draw background
    bg = BG_TITLE;
    DrawBackground();

    // play music
    FamiToneMusicPlay(SONG_TITLE);

    WaitVBlank();
    EnablePPU();
}


void InitScreenTimeline() {
    DisablePPU();

    state = STATE_SCREEN_TIMELINE;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_TIMELINE;
    ppu_data_size = sizeof(PAL_SCREEN_TIMELINE);
    WritePPU();

    // draw background
    bg = BG_SCREEN_TIMELINE;
    DrawBackground();

    // play music
    FamiToneMusicPlay(SONG_SCREEN_1);

    WaitVBlank();
    EnablePPU();
}


void InitScreenOTHEREXP() {
    DisablePPU();

    state = STATE_SCREEN_OTHEREXP;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_OTHEREXP;
    ppu_data_size = sizeof(PAL_SCREEN_OTHEREXP);
    WritePPU();

    // draw background
    bg = BG_SCREEN_OTHEREXP;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenCEH() {
    DisablePPU();

    state = STATE_SCREEN_CEH;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_CEH;
    ppu_data_size = sizeof(PAL_SCREEN_CEH);
    WritePPU();

    // draw background
    bg = BG_SCREEN_CEH;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenOSCP() {
    DisablePPU();

    state = STATE_SCREEN_OSCP;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_OSCP;
    ppu_data_size = sizeof(PAL_SCREEN_OSCP);
    WritePPU();

    // draw background
    bg = BG_SCREEN_OSCP;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenCCSSA() {
    DisablePPU();

    state = STATE_SCREEN_CCSSA;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_CCSSA;
    ppu_data_size = sizeof(PAL_SCREEN_CCSSA);
    WritePPU();

    // draw background
    bg = BG_SCREEN_CCSSA;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenONION() {
    DisablePPU();

    state = STATE_SCREEN_ONION;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_ONION;
    ppu_data_size = sizeof(PAL_SCREEN_ONION);
    WritePPU();

    // draw background
    bg = BG_SCREEN_ONION;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenQR() {
    DisablePPU();

    state = STATE_SCREEN_QR;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_QR;
    ppu_data_size = sizeof(PAL_SCREEN_QR);
    WritePPU();

    // draw background
    bg = BG_SCREEN_QR;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenSPEAKING() {
    DisablePPU();

    state = STATE_SCREEN_SPEAKING;
    pattern_table = 1;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_SPEAKING;
    ppu_data_size = sizeof(PAL_SCREEN_SPEAKING);
    WritePPU();

    // draw background
    bg = BG_SCREEN_SPEAKING;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenSPEAKING_2() {
    DisablePPU();

    state = STATE_SCREEN_SPEAKING_2;
    pattern_table = 1;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_SPEAKING_2;
    ppu_data_size = sizeof(PAL_SCREEN_SPEAKING_2);
    WritePPU();

    // draw background
    bg = BG_SCREEN_SPEAKING_2;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenNESDEV() {
    DisablePPU();

    state = STATE_SCREEN_NESDEV;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_NESDEV;
    ppu_data_size = sizeof(PAL_SCREEN_NESDEV);
    WritePPU();

    // draw background
    bg = BG_SCREEN_NESDEV;
    DrawBackground();

    WaitVBlank();
    EnablePPU();
}


void InitScreenEnd() {
    DisablePPU();

    state = STATE_SCREEN_END;
    pattern_table = 0;

    // write palettes
    ppu_addr = PPU_PALETTE;
    ppu_data = PAL_SCREEN_END;
    ppu_data_size = sizeof(PAL_SCREEN_END);
    WritePPU();

    // draw background
    bg = BG_SCREEN_END;
    DrawBackground();

    // play music
    FamiToneMusicPlay(SONG_SCREEN_END);

    WaitVBlank();
    EnablePPU();
}


void HandleInput() {
    switch(state) {
        case STATE_TITLE:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenTimeline();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenTimeline();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_TIMELINE:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenOTHEREXP();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenOTHEREXP();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_OTHEREXP:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenCEH();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenCEH();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_CEH:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenOSCP();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenOSCP();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_OSCP:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenCCSSA();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenCCSSA();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_CCSSA:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenONION();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenONION();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_ONION:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenSPEAKING();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenSPEAKING();
                FamiToneSfxPlay(SFX_START);
            }
            break;
            case STATE_SCREEN_SPEAKING:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenSPEAKING_2();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenSPEAKING_2();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_SPEAKING_2:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenNESDEV();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenNESDEV();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_NESDEV:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenQR();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenQR();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_QR:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitScreenEnd();
                FamiToneSfxPlay(SFX_START);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitScreenEnd();
                FamiToneSfxPlay(SFX_START);
            }
            break;
        case STATE_SCREEN_END:
            if ((InputPort1 & BUTTON_START) && !(InputPort1Prev & BUTTON_START)) {
                InitTitle();
                FamiToneSfxPlay(SFX_RING);
            }
            if ((InputPort1 & BUTTON_A) && !(InputPort1Prev & BUTTON_A)) {
                InitTitle();
                FamiToneSfxPlay(SFX_RING);
            }
            break;
        default:
            break;
    }
}


void Update() {
    switch(state) {
        // case STATE_OSCP:
        //     UpdateCredits();
        //     break;
        // case STATE_SCREEN_1:
        //     break;
    default:
        break;
    }
}


void main(void) {
    FamiToneInit();
    FamiToneSfxInit();
    InitTitle();

    // turn on rendering
    ResetScroll();
    EnablePPU();

    while (1) {
        WaitFrame();
        FamiToneUpdate();
        HandleInput();
       // Update();
        ResetScroll();
    };
};