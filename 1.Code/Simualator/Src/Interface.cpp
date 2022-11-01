/******************** (C) COPYRIGHT 2022 Geek************************************
* File Name          : Interface.c
* Current Version    : V2.0
* Author             : logzhan
* Date of Issued     : 2022.10.15
* Comments           : PDR�����㷨���ⲿ�ӿ�
********************************************************************************/
#include "Interface.h"
#include "Location.h"

/* Global Variable Definition ------------------------------------------------*/
const char* PDR_Version = "2.0";
Nmea_t      Nmea;
IMU_t       Imu;
/* Extern Variable Definition ------------------------------------------------*/
extern EKFPara_t  EkfPara;

/**---------------------------------------------------------------------
* Function    : ParseDataAndUpdate
* Description : �����ַ�����Ϣ������
* Date        : 2022/10/16 logzhan
*---------------------------------------------------------------------**/
int ParseDataAndUpdate(char* line, LctFs_t* LocFusion)
{   
    // ����Gnss��Imu��������PDR����
	//ParseGnssInsData(line, &Imu, &Nmea);
	// ����Imu��Nmea�ṹ�壬�����ں�λ��
	return PDRLocationMainLoop(&Imu, &Nmea, LocFusion);
}

/**---------------------------------------------------------------------
* Function    : PDRLocationMainLoop
* Description : PDR��λ��ѭ��
* Date        : 2022/11/1 logzhan
*---------------------------------------------------------------------**/
int PDRLocationMainLoop(IMU_t* imu, Nmea_t* nmea, LctFs_t* LocFusion) {
    int type = 0;

    if (imu->gyr.update) {
        // ��������Ǹ�������ù��Դ���������
        InsLocationUpdate(imu, &EkfPara);
        imu->gyr.update = NO_UPDATE;
    }
    // ���GPS�����£�����
    if (!nmea->Update)return TYPE_FIX_NONE;

    // дGPS���LOG��Ϣ
    //SaveGnssInfo(nmea, LocFusion, NULL);

    // ��GPS�����GPS�ں϶�λ
    //int flag = GnssInsFusionLocation(nmea, &g_kfPara, LocFusion);

    //if (flag != TYPE_FIX_NONE) {
    //    // ����ǿ������֣�ֱ�����GPS��������ƽ������
    //    LocFusion->latitude = R2D(LocFusion->latitude);
    //    LocFusion->longitudinal = R2D(LocFusion->longitudinal);

    //    LocFusion->last_lat = LocFusion->latitude;
    //    LocFusion->last_lon = LocFusion->longitudinal;
    //    type = 1;
    //}
    //else if (LocFusion->last_lat != 0.0 && LocFusion->last_lon != 0.0) {
    //    LocFusion->latitude = LocFusion->last_lat;
    //    LocFusion->longitudinal = LocFusion->last_lon;
    //    type = 1;
    //}
    //ClearNmeaFlg(nmea);
    return type;
}

/**----------------------------------------------------------------------
* Function    : GetPDRVersion
* Description : ��ȡpdr�汾��
* Date        : 2022/10/15 logzhan
*---------------------------------------------------------------------**/
const char* GetPDRVersion(void) {
    return PDR_Version;
}