//	Фильтр Себастьяна Маджвика

#ifndef iarduino_Position_BMX055_Madgwick_no_magnetometer_h
#define iarduino_Position_BMX055_Madgwick_no_magnetometer_h

class iarduino_Position_BMX055_FILTER_MADGWICK_NO_BMM: public iarduino_Position_BMX055_FILTER{
	public:
		//		Переменные:
		float	GyroMeasError = PI * (40.0f / 180.0f);   // gyroscope measurement error in rads/s (start at 40 deg/s)
		float	GyroMeasDrift = PI * (0.0f  / 180.0f);   // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
		float	beta = sqrt(3.0f / 4.0f) * GyroMeasError;   // compute beta
		float	zeta = sqrt(3.0f / 4.0f) * GyroMeasDrift;   // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value

//		Функция выполнения фильтра Маджвика:
		void	filter(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz, float*q1, float*q2, float*q3, float*q4 ,float deltat){
					float norm;
					float s1, s2, s3, s4;
					float qDot1, qDot2, qDot3, qDot4;
	
					// Auxiliary variables to avoid repeated arithmetic
					float _2q1 = 2.0f * (*q1);
					float _2q2 = 2.0f * (*q2);
					float _2q3 = 2.0f * (*q3);
					float _2q4 = 2.0f * (*q4);
					float _4q1 = 4.0f * (*q1);
					float _4q2 = 4.0f * (*q2);
					float _4q3 = 4.0f * (*q3);
					float _8q2 = 8.0f * (*q2);
					float _8q3 = 8.0f * (*q3);
					float q1q1 = (*q1) * (*q1);
					float q2q2 = (*q2) * (*q2);
					float q3q3 = (*q3) * (*q3);
					float q4q4 = (*q4) * (*q4);

					// Normalise accelerometer measurement
					norm = sqrtf(ax * ax + ay * ay + az * az);
					if (norm == 0.0f) return; // handle NaN
					norm = 1.0f/norm;
					ax *= norm;
					ay *= norm;
					az *= norm;

					// Gradient decent algorithm corrective step
					s1 = _4q1 * q3q3 + _2q3 * ax + _4q1 * q2q2 - _2q2 * ay;
					s2 = _4q2 * q4q4 - _2q4 * ax + 4.0f * q1q1 * (*q2) - _2q1 * ay - _4q2 + _8q2 * q2q2 + _8q2 * q3q3 + _4q2 * az;
					s3 = 4.0f * q1q1 * (*q3) + _2q1 * ax + _4q3 * q4q4 - _2q4 * ay - _4q3 + _8q3 * q2q2 + _8q3 * q3q3 + _4q3 * az;
					s4 = 4.0f * q2q2 * (*q4) - _2q2 * ax + 4.0f * q3q3 * (*q4) - _2q3 * ay;
					norm = sqrtf(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
					norm = 1.0f/norm;
					s1 *= norm;
					s2 *= norm;
					s3 *= norm;
					s4 *= norm;

					// Compute rate of change of quaternion
					qDot1 = 0.5f * (-(*q2) * gx - (*q3) * gy - (*q4) * gz) - beta * s1;
					qDot2 = 0.5f * ((*q1) * gx + (*q3) * gz - (*q4) * gy) - beta * s2;
					qDot3 = 0.5f * ((*q1) * gy - (*q2) * gz + (*q4) * gx) - beta * s3;
					qDot4 = 0.5f * ((*q1) * gz + (*q2) * gy - (*q3) * gx) - beta * s4;

					// Integrate to yield quaternion
					(*q1) += qDot1 * deltat;
					(*q2) += qDot2 * deltat;
					(*q3) += qDot3 * deltat;
					(*q4) += qDot4 * deltat;
					norm = sqrtf((*q1) * (*q1) + (*q2) * (*q2) + (*q3) * (*q3) + (*q4) * (*q4));    // normalise quaternion
					norm = 1.0f/norm;
					(*q1) *= norm;
					(*q2) *= norm;
					(*q3) *= norm;
					(*q4) *= norm;
        }
//		Функция возвращающая тип данного фильтра:
		uint8_t	getFilter(void){return FILTER_MADGWICK_NO_BMM;}																				//
};

#endif