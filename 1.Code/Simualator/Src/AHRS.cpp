/******************** (C) COPYRIGHT 2022 Geek************************************
* File Name          : AHRS.cpp
* Current Version    : V1.0
* Author             : logzhan
* Date of Issued     : 2022.09.24
* Comments           : PDR��̬����
********************************************************************************/
/* Header File Including -----------------------------------------------------*/
#include <string.h>
#include <math.h>
#include "AHRS.h"
#include "Quaternion.h"
/* Macro Definition ----------------------------------------------------------*/
#define FLT_THRES                           0.000001f                // ��������С��ֵ
#define ENABLE_MAG                          0
/* Global Variable Definition ------------------------------------------------*/
AHRS_t Ahrs;

/**----------------------------------------------------------------------
* Function    : AHRS_Init
* Description : AHRS��ʼ��
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void AHRS_Init() 
{
    memset(&Ahrs, 0, sizeof(Ahrs));
    Ahrs.Kp = AHRS_KP;
    Ahrs.Dt = 1.0f / AHRS_SAMPLE_FREQ;
    Ahrs.q[0] = 1.0f;
}

/**---------------------------------------------------------------------
* Function    : Vec3Norm
* Description : ��ά������������һ��
* Date        : 2022/11/1 logzhan
*---------------------------------------------------------------------**/
void Vec3Norm(float* vx, float* vy, float* vz)
{
    float norm = sqrtf(((*vx) * (*vx) + (*vy) * (*vy) +
        (*vz) * (*vz)));
    // ��ֹ����ģΪ0�����
    if (norm > FLT_THRES) {
        norm = 1 / norm;
        (*vx) *= norm;   (*vy) *= norm;   (*vz) *= norm;
    }
}

/**----------------------------------------------------------------------
* Function    : MahonyUpdateAHRS
* Description : Mahony��̬�����㷨
* Date        : 2022/09/21 logzhan 
*---------------------------------------------------------------------**/
void MahonyUpdateAHRS(float gx, float gy, float gz, float ax, float ay, float az,
                      float mx, float my, float mz)
{
    float* q = Ahrs.q;
    // ��һ�������ƺͼ��ٶȼ�
    Vec3Norm(&ax, &ay, &az);

    float wx = 0.0f, wy = 0.0f, wz = 0.0f;

#if ENABLE_MAG
    if (!((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f))) {

        pdr_v3Norm(&mx, &my, &mz);

        // �Ѵų�������ϵת������������ϵ h = R^-1 * (mx,my,mz)
        float hx = 2.0f * (mx * (0.5f - q2 * q2 - q[3] * q[3]) + my * (q[1] * q2 - q[0] * q[3]) + mz * (q[1] * q[3] + q[0] * q2));
        float hy = 2.0f * (mx * (q[1] * q2 + q[0] * q[3]) + my * (0.5f - q[1] * q[1] - q[3] * q[3]) + mz * (q2 * q[3] - q[0] * q[1]));
        float hz = 2.0f * (mx * (q[1] * q[3] - q[0] * q2) + my * (q2 * q[3] + q[0] * q[1]) + mz * (0.5f - q[1] * q[1] - q2 * q2));

        // ������bx = 0, by ָ������Ϊ�ֻ�IMU����ʹ�õ��Ƕ�����(x,y,z)����ϵ
        float by = (float)sqrt(hx * hx + hy * hy);
        float bz = hz;

        wx = by * (q[0] * q[3] + q[1] * q2) + bz * (q[1] * q[3] - q[0] * q2);
        wy = by * (0.5f - q[1] * q[1] - q[3] * q[3]) + bz * (q[0] * q[1] + q2 * q[3]);
        wz = by * (q2 * q[3] - q[0] * q[1]) + bz * (0.5f - q[1] * q[1] - q2 * q2);
    }
#endif
    // ������ת������������ϵ   v = R * (0,0,1)
    float vx = q[1] * q[3] - q[0] * q[2];
    float vy = q[0] * q[1] + q[2] * q[3];
    float vz = q[0] * q[0] - 0.5f + q[3] * q[3];

    // ����ʸ��������
    float ex = ay * vz - az * vy + my * wz - mz * wy;
    float ey = az * vx - ax * vz + mz * wx - mx * wz;
    float ez = ax * vy - ay * vx + mx * wy - my * wx;

    // Apply proportional feedback
    gx += Ahrs.Kp * ex;
    gy += Ahrs.Kp * ey;
    gz += Ahrs.Kp * ez;

    // ���������������Ԫ��
    float qa = q[0]; float qb = q[1]; float qc = q[2];
    q[0] += (-qb * gx - qc * gy - q[3] * gz) * 0.5f * (Ahrs.Dt);
    q[1] += (qa * gx + qc * gz - q[3] * gy) * 0.5f * (Ahrs.Dt);
    q[2] += (qa * gy - qb * gz + q[3] * gx) * 0.5f * (Ahrs.Dt);
    q[3] += (qa * gz + qb * gy - qc * gx) * 0.5f * (Ahrs.Dt);

    // ��Ԫ����һ��
    QuaternionNorm(&q[0], &q[1], &q[2], &q[3]);

    // ��Ԫ��תŷ����
    Ahrs.Pitch = (float)asin(-2.0f * (q[3] * q[1] - q[0] * q[2])) * (180.0f / 3.141592f);
    Ahrs.Yaw   = (float)atan2(q[2] * q[1] + q[0] * q[3], 0.5f - q[2] * q[2] - q[3] * q[3]) * (180.0f / 3.141592f);
    Ahrs.Roll  = (float)atan2(q[2] * q[3] + q[0] * q[1], 0.5f - q[2] * q[2] - q[1] * q[1]) * (180.0f / 3.141592f);
}

/**----------------------------------------------------------------------
* Function    : UpdateAHRS
* Description : AHRS�ںϽ���
* Date        : 2022/09/23 logzhan
*---------------------------------------------------------------------**/
int UpdateAHRS(IMU_t* imu) 
{    
    MahonyUpdateAHRS(imu->gyr.s[0], imu->gyr.s[1], imu->gyr.s[2],
                     imu->acc.s[0], imu->acc.s[1], imu->acc.s[2],
                     imu->mag.s[0], imu->mag.s[1], imu->mag.s[2]);
	return PDR_TRUE;
}