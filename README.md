2020.12.29 Расточной-наплавчный мобильный комплекс XDS-50.
Два привода:
    1. Подача - шаговый двигатель с контроллером SH-DSP86
    2. Главное движение - синхронный двигатель с постоянными магнитами, с сервоприводом - 130SFM-E15015
Приводами управляем совмещенный PLC+HMI не понятной марки, Китайского происхождения.
Захотелось сделать свой контроллер управления, т.к. на родном не хватает многих функций, хотя их можно было бы реализовать.
Дисплей решено оставить родным - 192х64. Контроллер - STM32F401CCU6. Управляется дисплей от двух сдвиговых регистров PCF8574.
