

#ifndef MESSAGECONTROLS_H_
#define MESSAGECONTROLS_H_

#include <LiquidCrystal.h>

#include "MessageStructure.h"

extern LiquidCrystal_h lcd;


typedef enum {none,right,left,up,down,select} Button;

Button CheckButton();

void MainMenu();

void ChatSelectMenu(pViewer View,int chatIndex);

int ViewChat(pChat chat);

#endif