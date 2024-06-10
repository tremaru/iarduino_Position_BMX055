// ПРИМЕР КАЛИБРОВКИ И ЧТЕНИЯ ДАННЫХ МАГНИТОМЕТРА:             // * Строки со звёздочкой являются необязательными.
// с предварительной калибровкой датчика                       //   МАГНИТОМЕТР: измеряет магнитную индукцию, он определяет положение устройства в пространстве отностиельно магнитных полюсов земли.
                                                               //   Значения оси направленной в сторону северного полюса будут положительными, а значения оси направленной в сторону южного полюса будут отрицательны.
                                                               //   На экваторе магнитные линии параллельны земле (0°), но ближе к полюсам их угол относительно земли приближается к 90° и они становятся перпендикулярны земле.
                                                               //   Так что не удивляйтесь если максимальные показания осей будут направлены вниз или верх от земли, это не помешает использовать показания остальных осей как компас.
                                                               //   Показания магнитометра сильно меняются от любых намагниченных предметов, по этому его нужно калибровать или указывать полученные ранее калибровочные коэффициенты.
                                                               //
// Требуется установить библиотеку <iarduino_I2C_Software.h>   //   https://iarduino.ru/file/627.html
                                                               //
// ССЫЛКИ для ознакомления:                                    //   
// IMU-сенсор на 9 степеней свободы (Trema-модуль V2.0):       //   https://iarduino.ru/shop/Sensory-Datchiki/imu-9.html
// Информация о подключении модулей к шине I2C:                //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                  //   https://wiki.iarduino.ru/page/Trema_IMU9/
                                                               //
#define BMX055_DISABLE_BMA                                     // * Не использовать акселерометр (данную строку можно и не писать, но её наличие освобождает память программ за счет неиспользуемого датчика)
#define BMX055_DISABLE_BMG                                     // * Не использовать гироскоп     (данную строку можно и не писать, но её наличие освобождает память программ за счет неиспользуемого датчика)
                                                               //
#include <iarduino_I2C_Software.h>                             //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_Position_BMX055.
SoftTwoWire sWire(3,4);                                        //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                               //
#include <iarduino_Position_BMX055.h>                          //   Подключаем библиотеку для работы с Trema-модулем IMU 9 DOF.
iarduino_Position_BMX055 sensor(BMM);                          //   Создаём объект sensor указывая что ему требуется работать только с магнитометром.
                                                               //   Если указать параметр BMA - то объект будет работать только с акселерометром.
                                                               //   Если указать параметр BMG - то объект будет работать только с гироскопом.
                                                               //   Если указать параметр BMM - то объект будет работать только с магнитометром.
                                                               //   Если указать параметр BMX - то объект будет работать со всеми датчиками сразу.
                                                               // 
//   Если требуется выполнить калибровку:                      // *
     float coefficients[3];                                    // * В этот массив будут записаны результаты калибровки. Эти данные можно сохранить и использовать вместо калибровки.
                                                               // 
//   Если уже известны результаты калибровки:                  // *
//   float coefficients[3] = {-122.5f, 63.75f, -105.63f};      // * Определяем массив данных полученных функцией getFastOffset() после калибровки.
                                                               //   У вас будут другие значения! Значения зависят от модуля и установленных рядом с ним металлических и магнитных предметов.
