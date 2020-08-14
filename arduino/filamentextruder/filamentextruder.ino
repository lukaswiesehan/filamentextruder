//Include libraries
#include "Nextion.h"

//Define defaults
#define NOMINAL_TEMP 165
#define WINDUP_SPEED 3.00
#define SPOOL_WIDTH 73
#define SPOOL_INNER_DIAMETER 100
#define SPOOL_OUTER_DIAMETER 200

//Declare Extruder FSM states
enum states {initialize, refStep, idle, settings, heatup, ready, extrude, windUp};
states currentState = initialize;

//Declare extruder process variables
int nominalTemp = NOMINAL_TEMP;
int actualTemp = 0;
float windUpSpeed = WINDUP_SPEED;
int spoolWidth = SPOOL_WIDTH;
int spoolInnerDiameter = SPOOL_INNER_DIAMETER;
int spoolOuterDiameter = SPOOL_OUTER_DIAMETER;

//Declare Nextion objects
//Page 0: init
NexPage initPage(0, 0, "init");
NexPicture init_pInitSensors(0, 6, "pInitSensors");
NexPicture init_pInitPID(0, 7, "pInitPID");
NexPicture init_pInitMotors(0, 8, "pInitMotors");
NexPicture init_pRefStepper(0, 9, "pRefStepper");
//Page 1: idle
NexPage idlePage(1, 0, "idle");
NexButton idle_bHeatUp(1, 3, "bHeatUp");
NexButton idle_bSettings(1, 4, "bSettings");
//Page 2: heatup
NexPage heatupPage(2, 0, "heatup");
NexButton heatup_bCooldown(2, 2, "bCooldown");
NexButton heatup_bStartExt(2, 13, "bStartExt");
NexText heatup_tReady(2, 15, "tReady");
NexButton heatup_bTempMinus5(2, 8, "bTempMinus5");
NexButton heatup_bTempMinus1(2, 10, "bTempMinus1");
NexButton heatup_bTempPlus1(2, 11, "bTempPlus1");
NexButton heatup_bTempPlus5(2, 9, "bTempPlus5");
NexNumber heatup_nNominalTemp(2, 16, "nNominalTemp");
NexNumber heatup_nActualTemp(2, 4, "nActualTemp");
NexProgressBar heatup_jTempBar(2, 3, "jTempBar");
//Page 3: extrude
NexPage extrudePage(3, 0, "extrude");
NexButton extrude_bCooldown(3, 2, "bCooldown");
NexButton extrude_bPauseExt(3, 11, "bPauseExt");
NexButton extrude_bStartWind(3, 10, "bStartWind");
NexButton extrude_bTempMinus1(3, 8, "bTempMinus1");
NexButton extrude_bTempPlus1(3, 9, "bTempPlus1");
NexNumber extrude_nNominalTemp(3, 14, "nNominalTemp");
NexNumber extrude_nActualTemp(3, 4, "nActualTemp");
NexProgressBar extrude_jTempBar(3, 3, "jTempBar");
//Page 4: windup
NexPage windupPage(4, 0, "windup");
NexButton windup_bCooldown(4, 2, "bCooldown");
NexButton windup_bPauseWind(4, 10, "bPauseWind");
NexButton windup_bTempMinus1(4, 8, "bTempMinus1");
NexButton windup_bTempPlus1(4, 9, "bTempPlus1");
NexButton windup_bSpeedMin01(4, 14, "bSpeedMin01");
NexButton windup_bSpeedMin001(4, 15, "bSpeedMin001");
NexButton windup_bSpeedPlus01(4, 12, "bSpeedPlus01");
NexButton windup_bSpeedPlus001(4, 13, "bSpeedPlus001");
NexNumber windup_nNominalTemp(4, 10, "nNominalTemp");
NexText windup_tSpeed(4, 16, "tSpeed");
NexNumber windup_nActualTemp(4, 4, "nActualTemp");
NexProgressBar windup_jTempBar(4, 3, "jTempBar");
//Page 5: settings
NexPage settingsPage(5, 0, "settings");
NexButton settings_bSave(5, 33, "bSave");
NexButton settings_bTempMinus5(5, 2, "bTempMinus5");
NexButton settings_bTempMinus1(5, 4, "bTempMinus1");
NexButton settings_bTempPlus1(5, 5, "bTempPlus1");
NexButton settings_bTempPlus5(5, 3, "bTempPlus5");
NexButton settings_bSpeedMin01(5, 9, "bSpeedMin01");
NexButton settings_bSpeedMin001(5, 11, "bSpeedMin001");
NexButton settings_bSpeedPlus001(5, 12, "bSpeedPlus001");
NexButton settings_bSpeedPlus01(5, 10, "bSpeedPlus01");
NexButton settings_bWidthMinus5(5, 15, "bWidthMinus5");
NexButton settings_bWidthMinus1(5, 17, "bWidthMinus1");
NexButton settings_bWidthPlus1(5, 18, "bWidthPlus1");
NexButton settings_bWidthPlus5(5, 16, "bWidthPlus5");
NexButton settings_bInnerMinus5(5, 21, "bInnerMinus5");
NexButton settings_bInnerMinus1(5, 23, "bInnerMinus1");
NexButton settings_bInnerPlus1(5, 24, "bInnerPlus1");
NexButton settings_bInnerPlus5(5, 22, "bInnerPlus5");
NexButton settings_bOuterMinus5(5, 27, "bOuterMinus5");
NexButton settings_bOuterMinus1(5, 29, "bOuterMinus1");
NexButton settings_bOuterPlus1(5, 30, "bOuterPlus1");
NexButton settings_bOuterPlus5(5, 28, "bOuterPlus5");
NexNumber settings_nTemp(5, 7, "nTemp");
NexText settings_tSpeed(5, 14, "tSpeed");
NexText settings_tWidth(5, 20, "tWidth");
NexText settings_tInnerDia(5, 26, "tInnerDia");
NexText settings_tOuterDia(5, 32, "tOuterDia");

