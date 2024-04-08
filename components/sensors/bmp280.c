/**
 * \file bmp280.c
 * \author Ugurcan OZTURK
 * \brief	BMP280 Sensor Source File
 * \date 04.04.2024
 */


 /******************************************************************************
 *** INCLUDES
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "bmp280.h"

/******************************************************************************
 *** DEFINES
 ******************************************************************************/
#define    STOPPER                0                                      
#define    MEDIAN_FILTER_SIZE     5

/******************************************************************************
 *** VARIABLES
 ******************************************************************************/
BMP280_registerCtrl_meas_t BMP_ctrl_measConf;
BMP280_registerConfig_t BMP_configReg;
 uint16_t BMP_dig_T1;
 int16_t BMP_dig_T2;
 int16_t BMP_dig_T3;  
 int32_t BMP_t_fine;
 int32_t BMP_rawTemp;


/******************************************************************************
 *** FUNCTION PROTOTYPES
 ******************************************************************************/

/** \brief  BMP280 operating mode initialize function
 * \param modeStatus Operating mode selection
 * \return Nothing
 */
static void BMP280_ModeInit(BMP280_modestatus_e modeStatus);

/** \brief  BMP280 pressure oversampling initialize function
 * \param pressOver Pressure oversampling selection
 * \return Pressure Oversampling status
 */
static int16_t BMP280_PressOverSamp(BMP280_press_oversampling_e pressOver);

/** \brief  BMP280 temperature oversampling initialize function
 * \param tempOver Temperature oversampling selection
 * \return Temperature Oversampling status
 */
static int16_t BMP280_TempOverSamp(BMP280_temp_oversampling_e tempOver);

/** \brief  BMP280 internal IIR filter initialize function
 * \param filterStatus Filter mode selection
 * \return 
 */
static int16_t BMP280_FilterInit(BMP280_filtermode_e filterStatus);

/** \brief  BMP280 controls inactive duration tstandby in normal mode
 * \param standbyStatus StandBy value selection
 * \return 
 */
static int16_t BMP280_StandByInit(BMP280_standbymode_e standbyStatus);

/** \brief  BMP280 sensor read the trimming parameters
 * \param[] Nothing
 * \return 
 */

void BMP280_ReadTrimmingTemperature(void);

/** \brief  BMP280 sensor read and compensation
 * \param adc_T Raw temperature data
 * \return T Final data
 */

int32_t BMP280_compensate_T_int32(int32_t adc_T);



/******************************************************************************
 *** LOCAL FUNCTIONS
 ******************************************************************************/

static int16_t BMP280_FilterInit(BMP280_filtermode_e filterStatus){
     
     uint8_t flag;

     flag = filterStatus;

     switch (flag)
     {
     case BMP280_FILTER_OFF:
          BMP_configReg.bit.filter_u3 = 0x00; 
          break;
     case BMP280_FILTER_X2:
          BMP_configReg.bit.filter_u3 = 0x01;
          break;
     case BMP280_FILTER_X4:
          BMP_configReg.bit.filter_u3 = 0x02;
          break;
     case BMP280_FILTER_X8:
          BMP_configReg.bit.filter_u3 = 0x03;
          break;
     case BMP280_FILTER_X16:
          BMP_configReg.bit.filter_u3 = 0x04;
          break;
     }

     return flag;
}

static int16_t BMP280_StandByInit(BMP280_standbymode_e standbyStatus){
     
     uint8_t flag;

     flag = standbyStatus;

     switch (flag)
     {
     case BMP280_STANDBY_5: 
          BMP_configReg.bit.t_sb_u3 = 0x00;
          break;
     case BMP280_STANDBY_625:
          BMP_configReg.bit.t_sb_u3 = 0x01;
          break;
     case BMP280_STANDBY_1250:
          BMP_configReg.bit.t_sb_u3 = 0x02;
          break;
     case BMP280_STANDBY_2500:
          BMP_configReg.bit.t_sb_u3 = 0x03;
          break;
     case BMP280_STANDBY_5000:
          BMP_configReg.bit.t_sb_u3 = 0x04;
          break;
     case BMP280_STANDBY_10000:
          BMP_configReg.bit.t_sb_u3 = 0x05;
          break;
     case BMP280_STANDBY_100:
          BMP_configReg.bit.t_sb_u3 = 0x06;
          break;
     case BMP280_STANDBY_200:
          BMP_configReg.bit.t_sb_u3 = 0x07;
          break;
     }
     return flag;
}

