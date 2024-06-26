/*
 * BitMath.h
 *
 * Created: 5/13/2024 12:20:18 AM
 *  Author: shady
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_

#define SetBit(Reg,BitNo) (Reg |= (1<<BitNo))
#define ClearBit(Reg,BitNo) (Reg &= ~(1<<BitNo))
#define ToggleBit(Reg,BitNo) (Reg ^= (1<<BitNo))
#define GetBit(Reg,BitNo) ((Reg>>BitNo) & 1)

#endif /* BITMATH_H_ */