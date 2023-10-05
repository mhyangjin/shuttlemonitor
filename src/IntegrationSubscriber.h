//======================================================================*/
//   Create Date: 2023/08/126
//   ClassName  : IntegrationSubscriber
//   Author     : mhjin julu1@naver.com
//   Class Def  :IntegrationSubscriber
//======================================================================*/
#ifndef INTEGRATIONSUBSCRIBER_H
#define INTEGRATIONSUBSCRIBER_H
#include "init.h"
#include <QThread>
#include <std_msgs/String.h>
#include <ros/ros.h>
#include <ros/network.h>
#include <shuttle_monitor/IntergrateRecognition.h>
#include "CarInfo.h"
#include "StateManager.h"

class IntegrationSubscriber : public QThread {
public:
    IntegrationSubscriber(ros::MultiThreadedSpinner*, CarInfo*, StateManager*);
    void subscribeCallBack( const shuttle_monitor::IntergrateRecognition&);
    void run();

private:
    bool running;
    ros::Subscriber subscriber;
    ros::NodeHandle nodeHandle;
    ros::MultiThreadedSpinner* spiner;
    QString topicName="/iIntegrateRecognition";
	CarInfo* carInfo=NULL;
	StateManager* stateManager=NULL;
};

#endif