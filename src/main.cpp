//======================================================================*/
//   Create Date: 2023/08/18
//   ClassName  : main
//   Author     : mhjin, julu1@naver.com
//   Class Def  : shuttleMonitor.exe
//======================================================================*/
#include "MainMonitor.h"
#include <ros/ros.h>
#include "init.h"
#include <signal.h>
#include <QApplication>
#include <QThread>
static void sig_core(int);

int main(int argc, char *argv[])
{
	ROSCONSOLE_AUTOINIT;

	signal(SIGSEGV, sig_core);
	signal(SIGBUS, sig_core);
	signal(SIGABRT, sig_core);


	log4cxx::LoggerPtr my_logger;
	my_logger=log4cxx::Logger::getLogger(ROSCONSOLE_DEFAULT_NAME);
	my_logger->setLevel(ros::console::g_level_lookup[ros::console::levels::Info]);
	ROS_DEBUG("LOG Level >> over Debug");
	ROS_INFO("LOG Level >> over Info");
	ROS_WARN("LOG Level >> over Warn");
	ROS_ERROR("LOG Level >> over Error");
	ROS_FATAL("LOG Level >> over Fatal");

	if( !ros::isInitialized() )
	{
		ROS_INFO("ros::Initializing....");
		ros::init( argc, argv, "shuttle_monitor", ros::init_options::AnonymousName );

		// if (!ros::master::check()) {
		// 	ROS_INFO("ros::core startind.....");
		// 	system("roscore &");
		// 	QThread::sleep(3);
		// }
	}

    QApplication a(argc, argv);
    MainMonitor w;
    w.show();
    return a.exec();
}


void sig_core(int signal_no) {
  ROS_FATAL("shuttleMonitor: abnormal exit by signal-%d", signal_no);

  exit(1);
}

