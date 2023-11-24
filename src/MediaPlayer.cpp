//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : MediaPlayer
//   Author     : mhjin julu1@naver.com
//   Class Def  :MediaPlayer
//======================================================================*/
#include "MediaPlayer.h"
#include <iostream>

MediaPlayer::MediaPlayer(ConfigLoader* _configLoader)
:configLoader(_configLoader) {
	player= new	QMediaPlayer();
	qPlayList= new QMediaPlaylist();
	for ( int i=0; i < 7; i++ ){
		//QFile * file=new QFile(tts_mp3[i]);

		qPlayList->addMedia(QUrl(tts_mp3[i]));
	}
	player->setPlaylist(qPlayList);
	qtimerMap.insert(States::FALL_DOWN, QTime::currentTime());
	qtimerMap.insert(States::HANDLE_CRASH, QTime::currentTime());
	qtimerMap.insert(States::WEAR_BELT, QTime::currentTime());
	qtimerMap.insert(States::SHARP_TURN, QTime::currentTime());
	qtimerMap.insert(States::SUDDEN_STOP, QTime::currentTime());
	qtimerMap.insert(States::FINISH, QTime::currentTime());

	ttsDelayMap=configLoader->getTtsTimeSleep();

}
MediaPlayer::~MediaPlayer() {
	delete qPlayList;
	delete player;
}
void MediaPlayer::playMedia(States states) {


	const QTime time=qtimerMap.value(states);
	QTime currTime=QTime::currentTime();
	int delayTime=ttsDelayMap.find(states).value();
	QTime addTime=time.addSecs(delayTime);

	ROS_INFO("mediaplayer called : %d::[%d]", states,  delayTime);
	if (currTime>= addTime ) {	//define에 세팅된 값
		ROS_INFO("mediaplayer play! : %d", states);
		qPlayList->setCurrentIndex(states);
		qPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
		player->play();
		qtimerMap.insert(states, currTime);
	}
}

