#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGuiApplication>
#include <QNativeGestureEvent>
#include "settingwidget.h"
#include "myfiledialog.h"
#include "api.h"
#include "xlsxdocument.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    enum ThemeType
    {
        Dark,
        Light,
        System
    };
    enum FileDialogType
    {
        QtDialog,
        MyDialog
    };
    enum InfoType
    {
        Global,
        Personal
    };
    Widget(QWidget *parent = nullptr);
    ~Widget();
    bool eventFilter(QObject *watched, QEvent *event);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result);
#else
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif
    static Widget* getCurrentWindow();
signals:
    void systemThemeChanged();
    void androidConfigurationChanged();
    void qtMessageUpdated(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    void error(QString message);
private slots:
    void initSettings(bool clear = false);
    void readSettings();
    void refreshUI();
    void showTypeManager();
    void createProject();
    void openProject(QString filePath = QString(),bool needPassword = true);
    void loadFileList();
    void closeCurrentProject();
    void showEditDialog(InfoType type,int personIndex = -1);
    void loadInfoTable();
    void processArguments();
    QStringList showEditStringListDialog(QStringList list,bool isEditMode = true,bool hideModeBox = false);
    int getTypeIndexFromKey(QString key);
    int getTypeIndexFromName(QString name);
    void removeProjectFilter();
    void infoTableClicked(int y,int x);
    void showAutoChangeDialog();
    QStringList getTypeInfo(QString key);
    int getPeopleCount();
    ThemeType getApplicationTheme();
    FileDialogType getApplicationFileDialogType();
private:
    bool currentThemeisDark = false;
    bool isMaximizedBeforeFullScreen = false;
    int back_close_interval = 1000;
    QList<QTime> back_press_timelist;
    QString datapath;
    QString settingpath;
    QSettings* settings = nullptr;
    QtMessageHandler defaultMessageHandler;
    QStringList qtMsgList;
    QFont defaultFont = QFont();

    QPushButton* welcomebutton;
    QPushButton* mainbutton;
    QPushButton* settingbutton;
    QPushButton* fullscreenbutton;
    QWidget* welcomewidget;
    QWidget* mainwidget;
    SettingWidget* settingwidget;

    SettingWidget* filelist;
    QPushButton* openbutton;
    QPushButton* newbutton;
    QPushButton* closebutton;
    QPushButton* typebutton;
    QPushButton* showglobalbutton;
    QPushButton* showpersonbutton;
    QPushButton* closeprojectbutton;
    QLineEdit* filteredit;
    QRadioButton* casebutton;
    QRadioButton* exactbutton;
    QPushButton* autochangebutton;
    QPushButton* outputbutton;
    QPushButton* minimizebutton;

    QTableWidget* infotable;
    QSettings* project = nullptr;
};
#endif // WIDGET_H