void setup(){                                                  // 
     Serial.begin(9600);                                       //   Инициируем передачу данных в монитор последовательного порта на скорости 9600 бит/сек.
     while(!Serial){}                                          // * Ждём готовность Serial к передаче данных в монитор последовательного порта.
     sensor.begin(&sWire);                                     //   Инициируем работу с магнитометром, так как именно для работы с ним создан объект sensor. Указав ссылку на объект для работы с шиной I2C на которой находится модуль (по умолчанию &Wire).
//   sensor.setScale(BMM_ENHANCED);                            // * Меняем количество выборок на предустановленное значение BMM_ENHANCED. Возможные значения: BMM_LOW_PWR, BMM_REGULAR (по умолчанию), BMM_ENHANCED, BMM_HIGH.
//   sensor.setBandwidths(BMM_20Hz);                           // * Меняем частоту обновления данных на 20Гц. Возможные значения: BMM_2Hz, BMM_6Hz, BMM_8Hz, BMM_10Hz (по умолчанию), BMM_15Hz, BMM_20Hz, BMM_25Hz, BMM_30Hz.
//   Выводим подсказку по калибровке:                          // * Чем выше диапазон и частота, тем ниже точность. Предустановленные значения setScale() меняют и частоту обновления setBandwidths().
     Serial.println(F("КАЛИБРОВКА:"));                         // *
     Serial.println(F("Вращайте модуль в руках..."));          // *
     Serial.println(F("Добейтесь следующих положений:"));      // * Последовательность положений не имеет значения.
     Serial.println(F("- ось X направлена вверх, потом вниз"));// * Модуль нужно направить не только осью вверх и вниз, а немного поворачивая модуль как юла (волчок) который собирается упасть.
     Serial.println(F("- ось Y направлена вверх, потом вниз"));// * 
     Serial.println(F("- ось Z направлена вверх, потом вниз"));// * 
     Serial.println(F("Вращайте модуль в каждом положении.")); // * В процесске калибровки модуль должен зафиксировать все максимумы и минимумы магнитных полей земли по всем осям.
     Serial.println(F("Калибровка закончится через 30 сек.")); // * 
     Serial.println(F("ВАЖНО: НЕ НАЖИМАЙТЕ RESET!!!"));        // * ЕСЛИ НАЖАТЬ RESET ИЛИ ПРЕРВАТЬ ВЫПОЛНЕНИЕ КАЛИБРОВКИ, ТО ВЕЛИКА ВЕРОЯТНОСТЬ ПРЕРВАТЬ ПАКЕТ ПЕРЕДАЧИ ДАННЫХ ПО ШИНЕ I2C, ЧТО ПРИВЕДЁТ К "ЗАВИСАНИЮ" МОДУЛЯ, ТОГДА ПОТРЕБУЕТСЯ ПЕРЕПОДКЛЮЧИТЬ МОДУЛЬ К ШИНЕ I2C.
//   Выполняем калибровку:                                     //
     uint32_t i = millis();                                    //   Запоминаем время начала калибровки.
     while( (millis()-i)<30000 ){ sensor.setFastOffset(); }    //   Обращаемся к функции setFastOffset() в течении 30 секунд, пока пользователь вращает модуль.
     Serial.println(F("Калибровка завершена!"));               //
                                                               // 
//   Получаем и выводим результат калибровки:                  // *
     sensor.getFastOffset(coefficients);                       // * Получаем результат калибровки в массив coefficients. Эти данные можно указать в 25 строке этого скетча и использовать вместо калибровки.
     Serial.print(F("Калибровочные коэффициенты: "));          // *
     Serial.print(coefficients[0]); Serial.print(", ");        // *
     Serial.print(coefficients[1]); Serial.print(", ");        // *
     Serial.print(coefficients[2]); Serial.println();          // *
                                                               //
//   Если уже известны результаты калибровки:                  //
//   то вместо объявления массива coefficients[3], определяем  //
//   этот массив: float coefficients[3] = {...,...,...};       //   В этой строке указываем известные калибровочные коэффициенты.
//   а вместо выполнения калибровки, указываем значения,       //
//   для этого функцию sensor.setFastOffset() вызываем не      //
//   в цикле, а однократно: sensor.setFastOffset(coefficients) //   В этой строке указываем массив с калибровочными коэффициентами.
                                                               //
//   ВАЖНО:                                                    //
//   После изменения количества выборок setScale(), или        //
//   частоты обновления данных setBandwidths(), нужно опять    //
//   выполнить калибровку или указать калибровочные данные     //
//   соответствующие выбранным настройкам.                     //
//   Функция setFastOffset(BMM_RESET) сбрасывает результат     //
//   калибровки и указанных калибровочных коэффициентов.       //
}                                                              //
                                                               //
void loop(){                                                   // 
     sensor.read();                                            //   Функция read() читает данные того датчика, для которого был создан объект sensor.
                                                               //   Для объекта работающего с магнитометром, функция read() может принять
                                                               //   один из двух параметров: BMM_MG или BMM_MCT.
                                                               //   Если параметра нет, то используется параметр по умолчанию
                                                               //   sensor.read(BMM_MG);  читать индукцию магнитного поля в мГс. (по умолчанию).
                                                               //   sensor.read(BMM_MCT); читать индукцию магнитного поля в мкТл.
                                                               //   Данные прочитанные функцией read() сохраняются в переменных axisX, axisY, axisZ и temp.
     Serial.print((String) "X="+sensor.axisX+", ");            //   Выводим проекцию индукции магнитного поля на ось X в мГс.
     Serial.print((String) "Y="+sensor.axisY+", ");            //   Выводим проекцию индукции магнитного поля на ось Y в мГс.
     Serial.print((String) "Z="+sensor.axisZ+" мГс \r\n");     //   Выводим проекцию индукции магнитного поля на ось Z в мГс.
}