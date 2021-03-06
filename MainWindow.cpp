#include "MainWindow.h"

/**
 * @brief MainWindow::MainWindow
 * @brief Principal constructor
 */
MainWindow::MainWindow(QWidget* parent)
    :QMainWindow(parent)
{
    //WebEngineTools *page = new WebEngineTools;
    createMenu();

    tabContainer = new QTabWidget();
        tabContainer->setTabShape(QTabWidget::Triangular);
        tabContainer->setTabsClosable(true);
        tabContainer->setMovable(true);
    //tabContainer->addTab(page->newPage(tr("www.google.fr")),tr("New Tab"));
    addNewTab();
    connect(tabContainer,SIGNAL(tabCloseRequested(int)),this,SLOT(removeTab(int)));
    connect(tabContainer,SIGNAL(currentChanged(int)),this,SLOT(changeTab(int)));
    setCentralWidget(tabContainer);
    setWindowIcon(QIcon(":/fznavigator_icones/web.png"));
    this->resize(1024,650);
}

/**
 * @brief MainWindow::~MainWindow
 * @brief ___________________________
 * @brief Destruct every objects
 */
MainWindow::~MainWindow()
{
      delete newWindowsAction;
      delete closeTabAction;
      delete exitAction;
      delete newTabAction;
    delete fileMenu;

    delete  helpMenu;

    if(m_previous!=nullptr)
    {
        delete m_previous;
        delete m_nextPage;
        delete m_refresh;
        delete m_stop;
        delete m_go;
    }

    if(tabContainer!=nullptr)
    {
        delete tabContainer;
    }
}


/**
 * @brief MainWindow::createMenu
 * @brief ___________________________________
 * @brief Adding a menu bar and connections for some action in the main interface
 */
void MainWindow::createMenu()
{
    newWindowsAction   = new QAction(tr("New window"),menuBar());
    exitAction         = new QAction(tr("Quit"),menuBar());
    newTabAction       = new QAction(tr("New tab"),menuBar());
    closeTabAction     = new QAction(tr("Close tab"),menuBar());

    fileMenu = menuBar()->addMenu(tr("File"));
      fileMenu->addAction(newWindowsAction);
      fileMenu->addAction(closeTabAction);
      fileMenu->addAction(newTabAction);
      fileMenu->addAction(exitAction);

    m_previous = new QAction(QIcon(":/fznavigator_icones/prev.png"),tr("Back"));
    m_nextPage = new QAction(QIcon(":/fznavigator_icones/next.png"),tr("Forward"));
    m_refresh  = new QAction(QIcon(":/fznavigator_icones/refresh.png"),tr("Reload"));
    m_stop     = new QAction(QIcon(":/fznavigator_icones/stop.png"),tr("Stop"));
    m_go       = new QAction(QIcon(":/fznavigator_icones/go.png"),tr("Go"));

    navigationMenu = menuBar()->addMenu(tr("Navigation"));
    navigationMenu->addAction(m_previous);
    navigationMenu->addAction(m_nextPage);
    navigationMenu->addAction(m_refresh);
    navigationMenu->addAction(m_stop);
    navigationMenu->addAction(m_go);

    helpMenu = menuBar()->addMenu(tr("Help"));

    createShortcut();

   menuBar()->setVisible(true);
   connect(newWindowsAction,SIGNAL(triggered()),this,SLOT(newWindow()));
   connect(closeTabAction,SIGNAL(triggered()),this,SLOT(removeTab()));
   connect(newTabAction,SIGNAL(triggered()),this,SLOT(addNewTab()));
   connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
}
void MainWindow::createShortcut()
{
    newWindowsAction->setShortcut(QKeySequence(QKeySequence::New));
    closeTabAction->setShortcut(QKeySequence("CTRL+W"));
    newTabAction->setShortcut(QKeySequence(QKeySequence::AddTab));
    exitAction->setShortcut(QKeySequence("CTRL+Q"));
}

/**
 * @brief MainWindow::addNewTab
 * @brief _________________________________
 * @brief Creating a new instance of Web Engine and adding the widget in a tab in the main window
 */
void MainWindow::addNewTab()
{
    WebEngineTools *web = new WebEngineTools(this);
    int index = tabContainer->addTab(web->newPage("duckduckgo.com"),tr("About:blank"));
    tabContainer->setCurrentIndex(index);

    QWebEngineView *webPage = web->centralWidget()->findChild<QWebEngineView*>();
   connect( webPage,SIGNAL(titleChanged(QString)),this,SLOT(changeTitle(QString)));
}
void MainWindow::removeTab()
{
    if(tabContainer->count()<=1)
        this->close();
    else
        tabContainer->removeTab(tabContainer->currentIndex());
}
void MainWindow::removeTab(int index)
{
    if(tabContainer->count()<=1)//as the current window is a child of the main
        this->close();          //window, it will be free by polmorphism
    else
    {
        tabContainer->removeTab(index);
        delete currentWindow();
    }
}
void MainWindow::newWindow()
{
    //nullptr mean that this new window has no parent
    MainWindow *window = new MainWindow(nullptr);
    window->show();
}


WebEngineTools *MainWindow::currentWindow()
{
    return (WebEngineTools*)(tabContainer->currentWidget());
}
QWebEngineView *MainWindow::currentPage()
{
    return currentWindow()->centralWidget()->findChild<QWebEngineView *>();
}
void MainWindow::changeTab(int)
{
    QString title = currentWindow()->title();
   if(title.isEmpty())
        this->setWindowTitle(tr("FzNavigator"));
   else
        this->setWindowTitle(title + tr(" - fzNavigator"));
}

void MainWindow::changeTitle(QString title)
{
    //truncate the title if it too long
    QString newTitle = title;
    if(title.size() > 25)
    {
        newTitle = title.left(25) + "...";
    }
    int index = tabContainer->currentIndex();

    tabContainer->setTabText(index,newTitle);
    this->setWindowTitle(newTitle);
}
