//======================================================================*/
//   Create Date: 2022/11/17
//   ClassName  : YmlLoader
//   Author     : mhjin julu1@naver.com
//   Class Def  : yml file loader
//======================================================================*/
#include "YmlLoader.h"

YAML::Node YmlLoader::loadConfig( QString rvizFileName) {
    YAML::Node _rootNode=YAML::LoadFile(qPrintable(rvizFileName));
    //printNodes(&_rootNode);
    // loadNodes(&_rootNode);
	return _rootNode;
}

void YmlLoader::loadNodes(YAML::Node* node) {
    // for(YAML::const_iterator it=node->begin(); it!=node->end(); it++) {
    //     YAML::Node _node=it->first;
    //     YAML::Node _value=it->second;
    //     string nodeStr=_node.as<string>();
    //     string valueStr;
    //     switch ( _value.Type()) {
    //         case YAML::NodeType::Scalar:
    //             valueStr=_value.as<string>();
    //             config->mapSetValue(QString::fromStdString(nodeStr),QString::fromStdString(valueStr));
    //             break;
    //         case YAML::NodeType::Sequence:
    //             for (size_t i=0; i< _value.size(); i++) {
    //                 YAML::Node arrayValue=_value[i];
    //                 if (arrayValue.Type() == YAML::NodeType::Scalar) {
    //                     valueStr=arrayValue.as<string>();
    //                 }
    //                 else
    //                     loadNodes(&arrayValue, &seqConfig);
    //             }
    //             break;
    //         case YAML::NodeType::Map:
    //             childConfig=config->mapMakeChild(QString::fromStdString(nodeStr));
    //             loadNodes(&_value, &childConfig);
    //             break;
    //         default :
    //             ROS_WARN("YmlLoader::loadNodes:NONE:Type is not valid!");
    //     }
    // }
}

void YmlLoader::printNodes(YAML::Node* node) {
    for(YAML::const_iterator it=node->begin(); it!=node->end(); it++) {
        YAML::Node _node=it->first;
        YAML::Node value=it->second;
        cout<<_node.as<string>()<< ": ";
        switch ( value.Type()) {
            case YAML::NodeType::Scalar:
                cout << "(S)"<<value.as<string>()<<endl;
                break;
            case YAML::NodeType::Sequence:
                cout <<"  - ";
                for (size_t i=0; i< value.size(); i++) {
                    YAML::Node arrayValue=value[i];
                    if (arrayValue.Type() == YAML::NodeType::Scalar) {
                        cout << "(A)"<<arrayValue.as<string>()<<endl;
                    }
                    else
                        printNodes(&arrayValue);
                }
                break;
            case YAML::NodeType::Map:
                printNodes(&value);
                break;
            default :
                cout <<"NONE" << endl;
        }
    }
}


