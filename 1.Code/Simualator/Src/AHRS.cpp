#include "AHRS.h"
#include "PDRBase.h"

/**----------------------------------------------------------------------
* Function    : AHRS_Init
* Description : AHRS初始化
* Date        : 2022/09/21 logzhan
*---------------------------------------------------------------------**/
void AHRS_Init() {

}

/**----------------------------------------------------------------------
* Function    : MahonyUpdateAHRS
* Description : Mahony姿态更新算法
* Date        : 2022/09/21 logzhan 
*---------------------------------------------------------------------**/
void MahonyUpdateAHRS() {

}

/**----------------------------------------------------------------------
* Function    : UpdateAHRS
* Description : AHRS融合解算
* Date        : 2022/09/23 logzhan
*---------------------------------------------------------------------**/
int UpdateAHRS(IMU_t* IMU) {
	return PDR_TRUE;
}