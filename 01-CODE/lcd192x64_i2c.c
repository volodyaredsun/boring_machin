#include "lcd192x64_i2c.h"

int SendLCD(_Bool cd, uint8_t lcd, uint8_t data)
{
    HAL_StatusTypeDef res = 0;
	uint8_t cmd[1] = {0};
	
	if (cd == 1)
	{
		cmd[0] &= ~_PIN_RS;			// Instruction		
	}
	else
		cmd[0] |= _PIN_RS;			// Data

	cmd[0] &= ~_PIN_RW;				// MCU -> LCD
    cmd[0] |= _PIN_RST;				// RESET lcd, это нормальная работа дисплея
	
	switch(lcd)
	{
		case lcd1:
		{
			cmd[0] &= ~_PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
		case lcd2:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] &= ~_PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
		case lcd3:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] &= ~_PIN_CS3;
            break;
		}
        case lcds:
		{
            cmd[0] &= ~_PIN_CS1;
			cmd[0] &= ~_PIN_CS2;
			cmd[0] &= ~_PIN_CS3;
            break;
		}
		case nlcds:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
	}
	
    TurnOutputPort();
    WB0(data & (1 << 0));
    WB1(data & (1 << 1));
    WB2(data & (1 << 2));
    WB3(data & (1 << 3));
    WB4(data & (1 << 4));
    WB5(data & (1 << 5));
    WB6(data & (1 << 6));
    WB7(data & (1 << 7));
    printf("dat =  %02d \n\r", data);
    printf("db =  %02d \n\r", data & (1 << 7));
	res = HAL_I2C_Master_Transmit(&hi2c1, _I2C_ADDR_C, &cmd[0], 1, 100);   // выставляем команду
    SetE;
    __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
        __asm("nop");
    __asm("nop");
    //HAL_Delay(1);
    ResE;
    printf("READ_cmd =  %02d \n\r", cmd[0]);
    return res;
}

_Bool BusyLCD(uint8_t lcd)
{
    HAL_StatusTypeDef res = 0;
    uint8_t d = 0;
    uint8_t cmd[1] = {0};
    
    TurnInputPort();
    
    cmd[0] &= ~_PIN_RS;            // Instruction
    cmd[0] |= _PIN_RW;             // LCD -> MCU
    cmd[0] |= _PIN_RST;
    
    switch(lcd)
	{
		case lcd1:
		{
			cmd[0] &= ~_PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
		case lcd2:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] &= ~_PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
		case lcd3:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] &= ~_PIN_CS3;
            break;
		}
        case lcds:
		{
            cmd[0] &= ~_PIN_CS1;
			cmd[0] &= ~_PIN_CS2;
			cmd[0] &= ~_PIN_CS3;
            break;
		}
		case nlcds:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
	}
    
    res = HAL_I2C_Master_Transmit(&hi2c1, _I2C_ADDR_C, &cmd[0], 1, 100);
    SetE;
    __asm("nop");
    __asm("nop");
    ResE;
    
    RB0(d);
    RB1(d);
    RB2(d);
    RB3(d);
    RB4(d);
    RB5(d);
    RB6(d);
    RB7(d);
    
    printf("ByteStateLCD =  %02d \n\r", d);
    return d & _LCD_busy;
}

uint8_t DataLCD(uint8_t lcd)
{
    HAL_StatusTypeDef res = 0;
    uint8_t cmd[1] = {0};
    uint8_t d = 0;

    TurnInputPort();
    
    switch(lcd)
	{
		case lcd1:
		{
			cmd[0] &= ~_PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
		case lcd2:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] &= ~_PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
		case lcd3:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] &= ~_PIN_CS3;
            break;
		}
        case lcds:
		{
            cmd[0] &= ~_PIN_CS1;
			cmd[0] &= ~_PIN_CS2;
			cmd[0] &= ~_PIN_CS3;
            break;
		}
		case nlcds:
		{
			cmd[0] |= _PIN_CS1;
			cmd[0] |= _PIN_CS2;
			cmd[0] |= _PIN_CS3;
            break;
		}
	}
    
    cmd[0] |= _PIN_RS;              // Data
    cmd[0] |= _PIN_RW;              // LCD -> MCU
    cmd[0] |= _PIN_RST;

    res += HAL_I2C_Master_Transmit(&hi2c1, _I2C_ADDR_C, &cmd[0], 1, 100);
    SetE;
    __asm("nop");
    __asm("nop");
    ResE;
    __asm("nop");
    __asm("nop");
    SetE;   

    RB0(d);
    RB1(d);
    RB2(d);
    RB3(d);
    RB4(d);
    RB5(d);
    RB6(d);
    RB7(d);
    
    ResE;

    printf("N_______________________________________\n\r");
    printf("d[0] = 0x%02X \n\r", cmd[0]);
    printf("dat =  %02d \n\r", d);
    printf("E________________________________________\n\r");
    
    return d;
}

