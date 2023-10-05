//======================================================================*/
//   Create Date: 2023/08/18
//   ClassName  : PositionMapper
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#include "PositionMapper.h"

PositionMapper::PositionMapper(Ui::MainMonitor *_ui)
:ui(_ui){
	positions.push_back( new Position(34.752818, 127.749523, 200,190));
	positions.push_back( new Position(34.752176, 127.750285, 250,220));
	positions.push_back( new Position(34.750036, 127.748405, 220,280));
	positions.push_back( new Position(34.748999, 127.750010, 280,330));
	positions.push_back( new Position(34.747901, 127.750081, 290,410));
	positions.push_back( new Position(34.746908, 127.751485, 340,460));
	positions.push_back( new Position(34.746076, 127.751564, 330,540));
	positions.push_back( new Position(34.744949, 127.750406, 290,570));
	positions.push_back( new Position(34.744319, 127.751223, 320,610));
	positions.push_back( new Position(34.743808, 127.751971, 330,610));
	positions.push_back( new Position(34.743167, 127.753864, 360,650));
	positions.push_back( new Position(34.742376, 127.754984, 430,690));
	positions.push_back( new Position(34.745423, 127.749120, 220,540));
	positions.push_back( new Position(34.746156, 127.748219, 180,470));
	positions.push_back( new Position(34.747737, 127.746627, 140,410));
	positions.push_back( new Position(34.748830, 127.747477, 180,350));

	latest_pos = 0;
	ui->label_car->move(200,190);
}

PositionMapper::~PositionMapper(){}

void PositionMapper::setPosition(double lat, double lon) {
	Position* pos=findclosedPosition(lat, lon);
	if ( pos != NULL) {
		ui->label_car->move(pos->getX(),pos->getY());
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
	return pos;
}