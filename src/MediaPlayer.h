//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : CarInfo
//   Author     : mhjin julu1@naver.com
//   Class Def  :CarInfo
//======================================================================*/
#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMap>
#include <QTime>
#include "init.h"
#include "ConfigLoader.h"
class MediaPlayer {
public:
	MediaPlayer(ConfigLoader*);

	void playMedia(States states);

private:
	QMediaPlayer *player=NULL;
	QMap<States, QTime> qtimerMap;
	QMediaPlaylist* qPlayList=NULL;
	ConfigLoader* configLoader=NULL;
	QMap<States, int> ttsDelayMap;
};
#endif // MEDIAPLAYER_H
