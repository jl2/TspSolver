#include <QtGui>
#include <stdexcept>
#include "qtsp.h"

void QTsp::readSettings() {
  openDir = tr("../tsps/");
}
QTsp::QTsp(QWidget *parent) : QMainWindow(parent) {
  readSettings();
  loadPlugins();
  setupActions();
  setupToolBar();
  setupMenuBar();
  setupStatusBar();

  titleBarPrefix = tr("QTsp");
  setWindowTitle(titleBarPrefix);
  
  tspFrame = new TspDrawer;
  setCentralWidget(tspFrame);
  
  curFileName=tr("");
  cities=0;
}

QTsp::~QTsp() {
  closeFile();
}

void QTsp::fillInAction(QAction **action, QString text,
			       QString toolTip, const char *method,
			       Qt::ConnectionType type, QIcon icon = QIcon(":/images/blank.png")) {
  *action = new QAction(this);
  (*action)->setText(text);
  (*action)->setToolTip(toolTip);
  (*action)->setStatusTip(toolTip);
  (*action)->setIcon(icon);
  (*action)->setDisabled(true);
  connect(*action, SIGNAL(triggered()), this, method, type);
}
void QTsp::fillInAction(QAction **action, QString text,
			       QString toolTip, const char *method,
			       QIcon icon = QIcon(":/images/blank.png")) {
  *action = new QAction(this);
  (*action)->setText(text);
  (*action)->setToolTip(toolTip);
  (*action)->setStatusTip(toolTip);
  (*action)->setIcon(icon);
  (*action)->setDisabled(true);
  connect(*action, SIGNAL(triggered()), this, method);
}
void QTsp::setupFileActions() {
  fillInAction(&openAction, tr("Open..."), tr("Open an existing tsp."),
	       SLOT(openFile()), QIcon(":/images/open.png"));
  fillInAction(&closeAction, tr("Close"), tr("Close current tsp"),
	       SLOT(closeFile()), QIcon(":/images/close.png"));
  fillInAction(&saveAction, tr("Save"), tr("Save the current file"),
	       SLOT(saveFile()), QIcon(":/images/save.png"));
  fillInAction(&saveAsAction, tr("Save as..."), tr("Save the current tour to a new file"),
	       SLOT(saveFileAs()), QIcon(":/images/save.png"));
  fillInAction(&exitAction, tr("E&xit"), tr("Exit QTsp"), SLOT(close()));
}

void QTsp::setupHelpActions() {
  fillInAction(&aboutAction, tr("&About"), tr("About QTsp"),
	       SLOT(about()), QIcon(":/images/globe.png"));

}

void QTsp::setupActions() {
  setupFileActions();
  setupHelpActions();
  fillInAction(&solveAction, tr("&Solve"), tr("Solve Current TSP"),
	       SLOT(solveCurrent()), QIcon(":/images/globe.png"));

  fillInAction(&configAction, tr("&Configure"),
	       tr("Set configuration options for the current solver."),
	       SLOT(configureSolver()), QIcon(":/images/globe.png"));
  
  aboutAction->setDisabled(false);
  openAction->setDisabled(false);
  exitAction->setDisabled(false);
  solveAction->setDisabled(true);
}

void QTsp::setupToolBar() {
  QToolBar *tb = new QToolBar("Main", this);
  tb->addAction(openAction);
  tb->addAction(closeAction);
  tb->addSeparator();
  tb->addAction(solveAction);
  addToolBar(tb);
}

void QTsp::setupMenuBar() {
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(closeAction);
  fileMenu->addSeparator();
  fileMenu->addAction(saveAction);
  fileMenu->addAction(saveAsAction);
  fileMenu->addSeparator();
  fileMenu->addAction(solveAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);

  solverMenu = menuBar()->addMenu(tr("&Solve"));
  solverMenu->addAction(configAction);
  solverMenu->addSeparator();
  for (std::map<std::string, TspSolver *>::iterator iter = solvers.begin();
       iter != solvers.end();
       ++iter) {
    QAction *temp;
    fillInAction(&temp,
		 QString(iter->second->getName().c_str()),
		 QString(iter->second->getDescription().c_str()),
		 SLOT(solverChanged()));
    solverMenu->addAction(temp);
  }
  
  menuBar()->addSeparator();
  
  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAction);
}

