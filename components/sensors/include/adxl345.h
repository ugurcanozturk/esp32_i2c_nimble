/**
 * \file adxl.h
 * \author Ugurcan OZTURK
 * \brief	ADXL345 Sensor Header File
 * \date 02.04.2024
 */


 /******************************************************************************
 *** INCLUDES
 ******************************************************************************/

#include "adxl345Config.h"

/******************************************************************************
*** VARIABLES
******************************************************************************/




/******************************************************************************
*** ENUMS
******************************************************************************/

   /** @enum ADXL_registeraddr_e
   *   @brief ADXL345 register address
   */
typedef enum {

	REGISTER_DEVID_ADDR          = 0x00,
	REGISTER_THRESH_TAP_ADDR     = 0x1D,
	REGISTER_OFSX_ADDR           = 0x1E,
	REGISTER_OFSY_ADDR           = 0x1F,
	REGISTER_OFSZ_ADDR           = 0x20,
	REGISTER_DUR_ADDR            = 0x21,
	REGISTER_LATENT_ADDR         = 0x22,
	REGISTER_WINDOW_ADDR         = 0x23,
	REGISTER_THRESH_ACT_ADDR     = 0x24,
	REGISTER_THRESH_INACT_ADDR   = 0x25,
	REGISTER_TIME_INACT_ADDR     = 0x26,
	REGISTER_ACT_INACT_CTL_ADDR  = 0x27,
	REGISTER_THRESH_FF_ADDR      = 0x28,
	REGISTER_TIME_FF_ADDR        = 0x29,
	REGISTER_TAP_AXES            = 0x2A,
	REGISTER_ACT_TAP_STATUS_ADDR = 0x2B,
	REGISTER_BW_RATE_ADDR        = 0x2C,
	REGISTER_POWER_CTL_ADDR      = 0x2D,
	REGISTER_INT_ENABLE_ADDR     = 0x2E,
	REGISTER_INT_MAP_ADDR        = 0x2F,
	REGISTER_INT_SOURCE_ADDR     = 0x30,
	REGISTER_DATA_FORMAT_ADDR    = 0x31,
	REGISTER_DATAX0_ADDR         = 0x32,
	REGISTER_DATAX1_ADDR         = 0x33,
	REGISTER_DATAY0_ADDR         = 0x34,
	REGISTER_DATAY1_ADDR         = 0x35,
	REGISTER_DATAZ0_ADDR         = 0x36,
	REGISTER_DATAZ1_ADDR         = 0x37,
	REGISTER_FIFO_CTL_ADDR       = 0x38,
	REGISTER_FIFO_STATUS_ADDR    = 0x39

}ADXL_registeraddr_e;

/******************************************************************************
 *** UNIONS
 ******************************************************************************/

 /** @union ADXL_threstap_t
 *   @brief ADXL345 THRES_TAP register bit field
 */
typedef union{

	struct
	{
	  uint8_t thresTap_u8 : 8;
	}bit;
	 uint8_t u8;
}ADXL_threstap_t;

