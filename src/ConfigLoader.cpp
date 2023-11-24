//======================================================================*/
//   Create Date: 2022/11/15
//   ClassName  : Daqmain
//   Author     : mhjin julu1@naver.com
//   Class Def  : ConfigLoader
//======================================================================*/
#include "ConfigLoader.h"
#include "YmlLoader.h"
#include <string.h>
#include <fstream>
#include "yaml-cpp/yaml.h"

ConfigLoader::ConfigLoader(){

    try {
		YAML::Node _rootNode=YAML::LoadFile(configFileName);
        YAML::Node launchNode=_rootNode["gpspos"];

        for (size_t i=0; i< launchNode.size(); i++) {
            double lat=std::stod(launchNode[i]["Lat"].as<string>());
			double log=std::stod(launchNode[i]["Lon"].as<string>());
            int ui_x=std::stoi(launchNode[i]["UIx"].as<string>());
			int ui_y=std::stoi(launchNode[i]["UIy"].as<string>());
			QString posinfo=QString::fromStdString(launchNode[i]["pos"].as<string>());
			ROS_INFO("lat: %f",lat );
			ROS_INFO("ui_x: %d",ui_x );
			positions.push_back( new Position(lat, log, ui_x,ui_y,posinfo));
        }

		launchNode=_rootNode["tts_time_sleep"];
		int fall_down	=std::stoi(launchNode["fall_down"].as<string>());
		int finish		=std::stoi(launchNode["finish"].as<string>());
		int handle_crash=std::stoi(launchNode["handle_crash"].as<string>());
		int sharp_turn	=std::stoi(launchNode["sharp_turn"].as<string>());
		int surdden_stop=std::stoi(launchNode["surdden_stop"].as<string>());
		int wear_belt	=std::stoi(launchNode["wear_belt"].as<string>());
		ROS_INFO("surdden_stop: %d",surdden_stop );
		ttsTimeSleep.insert(States::FALL_DOWN, 		fall_down);
		ttsTimeSleep.insert(States::HANDLE_CRASH, 	handle_crash);
		ttsTimeSleep.insert(States::WEAR_BELT, 		wear_belt);
		ttsTimeSleep.insert(States::SHARP_TURN, 		sharp_turn);
		ttsTimeSleep.insert(States::SUDDEN_STOP, 	SUDDEN_STOP);
		ttsTimeSleep.insert(States::FINISH, 			finish);

		launchNode=_rootNode["position_resolution"];
		ROS_INFO("positionResolution:====");
		positionResolution	=std::stoi(launchNode["distance"].as<string>());
		ROS_INFO("positionResolution: %d",positionResolution );
		launchNode=_rootNode["carinfo"];
		carNo=QString::fromStdString(launchNode["carno"].as<string>());
    }
    catch (const YAML::BadFile& e) {
        ROS_INFO("Configfille is not exist. generate default configfile ");
    }
    catch ( ...) {
        ROS_INFO("Unkown Exception. generate default configfile ");
    }
}

ConfigLoader::~ConfigLoader() {
for (auto iter=positions.begin(); iter!=positions.end(); iter++) {
        delete *iter;
    }
}

QString ConfigLoader::getCarNo() {
	return carNo;
}
int ConfigLoader::getPosisionResolution() {
	return positionResolution;

}
QMap<States, int> ConfigLoader::getTtsTimeSleep() {
	return ttsTimeSleep;
}
QList<Position*> ConfigLoader::getPositions() {
	return positions;
}