#include "FXAS21002C_Basic.h"
#include "FXAS21002C_Registers.h"
#include "EEPROM.h"

//Constructor
FXAS21002CBasic::FXAS21002CBasic(byte address, int port_no)
{
    while (!((address >= 0x20) && (address <= 0x21)))
    {
        Serial.println("Invalid address for FXAS21002C");
        delay(1000);
    }
    setupDevice(address,port_no);
    checkConnection();
    changeRange(DEFAULT_FSR);
    changeODR(DEFAULT_ODR);
}

//Changes device between active and Standby Mode
void FXAS21002CBasic::changePowerMode(byte mode)
{
    writeBitsToReg(CTRL_REG1,POWER_MODE_BITS,mode);
}

//Wait till power mode transits
void FXAS21002CBasic::waitTill(byte mode)
{ 
    while (readPowerMode() != mode)
        {
        }

}

//Returns the current system mode
byte FXAS21002CBasic::readPowerMode()
{
    return readBitsFromReg(CTRL_REG1,POWER_MODE_BITS);
}

//Changes the device output data rate
void FXAS21002CBasic::changeODR(int odr)
{

     if (readPowerMode() != STANDBY)
    {
        changePowerMode(STANDBY);
        waitTill(STANDBY);
    }

    switch (odr)
    {
    case 800:
        writeBitsToReg(CTRL_REG1,ODR_BITS,0b00000000);
        break;
    case 400:
        writeBitsToReg(CTRL_REG1,ODR_BITS,0b00000100);
        break;
    case 200:
        writeBitsToReg(CTRL_REG1,ODR_BITS,0b00001000);
        break;
    case 100:
        writeBitsToReg(CTRL_REG1,ODR_BITS,0b00001100);
        break;
    case  50:
        writeBitsToReg(CTRL_REG1,ODR_BITS,0b00010000);
        break;
    case  25:
        writeBitsToReg(CTRL_REG1,ODR_BITS,0b00010100);
        break;
    case  12:
        writeBitsToReg(CTRL_REG1,ODR_BITS,0b00011000);
        break;

    default:
        break;
    }

    changePowerMode(ACTIVE);
    waitTill(ACTIVE);

}

//change range of gyro, doesn't offer fsr boost!
void FXAS21002CBasic::changeRange(int fsr)
{
     if (readPowerMode() != STANDBY)
    {
        changePowerMode(STANDBY);
        waitTill(STANDBY);
    }

    switch (fsr)
    {
    case 2000:
        writeBitsToReg(CTRL_REG0,FSR_BITS,0b00000000);
       sensitivity = 7.8125*8*0.001;
        break;
    case 1000:
        writeBitsToReg(CTRL_REG0,FSR_BITS,0b00000001);
        sensitivity = 7.8125*4*0.001;
        break;
    case 500:
        
        writeBitsToReg(CTRL_REG0,FSR_BITS,0b00000010);
        sensitivity = 7.8125*2*0.001;
        break;
    case 250:
        
        writeBitsToReg(CTRL_REG0,FSR_BITS,0b00000011);
        sensitivity = 7.8125*1*0.001;
        break;
    
    default:
        break;
    
   
    }

     //Entering Active Mode
    changePowerMode(ACTIVE);
    waitTill(ACTIVE);

}

//Load calibration constants from eeprom
void FXAS21002CBasic::loadCalibrationData(byte eeprom_address){
     byte temp[4*3];
    for (int i = 0; i < 4*3; i++)
    {
        temp[i] = EEPROM.read(eeprom_address + i);
    }
    memcpy(gyro_offset_,temp,4*3);

}
//update angular acceleration
void FXAS21002CBasic::updateGyroData(float* gyro_data)
{ 
    gyro_data[0]  = (readShortIntFromReg(OUT_X_MSB_REG)*sensitivity) - gyro_offset_[0];
    gyro_data[1]  = (readShortIntFromReg(OUT_Y_MSB_REG)*sensitivity) - gyro_offset_[1]; 
    gyro_data[2]  = (readShortIntFromReg(OUT_Z_MSB_REG)*sensitivity) - gyro_offset_[2];
    
    return ;

}