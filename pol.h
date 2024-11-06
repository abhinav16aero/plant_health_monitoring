#ifndef HELPER_H
#define HELPER_H

#include"co2.h"
#include"dust.h"


class PollutantSensors{
    private:
        CO2 co2_sensor;
        DUST dust_sensor;
    public:
        char reading[512];

        PollutantSensors();
        void Sample(Stream &dustport, Stream &co2port);
        void WriteToBuff(void);
};

PollutantSensors::PollutantSensors(){
    co2_sensor=CO2();
    dust_sensor=DUST();
}

void PollutantSensors::Sample(Stream &dustport, Stream &co2port){
    // Serial.println("Read dust");
    dust_sensor.Sample(dustport);
    
    co2_sensor.Sample(co2port);
    // Serial.println("Read co2");
    WriteToBuff();
}

void PollutantSensors::WriteToBuff(){
  sprintf(reading,"{\"T\":%d%d.%d,\"H\":%d%d.%d,\"FMHDS\":%d,\"PMS1\":%d,\"PMS2_5\":%d,\"PMS10\":%d,\"CO2\":%d}",
  dust_sensor.TPS/100, (dust_sensor.TPS/10)%10, dust_sensor.TPS%10, 
  dust_sensor.HDS/100, (dust_sensor.HDS/10)%10, dust_sensor.HDS%10, 
  dust_sensor.FMHDS, 
  dust_sensor.PMS1,
  dust_sensor.PMS2_5,
  dust_sensor.PMS10,
  co2_sensor.co2
  );

  // sprintf(reading,"{\"CO2\":%d}",co2_sensor.co2);
}


#endif