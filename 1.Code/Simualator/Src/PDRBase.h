#ifndef  _PDR_BASE_H_
#define  _PDR_BASE_H_

#define ACCURACY_ERR_MAX                    1000                 // GPS��accuracy���ֵ,һ�����ڳ�ʼ����
#define N                                   4                    // ����ά��
#define MAX_NO_GPS_PREDICT                  10		             // ��GPS��Ϣ״̬�����λ����������			     


typedef struct {
	double xk[N];             // ϵͳ״̬����  xk[0]: ����x  xk[1]������y  xk[2]������  xk[3] �������
	double p_xk[N];           // ���Ԥ�����  xk[0]: ����x  xk[1]������y  xk[2]������  xk[3] �������
	double zk[N];
	double p_pk[N][N];
	double pk[N][N];
	double phi[N][N];
	double hk[N][N];
	double q[N][N];           // �������˲���Q����(��������)
	double r[N][N];           // �������˲�R����(�۲�����)
	double Kk[N][N];
	double lambda;
	double plat;
	double plon;
	double initHeading;
}EKFPara_t;

#endif // ! _PDR_BASE_H
