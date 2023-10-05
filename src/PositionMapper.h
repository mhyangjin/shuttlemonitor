//======================================================================*/
//   Create Date: 2023/08/18
//   ClassName  : PositionMapper
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#ifndef POSITIONMAPPER_H
#define POSITIONMAPPER_H
#include "init.h"
#include "Position.h"

class PositionMapper {
public:
    PositionMapper(Ui::MainMonitor *);
	~PositionMapper();

	void setPosition(double lat, double lon);

private:
	Position* findclosedPosition(double, double);

	Ui::MainMonitor *ui;
	QList<Position*> positions;
	int latest_pos;
	int maxDistance=5; //버스 아이콘 위치를 조정할 거리(미터),5미터 안에 위치하면 아이콘을 옮긴다
};

#endif