// ПРИМЕР ОПРЕДЕЛЕНИЯ ПОЛОЖЕНИЯ МОДУЛЯ:                        // * Строки со звёздочкой являются необязательными.
// Перед определением положения модуля рекомендуется           //   АКСЕЛЕРОМЕТР: измеряет кажущееся угловое ускорение, которое является геометрической разницей между истинным угловым ускорением и ускорением силы гравитации (g).
// выполнить калибровку см. пример: all/angle_calib            //   Если акселерометр неподвижен (истинное ускорение отсутствует), его оси XY параллельны земле, а ось Z направлена вверх, то ...
                                                               //   проекция кажущегося ускорения на ось Z = 0 - -g = g. Где 0 это истинное ускорение, а -g сила гравитации направленная в сторону противоположную оси Z.
                                                               //   Так как вектор g всегда направлен к земле, то в неподвижном состоянии, по данным датчика можно определить угол наклона устройства относительно поверхности Земли.
                                                               //   Эти данные можно использовать, например, для поворота изображения на экране (альбомное / ландшафтное).
                                                               //
                                                               //   ГИРОСКОП: измеряет угловую скорость вокруг собственных осей, он определяет воздействие момента внешней силы.
                                                               //   Эти данные можно использовать, например, для включения режима фиксации жесткого диска в случае падения, удара или резкого перемещения ноутбука.
                                                               //
                                                               //   МАГНИТОМЕТР: измеряет магнитную индукцию, он определяет положение устройства в пространстве отностиельно магнитных полюсов земли.
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
// #define BMX055_DISABLE_BMM                                  // * Не использовать магнитометр. Курс будет ориентирован на начальное положение модуля, а не на магнитные полюса земли (работает только с фильтром Маджвика).
// #define BMX055_DISABLE_MADGWICK                             // * Не использовать код фильтра Маджвика (этот фильтр используется по умолчанию).
// #define BMX055_ENABLE_MAHONY                                // * Использовать код фильтра Махони (обязательно, если отключён фильтр Маджвика).
                                                               //
#include <iarduino_I2C_Software.h>                             //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки iarduino_Position_BMX055.
SoftTwoWire sWire(3,4);                                        //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                               //
#include <iarduino_Position_BMX055.h>                          //   Подключаем библиотеку iarduino_Position_BMX055 для работы с Trema-модулем IMU 9 DOF.
iarduino_Position_BMX055 sensor(BMX);                          //   Создаём объект sensor указывая что требуется работать со всеми датчиками модуля.
                                                               //   Если указать параметр BMA - то объект будет работать только с акселерометром.
                                                               //   Если указать параметр BMG - то объект будет работать только с гироскопом.
                                                               //   Если указать параметр BMM - то объект будет работать только с магнитометром.
                                                               //   Если указать параметр BMX - то объект будет работать со всеми датчиками сразу.
void setup(){                                                  // 
     Serial.begin(9600);                                       //   Инициируем передачу данных в монитор последовательного порта на скорости 9600 бит/сек.
     while(!Serial){}                                          // * Ждём готовность Serial к передаче данных в монитор последовательного порта.
     sensor.begin(&sWire);                                     //   Инициируем работу со всеми датчиками модуля, так как именно для работы с ними создан объект sensor. Указав ссылку на объект для работы с шиной I2C на которой находится модуль (по умолчанию &Wire).
//   sensor.setScale(BMA_4G);                                  // * Меняем диапазон измерений акселерометра до ±4G.          Возможные значения: BMA_2G (по умолчанию), BMA_4G, BMA_8G, BMA_16G.
//   sensor.setScale(BMG_500DPS);                              // * Меняем диапазон измерений гироскопа до ±500°/с.          Возможные значения: BMG_125DPS (по умолчанию), BMG_250DPS, BMG_500DPS, BMG_1000DPS, BMG_2000DPS.
//   sensor.setScale(BMM_ENHANCED);                            // * Меняем количество выборок магнитометра на BMM_ENHANCED.  Возможные значения: BMM_LOW_PWR, BMM_REGULAR (по умолчанию), BMM_ENHANCED, BMM_HIGH.
//   sensor.setBandwidths(BMA_125Hz);                          // * Меняем частоту обновления данных акселерометра на 125Гц. Возможные значения: BMA_8Hz, BMA_16Hz (по умолчанию), BMA_31Hz, BMA_63Hz, BMA_125Hz, BMA_250Hz, BMA_500Hz, BMA_1000Hz.
//   sensor.setBandwidths(BMG_64Hz);                           // * Меняем частоту обновления данных гироскопа     на 64Гц.  Возможные значения: BMG_12Hz, BMG_23Hz (по умолчанию), BMG_32Hz, BMG_47Hz, BMG_64Hz, BMG_116Hz, BMG_230Hz, BMG_523Hz.
//   sensor.setBandwidths(BMM_20Hz);                           // * Меняем частоту обновления данных магнитометра  на 20Гц.  Возможные значения: BMM_2Hz, BMM_6Hz, BMM_8Hz, BMM_10Hz (по умолчанию), BMM_15Hz, BMM_20Hz, BMM_25Hz, BMM_30Hz.
//   sensor.setFastOffset(BMA);                                // * Выполняем калибровку акселерометра после установки нового диапазона измерений или частоты обновления данных.
//   sensor.setFastOffset(BMG);                                // * Выполняем калибровку гироскопа после установки нового диапазона измерений или частоты обновления данных.
//   while(не_истекло_время){sensor.setFastOffset(BMM);}       // * Выполняем калибровку магнитометра после установки нового диапазона измерений или частоты обновления данных в течении указанного времени модуль должен вращаться (см. пример: angle_calib).
}                                                              //
                                                               //
