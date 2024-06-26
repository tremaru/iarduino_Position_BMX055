//	Гироскоп (гиродатчик)					//	Это датчик измеряющий угловую скорость вокруг собственных осей, он определяет воздействие момента внешней силы.
											//	Эти данные можно использовать, например, для включения режима фиксации жесткого диска в случае падения, удара или резкого перемещения ноутбука
											//
#ifndef iarduino_Position_BMX055_BMG_h		//	Функции работы с гироскопом модуля BMX055
#define iarduino_Position_BMX055_BMG_h		//
//	КОНСТАНТЫ ГИРОСКОПА						//
#define	BMG						30			//	Константа используемая в качестве аргумента при объявлении объекта для работы с гироскопом
#define	BMG_ERR_ID				31			//	Ошибка возвращаемая функцией test(): датчик не найден
#define	BMG_ERR_ST				32			//	Ошибка возвращаемая функцией test(): выявлены неисправности при самотестировании
#define	BMG_DEG_S				33			//	Аргумент функции read()          указывающий выводить данные в °/cек
#define	BMG_RAD_S				34			//	Аргумент функции read()          указывающий выводить данные в рад/cек
#define	BMG_12Hz				35			//	Аргумент функции setBandwidths() указывающий полосу пропускания в Hz - Гц (полоса пропускания  12 Гц, интервал обновлений данных  100 Гц).
#define BMG_23Hz				36			//	Аргумент функции setBandwidths() указывающий полосу пропускания в Hz - Гц (полоса пропускания  23 Гц, интервал обновлений данных  200 Гц).
#define BMG_32Hz				37			//	Аргумент функции setBandwidths() указывающий полосу пропускания в Hz - Гц (полоса пропускания  32 Гц, интервал обновлений данных  100 Гц).
#define BMG_47Hz				38			//	Аргумент функции setBandwidths() указывающий полосу пропускания в Hz - Гц (полоса пропускания  47 Гц, интервал обновлений данных  400 Гц).
#define BMG_64Hz				39			//	Аргумент функции setBandwidths() указывающий полосу пропускания в Hz - Гц (полоса пропускания  64 Гц, интервал обновлений данных  200 Гц).
#define BMG_116Hz				40			//	Аргумент функции setBandwidths() указывающий полосу пропускания в Hz - Гц (полоса пропускания 116 Гц, интервал обновлений данных 1000 Гц).
#define BMG_230Hz				41			//	Аргумент функции setBandwidths() указывающий полосу пропускания в Hz - Гц (полоса пропускания 230 Гц, интервал обновлений данных 2000 Гц).
#define BMG_523Hz				42			//	Аргумент функции setBandwidths() указывающий полосу пропускания в Hz - Гц (полоса пропускания 523 Гц, интервал обновлений данных 2000 Гц).
#define	BMG_125DPS				43			//	Аргумент функции setScale()      указывающий диапазон измерений в DPS - °/с (значение регистров данных 0x8000...0x7FFF соответствует скорости ± 125°/с).
#define	BMG_250DPS				44			//	Аргумент функции setScale()      указывающий диапазон измерений в DPS - °/с (значение регистров данных 0x8000...0x7FFF соответствует скорости ± 250°/с).
#define	BMG_500DPS				45			//	Аргумент функции setScale()      указывающий диапазон измерений в DPS - °/с (значение регистров данных 0x8000...0x7FFF соответствует скорости ± 500°/с).
#define	BMG_1000DPS				46			//	Аргумент функции setScale()      указывающий диапазон измерений в DPS - °/с (значение регистров данных 0x8000...0x7FFF соответствует скорости ±1000°/с).
#define	BMG_2000DPS				47			//	Аргумент функции setScale()      указывающий диапазон измерений в DPS - °/с (значение регистров данных 0x8000...0x7FFF соответствует скорости ±2000°/с).
//	АДРЕС И ID ЧИПА:						//
#define	BMG_ADDRES				0x69		//	Адрес датчика на шине I2C
#define	BMG_ID					0x0F		//	ID датчика
//	РЕГИСТРЫ ЧИПА:							//											|	бит7	|	бит6	|	бит5	|	бит4	|	бит3	|	бит2	|	бит1	|	бит0	|при вкл|	Комментарий
#define	REG_BMG_CHIPID			0x00		//	ID чипа									|											ID<7:0>												| 0x0F	|	ID<7:0>		- значение регистра должно быть равно 0x0F (константа BMG_ID)
#define	REG_BMG_X_LSB			0x02		//	Данные угловой скорости по оси X		|											x_lsb<7:0>											| 0x00	|	x_lsb<7:0>	- младшие биты данных оси X
#define	REG_BMG_X_MSB			0x03		//	Данные угловой скорости по оси X		|											x_msb<7:0>											| 0x00	|	x_msb<7:0>	- старшие биты данных оси X
#define	REG_BMG_Y_LSB			0x04		//	Данные угловой скорости по оси Y		|											y_lsb<7:0>											| 0x00	|	y_lsb<7:0>	- младшие биты данных оси Y
#define	REG_BMG_Y_MSB			0x05		//	Данные угловой скорости по оси Y		|											y_msb<7:0>											| 0x00	|	y_msb<7:0>	- старшие биты данных оси Y
#define	REG_BMG_Z_LSB			0x06		//	Данные угловой скорости по оси Z		|											z_lsb<7:0>											| 0x00	|	z_lsb<7:0>	- младшие биты данных оси Z
#define	REG_BMG_Z_MSB			0x07		//	Данные угловой скорости по оси Z		|											z_msb<7:0>											| 0x00	|	z_msb<7:0>	- старшие биты данных оси Z
#define REG_BMG_INT_ST_0		0x09		//	Флаги состояния прерываний				| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	|	any		|	high	| -	- -	- -	| 0x00	|	any - обнаружено любое движение, high - обнаружено быстрое движение
#define REG_BMG_INT_ST_1		0x0A		//	Флаги состояния прерываний				|	data	|auto_offset|fast_ofsset| fifo_int	| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	| 0x00	|	data - готовы новые данные, auto_offset - выполнена автоматическая компенсация смещения, fast_ofsset - выполнена быстрая компенсания смещения, fifo_int - буфер FIFO заполнен полностью или до уровня (watermark)
#define REG_BMG_INT_ST_2		0x0B		//	Флаги состояния прерываний				| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	| any_sign	| anyFirstZ	| anyFirstY	| anyFirstX	| 0x00	|	any_sign - знак направления движения вызвавшего прерывание по обнаруженного любого движения, anyFirstZ - прерывание по обнаружению любого движения вызвано данными оси Z, anyFirstY - прерывание по обнаружению любого движения вызвано данными оси Y, anyFirstX - прерывание по обнаружению любого движения вызвано данными оси X
#define REG_BMG_INT_ST_3		0x0C		//	Флаги состояния прерываний				| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	| high_sign	|highFirstZ	|highFirstY	|highFirstX	| 0x00	|	any_sign - знак направления движения вызвавшего прерывание по обнаруженного высокой скорости, highFirstZ - прерывание по обнаружению высокой скорости вызвано данными оси Z, highFirstY - прерывание по обнаружению высокой скорости вызвано данными оси Y, highFirstX - прерывание по обнаружению высокой скорости вызвано данными оси X
#define REG_BMG_FIFO_ST			0x0E		//	Статус буфера FIFO						|  overrun	|						fifo_frame_counter<6:0>										| 0x00	|	overrun - произошло переполнение буфера FIFO, fifo_frame_counter<6:0> - размер буфера FIFO (количество кадров хранимых в буфере)
#define REG_BMG_RANGE			0x0F		//	Диапазон измеряемой угловой скорости	| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	|			range<2:0>				| 0x00	|	range<2:0> - диапазон измеряемой угловой скорости: «000» ±2000°/с (разрешение 16,4 LSB/°/с => 61,0 м°/с/LSB); «001» ±1000°/с (разрешение 32,8 LSB/°/с => 30,5 м°/с/LSB); «010» ±500°/с (разрешение 65,6 LSB/°/с => 15,3 м°/с/LSB); «011» ±250°/с (разрешение 131,2 LSB/°/с => 7,6 м°/с/LSB); «100» ±125°/с (разрешение 262,4 LSB/°/с => 3,8 м°/с/LSB)
#define REG_BMG_BW				0x10		//	Полоса пропускания (Bandwidths)			| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	|					bw<3:0>						| 0x80	|	bw<4:0> - полоса пропускания фильтрованных данных: «0111» 32 Гц; «0110» 64 Гц; «0101» 12 Гц; «0100» 23 Гц; «0011» 47 Гц; «0010» 116 Гц; «0001» 230 Гц; «0000» Нефильтрованное = 523 Гц
#define REG_BMG_LPM1			0x11		//	Выбор основных режимов питания			|  suspend	| -	- -	- -	|deep_suspend|	- -	- -	|			sleep_dur<2:0>			| -	- -	- -	| 0x00	|	suspend - спящий режим, deep_suspend - глубокий спящий режим. Можно устанавливать только один из этих флагов. Сброс обоих флагов в 0 установит нормальный режим, sleep_dur<2:0> - продолжительность фазы ожидания в режимах fast-power-up (быстрого включения питания) и power-saving (повышенного энергосбережения): «000» 2мс; «001» 4мс; «010» 5мс; «011» 8мс; «100» 10мс; «101» 15мс; «110» 18мс; «111» 20мс
#define REG_BMG_LPM2			0x12		//	Конфигурация режимов питания.			|fastPowerUp|powSaveMode|	ext_trig_sel<1:0>	| -	- -	- -	|		autosleep_dur<2:0>			| 0x00	|	
#define REG_BMG_D_HBW			0x13		//	Выбор типа данных и их затенение		|dataHigh_bw| shadow_dis| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	| 0x00	|	dataHigh_bw: «1» получение нефильтрованных данных; «0» получение фильтрованных данных, shadow_dis: «1» отключить / «0» включить механизм затенения регистров вывода данных угловой скорости. (затенение обеспечивает целостность данных, блокируя запись новых данных в старшие биты (MSB) если началось чтение младших битов (LSB), до тех пор пока не будут прочитаны старшие биты (MSB) данных угловой скорости).
#define REG_BMG_RESET			0x14		//	Программная перезагрузка				|											softreset<7:0>										| 0x00	|	Запись значения 0xB6 приведёт к перезагрузке и сбросу регистров.
#define REG_BMG_INT_EN_0		0x15		//	Флаги разрешения прерываний				|  data_en	|  fifo_en	| -	- -	- -	- -	- -	- -	- -	- -	- -	|autoOffsetEn|	- -	- -	- -	- -	- -	| 0x00	|	data_en - разрешает прерывание по поступлению новых данных, fifo_en - разрешает прерывание по переполнению буфера fifo, autoOffsetEn - разрешает прерывание по автоматической компенсации смещения
#define REG_BMG_INT_OUT_CTRL	0x16		//	Выбор поведения выводов INT3 и INT4		| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	|  int2_od	|  int2_lvl	|  int1_od	| int1_lvl	| 0x0F	|	int2_od - выбор типа схемы для вывода INT4 («0» комплиментарная (push-pull); «1» открытый сток), int2_lvl - активный уровень на выводе INT4, int1_od - выбор типа схемы для вывода INT3 («0» комплиментарная (push-pull); «1» открытый сток), int1_lvl - активный уровень на выводе INT3
#define REG_BMG_INT_MAP_0		0x17		//	Флаги направляющие прерывания на INT3	| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	| int1_high	| -	- -	- -	|  int1_any	| -	- -	- -	| 0x00	|	int1_high - направить прерывание по обнаружению высокой скорости на вывод INT3, int1_any - направить прерывание по обнаружению любого движения на вывод INT3
#define REG_BMG_INT_MAP_1		0x18		//	Флаги направл-е прерывания на INT3,INT4	| int2_data	|int2FOffset| int2_fifo	|int2AOffset|int1AOffset| int1_fifo	|int1FOffset| int1_data	| 0x00	|	int2_data - направить прерывание по поступлению новых данных на вывод INT4, int2FOffset - направить прерывание по выполнению быстрой компенсании смещения на вывод INT4, int2_fifo - направить прерывание по переполнению буфера fifo или его заполнению до уровня (watermark) на вывод INT4, int2AOffset - направить прерывание по выполнению автоматической компенсании смещения на вывод INT4, int1AOffset - направить прерывание по выполнению автоматической компенсании смещения на вывод INT3, int1_fifo - направить прерывание по переполнению буфера fifo или его заполнению до уровня (watermark) на вывод INT3, int1FOffset - направить прерывание по выполнению быстрой компенсании смещения на вывод INT3, int1_data - направить прерывание по поступлению новых данных на вывод INT4
#define REG_BMG_INT_MAP_2		0x19		//	Флаги направляющие прерывания на INT4	| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	| int2_high	| -	- -	- -	|  int2_any	| -	- -	- -	| 0x00	|	int2_high - направить прерывание по обнаружению высокой скорости на вывод INT4, int2_any - направить прерывание по обнаружению любого движения на вывод INT4
#define REG_BMG_INT_SRC			0x1A		//	Тип данных используемых для прерываний	| -	- -	- -	- -	- -	- -	|slow_offset| -	- -	- -	| high_data	| -	- -	- -	|  any_data	| -	- -	- -	| 0x00	|	Источником данных для соответствующих прерываний будут: «0» фильтрованные данные; «1» нефильтрованные данные
#define REG_BMG_INT_0			0x1B		//	Значения для прерывания любого движения	|fast_offset|									any_th<6:0>										| 0x04	|	fast_offset - источник данных для быстрой компенсации смещения будут: «0» фильтрованные данные; «1» нефильтрованные данные, any_th<6:0> - угловая скорость являющаяся порогом срабатывания для прерывания обнаружения любого движения: скорость = (1 + any_th<6:0>) * 16 LSB
#define REG_BMG_INT_1			0x1C		//	Значения для прерывания любого движения	|	awake_dur<1:0>		|	any_dursample<1:0>	| -	- -	- -	|  any_en_z	|  any_en_y	|  any_en_x	| 0xA0	|	
#define REG_BMG_INT_EN_1		0x1E		//	Разрешение прерывания FIFO по уровню	| fifo_wm_en| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	| 0x08	|	fifo_wm_en - разрешает прерывание по заполнению буфера fifo до уровня (watermark)
#define REG_BMG_INT_RST_LATCH	0x21		//	Выбор режима и сброс прерываний			| reset_int	|offsetReset| -	- -	- -	|  status	|				latch_int<3:0>					| 0x00	|	reset_int - установка в «1» приведёт к сбросу активных прерываний, offset_reset - установка в «1» приведёт к сбросу значений смещения вычисленных с помощью FastOffset, SlowOffset и AutoOffset, latch_int<3:0> - определяет режим прерываний фиксированный, не фиксированный, или временный
#define REG_BMG_INT_2			0x22		//	Значения прерывания высокой скорости	|	high_hy_x<1:0>		|					high_th_x <4:0>							| high_en_x	| 0x02	|	high_hy_x<1:0> - гистерезис прерывания высокой скорости = (255 + 256 * high_hy_x<1:0>) * 4 LSB, high_th_x<4:0> - порог скорости выше которого будет срабатывать прерывание по обнаружению высокой скорости = (255 + 256 * high_th_x<4:0>) * 4 LSB, high_en_x - флаг разрешающий прерывание по обнаруженного высокой скорости оси X
#define REG_BMG_INT_3			0x23		//	Значения прерывания высокой скорости	|											high_dur_x<7:0>										| 0x19	|	high_dur_x<7:0> - пороговая длительность высокой скорости = (1 + high_dur_x<7:0>) * 2,5мс. Прерывание по обнаружению высокой скорости сработает если эта высокая скорость будет фиксироваться в течении не менее указанного времни
#define REG_BMG_INT_4			0x24		//	Значения прерывания высокой скорости	|	high_hy_y<1:0>		|					high_th_y <4:0>							| high_en_y	| 0x02	|	high_hy_y<1:0> - гистерезис прерывания высокой скорости = (255 + 256 * high_hy_y<1:0>) * 4 LSB, high_th_y<4:0> - порог скорости выше которого будет срабатывать прерывание по обнаружению высокой скорости = (255 + 256 * high_th_y<4:0>) * 4 LSB, high_en_y - флаг разрешающий прерывание по обнаруженного высокой скорости оси Y
#define REG_BMG_INT_5			0x25		//	Значения прерывания высокой скорости	|											high_dur_y<7:0>										| 0x19	|	high_dur_y<7:0> - пороговая длительность высокой скорости = (1 + high_dur_y<7:0>) * 2,5мс. Прерывание по обнаружению высокой скорости сработает если эта высокая скорость будет фиксироваться в течении не менее указанного времни
#define REG_BMG_INT_6			0x26		//	Значения прерывания высокой скорости	|	high_hy_z<1:0>		|					high_th_z <4:0>							| high_en_z	| 0x02	|	high_hy_z<1:0> - гистерезис прерывания высокой скорости = (255 + 256 * high_hy_z<1:0>) * 4 LSB, high_th_z<4:0> - порог скорости выше которого будет срабатывать прерывание по обнаружению высокой скорости = (255 + 256 * high_th_z<4:0>) * 4 LSB, high_en_z - флаг разрешающий прерывание по обнаруженного высокой скорости оси Z
#define REG_BMG_INT_7			0x27		//	Значения прерывания высокой скорости	|											high_dur_z<7:0>										| 0x19	|	high_dur_z<7:0> - пороговая длительность высокой скорости = (1 + high_dur_z<7:0>) * 2,5мс. Прерывание по обнаружению высокой скорости сработает если эта высокая скорость будет фиксироваться в течении не менее указанного времни
#define REG_BMG_SOFS			0x31		//	Настройки медленной компенсации смещения| slow_offset_th<1:0>	|		slow_offset_dur<2:0>		|SOffsetEn_z|SOffsetEn_y|SOffsetEn_x| 0x60	|	slow_offset_th<1:0> - выбор скорости для медленной компенсации смещения: «00» 0.1°/с; «01» 0.2°/с; «10» 0.5°/с; «11» 1.0°/с, slow_offset_dur<2:0> - выбор периода времени для медленной компенсации смещения: 0=40мс; 1=80мс; 2=160мс; 3=320мс; 4=640мс; 5=1280мс, SOffsetEn_z - флаг разрешающий медленную компенсацию смещения по оси Z, SOffsetEn_y - флаг разрешающий медленную компенсацию смещения по оси Y, SOffsetEn_x - флаг разрешающий медленную компенсацию смещения по оси X,
#define REG_BMG_AOFS_FOFS		0x32		//	Настр-ки авто/быстр компенсации смещения|autoOffsetWordLen<1:0>	|fastOffsetWordLen<1:0>	| FOffsetEn	|FOffsetEn_z|FOffsetEn_y|FOffsetEn_x| 0xC0	|	autoOffsetWordLen<1:0> - выбор количества выборок для автоматической компенсации смещения: «00» 32 выборки; «01» 64 выборки; «10» 128 выборок; «11» 256 выборок, fastOffsetWordLen<1:0> - выбор количества выборок для быстрой компенсации смещения: «00» 32 выборки; «01» 64 выборки; «10» 128 выборок; «11» 256 выборок, FOffsetEn - флаг запускающий быструю компенсацию смещения для задействованных осей, FOffsetEn_z - флаг разрешающий быструю компенсацию смещения по оси Z, FOffsetEn_y - флаг разрешающий быструю компенсацию смещения по оси Y, FOffsetEn_x - флаг разрешающий быструю компенсацию смещения по оси X
#define REG_BMG_TRIM_NVM_CTRL	0x33		//	Настройка энергонезависимой памяти NVM	|				nvm_remain<3:0>					|  nvm_load	|  nvm_rdy	| nvm_trig	| nvm_mode	| 0x00	|	nvm_remain<3:0> - количество оставшихся циклов записи в NVM (многократно программируемую энергонезависимую память), nvm_load - флаг разрешающий обновление всех конфигурационных регистров из NVM памяти, nvm_rdy - флаг состояния готовности памяти NVM у записи: «0» выполняется запись (обновление) NVM; «1» память NVM готова принять новые тданные для записи, nvm_trig - флаг запускающий опреацию записи в NVM: «1» запуск; «0» нет, nvm_mode - флаг разблокировки записи в NVM: «1» запись разрешена (разблокирована); «0» запись запрещена (заблокирована).
#define REG_BMG_BGW_SPI3_WDT	0x34		//	Настройки для цифровых интерфейсов		| -	- -	- -	- -	- -	- -	|extFifoSCen|extFifoSsel|burstSameEn| i2c_wdt_en|i2c_wdt_sel|	spi3	| 0x00	|	extFifoSCen - флаг разрешающий внешнюю синхронизацию FIFO, extFifoSsel - выбор источника для внешней синхронизации FIFO: «0» INT3; «1» INT4, burstSameEn - назначение не описано, i2c_wdt_en - флаг активации сторожевого таймера WDT на выводе SDA для шины I2C: «1» активен; «0» отключён, i2c_wdt_sel - выбор периода ожидания для сторожевого таймера на шине I2C: «0» 1 мс; «1» 50 мс, spi3 - флаг выбора 3-проводного режима шины SPI: «1» 3-проводной режим; «0» 4-проводный режим.
#define REG_BMG_OFC_0			0x36		//	Значения компенсации смещения			|	offset_x<3:2>		|			offset_y<3:1>			|			offset_z<3:1>			| N/A	|	offset_x<3:2> - средние биты значения компенсации смещения для оси X, offset_y<3:1> - средние биты значения компенсации смещения для оси Y, offset_z<3:1> - средние биты значения компенсации смещения для оси Z
#define REG_BMG_OFC_1			0x37		//	Значения компенсации смещения			|										offset_x<11:4>											| N/A	|	offset_x<11:4> - старшие биты значения компенсации смещения для оси X
#define REG_BMG_OFC_2			0x38		//	Значения компенсации смещения			|										offset_y<11:4>											| N/A	|	offset_y<11:4> - старшие биты значения компенсации смещения для оси Y
#define REG_BMG_OFC_3			0x39		//	Значения компенсации смещения			|										offset_z<11:4>											| N/A	|	offset_z<11:4> - старшие биты значения компенсации смещения для оси Z
#define REG_BMG_TRIM_GP_0		0x3A		//	Значения компенсации смещения			|					GP0<3:0>					|	offset_x<1:0>		|offset_y[0]|offset_z[0]| N/A	|	GP0<3:0>  - младшие биты регистра данных общего назначения с резервным копированием NVM, offset_x<1:0> - младшие биты значения компенсации смещения для оси X, offset_y[0] - младший бит значения компенсации смещения для оси Y, offset_z[0] - младший бит значения компенсации смещения для оси Z
#define REG_BMG_TRIM_GP_1		0x3B		//	Регистр памяти NVM общего назначения	|											GP0<11:4>											| N/A	|	GP0<11:4> - старшие биты регистра данных общего назначения с резервным копированием NVM.
#define REG_BMG_BI_SELF_TEST	0x3C		//	Запуск и результат самотестирования		| -	- -	- -	- -	- -	- -	- -	- -	- -	|  rate_ok	| -	- -	- -	| bist_fail	| bist_rdy	| trig_bist	| N/A	|	rate_ok - индикатор правильной работы датчика, bist_fail - флаг результата самотестирования (читается при установленном флаге bist_rdy): «0» самотестирование пройдено; «1» самотестирование не пройдено, bist_rdy - флаг готовности результата самотестирования, trig_bist - установка в «1» запускает самотестирование
#define REG_BMG_FIFO_CONFIG_0	0x3D		//	Уровень watermark для буфера FIFO		|	 tag	|					fifo_water_mark_level_trigger_retain<6:0>						| 0x00	|	tag - флаг вызывает прерывание FIFO. fifo_water_mark_level_trigger_retain<6:0> - уровень watermark для буфера FIFO. Как только буфер заполнится до этого уровня - сработает прерывание fifo_int если оно разрешено флагом fifo_wm_en
#define REG_BMG_FIFO_CONFIG_1	0x3E		//	Настройки конфигурации буфера FIFO		|	fifo_mode<1:0>		| -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	| fifo_data_select<1:0>	| 0x00	|	fifo_mode<1:0> - выбор режима работы буфера FIFO: «00» BYPASS (глубина буфера 1 кадр, старые данные стираются); «01» FIFO (сбор данных прекращается при полном заполнении буфера - 100 кадров); «10» STREAM (сбор данных продолжается при полном заполнении буфера, старые кадры стираются), fifo_data_select<1:0> - выбор данных для буфера FIFO: «00» собираются данные всех осей XYZ; «01» собираются данные только оси X; «10» собираются данные только оси Y; «11» собираются данные только оси Z. При записи данных в регистр FIFO_CONFIG_1, память FIFO буфера и флаг fifo-full очищается.
#define REG_BMG_FIFO_DATA		0x3F		//	Регистр чтения данных из буфера FIFO	|										fifo_data<7:0>											| 0x00	|	fifo_data<7:0> - байт для чтения данных из буфера FIFO. Данные буфера FIFO хранятся кадрами (объём буфера равен 32 кадра). Состав кадра зависит от значения битов fifo_data_select<1:0> регистра REG_BMA_FIFO_CONFIG_1: Если выбраны данные всех осей XYZ, то каждый кадр считывается побайтно в следующем порядке X-lsb, X-msb, Y-lsb, Y-msb, Z-lsb, Z-msb; Если выбраны данные только оси X, то каждый кадр считывается побайтно в следующем порядке X-lsb, X-msb; Если выбраны данные только оси Y или только оси Z, то каждый кадр считывается побайтно, как и для оси X. Если чтение буфера остановлено и кадр считан не полностью, то при следующей инициализации чтения в fifo_data<7:0> будет находиться пербый байт следующего кадра.

