//  Раскомментируйте для программной реализации шины I2C:   //
//  #define pin_SW_SDA 3                                    // Назначение любого вывода Arduino для работы в качестве линии SDA программной шины I2C.
//  #define pin_SW_SCL 9                                    // Назначение любого вывода Arduino для работы в качестве линии SCL программной шины I2C.
//  Раскомментируйте для совместимости с большинством плат: //
//  #include <Wire.h>                                       // Библиотека iarduino_Position_BMX055 будет использовать методы и функции библиотеки Wire.
//  Ссылки для ознакомления:                                //
//  Подробная информация о подключении модуля к шине I2C:   // http://wiki.iarduino.ru/page/i2c_connection/
//  Подробная информация о функциях и методах библиотеки:   // http://wiki.iarduino.ru/page/Trema_IMU9/
                                                            //
/* ОТДЕЛЬНОЕ ЧТЕНИЕ ВСЕХ ДАТЧИКОВ */                        // 
                                                            //
#include <iarduino_Position_BMX055.h>                       // Подключаем библиотеку iarduino_Position_BMX055 для работы с Trema-модулем IMU 9 DOF.
iarduino_Position_BMX055 sensorA(BMA);                      // Создаём объект sensorA указывая что ему требуется работать только с акселерометром.
iarduino_Position_BMX055 sensorG(BMG);                      // Создаём объект sensorG указывая что ему требуется работать только с гироскопом.
iarduino_Position_BMX055 sensorM(BMM);                      // Создаём объект sensorM указывая что ему требуется работать только с магнитометром.
                                                            // Имена создаваемых объектов должны отличаться!
void setup(){                                               // 
     Serial.begin(9600);                                    // Инициируем передачу данных в монитор последовательного порта на скорости 9600 бит/сек.
     while(!Serial){}                                       // Ждём готовность Serial к передаче данных в монитор последовательного порта.
     sensorA.begin();                                       // Инициируем работу с датчиком объекта sensorA - это акселерометр.
     sensorG.begin();                                       // Инициируем работу с датчиком объекта sensorG - это гироскоп.
     sensorM.begin();                                       // Инициируем работу с датчиком объекта sensorM - это магнитометр.
}                                                           //
void loop(){                                                // 
                                                            // Функция read() читает данные того датчика, для которого был создан объект.
                                                            // Так как мы создали 3 разных объекта для работы с разными датчиками, то
                                                            // данные читаемые функцией read() будут зависеть от объекта для которого она вызвана.
                                                            // Функцию read() можно вызвать с параметром, выбрав единицы измерений выводимых данных.
                                                            // Если функция read вызывается без параметра, то данные выводятся в единицах по умолчанию.
     sensorA.read();                                        // sensorA.read(BMA_M_S);   читать угловое ускорение в м/с² (по умолчанию).
                                                            // sensorA.read(BMA_G);     читать угловое ускорение в g.
                                                            // sensorA.read(BMA_DEG);   читать углы «крен» и «тангаж» в градусах.
                                                            // sensorA.read(BMA_RAD);   читать углы «крен» и «тангаж» в радианах.
     sensorG.read();                                        // sensorG.read(BMG_DEG_S); читать угловую скорость в °/c. (по умолчанию).
                                                            // sensorG.read(BMG_RAD_S); читать угловую скорость в рад/c.
     sensorM.read();                                        // sensorM.read(BMM_MG);    читать индукцию магнитного поля в мГс. (по умолчанию).
                                                            // sensorM.read(BMM_MCT);   читать индукцию магнитного поля в мкТл.
                                                            // Данные прочитанные функцией read() сохраняются в переменных axisX, axisY, axisZ и temp.
                                                            // Значение этих переменных у каждого объекта своё.
     Serial.print("АКСЕЛЕРОМЕТР(");
     Serial.print("X="); Serial.print(sensorA.axisX); Serial.print(", ");
     Serial.print("Y="); Serial.print(sensorA.axisY); Serial.print(", ");
     Serial.print("Z="); Serial.print(sensorA.axisZ); Serial.print(" м/с²) ");
     Serial.print("ГИРОСКОП(");
     Serial.print("X="); Serial.print(sensorG.axisX); Serial.print(", ");
     Serial.print("Y="); Serial.print(sensorG.axisY); Serial.print(", ");
     Serial.print("Z="); Serial.print(sensorG.axisZ); Serial.print(" °/c) ");
     Serial.print("МАГНИТОМЕТР(");
     Serial.print("X="); Serial.print(sensorM.axisX); Serial.print(", ");
     Serial.print("Y="); Serial.print(sensorM.axisY); Serial.print(", ");
     Serial.print("Z="); Serial.print(sensorM.axisZ); Serial.print(" мГс)\r\n");
}
