#ifndef MYFILEDIALOG_H
#define MYFILEDIALOG_H

#include <QDialog>
#include "api.h"
#include "settingwidget.h"
#include "mynativeeventfilter.h"

static QString startOpenDocumentIntent_private(QString action,QString dir,QString filter)
{
#ifdef Q_OS_ANDROID
    if(QFileInfo(dir).isFile())
    {
        dir = QFileInfo(dir).absolutePath();
    }
    if(!Android::isExternalStorageUri(dir))
    {
        dir = Android::getExternalStorageUriFromPath(dir);
    }
    QEventLoop* loop = new QEventLoop;
    QString* ret = new QString;
    QJniObject intent("android/content/Intent");
    intent.callObjectMethod("setAction","(Ljava/lang/String;)Landroid/content/Intent;",QJniObject::fromString(action).object());
    intent.callObjectMethod("setFlags", "(I)Landroid/content/Intent;",1|2|64|128|32768);
    //FLAG_GRANT_READ_URI_PERMISSION
    //FLAG_GRANT_WRITE_URI_PERMISSION
    //FLAG_GRANT_PERSISTABLE_URI_PERMISSION
    //FLAG_GRANT_PREFIX_URI_PERMISSION
    //FLAG_ACTIVITY_CLEAR_TASK
    if(action == "android.intent.action.OPEN_DOCUMENT")
    {
        intent.callObjectMethod("addCategory","(Ljava/lang/String;)Landroid/content/Intent;",QJniObject::fromString("android.intent.category.OPENABLE").object());
        intent.callObjectMethod("setType","(Ljava/lang/String;)Landroid/content/Intent;",QJniObject::fromString(filter).object());
    }
    else if(action == "android.intent.action.CREATE_DOCUMENT")
    {
        intent.callObjectMethod("addCategory","(Ljava/lang/String;)Landroid/content/Intent;",QJniObject::fromString("android.intent.category.OPENABLE").object());
        intent.callObjectMethod("setType","(Ljava/lang/String;)Landroid/content/Intent;",QJniObject::fromString(filter).object());
    }
    if(!dir.isEmpty())
    {
        QString uri_str = dir;
        QJniObject uri = QJniObject::callStaticObjectMethod("android/net/Uri","parse","(Ljava/lang/String;)Landroid/net/Uri;",QJniObject::fromString(uri_str).object());
        intent.callObjectMethod("putExtra","(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;",QJniObject::fromString("android.provider.extra.INITIAL_URI").object(),uri.object());

        QString name = QFileInfo(dir).fileName();
        if(!name.isEmpty() && action == "android.intent.action.CREATE_DOCUMENT")
        {
            intent.callObjectMethod("putExtra","(Ljava/lang/String;Ljava/lang/CharSequence;)Landroid/content/Intent;",QJniObject::fromString("android.intent.extra.TITLE").object(),QJniObject::fromString(name).object());
        }
    }
    QtAndroidPrivate::startActivity(intent,0,[=](int requestCode, int resultCode, const QJniObject &data){
        QJniObject context = QNativeInterface::QAndroidApplication::context();
        QJniObject contentResolver = context.callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");
        if(data.isValid())
        {
            QJniObject uri = data.callObjectMethod("getData","()Landroid/net/Uri;");
            if(uri.isValid())
            {
                *ret = uri.toString();
                contentResolver.callMethod<void>("takePersistableUriPermission","(Landroid/net/Uri;I)V",uri.object(),1|2);
            }
        }
        loop->quit();
    });
    loop->exec();
    return *ret;
#else
    return QString();
#endif
}

class MyFileIconProvider : public QFileIconProvider
{
public:
    MyFileIconProvider() {}
    void setIcon(QString suffix,QIcon icon)
    {
        suffix = suffix.toLower();
        int index = suffixlist.indexOf(suffix);
        if(index == -1)
        {
            suffixlist.append(suffix);
            suffixiconlist.append(icon);
        }
        else
            suffixiconlist[index] = icon;
    }
    void setIcon(IconType type,QIcon icon)
    {
        int index = typelist.indexOf((int)type);
        if(index == -1)
        {
            typelist.append((int)type);
            typeiconlist.append(icon);
        }
        else
            typeiconlist[index] = icon;
    }
    void removeIcon(QString suffix)
    {
        suffix = suffix.toLower();
        int index = suffixlist.indexOf(suffix);
        if(index != -1)
        {
            suffixlist.removeAt(index);
            suffixiconlist.removeAt(index);
        }
    }
    void removeIcon(IconType type)
    {
        int index = typelist.indexOf((int)type);
        if(index != -1)
        {
            typelist.removeAt(index);
            typeiconlist.removeAt(index);
        }
    }
    void setUseQtProviderOnly(bool on) {flag_qt = on;}
    bool useQtProviderOnly() {return flag_qt;}
    QIcon icon(const QFileInfo &info) const override
    {
        if(!flag_qt)
        {
            int index = suffixlist.indexOf(info.suffix());
            if(index != -1)
                return suffixiconlist.at(index);
        }
        return QFileIconProvider::icon(info);
    }
    QIcon icon(IconType type) const override
    {
        if(!flag_qt)
        {
            int index = typelist.indexOf((int)type);
            if(index != -1)
                return typeiconlist.at(index);
        }
        return QFileIconProvider::icon(type);
    }
private:
    bool flag_qt = false;
    QList<QString> suffixlist;
    QList<QIcon> suffixiconlist;
    QList<int> typelist;
    QList<QIcon> typeiconlist;
};

