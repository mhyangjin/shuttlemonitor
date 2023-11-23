//======================================================================*/
//   Create Date: 2022/11/17
//   ClassName  : YmlLoader
//   Author     : mhjin julu1@naver.com
//   Class Def  : yml file loader
//======================================================================*/
#ifndef YMLLOADER_H
#define YMLLOADER_H
#include "init.h"
#include <QString>
#include <yaml-cpp/yaml.h>

class YmlLoader {
public:
    static YAML::Node loadConfig( QString);
    static void printNodes(YAML::Node*);
    static void loadNodes(YAML::Node*);


};
#endif