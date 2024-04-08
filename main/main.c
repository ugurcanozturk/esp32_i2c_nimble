#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_nimble_hci.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "sdkconfig.h"
#include "driver/i2c.h"
#include "bme280.h"
#include "adxl345.h"
#include "bmp280.h"


#define I2C_MASTER_SCL_IO             (GPIO_NUM_22)
#define I2C_MASTER_SDA_IO             (GPIO_NUM_21)
#define I2C_PORT_NUM_0                ( I2C_NUM_0 )
#define BME280_SENSOR_ADDR            (    0x76   )
#define ADXL345_SENSOR_ADDR           (    0x53   )
#define BMP280_SENSOR_ADDR            (    0x77   )
#define I2C_MASTER_FREQ_HZ            (   400000  )
#define I2C_MASTER_TIMEOUT_MS         (     1000  )
#define I2C_MASTER_TX_BUF_DISABLE     (      0    )                     
#define I2C_MASTER_RX_BUF_DISABLE     (      0    )
#define DATA_BUFFER_SIZE              (     20    )

char *TAG = "BLE-Ugur";
uint8_t ble_addr_type;
static const char *BME280 = "bme280 sicaklik";
static const char *BMP280 = "bmp280 sicaklik";
static const char *ADXL = "x axis";
void ble_app_advertise(void);
static esp_err_t  i2c_master_init(void);
int16_t x_axis;
int16_t bme280_temp;
int16_t bmp280_temp;

int16_t x_axisFiltered[DATA_BUFFER_SIZE];
int16_t bme280_tempFiltered[DATA_BUFFER_SIZE];
int16_t bmp280_tempFiltered[DATA_BUFFER_SIZE];
int16_t blePacket[3];


// Karakteristik tanımlama
#define SENSOR_DATA_UUID 0x3636
static uint8_t sensor_data_chr_value;

// Callback fonksiyonu
static int sensor_data_read(uint16_t con_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    os_mbuf_append(ctxt->om, &blePacket, sizeof(blePacket));
    return 0;
}

// Hizmet ve karakteristik tanımlama
static const struct ble_gatt_svc_def gatt_svcs[] = {
    {
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = BLE_UUID16_DECLARE(0x1800), // Özel bir servis UUID'si atanabilir
        .characteristics = (struct ble_gatt_chr_def[]){
            {
                .uuid = BLE_UUID16_DECLARE(SENSOR_DATA_UUID),
                .flags = BLE_GATT_CHR_F_READ,
                .access_cb = sensor_data_read,
            },
            {0},
        },
    },
    {0},
};

// BLE olaylarını işleme fonksiyonu
static int ble_gap_event(struct ble_gap_event *event, void *arg)
{
    switch (event->type)
    {
    case BLE_GAP_EVENT_CONNECT:
        ESP_LOGI("GAP", "BLE GAP EVENT CONNECT %s", event->connect.status == 0 ? "OK!" : "FAILED!");
        if (event->connect.status != 0)
        {
            // Bağlantı başarısız oldu, reklamı başlat
            ble_app_advertise();
        }
        break;
    case BLE_GAP_EVENT_DISCONNECT:
        ESP_LOGI("GAP", "BLE GAP EVENT DISCONNECTED");
        break;
    case BLE_GAP_EVENT_ADV_COMPLETE:
        ESP_LOGI("GAP", "BLE GAP EVENT");
        // Reklam tamamlandı, reklamı yeniden başlat
        ble_app_advertise();
        break;
    default:
        break;
    }
    return 0;
}

// BLE bağlantısını başlatma fonksiyonu
void ble_app_advertise(void)
{
    // Reklam verisi hazırlama
    struct ble_hs_adv_fields fields;
    const char *device_name;
    memset(&fields, 0, sizeof(fields));
    device_name = ble_svc_gap_device_name();
    fields.name = (uint8_t *)device_name;
    fields.name_len = strlen(device_name);
    fields.name_is_complete = 1;

    // Reklam parametrelerini ayarlama
    struct ble_gap_adv_params adv_params;
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

    // Reklam başlatma
    ble_gap_adv_start(ble_addr_type, NULL, BLE_HS_FOREVER, &adv_params, ble_gap_event, NULL);
}

