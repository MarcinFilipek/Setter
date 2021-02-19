/*
 * TColorDesc.h
 *
 *  Created on: 18 sie 2014
 *      Author: sporysz
 */

#ifndef TCOLORDESC_H_
#define TCOLORDESC_H_

#include <stdint.h>

union TColorDesc
{
    struct
    {
        uint8_t A;
        uint8_t B;
        uint8_t G;
        uint8_t R;
    }STRUCT;
    uint32_t RGBA;

    static TColorDesc fromARGB(uint8_t A, uint8_t R, uint8_t G, uint8_t B)
    {
    	TColorDesc color;
    	color.STRUCT.A = A;
    	color.STRUCT.R = R;
    	color.STRUCT.G = G;
    	color.STRUCT.B = B;
    	return color;
    }
};

#define COLDESC_EXPAND_RGB(x) x.STRUCT.R, x.STRUCT.G, x.STRUCT.B
#define COLDESC_EXPAND_RGBA(x) x.STRUCT.R, x.STRUCT.G, x.STRUCT.B, x.STRUCT.A



#endif /* TCOLORDESC_H_ */
