/**
 * \file adxl.c
 * \author Ugurcan OZTURK
 * \brief	ADXL345 Sensor Header File
 * \date 02.04.2024
 */


 /******************************************************************************
 *** INCLUDES
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "adxl345.h"


/******************************************************************************
 *** DEFINES
 ******************************************************************************/
#define    STOPPER                0                                      
#define    MEDIAN_FILTER_SIZE     5

 /******************************************************************************
 *** VARIABLES
 ******************************************************************************/




/******************************************************************************
*** FUNCTION PROTOTYPES
******************************************************************************/

/** \brief  ADXL345 operating mode initialize function
 * \param modeSelection User mode selection type enumaration
 * \return ADXL345 mode
 */
static int8_t ADXL345_ModeInit(ADXL_mode_e modeSelection);

/** \brief  ADXL345 Range initialize function
 * \param rangeSelection User range selection type enumaration
 * \return Nothing
 */
static int8_t ADXL345_RangeInit(ADXL_range_e rangeSelection);

/** \brief  ADXL345 FIFO mode initialize function
 * \param fifoSelection User fifo mode selection type enumaration
 * \return Nothing
 */
static int8_t ADXL345_FIFOInit(ADXL_fifomode_e fifoSelection);

/** \brief  ADXL345 Bandwidth and data rate speed initialize function
 * \param fifoSelection User fifo mode selection type enumaration
 * \return Nothing
 */
static int8_t ADXL345_BWInit(ADXL_powerdataratebw_e modeSelection);



/******************************************************************************
*** LOCAL FUNCTIONS
******************************************************************************/

static int8_t ADXL345_ModeInit(ADXL_mode_e modeSelection) {

	ADXL_power_ctl_t modeConfig;
	uint8_t flag;

	flag = modeSelection;

	switch (flag)
	{
	case ADXL_WAKEUP:
		modeConfig.bit.wakeup_u2     = 0x03;  // 1Hz readings in sleep mode
		break;
	case ADXL_SLEEP:
		modeConfig.bit.sleep_u1      = 0x01;
		break;
	case ADXL_MEASURE:
		modeConfig.bit.measure_u1    = 0x01;
		break;
	case ADXL_AUTOSLEEP:
		modeConfig.bit.auto_sleep_u1 = 0x01;
	}

	
    adxl_register_write(REGISTER_POWER_CTL_ADDR,modeConfig.u8);

	return flag;
}

static int8_t ADXL345_RangeInit(ADXL_range_e rangeSelection) {

	ADXL_dataformat_t rangeConf;
	uint8_t flag;

	flag = rangeSelection;

	switch (flag)
	{
	case RANGE_2G:
		rangeConf.bit.range_u2 = 0x00;
		break;
	case RANGE_4G:
		rangeConf.bit.range_u2 = 0x01;
		break;
	case RANGE_8G:
		rangeConf.bit.range_u2 = 0x02;
		break;
	case RANGE_16G:
		rangeConf.bit.range_u2 = 0x03;
		break;
	}
	
     adxl_register_write(REGISTER_DATA_FORMAT_ADDR,rangeConf.u8);
	return flag;
}

static int8_t ADXL345_FIFOInit(ADXL_fifomode_e fifoSelection) {

	ADXL_fifoctl_t fifoConf;
	uint8_t flag;

	flag = fifoSelection;

	switch (flag)
	{
	case FIFO_BYPASS:
		fifoConf.bit.fifoMode_u2 = 0x00;
		break;
	case FIFO_ENABLE:
		fifoConf.bit.fifoMode_u2 = 0x01;
		break;
	case FIFO_STREAM:
		fifoConf.bit.fifoMode_u2 = 0x02;
		break;
	case FIFO_TRIGGER:
		fifoConf.bit.fifoMode_u2 = 0x03;
		break;
	}
	adxl_register_write(REGISTER_FIFO_CTL_ADDR, fifoConf.u8);
	return flag;
}

static int8_t ADXL345_BWInit(ADXL_powerdataratebw_e modeSelection) {

	ADXL_bw_rate_t bwConfig;
	uint8_t flag;

	flag = modeSelection;

	switch (flag)
	{
	case DATARATE50_BANDWIDTH25:
		bwConfig.bit.rate_u4 = 0x09;
		break;
	case DATARATE100_BANDWIDTH50:
		bwConfig.bit.rate_u4 = 0x0A;
		break;
	case DATARATE200_BANDWIDTH100:
		bwConfig.bit.rate_u4 = 0x0B;
		break;
	case DATARATE400_BANDWIDTH200:
		bwConfig.bit.rate_u4 = 0x0C;
		break;
	case DATARATE800_BANDWIDTH400:
		bwConfig.bit.rate_u4 = 0x0D;
		break;
	}
	adxl_register_write(REGISTER_BW_RATE_ADDR,bwConfig.u8);
	return flag;
}




/******************************************************************************
*** GLOBAL FUNCTIONS
******************************************************************************/

void ADXL345_Init(void) {

	ADXL345_ModeInit(ADXL_MEASURE);
	ADXL345_RangeInit(RANGE_4G);
	ADXL345_FIFOInit(FIFO_STREAM); // always new data
	ADXL345_BWInit(DATARATE400_BANDWIDTH200);
}

int16_t ADXL345_XaxisCalculate(void){
     uint16_t xaxis;
     uint8_t xraw_0;
     uint8_t xraw_1;
     

     adxl_register_read(REGISTER_DATAX0_ADDR, &xraw_0,sizeof(xraw_0));
     adxl_register_read(REGISTER_DATAX1_ADDR, &xraw_1,sizeof(xraw_1));

     xaxis = (xraw_1 << 8) | xraw_0;

     return xaxis;
}

int16_t ADXL345_YaxisCalculate(void){
     uint16_t yaxis;
     uint8_t yraw_0;
     uint8_t yraw_1;

     adxl_register_read(REGISTER_DATAY0_ADDR,&yraw_0,sizeof(yraw_0));
     adxl_register_read(REGISTER_DATAY1_ADDR,&yraw_1,sizeof(yraw_1));

     yaxis = (yraw_1 << 8) | yraw_0;

     return yaxis;
}

int16_t ADXL345_ZaxisCalculate(void){
     int16_t zaxis;
     uint8_t zraw_0;
     uint8_t zraw_1;

     adxl_register_read(REGISTER_DATAZ0_ADDR,&zraw_0,sizeof(zraw_0));
     adxl_register_read(REGISTER_DATAZ1_ADDR,&zraw_1,sizeof(zraw_1));

     zaxis = (zraw_1 << 8) | zraw_0;

     return zaxis;
}

uint16_t adxl_median_filter(uint16_t adxlData){
	struct pair
 {
   struct pair *point;                              /* Bağlı liste içinde sıralı düzen oluşturan pointerlar */
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

 if (adxlData == STOPPER)
 {
   adxlData = STOPPER + 1;                             
 }

 if ( (++datpoint - buffer) >= MEDIAN_FILTER_SIZE)
 {
   datpoint = buffer;                               
 }

 datpoint->value = adxlData;                          
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

   if (scan->value < adxlData)                        
   {
     datpoint->point = scanold->point;             
     scanold->point = datpoint;                    
     adxlData = STOPPER;
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

   if (scan->value < adxlData)
   {
     datpoint->point = scanold->point;
     scanold->point = datpoint;
     adxlData = STOPPER;
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