// BLE senkronizasyonu tamamlandığında çağrılan fonksiyon
void ble_app_on_sync(void)
{
    // Adres tipini otomatik olarak belirleme
    ble_hs_id_infer_auto(0, &ble_addr_type);
    // Reklamı başlatma
    ble_app_advertise();
}

void host_task(void *param)
{
    nimble_port_run(); // This function will return only when nimble_port_stop() is executed
}

// Ana uygulama
void app_main()
{
    i2c_master_init();
    BME280_Init();
    BMP280_Init();
    ADXL345_Init();
   
    nvs_flash_init(); // NVS flash'ını başlatma
    nimble_port_init(); // Host yığını başlatma
    // Servisleri başlatma
    ble_svc_gap_device_name_set("BLE-Server");
    ble_svc_gap_init();
    ble_svc_gatt_init();
    ble_gatts_count_cfg(gatt_svcs);
    ble_gatts_add_svcs(gatt_svcs);
    // Senkronizasyon tamamlandığında çağrılacak fonksiyonu ayarlama
    ble_hs_cfg.sync_cb = ble_app_on_sync;
    // Ana görevi başlatma
    nimble_port_freertos_init(host_task);  
    
    while (1)
    {

         for(int i=0; i<DATA_BUFFER_SIZE;i++){
            
             bme280_temp =  BME280_CalculateTemp() /100;
             bmp280_temp = BMP280_CalculateTemp() /100;
             x_axis = ADXL345_XaxisCalculate();
            bme280_tempFiltered[i] = bme280_median_filter(bme280_temp);
            bmp280_tempFiltered[i] = bmp280_median_filter(bmp280_temp);
            x_axisFiltered[i]      = adxl_median_filter(x_axis);
            blePacket[0] = bme280_tempFiltered[i] ;
            blePacket[1] = bmp280_tempFiltered[i] ;
            blePacket[2] = x_axisFiltered[i]; 

            ESP_LOGI(BME280, "sicaklik bme280 = %x\n", bme280_tempFiltered[i]);
            ESP_LOGI(BMP280, "sicaklik bmep80 = %x\n", bmp280_tempFiltered[i] );
            ESP_LOGI(ADXL, "x axis = %x\n",x_axisFiltered[i]  );
             vTaskDelay(30000 / portTICK_PERIOD_MS);
         }
         
    }

}

static esp_err_t  i2c_master_init(void)
{
    int i2c_master_port = I2C_PORT_NUM_0;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

int16_t bme280_register_write(BME280_registerAddr_e reg_addr, uint8_t data){
     
     
     int temp = 0;
     uint8_t write_buf[2] ={reg_addr, data};

     

     i2c_master_write_to_device(I2C_PORT_NUM_0, BME280_SENSOR_ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

     return temp;
}

int16_t bme280_register_read(BME280_registerAddr_e reg_addr, uint8_t *data, size_t len){
  
    i2c_master_write_read_device(I2C_PORT_NUM_0, BME280_SENSOR_ADDR,&reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    

      return 0;
}

int16_t adxl_register_read(ADXL_registeraddr_e reg_addr, uint8_t *data, size_t len){

    i2c_master_write_read_device(I2C_PORT_NUM_0, ADXL345_SENSOR_ADDR,&reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return 0;
}

int16_t adxl_register_write(ADXL_registeraddr_e reg_addr, uint8_t data){
     
     
     uint8_t write_buf[2] ={reg_addr, data};

    i2c_master_write_to_device(I2C_PORT_NUM_0, ADXL345_SENSOR_ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return 0;
}

int16_t bmp280_register_write(BMP280_registerAddr_e reg_addr, uint8_t data){
     
     int temp = 0;
     uint8_t write_buf[2] ={reg_addr, data};


     i2c_master_write_to_device(I2C_PORT_NUM_0, BMP280_SENSOR_ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

     return temp;
}

int16_t bmp280_register_read(BMP280_registerAddr_e reg_addr, uint8_t *data, size_t len){
 
     i2c_master_write_read_device(I2C_PORT_NUM_0, BMP280_SENSOR_ADDR,&reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
     
      return 0;
}