/** @union ADXL_ofsx_t
*   @brief ADXL345 OFSX register bit field
*/
typedef union {

	struct
	{
		uint8_t ofsx_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_ofsx_t;

/** @union ADXL_ofsy_t
*   @brief ADXL345 OFSY register bit field
*/
typedef union {

	struct
	{
		uint8_t ofsy_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_ofsy_t;

/** @union ADXL_ofsz_t
*   @brief ADXL345 OFSZ register bit field
*/
typedef union {

	struct
	{
		uint8_t ofsz_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_ofsz_t;

/** @union ADXL_dur_t
*   @brief ADXL345 DUR register bit field
*/
typedef union {

	struct 
	{
		uint8_t dur_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_dur_t;

/** @union ADXL_latent_t
*   @brief ADXL345 Latent register bit field
*/
typedef union {

	struct
	{
		uint8_t latent_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_latent_t;

/** @union ADXL_window_t
*   @brief ADXL345 Window register bit field
*/
typedef union {

	struct
	{
		uint8_t window_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_window_t;

/** @union ADXL_threshact_t
*   @brief ADXL345 THRESH_ACT register bit field
*/
typedef union {

	struct
	{
		uint8_t threshact_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_threshact_t;

/** @union ADXL_thresinact_t
*   @brief ADXL345 THRESH_INACT register bit field
*/
typedef union {

	struct
	{
		uint8_t threshinact_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_thresinact_t;

/** @union ADXL_timeinact_t
*   @brief ADXL345 TIME_INACT register bit field
*/
typedef union {

	struct
	{
		uint8_t timeinact_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_timeinact_t;

/** @union ADXL_actinact_ctl_t
*   @brief ADXL345 ACT_INACT_CTL register bit field
*/
typedef union {

	struct 
	{
		uint8_t inactZ_Enable_u1 : 1;
		uint8_t inactY_Enable_u1 : 1;
		uint8_t inactX_Enable_u1 : 1;
		uint8_t inactAc_Dc_u1    : 1;
		uint8_t actZ_Enable_u1   : 1;
		uint8_t actY_Enable_u1   : 1;
		uint8_t actX_Enable_u1   : 1;
		uint8_t actAc_Dc_u1      : 1;
	}bit;
	    uint8_t u8;
}ADXL_actinact_ctl_t;

/** @union ADXL_thresh_ff_t
*   @brief ADXL345 THRESH_FF register bit field
*/
typedef union {

	struct
	{
		uint8_t threshff_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_thresh_ff_t;

/** @union ADXL_time_ff_t
*   @brief ADXL345 TIME_FF register bit field
*/
typedef union {

	struct
	{
		uint8_t timeff_u8 : 8;
	}bit;
	uint8_t u8;
}ADXL_time_ff_t;

/** @union ADXL_tapaxes_t
*   @brief ADXL345 TAP_AXES register bit field
*/
typedef union {

	struct 
	{
		uint8_t tap_z_u1    : 1;
		uint8_t tap_y_u1    : 1;
		uint8_t tap_x_u1    : 1;
		uint8_t suppress_u1 : 1;
		uint8_t reserved    : 4;
	}bit;
	uint8_t u8;
}ADXL_tapaxes_t;

/** @union ADXL_acttap_status_t
*   @brief ADXL345 ACT_TAP_STATUS register bit field
*/
typedef union {

	struct 
	{
		uint8_t tap_z_u1    : 1;
		uint8_t tap_y_u1    : 1;
		uint8_t tap_x_u1    : 1;
		uint8_t asleep_u1   : 1;
		uint8_t act_z_u1    : 1;
		uint8_t act_y_u1    : 1;
		uint8_t act_x_u1    : 1;
		uint8_t reserved    : 1;
	}bit;
	uint8_t u8;
}ADXL_acttap_status_t;

/** @union ADXL_bw_rate_t
*   @brief ADXL345 BW_RATE register bit field
*/
typedef union {

	struct 
	{
		uint8_t rate_u4      : 4;
		uint8_t low_power_u1 : 1;
		uint8_t reserved     : 3;
	}bit;
	uint8_t u8;
}ADXL_bw_rate_t;

/** @union ADXL_power_ctl_t
*   @brief ADXL345 POWER_CTL register bit field
*/
typedef union {

	struct 
	{
		uint8_t wakeup_u2     : 2;
		uint8_t sleep_u1      : 1;
		uint8_t measure_u1    : 1;
		uint8_t auto_sleep_u1 : 1;
		uint8_t link_u1       : 1;
		uint8_t reserved      : 2;

	}bit;
	uint8_t u8;
}ADXL_power_ctl_t;

/** @union ADXL_intenable_t
*   @brief ADXL345 INT_ENABLE register bit field
*/
typedef union {

	struct 
	{
		uint8_t overrun_u1    : 1;
		uint8_t watermark     : 1;
		uint8_t freeAll_u1    : 1;
		uint8_t inactivity_u1 : 1;
		uint8_t activity_u1   : 1;
		uint8_t doubleTap_u1  : 1;
		uint8_t singleTap_u1  : 1;
		uint8_t dataReady_u1  : 1;
	}bit;
	uint8_t u8;
}ADXL_intenable_t;

/** @union ADXL_intmap_t
*   @brief ADXL345 INT_MAP register bit field
*/
typedef union {

	struct
	{
		uint8_t overrun_u1 : 1;
		uint8_t watermark : 1;
		uint8_t freeAll_u1 : 1;
		uint8_t inactivity_u1 : 1;
		uint8_t activity_u1 : 1;
		uint8_t doubleTap_u1 : 1;
		uint8_t singleTap_u1 : 1;
		uint8_t dataReady_u1 : 1;
	}bit;
	uint8_t u8;
}ADXL_intmap_t;

/** @union ADXL_intsource_t
*   @brief ADXL345 INT_SOURCE register bit field
*/
typedef union {

	struct
	{
		uint8_t overrun_u1    : 1;
		uint8_t watermark     : 1;
		uint8_t freeAll_u1    : 1;
		uint8_t inactivity_u1 : 1;
		uint8_t activity_u1   : 1;
		uint8_t doubleTap_u1  : 1;
		uint8_t singleTap_u1  : 1;
		uint8_t dataReady_u1  : 1;
	}bit;
	uint8_t u8;
}ADXL_intsource_t;

/** @union ADXL_dataformat_t
*   @brief ADXL345 DATA_FORMAT register bit field
*/
typedef union {

	struct 
	{
		uint8_t range_u2     : 2;
		uint8_t justify_u1   : 1;
		uint8_t fullres_u1   : 1;
		uint8_t reserved_u1  : 1;
		uint8_t intInvert_u1 : 1;
		uint8_t spi_u1       : 1;
		uint8_t selfTest     : 1;
	}bit;
	uint8_t u8;
}ADXL_dataformat_t;

/** @union ADXL_fifoctl_t
*   @brief ADXL345 FIFO_CTL register bit field
*/
typedef union {

	struct 
	{
		uint8_t samples_u5  : 5;
		uint8_t trigger_u1  : 1;
		uint8_t fifoMode_u2 : 2;
	}bit;
	uint8_t u8;
}ADXL_fifoctl_t;

/** @union ADXL_fifoctl_t
*   @brief ADXL345 FIFO_STATUS register bit field
*/
typedef union {

	struct 
	{
		uint8_t entries_u5  : 5;
		uint8_t reserved_u1 : 1;
		uint8_t fifoTrig_u1 : 1;
	}bit;
}ADXL_fifostatus_t;

/******************************************************************************
 *** FUNCTION PROTOTYPES
 ******************************************************************************/


 /** \brief  ADXL345 general initialize function
  * \param[]
  * \return Nothing
  */
void ADXL345_Init(void);

/** \brief  ADXL345 calculate x,y,z axis data
 * \param[]
 * \return Nothing
 */
void ADXL345_CalculateData(void);

/** \brief  ADXL345 read register function
 * \param reg_addr Register address
 * \param data Reading data buffer
 * \param len Reading data size
 * \return 0
 */
int16_t adxl_register_read(ADXL_registeraddr_e reg_addr, uint8_t *data, size_t len);

/** \brief  ADXL345 write register function
 * \param reg_addr Register address
 * \param data Reading data buffer
 * \return 0
 */
int16_t adxl_register_write(ADXL_registeraddr_e reg_addr, uint8_t data);

/** \brief  ADXL345 X axis non calibration data calculating
 * \param[] Nothing
 * \return Non calibration X axis data
 */
int16_t ADXL345_XaxisCalculate(void);

/** \brief  ADXL345 Y axis non calibration data calculating
 * \param[] Nothing
 * \return Non calibration Y axis data
 */
int16_t ADXL345_YaxisCalculate(void);

/** \brief  ADXL345 Z axis non calibration data calculating
 * \param[] Nothing
 * \return Non calibration Z axis data
 */
int16_t ADXL345_ZaxisCalculate(void);

/** \brief  ADXL345 sensor data filtering
 * \param adxlData Raw temperature data
 * \return Filtering data 
 */
uint16_t adxl_median_filter(uint16_t adxlData);