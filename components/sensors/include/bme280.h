/**
 * \file bme280.h
 * \author Ugurcan OZTURK
 * \brief	BME280 Sensor Header File
 * \date 26.03.2024
 */

 /******************************************************************************
 *** INCLUDES
 ******************************************************************************/
#include "bme280Config.h"


/******************************************************************************
 *** VARIABLES
 ******************************************************************************/



 
/******************************************************************************
 *** ENUMS
 ******************************************************************************/

/** @enum BME280_registerAddr_e
*   @brief BME280 register address
*/
typedef enum{
    REGISTER_ID_ADDR         = 0xD0,
    REGISTER_RESET_ADDR      = 0xE0,
    REGISTER_CTRL_HUM_ADDR   = 0xF2,
    REGISTER_STATUS_ADDR     = 0xF3,
    REGISTER_CTRL_MEAS_ADDR  = 0xF4,
    REGISTER_CONFIG_ADDR     = 0xF5,
    REGISTER_PRESS_MSB_ADDR  = 0xF7,
    REGISTER_PRESS_LSB_ADDR  = 0xF8,
    REGISTER_PRESS_XLSB_ADDR = 0xF9,
    REGISTER_TEMP_MSB_ADDR   = 0xFA,
    REGISTER_TEMP_LSB_ADDR   = 0xFB,
    REGISTER_TEMP_XLSB_ADDR  = 0xFC,
    REGISTER_HUM_MSB_ADDR    = 0xFD,
    REGISTER_HUM_LSB_ADDR    = 0xFE
}BME280_registerAddr_e;

typedef enum{
    REGISTER_CALIBRATION_TEMP1 = 0x88,
    REGISTER_CALIBRATION_TEMP2,
    REGISTER_CALIBRATION_TEMP3,
    REGISTER_CALIBRATION_TEMP4,
    REGISTER_CALIBRATION_TEMP5,
    REGISTER_CALIBRATION_TEMP6

}BME280_calibrationaddr_e;



/******************************************************************************
 *** UNIONS
 ******************************************************************************/

/** @union BME280_registerId_t
*   @brief BME280 register id bit field
*/
typedef union {
    
    struct 
    {
        uint8_t regId_u8 : 8;
    }bit;

    uint8_t u8;
}BME280_registerId_t;

/** @union BME280_registerReset_t
*   @brief BME280 Reset register bit field
*/
typedef union{

    struct 
    {
        uint8_t regReset_u8 : 8;
    }bit;
    
    uint8_t u8;
}BME280_registerReset_t;

/** @union BME280_registerctrlhum_t
*   @brief BME280 ctrl_hum register bit field
*/
typedef union{

    struct 
    {
        uint8_t osrs_h_u3   : 3;
        uint8_t reserved_u5 : 5;
    }bit;

    uint8_t u8;
}BME280_registerctrlhum_t;

/** @union BME280_registerStatus_t
*   @brief BME280 Status register bit field
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
}BME280_registerStatus_t;

/** @union BME280_registerCtrl_meas_t
*   @brief BME280 ctrl_meas register bit field
*/
typedef union{

    struct 
    {
        uint8_t mode_u2   : 2;
        uint8_t osrs_p_u3 : 3;
        uint8_t osrs_t_u3 : 3;
    }bit;
    
    uint8_t u8;
}BME280_registerCtrl_meas_t;

/** @union BME280_registerConfig_t
*   @brief BME280 config register bit field
*/
typedef union{

    struct 
    {
        uint8_t spi3w_en_u1: 1;
        uint8_t filter_u3  : 3;
        uint8_t t_sb_u3    : 3;
    }bit;
    
    uint8_t u8;
}BME280_registerConfig_t;

/** @union BME280_registerPress_msb_t
*   @brief BME280 press_msb register bit field
*/
typedef union {

    struct 
    {
        uint8_t press_msb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BME280_registerPress_msb_t;

/** @union BME280_registerPress_lsb_t
*   @brief BME280 press_lsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t press_lsb_u8 : 8;
    }bit;

    uint8_t u8;
}BME280_registerPress_lsb_t;

/** @union BME280_registerpress_xlsb_t
*   @brief BME280 press_xlsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t reserved_u4   : 4;
        uint8_t press_xlsb_u4 : 4;
    }bit;
    
    uint8_t u8;
}BME280_registerpress_xlsb_t;

/** @union BME280_registertemp_msb_t
*   @brief BME280 temp_msb register bit field
*/
typedef union{

    struct 
    {
        uint8_t temp_msb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BME280_registertemp_msb_t;

/** @union BME280_registertemp_lsb_t
*   @brief BME280 temp_lsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t temp_lsb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BME280_registertemp_lsb_t;

/** @union BME280_registertemp_xlsb_t
*   @brief BME280 temp_xlsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t reserved_u4  : 4;
        uint8_t temp_xlsb_u4 : 4;
    }bit;
    
    uint8_t u8;
}BME280_registertemp_xlsb_t;

/** @union BME280_registerhum_msb_t
*   @brief BME280 hum_msb register bit field
*/
typedef union{

    struct 
    {
        uint8_t hum_msb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BME280_registerhum_msb_t;

/** @union BME280_registerhum_lsb_t
*   @brief BME280 hum_lsb register bit field
*/
typedef union{

    struct 
    {
        uint8_t hum_lsb_u8 : 8;
    }bit;
    
    uint8_t u8;
}BME280_registerhum_lsb_t;


/******************************************************************************
 *** FUNCTION PROTOTYPES
 ******************************************************************************/

/** \brief  BME280 sensor initialize function
 * \param[] Nothing
 * \return  Nothing
 */
void BME280_Init(void);

/** \brief  BME280 sensor reset disable or enable function
 * \param resetMode Enable or Disable
 * \return  Nothing
 */

/** \brief  BME280 sensor ctrl_meas register initalize global function
 * \param[] Nothing
 * \return  Nothing
 */
void BME280_ctrlmeasInit (void);

/** \brief  BME280 sensor config register initalize global function
 * \param[] Nothing
 * \return  Nothing
 */
void BME280_configRegisterInit(void);

/** \brief  BME280 sensor software reset function
 * \param resetMode Enable or Disable
 * \return  Nothing
 */
void BME280_reset(BME280_resetmode_e resetMode);

/** \brief  BME280 sensor read to register function
 * \param reg_addr register address
 * \param data receive data buffer
 * \param len data size
 * \return  
 */
int16_t bme280_register_read(BME280_registerAddr_e reg_addr, uint8_t *data, size_t len);

/** \brief  BME280 sensor write to register function
 * \param reg_addr register address
 * \param data transmit data buffer
 * \return  
 */
int16_t bme280_register_write(BME280_registerAddr_e reg_addr, uint8_t data);

/** \brief  BME280 sensor calculate temperature data
 * \param[]
 * \return  
 */
int32_t BME280_CalculateTemp(void);

/** \brief  BME280 sensor calculate humadity data
 * \param rawHum Raw temperature data
 * \return  
 */
int32_t BME280_CalculateHum(int32_t rawHum);

/** \brief  BME280 sensor calculate press data
 * \param rawPress Raw temperature data
 * \return  
 */
int32_t BME280_CalculatePress(int32_t rawPress);

/** \brief  BME280 sensor data filtering
 * \param bmeData Raw temperature data
 * \return Filtering data 
 */
uint16_t bme280_median_filter(uint16_t bmeData);