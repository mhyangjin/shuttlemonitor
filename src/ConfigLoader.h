//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : ConfigLoader
//   Author     : mhjin julu1@naver.com
//   Class Def  : ConfigLoader
//======================================================================*/
#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include "init.h"
#include <yaml-cpp/yaml.h>
#include <QMap>
#include <QString>
#include <QList>
#include "Position.h"

class ConfigLoader {
public:
    ConfigLoader();
    ~ConfigLoader();
    int getPosisionResolution();
    QMap<States, int> getTtsTimeSleep();
    QList<Position*> getPositions();
	QString getCarNo();
private:
    void loadConfig();
private:
    const string configFileName="./config.yml";
	int positionResolution;
    QMap<States, int> ttsTimeSleep;
	QList<Position*> positions;
	QString carNo;
};

#endif
