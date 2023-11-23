//======================================================================*/
//   Create Date: 2023/08/26
//   ClassName  : IntegrationSubscriber
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#include "IntegrationSubscriber.h"
#include <sstream>

IntegrationSubscriber::IntegrationSubscriber(ros::MultiThreadedSpinner* _spiner, CarInfo *_carInfo, StateManager* _stateManager, ConfigLoader* _configLoader,MediaPlayer* _mediaPlayer)
:spiner(_spiner),
carInfo(_carInfo),
stateManager(_stateManager),
configLoader(_configLoader),
mediaPlayer(_mediaPlayer)
{
	fall_down_time=QTime::currentTime();
	ttsDelayMap=configLoader->getTtsTimeSleep();
    subscriber = nodeHandle.subscribe(qPrintable(topicName), 100, &IntegrationSubscriber::subscribeCallBack,this );
    this->start();
}

void IntegrationSubscriber::run() {
    spiner->spin();
}

void IntegrationSubscriber::subscribeCallBack(const shuttle_monitor::IntergrateRecognition& messages) {
// uint32 ps_id
// uint16 ps_status (Standing : 0 / sitting : 1 / fall down : 2 / dump : 3)
// string ps_gender "F","M"
// string ps_age "A", "C"
    stringstream  ss;
    ss << messages;
    QString _data=QString::fromStdString(ss.str());
	ROS_INFO("IntergrateRecognition::subscribeCallBack %s", qPrintable(_data));

	int ps_num=messages.ps_numb;
	int a_m_num=0;
	int a_f_num=0;
	int c_m_num=0;
	int c_f_num=0;
	bool fall_down=false;
	bool dump=false;
	bool standing=false;

	for ( int i=0; i< ps_num; i++) {
		ROS_INFO("PERSON ID: %d", messages.ps_recog[i].ps_id);
		if ( messages.ps_recog[i].ps_gender == "F") {
			if ( messages.ps_recog[i].ps_age == "adult") {
				a_f_num++;
			}
			else {
				c_f_num++;
			}
		}
		else {
			if ( messages.ps_recog[i].ps_age == "adult") {
				a_m_num++;
			}
			else {
				c_m_num++;
			}
		}

		switch (messages.ps_recog[i].ps_status ) {
			case 0:
				standing=true;
				break;
			case 2:
				fall_down=true;
				break;
			case 3:
				dump=true;
				break;
		}
	}
	stateManager->changeOnBoading(a_m_num,a_f_num,c_m_num,c_f_num);
	if (standing) {
		stateManager->changeWearBelt();
	}
	if (fall_down) {
		stateManager->changeFallDown();
		mediaPlayer->playMedia(States::FALL_DOWN);
	}
	if (dump) {

	}
}
