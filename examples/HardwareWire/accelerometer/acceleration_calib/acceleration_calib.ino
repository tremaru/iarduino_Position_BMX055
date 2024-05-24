// ПРИМЕР КАЛИБРОВКИ И ЧТЕНИЯ ДАННЫХ АКСЕЛЕРОМЕТРА:            // * Строки со звёздочкой являются необязательными.
// с предварительной калибровкой датчика                       //   АКСЕЛЕРОМЕТР: измеряет кажущееся угловое ускорение, которое является геометрической разницей между истинным угловым ускорением и ускорением силы гравитации (g).
                                                               //   Если акселерометр неподвижен (истинное ускорение отсутствует), его оси XY параллельны земле, а ось Z направлена вверх, то ...
                                                               //   проекция кажущегося ускорения на ось Z = 0 - -g = g. Где 0 это истинное ускорение, а -g сила гравитации направленная в сторону противоположную оси Z.
                                                               //   Так как вектор g всегда направлен к земле, то в неподвижном состоянии, по данным датчика можно определить угол наклона устройства относительно поверхности Земли.
                                                               //   Эти данные можно использовать, например, для поворота изображения на экране (альбомное / ландшафтное).
// ССЫЛКИ для ознакомления:                                    //   
// IMU-сенсор на 9 степеней свободы (Trema-модуль V2.0):       //   https://iarduino.ru/shop/Sensory-Datchiki/imu-9.html
// Информация о подключении модулей к шине I2C:                //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                  //   https://wiki.iarduino.ru/page/Trema_IMU9/
                                                               //
#define BMX055_DISABLE_BMG                                     // * Не использовать гироскоп     (данную строку можно и не писать, но её наличие освобождает память программ за счет неиспользуемого датчика).
#define BMX055_DISABLE_BMM                                     // * Не использовать магнитометр  (данную строку можно и не писать, но её наличие освобождает память программ за счет неиспользуемого датчика).
                                                               //
#include <Wire.h>                                              //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_Position_BMX055.
#include <iarduino_Position_BMX055.h>                          //   Подключаем библиотеку для работы с Trema-модулем IMU 9 DOF.
iarduino_Position_BMX055 sensor(BMA);                          //   Создаём объект sensor указывая что ему требуется работать только с акселерометром.
                                                               //   Если указать параметр BMA - то объект будет работать только с акселерометром.
                                                               //   Если указать параметр BMG - то объект будет работать только с гироскопом.
                                                               //   Если указать параметр BMM - то объект будет работать только с магнитометром.
                                                               //   Если указать параметр BMX - то объект будет работать со всеми датчиками сразу.
void setup(){                                                  // 
     Serial.begin(9600);                                       //   Инициируем передачу данных в монитор последовательного порта на скорости 9600 бит/сек.
     while(!Serial){}                                          // * Ждём готовность Serial к передаче данных в монитор последовательного порта.
     sensor.begin(&Wire); // &Wire1, &Wire2 ...                //   Инициируем работу с акселерометром, так как именно для работы с ним создан объект sensor. Указав ссылку на объект для работы с шиной I2C на которой находится модуль (по умолчанию &Wire).
//   sensor.setScale(BMA_4G);                                  // * Меняем диапазон измерений до ±4G. Возможные значения: BMA_2G (по умолчанию), BMA_4G, BMA_8G, BMA_16G.
//   sensor.setBandwidths(BMA_125Hz);                          // * Меняем частоту обновления данных на 125Гц. Возможные значения: BMA_8Hz, BMA_16Hz (по умолчанию), BMA_31Hz, BMA_63Hz, BMA_125Hz, BMA_250Hz, BMA_500Hz, BMA_1000Hz.
//   Выводим подсказку по калибровке:                          //   Чем выше диапазон и частота, тем ниже точность.
     Serial.println(F("КАЛИБРОВКА:"));                         // *
     Serial.println(F("Установите модуль так, чтоб"));         // *
     Serial.println(F("ось Z была направлена вверх."));        // * Это положение при котором детали на плате модуля смотрят вверх.
     Serial.println(F("Модуль должен быть неподвижен."));      // *
     Serial.println(F("Калибровка начнётся через 5 сек."));    // *
     delay(5000);                                              // * Даём время установить модуль в требуемое положение.
//   Выполняем калибровку:                                     //
     Serial.println(F("Начинаем калибровку..."));              // *
     sensor.setFastOffset();                                   //   После калибровки, оси X и Y будут показывать 0.0 м/с², а ось Z 9.81 м/с².
     Serial.println(F("Калибровка завершена!"));               // 
     delay(1000);                                              // * После калибровки данные скорректируются через 200-300 мс.
//   ВАЖНО:                                                    //
//   Если в скетче меняется диапазон измерений setScale()      //
//   или частота обновления данных setBandwidths(), то         //
//   калибровка выполняется после указанных изменений.         //
}                                                              //
                                                               //
void loop(){                                                   // 
     sensor.read();                                            //   Функция read() читает данные того датчика, для которого был создан объект sensor.
                                                               //   Для объекта работающего с акселерометром, функция read() может принять
                                                               //   один из четырёх параметров: BMA_M_S, BMA_G, BMA_DEG, или BMA_RAD.
                                                               //   Если параметра нет (как в примере), то используется параметр по умолчанию:
                                                               //   sensor.read(BMA_M_S); читать угловое ускорение в м/с² (по умолчанию).
                                                               //   sensor.read(BMA_G  ); читать угловое ускорение в g.
                                                               //   sensor.read(BMA_DEG); читать углы «крен» и «тангаж» в градусах.
                                                               //   sensor.read(BMA_RAD); читать углы «крен» и «тангаж» в радианах.
                                                               //   Данные прочитанные функцией read() сохраняются в переменных axisX, axisY, axisZ и temp.
     Serial.print((String) "X="+sensor.axisX+", ");            //   Выводим проекцию кажущегося углового ускорения на ось X в м/с².
     Serial.print((String) "Y="+sensor.axisY+", ");            //   Выводим проекцию кажущегося углового ускорения на ось Y в м/с².
     Serial.print((String) "Z="+sensor.axisZ+" м/с² \r\n");    //   Выводим проекцию кажущегося углового ускорения на ось Z в м/с².
}