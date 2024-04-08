/**
 * \file bmp280.h
 * \author Ugurcan OZTURK
 * \brief	BMP280 Sensor Header File
 * \date 04.04.2024
 */

 /******************************************************************************
 *** INCLUDES
 ******************************************************************************/
#include "bmp280Config.h"


/******************************************************************************
 *** VARIABLES
 ******************************************************************************/



 
/******************************************************************************
 *** ENUMS
 ******************************************************************************/



/** @enum BMP280_registerAddr_e
*   @brief BMP280 register address
*/
typedef enum{
    BMP280_ID_ADDR         = 0xD0,
    BMP280_RESET_ADDR      = 0xE0,
    BMP280_CTRL_HUM_ADDR   = 0xF2,
    BMP280_STATUS_ADDR     = 0xF3,
    BMP280_CTRL_MEAS_ADDR  = 0xF4,
    BMP280_CONFIG_ADDR     = 0xF5,
    BMP280_PRESS_MSB_ADDR  = 0xF7,
    BMP280_PRESS_LSB_ADDR  = 0xF8,
    BMP280_PRESS_XLSB_ADDR = 0xF9,
    BMP280_TEMP_MSB_ADDR   = 0xFA,
    BMP280_TEMP_LSB_ADDR   = 0xFB,
    BMP280_TEMP_XLSB_ADDR  = 0xFC,
    BMP280_HUM_MSB_ADDR    = 0xFD,
    BMP280_HUM_LSB_ADDR    = 0xFE
}BMP280_registerAddr_e;

typedef enum{
    BMP280_CALIBRATION_TEMP1 = 0x88,
    BMP280_CALIBRATION_TEMP2,
    BMP280_CALIBRATION_TEMP3,
    BMP280_CALIBRATION_TEMP4,
    BMP280_CALIBRATION_TEMP5,
    BMP280_CALIBRATION_TEMP6

}BMP280_calibrationaddr_e;

/******************************************************************************
 *** UNIONS
 ******************************************************************************/

/** @union BMP280_registerId_t
*   @brief BMP280 register id bit field
*/
typedef union {
    
    struct 
    {
        uint8_t regId_u8 : 8;
    }bit;

    uint8_t u8;
}BMP280_registerId_t;

/** @union BMP280_registerReset_t
*   @brief BMP280 Reset register bit field
*/
typedef union{

    struct 
    {
        uint8_t regReset_u8 : 8;
    }bit;
    
    uint8_t u8;
}BMP280_registerReset_t;

/** @union BMP280_registerctrlhum_t
*   @brief BMP280 ctrl_hum register bit field
*/
typedef union{

    struct 
    {
        uint8_t osrs_h_u3   : 3;
        uint8_t reserved_u5 : 5;
    }bit;

    uint8_t u8;
}BMP280_registerctrlhum_t;

/** @union BMP280_registerStatus_t
*   @brief BMP280 Status register bit field
*/
typedef union {

    struct 
    {
        uint8_t im_update_u1 : 1;
        uint8_t reserved_u2  : 2;
        uint8_t measuring_u1 : 1;
        uint8_t reserved_u4  : 4;

    }bit;
    
    uint8_t u8;
}BMP280_registerStatus_t;

/** @union BMP280_registerCtrl_meas_t
*   @brief BMP280 ctrl_meas register bit field
*/
typedef union{

    struct 
    {
        uint8_t mode_u2   : 2;
        uint8_t osrs_p_u3 : 3;
        uint8_t osrs_t_u3 : 3;
    }bit;
    
    uint8_t u8;
}BMP280_registerCtrl_meas_t;

/** @union BMP280_registerConfig_t
*   @brief BMP280 config register bit field
*/
typedef union{

    struct 
    {
        uint8_t spi3w_en_u1: 1;
        uint8_t filter_u3  : 3;
        uint8_t t_sb_u3    : 3;
    }bit;
    
    uint8_t u8;
}BMP280_registerConfig_t;

/** @union BMP280_registerPress_msb_t
*   @brief BMP280 press_msb register bit field
*/
typedef union {

    struct 
    {
        uint8_t press_msb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BMP280_registerPress_msb_t;

/** @union BMP280_registerPress_lsb_t
*   @brief BMP280 press_lsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t press_lsb_u8 : 8;
    }bit;

    uint8_t u8;
}BMP280_registerPress_lsb_t;

/** @union BMP280_registerpress_xlsb_t
*   @brief BMP280 press_xlsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t reserved_u4   : 4;
        uint8_t press_xlsb_u4 : 4;
    }bit;
    
    uint8_t u8;
}BMP280_registerpress_xlsb_t;

/** @union BMP280_registertemp_msb_t
*   @brief BMP280 temp_msb register bit field
*/
typedef union{

    struct 
    {
        uint8_t temp_msb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BMP280_registertemp_msb_t;

/** @union BMP280_registertemp_lsb_t
*   @brief BMP280 temp_lsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t temp_lsb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BMP280_registertemp_lsb_t;

/** @union BMP280_registertemp_xlsb_t
*   @brief BMP280 temp_xlsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t reserved_u4  : 4;
        uint8_t temp_xlsb_u4 : 4;
    }bit;
    
    uint8_t u8;
}BMP280_registertemp_xlsb_t;

/** @union BMP280_registerhum_msb_t
*   @brief BMP280 hum_msb register bit field
*/
typedef union{

    struct 
    {
        uint8_t hum_msb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BMP280_registerhum_msb_t;

/** @union BMP280_registerhum_lsb_t
*   @brief BMP280 hum_lsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t hum_lsb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BMP280_registerhum_lsb_t;

/******************************************************************************
 *** FUNCTION PROTOTYPES
 ******************************************************************************/

/** \brief  BMP280 sensor initialize function
 * \param[] Nothing
 * \return  Nothing
 */
void BMP280_Init(void);

/** \brief  BMP280 sensor reset disable or enable function
 * \param resetMode Enable or Disable
 * \return  Nothing
 */

/** \brief  BMP280 sensor ctrl_meas register initalize global function
 * \param[] Nothing
 * \return  Nothing
 */
void BME280_ctrlmeasInit (void);

/** \brief  BMP280 sensor config register initalize global function
 * \param[] Nothing
 * \return  Nothing
 */
void BMP280_configRegisterInit(void);

/** \brief  BMP280 sensor software reset function
 * \param resetMode Enable or Disable
 * \return  Nothing
 */
void BMP280_reset(BMP280_resetmode_e resetMode);

/** \brief  BMP280 sensor read to register function
 * \param reg_addr register address
 * \param data receive data buffer
 * \param len data size
 * \return  
 */
int16_t bmp280_register_read(BMP280_registerAddr_e reg_addr, uint8_t *data, size_t len);

/** \brief  BME280 sensor write to register function
 * \param reg_addr register address
 * \param data transmit data buffer
 * \return  
 */
int16_t bmp280_register_write(BMP280_registerAddr_e reg_addr, uint8_t data);

/** \brief  BME280 sensor calculate temperature data
 * \param[]
 * \return  
 */
int32_t BMP280_CalculateTemp(void);

/** \brief  BMP280 sensor calculate press data
 * \param rawPress Raw temperature data
 * \return  
 */
int32_t BMP280_CalculatePress(int32_t rawPress);

/** \brief  BMP280 sensor data filtering
 * \param bmPData Raw temperature data
 * \return Filtering data 
 */
uint16_t bmp280_median_filter(uint16_t bmpData);