#include "iarduino_Position_BMX055_I2C.h"																						//	Подключаем файл iarduino_Position_BMX055_I2C.h - для работы с шиной I2C
																																//
class iarduino_Position_BMX055_BMG: public iarduino_Position_BMX055_BASE{														//
	public:																														//
	/**	функции доступные пользователю **/																						//
//		Инициализация датчика:																									//
		bool	begin(iarduino_I2C_Select* ptrI2C, bool setZero, float*ptrX,float*ptrY,float*ptrZ,float*ptrT, float*ptrQ1,float*ptrQ2,float*ptrQ3,float*ptrQ4){ // Аргументы: ptrI2C - указатель на объект работы с шиной I2C, setZero - флаг указывающий о необходимости установить текущие показания в 0, указатели на переменные выводимых данных)
					selI2C = ptrI2C;																							//	Присваиваем указателю selI2C адрес из указателя ptrI2C
					axisX  = ptrX;																								//	Присваиваем указателю axisX адрес из указателя ptrX который ссылается на переменную axisX класса iarduino_Position_BMX055 предназначенную для вывода данных по оси X
					axisY  = ptrY;																								//	Присваиваем указателю axisY адрес из указателя ptrY который ссылается на переменную axisY класса iarduino_Position_BMX055 предназначенную для вывода данных по оси Y
					axisZ  = ptrZ;																								//	Присваиваем указателю axisZ адрес из указателя ptrZ который ссылается на переменную axisZ класса iarduino_Position_BMX055 предназначенную для вывода данных по оси Z
					temp   = ptrT;																								//	Присваиваем указателю temp  адрес из указателя ptrT который ссылается на переменную temp  класса iarduino_Position_BMX055 предназначенную для вывода температуры
					if( selI2C->readByte(BMG_ADDRES, REG_BMG_CHIPID) != BMG_ID ){ return false; }								//	Возвращаем ошибку если содержимое регистра REG_BMG_CHIPID не совпало с реальным ID чипа указанным в константе BMG_ID
				//	Перезагружаем датчик:																						//
					selI2C->writeByte(BMG_ADDRES, REG_BMG_RESET, 0xB6);															//	Выполняем программную перезагрузку (записываем значение 0xB6 в регистр REG_BMG_RESET)
					delay(100);																									//	Ждём сброса регистров. Модуль мог не ответить ACK на предыдущую команду перезагрузки, значит мог вызвать timeout библиотеки I2C.
				//	Включаем датчик:																							//
					if(!selI2C->writeByte(BMG_ADDRES, REG_BMG_LPM1, 0x00) ){													//	Переводим гироскоп в нормальный режим питания (сбрасываем флаги suspend и deep_suspend)
						selI2C->begin();																						//	Повторно инициируем работу с шиной I2C, т.к. библиотека I2C могла находиться в timeout.
						selI2C->writeByte(BMG_ADDRES, REG_BMG_LPM1, 0x00);														//	Переводим гироскоп в нормальный режим питания (сбрасываем флаги suspend и deep_suspend)
					}																											//
				//	Настраиваем датчик:																							//
					setScale(varRanges);																						//	Устанавливаем диапазон измерений гироскопа (указывая предел измеряемой угловой скорости)
					setBandwidths(varBandwidth);																				//	Устанавливаем пропускную способность гироскопа (указывая частоту обновления фильтрованных данных)
					selI2C->writeByte(BMG_ADDRES, REG_BMG_D_HBW, 0x00);															//	Указываем гироскопу, что требуется выводить отфильтрованные данные (dataHigh_bw=0) с механизмом их затенения во время чтения (shadow_dis=0). Затенение осначает что значение регистров данных не будет изменяться от начала и до конца пакетного чтения
					if( setZero ){ setFastOffset(BMG); }																		//	Выполняем быструю компенсацию смещения данных (значение всех осей сбросятся в ноль, если данные текущих угловых скоростей по осям были меньше ±125°/с)
					return true;																								//
		}																														//
																																//
//		Самотестирование датчика:																								//
		uint8_t	test(void){																										//	Аргумент: отсутствует
					if( selI2C->readByte(BMG_ADDRES, REG_BMG_CHIPID) != BMG_ID ){ return BMG_ERR_ID; }							//	Возвращаем ошибку если содержимое регистра REG_BMG_CHIPID не совпало с реальным ID чипа указанным в константе BMG_ID
					uint8_t	i;																									//	Объявляем переменную для чтения результата самотестирования
					selI2C->writeByte(BMG_ADDRES, REG_BMG_BI_SELF_TEST, 0x01); 													//	Выполняем самотестирование BIST (Built-In Self Test) установив последний бит trig_bist регистра REG_BMG_BI_SELF_TEST
			do{ i = selI2C->readByte (BMG_ADDRES, REG_BMG_BI_SELF_TEST); delay(10); } while (i&0x02);							//	Ждём установки бита bist_rdy регистра REG_BMG_BI_SELF_TEST
					if( i&0x04 ){ return BMG_ERR_ST; }																			//	Если установлен бит bist_fail регистра REG_BMG_BI_SELF_TEST значит тест не пройден, возвращаем BMG_ERR_ST
					return 0;																									//	Выводим результат успешного самотестирования
		}																														//
																																//
//		Чтение данных из датчика:																								//
		bool	read(uint8_t thisMera){																							//	Аргумент: мера измерения читаемых данных (BMG_DEG_S / BMG_RAD_S)
					uint8_t i[6];																								//	Объявляем массив i размером 6 байт
					if( !selI2C->readBytes(BMG_ADDRES, REG_BMG_X_LSB, i, 6) ){ return false; }									//	Читаем 6 байт одним пакетом начиная с регистра REG_BMG_X_LSB в массив i
					float j = 1;																								//	Определяем множитель
					switch(thisMera){																							//	В зависимости от установленной меры измерений
						default:		thisMera = BMG_DEG_S;																	//	По умолчанию значения возвращаются в °/c
						case BMG_DEG_S:	j=1.0f;			break;																	//	Если данные требуется возвращать в °/c
						case BMG_RAD_S:	j=PI/180.0f;	break;																	//	Если данные требуется возвращать в рад/c
					}																											//
					*axisX = (float)((int16_t)( ((uint16_t)i[1]<<8 ) | (uint16_t)i[0] )) * varQuantum * j;						//	Получаем результирующее 16-битное значение из частей MSB (i[1]), LSB (i[0]), умножаем его на шаг квантования varQuantum и преобразуем в требуемую величину измерений
					*axisY = (float)((int16_t)( ((uint16_t)i[3]<<8 ) | (uint16_t)i[2] )) * varQuantum * j;						//	Получаем результирующее 16-битное значение из частей MSB (i[3]), LSB (i[2]), умножаем его на шаг квантования varQuantum и преобразуем в требуемую величину измерений
					*axisZ = (float)((int16_t)( ((uint16_t)i[5]<<8 ) | (uint16_t)i[4] )) * varQuantum * j;						//	Получаем результирующее 16-битное значение из частей MSB (i[5]), LSB (i[4]), умножаем его на шаг квантования varQuantum и преобразуем в требуемую величину измерений
					*temp  = 0;																									//  У гироскопа нет регистров для хранения данных температуры, возвращаем 0°С.
					return true;																								//
		}																														//
																																//
//		Установка диапазона измерений:																							//
		void	setScale(uint8_t scale){																						//	Аргумент: предел измеряемой угловой скорости
					uint8_t i=0x03;																								//	Значение для записи в регистр REG_BMG_RANGE.
					switch (scale){																								//	Проверяем значение аргумента функции (максимальная детектируемая угловая скорость)
						default:		  scale=BMG_125DPS;																		//	Если значение некорректное, то меняем его на BMG_125DPS (значение по умолчанию).
						case BMG_125DPS:  varQuantum = 124.87/32768.0; i=0x04; break; 											//	Вся шкала 16 бит (±32768) ≈ угловой скорости ±125 °/с. Определяем шаг квантования (какой угловой скорости равно значение «1» из регистра данных на выбранном диапазоне)
						case BMG_250DPS:  varQuantum = 249.75/32768.0; i=0x03; break; 											//	Вся шкала 16 бит (±32768) ≈ угловой скорости ±250 °/с. Определяем шаг квантования (какой угловой скорости равно значение «1» из регистра данных на выбранном диапазоне)
						case BMG_500DPS:  varQuantum = 499.5 /32768.0; i=0x02; break; 											//	Вся шкала 16 бит (±32768) ≈ угловой скорости ±500 °/с. Определяем шаг квантования (какой угловой скорости равно значение «1» из регистра данных на выбранном диапазоне)
						case BMG_1000DPS: varQuantum = 999.0 /32768.0; i=0x01; break; 											//	Вся шкала 16 бит (±32768) ≈ угловой скорости ±1000°/с. Определяем шаг квантования (какой угловой скорости равно значение «1» из регистра данных на выбранном диапазоне)
						case BMG_2000DPS: varQuantum = 1998.0/32768.0; i=0x00; break; 											//	Вся шкала 16 бит (±32768) ≈ угловой скорости ±2000°/с. Определяем шаг квантования (какой угловой скорости равно значение «1» из регистра данных на выбранном диапазоне)
					}																											//
					varRanges=scale;																							//	Запоминаем выбранный диапазон измерений
					selI2C->writeByte(BMG_ADDRES, REG_BMG_RANGE, i);															//	Устанавливаем диапазон измерений акселерометра (последние 3 бита регистра REG_BMG_RANGE)
		}																														//
																																//
//		Установка полосы пропускания для фильтрованных данных:																	//
		void	setBandwidths(uint8_t bandwidths){																				//	Аргумент: полоса пропускания
					uint8_t i=0x04;																								//	Значение для записи в регистр REG_BMA_BW.
					switch (bandwidths){																						//	Проверяем значение аргумента функции (максимальное детектируемое угловое ускорение)
						default:		bandwidths=BMG_23Hz;																	//	Если значение некорректное, то меняем его на BMG_23Hz (значение по умолчанию).
						case BMG_23Hz:	i=0x04; break;																			//	Для полосы пропускания  23 Гц (интервал обновлений данных  200 Гц) нужно записать i в биты bw<3:0> регистра REG_BMG_BW.
						case BMG_12Hz:	i=0x05; break;																			//	Для полосы пропускания  12 Гц (интервал обновлений данных  100 Гц) нужно записать i в биты bw<3:0> регистра REG_BMG_BW.
						case BMG_32Hz:	i=0x07; break;																			//	Для полосы пропускания  32 Гц (интервал обновлений данных  100 Гц) нужно записать i в биты bw<3:0> регистра REG_BMG_BW.
						case BMG_47Hz:	i=0x03; break;																			//	Для полосы пропускания  47 Гц (интервал обновлений данных  400 Гц) нужно записать i в биты bw<3:0> регистра REG_BMG_BW.
						case BMG_64Hz:	i=0x06; break;																			//	Для полосы пропускания  64 Гц (интервал обновлений данных  200 Гц) нужно записать i в биты bw<3:0> регистра REG_BMG_BW.
						case BMG_116Hz:	i=0x02; break;																			//	Для полосы пропускания 116 Гц (интервал обновлений данных 1000 Гц) нужно записать i в биты bw<3:0> регистра REG_BMG_BW.
						case BMG_230Hz:	i=0x01; break;																			//	Для полосы пропускания 230 Гц (интервал обновлений данных 2000 Гц) нужно записать i в биты bw<3:0> регистра REG_BMG_BW.
						case BMG_523Hz:	i=0x00; break;																			//	Для полосы пропускания 523 Гц (интервал обновлений данных 2000 Гц) нужно записать i в биты bw<3:0> регистра REG_BMG_BW.
					}																											//
					varBandwidth=bandwidths;																					//	Запоминаем выбранную полосу пропускания
					selI2C->writeByte(BMG_ADDRES, REG_BMG_BW, i);																//	Устанавливаем пропускную способность гироскопа (последние 4 бита регистра REG_BMG_BW)
		}																														//
																																//
//		Выполнение быстрой компенсации смещения данных:																			//
		void	setFastOffset(uint8_t offset){																					//	Аргумент: не имеет значения.
					       selI2C->writeByte(BMG_ADDRES, REG_BMG_AOFS_FOFS,0xFF);												//	Выполняем быструю компенсацию смещения для всех осей установив все биты регистра REG_BMG_AOFS_FOFS в «1»: autoOffsetWordLen<1:0>=«11» - 256 выборок для автоматической компенсации смещения (были установлены по умолчанию), fastOffsetWordLen<1:0>=«11» - 256 выборок для быстрой компенсации смещения, FOffsetEn=«1» - запускаем быструю компенсацию смещения для всех осей, так как флаги FOffsetEn_z, FOffsetEn_y и FOffsetEn_x тоже установлены в «1».
					while( selI2C->readByte (BMG_ADDRES, REG_BMG_AOFS_FOFS     )&0x08==0){;}									//	Ждём завершения быстрой компенсации смещения (ждём пока сбросится флаг FOffsetEn)
		}																														//
																																//
//		Функции не используемые гироскопом:																						//
		void	setFastOffset (float* offset){;}																				//	Установка массива компенсации смещения данных используется только для объекта BMM, но функцию объявить нужно, так как данный класс является производным и должен содержать все функции полиморфного класса
		void	getFastOffset (float* offset){;}																				//	Получение массива компенсации смещения данных используется только для объекта BMM, но функцию объявить нужно, так как данный класс является производным и должен содержать все функции полиморфного класса
		uint8_t	getFilter     (void         ){return 0;}																		//	Фильтр используется только для объекта BMX, но функцию объявить нужно, так как данный класс является производным и должен содержать все функции полиморфного класса
																																//
	private:																													//
	/**	Внутренние переменные **/																								//
		iarduino_I2C_Select *selI2C;																							//	Создаём указатель на объект работы с шиной I2C.
		uint8_t	varRanges =		BMG_125DPS;																						//	Определяем переменную для хранения полного диапазона измерений (какой угловой скорости соответствует значение где все биты установлены в «1»)
		uint8_t	varBandwidth =	BMG_23Hz;																						//	Определяем переменную для хранения полосы пропускания фильтрованных данных
		float	varQuantum =	124.87/32768.0;																					//	Определяем переменную для хранения шага квантования (какой угловой скорости равно значение «1» из регистра данных на выбранном диапазоне)
		float *	axisX;																											//	Объявляем указатель который будет ссылаться на переменную для вывода данных по оси X
		float *	axisY;																											//	Объявляем указатель который будет ссылаться на переменную для вывода данных по оси Y
		float *	axisZ;																											//	Объявляем указатель который будет ссылаться на переменную для вывода данных по оси Z
		float *	temp;																											//	Объявляем указатель который будет ссылаться на переменную для вывода температуры
};																																//
																																//
#endif																															//