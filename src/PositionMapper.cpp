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
	latest_pos = 0;
	ui->label_car->move(200,180);
}

PositionMapper::~PositionMapper(){}

void PositionMapper::setPosition(double lat, double lon) {
	Position* pos=findclosedPosition(lat, lon);
	if ( pos != NULL) {
		ui->label_car->move(pos->getX(),pos->getY());
		if (pos->getPosAttr()=="sudden_stop" ) {
			mediaPlayer->playMedia(States::SUDDEN_STOP);
		}
		if (pos->getPosAttr()=="curve" ) {
			mediaPlayer->playMedia(States::SHARP_TURN);
		}
		if (latest_pos > 0 &&  pos->getPosAttr()=="finish" ) {
			stateManager->changeFinish();
			mediaPlayer->playMedia(States::FINISH);
			latest_pos=0;
		}
	}
	//찾지 못했다면 이동하지 않는다.
}

Position* PositionMapper::findclosedPosition(double lat, double lon) {
	Position* pos=NULL;
	double distance = 0.0;
	//먼저 최종 위치에서 +1, -1 위치를 확인
	if (latest_pos == 0) {
		pos=positions.at(latest_pos +1);
		distance = pos->distance(lat, lon, 'K') * 1000; //meter로 환산
		if (distance <= maxDistance) {
			latest_pos=latest_pos +1;
			return pos;
		}
	}
	else {
		pos=positions.at(latest_pos +1);
		distance = pos->distance(lat, lon, 'K') * 1000; //meter로 환산
		if (distance <= maxDistance) {
			latest_pos=latest_pos +1;
			return pos;
		}

		pos=positions.at(latest_pos -1);
		distance = pos->distance(lat, lon, 'K') * 1000; //meter로 환산
		if (distance <= maxDistance) {
			latest_pos=latest_pos -1;
			return pos;
		}
	}

	//찾지 못했으면 처음부터 모두 찾기
	for ( int i=0; i <positions.size(); i++) {
		pos=positions.at(i);
		distance = pos->distance(lat, lon, 'K') * 1000; //meter로 환산
		if (distance <= maxDistance) {
			latest_pos=i;
			return pos;
		}
	}
	return NULL;
}