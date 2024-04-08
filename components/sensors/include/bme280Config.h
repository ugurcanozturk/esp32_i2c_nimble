/**
 * \file bme280Config.h
 * \author Ugurcan OZTURK
 * \brief	BME280 Sensor User Configuration Header File
 * \date 30.03.2024
 */


/******************************************************************************
 *** ENUMS
 ******************************************************************************/

/** @enum BME280_configstatus_e
*   @brief BME280 user configuration status
*/
typedef enum{
    BME280_CONFIG_ERROR,
    BME280_CONFIG_OK
}BME280_configstatus_e;


/** @enum BME280_resetmode_e
*   @brief BME280 reset mode enable or disable
*/
typedef enum{
    BME280_RESET_DISABLE,
    BME280_RESET_ENABLE
}BME280_resetmode_e;

/** @enum BME280_modestatus_e
*   @brief BME280 operating mode
*/
typedef enum{
    BME280_SLEEP_MODE,
    BME280_FORCED_MODE,
    BME280_NORMAL_MODE
}BME280_modestatus_e;

/** @enum BME280_hum_oversampling_e
*   @brief BME280 humadity oversampling user selection
*/
typedef enum{
    HUM_OVERSAMPLING_NO,
    HUM_OVERSAMPLING_X1,
    HUM_OVERSAMPLING_X2,
    HUM_OVERSAMPLING_X4,
    HUM_OVERSAMPLING_X8,
    HUM_OVERSAMPLING_X16
}BME280_hum_oversampling_e;

/** @enum BME280_press_oversampling_e
*   @brief BME280 pressure oversampling user selection
*/
typedef enum{
    PRESS_OVERSAMPLING_NO,
    PRESS_OVERSAMPLING_X1,
    PRESS_OVERSAMPLING_X2,
    PRESS_OVERSAMPLING_X4,
    PRESS_OVERSAMPLING_X8,
    PRESS_OVERSAMPLING_X16
}BME280_press_oversampling_e;

/** @enum BME280_temp_oversampling_e
*   @brief BME280 temperature oversampling user selection
*/
typedef enum{
    TEMP_OVERSAMPLING_NO,
    TEMP_OVERSAMPLING_X1,
    TEMP_OVERSAMPLING_X2,
    TEMP_OVERSAMPLING_X4,
    TEMP_OVERSAMPLING_X8,
    TEMP_OVERSAMPLING_X16
}BME280_temp_oversampling_e;

/** @enum BME280_filtermode_e
*   @brief BME280 temperature oversampling user selection
*/
typedef enum{
    BME280_FILTER_OFF,
    BME280_FILTER_X2,
    BME280_FILTER_X4,
    BME280_FILTER_X8,
    BME280_FILTER_X16
}BME280_filtermode_e;

/** @enum BME280_filtermode_e
*   @brief BME280 temperature oversampling user selection
*   @note The actual value is found by dividing by 10 (ms)
*/
typedef enum{
    BME280_STANDBY_5    ,  // 0.5ms
    BME280_STANDBY_625  ,  // 62.5ms
    BME280_STANDBY_1250 ,  // 125ms
    BME280_STANDBY_2500 ,  // 250ms
    BME280_STANDBY_5000 ,  // 500ms
    BME280_STANDBY_10000,  // 1000ms
    BME280_STANDBY_100  ,  // 10ms
    BME280_STANDBY_200     // 20ms
}BME280_standbymode_e;