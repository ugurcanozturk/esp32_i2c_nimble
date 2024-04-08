/**
 * \file bmp280Config.h
 * \author Ugurcan OZTURK
 * \brief	BMP280 Sensor User Configuration Header File
 * \date 04.04.2024
 */


/******************************************************************************
 *** ENUMS
 ******************************************************************************/

/** @enum BMP280_configstatus_e
*   @brief BMP280 user configuration status
*/
typedef enum{
    BMP280_CONFIG_ERROR,
    BMP280_CONFIG_OK
}BMP280_configstatus_e;


/** @enum BMP280_resetmode_e
*   @brief BMP280 reset mode enable or disable
*/
typedef enum{
    BMP280_RESET_DISABLE,
    BMP280_RESET_ENABLE
}BMP280_resetmode_e;

/** @enum BMP280_modestatus_e
*   @brief BMP280 operating mode
*/
typedef enum{
    BMP280_SLEEP_MODE,
    BMP280_FORCED_MODE,
    BMP280_NORMAL_MODE
}BMP280_modestatus_e;

/** @enum BMP280_hum_oversampling_e
*   @brief BMP280 humadity oversampling user selection
*/
typedef enum{
    BMP280_HUM_OVERSAMPLING_NO,
    BMP280_HUM_OVERSAMPLING_X1,
    BMP280_HUM_OVERSAMPLING_X2,
    BMP280_HUM_OVERSAMPLING_X4,
    BMP280_HUM_OVERSAMPLING_X8,
    BMP280_HUM_OVERSAMPLING_X16
}BMP280_hum_oversampling_e;

/** @enum BMP280_press_oversampling_e
*   @brief BMP280 pressure oversampling user selection
*/
typedef enum{
    BMP280_PRESS_OVERSAMPLING_NO,
    BMP280_PRESS_OVERSAMPLING_X1,
    BMP280_PRESS_OVERSAMPLING_X2,
    BMP280_PRESS_OVERSAMPLING_X4,
    BMP280_PRESS_OVERSAMPLING_X8,
    BMP280_PRESS_OVERSAMPLING_X16
}BMP280_press_oversampling_e;

/** @enum BMP280_temp_oversampling_e
*   @brief BMP280 temperature oversampling user selection
*/
typedef enum{
    BMP280_TEMP_OVERSAMPLING_NO,
    BMP280_TEMP_OVERSAMPLING_X1,
    BMP280_TEMP_OVERSAMPLING_X2,
    BMP280_TEMP_OVERSAMPLING_X4,
    BMP280_TEMP_OVERSAMPLING_X8,
    BMP280_TEMP_OVERSAMPLING_X16
}BMP280_temp_oversampling_e;

/** @enum BMP280_filtermode_e
*   @brief BMP280 temperature oversampling user selection
*/
typedef enum{
    BMP280_FILTER_OFF,
    BMP280_FILTER_X2,
    BMP280_FILTER_X4,
    BMP280_FILTER_X8,
    BMP280_FILTER_X16
}BMP280_filtermode_e;

/** @enum BMP280_filtermode_e
*   @brief BMP280 temperature oversampling user selection
*   @note The actual value is found by dividing by 10 (ms)
*/
typedef enum{
    BMP280_STANDBY_5    ,  // 0.5ms
    BMP280_STANDBY_625  ,  // 62.5ms
    BMP280_STANDBY_1250 ,  // 125ms
    BMP280_STANDBY_2500 ,  // 250ms
    BMP280_STANDBY_5000 ,  // 500ms
    BMP280_STANDBY_10000,  // 1000ms
    BMP280_STANDBY_100  ,  // 10ms
    BMP280_STANDBY_200     // 20ms
}BMP280_standbymode_e;