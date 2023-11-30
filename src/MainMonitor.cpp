//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : MainMonitor
//   Author     : mhjin julu1@naver.com
//   Class Def  : Shuttle_monitor MainWindow
//======================================================================*/
#include "MainMonitor.h"
#include "ConfigLoader.h"
MainMonitor::MainMonitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMonitor)
{
    ui->setupUi(this);
	configLoader= new ConfigLoader();
	carInfo = new CarInfo(ui, configLoader->getCarNo());
	mediaPlayer = new MediaPlayer(configLoader);
	stateManager= new StateManager(ui,configLoader->getCarNo());

	ROS_INFO("SHUTTLE_MONITOR::register actions..");
	connect(ui->btn_boarding, SIGNAL(clicked()), this, SLOT(onBoadingClicked()));
	connect(ui->btn_finish, SIGNAL(clicked()), this, SLOT(finishClicked()));
	connect(ui->btn_handle, SIGNAL(clicked()), this, SLOT(handleCrashClicked()));
	connect(ui->btn_falldown, SIGNAL(clicked()), this, SLOT(fallDownClicked()));
	connect(ui->btn_belt, SIGNAL(clicked()), this, SLOT(wearBeltClicked()));
	connect(ui->btn_curve, SIGNAL(clicked()), this, SLOT(sharpTurnClicked()));
	connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(surddenStopClicked()));
	// ui->btn_boarding->hide();
	// ui->btn_finish->hide();
	// ui->btn_handle->hide();
	// ui->btn_falldown->hide();
	// ui->btn_belt->hide();
	// ui->btn_curve->hide();
	// ui->btn_stop->hide();

	spiner= new ros::MultiThreadedSpinner(3);
	canSubscriber = new CanSubscriber(spiner,carInfo, stateManager, configLoader,mediaPlayer );
	integrationSubscriber = new IntegrationSubscriber(spiner,carInfo, stateManager, configLoader, mediaPlayer );
	positionMapper = new PositionMapper(ui,configLoader,mediaPlayer, stateManager);
	gPSSubscriber =new GPSSubscriber(spiner, positionMapper);
}


void MainMonitor::onBoadingClicked() {
	stateManager->changeOnBoading(3,4,1,1);
}
void MainMonitor::finishClicked() {
	mediaPlayer->playMedia(States::FINISH);
	stateManager->changeFinish();
}
void MainMonitor::fallDownClicked() {
	mediaPlayer->playMedia(States::FALL_DOWN);
	stateManager->changeFallDown();
}
void MainMonitor::handleCrashClicked() {
	ROS_INFO("handleCrashClicked");
	positionMapper->setPosition( 34.7433,  127.7540);
}
void MainMonitor::sharpTurnClicked() {
	mediaPlayer->playMedia(States::SHARP_TURN);
	stateManager->changeSharpTurn();
}
void MainMonitor::surddenStopClicked() {
	mediaPlayer->playMedia(States::SUDDEN_STOP);
	stateManager->changeSurddenStop();
}
void MainMonitor::wearBeltClicked() {
	mediaPlayer->playMedia(States::WEAR_BELT);
	stateManager->changeWearBelt();
}


MainMonitor::~MainMonitor()
{
	delete configLoader;
	delete carInfo;
	delete mediaPlayer;
	delete stateManager;
	delete spiner;
	delete canSubscriber;
	delete integrationSubscriber;
	delete positionMapper;
	delete gPSSubscriber;
    delete ui;

}

