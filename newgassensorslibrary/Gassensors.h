#ifndef gassensors_H
#define gassensors_H
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*MQ-GAS SENSORS LIBRARY*/
/************************Hardware Related Macros************************************/
#define         MQ2                 2
#define         MQ3                 3
#define         MQ4                 4
#define         MQ5                 5
#define         MQ6                 6
#define         MQ7                 7
#define         MQ8                 8
#define         MQ9                 9
#define         MQ135               135

#define         RL_VALUE_MQ2                  1           //define the load resistance connected to the gas sensor on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ2       9.577       //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO, which is extracted from the graph in datasheet

#define         RL_VALUE_MQ3                  1   
#define         RO_CLEAN_AIR_FACTOR_MQ3       60.314

#define         RL_VALUE_MQ4                  1  
#define         RO_CLEAN_AIR_FACTOR_MQ4       4.434

#define         RL_VALUE_MQ5                  1   
#define         RO_CLEAN_AIR_FACTOR_MQ5       6.455

#define         RL_VALUE_MQ6                  1    
#define         RO_CLEAN_AIR_FACTOR_MQ6       9.94

#define         RL_VALUE_MQ7                  1      
#define         RO_CLEAN_AIR_FACTOR_MQ7       26.09

#define         RL_VALUE_MQ8                  1     
#define         RO_CLEAN_AIR_FACTOR_MQ8       1

#define         RL_VALUE_MQ9                  1      
#define         RO_CLEAN_AIR_FACTOR_MQ9       9.799

#define         RL_VALUE_MQ135                1       
#define         RO_CLEAN_AIR_FACTOR_MQ135     3.59


/***********************Software Related Macros************************************/

#define         READ_SAMPLE_INTERVAL         (150)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (15)     //define the time interal(in milisecond) between each samples in normal operation
                                                     
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
#define         GAS_AMMONIUM                  (10)
#define         GAS_TOLUENE                   (11)
#define         GAS_ACETONE                   (12)

//#define         accuracy                      (0)   //for linearcurves
#define         accuracy                    (1)   //for nonlinearcurves, un comment this line and comment the above line if calculations
                                                    //are to be done using non linear curve equations
                                                    
/*****************************Gassensors class***********************************************/

class Gassensors {
  public:
    Gassensors(uint8_t pin, uint8_t type);
    float MQResistanceCalculation(int raw_adc);
    float MQRead(int mq_pin);
    int MQGetGasPercentage(float rs_ro_ratio, int gas_id);
    int gasppm(uint8_t pin, uint8_t type,int mqgases_id );
    float rs_ro_ratio(uint8_t pin);
    void printallgases(uint8_t type);
  private:
    uint8_t _pin, _type, RL_VALUE=1, RO_CLEAN_AIR_FACTOR;
    float _Rovalues[9]={8.82, 65.52,  59.47,  6.79, 8.4,  1.9,  98, 8.7,  17.85}; 
    // Run the Gassensors_calibration.ino file in clean air conditions to find out Rovalues and enter them in this array                    
};
#endif
