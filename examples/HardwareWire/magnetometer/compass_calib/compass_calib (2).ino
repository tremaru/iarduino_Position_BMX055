// ПРИМЕР РАБОТЫ С МАГНИТОМЕТРА В КАЧЕСТВЕ КОМПАСА:         // МАГНИТОМЕТР: измеряет магнитную индукцию, он определяет положение устройства в пространстве отностиельно магнитных полюсов земли.
// с предварительной калибровкой датчика                    // Значения оси направленной в сторону северного полюса будут положительными, а значения оси направленной в сторону южного полюса будут отрицательны.
                                                            // На экваторе магнитные линии параллельны земле (0°), но ближе к полюсам их угол относительно земли приближается к 90° и они становятся перпендикулярны земле.
                                                            // Так что не удивляйтесь если максимальные показания осей будут направлены вниз или верх от земли, это не помешает использовать показания остальных осей как компас.
                                                            // Показания магнитометра сильно меняются от любых намагниченных предметов, по этому его нужно калибровать или указывать полученные ранее калибровочные коэффициенты.
// ССЫЛКИ для ознакомления:                                 //   
// IMU-сенсор на 9 степеней свободы (Trema-модуль V2.0):    // https://iarduino.ru/shop/Sensory-Datchiki/imu-9.html
// Информация о подключении модулей к шине I2C:             // https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:               // https://wiki.iarduino.ru/page/Trema_IMU9/
                                                            // 
#define BMX055_DISABLE_BMA                                  // Не использовать акселерометр (данную строку можно и не писать, но её наличие освобождает память программ за счет неиспользуемого датчика).
#define BMX055_DISABLE_BMG                                  // Не использовать гироскоп     (данную строку можно и не писать, но её наличие освобождает память программ за счет неиспользуемого датчика).
                                                            //
#include <Wire.h>                                           // Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_Position_BMX055.
#include <iarduino_Position_BMX055.h>                       // Подключаем библиотеку для работы с Trema-модулем IMU 9 DOF.
iarduino_Position_BMX055 sensor(BMM);                       // Создаём объект sensor указывая что ему требуется работать только с магнитометром.
                                                            // Если указать параметр BMA - то объект будет работать только с акселерометром.
                                                            // Если указать параметр BMG - то объект будет работать только с гироскопом.
                                                            // Если указать параметр BMM - то объект будет работать только с магнитометром.
                                                            // Если указать параметр BMX - то объект будет работать со всеми датчиками сразу.
                                                            // 
//   Если требуется выполнить калибровку:                   //
     float coefficients[3];                                 // В этот массив будут записаны результаты калибровки. Эти данные можно сохранить и использовать вместо калибровки.
                                                            // 
//   Если уже известны результаты калибровки:               //
//   float coefficients[3] = {-122.5f, 63.75f, -105.63f};   // Определяем массив данных полученных функцией getFastOffset() после калибровки (строка 48 данного скетча).
                                                            // У вас будут другие значения! Значения зависят от модуля и установленных рядом с ним металлических и магнитных предметов.
