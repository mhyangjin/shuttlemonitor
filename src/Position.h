//======================================================================*/
//   Create Date: 2023/08/18
//   ClassName  : Position
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#ifndef POSITION_H
#define POSITION_H
#include "init.h"
#include <math.h>

class Position {
	public :
		Position(double lat, double lon, int x, int y);
		double distance(double lat2, double lon2, char unit);
		int getX();
		int getY();
	private :
	double deg2rad(double);
	double rad2deg(double);
		double latitude;
		double longitude;
		int x;
		int y;
};


#endif