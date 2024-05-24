// ПРИМЕР ОПРЕДЕЛЕНИЯ ПАДЕНИЯ АКСЕЛЕРОМЕТРА:                   // * Строки со звёздочкой являются необязательными.
                                                               //   АКСЕЛЕРОМЕТР: измеряет кажущееся угловое ускорение, которое является геометрической разницей между истинным угловым ускорением и ускорением силы гравитации (g).
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
#include <iarduino_Position_BMX055.h>                          //   Подключаем библиотеку iarduino_Position_BMX055 для работы с Trema-модулем IMU 9 DOF.
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
//   sensor.setFastOffset();                                   // * Выполняем калибровку акселерометра после установки нового диапазона измерений или частоты обновления данных.
}                                                              //   Чем выше диапазон и частота, тем ниже точность.
                                                               //
void loop(){                                                   //
     sensor.read();                                            //   Функция read() читает данные того датчика, для которого был создан объект.
                                                               //   Для объекта работающего с акселерометром, функция read() может принять
                                                               //   один из четырёх параметров: BMA_M_S, BMA_G, BMA_DEG, или BMA_RAD.
                                                               //   Если параметра нет, то используется параметр по умолчанию
                                                               //   sensor.read(BMA_M_S); читать угловое ускорение в м/с² (по умолчанию).
                                                               //   sensor.read(BMA_G  ); читать угловое ускорение в g.
                                                               //   sensor.read(BMA_DEG); читать углы «крен» и «тангаж» в градусах.
                                                               //   sensor.read(BMA_RAD); читать углы «крен» и «тангаж» в радианах.
                                                               //   Данные прочитанные функцией read() сохраняются в переменных axisX, axisY, axisZ и temp.
     float g=9.81f;                                            //   Ускорение свободного падения примерно равно 9,81 м/с².
     float x=sensor.axisX;                                     //   Получаем проекцию вектора кажущегося ускорения на ось X.
     float y=sensor.axisY;                                     //   Получаем проекцию вектора кажущегося ускорения на ось Y.
     float z=sensor.axisZ;                                     //   Получаем проекцию вектора кажущегося ускорения на ось Z.
     float a=sqrt(sq(x)+sq(y)+sq(z));                          //   Получаем величину вектора кажущегося ускорения a = √(x²+y²+z²).
                                                               // 
//   Кажущееся ускорение = истинное ускорение - гравитация.    //   В состоянии покоя истинное ускорение = 0, а ускорение силы гравитации = g.
//   При свободном падении, кажущееся ускорение почти = 0.     //   Истенное ускорение равно g и ускорение силы гравитации равно g. a=g-g=0.
//                                                             //
     if( a < g/4 ){                                            //   Если кажущееся ускорение ниже четверти g, значит модуль падает.
         Serial.print(F("Я падаю вдоль оси "));                //
     //  Определяем ось вдоль которой падает модуль:           //   g примерно = 9.81, значит истинное ускорение примерно равно 0, но ре равно 0.00000!
         x=abs(x); y=abs(y); z=abs(z);                         //   Берём модуль от значений прокции на оси.
         if( x>y ){ Serial.println(x>z?'X':'Z'); }             //   Если X>Y значит модуль падает вдоль оси X или Z.
         else     { Serial.println(y>z?'Y':'Z'); }             //   Иначе           модуль падает вдоль оси Y или Z.
     }                                                         //
}                                                              //