//Create touch event list
NexTouch *nexListenList[] = {
  //Page 1: idle
  &idle_bHeatUp,
  &idle_bSettings,
  //Page 2: heatup
  &heatup_bCooldown,
  &heatup_bStartExt,
  &heatup_tReady,
  &heatup_bTempMinus5,
  &heatup_bTempMinus1,
  &heatup_bTempPlus1,
  &heatup_bTempPlus5,
  //Page 3: extrude
  &extrude_bCooldown,
  &extrude_bPauseExt,
  &extrude_bStartWind,
  &extrude_bTempMinus1,
  &extrude_bTempPlus1,
  //Page 4: windup
  &windup_bCooldown,
  &windup_bPauseWind,
  &windup_bTempMinus1,
  &windup_bTempPlus1,
  &windup_bSpeedMin01,
  &windup_bSpeedMin001,
  &windup_bSpeedPlus01,
  &windup_bSpeedPlus001,
  //Page 5: settings
  &settings_bSave,
  &settings_bTempMinus5,
  &settings_bTempMinus1,
  &settings_bTempPlus1,
  &settings_bTempPlus5,
  &settings_bSpeedMin01,
  &settings_bSpeedMin001,
  &settings_bSpeedPlus001,
  &settings_bSpeedPlus01,
  &settings_bWidthMinus5,
  &settings_bWidthMinus1,
  &settings_bWidthPlus1,
  &settings_bWidthPlus5,
  &settings_bInnerMinus5,
  &settings_bInnerMinus1,
  &settings_bInnerPlus1,
  &settings_bInnerPlus5,
  &settings_bOuterMinus5,
  &settings_bOuterMinus1,
  &settings_bOuterPlus1,
  &settings_bOuterPlus5,
  NULL
};

