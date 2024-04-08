/**
 * \file bme280.c
 * \author Ugurcan OZTURK
 * \brief	BME280 Sensor Source File
 * \date 26.03.2024
 */


 /******************************************************************************
 *** INCLUDES
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "bme280.h"

/******************************************************************************
 *** DEFINES
 ******************************************************************************/
#define    STOPPER                0                                      
#define    MEDIAN_FILTER_SIZE     5

/******************************************************************************
 *** VARIABLES
 ******************************************************************************/
BME280_registerCtrl_meas_t ctrl_measConf;
BME280_registerConfig_t configReg;
uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;  
int32_t t_fine;
int32_t rawTemp;


/******************************************************************************
 *** FUNCTION PROTOTYPES
 ******************************************************************************/

/** \brief  BME280 operating mode initialize function
 * \param modeStatus Operating mode selection
 * \return Nothing
 */
static void BME280_ModeInit(BME280_modestatus_e modeStatus);

/** \brief  BME280 humadity oversampling initialize function
 * \param humOver Humadity oversampling selection
 * \return Humadity Oversampling status
 */
static int16_t BME280_HumadityOverSamp(BME280_hum_oversampling_e humOver);

/** \brief  BME280 pressure oversampling initialize function
 * \param pressOver Pressure oversampling selection
 * \return Pressure Oversampling status
 */
static int16_t BME280_PressOverSamp(BME280_press_oversampling_e pressOver);

/** \brief  BME280 temperature oversampling initialize function
 * \param tempOver Temperature oversampling selection
 * \return Temperature Oversampling status
 */
static int16_t BME280_TempOverSamp(BME280_temp_oversampling_e tempOver);

/** \brief  BME280 internal IIR filter initialize function
 * \param filterStatus Filter mode selection
 * \return 
 */
static int16_t BME280_FilterInit(BME280_filtermode_e filterStatus);

/** \brief  BME280 controls inactive duration tstandby in normal mode
 * \param standbyStatus StandBy value selection
 * \return 
 */
static int16_t BME280_StandByInit(BME280_standbymode_e standbyStatus);

/** \brief  BME280 sensor read the trimming parameters
 * \param[] Nothing
 * \return 
 */

void BME280_ReadTrimmingTemperature(void);

/** \brief  BME280 sensor read and compensation
 * \param adc_T Raw temperature data
 * \return T Final data
 */

int32_t BME280_compensate_T_int32(int32_t adc_T);



/******************************************************************************
 *** LOCAL FUNCTIONS
 ******************************************************************************/

static int16_t BME280_HumadityOverSamp(BME280_hum_oversampling_e humOver){
     
     uint16_t rx_flag;
     uint8_t flag;

     flag = humOver;

    BME280_registerctrlhum_t humaditySample;
     
     switch (flag)
     {
     case HUM_OVERSAMPLING_X1:
          humaditySample.bit.osrs_h_u3 = 0x01;
          break;
     case HUM_OVERSAMPLING_X2:
          humaditySample.bit.osrs_h_u3 = 0x02;
          break;
     case HUM_OVERSAMPLING_X4:
          humaditySample.bit.osrs_h_u3 = 0x03;
          break;
     case HUM_OVERSAMPLING_X8:
          humaditySample.bit.osrs_h_u3 = 0x04;
          break;
     case HUM_OVERSAMPLING_X16:
          humaditySample.bit.osrs_h_u3 = 0x05;
          break;
     }

     bme280_register_write(REGISTER_CTRL_HUM_ADDR, humaditySample.u8);

     bme280_register_read(REGISTER_CTRL_HUM_ADDR,&rx_flag,sizeof(rx_flag));

     if(rx_flag == 0x8000)
     {
          rx_flag = HUM_OVERSAMPLING_NO;
     }else
     {
          rx_flag = humOver;
     }
     
     return rx_flag;
}

static int16_t BME280_FilterInit(BME280_filtermode_e filterStatus){
     
     uint8_t flag;

     flag = filterStatus;

     switch (flag)
     {
     case BME280_FILTER_OFF:
          configReg.bit.filter_u3 = 0x00; 
          break;
     case BME280_FILTER_X2:
          configReg.bit.filter_u3 = 0x01;
          break;
     case BME280_FILTER_X4:
          configReg.bit.filter_u3 = 0x02;
          break;
     case BME280_FILTER_X8:
          configReg.bit.filter_u3 = 0x03;
          break;
     case BME280_FILTER_X16:
          configReg.bit.filter_u3 = 0x04;
          break;
     }

     return flag;
}