void QTsp::setupStatusBar() {
  statusBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  curDistanceLbl = new QLabel;
  curDistanceLbl->setMaximumWidth(fontMetrics().maxWidth()*24);
  curDistanceLbl->setMinimumWidth(fontMetrics().maxWidth()*10);
  curDistanceLbl->setText("Current Distance");
  curDistanceLbl->setAlignment(Qt::AlignHCenter);

  curFileNameLbl = new QLabel;
  curFileNameLbl->setMaximumWidth(fontMetrics().maxWidth()*24);
  curFileNameLbl->setMinimumWidth(fontMetrics().maxWidth()*10);
  curFileNameLbl->setText("File Name");
  curFileNameLbl->setAlignment(Qt::AlignHCenter);
  
  statusBar()->addWidget(curDistanceLbl);
  statusBar()->addWidget(curFileNameLbl);
}
void QTsp::notYetImplemented() {
  QMessageBox::critical(this, tr("Not Yet Implemented"),
			tr("Oops! That feature is not yet implemented!"),
			QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
}

bool QTsp::canContinue() {
  return true;
}

void QTsp::saveFile() {
  cities->saveToFile(curFileName.toStdString());
}

void QTsp::saveFileAs() {
  QString newFileName = QFileDialog::getSaveFileName(this,
					     tr("Choose a file to save to"),
					     openDir + curFileName,
					     tr("TSP Files (*.txt)"));
  curFileName = newFileName;
  saveFile();
}

void QTsp::openFile() {
  if (!canContinue()) {
    return;
  }
  QString newFileName = QFileDialog::getOpenFileName(this,
					     tr("Choose a file to open"),
					     openDir,
					     tr("TSP Files (*.txt)"));
  if (newFileName == tr("")) {
    // Cancelled
    return;
  }
  closeFile();
  try {
    cities = new CityList(newFileName.toStdString());
    curFileName = newFileName;
    curFileNameLbl->setText(newFileName);
    curDistanceLbl->setText(tr("%1").arg(cities->getCurrentLength()));
    double xmin, ymin, xmax, ymax;
    cities->getDimensions(xmin, ymin, xmax, ymax);
    xmin -= 0.01*(xmax-xmin);
    ymin -= 0.01*(ymax-ymin);
    xmax += 0.01*(xmax-xmin);
    ymax += 0.01*(ymax-ymin);;
    tspFrame->setDimensions(xmin, ymin, xmax, ymax);
    doRedraw();
  } catch (std::runtime_error re) {
    openFileError(re.what());
    return;
  }
  
  setWindowTitle(tr("%1 - %2").arg(titleBarPrefix).arg(newFileName));
  enableActionsOnOpen();
}

void QTsp::openFileError(QString what) {
  QMessageBox::critical(this, tr("Failed"),
			tr("Oops! That's a bad tsp file:\n%1").arg(what),
			QMessageBox::Ok, QMessageBox::NoButton,
			QMessageBox::NoButton);
}

void QTsp::disableActionsOnClose() {
  closeAction->setDisabled(true);
  solveAction->setDisabled(true);
  saveAction->setDisabled(true);
  saveAsAction->setDisabled(true);
  foreach(QAction *actn, solverMenu->actions()) {
    actn->setDisabled(true);
  }
}
void QTsp::enableActionsOnOpen() {
  closeAction->setDisabled(false);
  solveAction->setDisabled(false);
  saveAction->setDisabled(false);
  saveAsAction->setDisabled(false);
  foreach(QAction *actn, solverMenu->actions()) {
    actn->setDisabled(false);
  }
}

void QTsp::closeFile() {
  if (!canContinue()) {
    return;
  }
  if (cities) {
    delete cities;
    cities=0;
    tspFrame->setDrawable(false);
    tspFrame->setDimensions(-1, 1, -1, 1);
  }
  disableActionsOnClose();
  setWindowTitle(titleBarPrefix);
  curFileName = tr("");
}

void QTsp::about() {
  QMessageBox::about(this, tr("About"), tr("<h2>QTsp</h2><p>Qt version</p><p>"
					   "By Jeremiah LaRocco.</p>"));
}

void QTsp::solveCurrent() {
  solvers[curSolver]->solve(cities->getCities());
  curDistanceLbl->setText(tr("%1").arg(cities->getCurrentLength()));
  doRedraw();
}

void QTsp::loadPlugins() {
  QDir pluginDir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
  if (pluginDir.dirName().toLower() == "debug" ||
      pluginDir.dirName().toLower == "release")
    pluginDir.cdUp();
#elif defined(Q_OS_MAC)
  if (pluginDir.dirName() == "MacOS") {
    pluginDir.cdUp();
    pluginDir.cdUp();
    pluginDir.cdUp();
  }
#endif
  if (!pluginDir.cd("plugins"))
    return;
  foreach(QString fileName, pluginDir.entryList(QDir::Files)) {
    QPluginLoader loader(pluginDir.absoluteFilePath(fileName));
    if (TspSolver *interface = qobject_cast<TspSolver *>(loader.instance())) {
      solvers[interface->getName()] = interface;
    }
  }
  if (solvers.begin()!=solvers.end()) {
    curSolver = solvers.begin()->second->getName();
  }
}

void QTsp::solverChanged() {
  QAction *action = qobject_cast<QAction *>(QObject::sender());
  if (action==0) return;
  curSolver = action->text().toStdString();
  solveCurrent();
  curDistanceLbl->setText(tr("%1").arg(cities->getCurrentLength()));  
}

void QTsp::doRedraw() {
  tspFrame->setCities(cities->getCities());
  tspFrame->setDrawable(true);
}

void QTsp::configureSolver() {
  solvers[curSolver]->getConfiguration(this);
}