void BMP280_ReadTrimmingTemperature(void){

     uint8_t flaglsb_T1;
     uint8_t flagmsb_T1;
     uint8_t flaglsb_T2;
     uint8_t flagmsb_T2;
     uint8_t flaglsb_T3;
     uint8_t flagmsb_T3;

     bmp280_register_read(BMP280_CALIBRATION_TEMP1,&flaglsb_T1,sizeof(flaglsb_T1));

     bmp280_register_read(BMP280_CALIBRATION_TEMP2,&flagmsb_T1,sizeof(flagmsb_T1));

     BMP_dig_T1 = ((uint16_t)flagmsb_T1 << 8) | flaglsb_T1;

     bmp280_register_read(BMP280_CALIBRATION_TEMP3,&flaglsb_T2,sizeof(flaglsb_T2));

     bmp280_register_read(BMP280_CALIBRATION_TEMP4,&flagmsb_T2,sizeof(flagmsb_T2));

     BMP_dig_T2 = ((int16_t)flagmsb_T2 << 8) | flaglsb_T2;

     bmp280_register_read(BMP280_CALIBRATION_TEMP5,&flaglsb_T3,sizeof(flaglsb_T3));

     bmp280_register_read(BMP280_CALIBRATION_TEMP6,&flagmsb_T3,sizeof(flagmsb_T3));

     BMP_dig_T3 = ((int16_t)flagmsb_T3 << 8) | flaglsb_T3;
}

int32_t BMP280_compensate_T_int32(int32_t adc_T){

     int32_t var1, var2, T;
     var1 = ((((adc_T>>3) - ((int32_t)BMP_dig_T1<<1))) * ((int32_t)BMP_dig_T2)) >> 11;
     var2 = (((((adc_T>>4) - ((int32_t)BMP_dig_T1)) * ((adc_T>>4) - ((int32_t)BMP_dig_T1)))  >> 12) * ((int32_t)BMP_dig_T3)) >> 14;
     BMP_t_fine = var1 + var2;
     T = (BMP_t_fine * 5 + 128) >> 8;
     return T;
}

static void BMP280_ModeInit(BMP280_modestatus_e modeStatus){

    uint8_t flag;

     flag = modeStatus;

     switch (flag)
     {
     case BMP280_SLEEP_MODE:
          BMP_ctrl_measConf.bit.mode_u2 = 0x00;
          break;
     case BMP280_FORCED_MODE:
          BMP_ctrl_measConf.bit.mode_u2 = 0x01;
          break;
     case BMP280_NORMAL_MODE:
          BMP_ctrl_measConf.bit.mode_u2 = 0x03;
          break;
     }
}

static int16_t BMP280_PressOverSamp(BMP280_press_oversampling_e pressOver){
     uint8_t flag;

     flag = pressOver;

     switch (flag)
     {
     case BMP280_PRESS_OVERSAMPLING_X1:
          BMP_ctrl_measConf.bit.osrs_p_u3 = 0x01;
          break;
     case BMP280_PRESS_OVERSAMPLING_X2:
          BMP_ctrl_measConf.bit.osrs_p_u3 = 0x02;
          break;
     case BMP280_PRESS_OVERSAMPLING_X4:
          BMP_ctrl_measConf.bit.osrs_p_u3 = 0x03;
          break;
     case BMP280_PRESS_OVERSAMPLING_X8:
          BMP_ctrl_measConf.bit.osrs_p_u3 = 0x04;
          break;
     case BMP280_PRESS_OVERSAMPLING_X16:
          BMP_ctrl_measConf.bit.osrs_p_u3 = 0x05;
          break;
     }

     return flag;
}

