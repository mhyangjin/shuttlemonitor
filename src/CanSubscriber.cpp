//======================================================================*/
//   Create Date: 2023/08/18
//   ClassName  : CanSubscriber
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#include "CanSubscriber.h"
#include <sstream>

CanSubscriber::CanSubscriber(ros::MultiThreadedSpinner* _spiner, CarInfo *_carInfo, StateManager* _stateManager, ConfigLoader* _configLoader, MediaPlayer* _mediaPlayer)
:spiner(_spiner),
carInfo(_carInfo),
stateManager(_stateManager),
configLoader(_configLoader),
mediaPlayer(_mediaPlayer)
{
    subscriber = nodeHandle.subscribe(qPrintable(topicName), 100, &CanSubscriber::subscribeCallBack,this );
    this->start();
}

void CanSubscriber::run() {
    spiner->spin();
}

void CanSubscriber::subscribeCallBack(const shuttle_monitor::Can& messages) {
// 	bool veh_ctrl_mode : 0~1 (주행모드)
//  int8 veh_driving_state : (정차 : 2 / 주행 : 4)
//  bool emergency_stop : (정상 주행 : 0 / 비상정지 : 1)
//  int8 battery_soc : (0 ~ 255 (00%))
//  int8 veh_speed :0 ~ 250.0 (000kph)

    stringstream  ss;
    ss << messages;
    QString _data=QString::fromStdString(ss.str());
	// ROS_INFO("CanSubscriber::subscribeCallBack %s", qPrintable(_data));

	if ( messages.car.veh_ctrl_mode) {
		carInfo->setDriveMode("자율");
	}
	else {
		carInfo->setDriveMode("자율");
	}

	if ( messages.car.veh_driving_state == 2) {
		carInfo-> setDriveState("정차");
	}
	else {
		if ( messages.car.veh_driving_state == 4) {
			carInfo-> setDriveState("주행");
		}
	}

	if ( messages.car.emergency_stop) {
		carInfo->setEmergencyStop("비상정지");
		//mediaPlayer->playMedia(States::SUDDEN_STOP);
	}
	else {
		carInfo->setEmergencyStop("정상주행");
	}
	// ROS_INFO("CanSubscriber::Battery %d", messages.car.battery_soc);
	carInfo->setBettery(messages.car.battery_soc);
	carInfo->setDriveSpeed(messages.car.veh_speed);
}
