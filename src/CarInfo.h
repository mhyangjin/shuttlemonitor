//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : CarInfo
//   Author     : mhjin julu1@naver.com
//   Class Def  :CarInfo
//======================================================================*/
#ifndef CARINFO_H
#define CARINFO_H
#include <QMainWindow>
#include "init.h"

class CarInfo {
public:
	CarInfo(Ui::MainMonitor *, QString carNo);
	~CarInfo();
	void setDriveMode(QString);
    void setDriveState(QString);
    void setEmergencyStop(QString);
    void setBettery(int);
    void setDriveSpeed(int);
	int getDriveSpeed();
private:
    Ui::MainMonitor *ui;
	QString carNo;
	int Speed;
};
#endif