//Define button callback functions
//Page 1: idle
void idle_bHeatup_callback() {
  heatupPage.show();
  currentState = heatup;
  heatup_nNominalTemp.setValue(nominalTemp);
  dbSerialPrintln("currentState = heatup");
}
void idle_bSettings_callback() {
  settingsPage.show();
  currentState = settings;
  settings_nTemp.setValue(nominalTemp);
  settings_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
  settings_tWidth.setText(String(spoolWidth) + "mm");
  settings_tInnerDia.setText(String(spoolInnerDiameter) + "mm");
  settings_tOuterDia.setText(String(spoolOuterDiameter) + "mm");
  dbSerialPrintln("currentState = settings");
}
//Page 2: heatup
void heatup_bCooldown_callback() {
  idlePage.show();
  currentState = idle;
  dbSerialPrintln("currentState = idle");
}
void heatup_bStartExt_callback() {
  extrudePage.show();
  currentState = extrude;
  extrude_nNominalTemp.setValue(nominalTemp);
  dbSerialPrintln("currentState = extrude");
}
void heatup_bTempMinus5_callback() {
  nominalTemp -= 5;
  heatup_nNominalTemp.setValue(nominalTemp);
}
void heatup_bTempMinus1_callback() {
  nominalTemp -= 1;
  heatup_nNominalTemp.setValue(nominalTemp);
}
void heatup_bTempPlus1_callback() {
  nominalTemp += 1;
  heatup_nNominalTemp.setValue(nominalTemp);
}
void heatup_bTempPlus5_callback() {
  nominalTemp += 5;
  heatup_nNominalTemp.setValue(nominalTemp);
}
//Page 3: extrude
void extrude_bCooldown_callback() {
  idlePage.show();
  currentState = idle;
  dbSerialPrintln("currentState = idle");
}
void extrude_bPauseExt_callback() {
  heatupPage.show();
  currentState = heatup;
  heatup_nNominalTemp.setValue(nominalTemp);
  dbSerialPrintln("currentState = heatup");
}
void extrude_bStartWind_callback() {
  windupPage.show();
  currentState = windUp;
  windup_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
  windup_nNominalTemp.setValue(nominalTemp);
  dbSerialPrintln("currentState = windUp");
}
void extrude_bTempMinus1_callback() {
  nominalTemp -= 1;
  extrude_nNominalTemp.setValue(nominalTemp);
}
void extrude_bTempPlus1_callback() {
  nominalTemp += 1;
  extrude_nNominalTemp.setValue(nominalTemp);
}
//Page 4: windup
void windup_bCooldown_callback() {
  idlePage.show();
  currentState = idle;
  dbSerialPrintln("currentState = idle");
}
void windup_bPauseWind_callback() {
  extrudePage.show();
  currentState = extrude;
  extrude_nNominalTemp.setValue(nominalTemp);
  dbSerialPrintln("currentState = extrude");
}
void windup_bTempMinus1_callback() {
  nominalTemp -= 1;
  windup_nNominalTemp.setValue(nominalTemp);
}
void windup_bTempPlus1_callback() {
  nominalTemp += 1;
  windup_nNominalTemp.setValue(nominalTemp);
}
void windup_bSpeedMin01_callback() {
  windUpSpeed -= 0.1;
  windup_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
}
void windup_bSpeedMin001_callback() {
  windUpSpeed -= 0.01;
  windup_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
}
void windup_bSpeedPlus01_callback() {
  windUpSpeed += 0.1;
  windup_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
}
void windup_bSpeedPlus001_callback() {
  windUpSpeed += 0.01;
  windup_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
}
//Page 5: settings
void settings_bSave_callback() {
  idlePage.show();
  currentState = idle;
  dbSerialPrintln("currentState = idle");
}
void settings_bTempMinus5_callback() {
  nominalTemp -= 5;
  settings_nTemp.setValue(nominalTemp);
}
void settings_bTempMinus1_callback() {
  nominalTemp -= 1;
  settings_nTemp.setValue(nominalTemp);
}
void settings_bTempPlus1_callback() {
  nominalTemp += 1;
  settings_nTemp.setValue(nominalTemp);
}
void settings_bTempPlus5_callback() {
  nominalTemp += 5;
  settings_nTemp.setValue(nominalTemp);
}
void settings_bSpeedMin01_callback() {
  windUpSpeed -= 0.1;
  settings_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
}
void settings_bSpeedMin001_callback() {
  windUpSpeed -= 0.01;
  settings_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
}
void settings_bSpeedPlus001_callback() {
  windUpSpeed += 0.01;
  settings_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
}
void settings_bSpeedPlus01_callback() {
  windUpSpeed += 0.1;
  settings_tSpeed.setText(String(windUpSpeed).substring(0, 4) + " RPM");
}
void settings_bWidthMinus5_callback() {
  spoolWidth -= 5;
  settings_tWidth.setText(String(spoolWidth) + "mm");
}
void settings_bWidthMinus1_callback() {
  spoolWidth -= 1;
  settings_tWidth.setText(String(spoolWidth) + "mm");
}
void settings_bWidthPlus1_callback() {
  spoolWidth += 1;
  settings_tWidth.setText(String(spoolWidth) + "mm");
}
void settings_bWidthPlus5_callback() {
  spoolWidth += 5;
  settings_tWidth.setText(String(spoolWidth) + "mm");
}
void settings_bInnerMinus5_callback() {
  spoolInnerDiameter -= 5;
  settings_tInnerDia.setText(String(spoolInnerDiameter) + "mm");
}
void settings_bInnerMinus1_callback() {
  spoolInnerDiameter -= 1;
  settings_tInnerDia.setText(String(spoolInnerDiameter) + "mm");
}
void settings_bInnerPlus1_callback() {
  spoolInnerDiameter += 1;
  settings_tInnerDia.setText(String(spoolInnerDiameter) + "mm");
}
void settings_bInnerPlus5_callback() {
  spoolInnerDiameter += 5;
  settings_tInnerDia.setText(String(spoolInnerDiameter) + "mm");
}
void settings_bOuterMinus5_callback() {
  spoolOuterDiameter -= 5;
  settings_tOuterDia.setText(String(spoolOuterDiameter) + "mm");
}
void settings_bOuterMinus1_callback() {
  spoolOuterDiameter -= 1;
  settings_tOuterDia.setText(String(spoolOuterDiameter) + "mm");
}
void settings_bOuterPlus1_callback() {
  spoolOuterDiameter += 1;
  settings_tOuterDia.setText(String(spoolOuterDiameter) + "mm");
}
void settings_bOuterPlus5_callback() {
  spoolOuterDiameter += 5;
  settings_tOuterDia.setText(String(spoolOuterDiameter) + "mm");
}