static int16_t BMP280_TempOverSamp(BMP280_temp_oversampling_e tempOver){
      
      uint8_t flag;

      flag = tempOver;

     switch (flag)
     {
     case BMP280_TEMP_OVERSAMPLING_X1:
          BMP_ctrl_measConf.bit.osrs_t_u3 = 0x01;
          break;
     case BMP280_TEMP_OVERSAMPLING_X2:
          BMP_ctrl_measConf.bit.osrs_t_u3 = 0x02;
          break;
     case BMP280_TEMP_OVERSAMPLING_X4:
          BMP_ctrl_measConf.bit.osrs_t_u3 = 0x03;
          break;
     case BMP280_TEMP_OVERSAMPLING_X8:
          BMP_ctrl_measConf.bit.osrs_t_u3 = 0x04;
          break;
     case BMP280_TEMP_OVERSAMPLING_X16:
          BMP_ctrl_measConf.bit.osrs_t_u3 = 0x05;
          break;
     }

     return flag;
}     

/******************************************************************************
 *** GLOBAL FUNCTIONS
 ******************************************************************************/

void BMP280_ctrlmeasInit (void){
     
     BMP280_ModeInit(BMP280_NORMAL_MODE);
     BMP280_PressOverSamp(BMP280_PRESS_OVERSAMPLING_X16);
     BMP280_TempOverSamp(BMP280_TEMP_OVERSAMPLING_X2);

     bmp280_register_write(BMP280_CTRL_MEAS_ADDR,BMP_ctrl_measConf.u8);

}

void BMP280_configRegisterInit(void){

    BMP280_FilterInit(BMP280_FILTER_X16);
    BMP280_StandByInit(BMP280_STANDBY_5);

    bmp280_register_write(BMP280_CONFIG_ADDR,BMP_configReg.u8);

}

void BMP280_reset(BMP280_resetmode_e resetMode){
     
     if(resetMode == BMP280_RESET_ENABLE){
     BMP280_registerReset_t resetSelection;

     resetSelection.u8 = 0xB6;

     bmp280_register_write(BMP280_RESET_ADDR,resetSelection.u8);
     }
}


void BMP280_Init(void){
     
     BMP280_ctrlmeasInit();                           // 0xF4                             
   //  BMP280_HumadityOverSamp(HUM_OVERSAMPLING_X1);    //0xF2
     BMP280_configRegisterInit();                     //0xF5
                                               
}


int32_t BMP280_CalculateTemp(void){

     uint8_t flagxlsb;
     uint8_t flaglsb;
     uint8_t flagmsb;

     bmp280_register_read(BMP280_TEMP_XLSB_ADDR,&flagxlsb,sizeof(flagxlsb));

     bmp280_register_read(BMP280_TEMP_LSB_ADDR,&flaglsb,sizeof(flaglsb));

     bmp280_register_read(BMP280_TEMP_MSB_ADDR,&flagmsb,sizeof(flagmsb));

     BMP_rawTemp = (flagmsb << 12) | (flaglsb << 4) | (flagxlsb >> 4);
     
     BMP280_ReadTrimmingTemperature();
    

     return BMP280_compensate_T_int32(BMP_rawTemp);
}

uint16_t bmp280_median_filter(uint16_t bmpData)
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

 if (bmpData == STOPPER)
 {
   bmpData = STOPPER + 1;                            
 }

 if ( (++datpoint - buffer) >= MEDIAN_FILTER_SIZE)
 {
   datpoint = buffer;                               
 }

 datpoint->value = bmpData;                          
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

   if (scan->value < bmpData)                        
   {
     datpoint->point = scanold->point;            
     scanold->point = datpoint;                    
     bmpData = STOPPER;
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

   if (scan->value < bmpData)
   {
     datpoint->point = scanold->point;
     scanold->point = datpoint;
     bmpData = STOPPER;
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