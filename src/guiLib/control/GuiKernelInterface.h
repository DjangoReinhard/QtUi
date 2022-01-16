#ifndef GUIKERNELINTERFACE_H
#define GUIKERNELINTERFACE_H
#include <KernelInterface.h>
class QCloseEvent;
class QVariant;


class GuiKernelInterface : public KernelInterface
{
public:
//  core->axisMask( );
//  core->checkBE( );
//  core->isLatheMode( );
//  core->lcProperties( );
//  core->parseGCFile( fileName.toString());
//  core->toolOffset( );
//  core->toolTable( ).fileName());
//  core->toolTableModel( );
//  core->toolTable( ).tool(toolNum.toInt());
//  QString              helpFilename() const;
//  bool                 isLatheMode() const;
//  bool                 isSimulator() const;

  virtual void                 activatePage(const QString& pageName)       = 0;
  virtual bool                 checkBE()                                   = 0;
  virtual QString              curPage() const                             = 0;
  virtual void                 help4Keyword(const QString& keyWord)        = 0;
  virtual LcProperties&        lcProperties()                              = 0;
  virtual std::pair<QVector3D, QVector3D> machineLimits() const            = 0;
  virtual QMainWindow*         mainWindow()                                = 0;
  virtual void                 processGCodeFile(const QString& fileName);  = 0;
  virtual PluginPageInterface* pluggableMainPage(const QString pageID)     = 0;
  virtual QList<QString>       pluggableMainPages()                        = 0;
  virtual PluginPageInterface* pluggableNotebookPage(const QString pageID) = 0;
  virtual QList<QString>       pluggableNotebookPages()                    = 0;
  virtual void                 setAppMode4PageID(const QString& pageID)    = 0;
  virtual void                 setMainWindow(QMainWindow* w)               = 0;
  virtual void                 setViewStack(PageStack* v)                  = 0;
  virtual void                 setWindowTitle(const QString& title)        = 0;
  virtual void                 showHelp() const                            = 0;
  virtual QWidget*             stackedPage(const QString& pageName)        = 0;
  virtual PluginPageInterface* statusInfo(const QString infoID)            = 0;
  virtual QList<QString>       statusInfos()                               = 0;
  virtual Pos9                 toolOffset() const                          = 0;
  virtual ToolTable&           toolTable()                                 = 0;
  virtual ToolTable*           toolTableModel()                            = 0;
  virtual OcctQtViewer*        view3D()                                    = 0;
  virtual PageStack*           viewStack()                                 = 0;

  virtual void beAbortTask()                                       = 0;
  virtual void beEnableBlockDelete(bool enable)                    = 0;
  virtual void beEnableFlood(bool enable)                          = 0;
  virtual void beEnableMist(bool enable)                           = 0;
  virtual void beEnableOptionalStop(bool enable)                   = 0;
  virtual void beSetSpindleOverride(double rate)                   = 0;
  virtual void beJogStep(int axis, double stepSize, double speed)  = 0;
  virtual void beJogStart(int axis, double speed)                  = 0;
  virtual void beJogStop(int axis)                                 = 0;
  virtual void beHomeAxis(int jointNum)                            = 0;
  virtual void beLoadTaskPlan(const QString& gcodeFile)            = 0;
  virtual void beLoadToolTable(const QString& toolTableFile)       = 0;
  virtual void beSendMDICommand(const QString& command)            = 0;
  virtual void beSetAuto(int autoMode, int line)                   = 0;
  virtual void beSetFeedOverride(double rate)                      = 0;
  virtual void beSetRapidOverride(double rate)                     = 0;
  virtual void beSetSpindle(bool enable, int speed, int direction) = 0;
  virtual void beSetTaskMode(int mode)                             = 0;
  virtual void beSetTaskState(int state)                           = 0;
  virtual void beTaskPlanSynch()                                   = 0;

  virtual bool isLatheMode() const                        = 0;
  virtual void nop() const                                = 0;
  virtual void processGCodeFile(const QVariant& fileName) = 0;
  virtual void setupBackend()                             = 0;
  virtual void updateView(const QVariant& pos)            = 0;
  virtual void windowClosing(QCloseEvent* e)              = 0;
  };
#endif // GUIKERNELINTERFACE_H
