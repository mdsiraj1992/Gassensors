/************************MQ3sensor************************************/
/************************Hardware Related Macros************************************/
#define         MQ3PIN                       (0)      //define which analog input channel you are going to use
#define         RL_VALUE_MQ3                 (1)      //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ3      (60.314) //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                      //which is derived from the chart in datasheet

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
                                                     //normal operation

/**********************Application Related Macros**********************************/
#define         GAS_ALCOHOL                  (4)
#define         GAS_BENZENE                  (7)
#define         GAS_METHANE                  (2)
#define         GAS_HEXANE                   (8)
#define         GAS_LPG                      (1)
#define         GAS_CARBON_MONOXIDE          (3)
#define         accuracy                     (0)   //for linearcurves
//#define         accuracy                   (1)   //for nonlinearcurves, un comment this line and comment the above line if calculations 
                                                   //are to be done using non linear curve equations
/*****************************Globals***********************************************/
float           Ro = 10;                            //Ro is initialized to 10 kilo ohms

void setup() {
  Serial.begin(9600);                               //UART setup, baudrate = 9600bps
  Serial.print("Calibrating...\n");                
  Ro = MQCalibration(MQ3PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");

}

void loop() {

   Serial.print("ALCOHOL:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ3PIN)/Ro,GAS_ALCOHOL) );
   Serial.print( "mg/L" );
   Serial.print("    ");   
   Serial.print("BENZENE:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ3PIN)/Ro,GAS_BENZENE) );
   Serial.print( "mg/L" );
   Serial.print("    ");   
   Serial.print("METHANE:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ3PIN)/Ro,GAS_METHANE) );
   Serial.print( "mg/L" );
   Serial.print("    ");   
   Serial.print("HEXANE:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ3PIN)/Ro,GAS_HEXANE) );
   Serial.print( "mg/L" );
   Serial.print("    ");   
   Serial.print("LPG:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ3PIN)/Ro,GAS_LPG) );
   Serial.print( "mg/L" );
   Serial.print("    ");   
   Serial.print("CARBON_MONOXIDE:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ3PIN)/Ro,GAS_CARBON_MONOXIDE) );
   Serial.print( "mg/L" );
   Serial.print("\n");
   delay(200);
}

/****************** MQResistanceCalculation ****************************************
Input:   raw_adc - raw value read from adc, which represents the voltage
Output:  the calculated sensor resistance
Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/ 
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE_MQ3*(1023-raw_adc)/raw_adc));
}

/***************************** MQCalibration ****************************************
Input:   mq_pin - analog channel
Output:  Ro of the sensor
Remarks: This function assumes that the sensor is in clean air. It use  
         MQResistanceCalculation to calculates the sensor resistance in clean air 
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about 
         10, which differs slightly between different sensors.
************************************************************************************/ 
float MQCalibration(int mq_pin)
{
  int i;
  float RS_AIR_val=0,r0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {                     //take multiple samples
    RS_AIR_val += MQResistanceCalculation(analogRead(mq_pin)); //Serial.println("RS_AIR_val:"); 
   //Serial.println(RS_AIR_val );
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val = RS_AIR_val/CALIBARAION_SAMPLE_TIMES;              //calculate the average value
 /*Serial.println("RS_AIR_val:"); 
   Serial.println(RS_AIR_val );
    Serial.println(RO_CLEAN_AIR_FACTOR_MQ3 );
    Serial.println(RS_AIR_val/RO_CLEAN_AIR_FACTOR_MQ3 );*/
  r0 = RS_AIR_val/RO_CLEAN_AIR_FACTOR_MQ3;                      //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                                 //according to the chart in the datasheet 
/* Serial.println("roval:"); 
   Serial.println(r0 );
   Serial.print( "mg/L" );*/
  return r0; 
}

/*****************************  MQRead *********************************************
Input:   mq_pin - analog channel
Output:  Rs of the sensor
Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different consentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macros.
************************************************************************************/ 
float MQRead(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
 /* Serial.println("RSval:"); 
   Serial.println( rs);*/}
 
    //Serial.println(rs );
   
  rs = rs/READ_SAMPLE_TIMES;
 //Serial.println(rs); Serial.println(Ro);
//  Serial.println(rs/Ro);
  return rs;  
}

/*****************************  MQGetGasPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         gas_id      - target gas type
Output:  mg/L of the target gas
Remarks: This function uses different equations representing curves of each gas to 
         calculate the mg/L (milligrams per litre) of the target gas.
************************************************************************************/ 
int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{ 
  if ( accuracy == 0 ) {
    /*Serial.println("calculating mq3 ALCOHOL  gases"); 
               Serial.print("rs_ro_ratio:  ");                                                        //debug statements that display step by step calculation of ppm
               Serial.println(rs_ro_ratio);
               Serial.print("gas_id:  ");                                                        //debug statements that display step by step calculation of ppm
               Serial.println(gas_id);*/
  if (  gas_id == GAS_ALCOHOL ) {
    /* Serial.println("calculating mq3 ALCOHOL  gases"); 
               Serial.print("rs_ro_ratio:  ");                                                        //debug statements that display step by step calculation of ppm
               Serial.println(rs_ro_ratio);
               Serial.print("log of rs_ro_ratio: ");
               Serial.println(log10(rs_ro_ratio));
               Serial.print("-1.487* log of rs_ro_ratio: ");
               Serial.println((-1.487 * (log10(rs_ro_ratio))));
              // Serial.print("pow of 10, 3.891* log of rs_ro_ratio: ");
              // Serial.println(pow(10, ((-3.891 * (log10(rs_ro_ratio))))));
               Serial.print("-1.487 * log of rs_ro_ratio-0.401: ");
               Serial.println((-1.487  * (log10(rs_ro_ratio)))-0.401);*/
    return (pow(10,((-1.487*(log10(rs_ro_ratio))) - 0.401)));
  } else if ( gas_id == GAS_BENZENE ) {
    return (pow(10,((-2.659*(log10(rs_ro_ratio))) + 0.659)));
  } else if ( gas_id == GAS_METHANE ) {
    return (pow(10,((-17.95*(log10(rs_ro_ratio))) + 29.59)));
  } else if ( gas_id == GAS_HEXANE ) {
    return (pow(10,((-2.851*(log10(rs_ro_ratio))) + 3.889)));
  } else if ( gas_id == GAS_LPG ) {
    return (pow(10,((-3.386*(log10(rs_ro_ratio))) + 4.915)));
  } else if ( gas_id == GAS_CARBON_MONOXIDE ) {
    return (pow(10,((-3.947*(log10(rs_ro_ratio))) + 5.924)));
  }   
} 

  else if ( accuracy == 1 ) {
    if ( gas_id == GAS_ALCOHOL ) {
    return (pow(10,((-1.487*(log10(rs_ro_ratio))) - 0.401)));
  } else if ( gas_id == GAS_BENZENE ) {
    return (pow(10,(-2.877*pow((log10(rs_ro_ratio)), 3) + 2.084*pow((log10(rs_ro_ratio)), 2) - 2.925*(log10(rs_ro_ratio)) + 0.643)));
  } else if ( gas_id == GAS_METHANE ) {
    return (pow(10,((-17.95*(log10(rs_ro_ratio))) + 29.59)));
  } else if ( gas_id == GAS_HEXANE ) {
    return (pow(10,(1.795*pow((log10(rs_ro_ratio)), 3) - 7.343*pow((log10(rs_ro_ratio)), 2) + 7.020*(log10(rs_ro_ratio)) - 0.467)));
  } else if ( gas_id == GAS_LPG ) {
    return (pow(10,(-2.335*pow((log10(rs_ro_ratio)), 2) + (3.263*(log10(rs_ro_ratio))) + 0.253)));
  } else if ( gas_id == GAS_CARBON_MONOXIDE ) {
    return (pow(10,(-14.40*pow((log10(rs_ro_ratio)), 3) + 59.52*pow((log10(rs_ro_ratio)), 2) -84.98*(log10(rs_ro_ratio)) + 42.26)));
  }
}    
  return 0;
}

