//	Библиотека для работы с Trema модулем IMU 9 DOF на базе чипа BMX055. http://iarduino.ru/shop/Expansion-payments/imu-sensor-na-9-stepeney-svobody-trema-modul-v2-0.html
//  Версия: 1.0.1
//  Последнюю версию библиотеки Вы можете скачать по ссылке: http://iarduino.ru/file/337.html
//  Подробное описание функции бибилиотеки доступно по ссылке: http://wiki.iarduino.ru/page/Trema_IMU9/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел sajaem@narod.ru
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_Position_BMX055_h
#define iarduino_Position_BMX055_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <memorysaver.h>																														//	Подключаем файл «хранитель памяти»									(внутри файла есть комментарий поясняющий как сэкономить мапять)

class iarduino_Position_BMX055_BASE{																											//	Определяем полиморфный класс										(этот класс используется только для изначального создания объекта objClass)
	public:
		virtual bool	begin			(bool,float*,float*,float*,float*,float*,float*,float*,float*);											//	Объявляем функцию инициализации датчика(ов) модуля					(аргументы: флаг указывающий о необходимости установить текущие показания датчика в 0, указатели на переменные выводимых данных)
		virtual uint8_t	test			(void);																									//	Объявляем функцию тестирования  датчика(ов) модуля					(аргумент: 	отсутствует)
		virtual bool	read			(uint8_t);																								//	Объявляем функцию чтения данных датчика(ов) модуля					(аргумент: 	мера измерения читаемых данных)
		virtual void	setScale		(uint8_t);																								//	Объявляем функцию установки диапазона измерений						(аргумент: 	диапазон измерений)
		virtual void	setBandwidths	(uint8_t);																								//	Объявляем функцию установки полосы пропускания для фильтр. данных	(аргумент: 	полоса пропускания для фильтрованных данных)
		virtual void	setFastOffset	(void);																									//	Объявляем функцию выполнения быстрой компенсации смещения данных	(аргумент: 	отсутствует)
		virtual uint8_t	getFilter		(void);																									//	Объявляем функцию возвращающую тип используемого фильтра			(аргумент: 	отсутствует)
};

#include <iarduino_Position_BMX055_I2C.h>																										//	Подключаем файл iarduino_Position_BMX055_I2C.h - для работы с шиной I2C        (используя функции структуры iI2C)
#include <iarduino_Position_BMX055_BMA.h>																										//	Подключаем файл iarduino_Position_BMX055_BMA.h - для работы с акселерометром   (датчиком BMA модуля BMX055)
#include <iarduino_Position_BMX055_BMG.h>																										//	Подключаем файл iarduino_Position_BMX055_BMG.h - для работы с гироскопом       (датчиком BMG модуля BMX055)
#include <iarduino_Position_BMX055_BMM.h>																										//	Подключаем файл iarduino_Position_BMX055_BMM.h - для работы с магнитометром    (датчиком BMM модуля BMX055)
#include <iarduino_Position_BMX055_ALL.h>																										//	Подключаем файл iarduino_Position_BMX055_ALL.h - для работы со всеми датчиками (BMA, BMG, BMM модуля BMX055)

