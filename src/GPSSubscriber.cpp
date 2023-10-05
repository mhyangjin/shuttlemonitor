//======================================================================*/
//   Create Date: 2023/08/26
//   ClassName  : GPSSubscriber
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#include "GPSSubscriber.h"
#include <sstream>

GPSSubscriber::GPSSubscriber(ros::MultiThreadedSpinner* _spiner,PositionMapper* _positionManager )
:spiner(_spiner),
positionManager(_positionManager)
{
    subscriber = nodeHandle.subscribe(qPrintable(topicName), 10000, &GPSSubscriber::subscribeCallBack,this );
    this->start();
}

void GPSSubscriber::run() {
    spiner->spin();
}
void GPSSubscriber::subscribeCallBack(const sensor_msgs::NavSatFix::ConstPtr& msg) {
	ROS_INFO("SUTTTLE_MONITOR::GPSSubscriber get gps data (%f, %f)", msg -> latitude,msg -> longitude );
	positionManager->setPosition( msg->latitude, msg->longitude );
 }
