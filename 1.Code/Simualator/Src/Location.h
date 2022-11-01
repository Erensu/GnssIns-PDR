#ifndef _PDR_LOCATION_H_
#define _PDR_LOCATION_H_

#include "PDRBase.h"

/**---------------------------------------------------------------------
* Function    : PDRNav_Init
* Description : PDR����ϵͳ��ʼ��
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void PDRNav_Init(void);

/**----------------------------------------------------------------------
* Function    : InsLocation
* Description : PDR�ߵ�λ�ø���
* Date        : 2022-09-21 logzhan
*---------------------------------------------------------------------**/
void InsLocationUpdate(IMU_t* ImuData, EKFPara_t* Ekf);

/**----------------------------------------------------------------------
* Function    : GnssInsLocFusion
* Description : PDR��GNSS��INS�ں϶�λ
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void GnssInsLocationUpdate(void);

#endif