class iarduino_Position_BMX055{
	public:
	/**	Конструктор класса **/
		iarduino_Position_BMX055(uint8_t sensor = 0){																							//	Конструктор основного класса										(аргументы: sensor - название используемого(ых) датчика(ов) модуля. BMA-акселерометр, BMG-гироскоп, BMM-магнитометр, или все датчики сразу)
			switch(sensor){																														//	Тип выбранного модуля
				#ifndef BMX055_DISABLE_BMA																										//	Если не объявлена константа BMX055_DISABLE_BMA, то используем данные акселерометра
				case BMA:	objClass = new iarduino_Position_BMX055_BMA; break;																	//	Если используется только акселерометр, то присваеиваем указателю objClass ссылку на новый объект производного класса iarduino_Position_BMX055_BMA переопределяя на него все виртуальные функции полиморфного класса iarduino_Position_BMX055_BASE
				#endif																															//
				#ifndef BMX055_DISABLE_BMG																										//	Если не объявлена константа BMX055_DISABLE_BMG, то используем данные гироскопа
				case BMG:	objClass = new iarduino_Position_BMX055_BMG; break;																	//	Если используется только гироскоп,     то присваеиваем указателю objClass ссылку на новый объект производного класса iarduino_Position_BMX055_BMG переопределяя на него все виртуальные функции полиморфного класса iarduino_Position_BMX055_BASE
				#endif																															//
				#ifndef BMX055_DISABLE_BMM																										//	Если не объявлена константа BMX055_DISABLE_BMM, то используем данные магнитометра
				case BMM:	objClass = new iarduino_Position_BMX055_BMM; break;																	//	Если используется только магнитометр,  то присваеиваем указателю objClass ссылку на новый объект производного класса iarduino_Position_BMX055_BMM переопределяя на него все виртуальные функции полиморфного класса iarduino_Position_BMX055_BASE
				#endif																															//
				#ifndef BMX055_DISABLE_BMA																										//	Если не объявлена константа BMX055_DISABLE_BMA, то используем данные акселерометра
				#ifndef BMX055_DISABLE_BMG																										//	Если не объявлена константа BMX055_DISABLE_BMG, то используем данные гироскопа
				default:	objClass = new iarduino_Position_BMX055_ALL; break;																	//	Если используются все датчики модуля,  то присваеиваем указателю objClass ссылку на новый объект производного класса iarduino_Position_BMX055_ALL переопределяя на него все виртуальные функции полиморфного класса iarduino_Position_BMX055_BASE
				#endif																															//
				#endif																															//
			}																																	//
		}																																		//
	/**	Пользовательские функции **/
		bool	begin			(bool setZero = false)	{return	objClass -> begin			(setZero, &axisX,&axisY,&axisZ,&temp, &q1,&q2,&q3,&q4);	}	//	Определяем функцию инициализации датчика(ов) модуля					(аргумент: setZero - флаг указывающий о необходимости установить текущие показания датчика в 0)
		uint8_t	test			(void)					{return	objClass -> test			();														}	//	Определяем функцию тестирования  датчика(ов) модуля					(аргумент: отсутствует)
		bool	read			(uint8_t thisMera = 0)	{return	objClass -> read			(thisMera);												}	//	Определяем функцию чтения данных датчика(ов) модуля					(аргумент: thisMera - мера измерения читаемых данных)
		void	setScale		(uint8_t scale)			{		objClass -> setScale		(scale);												}	//	Определяем функцию установки диапазона измерений					(аргумент: scale - диапазон измерений)
		void	setBandwidths	(uint8_t bandwidths)	{		objClass -> setBandwidths	(bandwidths);											}	//	Определяем функцию установки полосы пропускания для фильтр. данных	(аргумент: bandwidths - полоса пропускания для фильтрованных данных)
		void	setFastOffset	(void)					{return	objClass -> setFastOffset	();														}	//	Определяем функцию выполнения быстрой компенсации смещения данных	(аргумент: 	отсутствует)
		uint8_t	getFilter		(void)					{return	objClass -> getFilter		();														}	//	Определяем функцию возвращающую тип используемого фильтра			(аргумент: 	отсутствует)
	/**	Пользовательские переменные **/
		float	axisX =			0;																										//	Определяем переменную для вывода данных по оси X
		float	axisY =			0;																										//	Определяем переменную для вывода данных по оси Y
		float	axisZ =			0;																										//	Определяем переменную для вывода данных по оси Z
		float	temp  =			0;																										//	Определяем переменную для вывода температуры
		float	q1    =			1.0f;																									//	Определяем переменную для вывода кватерниона
		float	q2    =			0.0f;																									//	Определяем переменную для вывода кватерниона
		float	q3    =			0.0f;																									//	Определяем переменную для вывода кватерниона
		float	q4    =			0.0f;																									//	Определяем переменную для вывода кватерниона

	private:
	/**	Внутренние переменные **/
		iarduino_Position_BMX055_BASE*	objClass;																								//	Объявляем указатель на объект полиморфного класса					(функции данного класса будут переопределены, т.к. указателю будет присвоена ссылка на производный класс)
};

#endif