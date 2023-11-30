//======================================================================*/
//   Create Date: 2023/08/18
//   ClassName  : PositionMapper
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#include "PositionMapper.h"

PositionMapper::PositionMapper(Ui::MainMonitor *_ui, ConfigLoader* _configLoader, MediaPlayer* _mediaPlayer,StateManager* _stateManager)
:ui(_ui),
configLoader(_configLoader),
mediaPlayer(_mediaPlayer),
stateManager(_stateManager){
	positions=configLoader->getPositions();
	maxDistance=configLoader->getPosisionResolution();
	curr_pos= 0;
	before_pos=0;
	ui->label_car->move(200,180);
	stateManager->changeOnBoadingReset();
}

PositionMapper::~PositionMapper(){}

void PositionMapper::setPosition(double lat, double lon) {
	Position* pos=findclosedPosition(lat, lon);
	if ( pos != NULL) {
		ROS_INFO("FIND");
		ui->label_car->move(pos->getX(),pos->getY());
		if (pos->getPosAttr()=="sudden_stop" ) {
			stateManager->changeSurddenStop();
			mediaPlayer->playMedia(States::SUDDEN_STOP);
			return;
		}
		if (pos->getPosAttr()=="curve" ) {
			stateManager->changeSharpTurn();
			mediaPlayer->playMedia(States::SHARP_TURN);
			return;
		}
		if (pos->getPosAttr()=="handle_crash" ) {
			stateManager->changeHandleCrash();
			mediaPlayer->playMedia(States::HANDLE_CRASH);
			return;
		}

		if (before_pos > 0 &&  pos->getPosAttr()=="finish" ) {
			stateManager->changeFinish();
			mediaPlayer->playMedia(States::FINISH);
			before_pos=0;
			curr_pos=0;
			return;
		}
		stateManager->changeOnBoadingReset();
	}
	//찾지 못했다면 이동하지 않는다.
}

Position* PositionMapper::findclosedPosition(double lat, double lon) {
	Position* pos=NULL;
	double distance = 0.0;

	//이전 위치부터 찾기
	for ( int i=before_pos; i <positions.size(); i++) {
		ROS_INFO("i - %d", i);
		pos=positions.at(i);
		distance = pos->distance(lat, lon, 'K') * 1000; //meter로 환산
		ROS_INFO("distance - %f, %d", distance, maxDistance);
		if (distance <= maxDistance) {
			if ( before_pos == i) {
				return NULL;
			}
			before_pos=curr_pos;
			curr_pos=i;
			return pos;
		}
	}

	//없으면 처음부터
	for ( int i=0; i <positions.size(); i++) {
		pos=positions.at(i);
		distance = pos->distance(lat, lon, 'K') * 1000; //meter로 환산
		if (distance <= maxDistance) {
			if ( before_pos == i) {
				return NULL;
			}
			before_pos=curr_pos;
			curr_pos=i;
			return pos;
		}
	}

	return NULL;
}