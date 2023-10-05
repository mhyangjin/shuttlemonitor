//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : CarInfo
//   Author     : mhjin julu1@naver.com
//   Class Def  :CarInfo
//======================================================================*/
#include "CarInfo.h"
#include <iostream>

CarInfo::CarInfo(Ui::MainMonitor *_ui, QString carNo)
:ui(_ui) {
	ROS_INFO("CarInfo::CarInfo");
	ui->label_car_no_data->setText(carNo);
}
CarInfo::~CarInfo() {

}
void CarInfo::setDriveMode(QString mode) {
	ui->label_mode_data->setText(mode);
}
void CarInfo::setDriveState(QString state) {
	ui->label_state_data->setText(state);
}
void CarInfo::setEmergencyStop(QString stop) {
	ui->label_stop_data->setText(stop);
}
void CarInfo::setBettery(int remains) {
	string remainString = to_string(remains) + " %";
	ui->label_battery_data->setText(QString::fromStdString(remainString));
}
void CarInfo::setDriveSpeed(int speed) {
	string speedString = to_string(speed) + " Km/s";
	ui->label_speed_data->setText(QString::fromStdString(speedString));
}