class MyFileDialog : public QDialog
{
    Q_OBJECT
public:
    MyFileDialog(QWidget *parent = nullptr);
    enum Mode
    {
        Explorer,
        OpenFile,
        OpenDir,
        SaveFile
    };
    enum Option
    {
        needDoubleClick = 0,
        showDotAndDotDot = 1,
        showHideenFile = 2,
        showSuffix = 3,
        showDir = 4,
        showFile = 5,
        showIcon = 6,
        showImageIcon = 7,
        useDarkModeIcon = 8
    };
    bool eventFilter(QObject *watched, QEvent *event);
    void loadPath(QString path);
    QString currentPath() {return pathlist.isEmpty() ? QString() : pathlist.last();}
    QStringList historyPaths() {return pathlist;}
    void clearHistory() { if(!pathlist.isEmpty()) pathlist = QList<QString>({pathlist.last()});}
    void setOption(Option opt,bool on) {setting[opt] = on;}
    bool testOption(Option opt) {return setting.at(opt);}
    void setMode(Mode mode) {m = mode; this->refreshUI();}
    Mode mode() {return m;}
    MyFileIconProvider* fileIconProvider() {return &iconprovider;}
    void setSuffixFilter(QStringList list) {showsuffixs = list;}
    QStringList suffixFilter() {return showsuffixs;}
    void setHiddenFiles(QStringList list) {hiddenfiles = list;}
    QStringList hiddenFiles() {return hiddenfiles;}
    void addHiddenFile(QString path) {hiddenfiles.append(path);}
    void removeHiddenFile(QString path)
    {int i = hiddenfiles.indexOf(path);
    if(i != -1) hiddenfiles.removeAt(i);}
    void addSuffixFilter(QString suffix) {showsuffixs.append(suffix);}
    void removeSuffix(QString suffix)
    {int i = showsuffixs.indexOf(suffix);
    if(i != -1) showsuffixs.removeAt(i);}
    QString currentSelectedFile() {return selectedfile;}
    static QString getOpenFileName(QObject* parent = nullptr,QString caption = QString(),QString dir = QString(),bool useNativeMethod = true,bool isDarkMode = false);
    static QString getExistingDirectory(QObject* parent = nullptr,QString caption = QString(),QString dir = QString(),bool useNativeMethod = true,bool isDarkMode = false);
    static QString getSaveFileName(QObject* parent = nullptr,QString caption = QString(),QString dir = QString(),bool useNativeMethod = true,bool isDarkMode = false);
signals:
    void currentPathChanged(QString oldpath,QString newpath);
    void currentSelectedFileChanged(QString path);
private slots:
    void refreshUI();
    QString toStandardFilePath(QString path);
    void itemVaildClicked(int index,QString key);
    void requestMenu(QString path);
    void initPathBox();
private:
    Mode m = Explorer;
    long long max_load_image_size = 1024 * 1024 * 10;
    QStringList pathlist;
    QStringList showsuffixs;
    QStringList hiddenfiles;
    QString selectedfile;
    MyFileIconProvider iconprovider;
    bool flag_accept = false;
    bool flag_pathbox_connected = false;

    //                      0     1     2    3    4    5    6    7     8
#ifdef Q_Device_Desktop
    QList<bool> setting = {true,false,true,true,true,true,true,true,false};
#else
    QList<bool> setting = {false,false,true,true,true,true,true,false,false};
#endif

    SettingWidget* mainwidget;
    QPushButton* backbutton;
    QPushButton* closebutton;
    QPushButton* commitbutton;
    QLineEdit* pathedit;
    QComboBox* pathbox;
    QProgressBar* bar;
    MyNativeEventFilter* filter;
};

#endif // MYFILEDIALOG_H
