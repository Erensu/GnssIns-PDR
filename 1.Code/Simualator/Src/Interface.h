#ifndef _PDR_INTERFACE_H
#define _PDR_INTERFACE_H
#include "PDRBase.h"

/**---------------------------------------------------------------------
* Function    : PDRLocationMainLoop
* Description : PDR��λ��ѭ��
* Date        : 2022/11/1 logzhan
*---------------------------------------------------------------------**/
int PDRLocationMainLoop(IMU_t* imu, Nmea_t* nmea, LctFs_t* LocFusion);


/**----------------------------------------------------------------------
* Function    : GetPDRVersion
* Description : ��ȡpdr�汾��
* Date        : 2022/10/15 logzhan
*---------------------------------------------------------------------**/
const char* GetPDRVersion(void);

#endif // _PDR_INTERFACE_H
