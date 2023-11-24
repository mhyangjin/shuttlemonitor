//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : StateManager
//   Author     : mhjin julu1@naver.com
//   Class Def  :StateManager
//======================================================================*/
#include "StateManager.h"
#include <iostream>

StateManager::StateManager(Ui::MainMonitor *_ui, QString carNo)
:ui(_ui) {
	ROS_INFO("StatManager::StateManager %s", qPrintable(carNo));
	for ( int i=0; i<7; i++) {
		ROS_INFO("laod images %s", qPrintable(state_imgs[i]));
		state_pixmaps[i].load(state_imgs[i]);
	}

	for ( int i=0; i<7; i++) {
		message_pixmaps[i].load(msg_imgs[i]);
	}
	ui->label_car_no_data->setText(carNo);
	setOnBoadingEnable(true);

}

StateManager::~StateManager() {
	ROS_INFO("StateManager::~StateManager");
}
//----------sate board
//label_state_img=on_blarding.jpg
//label_state_msg=총 00 명 탑승 중
//----------message board
//label_man_img show
void StateManager::changeOnBoadingReset() {
	changeManCount(adult_male, adult_female,child_male, child_female );
}
void StateManager::changeOnBoading(	int adult_male_count,
									int adult_female_count,
									int child_male_count,
									int child_female_count){

	if ( adult_male == adult_male_count
		&& adult_female == adult_female_count
		&& child_male == child_male_count
		&& child_female == child_female_count) {
		return;
	}
	else {
		adult_male=adult_male_count;
		adult_female=adult_female_count;
		child_male=child_male_count;
		child_female=child_female_count;

		changeManCount(adult_male, adult_female,child_male, child_female );
	}

}

void StateManager::changeManCount(	int adult_male_count,
									int adult_female_count,
									int child_male_count,
									int child_female_count)   {

	ROS_INFO("StateManager::changeOnBoading");
	int adult_count=adult_male_count + adult_female_count;
	int child_count=child_male_count + child_female_count;
	int customers=adult_count + child_count;

	//sate board
	string customers_string="총 " + to_string(customers) + " 탑승 중";
	ui->label_state_img->setPixmap(state_pixmaps[::ON_BOARDING]);
	ui->label_state_msg->setText(QString::fromStdString(customers_string));

	//message board
	ui->label_back_msg->setStyleSheet(msg_style[States::ON_BOARDING]);
	string adult_string = "성인 " + to_string(adult_count) + " 명";
	string adult_male_string = "남 " + to_string(adult_male_count) + " 명";
	string adult_female_string = "여 " + to_string(adult_female_count) + " 명";
	ui->label_adult_count->setText(QString::fromStdString(adult_string));
	ui->label_adult_male->setText(QString::fromStdString(adult_male_string));
	ui->label_adult_female->setText(QString::fromStdString(adult_female_string));

	string child_string = "유아 " + to_string(child_count) + " 명";
	string child_male_string = "남 " + to_string(child_male_count) + " 명";
	string child_female_string = "여 " + to_string(child_female_count) + " 명";

	ui->label_child_count->setText(QString::fromStdString(child_string));
	ui->label_child_male->setText(QString::fromStdString(child_male_string));
	ui->label_child_female->setText(QString::fromStdString(child_female_string));
	setOnBoadingEnable(true);
}

void StateManager::changeFinish(){
	ROS_INFO("StateManager::changeFinish");
	//sate board
	ui->label_state_img->setPixmap(state_pixmaps[States::FINISH]);
	ui->label_state_msg->setText(state_msgs[States::FINISH]);
	//message board
	ui->label_back_msg->setStyleSheet(msg_style[States::FINISH]);
	ui->label_warn_img->setPixmap(msg_imgs[States::FINISH]);
	setOnBoadingEnable(false);
}

void StateManager::changeFallDown(){
	ROS_INFO("StateManager::changeFallDown");
	//sate board
	ui->label_state_img->setPixmap(state_pixmaps[States::FALL_DOWN]);
	ui->label_state_msg->setText(state_msgs[States::FALL_DOWN]);
	//message board
	ui->label_back_msg->setStyleSheet(msg_style[States::FALL_DOWN]);
	ui->label_warn_img->setPixmap(msg_imgs[States::FALL_DOWN]);
	setOnBoadingEnable(false);
}

void StateManager::changeHandleCrash(){
	ROS_INFO("StateManager::changeHandleCrash");
	//sate board
	ui->label_state_img->setPixmap(state_pixmaps[States::HANDLE_CRASH]);
	ui->label_state_msg->setText(state_msgs[States::HANDLE_CRASH]);
	//message board
	ui->label_back_msg->setStyleSheet(msg_style[States::HANDLE_CRASH]);
	ui->label_warn_img->setPixmap(msg_imgs[States::HANDLE_CRASH]);
	setOnBoadingEnable(false);
}

void StateManager::changeSharpTurn(){
	ROS_INFO("StateManager::changeSharpTurn");
	//sate board
	ui->label_state_img->setPixmap(state_pixmaps[States::SHARP_TURN]);
	ui->label_state_msg->setText(state_msgs[States::SHARP_TURN]);
	//message board
	ui->label_back_msg->setStyleSheet(msg_style[States::SHARP_TURN]);
	ui->label_warn_img->setPixmap(msg_imgs[States::SHARP_TURN]);
	setOnBoadingEnable(false);
}

void StateManager::changeSurddenStop(){
	ROS_INFO("StateManager::changeSurddenStop");
	//sate board
	ui->label_state_img->setPixmap(state_pixmaps[States::SUDDEN_STOP]);
	ui->label_state_msg->setText(state_msgs[States::SUDDEN_STOP]);
	//message board
	ui->label_back_msg->setStyleSheet(msg_style[States::SUDDEN_STOP]);
	ui->label_warn_img->setPixmap(msg_imgs[States::SUDDEN_STOP]);
	setOnBoadingEnable(false);
}

void StateManager::changeWearBelt(){
	ROS_INFO("StateManager::changeWearBelt");
	//sate board
	ui->label_state_img->setPixmap(state_pixmaps[States::WEAR_BELT]);
	ui->label_state_msg->setText(state_msgs[States::WEAR_BELT]);
	//message board
	ui->label_back_msg->setStyleSheet(msg_style[States::WEAR_BELT]);
	ui->label_warn_img->setPixmap(msg_imgs[States::WEAR_BELT]);
	setOnBoadingEnable(false);
}

void StateManager::setOnBoadingEnable(bool enable) {
	if (enable) {
		ui->label_warn_img->hide();
		ui->label_adult_img->show();
		ui->label_adult_count->show();
		ui->label_adult_male->show();
		ui->label_adult_female->show();
		ui->label_child_img->show();
		ui->label_child_count->show();
		ui->label_child_male->show();
		ui->label_child_female->show();

	}
	else {
		ui->label_warn_img->show();
		ui->label_adult_img->hide();
		ui->label_adult_count->hide();
		ui->label_adult_male->hide();
		ui->label_adult_female->hide();
		ui->label_child_img->hide();
		ui->label_child_count->hide();
		ui->label_child_male->hide();
		ui->label_child_female->hide();
	}
}