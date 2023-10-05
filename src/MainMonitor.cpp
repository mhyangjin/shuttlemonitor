//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : MainMonitor
//   Author     : mhjin julu1@naver.com
//   Class Def  : Shuttle_monitor MainWindow
//======================================================================*/
#include "MainMonitor.h"

MainMonitor::MainMonitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMonitor)
{
    ui->setupUi(this);
	stateManager= new StateManager(ui);

	carInfo = new CarInfo(ui, "SCN001");
	ROS_INFO("DAQ::register actions..");
	connect(ui->btn_boarding, SIGNAL(clicked()), this, SLOT(onBoadingClicked()));
	connect(ui->btn_finish, SIGNAL(clicked()), this, SLOT(finishClicked()));
	connect(ui->btn_handle, SIGNAL(clicked()), this, SLOT(handleCrashClicked()));
	connect(ui->btn_falldown, SIGNAL(clicked()), this, SLOT(fallDownClicked()));
	connect(ui->btn_belt, SIGNAL(clicked()), this, SLOT(wearBeltClicked()));
	connect(ui->btn_curve, SIGNAL(clicked()), this, SLOT(sharpTurnClicked()));
	connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(surddenStopClicked()));

	spiner= new ros::MultiThreadedSpinner(3);
	canSubscriber = new CanSubscriber(spiner,carInfo, stateManager );
	integrationSubscriber = new IntegrationSubscriber(spiner,carInfo, stateManager );

	positionMapper = new PositionMapper(ui);
	gPSSubscriber =new GPSSubscriber(spiner, positionMapper);
}

void MainMonitor::onBoadingClicked() {
	stateManager->changeOnBoading(3,4,1,1);
}
void MainMonitor::finishClicked() {
	stateManager->changeFinish();
}
void MainMonitor::fallDownClicked() {
	stateManager->changeFallDown();
}
void MainMonitor::handleCrashClicked() {
	stateManager->changeHandleCrash();
}
void MainMonitor::sharpTurnClicked() {
	stateManager->changeSharpTurn();
}
void MainMonitor::surddenStopClicked() {
	stateManager->changeSurddenStop();
}
void MainMonitor::wearBeltClicked() {
	stateManager->changeWearBelt();
}

MainMonitor::~MainMonitor()
{
    delete ui;
	delete stateManager;
}

