//	Акселерометр, Гироскоп и Магнитометр	//	Это три датчика, показания которых можно использовать для определения абсолютной ориентации устройства в пространстве
											//	Данные углового ускорения, угловой скорости и магнитной индукции считываются с акселерометра, гироскопа и магнитометра, и являются входными данными для фильтра Маджвика, Махони, Калмана, или др.
											//  В данном скетче используются либо фильтр Маджвика, либо фильр Махони в результате чего мы получаем кватернионы абсолютной ориентации устройства. Кватернионы преобразуются в углы Эйлера: курс, тангаж и крен.
											//
#ifndef iarduino_Position_BMX055_ALL_h		//	Функции работы со всеми датчиками модуля BMX055
#define iarduino_Position_BMX055_ALL_h		//
//		КОНСТАНТЫ 							//
#define	BMX						0			//	Константа используемая в качестве аргумента при объявлении объекта для работы со всеми датчиками
#define	NO_FILTER				0			//	Константа используемая как ответ функции getFilter() если фильтры не выбраны
#define	FILTER_MADGWICK			1			//	Константа используемая как ответ функции getFilter() при выборе фильтра Маджвика для получения кватернионов (по умолчанию)
#define	FILTER_MADGWICK_NO_BMM	2			//	Константа используемая как ответ функции getFilter() при выборе фильтра Маджвика для получения кватернионов без использования данных магнитометра
#define	FILTER_MAHONY			3			//	Константа используемая как ответ функции getFilter() при выборе фильтра Махони   для получения кватернионов
#define	BMX_DEG					4			//	Аргумент функции read() указывающий выводить данные в градусах
#define	BMX_RAD					5			//	Аргумент функции read() указывающий выводить данные в радианах
#define	BMX_M_S					6			//	Аргумент функции read() указывающий выводить данные в м/с²         истинного ускорения (не путать с кажущимся угловым ускорением акселерометра)
#define	BMX_G					7			//	Аргумент функции read() указывающий выводить данные в количестве g истинного ускорения (не путать с кажущимся угловым ускорением акселерометра)
											//	
class iarduino_Position_BMX055_FILTER{																							//	Определяем полиморфный класс										(этот класс используется только для изначального создания объекта objFilter)
	public:																														//
		virtual void	filter(float,float,float,float,float,float,float,float,float,float*,float*,float*,float*,float);		//	Объявляем функцию получения кватернионов							(аргументы: BMAx, BMAy, BMAz, BMGx, BMGy, BMGz, BMMx, BMMy, BMMz, q1, q2, q3, q4, прошедшее время)
		virtual uint8_t	getFilter(void);																						//	Объявляем функцию получения типа используемого фильтра				(аргумент: 	отсутствует)
};																																//
class iarduino_Position_BMX055_NO_FILTER: public iarduino_Position_BMX055_FILTER{												//	Определяем производный класс
	public:																														//	Определяем функции которые будут выполняться если не назначен ни один из фильтров получения кватернионов
		void	filter(float ax,float ay,float az,float gx,float gy,float gz,float mx,float my,float mz,float*q01,float*q02,float*q03,float*q04,float i){*q01=1.0f; *q02=0.0f; *q03=0.0f; *q04=0.0f;}
		uint8_t	getFilter(void){return NO_FILTER;}																				//
};																																//
																																//
#include "iarduino_Position_BMX055_Madgwick.h"																					//	Подключаем файл iarduino_Position_BMX055_Madgwick.h        - с фильтром Маджвика
#include "iarduino_Position_BMX055_Madgwick_No_Mag.h"																			//	Подключаем файл iarduino_Position_BMX055_Madgwick_No_Mag.h - с фильтром Маджвика без данных магнитометра
#include "iarduino_Position_BMX055_Mahony.h"																					//	Подключаем файл iarduino_Position_BMX055_Mahony.h          - с фильтром Махони
																																//
#include "iarduino_Position_BMX055_I2C.h"																						//	Подключаем файл iarduino_Position_BMX055_I2C.h - для работы с шиной I2C
																																//
