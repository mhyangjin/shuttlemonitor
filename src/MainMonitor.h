//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : MainMonitor
//   Author     : mhjin julu1@naver.com
//   Class Def  : Shuttle_monitor MainWindow
//======================================================================*/
#ifndef MAINMONITOR_H
#define MAINMONITOR_H
#include <QMainWindow>
#include "init.h"
#include "StateManager.h"
#include "CarInfo.h"
#include "CanSubscriber.h"
#include "IntegrationSubscriber.h"
#include "GPSSubscriber.h"
#include "PositionMapper.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainMonitor; }
QT_END_NAMESPACE

class MainMonitor : public QMainWindow
{
    Q_OBJECT
	public slots:
	void onBoadingClicked();
    void finishClicked();
    void fallDownClicked();
    void handleCrashClicked();
    void sharpTurnClicked();
    void surddenStopClicked();
    void wearBeltClicked();

public:
    MainMonitor(QWidget *parent = nullptr);
    ~MainMonitor();

private:
    Ui::MainMonitor *ui=NULL;
	StateManager *stateManager=NULL;
	CanSubscriber *canSubscriber=NULL;
	IntegrationSubscriber *integrationSubscriber=NULL;
	GPSSubscriber * gPSSubscriber=NULL;
	PositionMapper* positionMapper=NULL;
	CarInfo *carInfo=NULL;
	ros::MultiThreadedSpinner* spiner=NULL;


};
#endif // MAINMONITOR_H
