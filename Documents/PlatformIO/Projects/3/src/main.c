#include "esp_common.h"
#include "freertos/task.h"
#include "gpio.h"

/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;
    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}
char* morse(char c){
  static char* morse_ch[]={
    "._!","_...!","_._.!","_..!",".!",".._.!","__.!","....!","..!",".___!"
    ,"_._!","._..!","__!","_.!","___!",".__.!","__._!","._.!","...!","_!"
    ,".._!","..._!",".__!","_.._!","_.__!","__..!"
  };
  return morse_ch[c - 'a'];
}

int str2morse(char *buff, int n,const char* str){
  while(*str && n!=0){
    buff = morse(*str);
    //char *strcpy(*buff, morse(str));
    buff++;
    str++;
  }
  return 1;
}

void morse_send(const char* msg){
  switch(*msg){
    case '.':
    GPIO_OUTPUT_SET(2, 0);
      vTaskDelay(250/portTICK_RATE_MS);
    GPIO_OUTPUT_SET(2, 1);
      vTaskDelay(250/portTICK_RATE_MS);
    break;

    case '_':
    GPIO_OUTPUT_SET(2, 0);
      vTaskDelay(750/portTICK_RATE_MS);
    GPIO_OUTPUT_SET(2, 1);
      vTaskDelay(250/portTICK_RATE_MS);
    break;

    case '!':
      GPIO_OUTPUT_SET(2, 1);
      vTaskDelay(500/portTICK_RATE_MS);
    break;

    case ' ':
      GPIO_OUTPUT_SET(2, 1);
      vTaskDelay(1000/portTICK_RATE_MS);
    break;
  }
}
void task_blink(void* ignore)
{
    GPIO_AS_OUTPUT(2);
    //gpio2_output_conf();
    while(true) {
      char* cadena = (char*)malloc(256);
      str2morse(cadena,256,"hola mundo");
      morse_send(cadena);
    }
    vTaskDelete(NULL);
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
    xTaskCreate(&task_blink, "startup", 2048, NULL, 1, NULL);
}