static int16_t BME280_StandByInit(BME280_standbymode_e standbyStatus){
     
     uint8_t flag;

     flag = standbyStatus;

     switch (flag)
     {
     case BME280_STANDBY_5: 
          configReg.bit.t_sb_u3 = 0x00;
          break;
     case BME280_STANDBY_625:
          configReg.bit.t_sb_u3 = 0x01;
          break;
     case BME280_STANDBY_1250:
          configReg.bit.t_sb_u3 = 0x02;
          break;
     case BME280_STANDBY_2500:
          configReg.bit.t_sb_u3 = 0x03;
          break;
     case BME280_STANDBY_5000:
          configReg.bit.t_sb_u3 = 0x04;
          break;
     case BME280_STANDBY_10000:
          configReg.bit.t_sb_u3 = 0x05;
          break;
     case BME280_STANDBY_100:
          configReg.bit.t_sb_u3 = 0x06;
          break;
     case BME280_STANDBY_200:
          configReg.bit.t_sb_u3 = 0x07;
          break;
     }
     return flag;
}

void BME280_ReadTrimmingTemperature(void){

     uint8_t flaglsb_T1;
     uint8_t flagmsb_T1;
     uint8_t flaglsb_T2;
     uint8_t flagmsb_T2;
     uint8_t flaglsb_T3;
     uint8_t flagmsb_T3;

     bme280_register_read(REGISTER_CALIBRATION_TEMP1,&flaglsb_T1,sizeof(flaglsb_T1));

     bme280_register_read(REGISTER_CALIBRATION_TEMP2,&flagmsb_T1,sizeof(flagmsb_T1));

     dig_T1 = ((uint16_t)flagmsb_T1 << 8) | flaglsb_T1;

     bme280_register_read(REGISTER_CALIBRATION_TEMP3,&flaglsb_T2,sizeof(flaglsb_T2));

     bme280_register_read(REGISTER_CALIBRATION_TEMP4,&flagmsb_T2,sizeof(flagmsb_T2));

     dig_T2 = ((int16_t)flagmsb_T2 << 8) | flaglsb_T2;

     bme280_register_read(REGISTER_CALIBRATION_TEMP5,&flaglsb_T3,sizeof(flaglsb_T3));

     bme280_register_read(REGISTER_CALIBRATION_TEMP6,&flagmsb_T3,sizeof(flagmsb_T3));

     dig_T3 = ((int16_t)flagmsb_T3 << 8) | flaglsb_T3;
}

int32_t BME280_compensate_T_int32(int32_t adc_T){

     int32_t var1, var2, T;
     var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
     var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1)))  >> 12) * ((int32_t)dig_T3)) >> 14;
     t_fine = var1 + var2;
     T = (t_fine * 5 + 128) >> 8;
     return T;
}

static void BME280_ModeInit(BME280_modestatus_e modeStatus){

    uint8_t flag;

     flag = modeStatus;

     switch (flag)
     {
     case BME280_SLEEP_MODE:
          ctrl_measConf.bit.mode_u2 = 0x00;
          break;
     case BME280_FORCED_MODE:
          ctrl_measConf.bit.mode_u2 = 0x01;
          break;
     case BME280_NORMAL_MODE:
          ctrl_measConf.bit.mode_u2 = 0x03;
          break;
     }
}

static int16_t BME280_PressOverSamp(BME280_press_oversampling_e pressOver){
     uint8_t flag;

     flag = pressOver;

     switch (flag)
     {
     case PRESS_OVERSAMPLING_X1:
          ctrl_measConf.bit.osrs_p_u3 = 0x01;
          break;
     case PRESS_OVERSAMPLING_X2:
          ctrl_measConf.bit.osrs_p_u3 = 0x02;
          break;
     case PRESS_OVERSAMPLING_X4:
          ctrl_measConf.bit.osrs_p_u3 = 0x03;
          break;
     case PRESS_OVERSAMPLING_X8:
          ctrl_measConf.bit.osrs_p_u3 = 0x04;
          break;
     case PRESS_OVERSAMPLING_X16:
          ctrl_measConf.bit.osrs_p_u3 = 0x05;
          break;
     }

     return flag;
}

static int16_t BME280_TempOverSamp(BME280_temp_oversampling_e tempOver){
      
      uint8_t flag;

      flag = tempOver;

     switch (flag)
     {
     case TEMP_OVERSAMPLING_X1:
          ctrl_measConf.bit.osrs_t_u3 = 0x01;
          break;
     case TEMP_OVERSAMPLING_X2:
          ctrl_measConf.bit.osrs_t_u3 = 0x02;
          break;
     case TEMP_OVERSAMPLING_X4:
          ctrl_measConf.bit.osrs_t_u3 = 0x03;
          break;
     case TEMP_OVERSAMPLING_X8:
          ctrl_measConf.bit.osrs_t_u3 = 0x04;
          break;
     case TEMP_OVERSAMPLING_X16:
          ctrl_measConf.bit.osrs_t_u3 = 0x05;
          break;
     }

     return flag;
}     

