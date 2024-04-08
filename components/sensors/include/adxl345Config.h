/**
 * \file adxlConfig.h
 * \author Ugurcan OZTURK
 * \brief	ADXL345 User Configuration Header File
 * \date 03.04.2024
 */


 /******************************************************************************
   *** ENUMS
   ******************************************************************************/

/** @enum ADXL_mode_e
*   @brief ADXL345 operating mode user selection
*/
typedef enum {
	ADXL_WAKEUP,
	ADXL_SLEEP,
	ADXL_MEASURE,
	ADXL_AUTOSLEEP
}ADXL_mode_e;

 /** @enum ADXL_powerdataratebw_e
 *   @brief ADXL345 Power mode Data Rate and Bandwidth frequency
 */
typedef enum {
	DATARATE0_10_BANDWIDTH0_05,   /* Data Rate : 0.10Hz Bandwidth : 0.05Hz */
	DATARATE0_20_BANDWIDTH0_10,   /* Data Rate : 0.20Hz Bandwidth : 0.10Hz */
	DATARATE0_39_BANDWIDTH0_20,   /* Data Rate : 0.39Hz Bandwidth : 0.20Hz */
	DATARATE0_78_BANDWIDTH0_39,   /* Data Rate : 0.78Hz Bandwidth : 0.39Hz */
	DATARATE1_56_BANDWIDTH0_78,   /* Data Rate : 1.56Hz Bandwidth : 0.78Hz */
	DATARATE3_13_BANDWIDTH1_56,   /* Data Rate : 3.13Hz Bandwidth : 1.56Hz */
	DATARATE6_25_BANDWIDTH3_13,   /* Data Rate : 6.25Hz Bandwidth : 3.13Hz */
	DATARATE12_5_BANDWIDTH6_25,   /* Data Rate : 12.5Hz Bandwidth : 6.25Hz */
	DATARATE25_BANDWIDTH12_5  ,   /* Data Rate : 25.0Hz Bandwidth : 12.5Hz */
	DATARATE50_BANDWIDTH25    ,   /* Data Rate : 50.0Hz Bandwidth : 25.0Hz */
	DATARATE100_BANDWIDTH50   ,   /* Data Rate : 100 Hz Bandwidth : 50.0Hz */
	DATARATE200_BANDWIDTH100  ,   /* Data Rate : 200 Hz Bandwidth : 100 Hz */
	DATARATE400_BANDWIDTH200  ,   /* Data Rate : 400 Hz Bandwidth : 200 Hz */
	DATARATE800_BANDWIDTH400  ,   /* Data Rate : 800 Hz Bandwidth : 400 Hz */
	DATARATE1600_BANDWIDTH800 ,   /* Data Rate : 1600Hz Bandwidth : 800 Hz */
	DATARATE3200_BANDWIDTH1600,   /* Data Rate : 3200Hz Bandwidth : 1600Hz */
}ADXL_powerdataratebw_e;

/** @enum ADXL_lowdataratebw_e
*   @brief ADXL345 Low power mode Data Rate and Bandwidth frequency
*/
typedef enum {
	DATARATE12_5_BANDWIDTH6_25_L,   /* Data Rate : 12.5Hz Bandwidth : 6.25Hz */
	DATARATE25_BANDWIDTH12_5_L  ,   /* Data Rate : 25.0Hz Bandwidth : 12.5Hz */
	DATARATE50_BANDWIDTH25_L    ,   /* Data Rate : 50.0Hz Bandwidth : 25.0Hz */
	DATARATE100_BANDWIDTH50_L   ,   /* Data Rate : 100 Hz Bandwidth : 50.0Hz */
	DATARATE200_BANDWIDTH100_L  ,   /* Data Rate : 200 Hz Bandwidth : 100 Hz */
	DATARATE400_BANDWIDTH200_L  ,   /* Data Rate : 400 Hz Bandwidth : 200 Hz */

}ADXL_lowdataratebw_e;

/** @enum ADXL_range_e
*   @brief ADXL345 Range "g" user selection
*/
typedef enum {
	RANGE_2G,
	RANGE_4G,
	RANGE_8G,
	RANGE_16G
}ADXL_range_e;

/** @enum ADXL_range_e
*   @brief ADXL345 Range "g" user selection
*/
typedef enum {
	FIFO_BYPASS,
	FIFO_ENABLE,
	FIFO_STREAM,
	FIFO_TRIGGER
}ADXL_fifomode_e;