
#ifndef FXAS21002C_BASIC_H
#define FXAS21002C_BASIC_H
#include "I2C_device.h"

class FXAS21002CBasic: protected I2CDevice
{
protected:
   float sensitivity;
   

public:
   FXAS21002CBasic() =default;
   FXAS21002CBasic(byte address,int port_no = 0);

  
   void getGyroData(float* gyro_data);
   void changeODR(int odr);
   void changeRange(int fsr);
  

   void changePowerMode(byte mode);
   byte readPowerMode();
   void waitTill(byte mode);

};
#endif