/******************************************************************************
 *** GLOBAL FUNCTIONS
 ******************************************************************************/

void BME280_ctrlmeasInit (void){
     
     BME280_ModeInit(BME280_NORMAL_MODE);
     BME280_PressOverSamp(PRESS_OVERSAMPLING_X16);
     BME280_TempOverSamp(TEMP_OVERSAMPLING_X2);

     bme280_register_write(REGISTER_CTRL_MEAS_ADDR,ctrl_measConf.u8);

}

void BME280_configRegisterInit(void){

    BME280_FilterInit(BME280_FILTER_X16);
    BME280_StandByInit(BME280_STANDBY_5);

    bme280_register_write(REGISTER_CONFIG_ADDR,configReg.u8);

}

void BME280_reset(BME280_resetmode_e resetMode){
     
     if(resetMode == BME280_RESET_ENABLE){
     BME280_registerReset_t resetSelection;

     resetSelection.u8 = 0xB6;

     bme280_register_write(REGISTER_RESET_ADDR,resetSelection.u8);
     }
}


void BME280_Init(void){
     
     BME280_ctrlmeasInit();                           // 0xF4                             
     BME280_HumadityOverSamp(HUM_OVERSAMPLING_X1);    //0xF2
     BME280_configRegisterInit();                     //0xF5
                                               
}


int32_t BME280_CalculateTemp(void){

     uint8_t flagxlsb;
     uint8_t flaglsb;
     uint8_t flagmsb;

     bme280_register_read(REGISTER_TEMP_XLSB_ADDR,&flagxlsb,sizeof(flagxlsb));

     bme280_register_read(REGISTER_TEMP_LSB_ADDR,&flaglsb,sizeof(flaglsb));

     bme280_register_read(REGISTER_TEMP_MSB_ADDR,&flagmsb,sizeof(flagmsb));

     rawTemp = (flagmsb << 12) | (flaglsb << 4) | (flagxlsb >> 4);
     
     BME280_ReadTrimmingTemperature();
    

     return BME280_compensate_T_int32(rawTemp);
}

uint16_t bme280_median_filter(uint16_t bmeData)
{
 struct pair
 {
   struct pair *point;                              /* Pointers forming list linked in sorted order */
   uint16_t     value;                                   /* Values to sort */
 };
 static struct pair buffer[MEDIAN_FILTER_SIZE] = {0}; /* Buffer of nwidth pairs */
 static struct pair *datpoint = buffer;               /* Pointer into circular buffer of data */
 static struct pair small = {NULL, STOPPER};          /* Chain stopper */
 static struct pair big = {&small, 0};                /* Pointer to head (largest) of linked list.*/

 struct pair *successor;                              /* Pointer to successor of replaced data item */
 struct pair *scan;                                   /* Pointer used to scan down the sorted list */
 struct pair *scanold;                                /* Previous value of scan */
 struct pair *median;                                 /* Pointer to median */
 uint16_t i;

 if (bmeData == STOPPER)
 {
   bmeData = STOPPER + 1;                            
 }
 if ( (++datpoint - buffer) >= MEDIAN_FILTER_SIZE)
 {
   datpoint = buffer;                               
 }

 datpoint->value = bmeData;                          
 successor = datpoint->point;                       
 median = &big;                                    
 scanold = NULL;                                    
 scan = &big;                                      
 /* Handle chain-out of first item in chain as special case */
 if (scan->point == datpoint)
 {
   scan->point = successor;
 }
 scanold = scan;                                     
 scan = scan->point ;                                

 /* Loop through the chain, normal loop exit via break. */
 for (i = 0 ; i < MEDIAN_FILTER_SIZE; ++i)
 {
   /* Handle odd-numbered item in chain  */
   if (scan->point == datpoint)
   {
     scan->point = successor;                      
   }

   if (scan->value < bmeData)                       
   {
     datpoint->point = scanold->point;            
     scanold->point = datpoint;                    
     bmeData = STOPPER;
   };

   /* Step median pointer down chain after doing odd-numbered element */
   median = median->point;                       
   if (scan == &small)
   {
     break;                                      
   }
   scanold = scan;                               
   scan = scan->point;                          

   /* Handle even-numbered item in chain.  */
   if (scan->point == datpoint)
   {
     scan->point = successor;
   }

   if (scan->value < bmeData)
   {
     datpoint->point = scanold->point;
     scanold->point = datpoint;
     bmeData = STOPPER;
   }

   if (scan == &small)
   {
     break;
   }

   scanold = scan;
   scan = scan->point;
 }
 return median->value;
}