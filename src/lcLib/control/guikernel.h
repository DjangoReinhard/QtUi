#ifndef GUIKERNEL_H
#define GUIKERNEL_H
#include <kernel.h>
#include <tooltable.h>
#include <axismask.h>
#include <gcodeinfo.h>
#include <positioncalculator.h>
#include <QThread>
#include <lcproperties.h>
#include <LCInter.h>

class PluginPageInterface;
class SysEventModel;
class OcctQtViewer;
class Ally3D;
class CenterView;
class QMainWindow;
class StatusReader;
class CommandWriter;
class QVariant;
class CanonIFSettings;
class QTimerEvent;
class QCloseEvent;


class GuiKernel : public Kernel
{
  Q_OBJECT
public:
  virtual int     axisMask() const override;
  DBConnection*   createDatabase(DBHelper& dbAssist);
  virtual void    logSysEvent(const QString& msg) override;
  virtual void    logSysEvent(const SysEvent& se) override;
  virtual void    initialize(const QLocale& locale, DBHelper& dbAssist) override;
  virtual QString fileName4(const QString& fileID) const override;
  virtual void    timerEvent(QTimerEvent* e) override;
  virtual void    windowClosing(QCloseEvent* e);
  bool isLatheMode() const;
  void nop() const;
  void parseGCode(QFile& file);
  void setupBackend();
  void updateView(const QVariant& pos);

protected:
  explicit GuiKernel(const QString& iniFilename, const QString& appName, const QString& groupID);
  virtual ~GuiKernel() = default;

signals:
  void abortTask();
  void enableBlockDelete(bool enable);
  void enableFlood(bool enable);
  void enableMist(bool enable);
  void enableOptionalStop(bool enable);
  void setSpindleOverride(double rate);
  void jogStep(int axis, double stepSize, double speed);
  void jogStart(int axis, double speed);
  void jogStop(int axis);
  void homeAxis(int jointNum);
  void loadTaskPlan(const QString& gcodeFile);
  void loadToolTable(const QString& toolTableFile);
  void sendMDICommand(const QString& command);
  void setAuto(int autoMode, int line);
  void setFeedOverride(double rate);
  void setRapidOverride(double rate);
  void setSpindle(bool enable, int speed, int direction);
  void setTaskMode(int mode);
  void setTaskState(int state);
  void taskPlanSynch();

private:
  LcProperties*      lcProps;
  ToolTable*         tt;
  LCInterface*       lcIF;
  AxisMask*          mAxis;
  OcctQtViewer*      view3D;
  CenterView*        centerView;
  QMainWindow*       mainWindow;
  Ally3D*            ally3D;
  GCodeInfo          gcodeInfo;
  PositionCalculator positionCalculator;
  StatusReader*      statusReader;
  CommandWriter*     commandWriter;
  QThread            backendCommThread;
  SysEventModel*     sysEvents;
  CanonIFSettings*   canonIF;
  QMap<QString, PluginPageInterface*> pages;
  QMap<QString, PluginPageInterface*> statusInfos;
  friend class GuiKernelCreator;
  friend class GuiCore;
  friend class CanonIF;
  };
#endif // GUIKERNEL_H
