#ifndef BG_SCREEN_END_H_
#define BG_SCREEN_END_H_

#include <stdint.h>

const uint8_t BG_SCREEN_END[112]={
0x03,0x00,0x03,0x8e,0xf4,0xf5,0x00,0x03,0x1c,0xf2,0xf0,0xf1,0xf3,0x00,0x03,0x1c,
0xdf,0xef,0x00,0x03,0x1d,0xbd,0xcf,0x00,0x03,0x1d,0xcd,0xce,0x00,0x03,0x1d,0xdd,
0xde,0x00,0x03,0x1d,0xed,0xee,0x00,0x03,0x1d,0xfd,0xfe,0x00,0x03,0x56,0x01,0x00,
0x17,0x09,0x0e,0x0e,0x05,0x12,0x00,0x09,0x13,0x00,0x19,0x0f,0x15,0x00,0x03,0xfe,
0x00,0x03,0xea,0x80,0xa0,0xa0,0x20,0x00,0x20,0x00,0x80,0xa8,0x02,0xa8,0x22,0x82,
0xa0,0xa0,0x00,0x03,0x02,0x88,0x22,0x00,0x80,0x20,0x00,0x03,0x05,0x88,0x22,0x00,
0x00,0x2a,0x02,0x00,0x00,0x88,0x02,0x00,0x00,0x02,0x00,0x03,0x13,0x00,0x03,0x00
};

const uint8_t PAL_SCREEN_END[16]={ 0x0f,0x00,0x10,0x30,0x0f,0x01,0x21,0x31,0x0f,0x02,0x05,0x25,0x0f,0x09,0x19,0x29 };

#endif // BG_SCREEN_END_H_