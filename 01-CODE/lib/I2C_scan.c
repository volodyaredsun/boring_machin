#include "I2C_scan.h"

void I2C_scan(void)
{
    HAL_StatusTypeDef res;
    printf("Scanning I2C bus:\r\n");
    for(uint16_t i = 0; i < 127; i++)
    {
        res = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, 10);
        if(res == HAL_OK)
        {
            printf("\r\nDETECTED ADDRESS = 0x%02X\r\n", i);
        }
        else
        {
            printf("0x%02X  ", i);
        }
    }
}
