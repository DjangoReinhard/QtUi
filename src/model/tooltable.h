#ifndef TOOLTABLE_H
#define TOOLTABLE_H
#include <toolentry.h>
#include <QAbstractTableModel>
#include <QListIterator>
#include <QString>
#include <QList>
#include <QMap>
class QFile;
class QModelIndex;

/**
 * @brief The ToolTable class
 * parse and hold tooltable of linuxcnc
 */
class ToolTable : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit ToolTable(const QString& fileName = QString());
  explicit ToolTable(QFile& file);
  explicit ToolTable(const ToolTable&& other);
  virtual ~ToolTable();

  ToolTable&       operator = (const ToolTable&& other);
  const ToolEntry& current() const  { return curTool; }
  const ToolEntry* tool(int num) const;
  QString          fileName() const { return fn; }
  int              entries() const;
  void             dump();
  bool             save();
  void             setCurrent(int lineNum);
  void             setDirty(bool dirty = true);
  void             setLatheMode(bool latheMode)  { this->latheMode = latheMode; }
  QList<ToolEntry*>::Iterator begin()            { return tools.begin(); }
  QList<ToolEntry*>::Iterator end()              { return tools.end();   }
  QList<ToolEntry*>::ConstIterator begin() const { return tools.begin(); }
  QList<ToolEntry*>::ConstIterator end() const   { return tools.end();   }

  // for AbstractTableModel
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

protected:
  void addTool(const ToolEntry& tool);
  void processFile(QFile& file);
  void processLine(int lineNum, const QString& line);

private:
  QMap<int, ToolEntry*> mappedTools;
  QList<ToolEntry*>     tools;
  ToolEntry             curTool;
  QString               fn;
  bool                  latheMode;
  bool                  dirty;
  };
#endif // TOOLTABLE_H
