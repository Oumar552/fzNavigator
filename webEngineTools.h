#ifndef WEBENGINETOOLS_H
#define WEBENGINETOOLS_H

#define APPDIR QCoreApplication::applicationDirPath()
#include <QtWidgets>
#include <QTranslator>
#include <QMainWindow>
#include <QWebEngineView>

class WebEngineTools: public QMainWindow
{
  Q_OBJECT
  public slots:
    void changeUrl(QUrl);
    void changeTitle(QString);
    void initLoading();
    void loadUrl();
    void loading(int);
    void endOfLoad(bool);
    void changeIcon(const QIcon&);
    void previous();
    void next();
    void refresh();
    void goHome();
    void stop();

  public:


    WebEngineTools(QWidget *parent);
    ~WebEngineTools();

    WebEngineTools* newPage(QString url);
    const QIcon &icon() {return m_icon ;}
          QString &title(){return m_title;}

        //  QVector<QAction*> allAction(){return liste;}

  private:
    QString const defaultHomePage = "http://www.duckduckgo.com/";
    QString         m_title;
    QIcon           m_icon;
    QWebEngineView *m_webPage;
    QToolBar       *m_toolbar;
    QAction        *m_homeAction;
    QAction        *m_submit;
    QLineEdit      *m_urlField;
    QAction        *m_previousPageAction;
    QAction        *m_nextPageAction;
    QAction        *m_refreshAction;
    QAction        *m_stopAction;
    QProgressBar   *m_progress;
   // QVector<QAction*> liste;

    void addToolbar();
    void addStatusBar();
    void addShortcut();


};

#endif // WEBENGINETOOLS_H