void setup(){                                               // 
     Serial.begin(9600);                                    // Инициируем передачу данных в монитор последовательного порта на скорости 9600 бит/сек.
     while(!Serial){}                                       // Ждём готовность Serial к передаче данных в монитор последовательного порта.
     sensor.begin(&Wire); // &Wire1, &Wire2 ...             // Инициируем работу с магнитометром, так как именно для работы с ним создан объект sensor. Указав ссылку на объект для работы с шиной I2C на которой находится модуль (по умолчанию &Wire).
//   sensor.setScale(BMM_ENHANCED);                         // Меняем количество выборок на предустановленное значение BMM_ENHANCED. Возможные значения: BMM_LOW_PWR, BMM_REGULAR (по умолчанию), BMM_ENHANCED, BMM_HIGH.
//   sensor.setBandwidths(BMM_20Hz);                        // Меняем частоту обновления данных на 20Гц. Возможные значения: BMM_2Hz, BMM_6Hz, BMM_8Hz, BMM_10Hz (по умолчанию), BMM_15Hz, BMM_20Hz, BMM_25Hz, BMM_30Hz.
//   Выводим подсказку по калибровке:                       // Чем выше диапазон и частота, тем ниже точность. Предустановленные значения setScale() меняют и частоту обновления setBandwidths().
     Serial.println("КАЛИБРОВКА:");                         //
     Serial.println("Вращайте модуль в руках...");          //
     Serial.println("Добейтесь следующих положений:");      // Последовательность положений не имеет значения.
     Serial.println("- ось X направлена вверх, потом вниз");// Модуль нужно направить не только осью вверх и вниз, а немного поворачивая модуль как юла (волчок) который собирается упасть.
     Serial.println("- ось Y направлена вверх, потом вниз");// 
     Serial.println("- ось Z направлена вверх, потом вниз");// 
     Serial.println("Вращайте модуль в каждом положении."); // В процесске калибровки модуль должен зафиксировать все максимумы и минимумы магнитных полей земли по всем осям.
     Serial.println("Калибровка закончится через 30 сек."); // 
//   Выполняем калибровку:                                  //
     uint32_t i = millis();                                 // Запоминаем время начала калибровки.
     while( (millis()-i)<30000 ){ sensor.setFastOffset(); } // Обращаемся к функции setFastOffset() в течении 30 секунд, пока пользователь вращает модуль.
     Serial.println("Калибровка завершена!");               //
                                                            // 
//   Получаем и выводим результат калибровки:               //
     sensor.getFastOffset(coefficients);                    // Получаем результат калибровки в массив coefficients. Эти данные можно указать в 25 строке этого скетча и использовать вместо калибровки.
     Serial.print("Калибровочные коэффициенты: ");          //
     Serial.print(coefficients[0]); Serial.print(", ");     //
     Serial.print(coefficients[1]); Serial.print(", ");     //
     Serial.print(coefficients[2]); Serial.println();       //
                                                            //
//   Если уже известны результаты калибровки:               //
//   то комментируем строку: float coefficients[3];         //
//   разкомментируем строку: float coefficients[3]={...};   // В этой строке нужно указать калибровочные коэффициенты.
//   А в коде setup() вместо выполнения калибровки указываем//
//   sensor.setFastOffset(coefficients);                    // Указываем массив с калибровочными коэффициентами вместо выполнения калибровки.
                                                            //
//   ВАЖНО:                                                 //
//   После изменения количества выборок setScale(), или     //
//   частоты обновления данных setBandwidths(), нужно опять //
//   выполнить калибровку или указать калибровочные данные  //
//   соответствующие выбранным настройкам.                  //
//   Функция setFastOffset(BMM_RESET) сбрасывает результат  //
//   калибровки и указанных калибровочных коэффициентов.    //
}                                                           //
                                                            //
void loop(){                                                // 
     sensor.read();                                         // Функция read() читает данные того датчика, для которого был создан объект sensor.
                                                            // Для объекта работающего с магнитометром, функция read() может принять
                                                            // один из двух параметров: BMM_MG или BMM_MCT.
                                                            // Если параметра нет, то используется параметр по умолчанию
                                                            // sensor.read(BMM_MG);  читать индукцию магнитного поля в мГс. (по умолчанию).
                                                            // sensor.read(BMM_MCT); читать индукцию магнитного поля в мкТл.
                                                            // Данные прочитанные функцией read() сохраняются в переменных axisX, axisY, axisZ и temp.
//   Получаем угол отклонения оси Y от северного полюса:    //
     int north = atan2(sensor.axisY,sensor.axisX)*180/PI;   // Поменяв местами параметры axisX и axisY, и умножив результат на -1, получим отклонение оси X от северного полюса.
     Serial.println((String) "Угол: "+north+"°" );          // 0° Север, 90° Запад, -90° Восток, ±180° Юг.
//   Компас будет работать при горизонтальном положении     //
//   осей X и Y модуля.                                     //
}                                                           //