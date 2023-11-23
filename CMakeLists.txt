cmake_minimum_required(VERSION 3.0.2)
project(shuttle_monitor)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  sensor_msgs
  std_msgs
)


add_message_files(
  FILES
  Ps_recog.msg
  IntergrateRecognition.msg
  Can.msg
  Car.msg
  Gps.msg
  )

generate_messages(
  DEPENDENCIES
  std_msgs)


# test를 위한 topic sender임
catkin_install_python(
  PROGRAMS
  script/can_sender.py
  script/Integrate_Sender.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


####################################################
# QT Environment
###################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets REQUIRED)

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
#QT5_WARP_UI(QT_FORMS_HPP ${QT_FORMS})

include_directories(
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Multimedia_INCLUDE_DIRS}
  ${Qt5MultimediaWidgets_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

add_definitions( -std=c++11 -fPIC)


##############################################################################
# Sources
##############################################################################
set( QT_SOURCES
  src/main.cpp
  src/defines.h
  src/init.h
  src/MainMonitor.h
  src/MainMonitor.cpp
  src/MainMonitor.ui
  src/StateManager.h
  src/StateManager.cpp
  src/CanSubscriber.h
  src/CanSubscriber.cpp
  src/IntegrationSubscriber.h
  src/IntegrationSubscriber.cpp
  src/CarInfo.h
  src/CarInfo.cpp
  src/GPSSubscriber.h
  src/GPSSubscriber.cpp
  src/PositionMapper.h
  src/PositionMapper.cpp
  src/Position.h
  src/Position.cpp
  src/MediaPlayer.h
  src/MediaPlayer.cpp
  src/images.qrc
  src/tts.qrc
  src/ConfigLoader.h
  src/ConfigLoader.cpp
  )

#set (CONFIG scripts/config.yml)
## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)
##############################################################################
# DAQ run scrpit. config parameters
##############################################################################
#catkin_install_python( PROGRAMS
#scrpits/runDAQ.py
#)

##############################################################################
# Binaries
##############################################################################
add_executable(${PROJECT_NAME} ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP} ${FILES} )

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::Multimedia
  Qt5::MultimediaWidgets
  libyaml-cpp.so
)
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  )