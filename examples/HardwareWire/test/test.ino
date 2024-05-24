// ПРИМЕР САМОТЕСТИРОВАНИЯ МОДУЛЯ:                             // * Строки со звёздочкой являются необязательными.
// (тестируются те датчики, для которых создан объект)         //   В начале самотестирования проверяется наличие ответа от датчиков.
                                                               //   При самотестировании акселерометра, к его сердечнику, внутрисхемно, прикладываются электростатические силы разных направлений вдоль каждой оси.
                                                               //   При самотестировании гироскопа, проверяются регулятор напряжения драйвера, регулятор смещения входных каналов по всем осям и регуляторы самих каналов.
                                                               //   При самотестировании магнитометра, проверяются лимиты показаний по всем осям, и чтение показаний оси Z с приложением тока разных направлений на встренную катушку индуктивности.
// ССЫЛКИ для ознакомления:                                    //   
// IMU-сенсор на 9 степеней свободы (Trema-модуль V2.0):       //   https://iarduino.ru/shop/Sensory-Datchiki/imu-9.html
// Информация о подключении модулей к шине I2C:                //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                  //   https://wiki.iarduino.ru/page/Trema_IMU9/
                                                               // 
#include <Wire.h>                                              //   Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_Position_BMX055.
#include <iarduino_Position_BMX055.h>                          //   Подключаем библиотеку для работы с Trema-модулем IMU 9 DOF.
iarduino_Position_BMX055 sensor(BMX);                          //   Создаём объект sensor указывая параметр BMX - требуется работать со всеми датчиками модуля.
                                                               //   Если указать параметр BMA - то объект будет работать только с акселерометром.
                                                               //   Если указать параметр BMG - то объект будет работать только с гироскопом.
                                                               //   Если указать параметр BMM - то объект будет работать только с магнитометром.
                                                               //   Если указать параметр BMX - то объект будет работать со всеми датчиками сразу.
void setup(){                                                  // 
     Serial.begin(9600);                                       //   Инициируем передачу данных в монитор последовательного порта на скорости 9600 бит/сек.
     while(!Serial){}                                          // * Ждём готовность Serial к передаче данных в монитор последовательного порта.
     sensor.begin(&Wire); // &Wire1, &Wire2 ...                //   Инициируем работу со всеми датчиками модуля, так как именно для работы с ними создан объект sensor. Указав ссылку на объект для работы с шиной I2C на которой находится модуль (по умолчанию &Wire).
//   sensor.setScale(BMA_4G);                                  //   Меняем диапазон измерений акселерометра до ±4G.          Возможные значения: BMA_2G (по умолчанию), BMA_4G, BMA_8G, BMA_16G.
//   sensor.setScale(BMG_500DPS);                              //   Меняем диапазон измерений гироскопа до ±500°/с.          Возможные значения: BMG_125DPS (по умолчанию), BMG_250DPS, BMG_500DPS, BMG_1000DPS, BMG_2000DPS.
//   sensor.setScale(BMM_ENHANCED);                            //   Меняем количество выборок магнитометра на BMM_ENHANCED.  Возможные значения: BMM_LOW_PWR, BMM_REGULAR (по умолчанию), BMM_ENHANCED, BMM_HIGH.
//   sensor.setBandwidths(BMA_125Hz);                          //   Меняем частоту обновления данных акселерометра на 125Гц. Возможные значения: BMA_8Hz, BMA_16Hz (по умолчанию), BMA_31Hz, BMA_63Hz, BMA_125Hz, BMA_250Hz, BMA_500Hz, BMA_1000Hz.
//   sensor.setBandwidths(BMG_64Hz);                           //   Меняем частоту обновления данных гироскопа     на 64Гц.  Возможные значения: BMG_12Hz, BMG_23Hz (по умолчанию), BMG_32Hz, BMG_47Hz, BMG_64Hz, BMG_116Hz, BMG_230Hz, BMG_523Hz.
//   sensor.setBandwidths(BMM_20Hz);                           //   Меняем частоту обновления данных магнитометра  на 20Гц.  Возможные значения: BMM_2Hz, BMM_6Hz, BMM_8Hz, BMM_10Hz (по умолчанию), BMM_15Hz, BMM_20Hz, BMM_25Hz, BMM_30Hz.
//   sensor.setFastOffset(BMA);                                //   Выполняем калибровку акселерометра после установки нового диапазона измерений или частоты обновления данных.
//   sensor.setFastOffset(BMG);                                //   Выполняем калибровку гироскопа после установки нового диапазона измерений или частоты обновления данных.
//   while(не_истекло_время){sensor.setFastOffset(BMM);}       //   Выполняем калибровку магнитометра после установки нового диапазона измерений или частоты обновления данных в течении указанного времени модуль должен вращаться.
//   Выводим подсказку по тестированию:                        //   Чем выше диапазон и частота, тем ниже точность.
     Serial.println(F("САМОТЕСТИРОВАНИЕ МОДУЛЯ:"));            // *
     Serial.println(F("Модуль должен быть неподвижен."));      // *
     Serial.println(F("Положение модуля не имеет значения.")); // *
     Serial.println(F("Тестирование начнётся через 5 сек."));  // *
     delay(5000);                                              // *
//   Выполняем самотестирование:                               //
     switch(sensor.test()){                                    //   Получаем результат самотестирования для его сравнения с указанными ниже константами.
         case 0:          Serial.println(F("Аппаратное самотестирование всех датчиков успешно пройдено!")); break;
         case BMA_ERR_ID: Serial.println(F("Акселерометр не найден."));                                     break;
         case BMG_ERR_ID: Serial.println(F("Гироскоп не найден."));                                         break;
         case BMM_ERR_ID: Serial.println(F("Магнитометр не найден."));                                      break;
         case BMA_ERR_ST: Serial.println(F("Акселерометр не прошел самотестирование."));                    break;
         case BMG_ERR_ST: Serial.println(F("Гироскоп не прошел самотестирование."));                        break;
         case BMM_ERR_ST: Serial.println(F("Магнитометр не прошел самотестирование."));                     break;
         default:         Serial.println(F("Модуль не прошел самотестирование по неизвестной причине."));   break;
     }                                                         //
//   ПРИМЕЧАНИЕ:                                               //
//   Если объект sensor создан не для всех датчиков (BMX),     //
//   а для работы с конкретным датчиком BMA, BMG или BMM,      //
//   то функция test() запустит самотестирование только        //
//   того датчика, для которого был создан объект sensor.      //
}                                                              //
                                                               //
void loop(){}                                                  //