//Define state machine evaluations
void evalStates() {
  switch(currentState) {
    case initialize:
      dbSerialPrintln("currentState = init");
      initPage.show();
      delay(500);
      init_pInitSensors.show();
      delay(600);
      init_pInitPID.show();
      delay(400);
      init_pInitMotors.show();
      currentState = refStep;
      dbSerialPrintln("currentState = refStep");
      break;
    case refStep:
      delay(2000);
      init_pRefStepper.show();
      delay(500);
      idlePage.show();
      currentState = idle;
      dbSerialPrintln("currentState = idle");
      break;
    case idle:
      break;
    case settings:
      break;
    case heatup:
      delay(5000);
      actualTemp = nominalTemp;
      if(actualTemp == nominalTemp) {
        heatup_bStartExt.show();
        heatup_tReady.show();
        currentState = ready;
        dbSerialPrintln("currentState = ready");
      }
      break;
    case ready:
      break;
    case extrude:
      break;
    case windUp:
      break;
    default:
      break;
  }
}

void setup() {
  //Initialize display
  nexInit();

  //Open debug serial 
  Serial.begin(9600);

  //Register callback functions
  //Page 1: idle
  idle_bHeatUp.attachPop(idle_bHeatup_callback);
  idle_bSettings.attachPop(idle_bSettings_callback);
  //Page 2: heatup
  heatup_bCooldown.attachPop(heatup_bCooldown_callback);
  heatup_bStartExt.attachPop(heatup_bStartExt_callback);
  heatup_bTempMinus5.attachPop(heatup_bTempMinus5_callback);
  heatup_bTempMinus1.attachPop(heatup_bTempMinus1_callback);
  heatup_bTempPlus1.attachPop(heatup_bTempPlus1_callback);
  heatup_bTempPlus5.attachPop(heatup_bTempPlus5_callback);
  //Page 3: extrude
  extrude_bCooldown.attachPop(extrude_bCooldown_callback);
  extrude_bPauseExt.attachPop(extrude_bPauseExt_callback);
  extrude_bStartWind.attachPop(extrude_bStartWind_callback);
  extrude_bTempMinus1.attachPop(extrude_bTempMinus1_callback);
  extrude_bTempPlus1.attachPop(extrude_bTempPlus1_callback);
  //Page 4: windup
  windup_bCooldown.attachPop(windup_bCooldown_callback);
  windup_bPauseWind.attachPop(windup_bPauseWind_callback);
  windup_bTempMinus1.attachPop(windup_bTempMinus1_callback);
  windup_bTempPlus1.attachPop(windup_bTempPlus1_callback);
  windup_bSpeedMin01.attachPop(windup_bSpeedMin01_callback);
  windup_bSpeedMin001.attachPop(windup_bSpeedMin001_callback);
  windup_bSpeedPlus01.attachPop(windup_bSpeedPlus01_callback);
  windup_bSpeedPlus001.attachPop(windup_bSpeedPlus001_callback);
  //Page 5: settings
  settings_bSave.attachPop(settings_bSave_callback);
  settings_bTempMinus5.attachPop(settings_bTempMinus5_callback);
  settings_bTempMinus1.attachPop(settings_bTempMinus1_callback);
  settings_bTempPlus1.attachPop(settings_bTempPlus1_callback);
  settings_bTempPlus5.attachPop(settings_bTempPlus5_callback);
  settings_bSpeedMin01.attachPop(settings_bSpeedMin01_callback);
  settings_bSpeedMin001.attachPop(settings_bSpeedMin001_callback);
  settings_bSpeedPlus001.attachPop(settings_bSpeedPlus001_callback);
  settings_bSpeedPlus01.attachPop(settings_bSpeedPlus01_callback);
  settings_bWidthMinus5.attachPop(settings_bWidthMinus5_callback);
  settings_bWidthMinus1.attachPop(settings_bWidthMinus1_callback);
  settings_bWidthPlus1.attachPop(settings_bWidthPlus1_callback);
  settings_bWidthPlus5.attachPop(settings_bWidthPlus5_callback);
  settings_bInnerMinus5.attachPop(settings_bInnerMinus5_callback);
  settings_bInnerMinus1.attachPop(settings_bInnerMinus1_callback);
  settings_bInnerPlus1.attachPop(settings_bInnerPlus1_callback);
  settings_bInnerPlus5.attachPop(settings_bInnerPlus5_callback);
  settings_bOuterMinus5.attachPop(settings_bOuterMinus5_callback);
  settings_bOuterMinus1.attachPop(settings_bOuterMinus1_callback);
  settings_bOuterPlus1.attachPop(settings_bOuterPlus1_callback);
  settings_bOuterPlus5.attachPop(settings_bOuterPlus5_callback);
}

void loop() {
  evalStates();
  nexLoop(nexListenList);
}

