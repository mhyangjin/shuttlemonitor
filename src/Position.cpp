//======================================================================*/
//   Create Date: 2023/08/18
//   ClassName  : Position
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#include "Position.h"

#define pi 3.14159265358979323846

Position::Position(double _lat, double _lon, int _x, int _y) {
	latitude=_lat;
	longitude=_lon;
	x=_x;
	y=_y;
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function prototypes                                           :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

double Position::distance(double lat2, double lon2, char unit) {
	double lat1=latitude;
	double lon1=longitude;

  double theta, dist;
  if ((lat1 == lat2) && (lon1 == lon2)) {
    return 0;
  }
  else {
    theta = lon1 - lon2;
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    switch(unit) {
      case 'M':
        break;
      case 'K':
        dist = dist * 1.609344;
        break;
      case 'N':
        dist = dist * 0.8684;
        break;
    }
    return (dist);
  }
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double Position::deg2rad(double deg) {
  return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double Position::rad2deg(double rad) {
  return (rad * 180 / pi);
}

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}