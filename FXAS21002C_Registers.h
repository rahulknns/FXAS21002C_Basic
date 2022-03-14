
#ifndef FXAS21002C_REGISTERS_H
#define FXAS21002C_REGISTERS_H

//Values for different configuration

#define STANDBY             0b00000000
#define ACTIVE              0b00000010
#define DEFAULT_ODR         100
#define DEFAULT_FSR         1000
//Register Addresses
#define OUT_X_MSB_REG 0x01
#define OUT_Y_MSB_REG 0x03
#define OUT_Z_MSB_REG 0x05
#define CTRL_REG0     0x0D
#define CTRL_REG1     0x13
#define CTRL_REG2     0x14
#define CTRL_REG3     0x15


//Bitmasks   
#define POWER_MODE_BITS      0b00000010
#define ODR_BITS             0b00011100 
#define FSR_BITS             0b00000011
#endif