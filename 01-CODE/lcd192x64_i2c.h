    /*
    LCD 192x64 параллельный интерфейс
	Два соединенных расширителя PCF8574,
	один на управление, второй на шину данных.
*/

#ifndef _LCD192X64_I2C_H
#define _LCD192X64_I2C_H

#include "i2c.h"
#include "printf_uart.h"

#define _LCD_WIDTH  192
#define _LCD_HEIGHT  64

#define _I2C_ADDR_C	(0x20 << 1) // Адрес расширителя шины команд, сдвинут на 1 бит влево для STM32

#define _PIN_RS     (1 << 0)    // 1 - DATA, 0 - Instruction
#define _PIN_RW     (1 << 1)    // 1 - Read (LCD -> MCU) 0 - Write (MCU -> LCD)
#define _PIN_E      (1 << 2)    // 0/1 - Enable signal
#define _PIN_CS1	(1 << 3)    // 0 - Select 1-64 columns, 1 - off
#define _PIN_RST	(1 << 4)	// 1 - normal work, 0 - reset lcd
#define _PIN_CS2	(1 << 5)	// 0 - Select 65-128 columns, 1 - off
#define _PIN_CS3	(1 << 6)	// 0 - Select 129-192 columns, 1 - off

#define RB0(x)      x = x + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) << 0)
#define RB1(x)      x = x + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) << 1)
#define RB2(x)      x = x + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) << 2)
#define RB3(x)      x = x + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) << 3)
#define RB4(x)      x = x + (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) << 4)
#define RB5(x)      x = x + (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) << 5)
#define RB6(x)      x = x + (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) << 6)
#define RB7(x)      x = x + (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) << 7)

#define WB0(x)      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, x)
#define WB1(x)      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, x)
#define WB2(x)      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, x)
#define WB3(x)      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, x)
#define WB4(x)      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, x)
#define WB5(x)      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, x)
#define WB6(x)      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, x)
#define WB7(x)      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, x)

#define SetE        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)
#define ResE        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)

#define lcd1		(0x00)
#define lcd2		(0x01)
#define lcd3		(0x02)
#define lcds		(0x03)
#define nlcds		(0x04)
#define white       (0x00)
#define black       (0x01)

#define _LCD_ON		(0x3f)		// включить дисплей
#define _LCD_OFF	(0x3e)		// выключить дисплей, данные остаются в ОЗУ
#define _LCD_Y0		(0x40)		// Y0, (0..63)
#define _LCD_X0		(0xb8)		// X0, (0..7)
#define _LCD_L0		(0xc0)		// Line0, (0..63)
#define _LCD_busy   (0x80)      // 7 бит занятости LCD



#define LCD_DELAY_MS 5          // HAL_Delay 5

int SendLCD(_Bool cd, uint8_t lcd, uint8_t data);
void TurnInputPort();                   // включение порта ввод данных
void TurnOutputPort();                  // включение порта на вывод данных
void OffLCD(uint8_t lcd);               // выключение дисплея
void OnLCD(uint8_t lcd);                // включение дисплея
_Bool BusyLCD(uint8_t lcd);             // чтение флага занятости LCD
uint8_t DataLCD(uint8_t lcd);               // чтение данных с LCD
void ResetLCD();                        // сброс LCD
void GoToColLCD(uint8_t col);           // выбор столбца 0..191 (по горизонтали)
void GoToRowLCD(uint8_t row);           // страница 0..7 (по вертикали)
void GoToLCD(uint8_t x, uint8_t y);     // переход на страницу и столбец
void SetPixLCD(uint8_t x, uint8_t y, uint8_t mode);   // установить пиксел 0 - w, 1 - b, 2 - i
void ClearLCD(uint8_t lcd, _Bool color);             // заливка LCD
void LCD_Init();                        // инициализация LCD
void LCD_sendStr(char* str);
#endif //_LCD192X64_I2C_H
