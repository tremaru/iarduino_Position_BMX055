[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

# iarduino_Position_BMX055

**This is a library for Arduino IDE. It allows to control [IMU-sensor, 9 DOF](https://iarduino.ru/shop/Sensory-Datchiki/imu-9.html) I2C modules made by iArduino.ru**

**Данная библиотека для Arduino IDE позвляет управлять Trema-модулем [IMU-сенсор на 9 степеней свободы](https://iarduino.ru/shop/Sensory-Datchiki/imu-9.html)**

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_librari/).

> Подробнее про подключение к [Arduino UNO](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) читайте на нашей [wiki](https://wiki.iarduino.ru/page/Trema_IMU9/)

| Модель | Ссылка на магазин |
|--|--|
| ![](https://wiki.iarduino.ru/img/resources/922/922.svg) | https://wiki.iarduino.ru/page/multi-servo-shield-na-16-servoprivodov/) |

##Основные функции библиотеки:

```C++
#include <iarduino_Position_BMX055.h> // Подключаем библиотеку для работы с Trema-модулем IMU 9 DOF.
iarduino_Position_BMX055 ОБЪЕКТ( ДАТЧИК ); // Создаём объект указывая с каким датчиком модуля ему работать.
```

**Инициализация работы с датчиком модуля.**

    Функция begin( [ КАЛИБРОВКА ] ); // Инициализация работы с датчиком модуля.

**Выполнение аппаратного самотестирования.**

    Функция test(); // Выполнение аппаратного самотестирования.

**Чтение показаний.**

    Функция read( [ ЕДИНИЦЫ_ИЗМЕРЕНИЯ ] ); // Чтение показаний.

**Установка диапазона измерений.**

    Функция setScale( ДИАПАЗОН ); // Установка диапазона измерений.

**Установка полосы пропускания.**

    Функция setBandwidths( ЧАСТОТА ); // Установка полосы пропускания.

**Калибровка - выполнение быстрой компенсации смещения данных.**

    Функция setFastOffset(); // Калибровка - выполнение быстрой компенсации смещения данных.

**Вывод названия фильтра используемого для расчёта кватернионов.**

    Функция getFilter(); // Вывод названия фильтра используемого для расчёта кватернионов.

**Показания для оси X или угол «тангаж».**

    Переменная axisX // (float) содержит показания для оси X или угол «тангаж».

**Показания для оси Y или угол «крен».**

    Переменная axisY // (float) содержит показания для оси Y или угол «крен».

**Показания для оси Z или угол «курс».**

    Переменная axisZ // (float) содержит показания для оси Z или угол «курс».

**Температура в °С.**

    Переменная temp // (float) содержит температуру в °С.

**кватернионы.**

    Переменные q1, q2, q3, q4 // (float) содержат кватернионы.
