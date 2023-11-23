//======================================================================*/
//   Create Date: 2022/11/1
//   ClassName  : Define
//   Author     : mhjin julu1@naver.com
//   Class Def  : labename, sensor name등 기본 설정
//======================================================================*/
#ifndef DEFINES_H
#define DEFINES_H

#include <QString>
#include <QStringList>

enum States {
    ON_BOARDING=0,
    FALL_DOWN=1,
	HANDLE_CRASH,
	WEAR_BELT,
	SHARP_TURN,
	SUDDEN_STOP,
	FINISH
};

const QString  state_imgs[7] = {
	":img/images/on_boarding.jpg",
    ":img/images/fall_down.jpg",
    ":img/images/handle_crash.jpg",
	":img/images/wear_belt.jpg",
    ":img/images/sharp_turn.jpg",
    ":img/images/surdden_stop.jpg",
	":img/images/finish.jpg",
};


const QString  msg_imgs[7] = {
	":img/images/on_boarding_adult_icon.jpg", //사용안함
    ":img/images/fall_down_message.jpg",
    ":img/images/handle_crash_message.jpg",
	":img/images/wear_belt_message.jpg",
    ":img/images/sharp_turn_message.jpg",
    ":img/images/surdden_stop_message.jpg",
	":img/images/finish_message.jpg",
};

// const QString  tts_mp3[7] = {
// 	"/home/mhjin/project/catkin_ws/src/shuttle_monitor/src/tts/fall_down_message.mp3", //사용안함
//     "/home/mhjin/project/catkin_ws/src/shuttle_monitor/src/tts/fall_down_message.mp3",
//     "/home/mhjin/project/catkin_ws/src/shuttle_monitor/src/tts/handle_crash_message.mp3",
// 	"/home/mhjin/project/catkin_ws/src/shuttle_monitor/src/tts/wear_belt_message.mp3",
//     "/home/mhjin/project/catkin_ws/src/shuttle_monitor/src/tts/sharp_turn_message.mp3",
//     "/home/mhjin/project/catkin_ws/src/shuttle_monitor/src/tts/surdden_stop_message.mp3",
// 	"/home/mhjin/project/catkin_ws/src/shuttle_monitor/src/tts/finish_message.mp3",
// };


const QString  tts_mp3[7] = {
	"qrc:tts/fall_down_message.mp3", //사용안함
    "qrc:tts/fall_down_message.mp3",
    "qrc:tts/handle_crash_message.mp3",
	"qrc:tts/wear_belt_message.mp3",
    "qrc:tts/sharp_turn_message.mp3",
    "qrc:tts/surdden_stop_message.mp3",
	"qrc:tts/finish_message.mp3",
};

const QString state_msgs[7]= {
	"",
	"긴급상황! 쓰러짐 사고 발생",
	"긴급상황! 충돌 사고 발생",
	"",
	"급선회 사고 다발 지역입니다.",
	"급정거 사고 다발 지역입니다.",
	"운행이 종료되었습니다."
};

const QString msg_style[7]= {
	"background-color:rgb(242,249,255);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
	"background-color:rgb(255,240,217);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
	"background-color:rgb(255,240,217);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
	"background-color:rgb(242,249,255);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
	"background-color:rgb(255,240,217);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
	"background-color:rgb(255,240,217);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
	"background-color:rgb(242,249,255);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
};


// const QString msg_style[7]= {
// 	"background-color:rgb(242,249,255);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
// 	"background-color:rgb(255,240,217);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
// 	"background-color:rgb(255,240,217);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
// 	"background-color:rgb(242,249,255);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
// 	"background-color:rgb(255,240,217);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
// 	"background-color:rgb(255,240,217);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
// 	"background-color:rgb(242,249,255);border-radius:5px;border: 1px outset rgb(186, 189, 182);",
// };
#endif