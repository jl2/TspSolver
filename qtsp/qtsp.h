#ifndef QTSP_INCLUDE_H
#define QTSP_INCLUDE_H

#include <QMainWindow>
#include "tspdrawer.h"
#include "citylist.h"
#include "tspsolver.h"

class QToolBar;
class QMenu;
class QAction;
class QLabel;
class QSplitter;
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QFrame;

class QTsp : public QMainWindow {
  Q_OBJECT;

  QToolBar *toolBar;
  QMenu *mainMenu;
  QMenu *solverMenu;
 public:
  QTsp(QWidget *parent = 0);
  ~QTsp();
  
  public slots:
  void openFile();
  void closeFile();
  void saveFileAs();
  void saveFile();
  void about();
  void solverChanged();
  void solveCurrent();
  void configureSolver();
  
 private:
  void readSettings();
  void setupActions();
  void setupFileActions();
  void setupEditActions();
  void setupCallPlanActions();
  void setupToolsActions();
  void setupHelpActions();
  void fillInAction(QAction **action, QString text,
		    QString toolTip, const char *method,
		    Qt::ConnectionType type, QIcon icon);
  void fillInAction(QAction **action, QString text,
		    QString toolTip, const char *method,
		    QIcon icon);


  void setupToolBar();
  void setupMenuBar();
  void setupStatusBar();

  void openFileError(QString what);

  void disableActionsOnClose();
  void enableActionsOnOpen();
  void notYetImplemented();

  void loadPlugins();
  
  bool canContinue();

  void doRedraw();
  
  QString openDir;
  QString curFileName;
  QString titleBarPrefix;
  
  QLabel *curDistanceLbl;
  QLabel *curFileNameLbl;
  
  TspDrawer *tspFrame;
  CityList *cities;
  std::string curSolver;
  
  QAction *openAction;
  QAction *closeAction;
  QAction *exitAction;
  QAction *saveAsAction;
  QAction *saveAction;
  QAction *aboutAction;
  QAction *solveAction;
  QAction *configAction;
  std::map<std::string, TspSolver *> solvers;
};

#endif