void loop(){                                                   //
     sensor.read();                                            //   Функция read() читает данные того датчика, для которого был создан объект sensor.
                                                               //   В этом скетче объект sensor создан для работы со всеми датчиками модуля (BMX).
                                                               //   В этом случае функция read() может принять один из следующих параметров:
                                                               //   sensor.read(BMX_DEG  ); читать углы Эйлера в градусах со всех датчиков (по умолчанию).
                                                               //   sensor.read(BMX_RAD  ); читать углы Эйлера в радианах со всех датчиков.
                                                               //   sensor.read(BMX_M_S  ); читать истинное ускорение со всех датчиков в м/с².
                                                               //   sensor.read(BMX_G    ); читать истинное ускорение со всех датчиков в количестве g.
                                                               //   sensor.read(BMA_M_S  ); читать угловое ускорение с акселерометра в м/с².
                                                               //   sensor.read(BMA_G    ); читать угловое ускорение с акселерометра в g.
                                                               //   sensor.read(BMA_DEG  ); читать углы «крен» и «тангаж» с акселерометра в градусах.
                                                               //   sensor.read(BMA_RAD  ); читать углы «крен» и «тангаж» с акселерометра в радианах.
                                                               //   sensor.read(BMG_DEG_S); читать угловую скорость с гироскопа в °/c.
                                                               //   sensor.read(BMG_RAD_S); читать угловую скорость с гироскопа в рад/c.
                                                               //   sensor.read(BMM_MG   ); читать индукцию магнитного поля с магнитометра в мГс.
                                                               //   sensor.read(BMM_MCT  ); читать индукцию магнитного поля с магнитометра в мкТл.
                                                               //   Данные прочитанные функцией read() сохраняются в переменных axisX, axisY, axisZ и temp.
     Serial.print((String) "КУРС="  +sensor.axisZ+", ");       //   КУРС   - угол поворота вдоль оси Z самолёт меняет направление полёта (0: север, +90: запад, -90: восток, ±180: юг).
     Serial.print((String) "ТАНГАЖ="+sensor.axisX+", ");       //   ТАНГАЖ - угол наклона оси X (нос самолёта) относительно горизонта (0: горизонтально, +90: нос вверх, -90: нос вниз).
     Serial.print((String) "КРЕН="  +sensor.axisY+"\r\n");     //   КРЕН   - угол наклона оси Y (крылья самолёта) относительно горизонта (0:горизонтально, +90:левое вверх, -90:левое вниз, ±180: бочка).
//   ПРИМЕЧАНИЕ:                                               //
//   Углы Эйлера удобно представлять на примере самолёта.      //
//   Ось X проходит вдоль фюзеляжа от хвоста к носу.           //
//   Ось Y проходит от правого крыла к левому.                 //
//   Ось Z проходит через центр самолёта снизу вверх.          //
//   КРЕН   поворот самолёта вдоль оси X (наклон крыльев).     //   Для удобства в библиотеке под углом КРЕН   подразумевается наклон оси Y относительно горизонта (наклон крыльев). Крен берётся из переменной axisY.
//   ТАНГАЖ поворот самолёта вдоль оси Y (нос вверх/вниз).     //   Для удобства в библиотеке под углом ТАНГАЖ подразумевается наклон оси X относительно горизонта (нос вверх/вниз). Тангаж берётся из переменной axisX.
//   КУРС   поворот самолёта вдоль оси Z (направление).        //   Курс берётся из переменной axisZ.
}
