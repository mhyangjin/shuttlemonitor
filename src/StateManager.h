//======================================================================*/
//   Create Date: 2023/08/15
//   ClassName  : StateManager
//   Author     : mhjin julu1@naver.com
//   Class Def  :StateManager
//======================================================================*/
#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <QMainWindow>
#include <QPixmap>
#include "init.h"

class StateManager {
public:
	StateManager(Ui::MainMonitor *,QString);
	~StateManager();
	void changeOnBoadingReset();
	void changeOnBoading(int , int , int, int );
    void changeFinish();
    void changeFallDown();
    void changeHandleCrash();
    void changeSharpTurn();
    void changeSurddenStop();
    void changeWearBelt();
private:
	void setOnBoadingEnable(bool);
	void changeManCount(int , int , int, int);

    Ui::MainMonitor *ui;
	QPixmap state_pixmaps[7];
	QPixmap message_pixmaps[7];
	int adult_female=0;
	int adult_male=0;
	int child_female=0;
	int child_male=0;

};
#endif
