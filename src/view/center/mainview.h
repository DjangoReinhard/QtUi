#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QWidget>
#include <QMap>
class DynFrame;
class QCloseEvent;
class Kernel;


class MainView : public QWidget
{
  Q_OBJECT
public:
  MainView(QWidget* parent = nullptr);

  QWidget*       activatePage(const QString& name);
  const QString& activePage() const;
  QWidget*       page(const QString& name);
  void           addPage(DynFrame* page, const QString& name = QString());
  void           dump() const;

private:
  void           windowClosing(QCloseEvent* e);

  QMap<QString, DynFrame*> pages;
  QString                  curPage;
  friend class Kernel;
  };
#endif // MAINVIEW_H
