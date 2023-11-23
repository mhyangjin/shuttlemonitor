//======================================================================*/
//   Create Date: 2023/08/18
//   ClassName  : CanSubscriber
//   Author     : mhjin julu1@naver.com
//   Class Def  :
//======================================================================*/
#ifndef CANSUBSCRIBER_H
#define CANSUBSCRIBER_H
#include "init.h"
#include <QThread>
#include <std_msgs/String.h>
#include <ros/ros.h>
#include <ros/network.h>
#include <sensor_msgs/NavSatFix.h>
#include <shuttle_monitor/Can.h>
#include <shuttle_monitor/IntergrateRecognition.h>
#include "CarInfo.h"
#include "StateManager.h"
#include "MediaPlayer.h"
#include "ConfigLoader.h"
class CanSubscriber : public QThread {
public:
    CanSubscriber(ros::MultiThreadedSpinner*, CarInfo*, StateManager*,ConfigLoader*,
	MediaPlayer*);
    void subscribeCallBack( const shuttle_monitor::Can&);
    void run();
//signals:

private:
    bool running;
    ros::Subscriber subscriber;
    ros::NodeHandle nodeHandle;
    ros::MultiThreadedSpinner* spiner;
    QString topicName="/can";
	CarInfo* carInfo=NULL;
	StateManager* stateManager=NULL;
	MediaPlayer* mediaPlayer=NULL;
	ConfigLoader* configLoader=NULL;
};

#endif