class iarduino_Position_BMX055_ALL: public iarduino_Position_BMX055_BASE{														//
	public:																														//
	/**	Конструктор класса **/																									//
		iarduino_Position_BMX055_ALL(){																							//	Конструктор класса
			#if !(defined BMX055_DISABLE_MADGWICK)																				//	Если не объявлена константа BMX055_DISABLE_MADGWICK, то используем фильтр Маджвика
				#ifndef BMX055_DISABLE_BMM																						//	Если не объявлена константа BMX055_DISABLE_BMM, то используем данные магнитометра
					objFilter = new iarduino_Position_BMX055_FILTER_MADGWICK; 													//	Используем фильтр Маджвика с магнитометром. Присваеиваем указателю objFilter ссылку на новый объект производного класса iarduino_Position_BMX055_FILTER_MADGWICK переопределяя на него виртуальные функции полиморфного класса iarduino_Position_BMX055_FILTER
				#else																											//	Если объявлена константа BMX055_DISABLE_BMM, то данные магнитометра не используем
					objFilter = new iarduino_Position_BMX055_FILTER_MADGWICK_NO_BMM; 											//	Используем фильтр Маджвика без магнитометра. Присваеиваем указателю objFilter ссылку на новый объект производного класса iarduino_Position_BMX055_FILTER_MADGWICK_NO_BMM переопределяя на него виртуальные функции полиморфного класса iarduino_Position_BMX055_FILTER
				#endif																											//
			#elif ((defined BMX055_ENABLE_MAHONY) && !(defined BMX055_DISABLE_BMM))												//	Если объявлена константа BMX055_ENABLE_MAHONY и не объявлена константа BMX055_DISABLE_BMM, то используем фильтр Махони
					objFilter = new iarduino_Position_BMX055_FILTER_MAHONY;   													//	Используем фильтр Махони. Присваеиваем указателю objFilter ссылку на новый объект производного класса iarduino_Position_BMX055_FILTER_MAHONY переопределяя на него виртуальные функции полиморфного класса iarduino_Position_BMX055_FILTER
		//	#elif ((defined BMX055_ENABLE_НОВЫЙ_ФИЛЬТР) && !(defined BMX055_DISABLE_BMM))										//	Если Вы захотите использовать свой фильтр, то придумайте для него константу BMX055_ENABLE_НОВЫЙ_ФИЛЬТР определив её в файле memorysaver.h
		//			objFilter = new iarduino_Position_BMX055_FILTER_НОВЫЙ_ФИЛЬТР;   											//	И присвойте указателю objFilter ссылку на новый объект созданного Вами производного класса iarduino_Position_BMX055_FILTER_НОВЫЙ_ФИЛЬТР. Разумеется не забудьте подключить файл с вашим фильтром до объявления класса iarduino_Position_BMX055_ALL
			#else																												//	Если объявлена константа BMX055_DISABLE_MADGWICK и не объявлена константа BMX055_ENABLE_MAHONY, то фильтр не определён
					objFilter = new iarduino_Position_BMX055_NO_FILTER;   														//	Если фильтры не выбраны, то присваеиваем указателю objFilter ссылку на новый объект производного класса iarduino_Position_BMX055_NO_FILTER переопределяя на него виртуальные функции полиморфного класса iarduino_Position_BMX055_FILTER
			#endif																												//
		}																														//
																																//
//		Инициализация датчиков:																									//
		bool	begin(iarduino_I2C_Select* ptrI2C, bool setZero, float*ptrX,float*ptrY,float*ptrZ,float*ptrT, float*ptrQ1,float*ptrQ2,float*ptrQ3,float*ptrQ4){ // Аргументы: ptrI2C - указатель на объект работы с шиной I2C, setZero - флаг указывающий о необходимости установить текущие показания в 0, указатели на переменные выводимых данных)
					axisX  = ptrX;																								//	Присваиваем указателю axisX  адрес из указателя ptrX который ссылается на переменную axisX класса iarduino_Position_BMX055 предназначенную для вывода данных по оси X
					axisY  = ptrY;																								//	Присваиваем указателю axisY  адрес из указателя ptrY который ссылается на переменную axisY класса iarduino_Position_BMX055 предназначенную для вывода данных по оси Y
					axisZ  = ptrZ;																								//	Присваиваем указателю axisZ  адрес из указателя ptrZ который ссылается на переменную axisZ класса iarduino_Position_BMX055 предназначенную для вывода данных по оси Z
					temp   = ptrT;																								//	Присваиваем указателю temp   адрес из указателя ptrT который ссылается на переменную temp  класса iarduino_Position_BMX055 предназначенную для вывода температуры
					q1     = ptrQ1;																								//	Присваиваем указателю q1     адрес из указателя ptrQ1 который ссылается на переменную q1   класса iarduino_Position_BMX055 предназначенную для вывода кватерниона
					q2     = ptrQ2;																								//	Присваиваем указателю q2     адрес из указателя ptrQ2 который ссылается на переменную q2   класса iarduino_Position_BMX055 предназначенную для вывода кватерниона
					q3     = ptrQ3;																								//	Присваиваем указателю q3     адрес из указателя ptrQ3 который ссылается на переменную q3   класса iarduino_Position_BMX055 предназначенную для вывода кватерниона
					q4     = ptrQ4;																								//	Присваиваем указателю q4     адрес из указателя ptrQ4 который ссылается на переменную q4   класса iarduino_Position_BMX055 предназначенную для вывода кватерниона
					bool i;																										//	Объявляем переменную для хранения результатов возвращаемых функциями begin объектов датчиков
					#ifndef BMX055_DISABLE_BMA																					//	Если используется акселерометр
					i = objBMA -> begin(ptrI2C, setZero, &BMAx,&BMAy,&BMAz,&BMAt, &q0,&q0,&q0,&q0);	if(!i){return i;}			//	Вызываем функцию инициализации акселерометра, указывая объект шины I2C, флаг необходимости установки осей в 0 и ссылки на переменные в которые требуется возвращать полученные результаты
					#endif																										//
					#ifndef BMX055_DISABLE_BMG																					//	Если используется гироскоп
					i = objBMG -> begin(ptrI2C, setZero, &BMGx,&BMGy,&BMGz,&BMGt, &q0,&q0,&q0,&q0);	if(!i){return i;}			//	Вызываем функцию инициализации гироскопа,     указывая объект шины I2C, флаг необходимости установки осей в 0 и ссылки на переменные в которые требуется возвращать полученные результаты
					#endif																										//
					#ifndef BMX055_DISABLE_BMM																					//	Если используется магнитометр
					i = objBMM -> begin(ptrI2C, false  , &BMMx,&BMMy,&BMMz,&BMMt, &q0,&q0,&q0,&q0);	if(!i){return i;}			//	Вызываем функцию инициализации магнитометра,  указывая объект шины I2C, флаг setZero сброшен, далее указываем ссылки на переменные в которые требуется возвращать полученные результаты
					#endif																										//
					return true;																								//
		}																														//
																																//
//		Самотестирование датчиков:																								//
		uint8_t	test(void){																										//	Аргумент: отсутствует
					uint8_t i;																									//	Объявляем переменную для хранения результатов возвращаемых функциями test объектов датчиков
					#ifndef BMX055_DISABLE_BMA																					//	Если используется акселерометр
					i = objBMA -> test();	if(i!=0){return i;}																	//	Вызываем функцию самотестирования акселерометра, в случае ошибки возвращаем её через переменную i
					#endif																										//
					#ifndef BMX055_DISABLE_BMG																					//	Если используется гироскоп
					i = objBMG -> test();	if(i!=0){return i;}																	//	Вызываем функцию самотестирования гироскопа,     в случае ошибки возвращаем её через переменную i
					#endif																										//
					#ifndef BMX055_DISABLE_BMM																					//	Если используется магнитометр
					i = objBMM -> test();	if(i!=0){return i;}																	//	Вызываем функцию самотестирования магнитометра,  в случае ошибки возвращаем её через переменную i
					#endif																										//
					return 0;																									//
		}																														//
																																//
//		Чтение данных из датчиков:																								//
		bool	read(uint8_t thisMera){																							//	Аргумент: мера измерения читаемых данных (0 - градусы / 1 - радианы)
					bool f, result=true;																						//
					#ifndef BMX055_DISABLE_BMA																					//	Если используется акселерометр
					f = objBMA -> read(BMA_G);		/* угловое ускорение  в g (количестве ускорений свободного падения) */		//	Вызываем функцию чтения данных акселерометра, которые запишутся в переменные BMAx, BMAy, BMAz, BMAt. Если данные не будут прочтены, то в переменных останутся предыдущие значения
					if( !f ){ result=false; }																					//
					#endif																										//
					#ifndef BMX055_DISABLE_BMG																					//	Если используется гироскоп
					f = objBMG -> read(BMG_RAD_S);	/* угловая скорость   в радианах на секунду	*/								//	Вызываем функцию чтения данных гироскопа,     которые запишутся в переменные BMGx, BMGy, BMGz, BMGt. Если данные не будут прочтены, то в переменных останутся предыдущие значения
					if( !f ){ result=false; }																					//
					#endif																										//
					#ifndef BMX055_DISABLE_BMM																					//	Если используется магнитометр
					f = objBMM -> read(BMM_MG);		/* магнитная индукция в миллигаусах			*/								//	Вызываем функцию чтения данных магнитометра,  которые запишутся в переменные BMMx, BMMy, BMMz, BMMt. Если данные не будут прочтены, то в переменных останутся предыдущие значения
					if( !f ){ result=false; }																					//
					#endif																										//
					thisUpdate=micros(); timeUpdate=((thisUpdate-lastUpdate)/1000000.0f); lastUpdate=thisUpdate;				//	Опеределяем время прошедшее после последнего получения кватернионов
					objFilter->filter(BMAx,BMAy,BMAz,BMGx,BMGy,BMGz,BMMx,BMMy,BMMz,q1,q2,q3,q4,timeUpdate);						//	Вызываем функцию чтения кватернионов,         которые запишутся в переменные q1, q2, q3, q4.
					float j = 1;																								//	Определяем множитель
					switch(thisMera){																							//	В зависимости от установленной меры измерений
						default:	thisMera=BMX_DEG;																			//	По умолчанию значения углов Эйлера возвращаются в градусах
						case		BMX_DEG:	j=180.0f/PI;	break;															//	Если данные требуется возвращать в градусах
						case		BMX_RAD:	j=1.0f;			break;															//	Если данные требуется возвращать в радианах
						case		BMX_M_S:	j=9.81f;		break;															//	Если данные требуется возвращать в м/с²         истинного ускорения, то сначала нужно получить углы Эйлера в радианах.
						case		BMX_G:		j=1.0f;			break;															//	Если данные требуется возвращать в количестве g истинного ускорения, то сначала нужно получить углы Эйлера в радианах.
					}																											//
					*axisX = float(-asin(2.0f*((*q1)*(*q3)-(*q2)*(*q4))                                                )) * j;	//	Получаем ТАНГАЖ            (pitch) угол наклона  вверх или вниз
					*axisY = float(atan2(2.0f*((*q1)*(*q2)+(*q3)*(*q4)),(*q1)*(*q1)-(*q2)*(*q2)-(*q3)*(*q3)+(*q4)*(*q4))) * j;	//	Получаем КРЕН              (roll)  угол наклона  влево или вправо
					*axisZ = float(atan2(2.0f*((*q2)*(*q3)+(*q1)*(*q4)),(*q1)*(*q1)+(*q2)*(*q2)-(*q3)*(*q3)-(*q4)*(*q4))) * j;	//	Получаем КУРС или РЫСКАНИЕ (yaw)   угол поворота влево или вправо
					*temp  = BMAt;																								//	Получаем ТЕМПЕРАТУРУ с акселерометра (можно получить и с магнитометра BMMt)
				//	Если требуется получить истинное ускорение:																	//
					if( thisMera==BMX_M_S || thisMera==BMX_G ){																	//	Истинное ускорение = вектор кажущегося ускорения акселерометра - вектор ускорения свободного падения (g)
						float angleX=PI/2.0f+(*axisX);																			//	Вычисляем угол angleX между осью axisX и вектором g, зная что вектор g всегда направлен вниз
						float angleY=PI/2.0f-(*axisY);																			//	Вычисляем угол angleY между осью axisY и проекцией вектора g на плоскость определённую осями axisY и axisZ
						float gX = cos(angleX);             *axisX = (BMAx-gX)*j;												//	Вычисляем gX - проекцию вектора g на ось axisX. После чего определяем разность между (проекциями векторов на ось axisX) кажущегося ускорения (BMAx) и ускорения свободного падения (gX). Для BMX_M_S переводим g в м/с², умножая результат на 9.81 м/с²
						float gY = sin(angleX)*cos(angleY); *axisY = (BMAy-gY)*j;												//	Вычисляем gY - проекцию вектора g на ось axisY. После чего определяем разность между (проекциями векторов на ось axisY) кажущегося ускорения (BMAy) и ускорения свободного падения (gX). Для BMX_M_S переводим g в м/с², умножая результат на 9.81 м/с²
						float gZ = sin(angleX)*sin(angleY); *axisZ = (BMAz-gZ)*j;												//	Вычисляем gZ - проекцию вектора g на ось axisZ. После чего определяем разность между (проекциями векторов на ось axisZ) кажущегося ускорения (BMAz) и ускорения свободного падения (gX). Для BMX_M_S переводим g в м/с², умножая результат на 9.81 м/с²
					}																											//	
					return result;																								//
		}																														//
																																//
//		Установка диапазона измерений:																							//
		void	setScale(uint8_t scale){																						//	Аргумент: предел диапазона измеряемерений.
					switch (scale){																								//	Проверяем значение аргумента функции
					#ifndef BMX055_DISABLE_BMA																					//	Если используется акселерометр
						case BMA_2G:																							//
						case BMA_4G:																							//
						case BMA_8G:																							//
						case BMA_16G:		objBMA -> setScale(scale); break;													//	Вызываем функцию установки диапазона измерений акселерометра.
					#endif																										//
					#ifndef BMX055_DISABLE_BMG																					//	Если используется гироскоп
						case BMG_125DPS:																						//
						case BMG_250DPS:																						//
						case BMG_500DPS:																						//
						case BMG_1000DPS:																						//
						case BMG_2000DPS:	objBMG -> setScale(scale); break;													//	Вызываем функцию установки диапазона измерений гироскопа.
					#endif																										//
					#ifndef BMX055_DISABLE_BMM																					//	Если используется магнитометр
						case BMM_LOW_PWR:																						//
						case BMM_REGULAR:																						//
						case BMM_ENHANCED:																						//
						case BMM_HIGH:		objBMM -> setScale(scale); break;													//	Вызываем функцию установки презустановленных значений магнитометра.
					#endif																										//
					}																											//
		}																														//
																																//
//		Установка полосы пропускания для фильтрованных данных:																	//
		void	setBandwidths(uint8_t bandwidths){																				//	Аргумент: скорость обновления данных.
					switch (bandwidths){																						//	Проверяем значение аргумента функции
					#ifndef BMX055_DISABLE_BMA																					//	Если используется акселерометр
						case BMA_16Hz:																							//
						case BMA_8Hz:																							//
						case BMA_31Hz:																							//
						case BMA_63Hz:																							//
						case BMA_125Hz:																							//
						case BMA_250Hz:																							//
						case BMA_500Hz:																							//
						case BMA_1000Hz:	objBMA -> setBandwidths(bandwidths); break;											//	Вызываем функцию установки полосы пропускания акселерометра.
					#endif																										//
					#ifndef BMX055_DISABLE_BMG																					//	Если используется гироскоп
						case BMG_23Hz:																							//
						case BMG_12Hz:																							//
						case BMG_32Hz:																							//
						case BMG_47Hz:																							//
						case BMG_64Hz:																							//
						case BMG_116Hz:																							//
						case BMG_230Hz:																							//
						case BMG_523Hz:		objBMG -> setBandwidths(bandwidths); break;											//	Вызываем функцию установки полосы пропускания гироскопа.
					#endif																										//
					#ifndef BMX055_DISABLE_BMM																					//	Если используется магнитометр
						case BMM_10Hz:																							//
						case BMM_2Hz:																							//
						case BMM_6Hz:																							//
						case BMM_8Hz:																							//
						case BMM_15Hz:																							//
						case BMM_20Hz:																							//
						case BMM_25Hz:																							//
						case BMM_30Hz:		objBMM -> setBandwidths(bandwidths); break;											//	Вызываем функцию установки полосы пропускания магнитометра.
					#endif																										//
					}																											//
		}																														//
																																//
//		Выполнение быстрой компенсации смещения данных:																			//
		void	setFastOffset(uint8_t offset){																					//	Аргумент: указывает какой датчик трубуется откалибровать (BMA/BMG/BMM/BMM_RESET).
					#ifndef BMX055_DISABLE_BMA																					//	Если используется акселерометр
					if( offset==BMA                      ){ objBMA -> setFastOffset(offset); }									//	Вызываем функцию быстрой компенсации смещения данных акселерометра
					#endif																										//
					#ifndef BMX055_DISABLE_BMG																					//	Если используется гироскоп
					if( offset==BMG                      ){ objBMG -> setFastOffset(offset); }									//	Вызываем функцию быстрой компенсации смещения данных гироскопа
					#endif																										//
					#ifndef BMX055_DISABLE_BMM																					//	Если используется магнитометр
					if( offset==BMM || offset==BMM_RESET ){ objBMM -> setFastOffset(offset); }									//	Вызываем функцию быстрой компенсации смещения данных магнитометра
					#endif																										//
		}																														//
																																//
//		Установка массива компенсации смещения данных магнитометра:																//
		void	setFastOffset(float* offset){																					//	Аргумент: массив с известными данными калибровки магнитометра.
					#ifndef BMX055_DISABLE_BMM																					//	Если используется магнитометр
						objBMM -> setFastOffset(offset);																		//	Перенаправляем вызов функции магнитометру.
					#endif																										//
		}																														//
																																//
//		Получение массива компенсации смещения данных магнитометра:																//
		void	getFastOffset(float* offset){																					//	Аргумент: массив для получения данных результата калибровки магнитометра.
					#ifndef BMX055_DISABLE_BMM																					//	Если используется магнитометр
						objBMM -> getFastOffset(offset);																		//	Перенаправляем вызов функции магнитометру.
					#endif																										//
		}																														//
																																//
//		Запрос используемого фильтра:																							//
		uint8_t	getFilter(void){																								//	Аргумент: отсутствует
					return objFilter->getFilter();																				//	Вызываем функцию возвращающую тип используемого фильтра
		}																														//
																																//
	private:																													//
	/**	Внутренние переменные **/																								//
		float	*	axisX;																										//	Объявляем указатель который будет ссылаться на переменную для вывода данных по оси X
		float	*	axisY;																										//	Объявляем указатель который будет ссылаться на переменную для вывода данных по оси Y
		float	*	axisZ;																										//	Объявляем указатель который будет ссылаться на переменную для вывода данных по оси Z
		float	*	temp;																										//	Объявляем указатель который будет ссылаться на переменную для вывода температуры
		float	*	q1;																											//	Объявляем указатель который будет ссылаться на переменную для вывода кватерниона
		float	*	q2;																											//	Объявляем указатель который будет ссылаться на переменную для вывода кватерниона
		float	*	q3;																											//	Объявляем указатель который будет ссылаться на переменную для вывода кватерниона
		float	*	q4;																											//	Объявляем указатель который будет ссылаться на переменную для вывода кватерниона
		float		q0;																											//	Объявляем переменную для передачи её данных в неиспользуемые агументы
		float		BMAx, BMAy, BMAz, BMAt;																						//	Объявляем переменные для хранения данных акселерометра
		float		BMGx, BMGy, BMGz, BMGt;																						//	Объявляем переменные для хранения данных гироскопа
		float		BMMx, BMMy, BMMz, BMMt;																						//	Объявляем переменные для хранения данных магнитометра
		uint32_t	thisUpdate, lastUpdate = 0;																					//  Объявляем переменные для хранения времени (мкс) текущего и предыдущего получения кватернионов
		float		timeUpdate;																									//	Объявляем переменную для хранения времени (сек) прошедшего после последнего получения кватернионов
																																//
		#ifndef BMX055_DISABLE_BMA																								//	Если используется акселерометр
		iarduino_Position_BMX055_BASE*	 objBMA = new iarduino_Position_BMX055_BMA;												//	Определяем указатель objBMA присвоив ему адрес нового объекта производного класса iarduino_Position_BMX055_BMA переопределяя на него все виртуальные функции полиморфного класса iarduino_Position_BMX055_BASE
		#endif																													//
		#ifndef BMX055_DISABLE_BMG																								//	Если используется гироскоп
		iarduino_Position_BMX055_BASE*	 objBMG = new iarduino_Position_BMX055_BMG;												//	Определяем указатель objBMG присвоив ему адрес нового объекта производного класса iarduino_Position_BMX055_BMG переопределяя на него все виртуальные функции полиморфного класса iarduino_Position_BMX055_BASE
		#endif																													//
		#ifndef BMX055_DISABLE_BMM																								//	Если используется магнитометр
		iarduino_Position_BMX055_BASE*	 objBMM = new iarduino_Position_BMX055_BMM;												//	Определяем указатель objBMM присвоив ему адрес нового объекта производного класса iarduino_Position_BMX055_BMM переопределяя на него все виртуальные функции полиморфного класса iarduino_Position_BMX055_BASE
		#endif																													//
		iarduino_Position_BMX055_FILTER* objFilter;																				//	Объявляем указатель на объект полиморфного класса iarduino_Position_BMX055_FILTER (функции данного класса будут переопределены, т.к. указателю будет присвоена ссылка на производный класс)
};																																//
																																//
#endif																															//