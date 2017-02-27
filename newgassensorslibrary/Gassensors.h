#ifndef gassensors_H
#define gassensors_H
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*MQ-GAS SENSORS LIBRARY*/
/************************Hardware Related Macros************************************/
/*#define         MQ2                 2
#define         MQ3                 3
#define         MQ4                 4
#define         MQ5                 5
#define         MQ6                 6
#define         MQ7                 7
#define         MQ8                 8
#define         MQ9                 9
#define         MQ135               135*/

#define         RL_VALUE_MQ2                 (5)        //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ2      (9.83)     //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                        //which is derived from the chart in datasheet
#define         RL_VALUE_MQ3                 (200)
#define         RO_CLEAN_AIR_FACTOR_MQ3      (9.83)

#define         RL_VALUE_MQ4                 (20)
#define         RO_CLEAN_AIR_FACTOR_MQ4      (9.83)

#define         RL_VALUE_MQ5                 (20)
#define         RO_CLEAN_AIR_FACTOR_MQ5      (9.83)

#define         RL_VALUE_MQ6                 (20)
#define         RO_CLEAN_AIR_FACTOR_MQ6      (9.83)

#define         RL_VALUE_MQ7                 (10)
#define         RO_CLEAN_AIR_FACTOR_MQ7      (9.83)

#define         RL_VALUE_MQ8                 (4.7)
#define         RO_CLEAN_AIR_FACTOR_MQ8      (9.83)

#define         RL_VALUE_MQ9                 (4.7)
#define         RO_CLEAN_AIR_FACTOR_MQ9      (9.83)

#define         RL_VALUE_MQ135                 (20)
#define         RO_CLEAN_AIR_FACTOR_MQ135      (9.83)


/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (5)   //define the time interal(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
                                                     //normal operation
                                                     
/**********************Application Related Macros**********************************/
#define         GAS_HYDROGEN                  (0)
#define         GAS_LPG                       (1)
#define         GAS_METHANE                   (2)
#define         GAS_CARBON_MONOXIDE           (3)
#define         GAS_ALCOHOL                   (4)
#define         GAS_SMOKE                     (5)
#define         GAS_PROPANE                   (6)
#define         GAS_BENZENE                   (7)
#define         GAS_HEXANE                    (8)
#define         GAS_CARBON_DIOXIDE            (9)
#define         GAS_3by4AE                    (10)
#define         GAS_AMMONIUM                  (11)
#define         GAS_1by4                      (12)
#define         GAS_NAME                      (13)

#define         accuracy                      (0)   //for linearcurves
//#define         accuracy                    (1)   //for nonlinearcurves, un comment this line and comment the above line if calculations
                                                    //are to be done using non linear curve equations
/*****************************Globals***********************************************/

class Gassensors {
  public:
    //int Gassensor_no=2;
    Gassensors(uint8_t pin, uint8_t type, uint8_t Gas_Name);
    float MQResistanceCalculation(int raw_adc);
    float MQCalibration(int mq_pin);
    float MQRead(int mq_pin);
    int MQGetGasPercentage(float rs_ro_ratio, int gas_id);
    int gasppm(uint8_t pin, uint8_t type,int mqgases_id=0, uint8_t Gas_Name=0 );
    float rs_ro_ratio(uint8_t pin);
    void printallgases(uint8_t type);
  private:
    uint8_t _pin, _type, _Gas_Name, _Rovalues[], RL_VALUE, RO_CLEAN_AIR_FACTOR;
};
#endif
