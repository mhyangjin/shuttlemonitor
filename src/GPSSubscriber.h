//======================================================================*/
//   Create Date: 2023/08/126
//   ClassName  : GPSSubscriber
//   Author     : mhjin julu1@naver.com
//   Class Def  :GPSSubscriber
//======================================================================*/
#ifndef GPSSUBSCRIBER_H
#define GPSSUBSCRIBER_H
#include "init.h"
#include <QThread>
#include <std_msgs/String.h>
#include <sensor_msgs/NavSatFix.h>
#include <ros/ros.h>
#include <ros/network.h>
#include "PositionMapper.h"

class GPSSubscriber : public QThread {
public:
    GPSSubscriber(ros::MultiThreadedSpinner*, PositionMapper*);
    void subscribeCallBack(const sensor_msgs::NavSatFix::ConstPtr&);
    void run();

private:
    bool running;
    ros::Subscriber subscriber;
    ros::NodeHandle nodeHandle;
    ros::MultiThreadedSpinner* spiner;
    QString topicName="/fix";
	PositionMapper* positionManager=NULL;
};

#endif