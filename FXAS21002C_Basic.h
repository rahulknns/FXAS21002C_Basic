
#ifndef FXAS21002C_BASIC_H
#define FXAS21002C_BASIC_H
#include "I2C_device.h"

//Values for different configuration

#define STANDBY             0b00000000
#define ACTIVE              0b00000010
#define DEFAULT_ODR         100
#define DEFAULT_FSR         1000
#define DEFAULT_ADDRESS     0X1E

class FXAS21002CBasic: protected I2CDevice
{
protected:
   float sensitivity_;
   

public:
   FXAS21002CBasic() =default;
   FXAS21002CBasic(byte address = DEFAULT_ADDRESS,TwoWire preferred_wire = &Wire);

  
   void updateGyroData(float* gyro_data);
   void changeODR(int odr);
   void changeRange(int fsr);
  

   void changePowerMode(byte mode);
   byte readPowerMode();
   void waitTill(byte mode);

};
#endif