void LCD_Init()
{   
    HAL_Delay(1);
    ResetLCD();              // сброс LCD при включении  
    HAL_Delay(1);
	SendLCD(1, lcds, _LCD_Y0);
    HAL_Delay(1);
	SendLCD(1, lcds, _LCD_X0);
	HAL_Delay(1);
	SendLCD(1, lcds, _LCD_L0);
	HAL_Delay(1);
}

void ResetLCD()
{
    uint8_t d[2] = {0};
    d[0] &= ~_PIN_RST;
    d[1] |= _PIN_RST;
    HAL_I2C_Master_Transmit(&hi2c1, _I2C_ADDR_C, &d[0], 1, 1000);
    HAL_Delay(1);
    HAL_I2C_Master_Transmit(&hi2c1, _I2C_ADDR_C, &d[1], 1, 1000);
}

void GoToRowLCD(uint8_t row)
{
    SendLCD(1, lcds, (row | _LCD_X0) & 0xbf);   // 0..7 строки
}

void GoToColLCD(uint8_t col)                    // 0..191 столбцы
{
    if (col < 64)
    {
        SendLCD(1, lcd1, (col | _LCD_Y0) & 0x7f);
    }
    else if (col < 128)
    {
        SendLCD(1, lcd2, ((col - 64) | _LCD_Y0) & 0x7f);
    }
    else if (col < 192)
    {
        SendLCD(1, lcd3, ((col - 128) | _LCD_Y0) & 0x7f);
    }
}
void GoToLCD(uint8_t x, uint8_t y)  // меняем местами строки и столбцы
{
    GoToRowLCD(y);                  // 0..7 строки
    GoToColLCD(x);                  // 0.191 столбцы
}

void SetPixLCD(uint8_t x, uint8_t y, uint8_t mode)
{
    uint8_t dlcd = 0;
    uint8_t data = 0;
    uint8_t lcd;

    GoToLCD(x, y/8);                      // из строк выделяем страницы
    if(x < 64){lcd = lcd1;} else if(x < 128){lcd = lcd2;} else if (x < 192){lcd = lcd3;}
    // из-за операции чтения, смещается на две единицы столбец
    dlcd = DataLCD(lcd);
    //printf("N_LCD = %02d \n\r", lcd);
    printf("dataLCD = 0x%02X \n\r", dlcd);
    switch (mode)
    {
        case 0:
        {
            //data = ~(1<<(y%8));
            data = dlcd & ~(1<<(y%8));    // белый пиксель
            break;
        }
        case 1:
        {
            //data = (1<<(y%8));
            data = dlcd | (1<<(y%8));     // черный пиксель
            break;
        }
        case 2:
        {
            data = dlcd ^ (1<<(y%8));     // инвертированный пиксель
            break;
        }
        case 3:
        {
            data = 0x55;
        }
    }
    SendLCD(0, lcd, data);
}

void ClearLCD(uint8_t lcd, _Bool color)
{
    uint8_t i, j;
    for(i=0; i<(_LCD_HEIGHT/8); i++)
    {
        GoToRowLCD(i);
        for(j=0; j<64; j++)         // после записи, адрес стобцов автоматически сдвигается на 1
        {
            if(color)
            {
                SendLCD(0, lcd, 0xff);
            }
            else
            {
                SendLCD(0, lcd, 0x00);
            }
        }
    }
}
void OffLCD(uint8_t lcd)
{
    SendLCD(1, lcd, _LCD_OFF);
}

void OnLCD(uint8_t lcd)
{
    SendLCD(1, lcd, _LCD_ON);
}

void LCD_sendStr(char* str)
{

}

void TurnInputPort()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void TurnOutputPort()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
    
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
    //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
    
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);    
}
