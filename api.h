#ifndef API_H
#define API_H

#define API_VER 20240802
#define Core_Private_Enabled
#define Gui_Private_Enabled

#ifdef QT_AXCONTAINER_LIB
#define Axcontainer_Enabled
#endif

#ifdef QT_NETWORK_LIB
#define Network_Enabled
#endif

#ifdef QT_CONCURRENT_LIB
#define Concurrent_Enabled
#endif

#if defined(QT_MULTIMEDIA_LIB) && defined(QT_MULTIMEDIAWIDGETS_LIB)
#define Multimedia_And_Widgets_Enabled
#define Multimedia_Private_Enabled
#endif
//#define WinRT_Enabled
//#define Win_Extra_Enabled
#define Load_Windows_LIBS
//#define Webview_Enabled

//
//  W A R N I N G
//  -------------
//
// It's discouraged to enable winrt lib in your Qt project,
// for there's been no solution to run on Windows 7 for winrt
// program so far.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <mutex>

#include <QObject>
#include <QApplication>
#include <QCoreApplication>
#include <QGuiApplication>

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QWindow>

#include <QEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QTouchEvent>
#include <QFocusEvent>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFileOpenEvent>

#include <QString>
#include <QStringList>
#include <QSet>
#include <QUrl>
#include <QByteArray>
#include <QDesktopServices>
#include <QProcess>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include <QStack>
#include <QStandardPaths>
#include <QSysInfo>
#include <QFont>
#include <QRegularExpression>
#include <QMimeData>
#include <QSettings>
#include <QFuture>
#include <QStyle>
#include <QStyleFactory>
#include <QCursor>
#include <QThread>
#include <QRegularExpression>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QClipboard>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>
#include <QVariantAnimation>
#include <QPropertyAnimation>

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextBrowser>
#include <QFileDialog>
#include <QProgressBar>
#include <QProgressDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QTreeView>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QSlider>
#include <QScroller>
#include <QScrollArea>
#include <QScrollBar>
#include <QScrollerProperties>
#include <QListView>
#include <QList>
#include <QRadioButton>
#include <QMessageBox>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QStandardItem>
#include <QColorDialog>
#include <QSpinBox>
#include <QFileIconProvider>
#include <QSplashScreen>
#include <QTableWidget>
#include <QHeaderView>
#include <QInputDialog>

#include <QImage>
#include <QImageIOHandler>
#include <QImageReader>
#include <QPixmap>
#include <QBitmap>
#include <QRect>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPalette>
#include <QStyleHints>
#include <QOperatingSystemVersion>
#include <QLocale>
#include <QCryptographicHash>

#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0))
#include <QPermission>
#include <QPermissions>
#endif

#ifdef Q_OS_WIN
#ifdef Webview_Enabled
#if defined(_MSC_VER)
#include <QtWebView>
#include <QtWebView/QtWebView>
#include <qwebview_global.h>
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0))
#include <QWebEngineView>
#endif
#endif
#endif
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#ifdef Win_Extra_Enabled
#include <QtWinExtras>
#include <QtWin>
#include <qwinfunctions.h>
#endif
#endif
#if (QT_VERSION > QT_VERSION_CHECK(6,0,0))
#ifdef Core_Private_Enabled
#endif
#endif
#if defined(_MSC_VER) && defined(WinRT_Enabled)
#include <winrt/base.h>
namespace winrt::impl
{
    template <typename Async>
    auto wait_for(Async const& async, Windows::Foundation::TimeSpan const& timeout);
}
#include <WinRTBase.h>
#include <winrt/Windows.ApplicationModel.LockScreen.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.Foundation.h>
#endif
#include <Windows.h>
#include <processthreadsapi.h>
#include <qt_windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <shellapi.h>
#include <ShlObj.h>
#include <Ole2.h>
#include <commdlg.h>
#include <dwmapi.h>
#include <Psapi.h>
#include <fcntl.h>
#include <io.h>
#include <Shlwapi.h>
#ifdef Load_Windows_LIBS
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "DbgHelp.lib")
#pragma comment(lib, "Shlwapi.lib")
#if defined(_MSC_VER) && defined(WinRT_Enabled)
#pragma comment(lib, "windowsapp")
#pragma comment(lib, "OLEAUT32.lib")
#endif
#endif
#endif

#ifdef Q_OS_ANDROID
#ifdef Core_Private_Enabled
#include <android/bitmap.h>
#include <QtCore/private/qandroidextras_p.h>
#include <QJniObject>
#include <QJniEnvironment>
//#include <QPermissions>
#endif
#endif

#ifdef Axcontainer_Enabled
#include <QAxObject>
#include <QAxBase>
#include <QAxBaseObject>
#include <QAxBaseWidget>
#include <QAxObjectInterface>
#include <QAxScript>
#include <QAxScriptEngine>
#include <QAxScriptManager>
#include <QAxSelect>
#include <QAxWidget>
#endif


#ifdef Network_Enabled
#include <QSslSocket>
#endif

#ifdef Concurrent_Enabled
#include <QtConcurrent>
#endif

#ifdef Core_Private_Enabled
#if(QT_VERSION>=QT_VERSION_CHECK(6,7,0))
#include "QtCore/private/qzipreader_p.h"
#include "QtCore/private/qzipwriter_p.h"
#endif
#endif
#ifdef Gui_Private_Enabled
#if(QT_VERSION<QT_VERSION_CHECK(6,7,0))
#include "QtGui/private/qzipreader_p.h"
#include "QtGui/private/qzipwriter_p.h"
#endif
#endif

#ifdef Network_Enabled
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#endif

#ifdef Multimedia_And_Widgets_Enabled
//#include <QVideoProbe>
#include <QImageWriter>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaMetaData>
#include <QVideoFrame>
#include <QGraphicsVideoItem>
#include <QAudioOutput>
#include <QMediaRecorder>
#include <QAudioDecoder>
#if(QT_VERSION>=QT_VERSION_CHECK(6,0,0))
#include <QVideoSink>
#include <QVideoFrameFormat>
#else
#ifdef Multimedia_Private_Enabled
#include <private/qvideoframe_p.h>
#endif
#include <QAbstractVideoSurface>
#include <QAudioRecorder>
#include <QAudioEncoderSettings>
#include <QVideoEncoderSettings>
#endif
#endif

#ifdef Q_OS_WIN
//Windows
#define Q_Device_Desktop
#else
#ifdef Q_OS_LINUX
#ifdef Q_OS_ANDROID
//Android
#define Q_Device_Mobile
#else
//Linix Desktop
#define Q_Device_Desktop
#endif
#else
#ifdef Q_OS_UNIX
#ifdef Q_OS_MAC
//Macos
#define Q_Device_Desktop
#else
#ifdef Q_OS_IOS
//ios
#define Q_Device_Mobile
#else
//unix unknown
#define Q_Device_Unknown
#endif
#endif
#else
//Unknown
#define Q_Device_Unknown
#endif
#endif
#endif

#ifdef Q_Device_Unknown
#define Q_Device_Desktop
#endif

static int Abs(int num)
{
    if(num >= 0)
        return num;
    else
        return -num;
}
static float Abs(float num)
{
    if(num >= 0)
        return num;
    else
        return -num;
}
static int Max(int a,int b)
{
    if(a > b)
        return a;
    else
        return b;
}
static float Max(float a,float b)
{
    if(a > b)
        return a;
    else
        return b;
}
static int Mini(int a,int b)
{
    if(a < b)
        return a;
    else
        return b;
}
static float Mini(float a,float b)
{
    if(a < b)
        return a;
    else
        return b;
}
static bool isint(QString str)
{
    bool ok;
    str.toInt(&ok);
    return ok;
}
static bool isfloat(QString str)
{
    bool ok;
    str.toFloat(&ok);
    return ok;
}
static bool isDouble(QString str)
{
    bool ok;
    str.toDouble(&ok);
    return ok;
}
static QString getlastPath(QString path)
{
    QString ret = path.replace("\\","/");

    if(ret.indexOf("/") != ret.lastIndexOf("/"))//2个或以上
    {
        if(ret.endsWith("/"))
            ret.chop(1);

        while(!ret.endsWith("/"))
        {
            ret.chop(1);
        }
        if(ret != "/")
            ret.chop(1);
    }
    else if(ret.contains("/"))
    {
        if(!ret.endsWith("/"))
        {
            while(!ret.endsWith("/"))
                ret.chop(1);
            if(ret != "/")
                ret.chop(1);
        }
        else if(ret != "/")
        {
            ret.chop(1);
        }
    }

    return ret;
}
static double distance(QPoint p1,QPoint p2)
{
    if(p1.x() == p2.x())
    {
        return double(Abs(p1.y()-p2.y()));
    }
    else if(p1.y() == p2.y())
    {
        return double(Abs(p1.x()-p2.x()));
    }
    else
    {
        return double(sqrt(double(Abs(p1.x()-p2.x())*Abs(p1.x()-p2.x())+Abs(p1.y()-p2.y())*Abs(p1.y()-p2.y()))));
    }
}
static QPoint midPoint(QPoint p1,QPoint p2)
{
    return QPoint((p1.x()+p2.x())/2,(p1.y()+p2.y())/2);
}
static QString runCommand(QString cmd)
{
    FILE *fp;
    char buffer[1024];
#ifdef Q_OS_WIN
    fp = _popen(cmd.toLocal8Bit().data(), "r");
#else
    fp = popen(cmd.toLocal8Bit().data(), "r");
#endif
    if (fp == NULL)
    {
        return "";
    }

    while(fgets(buffer, sizeof(buffer), fp) != NULL)
    {

    }
#ifdef Q_OS_WIN
    _pclose(fp);
#else
    pclose(fp);
#endif
    QString ret = QString(buffer);
    if(ret.endsWith("\n"))
        ret = ret.left(ret.length()-QString("\n").length());
    if(ret.endsWith("\r"))
        ret = ret.left(ret.length()-QString("\r").length());
    return ret;
}
static double setPrecision(double num,int p)
{
    return round(num*10*p)/(10*p);
}
static int getContainStringTimes(QString parent,QString s)
{
    int count = 0;
    int index = parent.indexOf(s);
    while(index != -1)
    {
        parent.remove(index,s.length());
        count++;
        index = parent.indexOf(s);
    }
    return count;
}
static int screenwidth() {return QGuiApplication::primaryScreen()->availableVirtualGeometry().width();}
static int screenheight() {return QGuiApplication::primaryScreen()->availableVirtualGeometry().height();}
static QSize screensize() {return QGuiApplication::primaryScreen()->availableVirtualGeometry().size();}
static QSize realScreenSize() {return QGuiApplication::primaryScreen()->geometry().size() * QGuiApplication::primaryScreen()->devicePixelRatio();}
static void wait(int time,int mode = 0)
{
    if(mode == 0)
    {
        QMutex mutex;
        QWaitCondition waitCondition;
        mutex.lock();
        waitCondition.wait(&mutex, time);
        mutex.unlock();
    }
    else
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,time);
    }
}
static QStringList findTextFiles(const QString& path, const QString& keyword)
{
    QDir dir(path);
    QStringList filters;
    filters << "*.txt" << "*.log" << "*.ini" << "*.cmd" << "*.bat";  // 只搜索文本文件
    dir.setNameFilters(filters);

    QStringList fileList;
    QRegularExpression regex(keyword, QRegularExpression::CaseInsensitiveOption);

    // 递归遍历目录下的所有文件
    foreach (const QString& file, dir.entryList(QDir::Files | QDir::NoSymLinks)) {
        QFile f(dir.filePath(file));
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&f);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (regex.match(line).hasMatch()) {
                    fileList.append(dir.filePath(file));
                    break;
                }
            }
        }
    }

    // 递归遍历子目录
    foreach (const QString& subdir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QStringList subFiles = findTextFiles(dir.filePath(subdir), keyword);
        fileList.append(subFiles);
    }

    return fileList;
}
static QStringList findFiles(const QString& path, const QString& keyword, const QString& suffix = "")
{
    QDir dir(path);
    QStringList filters;
    if (!suffix.isEmpty()) {
        filters << "*." + suffix;
    }
    dir.setNameFilters(filters);

    QStringList fileList;

    // 递归遍历目录下的所有文件
    foreach (const QString& file, dir.entryList(QDir::Files | QDir::NoSymLinks)) {
        if (file.contains(keyword, Qt::CaseInsensitive)) {
            fileList.append(dir.filePath(file));
        }
    }

    // 递归遍历子目录
    foreach (const QString& subdir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QStringList subFiles = findFiles(dir.filePath(subdir), keyword, suffix);
        fileList.append(subFiles);
    }

    return fileList;
}
static int getFilesNumber(QString path,QString type = "")
{
    QDir *dir=new QDir(path);
    QStringList filter;
    if(type != "")
    {
        filter << "*." + type;
        dir->setNameFilters(filter);
    }
    QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
    int count = fileInfo->count();
    if(type == "")
        count = count - 2;
    return count;
}
static QFileInfoList getFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = getFileList(name);
         file_list.append(child_file_list);
    }

    return file_list;
}
static qint64 getDirSize(QString path)
{
    if(QFileInfo(path).isFile())
        path = QFileInfo(path).absolutePath();
    if(QFileInfo(path).isDir())
    {
        qint64 sum = 0;
        for(QFileInfo info : getFileList(path))
        {
            sum += info.size();
            //sum += QFile(info.absoluteFilePath()).size();
        }
        return sum;
    }
    else
    {
        return 0;
    }
}
static bool hasFilePermission(QString filepath,QIODevice::OpenModeFlag device = QIODevice::ReadWrite)
{
    bool check = true;
    if(filepath != "")
    {
        QFile* file = new QFile(filepath);
        if(!file->exists())
            check = false;
        if(file->open(device))
        {
            file->close();
            delete file;
            if(!check)
                QFile::remove(filepath);
            return true;
        }
        else
        {
            delete file;
            return false;
        }
    }
    else
    {
        return false;
    }
}
static bool hasPathPermission(QString path,QIODevice::OpenModeFlag device = QIODevice::ReadWrite)
{
    if(path != "" && QFileInfo(path).isDir())
    {
        path.replace("\\","/");
        if(!path.endsWith("/"))
            path = path + "/";
        path = path + "my_app_textfile.txt";
        return hasFilePermission(path,device);
    }
    else if(QFileInfo(path).isFile())
    {
        return hasFilePermission(path,device);
    }
    else
    {
        return false;
    }
}
static bool staysOnTop(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
#ifdef Q_OS_WIN
        SetWindowPos(HWND(w->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#else
        if(w->isHidden())
        {
            w->setWindowFlags(w->windowFlags() | Qt::WindowStaysOnTopHint);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setFlags(w->windowFlags() | Qt::WindowStaysOnTopHint);
        }
#endif
        return true;
    }
    else
    {
        return false;
    }
}
static bool staysNotOnTop(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
#ifdef Q_OS_WIN
        SetWindowPos(HWND(w->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#else
        if(w->isHidden())
        {
            w->setWindowFlag(Qt::Window);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setFlags(Qt::Window);
        }
#endif
        return true;
    }
    else
    {
        return false;
    }
}
static bool fixSize(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
        if(w->isHidden())
        {
            w->setMaximumSize(w->size());
            w->setMinimumSize(w->size());
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setMaximumSize(w->size());
            pWin->setMinimumSize(w->size());
        }
        return true;
    }
    else
    {
        return false;
    }
}
static bool fixNoSize(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
        if(w->isHidden())
        {
            w->setMaximumSize(16777215,16777215);
            w->setMinimumSize(0,0);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setMaximumSize(QSize(16777215,16777215));
            pWin->setMinimumSize(QSize(0,0));
        }
        return true;
    }
    else
    {
        return false;
    }
}
static bool setMaximizeButton(QObject* obj,bool check)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
        if(w->isHidden())
        {
            w->setWindowFlag(Qt::WindowMaximizeButtonHint,check);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setFlag(Qt::WindowMaximizeButtonHint,check);
        }
        return true;
    }
    else
    {
        return false;
    }
}
static bool setCloseButton(QObject* obj,bool check)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
        if(w->isHidden())
        {
            w->setWindowFlag(Qt::WindowCloseButtonHint,check);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setFlag(Qt::WindowCloseButtonHint,check);
        }
        return true;
    }
    else
    {
        return false;
    }
}
static QString readtextfile(QString path)
{
    if(path != "")
    {
        QFile* file = new QFile(path);
        if(file->open(QIODevice::ReadOnly | QIODevice::Text) || file->open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QString content = QString::fromLocal8Bit(file->readAll());
            file->close();
            delete file;
            return content;
        }
        else
        {
            return QString();
        }
    }
    else
    {
        return QString();
    }
}
static QByteArray readfile(QString path)
{
    if(path != "")
    {
        QFile* file = new QFile(path);
        if(file->open(QIODevice::ReadOnly) || file->open(QIODevice::ReadWrite))
        {
            QByteArray content = file->readAll();
            file->close();
            delete file;
            return content;
        }
        else
        {
            return QByteArray();
        }
    }
    else
    {
        return QByteArray();
    }
}
static bool writetextfile(QString text,QString path)
{
    QFile* file = new QFile(path);
    if(file->open(QIODevice::WriteOnly) || file->open(QIODevice::ReadWrite))
    {
        file->write(text.toLatin1());
        file->close();
        return true;
    }
    else
    {
        return false;
    }
}
static bool writefile(QByteArray ba,QString path)
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly) || file.open(QIODevice::ReadWrite))
    {
        file.write(ba);
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}
static bool writetextfileappend(QString text,QString path)
{
    QFile* file = new QFile(path);
    if(file->open(QIODevice::WriteOnly | QIODevice::Append) || file->open(QIODevice::ReadWrite | QIODevice::Append))
    {
        file->write(text.toLatin1());
        file->close();
        return true;
    }
    else
    {
        return false;
    }
}
static bool copyfile(QString path1,QString path2)
{
    if(QFile::copy(path1,path2))
    {
        return true;
    }
    else if(QFileInfo(path1).isFile() && hasFilePermission(path1,QIODevice::ReadOnly) && hasFilePermission(path2,QIODevice::WriteOnly))
    {
        QByteArray ba = readfile(path1);
        writefile(ba,path2);
        ba = "";
        return QFile::exists(path2);
    }
    else
    {
        return false;
    }
}
static bool zipReader(QString zip,QString path)
{
#ifdef Gui_Private_Enabled
    if(!QFileInfo(path).isDir())
        QDir().mkpath(path);
    if(QFileInfo(path).isDir() && hasFilePermission(zip,QIODevice::ReadOnly) && hasPathPermission(path))
    {
        path = path.replace("\\","/");
        if(path.endsWith("/"))
            path.chop(1);


        QZipReader reader(zip);
        //qDebug() << reader.fileInfoList().size();
        reader.extractAll(path);
        for(int i = 0; i < reader.fileInfoList().size(); i++)
        {
            QString filepath = path + "/" + reader.fileInfoList().at(i).filePath;
            //qDebug() << filepath;
            QString tmp = filepath;
            while(!tmp.endsWith("/"))
                tmp.chop(1);
            if(!QFileInfo(tmp).isDir() || !QDir(tmp).exists())
                QDir().mkpath(tmp);

            QFile* file = new QFile(filepath);
            file->open(QIODevice::WriteOnly);
            file->write(reader.fileData(QString::fromLocal8Bit(reader.fileInfoList().at(i).filePath.toUtf8())));
            file->close();
            delete file;
        }
        reader.close();
    }
    else
    {
        qDebug() << QFileInfo(path).isDir();
        qDebug() << hasFilePermission(zip,QIODevice::ReadOnly);
        qDebug() << hasPathPermission(path);
        return false;
    }
#else
    return false;
#endif
}
static bool zipWriter(QString zip,QString path)
{
#ifdef Gui_Private_Enabled
    if(QFileInfo(path).isDir() && hasFilePermission(zip,QIODevice::WriteOnly) && hasPathPermission(path))
    {
        QFileInfoList list = getFileList(path);
        path.replace("\\","/");
        if(path.endsWith("/"))
            path.chop(1);
        if(path.contains("/"))
            while(!path.endsWith("/"))
                path.chop(1);
        else
            path = path + "/";
        QZipWriter writer(zip);
        for(int i = 0; i < list.size(); i++)
        {
            QString filepath = list.at(i).absoluteFilePath().replace("\\","/");
            QFile* file = new QFile(filepath);
            filepath = filepath.remove(0,path.length());

            QString tmp = filepath;
            QStringList DirectoryList;
            while(!tmp.endsWith("/"))
                tmp.chop(1);
            while(tmp != "")
            {
                if(tmp.endsWith("/"))
                    DirectoryList << tmp;
                tmp.chop(1);
            }
            for(int i = DirectoryList.size()-1; i >= 0; i = i - 1)
            {
                //qDebug() << DirectoryList.at(i);
                writer.addDirectory(DirectoryList.at(i));
            }

            if(file->open(QIODevice::ReadOnly))
            {
                writer.addFile(filepath,file->readAll());
                file->close();
                delete file;
            }
            else
            {
                qDebug() << "fail to read file:" << filepath;
            }
        }
        writer.close();
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
#ifndef QVIDEOFRAME_H
typedef int QVideoFrame;
#endif
static QImage frameToImage(QVideoFrame f)
{
#ifdef QVIDEOFRAME_H
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
            return f.toImage();
#else
#if defined(Multimedia_Private_Enabled) && defined(QVIDEOFRAME_P_H)
            QImage image = qt_imageFromVideoFrame(f);
#else
            QImage image;
            f.map(QAbstractVideoBuffer::ReadOnly);
            QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(f.pixelFormat());
            if(imageFormat != QImage::Format_Invalid)
            {
                image = QImage(f.bits(),f.width(),f.height(),f.bytesPerLine(),imageFormat);
            }
            else
            {
                int nbytes = f.mappedBytes();
                image = QImage::fromData(f.bits(), nbytes);
            }
            f.unmap();
#endif
#ifdef Q_OS_WIN
            image = image.mirrored();
#endif
            return image;
#endif
#else
    return QImage();
#endif
}
static QSize nativeLabelSize(QString text,Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop)
{
    QWidget* widget = new QWidget(nullptr);
    QLabel* label = new QLabel(widget);
    widget->hide();
    label->setText(text);
    label->setAlignment(align);
    label->show();
    QSize size = label->size();
    label->close();
    widget->close();
    return size;
}
static QSize nativeLabelSize(QLabel* label)
{
    return nativeLabelSize(label->text(),label->alignment());
}
static QObjectList allChildren(QObject* object)
{
    QObjectList list = object->children();
    int old = 0;
    while(list.count() != old)
    {
        old = list.count();
        for(int i = 0;i < list.count();i++)
        {
            QObject* obj = list.at(i);
            for(int j = 0;j < obj->children().count();j++)
            {
                if(!list.contains(obj->children().at(j)))
                    list << obj->children().at(j);
            }
        }
    }
    return list;
}
static QList<int> standardPrimeNumberList()
{
    return QList<int>({1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,3083,3089,3109,3119,3121,3137,3163,3167,3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,3259,3271,3299,3301,3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,3547,3557,3559,3571,3581,3583,3593,3607,3613,3617,3623,3631,3637,3643,3659,3671,3673,3677,3691,3697,3701,3709,3719,3727,3733,3739,3761,3767,3769,3779,3793,3797,3803,3821,3823,3833,3847,3851,3853,3863,3877,3881,3889,3907,3911,3917,3919,3923,3929,3931,3943,3947,3967,3989,4001,4003,4007,4013,4019,4021,4027,4049,4051,4057,4073,4079,4091,4093,4099,4111,4127,4129,4133,4139,4153,4157,4159,4177,4201,4211,4217,4219,4229,4231,4241,4243,4253,4259,4261,4271,4273,4283,4289,4297,4327,4337,4339,4349,4357,4363,4373,4391,4397,4409,4421,4423,4441,4447,4451,4457,4463,4481,4483,4493,4507,4513,4517,4519,4523,4547,4549,4561,4567,4583,4591,4597,4603,4621,4637,4639,4643,4649,4651,4657,4663,4673,4679,4691,4703,4721,4723,4729,4733,4751,4759,4783,4787,4789,4793,4799,4801,4813,4817,4831,4861,4871,4877,4889,4903,4909,4919,4931,4933,4937,4943,4951,4957,4967,4969,4973,4987,4993,4999,5003,5009,5011,5021,5023,5039,5051,5059,5077,5081,5087,5099,5101,5107,5113,5119,5147,5153,5167,5171,5179,5189,5197,5209,5227,5231,5233,5237,5261,5273,5279,5281,5297,5303,5309,5323,5333,5347,5351,5381,5387,5393,5399,5407,5413,5417,5419,5431,5437,5441,5443,5449,5471,5477,5479,5483,5501,5503,5507,5519,5521,5527,5531,5557,5563,5569,5573,5581,5591,5623,5639,5641,5647,5651,5653,5657,5659,5669,5683,5689,5693,5701,5711,5717,5737,5741,5743,5749,5779,5783,5791,5801,5807,5813,5821,5827,5839,5843,5849,5851,5857,5861,5867,5869,5879,5881,5897,5903,5923,5927,5939,5953,5981,5987,6007,6011,6029,6037,6043,6047,6053,6067,6073,6079,6089,6091,6101,6113,6121,6131,6133,6143,6151,6163,6173,6197,6199,6203,6211,6217,6221,6229,6247,6257,6263,6269,6271,6277,6287,6299,6301,6311,6317,6323,6329,6337,6343,6353,6359,6361,6367,6373,6379,6389,6397,6421,6427,6449,6451,6469,6473,6481,6491,6521,6529,6547,6551,6553,6563,6569,6571,6577,6581,6599,6607,6619,6637,6653,6659,6661,6673,6679,6689,6691,6701,6703,6709,6719,6733,6737,6761,6763,6779,6781,6791,6793,6803,6823,6827,6829,6833,6841,6857,6863,6869,6871,6883,6899,6907,6911,6917,6947,6949,6959,6961,6967,6971,6977,6983,6991,6997,7001,7013,7019,7027,7039,7043,7057,7069,7079,7103,7109,7121,7127,7129,7151,7159,7177,7187,7193,7207,7211,7213,7219,7229,7237,7243,7247,7253,7283,7297,7307,7309,7321,7331,7333,7349,7351,7369,7393,7411,7417,7433,7451,7457,7459,7477,7481,7487,7489,7499,7507,7517,7523,7529,7537,7541,7547,7549,7559,7561,7573,7577,7583,7589,7591,7603,7607,7621,7639,7643,7649,7669,7673,7681,7687,7691,7699,7703,7717,7723,7727,7741,7753,7757,7759,7789,7793,7817,7823,7829,7841,7853,7867,7873,7877,7879,7883,7901,7907,7919,7927,7933,7937,7949,7951,7963,7993,8009,8011,8017,8039,8053,8059,8069,8081,8087,8089,8093,8101,8111,8117,8123,8147,8161,8167,8171,8179,8191,8209,8219,8221,8231,8233,8237,8243,8263,8269,8273,8287,8291,8293,8297,8311,8317,8329,8353,8363,8369,8377,8387,8389,8419,8423,8429,8431,8443,8447,8461,8467,8501,8513,8521,8527,8537,8539,8543,8563,8573,8581,8597,8599,8609,8623,8627,8629,8641,8647,8663,8669,8677,8681,8689,8693,8699,8707,8713,8719,8731,8737,8741,8747,8753,8761,8779,8783,8803,8807,8819,8821,8831,8837,8839,8849,8861,8863,8867,8887,8893,8923,8929,8933,8941,8951,8963,8969,8971,8999,9001,9007,9011,9013,9029,9041,9043,9049,9059,9067,9091,9103,9109,9127,9133,9137,9151,9157,9161,9173,9181,9187,9199,9203,9209,9221,9227,9239,9241,9257,9277,9281,9283,9293,9311,9319,9323,9337,9341,9343,9349,9371,9377,9391,9397,9403,9413,9419,9421,9431,9433,9437,9439,9461,9463,9467,9473,9479,9491,9497,9511,9521,9533,9539,9547,9551,9587,9601,9613,9619,9623,9629,9631,9643,9649,9661,9677,9679,9689,9697,9719,9721,9733,9739,9743,9749,9767,9769,9781,9787,9791,9803,9811,9817,9829,9833,9839,9851,9857,9859,9871,9883,9887,9901,9907,9923,9929,9931,9941,9949,9967,9973});
}
static bool isPrimeNumber(int num)
{
    if(num != num)
        return false;
    if(num <= 0)
        return false;
    if(QList<int>({1,2,3,5,7,11,13}).contains(num))
        return true;
    QString str = QString::number(num);
    int end = str.right(1).toInt();
    if(end == 2 || end == 4 || end == 5 || end == 6 || end == 8 || end == 0)
        return false;
    else if(num%3 == 0 || num%7 == 0 || num%11 == 0)
        return false;

    if(standardPrimeNumberList().contains(num))
        return true;

    bool ret = true;
    int current = 13;
    double half = double(num)/2.0;
    while(ret && double(current) < half && current < num && current <= 2147483647)
    {
        int end1 = QString::number(current).right(1).toInt();
        if(end1 != 0 && end1 != 2 && end1 != 4 && end1 != 5 && end1 != 6 && end1 != 8)
        {
            ret = (num%current != 0);
        }
        current++;
    }
    return ret;
}
static QString getNextWord(QString w)
{
    if(w == "A")
        return "B";
    if(w == "B")
        return "C";
    if(w == "C")
        return "D";
    if(w == "D")
        return "E";
    if(w == "E")
        return "F";
    if(w == "F")
        return "G";
    if(w == "G")
        return "H";
    if(w == "H")
        return "I";
    if(w == "I")
        return "J";
    if(w == "J")
        return "K";
    if(w == "K")
        return "L";
    if(w == "L")
        return "M";
    if(w == "M")
        return "N";
    if(w == "N")
        return "O";
    if(w == "O")
        return "P";
    if(w == "P")
        return "Q";
    if(w == "Q")
        return "R";
    if(w == "R")
        return "S";
    if(w == "S")
        return "T";
    if(w == "T")
        return "U";
    if(w == "U")
        return "V";
    if(w == "V")
        return "W";
    if(w == "W")
        return "X";
    if(w == "X")
        return "Y";
    if(w == "Y")
        return "Z";
    if(w == "Z")
        return "";
    if(w == "a")
        return "b";
    if(w == "b")
        return "c";
    if(w == "c")
        return "d";
    if(w == "d")
        return "e";
    if(w == "e")
        return "f";
    if(w == "f")
        return "g";
    if(w == "g")
        return "h";
    if(w == "h")
        return "i";
    if(w == "i")
        return "j";
    if(w == "j")
        return "k";
    if(w == "k")
        return "l";
    if(w == "l")
        return "m";
    if(w == "m")
        return "n";
    if(w == "n")
        return "o";
    if(w == "o")
        return "p";
    if(w == "p")
        return "q";
    if(w == "q")
        return "r";
    if(w == "r")
        return "s";
    if(w == "s")
        return "t";
    if(w == "t")
        return "u";
    if(w == "u")
        return "v";
    if(w == "v")
        return "w";
    if(w == "w")
        return "x";
    if(w == "x")
        return "y";
    if(w == "y")
        return "z";
    if(w == "z")
        return "";
    return "";
}
static int getLongestStringIndex(QStringList list)
{
    int index = 0;
    int maxlength = -1;
    int result = -1;
    while(index < list.count())
    {
        int currentlength = list.at(index).length();
        if(currentlength > maxlength)
        {
            maxlength = currentlength;
            result = index;
        }
        index++;
    }
    return result;
}
static QStringList toStringList(QList<QByteArray> list)
{
    QStringList ret;
    for(QByteArray byte : list)
    {
        ret << QString(byte);
    }
    return ret;
}
static QString toString(bool b)
{
    if(b == true)
        return QString("true");
    else
        return QString("false");
}
static QString toString(QtMsgType type)
{
    QString text;
    switch (type)
    {
        case QtDebugMsg:
            text = "Debug";
            break;
        case QtWarningMsg:
            text = "Warning";
            break;
        case QtInfoMsg:
            text = "Info";
            break;
        case QtCriticalMsg:
            text = "Critical";
            break;
        case QtFatalMsg:
            text = "Fatal";
            break;
    }
    return text;
}
#ifdef QMEDIAPLAYER_H
static QString toString(QMediaPlayer::Error error)
{
    if(error == QMediaPlayer::NoError)
        return "QMediaPlayer::NoError";
    else if(error == QMediaPlayer::ResourceError)
        return "QMediaPlayer::ResourceError";
    else if(error == QMediaPlayer::FormatError)
        return "QMediaPlayer::FormatError";
    else if(error == QMediaPlayer::NetworkError)
        return "QMediaPlayer::NetworkError";
    else if(error == QMediaPlayer::AccessDeniedError)
        return "QMediaPlayer::AccessDeniedError";
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    else if(error == QMediaPlayer::ServiceMissingError)
        return "QMediaPlayer::ServiceMissingError";
    else if(error == QMediaPlayer::MediaIsPlaylist)
        return "QMediaPlayer::MediaIsPlaylist";
    else
        return QString();
#else
    return QString();
#endif
}
#endif
static bool isBool(QString s)
{
    if(s == "true" || s == "false")
        return true;
    else
        return false;
}
static bool toBool(QString s)
{
    if(s == "true")
        return true;
    else if(s == "false")
        return false;
    else
        return bool(s.toInt());
}
static QString calculateHash(QString filePath,QCryptographicHash::Algorithm method)
{
    QFile file(filePath);
    QCryptographicHash hash(method);

    if(file.open(QIODevice::ReadOnly) || file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            QByteArray content = file.read(1024 * 1024 * 100);
            hash.addData(content);
        }
        QByteArray ret = hash.result();
        file.close();
        return ret.toHex();
    }
    else
    {
        return QString();
    }
}
static QString calculateHashFromByte(QByteArray arr,QCryptographicHash::Algorithm method)
{
    QCryptographicHash hash(method);
    hash.addData(arr);
    QByteArray ret = hash.result();
    return ret.toHex();
}
static QString getMd5(QString filePath) {return calculateHash(filePath,QCryptographicHash::Md5);}
static QString getMd5FromByte(QByteArray arr) {return calculateHashFromByte(arr,QCryptographicHash::Md5);}
static QString getSha1(QString filePath) {return calculateHash(filePath,QCryptographicHash::Sha1);}
static QString getSha1FromByte(QByteArray arr) {return calculateHashFromByte(arr,QCryptographicHash::Sha1);}

#define javaPackage "com/MyActivity/MainActivity"
namespace Android {
#ifndef Q_OS_ANDROID
typedef int QJniObject;
typedef int QJniEnvironment;
#endif
#if QT_VERSION_MAJOR == 5 && defined(Q_OS_ANDROID)
typedef QAndroidJniObject QJniObject;
typedef QAndroidJniEnvironment QJniEnvironment;
#endif
static void showNativeToast(const QString &message,bool waitforfinished = false)
{
#ifdef Q_OS_ANDROID
    /*
    QJniObject javaToast = QJniObject::fromString(message);
    QJniObject::callStaticMethod<void>(javaPackage,
                                           "makeToast",
                                           "(Ljava/lang/String;)V",
                                           javaToast.object<jstring>());
                                           */
    QFuture<void> f = QNativeInterface::QAndroidApplication::runOnAndroidMainThread([message](){
        QJniObject context = QtAndroidPrivate::activity();
        QJniObject javaString = QJniObject::fromString(message);
        QJniObject toast = QJniObject::callStaticObjectMethod("android/widget/Toast", "makeText","(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",context.object(),javaString.object<jstring>(),jint(0));
        toast.callMethod<void>("show");
    });
    if(waitforfinished)
    {
        f.waitForFinished();
    }
#else
    qDebug() << message;
#endif
}
static QJniObject toJniFile(QString filePath)
{
#ifdef Q_OS_ANDROID
    QJniObject jFile("java/io/File","(Ljava/lang/String;)V",QJniObject::fromString(filePath).object());
    return jFile;
#else
    return 0;
#endif
}
static QJniObject parseUri(QString filePath)
{
#ifdef Q_OS_ANDROID
    if(!filePath.startsWith("file://") && !filePath.startsWith("content://"))
        filePath = "file://" + filePath;
    return QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;",QJniObject::fromString(filePath).object());
#else
    return 0;
#endif
}
static QString getNativeMimeType(QString fileName)
{
#ifdef Q_OS_ANDROID
    QJniObject context = QNativeInterface::QAndroidApplication::context();
    QJniObject contentResolver = context.callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");
    QJniObject type = contentResolver.callObjectMethod("getType","(Landroid/net/Uri;)Ljava/lang/String;",parseUri(fileName).object());
    return type.toString();
#endif
    return QString();
}
static void disableStrictMode()
{
#ifdef Q_OS_ANDROID
    QJniObject builder("android/os/StrictMode$VmPolicy$Builder");
    builder.callObjectMethod("detectAll", "()Landroid/os/StrictMode$VmPolicy$Builder;");
    QJniObject policy = builder.callObjectMethod("build", "()Landroid/os/StrictMode$VmPolicy;");
    QJniObject::callStaticMethod<void>("android/os/StrictMode", "setVmPolicy","(Landroid/os/StrictMode$VmPolicy;)V",policy.object<jobject>());
#endif
}
static QString getPackageName()
{
    QString packageName = "";
#ifdef Q_OS_ANDROID
#ifdef Core_Private_Enabled
    QJniObject context = QtAndroidPrivate::context();
    QJniObject packageNameObject = context.callObjectMethod("getPackageName", "()Ljava/lang/String;");
    if (packageNameObject.isValid())
    {
         packageName = packageNameObject.toString();
    }
#else
    QString path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation).replace("\\","/");
    if(path.endsWith("/"))
        path.chop(1);
    while(!path.endsWith("/"))
        path.chop(1);
    packageName = QDir(path).dirName();
#endif
#endif
    return packageName;
}
static int getSystemVersion()
{
    int androidSdkVersion = -1;
#ifdef Q_OS_ANDROID
    QJniObject context = QtAndroidPrivate::context();
    QJniObject sdkVersion = QJniObject::getStaticObjectField<jstring>("android/os/Build$VERSION", "RELEASE");
    if (sdkVersion.isValid())
    {
        androidSdkVersion = QJniObject::callStaticMethod<jint>("java/lang/Integer", "parseInt", "(Ljava/lang/String;)I", sdkVersion.object<jstring>());
    }
    if(androidSdkVersion == 0)
    {
        QJniEnvironment env;
        QJniObject sdkVersion = QJniObject::getStaticObjectField<jstring>("android/os/Build$VERSION", "RELEASE");
        if (sdkVersion.isValid())
        {
            std::string version = env->GetStringUTFChars(static_cast<jstring>(sdkVersion.object()), nullptr);
            androidSdkVersion = std::stoi(version);
        }
    }
#endif
    return androidSdkVersion;
}
static int getSdkVersion()
{
    int sdkversion = -1;
#ifdef Q_OS_ANDROID
    sdkversion = QJniObject::getStaticField<jint>("android.os.Build$VERSION", "SDK_INT");
#endif
    return sdkversion;
}
static int getTargetSdkVersion(QString packageName = getPackageName())
{
#ifdef Q_OS_ANDROID
    QJniObject packageManager = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
    QJniObject applicationInfo = packageManager.callObjectMethod("getApplicationInfo", "(Ljava/lang/String;I)Landroid/content/pm/ApplicationInfo;", QJniObject::fromString(packageName).object<jobject>(), 0);
    return applicationInfo.getField<jint>("targetSdkVersion");
#else
    return -1;
#endif
}
static QString getActivityName()
{
#ifdef Q_OS_ANDROID
    QJniObject activity = QtAndroidPrivate::activity();
    if (activity.isValid())
    {
        QJniObject activityClass = activity.callObjectMethod(
            "getClass", "()Ljava/lang/Class;"
        );
        QJniObject activityName = activityClass.callObjectMethod(
            "getName", "()Ljava/lang/String;"
        );
        if(activityName.isValid())
        {
            return activityName.toString();
        }
    }
    return QString();
#endif
    return QString();
}
static QJniObject getPackageManager()
{
#ifdef Q_OS_ANDROID
    return QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
#else
    return 0;
#endif
}
static bool isContentProviderUri(QString uri)
{
#ifdef Q_OS_ANDROID
    return (uri.startsWith("content://") && !uri.startsWith("content://com.android.externalstorage.documents/"));
#else
    return false;
#endif
}
static bool isExternalStorageUri(QString uri)
{
#ifdef Q_OS_ANDROID
    return uri.startsWith("content://com.android.externalstorage.documents/");
#else
    return false;
#endif
}
static QString getExternalStorageUriFromPath(QString path)
{
    QString head;
    if(QFileInfo(path).isFile())
    {
        head = "content://com.android.externalstorage.documents/document/primary%3A";
    }
    else if(QFileInfo(path).isDir())
    {
        head = "content://com.android.externalstorage.documents/tree/primary%3A";
    }
    else
    {
        return path;
    }
    if(path.startsWith("/sdcard/"))
    {
        path.remove(0,QString("/sdcard/").length());
    }
    else if(path.startsWith("/storage/emulated/0/"))
    {
        path.remove(0,QString("/storage/emulated/0/").length());
    }
    else if(path.startsWith("/sdcard"))
    {
        path.remove(0,QString("/sdcard").length());
    }
    else if(path.startsWith("/storage/emulated/0"))
    {
        path.remove(0,QString("/storage/emulated/0").length());
    }
    path.replace("/","%2F");
    path = head + path;
    return path;
}
static QString getRealPathFromExternalStorageUri(QString uri)
{
    int index = uri.indexOf("primary%3A");
    if(index != -1 && uri.startsWith("content://com.android.externalstorage.documents/"))
    {
        uri = uri.remove(0,index+QString("primary%3A").length());
        uri = "/sdcard/" + uri;
        uri.replace("%2F","/");
    }
    return uri;
}
static QString getRealPathFromUri(const QUrl &url)
{
    QString path = "";

    QFileInfo info = QFileInfo(url.toString());
    QString s = getRealPathFromExternalStorageUri(url.toString());
    if(QFile::exists(s))
    {
        return s;
    }
    if(info.isFile())
    {
        QString abs = QFileInfo(url.toString()).absoluteFilePath();
        if(!abs.isEmpty() && abs != url.toString() && QFileInfo(abs).isFile())
        {
            return abs;
        }
    }
    else if(info.isDir())
    {
        QString abs = QFileInfo(url.toString()).absolutePath();
        if(!abs.isEmpty() && abs != url.toString() && QFileInfo(abs).isDir())
        {
            return abs;
        }
    }
    QString localfile = url.toLocalFile();
    if((QFileInfo(localfile).isFile() || QFileInfo(localfile).isDir()) && localfile != url.toString())
    {
        return localfile;
    }
#ifdef Q_OS_ANDROID
    QJniObject jUrl = QJniObject::fromString(url.toString());
    QJniObject jContext = QtAndroidPrivate::context();
    QJniObject jContentResolver = jContext.callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");
    QJniObject jUri = QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", jUrl.object<jstring>());
    QJniObject jCursor = jContentResolver.callObjectMethod("query", "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;", jUri.object<jobject>(), nullptr, nullptr, nullptr, nullptr);
    QJniObject jScheme = jUri.callObjectMethod("getScheme", "()Ljava/lang/String;");
    QJniObject authority;
    if(jScheme.isValid())
    {
        authority = jUri.callObjectMethod("getAuthority", "()Ljava/lang/String;");
    }
    if(authority.isValid() && authority.toString() == "com.android.externalstorage.documents")
    {
        QJniObject jPath = jUri.callObjectMethod("getPath", "()Ljava/lang/String;");
        path = jPath.toString();
    }
    else if(jCursor.isValid() && jCursor.callMethod<jboolean>("moveToFirst"))
    {
        QJniObject jColumnIndex = QJniObject::fromString("_data");
        jint columnIndex = jCursor.callMethod<jint>("getColumnIndexOrThrow", "(Ljava/lang/String;)I", jColumnIndex.object<jstring>());
        QJniObject jRealPath = jCursor.callObjectMethod("getString", "(I)Ljava/lang/String;", columnIndex);
        path = jRealPath.toString();
        if(authority.isValid() && authority.toString().startsWith("com.android.providers") && !url.toString().startsWith("content://media/external/"))
        {
            QStringList list = path.split(":");
            if(list.count() == 2)
            {
                QString type = list.at(0);
                QString id = list.at(1);
                if(type == "image")
                    type = type + "s";
                if(type == "document" || type == "documents")
                    type = "file";
                if(type == "msf" || type == "download")
                    type = "downloads";
                if(QList<QString>({"images","video","audio"}).contains(type))
                    type = type + "/media";
                path = "content://media/external/"+type;
                path = path + "/" + id;
                return getRealPathFromUri(path);
            }
        }
    }
    else
    {
        QJniObject jPath = jUri.callObjectMethod("getPath", "()Ljava/lang/String;");
        path = jPath.toString();
    }

    if(path.startsWith("primary:"))
    {
        path = path.remove(0,QString("primary:").length());
        path = "/sdcard/" + path;
    }
    else if(path.startsWith("/document/primary:"))
    {
        path = path.remove(0,QString("/document/primary:").length());
        path = "/sdcard/" + path;
    }
    else if(path.startsWith("/tree/primary:"))
    {
        path = path.remove(0,QString("/tree/primary:").length());
        path = "/sdcard/" + path;
    }
    else if(path.startsWith("/storage/emulated/0"))
    {
        path = path.remove(0,QString("/storage/emulated/0").length());
        path = "/sdcard" + path;
    }
    else if(path.startsWith("/tree//"))
    {
        path = path.remove(0,QString("/tree//").length());
        path = "/" + path;
    }
    if(!QFileInfo(path).isFile() && !QFileInfo(path).isDir() && !path.startsWith("/data"))
        return url.toString();
    return path;
#else
    return url.toString();
#endif

}
static void startIntent(QString IntentString,bool append = false,bool waitforfinished = false,QString packageName = getPackageName())
{
/*
android.settings.MANAGE_ALL_FILES_ACCESS_PERMISSION 所有文件权限
android.settings.action.MANAGE_OVERLAY_PERMISSION 悬浮窗
android.settings.MANAGE_UNKNOWN_APP_SOURCES 安装应用
android.settings.APPLICATION_DETAILS_SETTINGS 详细信息
android.settings.SETTINGS 系统设置
*/
#ifdef Q_OS_ANDROID
    QEventLoop* loop = new QEventLoop();
    //bool usejni = false;

    if(IntentString.startsWith("ACTION_"))
    {
        IntentString = "android.settings." + IntentString.remove(0,QString("ACTION_").length());
    }
    if(IntentString == "android.settings.MANAGE_ALL_FILES_ACCESS_PERMISSION" && append)
        IntentString = "android.settings.MANAGE_APP_ALL_FILES_ACCESS_PERMISSION";
    if(IntentString == "android.settings.MANAGE_APP_ALL_FILES_ACCESS_PERMISSION" && !append)
        IntentString = "android.settings.MANAGE_ALL_FILES_ACCESS_PERMISSION";
    QJniObject ACTION = QJniObject::fromString(IntentString);
    QJniObject intent("android/content/Intent");
    intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", ACTION.object());
    if(append)
    {
        QJniObject uri = QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", QJniObject::fromString("package:" + packageName).object());
        intent.callObjectMethod("setData", "(Landroid/net/Uri;)Landroid/content/Intent;", uri.object());
    }

    if(waitforfinished)
    {
        auto callbackFunc = [loop](int requestCode, int resultCode, const QJniObject &data){
            qDebug() << requestCode << resultCode << data.toString() << bool(data.isValid());
            loop->quit();
        };
        QtAndroidPrivate::startActivity(intent,0,callbackFunc);
        loop->exec();
    }
    else
    {
        QtAndroidPrivate::startActivity(intent,0);
    }
#endif
}
static void setScreenOrientation(int orientation = -1)
{
#ifdef Q_OS_ANDROID
    QJniObject activity = QtAndroidPrivate::activity();
    if (activity.isValid())
    {
        if(orientation == Qt::LandscapeOrientation || orientation == 0)//横
        {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", 0);
        }
        else if(orientation == Qt::PortraitOrientation || orientation == 1)//竖
        {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", 1);
        }
        else if(orientation == Qt::PrimaryOrientation || orientation == -1)//自由
        {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", 2);
        }
        else
        {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", orientation);
        }
    }
#endif
}
static QString getModel()
{
#ifdef Q_OS_ANDROID
    QJniObject build = QJniObject::getStaticObjectField(
        "android/os/Build",
        "MODEL",
        "Ljava/lang/String;"
    );
    return build.toString();
#else
    return QString();
#endif
}
static QString getBrand()
{
#ifdef Q_OS_ANDROID
    QJniObject build = QJniObject::getStaticObjectField(
        "android/os/Build",
        "BRAND",
        "Ljava/lang/String;"
    );
    return build.toString();
#else
    return QString();
#endif
}
static bool checkPermission(QString permissionString)
{
#ifdef Q_OS_ANDROID
    QFuture<QtAndroidPrivate::PermissionResult> f = QtAndroidPrivate::checkPermission(permissionString);
    f.waitForFinished();
    return (f.result() == QtAndroidPrivate::PermissionResult::Authorized);
#else
    return false;
#endif
}
static bool requestPermission(QString permissionString)
{
#ifdef Q_OS_ANDROID
    QFuture<QtAndroidPrivate::PermissionResult> f = QtAndroidPrivate::requestPermission(permissionString);
    f.waitForFinished();
    return (f.result() == QtAndroidPrivate::PermissionResult::Authorized);
#else
    return false;
#endif
}
static bool hasStroagePermission()
{
#ifdef Q_OS_ANDROID
    if(!hasPathPermission("/sdcard"))
        return false;
    else
        return true;
#else
    return true;
#endif
}
static bool requestStroagePermission()
{
#ifdef Q_OS_ANDROID
    if(hasPathPermission("/sdcard",QIODevice::ReadWrite))
        return true;
    requestPermission("android.permission.READ_MEDIA_VIDEO");
    requestPermission("android.permission.READ_MEDIA_IMAGES");
    requestPermission("android.permission.READ_MEDIA_AUDIO");
    requestPermission("android.permission.READ_EXTERNAL_STORAGE");
    requestPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    startIntent("android.settings.MANAGE_ALL_FILES_ACCESS_PERMISSION",true,true);
    return hasPathPermission("/sdcard");
#else
#ifdef Q_OS_WIN
    return hasPathPermission("C:/");
#else
    return true;
#endif
#endif
}
static bool hasNotificationPermission() {return checkPermission("android.permission.POST_NOTIFICATIONS");}
static bool requestNotificationPermission() {return requestPermission("android.permission.POST_NOTIFICATIONS");}
static bool saveMediaToAlbum(QString mediaFilePath)
{
#ifdef Q_OS_ANDROID
    if(QFile::exists(mediaFilePath))
    {
        QJniEnvironment env;
        QJniObject javaFilePath = QJniObject::fromString(mediaFilePath);
        jobjectArray javaFilePathArray = env->NewObjectArray(1, env->FindClass("java/lang/String"), nullptr);
        env->SetObjectArrayElement(javaFilePathArray, 0, javaFilePath.object<jstring>());

        QJniObject mediaScanner("android/media/MediaScannerConnection");
        mediaScanner.callStaticMethod<void>("android/media/MediaScannerConnection","scanFile", "(Landroid/content/Context;[Ljava/lang/String;[Ljava/lang/String;Landroid/media/MediaScannerConnection$OnScanCompletedListener;)V",
                                            QJniObject(QtAndroidPrivate::context()).object(),
                                            javaFilePathArray,
                                            nullptr, nullptr);
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static QStringList getInstalledPackageList()
{
    QStringList list;
#ifdef Q_OS_ANDROID
    QJniObject context = QtAndroidPrivate::context();
    QJniObject packageManager = context.callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
    int flags = QJniObject::getStaticField<jint>("android/content/pm/PackageManager", "MATCH_UNINSTALLED_PACKAGES");
    QJniObject installedPackageInfoList = packageManager.callObjectMethod("getInstalledPackages", "(I)Ljava/util/List;", flags);
    jint packageCount = installedPackageInfoList.callMethod<jint>("size");
    for(jint i = 0; i < packageCount; ++i)
    {
        QJniObject packageInfo = installedPackageInfoList.callObjectMethod("get", "(I)Ljava/lang/Object;", i);
        QJniObject packageName = packageInfo.getObjectField("packageName", "Ljava/lang/String;");
        QString packageNameStr = packageName.toString();
        list << packageNameStr;
    }
#endif
    return list;
}
static bool startApplication(QString packageName,QString activityName = "")
{
    /*
    com.mojang.minecraftpe com.mojang.minecraftpe.MainActivity
    Minecraft PE package name and activity name for test
    */
#ifdef Q_OS_ANDROID
    QJniObject intent("android/content/Intent");
    if(intent.isValid() && packageName != "" && getInstalledPackageList().contains(packageName))
    {
        if(activityName == "")
        {
            QJniObject activity = QtAndroidPrivate::activity();
            QJniObject packageManager = activity.callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
            intent = packageManager.callObjectMethod("getLaunchIntentForPackage", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(packageName).object<jstring>());
        }
        else
        {
            intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.action.MAIN").object<jstring>());
            intent.callObjectMethod("setClassName", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(packageName).object<jstring>(), QJniObject::fromString(activityName).object<jstring>());
            intent.callObjectMethod("putExtra", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(packageName).object<jstring>(), QJniObject::fromString(activityName).object<jstring>());
            intent.callObjectMethod("addCategory", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.category.LAUNCHER").object<jstring>());
            intent.callObjectMethod("setFlags", "(I)Landroid/content/Intent;", QJniObject::getStaticField<jint>("android/content/Intent", "FLAG_ACTIVITY_NEW_TASK"));
        }

        QEventLoop* loop = new QEventLoop();
        auto callbackFunc = [loop](int requestCode, int resultCode, const QJniObject &data){
            //qDebug() << requestCode << " " << resultCode << "\n" << data.toString() << " " << (data==QJniObject());
            loop->quit();
        };
        QtAndroidPrivate::startActivity(intent, 0, callbackFunc);
        loop->exec();
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static QJniObject createBitmap(int width,int height)
{
#ifdef Q_OS_ANDROID
    QJniObject config = QJniObject::getStaticObjectField("android/graphics/Bitmap$Config",
                                                                           "ARGB_8888",
                                                                           "Landroid/graphics/Bitmap$Config;");

    return QJniObject::callStaticObjectMethod("android/graphics/Bitmap",
                                                         "createBitmap",
                                                         "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;",
                                                         width, height, config.object());
#else
    return 0;
#endif
}
static QJniObject createBitmap(QSize size) {return createBitmap(size.width(),size.height());}
static int getApplicationDefaultIconId()
{
#ifdef Q_OS_ANDROID
    return QJniObject::getStaticField<jint>("android/R$drawable", "sym_def_app_icon");
#endif
    return -1;
}
static int getApplicationIconId(QString packageName = getPackageName())
{
#ifdef Q_OS_ANDROID
    QJniObject packageManager = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
    QJniObject applicationInfo = packageManager.callObjectMethod("getApplicationInfo", "(Ljava/lang/String;I)Landroid/content/pm/ApplicationInfo;", QJniObject::fromString(packageName).object<jobject>(), 0);
    jint iconId = applicationInfo.getField<jint>("icon");
    if(iconId == 0)
    {
        iconId = getApplicationDefaultIconId();
    }
    return iconId;
#endif
    return -1;
}
static bool isApplicationUsingDefaultIcon(QString packageName = getPackageName())
{
#ifdef Q_OS_ANDROID
    QJniObject packageManager = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
    QJniObject applicationInfo = packageManager.callObjectMethod("getApplicationInfo", "(Ljava/lang/String;I)Landroid/content/pm/ApplicationInfo;", QJniObject::fromString(packageName).object<jobject>(), 0);
    jint iconId = applicationInfo.getField<jint>("icon");
    return (iconId == 0);
#else
    return false;
#endif
}
static QJniObject drawableToAndroidBitmap(QJniObject drawable)
{
#ifdef Q_OS_ANDROID
    jint intrinsicWidth = drawable.callMethod<jint>("getIntrinsicWidth");
    jint intrinsicHeight = drawable.callMethod<jint>("getIntrinsicHeight");
    QJniObject bitmap = createBitmap(intrinsicWidth,intrinsicHeight);
    QJniObject canvas("android/graphics/Canvas", "(Landroid/graphics/Bitmap;)V", bitmap.object<jobject>());
    QJniObject boundsRect("android/graphics/Rect", "(IIII)V", 0, 0, intrinsicWidth, intrinsicHeight);
    drawable.callMethod<void>("setBounds", "(Landroid/graphics/Rect;)V", boundsRect.object());
    drawable.callMethod<void>("draw", "(Landroid/graphics/Canvas;)V", canvas.object());
    return bitmap;
#else
    return 0;
#endif
}
static QJniObject getApplicationDefaultIconObject()
{
#ifdef Q_OS_ANDROID
    jint iconId = getApplicationDefaultIconId();
    QJniObject drawable = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getResources", "()Landroid/content/res/Resources;").callObjectMethod("getDrawable", "(I)Landroid/graphics/drawable/Drawable;", iconId);
    return drawableToAndroidBitmap(drawable);
#else
    return 0;
#endif
}
static QJniObject getApplicationIconObject(QString packageName = getPackageName()) {
#ifdef Q_OS_ANDROID
    if(isApplicationUsingDefaultIcon(packageName))
    {
        return getApplicationDefaultIconObject();
    }
    else
    {
        QJniObject packageManager = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
        QJniObject applicationInfo = packageManager.callObjectMethod("getApplicationInfo", "(Ljava/lang/String;I)Landroid/content/pm/ApplicationInfo;", QJniObject::fromString(packageName).object<jobject>(), 0);
        QJniObject drawable = packageManager.callObjectMethod("getApplicationIcon","(Landroid/content/pm/ApplicationInfo;)Landroid/graphics/drawable/Drawable;",applicationInfo.object<jobject>());
        return drawableToAndroidBitmap(drawable);
    }
#else
    return 0;
#endif
}
static QImage toImage(const QJniObject &bitmap)
{
#ifdef Q_OS_ANDROID
    QJniEnvironment qenv;
    JNIEnv* env = qenv.jniEnv();
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bitmap.object(), &info) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QImage();

    QImage::Format format;
    switch (info.format) {
    case ANDROID_BITMAP_FORMAT_RGBA_8888:
        format = QImage::Format_RGBA8888;
        break;
    case ANDROID_BITMAP_FORMAT_RGB_565:
        format = QImage::Format_RGB16;
        break;
    case ANDROID_BITMAP_FORMAT_RGBA_4444:
        format = QImage::Format_ARGB4444_Premultiplied;
        break;
    case ANDROID_BITMAP_FORMAT_A_8:
        format = QImage::Format_Alpha8;
        break;
    default:
        return QImage();
    }

    void *pixels;
    if (AndroidBitmap_lockPixels(env, bitmap.object(), &pixels) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QImage();

    QImage image(info.width, info.height, format);

    if (info.stride == uint32_t(image.bytesPerLine())) {
        memcpy((void*)image.constBits(), pixels, info.stride * info.height);
    } else {
        uchar *bmpPtr = static_cast<uchar *>(pixels);
        const unsigned width = std::min(info.width, (uint)image.width());
        const unsigned height = std::min(info.height, (uint)image.height());
        for (unsigned y = 0; y < height; y++, bmpPtr += info.stride)
            memcpy((void*)image.constScanLine(y), bmpPtr, width);
    }

    if (AndroidBitmap_unlockPixels(env, bitmap.object()) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QImage();

    image.convertedTo(QImage::Format_RGBA8888);
    return image;
#else
    return QImage();
#endif
}
static QImage getApplicationIcon(QString packageName = getPackageName()) {return toImage(getApplicationIconObject(packageName));}
static QImage getApplicationDefaultIcon() {return toImage(getApplicationDefaultIconObject());}
static QJniObject toAndroidBitmap(const QImage &img)
{
#ifdef Q_OS_ANDROID
    QImage image = img.format() == QImage::Format_RGBA8888 ? img : img.convertToFormat(QImage::Format_RGBA8888);
    QJniObject bitmap = createBitmap(img.width(), img.height());
    QJniEnvironment qenv;
    JNIEnv* env = qenv.jniEnv();
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bitmap.object(), &info) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QJniObject();

    if (info.format!= ANDROID_BITMAP_FORMAT_RGBA_8888)
        return QJniObject();

    void *pixels;
    if (AndroidBitmap_lockPixels(env, bitmap.object(), &pixels) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QJniObject();

    if (info.stride == uint32_t(image.bytesPerLine())) {
        memcpy(pixels, image.constBits(), info.stride * info.height);
    } else {
        uchar *bmpPtr = static_cast<uchar *>(pixels);
        const unsigned width = std::min(info.width, (uint)image.width());
        const unsigned height = std::min(info.height, (uint)image.height());
        for (unsigned y = 0; y < height; y++, bmpPtr += info.stride)
            memcpy(bmpPtr, image.constScanLine(y), width);
    }

    if (AndroidBitmap_unlockPixels(env, bitmap.object()) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QJniObject();

    return bitmap;
#else
    return 0;
#endif
}
static bool registerNativeMethod(const char* name,const char* signature,void* callBackPointer)
{
#ifdef Q_OS_ANDROID
    static JNINativeMethod methods[] {
    { name, signature, callBackPointer}
    };
    const char* kClassName = javaPackage;
    QJniEnvironment qtEnv;
    jclass clazz;
    JNIEnv *EV = qtEnv.operator ->();
    if(EV->ExceptionCheck())
    {
        EV->ExceptionDescribe();
        EV->ExceptionClear();
    }
    clazz =EV->FindClass(kClassName);
    if(clazz != NULL)
    {
        int i = EV->RegisterNatives(clazz, methods, 1);
        if(i == JNI_OK)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static void setKeepScreenOn(bool on)
{
#ifdef Q_OS_ANDROID
    QNativeInterface::QAndroidApplication::runOnAndroidMainThread([on](){
        QJniObject activity = QtAndroidPrivate::activity();
        QJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
        jint flags = QJniObject::getStaticField<jint>("android/view/WindowManager$LayoutParams", "FLAG_KEEP_SCREEN_ON");
        if(on)
            window.callMethod<void>("addFlags", "(I)V", flags);
        else
            window.callMethod<void>("clearFlags", "(I)V", flags);
    });
#endif
}
static bool setNativeWallpaper(QImage img)
{
#ifdef Q_OS_ANDROID
    if(checkPermission("android.permission.SET_WALLPAPER") && !img.isNull())
    {
        QJniObject bitmap = toAndroidBitmap(img);
        QJniObject wallpaperManager = QJniObject::callStaticObjectMethod("android/app/WallpaperManager", "getInstance", "(Landroid/content/Context;)Landroid/app/WallpaperManager;",QJniObject(QtAndroidPrivate::activity()).object<jobject>());
        wallpaperManager.callMethod<void>("setBitmap", "(Landroid/graphics/Bitmap;)V", bitmap.object<jobject>());
        return true;
    }
#endif
    return false;
}
static bool setNativeWallpaper(QString filePath)
{
#ifdef Q_OS_ANDROID
    QImage img;
    img.loadFromData(readfile(filePath));
    return setNativeWallpaper(img);
#endif
    return false;
}
static QJniObject getNativeWallpaperObject()
{
#ifdef Q_OS_ANDROID
    QJniObject wallpaperManager = QJniObject::callStaticObjectMethod("android/app/WallpaperManager", "getInstance", "(Landroid/content/Context;)Landroid/app/WallpaperManager;",QJniObject(QtAndroidPrivate::activity()).object<jobject>());
    QJniObject drawable = wallpaperManager.callObjectMethod("getDrawable","()Landroid/graphics/drawable/Drawable;");
    QJniObject bitmap = drawableToAndroidBitmap(drawable);
    return bitmap;
#else
    return 0;
#endif
}
static QImage getNativeWallpaper() {return toImage(getNativeWallpaperObject());}
static void showNotification(QString title,QString content,int notificationId = 0,QJniObject icon = getApplicationIconObject(),int iconId = getApplicationIconId(),bool autoCancel = true,bool ongoing = false,bool useprogress = false,QString channelID = "",QString channelName = "")
{
#ifdef Q_OS_ANDROID
    if(channelID.isEmpty())
    {
        channelID = "Soviet-Ball";
    }
    if(channelName.isEmpty())
    {
        channelName = "MyNotifier";
    }

    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    QJniObject channelID_object = QJniObject::fromString(channelID);
    QJniObject channelName_object = QJniObject::fromString(channelName);
    //int importance = QJniObject::getStaticField<jint>("android/app/NotificationManager", "IMPORTANCE_MAX");
    int importance = QJniObject::getStaticField<jint>("android/app/NotificationManager", "IMPORTANCE_DEFAULT");
    int sound = QJniObject::getStaticField<jint>("android/app/Notification","DEFAULT_SOUND");
    int flag1 = QJniObject::getStaticField<jint>("android/app/PendingIntent", "FLAG_MUTABLE");
    int flag2 = QJniObject::getStaticField<jint>("android/app/PendingIntent", "FLAG_UPDATE_CURRENT");
    int need_channel_api_level = 26;

    QJniObject notificationManager = activity.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", QJniObject::fromString("notification").object<jstring>());
    if(notificationManager.isValid())
    {
        QJniObject notificationBuilder;
        if(QNativeInterface::QAndroidApplication::sdkVersion() >= need_channel_api_level)
        {
            QJniObject notificationChannel("android/app/NotificationChannel",
                                                   "(Ljava/lang/String;Ljava/lang/CharSequence;I)V",
                                                   channelID_object.object<jstring>(),
                                                   channelName_object.object<jstring>(),
                                                   importance);
            notificationManager.callMethod<void>("createNotificationChannel", "(Landroid/app/NotificationChannel;)V", notificationChannel.object<jobject>());
            notificationBuilder = QJniObject("android/app/Notification$Builder",
                                             "(Landroid/content/Context;Ljava/lang/String;)V",
                                             activity.object<jobject>(),
                                             channelID_object.object<jstring>());
        }
        else
        {
            notificationBuilder = QJniObject("android/app/Notification$Builder",
                                             "(Landroid/content/Context;Ljava/lang/String;)V",
                                             activity.object<jobject>(),
                                             nullptr);
        }
        QJniObject activityClass = activity.callObjectMethod("getClass", "()Ljava/lang/Class;");
        QJniObject intent("android/content/Intent", "(Landroid/content/Context;Ljava/lang/Class;)V",
                                activity.object<jobject>(), activityClass.object<jstring>());
        QJniObject pendingIntent = QJniObject::callStaticObjectMethod("android/app/PendingIntent",
                                                                                   "getActivity",
                                                                                   "(Landroid/content/Context;ILandroid/content/Intent;I)Landroid/app/PendingIntent;",
                                                                                   activity.object<jobject>(), 0, intent.object<jobject>(),
                                                                                   flag1 | flag2);
        notificationBuilder.callObjectMethod("setSmallIcon", "(I)Landroid/app/Notification$Builder;", iconId);
        notificationBuilder.callObjectMethod("setLargeIcon", "(Landroid/graphics/Bitmap;)Landroid/app/Notification$Builder;", icon.object<jobject>());
        notificationBuilder.callObjectMethod("setContentTitle", "(Ljava/lang/CharSequence;)Landroid/app/Notification$Builder;", QJniObject::fromString(title).object<jstring>());
        notificationBuilder.callObjectMethod("setContentText", "(Ljava/lang/CharSequence;)Landroid/app/Notification$Builder;", QJniObject::fromString(content).object<jstring>());
        notificationBuilder.callObjectMethod("setDefaults", "(I)Landroid/app/Notification$Builder;", sound);
        notificationBuilder.callObjectMethod("setColor", "(I)Landroid/app/Notification$Builder;", QColor(Qt::green).rgb());
        notificationBuilder.callObjectMethod("setAutoCancel", "(Z)Landroid/app/Notification$Builder;", autoCancel);
        notificationBuilder.callObjectMethod("setOngoing", "(Z)Landroid/app/Notification$Builder;", ongoing);
        notificationBuilder.callObjectMethod("setColorized", "(Z)Landroid/app/Notification$Builder;", true);
        notificationBuilder.callObjectMethod("setContentIntent", "(Landroid/app/PendingIntent;)Landroid/app/Notification$Builder;",
                                  pendingIntent.object<jobject>());
        if(useprogress)
        {
            notificationBuilder.callObjectMethod("setProgress", "(IIZ)Landroid/app/Notification$Builder;",10,100,true);
        }
        QJniObject notification = notificationBuilder.callObjectMethod("build", "()Landroid/app/Notification;");
        notificationManager.callMethod<void>("notify", "(ILandroid/app/Notification;)V", notificationId, notification.object<jobject>());
    }
#endif
}
static void closeNotification(int id)
{
#ifdef Q_OS_ANDROID
    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    QJniObject notificationManager = activity.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", QJniObject::fromString("notification").object<jstring>());
    notificationManager.callMethod<void>("cancel", "(I)V", id);
#endif
}
static bool isClassAvailable(QString className)
{
#ifdef Q_OS_ANDROID
    className.replace(".","/");
    QJniEnvironment env;
    return (env->FindClass(className.toLatin1().data()) != NULL);
#else
    return false;
#endif
}
static bool isAndroidXEnabled() {return isClassAvailable("androidx/core/content/FileProvider");}
static bool isAndroidSupportV4Enabled() {return isClassAvailable("android/support/v4/content/FileProvider");}
static QString getFileProviderClassName(QString separator = ".")
{
    QString name;
    if(isAndroidXEnabled())
    {
        name = "androidx.core.content.FileProvider";
    }
    else if(isAndroidSupportV4Enabled())
    {
        name = "android.support.v4.content.FileProvider";
    }
    if(separator != ".")
    {
        name.replace(".",separator);
    }
    return name;
}
static bool isQtDefaultActivity()
{
#ifdef Q_OS_ANDROID
    QStringList list;
    list.append("org.qtproject.qt.android.bindings.QtActivity");
    list.append("org.qtproject.qt5.android.bindings.QtActivity");
    return list.contains(getActivityName());
#else
    return false;
#endif
}
static QString getUriForFile(QString path,QString provider_name = "",bool tryExteralFirst = false)
{
//流程：
//1.尝试转换为ExternalStorageUri
//2.尝试使用传入的provider名称参数
//3.尝试"包名+.qtprovider"
//3.尝试"包名+.provider"
//4.尝试"包名+.fileprovider"
#ifdef Q_OS_ANDROID
    QJniObject jFile("java/io/File","(Ljava/lang/String;)V",QJniObject::fromString(path).object());
    QJniObject context = QNativeInterface::QAndroidApplication::context();
    QJniObject uri;
    QString className = getFileProviderClassName("/");
    QString packageName = getPackageName();
    if(path.startsWith("content://"))
    {
        return path;
    }
    if(tryExteralFirst)
    {
        QString exteral = getExternalStorageUriFromPath(path);
        if(exteral != path && QFile::exists(exteral))
            return exteral;
    }
    QStringList list;
    if(!provider_name.isEmpty())
        list.append(provider_name);
    list.append(packageName + ".qtprovider");
    list.append(packageName + ".provider");
    list.append(packageName + ".fileprovider");
    list.append(packageName + ".fileProvider");
    if(!className.isEmpty())
    {
        for(QString name : list)
        {
            uri = QJniObject::callStaticObjectMethod(className.toLatin1().data(),"getUriForFile","(Landroid/content/Context;Ljava/lang/String;Ljava/io/File;)Landroid/net/Uri;",context.object(),QJniObject::fromString(name).object(),jFile.object());
            if(uri.isValid() && QFile::exists(uri.toString()))
                return uri.toString();
        }
    }
    if(!tryExteralFirst)
    {
        QString exteral = getExternalStorageUriFromPath(path);
        if(exteral != path && QFile::exists(exteral))
            return exteral;
    }
    return "file://"+path;
#else
    return "file://"+path;
#endif
}
static bool shareFile(QString path,QString provider_name = "",bool enableChooser = true)
{
#ifdef Q_OS_ANDROID
    if(path.startsWith("file://"))
        path = path.remove(0,QString("file://").length());
    if(!QFile::exists(path))
        return false;
    disableStrictMode();

    QString uri;
    if(isExternalStorageUri(path))
    {
        //process content://com.android.externalstorage.documents/...
        QString real = getRealPathFromUri(path);
        if(real != path && real.startsWith("/") && QFile::exists(real))
        {
            QString s = getUriForFile(real,provider_name);
            if(s != real && s.startsWith("content://") && !isExternalStorageUri(s) && s != path && QFile::exists(s))
                path = s;
            else
            {
                //fail to convert to fileprovider uri
                if(enableChooser)
                {
                    path = "file://" + real;
                }
                else
                {
                    return QDesktopServices::openUrl(path);
                }
            }
        }
        else
        {
            //fail to convert to real path
            return QDesktopServices::openUrl(path);
        }
    }

    //process real file path or processd fileprovider uri
    if((path.startsWith("content://") && !isExternalStorageUri(path)) || path.startsWith("file://"))
    {
        uri = path;
    }
    else
    {
        QString s = getUriForFile(path,provider_name);
        if(s != path && s.startsWith("content://") && !isExternalStorageUri(s) && s != path && QFile::exists(s))
            uri = s;
        else
            uri = "file://" + path;
    }

    if(enableChooser)
    {
        QJniObject intent("android/content/Intent","(Ljava/lang/String;)V",QJniObject::fromString("android.intent.action.SEND").object());
        QJniObject juri = QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;",QJniObject::fromString(uri).object());
        QJniObject type;
        if(uri.startsWith("file://"))
        {
            type = QJniObject::fromString("application/*");
        }
        else
        {
            type = QJniObject::fromString(getNativeMimeType(uri));
        }
        intent.callObjectMethod("addFlags", "(I)Landroid/content/Intent;",268435456|1);
        intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", type.object());
        intent.callObjectMethod("putExtra", "(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;", QJniObject::fromString("android.intent.extra.STREAM").object(), juri.object());
        QJniObject chooser = QJniObject::callStaticObjectMethod("android/content/Intent","createChooser","(Landroid/content/Intent;Ljava/lang/CharSequence;)Landroid/content/Intent;",intent.object(),QJniObject::fromString("分享文件").object());
        QtAndroidPrivate::startActivity(chooser,0);
        return true;
    }
    else
    {
        return QDesktopServices::openUrl(uri);
    }
#else
    return false;
#endif
}
static void installApplication(QString path,QString provider_name = "")
{
#ifdef Q_OS_ANDROID
    if(isExternalStorageUri(path))
    {
        path = getRealPathFromUri(path);
    }
    if(!path.startsWith("content://") && !path.startsWith("file://"))
    {
        path = getUriForFile(path,provider_name);
    }
    if(!path.startsWith("content://"))
    {
        disableStrictMode();
    }
    QJniObject uri = QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;",QJniObject::fromString(path).object());
    QJniObject intent("android/content/Intent","(Ljava/lang/String;)V",QJniObject::fromString("android.intent.action.VIEW").object());
    intent.callObjectMethod("addFlags", "(I)Landroid/content/Intent;",268435456|1);
    intent.callObjectMethod("setDataAndType", "(Landroid/net/Uri;Ljava/lang/String;)Landroid/content/Intent;",uri.object(),QJniObject::fromString("application/vnd.android.package-archive").object());
    QtAndroidPrivate::startActivity(intent,0);
#else
#endif
}
static QString getLauncherPackageName()
{
#ifdef Q_OS_ANDROID
    QJniObject intent("android/content/Intent");
    intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.action.MAIN").object<jstring>());
    intent.callObjectMethod("addCategory", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.category.HOME").object<jstring>());
    intent.callObjectMethod("addCategory", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.category.DEFAULT").object<jstring>());
    QJniObject resolveInfo = getPackageManager().callObjectMethod("resolveActivity", "(Landroid/content/Intent;I)Landroid/content/pm/ResolveInfo;", intent.object(),0);
    QJniObject activityInfo = resolveInfo.getObjectField("activityInfo","Landroid/content/pm/ActivityInfo;");
    QString packageName = activityInfo.getObjectField<jstring>("packageName").toString();
    return packageName;
#else
    return QString();
#endif
}
static void moveTaskToBack()
{
#ifdef Q_OS_ANDROID
    QJniObject intent("android/content/Intent");
    intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.action.MAIN").object<jstring>());
    intent.callObjectMethod("addCategory", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.category.HOME").object<jstring>());
    intent.callObjectMethod("addCategory", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.category.DEFAULT").object<jstring>());
    QtAndroidPrivate::startActivity(intent,0);
#endif
}
static QString startOpenDocumentIntent(QString action,QString dir,QString filter)
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
static QString getOpenFileName(QString dir = "",QString filter = "*/*") {return startOpenDocumentIntent("android.intent.action.OPEN_DOCUMENT",dir,filter);}
static QString getExistingDirectory(QString dir = "",QString filter = "*/*") {return startOpenDocumentIntent("android.intent.action.OPEN_DOCUMENT_TREE",dir,filter);}
static QString getSaveFileName(QString dir = "",QString filter = "*/*") {return startOpenDocumentIntent("android.intent.action.CREATE_DOCUMENT",dir,filter);}
static bool isRootedDevice()
{
#ifdef Q_OS_ANDROID
    return runCommand("which su").startsWith("/system");
#else
    return false;
#endif
}

class Notification : public QObject
{
    Q_OBJECT
public:
    enum Importance
    {
        None,
        Min,
        Low,
        Default,
        High,
        Max
    };
    static int need_channel_api_level() {return 26;}
    void show()
    {
    #ifdef Q_OS_ANDROID
        QJniObject activity = QNativeInterface::QAndroidApplication::context();
        QJniObject channelID_object = QJniObject::fromString(m_channel_id);
        QJniObject channelName_object = QJniObject::fromString(m_channel_name);
        int importance;
        int sound = QJniObject::getStaticField<jint>("android/app/Notification","DEFAULT_SOUND");
        int flag1 = QJniObject::getStaticField<jint>("android/app/PendingIntent", "FLAG_MUTABLE");
        int flag2 = QJniObject::getStaticField<jint>("android/app/PendingIntent", "FLAG_UPDATE_CURRENT");
        int need_channel_api_level = Notification::need_channel_api_level();

        if(m_importance == Default)
            importance = QJniObject::getStaticField<jint>("android/app/NotificationManager", "IMPORTANCE_DEFAULT");
        if(m_importance == High)
            importance = QJniObject::getStaticField<jint>("android/app/NotificationManager", "IMPORTANCE_HIGH");
        if(m_importance == Low)
            importance = QJniObject::getStaticField<jint>("android/app/NotificationManager", "IMPORTANCE_LOW");
        if(m_importance == None)
            importance = QJniObject::getStaticField<jint>("android/app/NotificationManager", "IMPORTANCE_NONE");
        if(m_importance == Min)
            importance = QJniObject::getStaticField<jint>("android/app/NotificationManager", "IMPORTANCE_MIN");
        if(m_importance == Max)
            importance = QJniObject::getStaticField<jint>("android/app/NotificationManager", "IMPORTANCE_MAX");

        QJniObject notificationManager = activity.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", QJniObject::fromString("notification").object<jstring>());
        if(notificationManager.isValid())
        {
            QJniObject notificationBuilder;
            if(QNativeInterface::QAndroidApplication::sdkVersion() >= need_channel_api_level)
            {
                QJniObject notificationChannel("android/app/NotificationChannel",
                                                       "(Ljava/lang/String;Ljava/lang/CharSequence;I)V",
                                                       channelID_object.object<jstring>(),
                                                       channelName_object.object<jstring>(),
                                                       importance);
                notificationManager.callMethod<void>("createNotificationChannel", "(Landroid/app/NotificationChannel;)V", notificationChannel.object<jobject>());
                notificationBuilder = QJniObject("android/app/Notification$Builder",
                                                 "(Landroid/content/Context;Ljava/lang/String;)V",
                                                 activity.object<jobject>(),
                                                 channelID_object.object<jstring>());
            }
            else
            {
                notificationBuilder = QJniObject("android/app/Notification$Builder",
                                                 "(Landroid/content/Context;Ljava/lang/String;)V",
                                                 activity.object<jobject>(),
                                                 nullptr);
            }
            QJniObject activityClass = activity.callObjectMethod("getClass", "()Ljava/lang/Class;");
            QJniObject intent("android/content/Intent", "(Landroid/content/Context;Ljava/lang/Class;)V",
                                    activity.object<jobject>(), activityClass.object<jstring>());
            QJniObject pendingIntent = QJniObject::callStaticObjectMethod("android/app/PendingIntent",
                                                                                       "getActivity",
                                                                                       "(Landroid/content/Context;ILandroid/content/Intent;I)Landroid/app/PendingIntent;",
                                                                                       activity.object<jobject>(), 0, intent.object<jobject>(),
                                                                                       flag1 | flag2);
            notificationBuilder.callObjectMethod("setSmallIcon", "(I)Landroid/app/Notification$Builder;", m_iconid);
            notificationBuilder.callObjectMethod("setLargeIcon", "(Landroid/graphics/Bitmap;)Landroid/app/Notification$Builder;", m_icon.object<jobject>());
            notificationBuilder.callObjectMethod("setContentTitle", "(Ljava/lang/CharSequence;)Landroid/app/Notification$Builder;", QJniObject::fromString(m_title).object<jstring>());
            notificationBuilder.callObjectMethod("setContentText", "(Ljava/lang/CharSequence;)Landroid/app/Notification$Builder;", QJniObject::fromString(m_content).object<jstring>());
            notificationBuilder.callObjectMethod("setDefaults", "(I)Landroid/app/Notification$Builder;", sound);
            notificationBuilder.callObjectMethod("setColor", "(I)Landroid/app/Notification$Builder;", m_color.rgb());
            notificationBuilder.callObjectMethod("setAutoCancel", "(Z)Landroid/app/Notification$Builder;", m_autocancel);
            notificationBuilder.callObjectMethod("setOngoing", "(Z)Landroid/app/Notification$Builder;", m_ongoing);
            notificationBuilder.callObjectMethod("setColorized", "(Z)Landroid/app/Notification$Builder;", m_colorized);
            notificationBuilder.callObjectMethod("setContentIntent", "(Landroid/app/PendingIntent;)Landroid/app/Notification$Builder;",
                                      pendingIntent.object<jobject>());
            if(m_progress_enabled)
            {
                bool busy = false;
                if(m_progress_max <= 0 && m_progress_value <= 0)
                    busy = true;
                notificationBuilder.callObjectMethod("setProgress", "(IIZ)Landroid/app/Notification$Builder;",m_progress_max,m_progress_value,busy);
            }
            QJniObject notification = notificationBuilder.callObjectMethod("build", "()Landroid/app/Notification;");
            notificationManager.callMethod<void>("notify", "(ILandroid/app/Notification;)V", m_id, notification.object<jobject>());
            m_ishidden = false;
        }
    #endif
    }
    void close()
    {
#ifdef Q_OS_ANDROID
        QJniObject activity = QNativeInterface::QAndroidApplication::context();
        QJniObject notificationManager = activity.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", QJniObject::fromString("notification").object<jstring>());
        notificationManager.callMethod<void>("cancel", "(I)V", m_id);
#endif
        m_ishidden = true;
    }
    void setID(int i)
    {
        if(!m_ishidden)
        {
            this->close();
        }
        m_id = i;
    }
    int ID() {return m_id;}
    void setChannelID(QString s)
    {
        m_channel_id = s;
    }
    QString channelID() {return m_channel_id;}
    void setChannelName(QString s)
    {
        m_channel_name = s;
    }
    QString channelName() {return m_channel_name;}
    void setAutoCancel(bool on)
    {
        m_autocancel = on;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    bool isAutoCancel() {return m_autocancel;}
    void setColorized(bool on)
    {
        m_colorized = on;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    bool isColorized() {return m_colorized;}
    void setProgressBarEnabled(bool on)
    {
        m_progress_enabled = on;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    bool isProgressBarEnabled() {return m_progress_enabled;}
    void setProgress(int value,int max)
    {
        m_progress_value = value;
        m_progress_max = max;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    void setProgress(QProgressBar* bar) {this->setProgress(bar->value(),bar->maximum()-bar->minimum());}
    int value() {return m_progress_value;}
    int max_value() {return m_progress_max;}
    void setColor(QColor c)
    {
        m_color = c;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    QColor color() {return m_color;}
    void setImportance(Importance i)
    {
        m_importance = i;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    Importance importance() {return m_importance;}
    void setTitle(QString s)
    {
        m_title = s;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    QString title() {return m_title;}
    void setContent(QString s)
    {
        m_content = s;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    QString content() {return m_content;}
    bool isHidden() {return m_ishidden;}
    void setIcon(QJniObject bitmap)
    {
        m_icon = bitmap;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    QJniObject icon() {return m_icon;}
    void setIconID(int n)
    {
        m_iconid = n;
        if(!m_ishidden)
        {
            this->show();
        }
    }
    int iconID() {return m_iconid;}
private:
    QString m_channel_id = qApp->applicationName();
    QString m_channel_name = "Default";
    QString m_title;
    QString m_content;
    int m_id = 0;
    int m_iconid = getApplicationIconId();
    bool m_colorized = true;
    bool m_progress_enabled = false;
    int m_progress_value = 0;
    int m_progress_max = 100;
    bool m_autocancel = true;
    bool m_ongoing = false;
    bool m_ishidden = true;
    QJniObject m_icon = getApplicationIconObject();
    QColor m_color = QColor();
    Importance m_importance = Default;
};

}

namespace Windows {
static int getProcessAmount(QString name)
{
#ifdef Q_OS_WIN
    QProcess* process = new QProcess;
    process->start("tasklist" ,QStringList()<<"/FI"<<"imagename eq "+name);
    process->waitForFinished();
    QString outputStr = QString::fromLocal8Bit(process->readAllStandardOutput());
    return getContainStringTimes(outputStr,name);
#else
    return -1;
#endif
}
static int killExecute(const QString& exe)
{
#ifdef Q_OS_WIN
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return -1;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return -1;
    }
    BOOL bRet = FALSE;
    DWORD dwPid = -1;
    while (Process32Next(hProcessSnap, &pe32))
    {
        int iLn = WideCharToMultiByte (CP_UTF8, 0, const_cast<LPWSTR> (pe32.szExeFile), static_cast< int>( sizeof(pe32.szExeFile)), NULL, 0, NULL, NULL);
        std:: string result (iLn, 0);
        WideCharToMultiByte (CP_UTF8, 0, pe32.szExeFile, static_cast< int>( sizeof(pe32.szExeFile)), const_cast<LPSTR> (result.c_str()), iLn, NULL, NULL);
        if(0 == strcmp(exe.toStdString().c_str(), result.c_str ()))
        {
            dwPid = pe32.th32ProcessID;
            bRet = TRUE;
            break;
        }
    }
    CloseHandle(hProcessSnap);
    //qDebug()<< "已终止进程,PID为" <<dwPid;
    HANDLE hProcess = NULL;
    hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,dwPid);
    if (hProcess== NULL)
    {
        return -1;
    }
    DWORD ret = TerminateProcess(hProcess, 0);
    if(ret == 0)
    {
        return -1;
    }
    return static_cast<int>(dwPid);
#else
    return -1;
#endif
}
static void showTabTip()
{

#ifdef Q_OS_WIN
    bool ret = false;
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    char* windir = getenv("windir");
    char winroot = 'c';
    if (!windir || strcmp(windir, ""))
    {
        winroot = windir[0];
    }
    char tabtip[260];
    char tabtipworksp[260];
    qDebug() << osvi.dwMajorVersion;
    if (osvi.dwMajorVersion <= 5)
    {
        // XP
        sprintf(tabtip, "%c:\\Windows\\System32\\osk.exe ", winroot);
        sprintf(tabtipworksp, "%c:\\Windows\\System32", winroot);
        ret = QProcess::startDetached(tabtip, QStringList(), tabtipworksp);
    }
    else if (osvi.dwMajorVersion >= 6)
    {
        if (osvi.dwMinorVersion >= 2)
        {
            //qDebug() << "???";
            // win8, win8.1, Windows Server 2012
            PVOID OldValue;
            BOOL bRet = Wow64DisableWow64FsRedirection(&OldValue);
            ShellExecuteA(NULL, "open", "osk.exe", 0, 0, SW_SHOW);
            if (bRet)
            {
                Wow64RevertWow64FsRedirection(OldValue);
            }
            return;
        }
        // vista win7
        sprintf(tabtip, "%c:\\Program Files\\Common Files\\Microsoft Shared\\ink\\TabTip.exe ", winroot);
        sprintf(tabtipworksp, "%c:\\Program Files\\Common Files\\Microsoft Shared\\ink", winroot);
        ret = QProcess::startDetached(tabtip, QStringList(), tabtipworksp);
        if (!ret)
        {
            sprintf(tabtip, "%c:\\Program Files (x86)\\Common Files\\Microsoft Shared\\ink\\TabTip32.exe ", winroot);
            sprintf(tabtipworksp, "%c:\\Program Files (x86)\\Common Files\\Microsoft Shared\\ink", winroot);
            ret = QProcess::startDetached(tabtip, QStringList(), tabtipworksp);
            if (!ret)
            {
                HWND hTabTip = ::FindWindowA("IPTip_Main_Window", 0);
                if (hTabTip)
                {
                    ShowWindow(hTabTip, SW_NORMAL);
                    DWORD WM_DESKBAND_CLICKED = ::RegisterWindowMessage(L"TabletInputPanelDeskBandClicked");
                    ::PostMessage(hTabTip, WM_DESKBAND_CLICKED, 0, 0);
                }
                else
                {
                    sprintf(tabtip, "%c:\\Windows\\System32\\osk.exe ", winroot);
                    sprintf(tabtipworksp, "%c:\\Windows\\System32", winroot);
                    ret = QProcess::startDetached(tabtip, QStringList(), tabtipworksp);
                }
            }
        }
    }
#endif

}
static void setNativeDarkTitleBar(WId w,bool on = true)
{
#ifdef Q_OS_WIN
    BOOL value = TRUE;
    if(on == false)
        value = FALSE;
    ::DwmSetWindowAttribute(HWND(w),20,&value,sizeof(value));
#endif
}
static bool isAdmin()
{
#ifdef Q_OS_WIN
    return bool(IsUserAnAdmin());
#else
    return false;
#endif
}
static bool runAsAdmin(QString program = QApplication::applicationFilePath())
{
#ifdef Q_OS_WIN
    HINSTANCE hInstance = ShellExecute(NULL, L"runas", program.replace("/","\\").toStdWString().c_str(), NULL, NULL, SW_SHOWNORMAL);
    if(hInstance > (HINSTANCE)32)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static bool setUACAcceptNativeDrops(QObject* object)
{
/*
 * from https://github.com/junbaibai0719/qt_uac_drag_demo/tree/main and https://www.zhihu.com/question/607474668
 * this fuction can be used to enable drag events for UAC applications, then you can process them in native event(563).
 */
#ifdef Q_OS_WIN
    QWidget* w = static_cast<QWidget*>(object);
    if(w)
    {
        bool hide = w->isHidden();
        w->show();
        void* user32 = LoadLibraryA("user32");
        FARPROC func = GetProcAddress((HMODULE)user32, "ChangeWindowMessageFilter");
        (*func)();
        user32 = LoadLibraryA("user32");
        func = GetProcAddress((HMODULE)user32, "ChangeWindowMessageFilter");
        (*func)();
        ChangeWindowMessageFilter(WM_DROPFILES, 1);
        ChangeWindowMessageFilterEx((HWND)w->effectiveWinId(), WM_DROPFILES, MSGFLT_ALLOW, NULL);
        ChangeWindowMessageFilterEx((HWND)w->effectiveWinId(), WM_COPYDATA, MSGFLT_ALLOW, NULL);
        ChangeWindowMessageFilterEx((HWND)w->effectiveWinId(), 0x0049, MSGFLT_ALLOW, NULL);
        DragAcceptFiles((HWND)w->effectiveWinId(), true);
        RevokeDragDrop((HWND)w->winId());
        if(hide)
        {
            w->hide();
        }
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static bool setUACAcceptNativeDrops(WId winId)
{
#ifdef Q_OS_WIN
    return setUACAcceptNativeDrops(QWidget::find(winId));
#else
    return false;
#endif
}
#ifndef Q_OS_WIN
typedef int MSG;
#endif
static QStringList getStringListFromNativeDropEvent(MSG* msg)
{
/* from https://www.zhihu.com/question/607474668
 * this fuction can be used to process drop in native event
 */
#ifdef Q_OS_WIN
    if(msg->message == 563)
    {
        QStringList list;
        UINT file_num = DragQueryFile((HDROP) msg->wParam, 0xFFFFFFFF, NULL, 0);
        for(int i=0;i<file_num;i++)
        {
            UINT file_name_size = DragQueryFile((HDROP) msg->wParam, i, NULL, 0) + 1;
            LPWSTR fn = (LPWSTR)malloc(sizeof(WCHAR)*file_name_size);
            DragQueryFile((HDROP) msg->wParam, i, fn, file_name_size);
            QString filename = QString::fromStdWString(fn);
            free(fn);
            list << filename.replace("\\","/");
        }
        return list;
    }
    else
    {
        return QStringList();
    }
#else
    return QStringList();
#endif
}
static QList<QUrl> getUrlListFromNativeDropEvent(MSG* msg)
{
/* from https://www.zhihu.com/question/607474668
 * this fuction can be used to process drop in native event
 */
#ifdef Q_OS_WIN
    if(msg->message == 563)
    {
        QList<QUrl> list;
        UINT file_num = DragQueryFile((HDROP) msg->wParam, 0xFFFFFFFF, NULL, 0);
        for(int i=0;i<file_num;i++)
        {
            UINT file_name_size = DragQueryFile((HDROP) msg->wParam, i, NULL, 0) + 1;
            LPWSTR fn = (LPWSTR)malloc(sizeof(WCHAR)*file_name_size);
            DragQueryFile((HDROP) msg->wParam, i, fn, file_name_size);
            QString filename = QString::fromStdWString(fn);
            free(fn);
            list << QUrl::fromLocalFile(filename.replace("\\","/"));
        }
        return list;
    }
    else
    {
        return QList<QUrl>();
    }
#else
    return QList<QUrl>();
#endif
}
static bool processNativeDropEvent(MSG* msg,QObject* recieveObject = nullptr)
{
#ifdef Q_OS_WIN
    if(msg->message == 563)
    {
        QMimeData* data = new QMimeData;
        QObjectList list;
        QWidget* w;
        QPoint pos = QPoint(0,0);
        data->setUrls(getUrlListFromNativeDropEvent(msg));

        if(recieveObject)
        {
            list << recieveObject;
        }
        else
        {
            list << QWidget::find(WId(msg->hwnd));
            POINT nativePoint = msg->pt;
            MapWindowPoints(NULL,msg->hwnd,&nativePoint,1);
            w = static_cast<QWidget*>(list.at(0));
            if(w && w->rect().contains(QPoint(nativePoint.x,nativePoint.y)))
            {
                pos = QPoint(nativePoint.x,nativePoint.y);
                pos = w->mapToGlobal(pos);
                while(w->childAt(w->mapFromGlobal(pos)) && w->childAt(w->mapFromGlobal(pos)) != w && w->childAt(w->mapFromGlobal(pos))->acceptDrops())
                {
                    w = w->childAt(w->mapFromGlobal(pos));
                    list << QObjectList() << w;
                }
            }
        }

        for(int i = 0;i < list.size();i++)
        {
            QObject* object = list.at(i);
            QPoint p = pos;
            if(static_cast<QWidget*>(object))
            {
                p = static_cast<QWidget*>(object)->mapFromGlobal(pos);
            }
            QDragEnterEvent event1(p,Qt::DropAction::CopyAction,data,Qt::LeftButton,Qt::NoModifier);
            QDropEvent event2(p,Qt::DropAction::CopyAction,data,Qt::LeftButton,Qt::NoModifier,QEvent::Drop);
            QApplication::sendEvent(object,&event1);
            QApplication::sendEvent(object,&event2);
        }
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static QStringList getDrivers()
{
    QStringList list;
#ifdef Q_OS_WIN
    QString disk = "A";
    while(disk != "")
    {
        if(QFileInfo(disk+":/").isDir())
            list << QString(disk+":/");
        disk = getNextWord(disk);
    }
#endif
    return list;
}
static bool hideFile(QString path)
{
#ifdef Q_OS_WIN
    return bool(SetFileAttributes(path.toStdWString().c_str(), FILE_ATTRIBUTE_HIDDEN));
#else
    return false;
#endif
}
static bool isHiddenFile(QString path)
{
#ifdef Q_OS_WIN
    DWORD fileAttributes = GetFileAttributesW(path.toStdWString().c_str());
    if (fileAttributes == INVALID_FILE_ATTRIBUTES)
        return false;
    return (fileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
#else
    return false;
#endif
}
static bool setNativeWallpaper(QString filePath)
{
#ifdef Q_OS_WIN
    BOOL ret = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 1, (void*)filePath.utf16(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    return bool(ret);
#else
    return false;
#endif
}
static bool setNativeWallpaper(QImage image)
{
#ifdef Q_OS_WIN
    QString private_wallpaper_dirname = "Wallpaper";
    QString filename = "paper.png";
    QString path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/"+QApplication::applicationName()+"/"+private_wallpaper_dirname+"/";
    QDir().mkpath(path);
    path += filename;
    if(image.save(path))
    {
        return setNativeWallpaper(path);
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static QString getNativeWallpaperPath()
{
#ifdef Q_OS_WIN
    HKEY hKey;
    LSTATUS status = RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_READ, &hKey);
    if(status != ERROR_SUCCESS)
    {
        return QString();
    }
    wchar_t wallpaperPath[MAX_PATH];
    DWORD bufferSize = sizeof(wallpaperPath);
    status = RegQueryValueExW(hKey, L"Wallpaper", NULL, NULL, reinterpret_cast<LPBYTE>(wallpaperPath), &bufferSize);
    RegCloseKey(hKey);
    if (status != ERROR_SUCCESS)
    {
        return QString();
    }
    QString wallpaperFilePath = QString::fromWCharArray(wallpaperPath);
    wallpaperFilePath.replace("\\","/");
    return wallpaperFilePath;
#else
    return QString();
#endif
}
static QImage getNativeWallpaper()
{
    QImage image;
    image.loadFromData(readfile(getNativeWallpaperPath()));
    return image;
}
static void LaunchUri(QString uri)
{
#ifdef WINRT_BASE_H
    winrt::Windows::System::Launcher::LaunchUriAsync(winrt::Windows::Foundation::Uri(uri.toStdWString().c_str()));
#else
    QProcess p;
    p.startDetached("cmd.exe", QStringList()<<"/c"<<("start "+uri));
#endif
}
}

static int messagebox(QWidget* w,QMessageBox::Icon icon,QString title,QString text)
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(icon == QMessageBox::Information)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONINFORMATION);
    else if(icon == QMessageBox::Critical)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONERROR);
    else if(icon == QMessageBox::Question)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONQUESTION);
    else if(icon == QMessageBox::Warning)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONWARNING);
    else if(icon == QMessageBox::NoIcon)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1);
#else
#ifdef Q_OS_ANDROID
    if(icon == QMessageBox::NoIcon && title == "")
    {
        QMessageBox box;
        box.setText(text);
        box.exec();
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton("确定", QMessageBox::AcceptRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
    }
#else
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton("确定", QMessageBox::AcceptRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
#endif
#endif
    return ret;
}
static int messagebox(QMainWindow* w,QMessageBox::Icon icon,QString title,QString text)
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(icon == QMessageBox::Information)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONINFORMATION);
    else if(icon == QMessageBox::Critical)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONERROR);
    else if(icon == QMessageBox::Question)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONQUESTION);
    else if(icon == QMessageBox::Warning)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONWARNING);
    else if(icon == QMessageBox::NoIcon)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1);
#else
#ifdef Q_OS_ANDROID
    if(icon == QMessageBox::NoIcon && title == "")
    {
        QMessageBox box;
        box.setText(text);
        box.exec();
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton("确定", QMessageBox::AcceptRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
    }
#else
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton("确定", QMessageBox::AcceptRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
#endif
#endif
    return ret;
}
static int messagebox(QDialog* w,QMessageBox::Icon icon,QString title,QString text)
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(icon == QMessageBox::Information)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONINFORMATION);
    else if(icon == QMessageBox::Critical)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONERROR);
    else if(icon == QMessageBox::Question)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONQUESTION);
    else if(icon == QMessageBox::Warning)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONWARNING);
    else if(icon == QMessageBox::NoIcon)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1);
#else
#ifdef Q_OS_ANDROID
    if(icon == QMessageBox::NoIcon && title == "")
    {
        QMessageBox box;
        box.setText(text);
        box.exec();
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton("确定", QMessageBox::AcceptRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
    }
#else
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton("确定", QMessageBox::AcceptRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
#endif
#endif
    return ret;
}
static int messagebox(QMessageBox::Icon icon,QString title,QString text)
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(icon == QMessageBox::Information)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONINFORMATION);
    else if(icon == QMessageBox::Critical)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONERROR);
    else if(icon == QMessageBox::Question)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONQUESTION);
    else if(icon == QMessageBox::Warning)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONWARNING);
    else if(icon == QMessageBox::NoIcon)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1);
#else
#ifdef Q_OS_ANDROID
    if(icon == QMessageBox::NoIcon && title == "")
    {
        QMessageBox box;
        box.setText(text);
        box.exec();
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton("确定", QMessageBox::AcceptRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
    }
#else
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton("确定", QMessageBox::AcceptRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
#endif
#endif
    return ret;
}

static int OkCancelBox(QWidget* w,QMessageBox::Icon icon,QString title,QString text,QString button1text = "",QString button2text = "")
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(button1text == "" && button2text == "")
    {
        if(icon == QMessageBox::Information)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONINFORMATION);
        else if(icon == QMessageBox::Critical)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONERROR);
        else if(icon == QMessageBox::Question)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONQUESTION);
        else if(icon == QMessageBox::Warning)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONWARNING);
        else if(icon == QMessageBox::NoIcon)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1);
        if(ret == IDOK)
            ret = 1;
        else if(ret == IDCANCEL)
            ret = 2;
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton(button1text, QMessageBox::AcceptRole);
        dlg.addButton(button2text, QMessageBox::RejectRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
        else if(r == QMessageBox::RejectRole)
        {
            ret = 2;
            dlg.close();
        }
    }
#else
    if(button1text == "" && button2text == "")
    {
        button1text = "确定";
        button2text = "取消";
    }
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton(button1text, QMessageBox::AcceptRole);
    dlg.addButton(button2text, QMessageBox::RejectRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
    else if(r == QMessageBox::RejectRole)
    {
        ret = 2;
        dlg.close();
    }
#endif
    return ret;
}
static int OkCancelBox(QMainWindow* w,QMessageBox::Icon icon,QString title,QString text,QString button1text = "",QString button2text = "")
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(button1text == "" && button2text == "")
    {
        if(icon == QMessageBox::Information)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONINFORMATION);
        else if(icon == QMessageBox::Critical)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONERROR);
        else if(icon == QMessageBox::Question)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONQUESTION);
        else if(icon == QMessageBox::Warning)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONWARNING);
        else if(icon == QMessageBox::NoIcon)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1);
        if(ret == IDOK)
            ret = 1;
        else if(ret == IDCANCEL)
            ret = 2;
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton(button1text, QMessageBox::AcceptRole);
        dlg.addButton(button2text, QMessageBox::RejectRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
        else if(r == QMessageBox::RejectRole)
        {
            ret = 2;
            dlg.close();
        }
    }
#else
    if(button1text == "" && button2text == "")
    {
        button1text = "确定";
        button2text = "取消";
    }
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton(button1text, QMessageBox::AcceptRole);
    dlg.addButton(button2text, QMessageBox::RejectRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
    else if(r == QMessageBox::RejectRole)
    {
        ret = 2;
        dlg.close();
    }
#endif
    return ret;
}
static int OkCancelBox(QDialog* w,QMessageBox::Icon icon,QString title,QString text,QString button1text = "",QString button2text = "")
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(button1text == "" && button2text == "")
    {
        if(icon == QMessageBox::Information)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONINFORMATION);
        else if(icon == QMessageBox::Critical)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONERROR);
        else if(icon == QMessageBox::Question)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONQUESTION);
        else if(icon == QMessageBox::Warning)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONWARNING);
        else if(icon == QMessageBox::NoIcon)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1);
        if(ret == IDOK)
            ret = 1;
        else if(ret == IDCANCEL)
            ret = 2;
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton(button1text, QMessageBox::AcceptRole);
        dlg.addButton(button2text, QMessageBox::RejectRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
        else if(r == QMessageBox::RejectRole)
        {
            ret = 2;
            dlg.close();
        }
    }
#else
    if(button1text == "" && button2text == "")
    {
        button1text = "确定";
        button2text = "取消";
    }
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton(button1text, QMessageBox::AcceptRole);
    dlg.addButton(button2text, QMessageBox::RejectRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
    else if(r == QMessageBox::RejectRole)
    {
        ret = 2;
        dlg.close();
    }
#endif
    return ret;
}

static int EventMessageBox(QWidget* parent,QImage img,QString title,QString text,QString button1text,QString button2text = "",QString button3text = "",QString button4text = "",QString tip1 = "",QString tip2 = "",QString tip3 = "",QString tip4 = "")
{
    QDialog* dlg = new QDialog(parent);
    QLabel* titlelabel = new QLabel(dlg);
    QLabel* imagelabel = new QLabel(dlg);
    QLabel* textlabel = new QLabel(dlg);
    QPushButton* button1 = new QPushButton(dlg);
    QPushButton* button2 = new QPushButton(dlg);
    QPushButton* button3 = new QPushButton(dlg);
    QPushButton* button4 = new QPushButton(dlg);
    QLineEdit* edit = new QLineEdit(dlg);
    edit->setText("0");
    edit->hide();

#ifdef Q_Device_Desktop
    dlg->resize(400,300);
    dlg->setWindowFlags(Qt::FramelessWindowHint);
    dlg->setStyleSheet("background-color:black;border: 0.5px solid rgb(255, 255, 255);");
#else
    dlg->resize(screensize());
#endif


    titlelabel->resize(dlg->width(),30);
    titlelabel->move(0,0);
    titlelabel->setStyleSheet("color:white;background-color:black;");
    titlelabel->setAlignment(Qt::AlignCenter);
    titlelabel->setText(title);

    imagelabel->resize(dlg->width()-20,(dlg->width()-20)*(float(img.height())/float(img.width())));
    imagelabel->move(titlelabel->x()+10,titlelabel->y()+titlelabel->height()+10);
    imagelabel->setPixmap(QPixmap::fromImage(img).scaled(imagelabel->width(),imagelabel->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    textlabel->resize(dlg->width(),60);
    textlabel->move(0,imagelabel->y()+imagelabel->height()+10);
    textlabel->setStyleSheet("color:white;background-color:black;");
    textlabel->setAlignment(Qt::AlignCenter);
    textlabel->setText(text);

    button1->resize(imagelabel->width(),30);
    button2->resize(button1->size());
    button3->resize(button1->size());
    button4->resize(button1->size());

    button1->move(imagelabel->x(),textlabel->y()+textlabel->height()+10);
    button2->move(button1->x(),button1->y()+button1->height()+10);
    button3->move(button2->x(),button2->y()+button2->height()+10);
    button4->move(button3->x(),button3->y()+button3->height()+10);

    button1->setStyleSheet("QPushButton{background-color:rgb(0,0,0);border: 0.5px solid rgb(255, 255, 255);color:rgb(255,255,255);}");
    button2->setStyleSheet(button1->styleSheet());
    button3->setStyleSheet(button1->styleSheet());
    button4->setStyleSheet(button1->styleSheet());

    button1->setText(button1text);
    button2->setText(button2text);
    button3->setText(button3text);
    button4->setText(button4text);

    button1->setToolTip(tip1);
    button2->setToolTip(tip2);
    button3->setToolTip(tip3);
    button4->setToolTip(tip4);
    dlg->setFixedHeight(button4->y()+button4->height()+10);

    QObject::connect(button1,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        edit->setText("1");
        dlg->close();
    });
    QObject::connect(button2,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        edit->setText("2");
        dlg->close();
    });
    QObject::connect(button3,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        edit->setText("3");
        dlg->close();
    });
    QObject::connect(button4,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        edit->setText("4");
        dlg->close();
    });

    if(button4text == "")
    {
        dlg->setFixedHeight(button4->y());
        button4->hide();
        button4->disconnect();
    }
    if(button3text == "")
    {
        dlg->setFixedHeight(button3->y());
        button3->hide();
        button3->disconnect();
    }
    if(button2text == "")
    {
        dlg->setFixedHeight(button2->y());
        button2->hide();
        button2->disconnect();
    }

    dlg->exec();
    return edit->text().toInt();
}
static WId processDialog(QWidget* parent = nullptr,QString title = " ")
{
    QDialog* dlg = new QDialog(parent);
    QComboBox* modebox = new QComboBox(dlg);
    QStringList mode;
    QLineEdit* commandEdit = new QLineEdit(dlg);
    QLineEdit* argumentEdit = new QLineEdit(dlg);
    QPushButton* runbutton = new QPushButton(dlg);
    QPushButton* closebutton = new QPushButton(dlg);
    QPushButton* killbutton = new QPushButton(dlg);
#ifdef Q_OS_LINUX
    QPushButton* rootbutton = new QPushButton(dlg);
#endif
    QLabel* l1 = new QLabel(dlg);
    QLabel* l2 = new QLabel(dlg);
    QLabel* l3 = new QLabel(dlg);
    QProcess* p = new QProcess(dlg);

    dlg->setWindowTitle(title);
#ifdef Q_Device_Mobile
    dlg->resize(screensize());
    //dlg->showFullScreen();
#else
    dlg->resize(430,170);
    fixSize(dlg);
#endif

    l1->resize(90,30);
    l2->resize(l1->size());
    l3->resize(l1->size());
    l1->move(10,10);
    l2->move(l1->x(),l1->y()+l1->height()+10);
    l3->move(l1->x(),l2->y()+l2->height()+10);
    l1->setText("mode:");
    l2->setText("command:");
    l3->setText("arguments:");
    l1->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    l2->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    l3->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    modebox->move(l1->x()+l1->width()+10,l1->y());
    modebox->resize(dlg->width()-modebox->x()-10,l1->height());
    mode << "QProcess::execute(QString&)" << "system(char*)" << "QProcess::start(QString&,QStringList&)" << "QProcess::startDetached(QString&,QStringList&)";
    modebox->addItems(mode);

    commandEdit->move(l2->x()+l2->width()+10,l2->y());
    commandEdit->resize(modebox->size());

    argumentEdit->move(l3->x()+l3->width()+10,l3->y());
    argumentEdit->resize(commandEdit->size());

    closebutton->resize(50,30);
    closebutton->move(dlg->width()-closebutton->width()-10,l3->y()+l3->height()+10);
    closebutton->setText("取消");
    closebutton->setStyleSheet("QPushButton{background-color:rgb(255,255,255);border: 0.5px solid #DBDBDB;border-radius:5;color:rgb(0,0,0);}QPushButton:pressed{background-color:#D9D9D9;border: 0.5px solid #DBDBDB;}QPushButton:hover{background-color:#D9D9D9;border: 0.5px solid #DBDBDB;}");

    killbutton->resize(100,30);
    killbutton->move(closebutton->x()-killbutton->width()-10,closebutton->y());
    killbutton->setText("终止进程");
    killbutton->setStyleSheet(closebutton->styleSheet());

    runbutton->resize(closebutton->size());
    runbutton->move(killbutton->x()-runbutton->width()-10,killbutton->y());
    runbutton->setText("执行");
    runbutton->setStyleSheet("QPushButton{background-color:rgb(0,103,192);border: 0.5px solid rgb(0,103,192);border-radius:5;color:rgb(255,255,255);}QPushButton:pressed{background-color:#0A63A8;border: 0.5px solid #0A63A8;}QPushButton:hover{background-color:#0A63A8;border: 0.5px solid #0A63A8;}");

#ifdef Q_OS_LINUX
    rootbutton->move(runbutton->x(),runbutton->y()+runbutton->height()+10);
    rootbutton->resize(runbutton->width()+closebutton->width()+killbutton->width()+20,runbutton->height());
    rootbutton->setText("请求Root权限");
    rootbutton->setStyleSheet(closebutton->styleSheet());
#endif

    QObject::connect(closebutton,&QPushButton::clicked,[dlg](){
        dlg->close();
    });
    QObject::connect(modebox,QOverload<const QString &>::of(&QComboBox::currentTextChanged),[=](QString text)mutable{
        if(modebox->currentText() == "QProcess::execute(QString&)" || modebox->currentText() == "system(char*)")
        {
            argumentEdit->setEnabled(false);
        }
        else
        {
            argumentEdit->setEnabled(true);
        }
    });
    argumentEdit->setEnabled(false);
    QObject::connect(runbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        if(modebox->currentText() == "QProcess::execute(QString&)" && commandEdit->text() != "")
            QProcess::execute(commandEdit->text());
        else if(modebox->currentText() == "system(char*)" && commandEdit->text() != "")
            system(QString(commandEdit->text()+" "+argumentEdit->text()).toLocal8Bit().data());
        else if(modebox->currentText() == "QProcess::start(QString&,QStringList&)" && commandEdit->text() != "")
            p->start(commandEdit->text(),QStringList() << argumentEdit->text());
        else if(modebox->currentText() == "QProcess::startDetached(QString&,QStringList&)" && commandEdit->text() != "")
            p->startDetached(commandEdit->text(),QStringList() << argumentEdit->text());
    });
    QObject::connect(killbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        p->kill();
    });
#ifdef Q_OS_LINUX
    QObject::connect(rootbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{QProcess::execute("su");
    });
#endif
    dlg->exec();
    return dlg->winId();
}
static WId playerDialog(QWidget* parent,QString path,QSize size = QSize(600,400))
{
#ifdef Multimedia_And_Widgets_Enabled
    QDialog* dlg = new QDialog(parent);
    QMediaPlayer* player = new QMediaPlayer(dlg);
    QVideoWidget* videowidget = new QVideoWidget(dlg);
    QAudioOutput* audiooutput = new QAudioOutput;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
#endif

#ifdef Q_Device_Desktop
    dlg->resize(size);
    fixSize(dlg);
#else
    if(size.width() == 600 && size.height() == 400)
        dlg->resize(screensize());
    else
        dlg->resize(size);
#endif
    videowidget->resize(dlg->size());
    player->setVideoOutput(videowidget);

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    if(hasFilePermission(path) == true)
    {
        player->setSource(QUrl::fromLocalFile(path));
        player->setAudioOutput(audiooutput);
    }
#else
    if(hasFilePermission(path) == true)
    {
        player->setMedia(QUrl::fromLocalFile(path));
    }
#endif

    //qDebug() << path << hasFilePermission(path);

    player->play();
    dlg->setWindowTitle(QFileInfo(path).fileName());
    dlg->exec();
    player->stop();
    return dlg->winId();
#else
    return parent->winId();
#endif
}
static WId fileDialog(QWidget* parent,QString title = " ")
{
    QDialog* w = new QDialog(parent);
    QWidget* dlg = new QWidget(w);
    dlg->setWindowTitle(title);
#ifdef Q_Device_Mobile
    w->resize(screensize());
    dlg->resize(screensize());
#else
    dlg->resize(500,600);
#endif

    QLabel* l1 = new QLabel(dlg);
    QLabel* l2 = new QLabel(dlg);
    QLabel* l3 = new QLabel(dlg);
    QLabel* l4 = new QLabel(dlg);
    QLabel* l5 = new QLabel(dlg);
    QLabel* l6 = new QLabel(dlg);
    QLabel* l7 = new QLabel(dlg);
    QLabel* l8 = new QLabel(dlg);
    QLabel* l9 = new QLabel(dlg);
    QLabel* l10 = new QLabel(dlg);
    QLabel* l11 = new QLabel(dlg);

    l1->setText("QFile file(");
    l2->setText(");");
    l3->setText("QIODevice::OpenModeFlag flag = ");
    l4->setText(";");
    l5->setText("bool check1 = file.exists();");
    l6->setText("bool check2 = file.open(flag);");
    l7->setText("QString content = file.readAll();");
    l8->setText("file.write(");
    l9->setText(");");
    l10->setText("file.close();");
    l11->setText("qDebug() << ");

    l1->setAlignment(Qt::AlignCenter);
    l2->setAlignment(Qt::AlignCenter);
    l3->setAlignment(Qt::AlignCenter);
    l4->setAlignment(Qt::AlignCenter);
    l5->setAlignment(Qt::AlignCenter);
    l6->setAlignment(Qt::AlignCenter);
    l7->setAlignment(Qt::AlignCenter);
    l8->setAlignment(Qt::AlignCenter);
    l9->setAlignment(Qt::AlignCenter);
    l10->setAlignment(Qt::AlignCenter);
    l11->setAlignment(Qt::AlignCenter);

    QComboBox* flagbox = new QComboBox(dlg);
    QComboBox* debugbox = new QComboBox(dlg);
    QStringList list1;
    QStringList list2;
    list1 << "QIODevice::ReadWrite" << "QIODevice::ReadOnly" << "QIODevice::WriteOnly";
    list2 << "check1" << "check2" << "content";
    flagbox->addItems(list1);
    debugbox->addItems(list2);

    QLineEdit* fileedit = new QLineEdit(dlg);
    QTextEdit* writeedit = new QTextEdit(dlg);
    QPushButton* browsebutton = new QPushButton(dlg);
    QPushButton* commitbutton = new QPushButton(dlg);
    QPushButton* cancelbutton = new QPushButton(dlg);
    QPushButton* clearbutton = new QPushButton(dlg);
    browsebutton->setIcon(QIcon(":/icon/folder.ico"));
    browsebutton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    commitbutton->setText("确定");
    commitbutton->setStyleSheet("QPushButton{background-color:rgb(0,103,192);border: 0.5px solid rgb(0,103,192);border-radius:5;color:rgb(255,255,255);}QPushButton:pressed{background-color:#0A63A8;border: 0.5px solid #0A63A8;}QPushButton:hover{background-color:#0A63A8;border: 0.5px solid #0A63A8;}");
    cancelbutton->setText("取消");
    cancelbutton->setStyleSheet("QPushButton{background-color:rgb(255,255,255);border: 0.5px solid #DBDBDB;border-radius:5;color:rgb(0,0,0);}QPushButton:pressed{background-color:#D9D9D9;border: 0.5px solid #DBDBDB;}QPushButton:hover{background-color:#D9D9D9;border: 0.5px solid #DBDBDB;}");
    clearbutton->setText("clear");
    fileedit->setClearButtonEnabled(true);

    l1->move(10,10);
    l1->resize(80,30);
    l2->resize(l1->height(),l1->height());
    l2->move(dlg->width()-10-l2->width(),l1->y());
    browsebutton->resize(l1->height(),l1->height());
    browsebutton->move(l2->x()-10-browsebutton->width(),l1->y());
    fileedit->resize(browsebutton->x()-l1->x()-l1->width()-20,l1->height());
    fileedit->move(l1->x()+l1->width()+10,l1->y());

    l3->move(l1->x(),l1->y()+l1->height()+10);
    l3->resize(200,l1->height());
    l4->resize(15,25);
    l4->move(dlg->width()-10-l4->width(),l3->y());
    flagbox->move(l3->x()+l3->width()+10,l3->y());
    flagbox->resize(l4->x()-20-l3->x()-l3->width(),l1->height());

    l5->move(l1->x(),l3->y()+l3->height()+10);
    l5->resize(dlg->width()-20,l1->height());
    l6->move(l1->x(),l5->y()+l5->height()+10);
    l6->resize(l5->size());
    l7->move(l1->x(),l6->y()+l6->height()+10);
    l7->resize(l5->size());

    l8->resize(80,l1->height());
    l8->move(l7->x(),l7->y()+l7->height()+10);
    l9->resize(15,l1->height());
    l9->move(dlg->width()-10-l9->width(),l8->y()+l8->height()+10);
    writeedit->move(l8->x()+l8->width()+10,l8->y());
    writeedit->resize(l9->x()-l8->x()-l8->width()-20,l9->y()+l9->height()-l8->y());

    l10->move(l8->x(),l9->y()+l9->height()+10);
    l10->resize(l5->size());
    l11->move(l10->x(),l10->y()+l10->height()+10);
    l11->resize(100,l1->height());

    commitbutton->resize(50,30);
    cancelbutton->resize(commitbutton->size());
    cancelbutton->move(dlg->width()-10-cancelbutton->width(),l11->y());
    commitbutton->move(cancelbutton->x()-10-commitbutton->width(),cancelbutton->y());
    debugbox->move(l11->x()+l11->width()+10,l11->y());
    debugbox->resize(commitbutton->x()-l11->x()-l11->width()-20,l1->height());

    clearbutton->resize(l8->size());
    clearbutton->move(l8->x(),l8->y()+l8->height()+10);
    dlg->resize(dlg->width(),commitbutton->y()+commitbutton->height()+10);
#ifdef Q_Device_Mobile
    //QMessageBox::information(dlg,"",QString("screenheight:"+QString::number(screenheight())+"\ndlg.height():"+QString::number(dlg->height())));
    QScrollArea* s = new QScrollArea(w);
    s->setWidget(dlg);
    s->setGeometry(0,0,screenwidth(),screenheight());
    s->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller::grabGesture(s->viewport(),QScroller::LeftMouseButtonGesture);
#endif

    QObject::connect(browsebutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        QString path;
//#ifndef Q_OS_ANDROID
        dlg->hide();
        path = QFileDialog::getOpenFileName();
        QMessageBox::information(dlg,""," ");
        dlg->show();
//#else
//        MyFileDialog* dialog = new MyFileDialog(dlg);
//        path = dialog->getOpenFileName();
//#endif
        if(path != "")
            fileedit->setText(path);
    });
    QObject::connect(cancelbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        dlg->close();
        w->close();
    });
    QObject::connect(debugbox,QOverload<const QString &>::of(&QComboBox::currentTextChanged),[=](QString text)mutable{

    });
    QObject::connect(clearbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        writeedit->setText("");
    });
    QObject::connect(commitbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        if(fileedit->text() != "")
        {
            if(debugbox->currentText() == "check1")
            {
                bool check1 = QFile(fileedit->text()).exists();
                if(check1 == true)
                    messagebox(dlg,QMessageBox::NoIcon,"","check1 == true");
                else
                    messagebox(dlg,QMessageBox::NoIcon,"","check1 == false");
            }
            else if(debugbox->currentText() == "check2")
            {
                QIODevice::OpenModeFlag flag;
                if(flagbox->currentText() == "QIODevice::ReadWrite")
                    flag = QIODevice::ReadWrite;
                else if(flagbox->currentText() == "QIODevice::ReadOnly")
                    flag = QIODevice::ReadOnly;
                else if(flagbox->currentText() == "QIODevice::WriteOnly")
                    flag = QIODevice::WriteOnly;
                bool check2 = hasFilePermission(fileedit->text(),flag);
                if(check2 == true)
                    messagebox(dlg,QMessageBox::NoIcon,"","check2 == true");
                else
                    messagebox(dlg,QMessageBox::NoIcon,"","check2 == false");
            }
            else if(debugbox->currentText() == "content")
            {
                QString content = "";
                QFile file(fileedit->text());
                if(file.open(QIODevice::ReadOnly))
                {
                    content = file.readAll();
                    file.close();
                    file.deleteLater();
                    messagebox(dlg,QMessageBox::NoIcon,"",QString("content:\n"+content));
                }
                else
                {
                    messagebox(dlg,QMessageBox::NoIcon,"","fail to read file");
                }
            }
            if(writeedit->toPlainText() != "")
            {
                QFile file(fileedit->text());
                if(file.open(QIODevice::WriteOnly))
                {
                    file.write(writeedit->toPlainText().toLocal8Bit());
                    file.close();
                    file.deleteLater();
                }
                else
                {
                    messagebox(dlg,QMessageBox::NoIcon,"","fail to write file");
                }
            }
        }
    });
    w->exec();
    return w->winId();
}
static void showPixmapDialog(QPixmap pixmap,QObject* parent = nullptr,QString title = "")
{
    QDialog* dlg = new QDialog();

    QLabel* label = new QLabel(dlg);
    label->move(0,0);
    label->setPixmap(pixmap);
    if(!title.isEmpty())
    {
        dlg->setWindowTitle(title);
    }
    if(pixmap.isNull())
    {
        label->resize(100,100);
    }
    else
    {
        label->resize(pixmap.size());
    }
    dlg->resize(label->size());
    label->show();
    dlg->exec();
}
static QString lineEditDialog(QWidget* parent,QString text,QString title,QString placeholdertext = "",bool clearbutton = true)
{
    QDialog* dlg = new QDialog(parent);
    QLineEdit* edit = new QLineEdit(dlg);
    QPushButton* commitbutton = new QPushButton(dlg);
    QPushButton* cancelbutton = new QPushButton(dlg);

#ifdef Q_Device_Desktop
    dlg->resize(350,90);
    dlg->setWindowTitle(title);
#else
    dlg->resize(screensize());
#endif
    //setCloseButton(dlg,false,0);

    edit->resize(dlg->width()-20,30);
    edit->move(10,10);
    edit->setText(text);
    if(placeholdertext != "")
        edit->setPlaceholderText(placeholdertext);
    if(clearbutton == true)
        edit->setClearButtonEnabled(true);

    cancelbutton->resize(edit->height()/3*5,edit->height());
    commitbutton->resize(cancelbutton->size());
    cancelbutton->move(edit->x()+edit->width()-cancelbutton->width(),edit->y()+edit->height()+10);
    commitbutton->move(cancelbutton->x()-10-commitbutton->width(),cancelbutton->y());
    cancelbutton->setText("取消");
    commitbutton->setText("确定");

//    qDebug() << edit->width() << edit->height();
//    messagebox(parent,QMessageBox::NoIcon,"",QString::number(edit->width())+","+QString::number(edit->height()));

    QObject::connect(commitbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check){
        if(edit->text() != "")
            dlg->close();
    });
    QObject::connect(cancelbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check){
        edit->setText(text);
        dlg->close();
    });
    QObject::connect(edit,QOverload<>::of(&QLineEdit::returnPressed),[=](){
        commitbutton->click();
    });

    dlg->exec();
    return edit->text();
}
static WId showTextDialog(QString text,QWidget* parent = nullptr,QString title = " ",bool useTextBrowser = true)
{
    QDialog* dlg = new QDialog(parent);

    dlg->setWindowTitle(title);
#ifdef Q_Device_Mobile
    dlg->resize(screensize());
#else
    dlg->resize(400,300);
    fixSize(dlg);
#endif

    if(!useTextBrowser)
    {
        QTextEdit* edit = new QTextEdit(dlg);
        edit->move(0,0);
        edit->resize(dlg->size());
        edit->setText(text);
    #ifdef Q_Device_Desktop
        QScroller::grabGesture(edit->viewport(),QScroller::TouchGesture);
    #else
        QScroller::grabGesture(edit->viewport(),QScroller::LeftMouseButtonGesture);
    #endif
    }
    else
    {
        QTextBrowser* edit = new QTextBrowser(dlg);
        edit->move(0,0);
        edit->resize(dlg->size());
        edit->setText(text);
    #ifdef Q_Device_Desktop
        QScroller::grabGesture(edit->viewport(),QScroller::TouchGesture);
    #else
        QScroller::grabGesture(edit->viewport(),QScroller::LeftMouseButtonGesture);
    #endif
    }
    \
    dlg->exec();
    return dlg->winId();
}

static QString GetDebugInfo(QWidget* w = nullptr)
{
    QString ret;

    ret = ret + "ApplicationFilePath" + ": " + QCoreApplication::applicationFilePath() + "\n";
    ret = ret + "ApplicationDirPath" + ": " + QCoreApplication::applicationDirPath() + "\n";
    ret = ret + "ApplicationCurrentPath" + ": " + QDir::currentPath() + "\n";
    ret = ret + "ApplicationName" + ": " + QCoreApplication::applicationName() + "\n";
    if(!QCoreApplication::applicationVersion().isEmpty())
        ret = ret + "ApplicationVersion" + ": " + QCoreApplication::applicationVersion() + "\n";
    else
        ret = ret + "ApplicationVersion" + ": " + "nullptr" + "\n";
    ret = ret + "ApplicationPid" + ": " + QString::number(QCoreApplication::applicationPid()) + "\n";
    ret = ret + "ApplicationArguments" + ": " + QCoreApplication::arguments().join(";") + "\n";
    if(w != nullptr)
    {
        ret = ret + "ApplicationWinId" + ": " + QString::number(w->winId()) + "\n";
#ifdef Q_OS_WIN
        TCHAR szBuffer[256];
        wsprintf(szBuffer, L"0x%08p", HWND(w->winId()));
        QString strHWND = QString::fromWCharArray(szBuffer);
        ret = ret + "ApplicationHWND" + ": " + strHWND + "\n";
#endif
    }

    ret = ret + "\n";
    ret = ret + "HomeDirPath" + ": " + QDir::homePath() + "\n";
    ret = ret + "HomeDirName" + ": " + QDir::home().dirName() + "\n";
    ret = ret + "TempDirName" + ": " + QDir::tempPath() + "\n";
    ret = ret + "DesktopLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "\n";
    ret = ret + "DownloadLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "\n";
    ret = ret + "DocumentsLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\n";
    ret = ret + "PicturesLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "\n";
    ret = ret + "MoviesLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::MoviesLocation) + "\n";
    ret = ret + "MusicLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::MusicLocation) + "\n";
    ret = ret + "GenericDataLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "\n";
    ret = ret + "GenericCacheLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) + "\n";
    ret = ret + "GenericConfigLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "\n";
    ret = ret + "ScreenSize" + ": " + QString(QString::number(screensize().width())+"*"+QString::number(screensize().height())) + "\n";
    ret = ret + "RealScreenSize" + ": " + QString(QString::number(realScreenSize().width())+"*"+QString::number(realScreenSize().height())) + "\n";

    ret = ret + "\n";
    ret = ret + "SystemProductName" + ": " + QSysInfo::prettyProductName() + "\n";
    ret = ret + "SystemProductType" + ": " + QSysInfo::productType() + "\n";
    ret = ret + "SystemProductVersion" + ": " + QSysInfo::productVersion() + "\n";
    ret = ret + "prettyProductName" + ": " + QSysInfo::prettyProductName() + "\n";
    ret = ret + "buildAbi" + ": " + QSysInfo::buildAbi() + "\n";
    ret = ret + "buildCpuArchitecture" + ": " + QSysInfo::buildCpuArchitecture() + "\n";
    ret = ret + "currentCpuArchitecture" + ": " + QSysInfo::currentCpuArchitecture() + "\n";
    ret = ret + "kernelType" + ": " + QSysInfo::kernelType() + "\n";
    ret = ret + "kernelVersion" + ": " + QSysInfo::kernelVersion() + "\n";
    ret = ret + "machineHostName" + ": " + QSysInfo::machineHostName() + "\n";
    ret = ret + "machineUniqueId" + ": " + (QString)QSysInfo::machineUniqueId() + "\n";
    ret = ret + "bootUniqueId" + ": " + (QString)QSysInfo::bootUniqueId() + "\n";
    ret = ret + "QtVersion" + ": " + QString(QT_VERSION_STR) + "\n";
    ret = ret + "QtMajorVersion" + ": " + QString::number(QT_VERSION_MAJOR) + "\n";
#ifdef Core_Private_Enabled
#ifdef Network_Enabled
    if(QSslSocket::supportsSsl())
        ret = ret + "SupportOpenssl" + ": " + "true" + "\n";
    else
        ret = ret + "SupportOpenssl" + ": " + "false" + "\n";
#endif
#endif

//Android Debug
#ifdef Q_OS_ANDROID
#ifdef Core_Private_Enabled
    ret = ret + "\n";
    ret = ret + "Android:\r\n";
    ret = ret + "PackageName" + ": " + Android::getPackageName() + "\n";
    ret = ret + "ActivityName" + ": " + Android::getActivityName() + "\n";
    ret = ret + "SystemVersion" + ": " + QString::number(Android::getSystemVersion()) + "\n";
    ret = ret + "SdkVersion" + ": " + QString::number(QNativeInterface::QAndroidApplication::sdkVersion()) + "\n";
    ret = ret + "TargetSdkVersion" + ": " + QString::number(Android::getTargetSdkVersion()) + "\n";
    ret = ret + "isActivityContext" + ": " + toString(QNativeInterface::QAndroidApplication::isActivityContext()) + "\n";
    ret = ret + "isQtDefaultActivity" + ": " + toString(Android::isQtDefaultActivity()) + "\n";
    ret = ret + "isAndroidXEnabled" + ": " + toString(Android::isAndroidXEnabled()) + "\n";
    ret = ret + "isAndroidSupportV4Enabled" + ": " + toString(Android::isAndroidSupportV4Enabled()) + "\n";
    ret = ret + "hasStroagePermission" + ": " + toString(Android::hasStroagePermission()) + "\n";
    ret = ret + "isApplicationUsingDefaultIcon" + ": " + toString(Android::isApplicationUsingDefaultIcon()) + "\n";
    ret = ret + "ApplicationIconId" + ": " + QString::number(Android::getApplicationIconId()) + "\n";
    ret = ret + "ApplicationDefaultIconId" + ": " + QString::number(Android::getApplicationDefaultIconId()) + "\n";
    ret = ret + "Brand" + ": " + Android::getBrand() + "\n";
    ret = ret + "Model" + ": " + Android::getModel() + "\n";
    ret = ret + "LauncherPackageName" + ": " + Android::getLauncherPackageName() + "\n";
    ret = ret + "InstalledPackageList" + ": \n" + Android::getInstalledPackageList().join(";\n") + "\n";
#endif
#endif

    return ret;
}
static WId showDebugInfo(QWidget* parent = nullptr,QString title = " ",bool useTextBrowser = true)
{
    QDialog* dlg = new QDialog(parent);

    dlg->setWindowTitle(title);
#ifdef Q_Device_Mobile
    dlg->resize(screensize());
#else
    dlg->resize(400,300);
    fixSize(dlg);
#endif

    if(!useTextBrowser)
    {
        QTextEdit* edit = new QTextEdit(dlg);
        edit->move(0,0);
        edit->resize(dlg->size());
        edit->setText(GetDebugInfo(parent));
    #ifdef Q_Device_Desktop
        QScroller::grabGesture(edit->viewport(),QScroller::TouchGesture);
    #else
        QScroller::grabGesture(edit->viewport(),QScroller::LeftMouseButtonGesture);
    #endif
    }
    else
    {
        QTextBrowser* edit = new QTextBrowser(dlg);
        edit->move(0,0);
        edit->resize(dlg->size());
        edit->setText(GetDebugInfo(parent));
    #ifdef Q_Device_Desktop
        QScroller::grabGesture(edit->viewport(),QScroller::TouchGesture);
    #else
        QScroller::grabGesture(edit->viewport(),QScroller::LeftMouseButtonGesture);
    #endif
    }
    \
    dlg->exec();
    return dlg->winId();
}

static QPixmap floodFill(QPixmap &pixmap, QPoint seedPoint, QColor newColor,int tolerance = 0)
{
    if(tolerance >= 0 && tolerance < 255)
    {
        QImage image = pixmap.toImage();
        QColor oldColor = image.pixelColor(seedPoint);
        if (oldColor == newColor && tolerance == 0)
        {
            return pixmap;
        }

        QStack<QPoint> stack;
        stack.push(seedPoint);

        while (!stack.isEmpty())
        {
            QPoint current = stack.pop();
            //if (image.valid(current) && image.pixelColor(current) == oldColor)
            if (image.valid(current) && Abs(image.pixelColor(current).red()-oldColor.red()) <= tolerance && Abs(image.pixelColor(current).green()-oldColor.green()) <= tolerance && Abs(image.pixelColor(current).blue()-oldColor.blue()) <= tolerance)
            {
                image.setPixelColor(current, newColor);
                stack.push(QPoint(current.x() + 1, current.y()));
                stack.push(QPoint(current.x() - 1, current.y()));
                stack.push(QPoint(current.x(), current.y() + 1));
                stack.push(QPoint(current.x(), current.y() - 1));
            }
        }
        pixmap = QPixmap::fromImage(image);
        image = QImage();
    }
    else if(tolerance == 255)
    {
        QPixmap p = pixmap;
        QPainter painter(&p);
        painter.fillRect(p.rect(),newColor);
        pixmap = p;
    }
    return pixmap;
}
static QImage floodFill(QImage &image, QPoint seedPoint, QColor newColor,int tolerance = 0)
{
    if(tolerance >= 0 && tolerance < 255)
    {
        QColor oldColor = image.pixelColor(seedPoint);
        if (oldColor == newColor && tolerance == 0)
        {
            return image;
        }

        QStack<QPoint> stack;
        stack.push(seedPoint);

        while (!stack.isEmpty())
        {
            QPoint current = stack.pop();
            //if (image.valid(current) && image.pixelColor(current) == oldColor)
            if (image.valid(current) && Abs(image.pixelColor(current).red()-oldColor.red()) <= tolerance && Abs(image.pixelColor(current).green()-oldColor.green()) <= tolerance && Abs(image.pixelColor(current).blue()-oldColor.blue()) <= tolerance)
            {
                image.setPixelColor(current, newColor);
                stack.push(QPoint(current.x() + 1, current.y()));
                stack.push(QPoint(current.x() - 1, current.y()));
                stack.push(QPoint(current.x(), current.y() + 1));
                stack.push(QPoint(current.x(), current.y() - 1));
            }
        }
    }
    else if(tolerance == 255)
    {
        QPixmap pixmap = QPixmap::fromImage(image);
        QPainter painter(&pixmap);
        painter.fillRect(pixmap.rect(),newColor);
        image = pixmap.toImage();
    }
    return image;
}
static QPixmap setOpacity(QPixmap &pixmap,int opacity)
{
    if(opacity < 255 && opacity >= 0 && !pixmap.isNull())
    {
        int x;
        int y;
        QImage image = pixmap.toImage();
        image = image.convertToFormat(QImage::Format_ARGB32);
        QColor color;
        for(x = 0;x <= image.width();x++)
        {
            for(y = 0;y <= image.height();y++)
            {
                if(image.valid(QPoint(x,y)) && image.pixelColor(x,y) != QColor(0,0,0,0))
                {
                    color = image.pixelColor(x,y);
                    image.setPixelColor(x,y,QColor(color.red(),color.green(),color.blue(),opacity));
                }
            }
        }
        color = QColor();
        x = NULL;
        y = NULL;
        pixmap = QPixmap::fromImage(image);
        image = QImage();
    }
    return pixmap;
}
static QImage setOpacity(QImage &image,int opacity)
{
    if(opacity < 255 && opacity >= 0 && !image.isNull())
    {
        int x;
        int y;
        image = image.convertToFormat(QImage::Format_ARGB32);
        QColor color;
        for(x = 0;x <= image.width();x++)
        {
            for(y = 0;y <= image.height();y++)
            {
                if(image.valid(QPoint(x,y)) && image.pixelColor(x,y) != QColor(0,0,0,0))
                {
                    color = image.pixelColor(x,y);
                    image.setPixelColor(x,y,QColor(color.red(),color.green(),color.blue(),opacity));
                }
            }
        }
        color = QColor();
        x = NULL;
        y = NULL;
    }
    return image;
}
static QPixmap replaceColor(QPixmap &pixmap,QColor oldColor,QColor newColor)
{
    if(!pixmap.isNull())
    {
        int x;
        int y;
        QImage image = pixmap.toImage();
        image = image.convertToFormat(QImage::Format_ARGB32);
        for(x = 0;x <= image.width();x++)
        {
            for(y = 0;y <= image.height();y++)
            {
                if(image.valid(QPoint(x,y)) && image.pixelColor(QPoint(x,y)) == oldColor)
                {
                    image.setPixelColor(x,y,newColor);
                }
            }
        }
        x = NULL;
        y = NULL;
        pixmap = QPixmap::fromImage(image);
        image = QImage();
    }
    return pixmap;
}
static QImage replaceColor(QImage &image,QColor oldColor,QColor newColor)
{
    if(!image.isNull())
    {
        int x;
        int y;
        image = image.convertToFormat(QImage::Format_ARGB32);
        for(x = 0;x <= image.width();x++)
        {
            for(y = 0;y <= image.height();y++)
            {
                if(image.valid(QPoint(x,y)) && image.pixelColor(QPoint(x,y)) == oldColor)
                {
                    image.setPixelColor(x,y,newColor);
                }
            }
        }
        x = NULL;
        y = NULL;
    }
    return image;
}
static QPixmap rectPixmap(int width,int height,QColor lineColor,int pensize,QColor fillColor = QColor(0,0,0,0),int round = -1)
{
    if(width > pensize && height > pensize && pensize > 0)
    {
        QPixmap pixmap(width+pensize,height+pensize);
        pixmap.fill(QColor(0,0,0,0));
        QPainter* painter = new QPainter(&pixmap);
        QPen pen;
        QBrush brush;
        if(fillColor != QColor(0,0,0,0))
        {
            brush.setColor(fillColor);
            brush.setStyle(Qt::SolidPattern);
            painter->setBrush(brush);
        }
        pen.setColor(lineColor);
        pen.setWidth(pensize);
        painter->setPen(pen);
        if(round > 0)
            painter->drawRoundedRect(QRect(pensize/2.0,pensize/2.0,width,height),round,round);
        else
            painter->drawRect(pensize/2.0,pensize/2.0,width,height);
        pen = QPen();
        brush = QBrush();
        delete painter;
        return pixmap;
    }
    else
    {
        return QPixmap();
    }
}
static QPixmap roundPixmap(int width,int height,QColor lineColor,int pensize,QColor fillColor = QColor(0,0,0,0))
{
    if(width > pensize && height > pensize && pensize > 0)
    {
        QPixmap pixmap(width+pensize,height+pensize);
        pixmap.fill(QColor(0,0,0,0));
        QPainter* painter = new QPainter(&pixmap);
        QPen pen;
        QBrush brush;
        if(fillColor != QColor(0,0,0,0))
        {
            brush.setColor(fillColor);
            brush.setStyle(Qt::SolidPattern);
            painter->setBrush(brush);
        }
        pen.setColor(lineColor);
        pen.setWidth(pensize);
        painter->setPen(pen);
        painter->drawEllipse(pensize/2.0,pensize/2.0,width,height);
        pen = QPen();
        brush = QBrush();
        delete painter;
        return pixmap;
    }
    else
    {
        return QPixmap();
    }
}
static QPixmap textPixmap(QString str,QColor textcolor = Qt::white,QColor backgroundcolor = Qt::transparent,QSize size = QSize(),int flags = Qt::AlignLeft|Qt::AlignTop,int font_size = -1)
{
    if(size.isEmpty())
        size = nativeLabelSize(str);
    if(!str.isEmpty() && textcolor.isValid() && backgroundcolor.isValid())
    {
        QPixmap pixmap(size);
        pixmap.fill(backgroundcolor);
        QPainter* painter = new QPainter(&pixmap);
        QPen pen;
        QFont font;
        pen.setColor(textcolor);
        painter->setPen(pen);
        if(font_size <= 0)
        {
            int s = 0;
            font.setPixelSize(s+1);
            painter->setFont(font);
            while(pixmap.rect().contains(painter->boundingRect(pixmap.rect(),flags,str)))
            {
                s++;
                font.setPixelSize(s+1);
                painter->setFont(font);
            }
            font.setPixelSize(s);
        }
        else
        {
            font.setPixelSize(font_size);
        }
        painter->setFont(font);
        painter->drawText(pixmap.rect(),flags,str);
        return pixmap;
    }
    else
    {
        return QPixmap();
    }
}

#ifdef Network_Enabled
static bool sendTcpMessage(QHostAddress address,quint16 port,QString message)
{
    QTcpSocket* socket = new QTcpSocket();
    QEventLoop* loop = new QEventLoop();
    bool ret = false;
    QObject::connect(socket,QOverload<>::of(&QTcpSocket::connected),[socket,loop,&ret,message](){
        socket->write(message.toLatin1());
        ret = true;
        loop->quit();
    });
    QObject::connect(socket,QOverload<>::of(&QTcpSocket::disconnected),[socket,loop,&ret](){
        loop->quit();
    });
    socket->connectToHost(address,port);
    if(!ret)
        loop->exec();
    socket->disconnect();
    socket->disconnectFromHost();
    return ret;
}
#endif

static bool isSystemDarkMode()
{
#if(QT_VERSION>=QT_VERSION_CHECK(6,5,0))
    Qt::ColorScheme scheme = QGuiApplication::styleHints()->colorScheme();
    if(scheme != Qt::ColorScheme::Unknown)
        return bool(scheme==Qt::ColorScheme::Dark);
#endif
#if defined(Q_OS_ANDROID)
    QJniObject activity = QtAndroidPrivate::activity();
    if(activity.isValid())
    {
        QJniObject resources = activity.callObjectMethod("getResources", "()Landroid/content/res/Resources;");
        if (resources.isValid())
        {
            QJniObject configuration = resources.callObjectMethod("getConfiguration", "()Landroid/content/res/Configuration;");
            if (configuration.isValid())
            {
                jint uiMode = configuration.getField<jint>("uiMode");
                jint nightMode = QJniObject::getStaticField<jint>("android/content/res/Configuration", "UI_MODE_NIGHT_MASK");
                jint currentNightMode = uiMode & nightMode;
                if (currentNightMode == QJniObject::getStaticField<jint>("android/content/res/Configuration", "UI_MODE_NIGHT_YES"))
                {
                    return true;
                }
            }
        }
    }
    return false;
    /*
    if(activity.isValid())
    {
        int darkMode = QJniObject::callStaticMethod<jint>(
            javaPackage,
            "isDarkMode",
            "(Landroid/content/Context;)I",
            activity.object<jobject>()
        );
        if(darkMode == 1)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
    */
#else
#if defined(Q_OS_WIN)
    QSettings* settings = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",QSettings::NativeFormat);
    if(settings->contains("AppsUseLightTheme") && settings->value("AppsUseLightTheme") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
#if defined(Q_OS_MAC)
    return bool(runCommand("defaults read -g AppleInterfaceStyle")==QString("Dark"));
#else
    return false;
#endif
#endif
#endif

}
static void setDarkTitleBar(WId w,bool on = true)
{
#ifdef Q_OS_WIN
    Windows::setNativeDarkTitleBar(w,on);
#else
#endif
}
static void setApplicationDarkMode(bool on,QObject* mainWindow = qApp->topLevelWidgets().at(0),QList<QObject*> widgets = QList<QObject*>(),QList<QPalette> lightPalettes = QList<QPalette>(),QList<QPalette> darkPalettes = QList<QPalette>())
{
    const QString style = "Fusion";
#ifdef Q_OS_WIN
    QString native_style = "windowsvista";
#else
#ifdef Q_OS_ANDROID
    const QString native_style = "";
#else
    QString native_style = "";
#endif
#endif
//    for(QWidget* w : QApplication::topLevelWidgets())
//    {
//        setDarkTitleBar(w->winId(),on);
//    }
    QWidget* widget = static_cast<QWidget*>(mainWindow);
    if(on == true)
    {
        int j = 0;
        while(j < widgets.count() && j < darkPalettes.count())
        {
            QWidget* w = static_cast<QWidget*>(widgets.at(j));
            if(w)
            {
                w->setPalette(darkPalettes.at(j));
            }
            j++;
        }

        QObjectList list = allChildren(widget);
        for(int i = 0;i < list.count();i++)
        {
            QObject* obj = list.at(i);
            if(QString(obj->metaObject()->className()) == "QLineEdit" && static_cast<QLineEdit*>(obj) != nullptr)
            {
            }
            else if(static_cast<QWidget*>(obj) != nullptr && static_cast<QWidget*>(obj)->parent() == nullptr)
            {
                 setDarkTitleBar(static_cast<QWidget*>(obj)->winId(),on);
            }
            else if(QString(obj->metaObject()->className()) == "QComboBox" && static_cast<QComboBox*>(obj) != nullptr)
            {
                QPalette p3;
                p3.setColor(QPalette::Window,QColor(40,40,40));
                p3.setColor(QPalette::Button,QColor(40,40,40));
                p3.setColor(QPalette::Base,QColor(40,40,40));
                p3.setColor(QPalette::WindowText,Qt::white);
                p3.setColor(QPalette::ButtonText,Qt::white);
                static_cast<QComboBox*>(obj)->setPalette(p3);
                static_cast<QComboBox*>(obj)->update();
            }
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0)) && defined(Q_OS_ANDROID)
        if(Android::getSystemVersion() >= 12 && isSystemDarkMode())
            return;
#endif
        if(QApplication::style() != QStyleFactory::create(style))
        {
            QApplication::setStyle(QStyleFactory::create(style));
        }
        if(widget != nullptr)
        {
            setDarkTitleBar(widget->winId(),on);
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0)) && defined(Q_OS_WIN)
//        if(isSystemDarkMode())
//            return;
#endif
        QPalette p;
        p.setColor(QPalette::Window,QColor(40,40,40));
        p.setColor(QPalette::Button,QColor(40,40,40));
        p.setColor(QPalette::WindowText,Qt::white);
        p.setColor(QPalette::ButtonText,Qt::white);
        p.setColor(QPalette::Base,QColor(50,50,50));
        p.setColor(QPalette::Text,Qt::white);
        p.setColor(QPalette::PlaceholderText,QColor(160,160,160));
        p.setColor(QPalette::Disabled, QPalette::Window, QColor(68, 68, 68));
        QApplication::setPalette(p);
    }
    else
    {
        int j = 0;
        while(j < widgets.count() && j < lightPalettes.count())
        {
            QWidget* w = static_cast<QWidget*>(widgets.at(j));
            if(w)
            {
                w->setPalette(lightPalettes.at(j));
            }
            j++;
        }

        QObjectList list = allChildren(widget);
        for(int i = 0;i < list.count();i++)
        {
            QObject* obj = list.at(i);
            if(QString(obj->metaObject()->className()) == "QLineEdit" && static_cast<QLineEdit*>(obj) != nullptr)
            {
            }
            else if(static_cast<QWidget*>(obj) != nullptr && static_cast<QWidget*>(obj)->parent() == nullptr)
            {
                 setDarkTitleBar(static_cast<QWidget*>(obj)->winId(),on);
            }
            else if(QString(obj->metaObject()->className()) == "QComboBox" && static_cast<QComboBox*>(obj) != nullptr)
            {
                QPalette p3;
                p3.setColor(QPalette::Window,Qt::white);
                p3.setColor(QPalette::Button,Qt::white);
                p3.setColor(QPalette::Base,Qt::white);
                p3.setColor(QPalette::WindowText,Qt::black);
                p3.setColor(QPalette::ButtonText,Qt::black);
                static_cast<QComboBox*>(obj)->setPalette(p3);
                static_cast<QComboBox*>(obj)->update();
            }
        }
        if(QStyleFactory::keys().contains(native_style.toLatin1()) && QApplication::style() != QStyleFactory::create(native_style))
        {
            QApplication::setStyle(QStyleFactory::create(native_style));
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0)) && defined(Q_OS_ANDROID)
        if(Android::getSystemVersion() >= 12 && !isSystemDarkMode())
            return;
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0)) && defined(Q_OS_WIN)
        //return;
#endif
        QPalette p;
        p.setColor(QPalette::Window,QColor(240,240,240));
        p.setColor(QPalette::Button,QColor(240,240,240));
        p.setColor(QPalette::WindowText,Qt::black);
        p.setColor(QPalette::ButtonText,Qt::black);
        p.setColor(QPalette::Base,Qt::white);
        p.setColor(QPalette::PlaceholderText,QColor(160,160,160));
        p.setColor(QPalette::Text,Qt::black);
        p.setColor(QPalette::Disabled, QPalette::Window, QColor(68, 68, 68));
        QApplication::setPalette(p);
    }
}

static QImage getApplicationIcon()
{
#ifdef Q_OS_ANDROID
    return Android::getApplicationIcon();
#else
    return QFileIconProvider().icon(QFileInfo(QApplication::applicationFilePath())).pixmap(256,256).toImage();
#endif
}
static void openSystemSetting()
{
#ifdef Q_OS_WIN
    if(QFile::exists("C:/Windows/ImmersiveControlPanel/SystemSettings.exe"))
    {
        Windows::LaunchUri("ms-settings:");
    }
    else
    {
        QProcess::startDetached("control.exe");
    }
#else
#ifdef Q_OS_ANDROID
    //Android::startIntent("android.settings.SETTINGS");
    Android::startApplication("com.android.settings");
#endif
#endif
}
static void openSystemExplorer(QString path = "")
{
#ifdef Q_OS_WIN
    if(QFileInfo(path).isDir())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
    else if(QFileInfo(path).isFile())
    {
        ShellExecuteW(NULL, L"open", L"explorer", QString("/select, \"%1\"").arg(path.replace("/","\\")).toStdWString().c_str(), NULL, SW_SHOW);
    }
    else
    {
        QProcess::startDetached("explorer.exe");
    }
#else
#ifdef Q_OS_ANDROID
    Android::startApplication("com.android.documentsui");
#else
    if(QFileInfo(path).isFile() && !QFileInfo(path).absolutePath().isEmpty())
    {
        path = QFileInfo(path).absolutePath();
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
#endif
#endif
}

static bool setWallpaper(QImage wallpaper)
{
#ifdef Q_OS_WIN
    return Windows::setNativeWallpaper(wallpaper);
#else
#ifdef Q_OS_ANDROID
    return Android::setNativeWallpaper(wallpaper);
#else
    return false;
#endif
#endif
}
static bool setWallpaper(QString wallpaperFilePath)
{
#ifdef Q_OS_WIN
    return Windows::setNativeWallpaper(wallpaperFilePath);
#else
#ifdef Q_OS_ANDROID
    return Android::setNativeWallpaper(wallpaperFilePath);
#else
    return false;
#endif
#endif
}
static QImage getWallpaper()
{
#ifdef Q_OS_WIN
    return Windows::getNativeWallpaper();
#else
#ifdef Q_OS_ANDROID
    return Android::getNativeWallpaper();
#else
    return false;
#endif
#endif
}

static QPixmap getSplashPixmap(QSize size,QPixmap icon = QPixmap::fromImage(getApplicationIcon()),QString name = qApp->applicationName(),bool dark = isSystemDarkMode(),int alpha = 255)
{
    QColor textcolor;
    QColor backgroundcolor;
    if(dark)
    {
        textcolor = Qt::white;
        backgroundcolor = QColor(40,40,40,alpha);
    }
    else
    {
        textcolor = Qt::black;
        backgroundcolor = QColor(255,255,255,alpha);
    }
    QPixmap pixmap(size);
    pixmap.fill(backgroundcolor);
    QPainter* painter = new QPainter(&pixmap);
    if(icon.isNull() || size.width() <= size.height())
    {
        painter->drawPixmap(QPoint(size.width()/4,size.height()/4),textPixmap(name,textcolor,backgroundcolor,size/2,Qt::AlignCenter));
    }
    else
    {
        icon = icon.scaled(QSize(size.height()/2/3,size.height()/2/3),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        painter->drawPixmap(QPoint(size.width()/4,size.height()/4+size.height()/2/3),icon);
        painter->drawPixmap(QPoint(size.width()/4+size.height()/2/3+10,size.height()/4),textPixmap(name,textcolor,backgroundcolor,QSize(size.width()/2-size.height()/2/3-10,size.height()/2),Qt::AlignCenter));
    }
    return pixmap;
}

static QString toString(QColor c)
{
    QString s;
    s += "rgba(";
    s += QString::number(c.red());
    s += ",";
    s += QString::number(c.green());
    s += ",";
    s += QString::number(c.blue());
    s += ",";
    s += QString::number(c.alpha());
    s += ")";
    return s;
}
static QString toLinkedString(QString s,QString url)
{
    return QString("<a href=\""+url+"\">"+s+"</a>");
}

static bool isTopMostWindow(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w != nullptr)
    {
        if(w->windowFlags().testFlag(Qt::WindowStaysOnTopHint))
            return true;
        else
        {
#ifdef Q_OS_WIN
            HWND hwnd = (HWND)w->winId();
            LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
            return ((exStyle & WS_EX_TOPMOST) != 0);
#else
            return false;
#endif
        }
    }
    else
    {
        return false;
    }
}

static double getSum(QTableWidget* w)
{
    double sum = 0;
    for(int row = 0; row < w->rowCount(); row++)
    {
        for(int column = 0; column < w->columnCount(); column++)
        {
            auto item = w->item(row,column);
            if(item != nullptr)
            {
                QString text = item->text();
                if(isDouble(text))
                {
                    double d = text.toDouble();
                    sum += d;
                }
            }
        }
    }
    return sum;
}
static double getRowSum(QTableWidget* w,int row)
{
    double sum = 0;
    for(int column = 0; column < w->columnCount(); column++)
    {
        auto item = w->item(row,column);
        if(item != nullptr)
        {
            QString text = item->text();
            if(isDouble(text))
            {
                double d = text.toDouble();
                sum += d;
            }
        }
    }
    return sum;
}
static double getColumnSum(QTableWidget* w,int column)
{
    double sum = 0;
    for(int row = 0; row < w->rowCount(); row++)
    {
        auto item = w->item(row,column);
        if(item != nullptr)
        {
            QString text = item->text();
            if(isDouble(text))
            {
                double d = text.toDouble();
                sum += d;
            }
        }
    }
    return sum;
}
static void moveRow(QTableWidget* w,int oldRowIndex,int newRowIndex)
{
    QList<QTableWidgetItem*> list;
    for(int column = 0; column < w->columnCount(); column++)
        list.append(w->takeItem(oldRowIndex,column));
    w->removeRow(oldRowIndex);
    w->insertRow(newRowIndex);
    for(int column = 0; column < w->columnCount(); column++)
        w->setItem(newRowIndex,column,list.at(column));
}
template <class T>
static int getMinIndex(QList<T> list,int beginIndex = 0,int endIndex = -1)
{
    if(endIndex == -1)
        endIndex = list.count();
    int ret = beginIndex, index = beginIndex;
    T value = list.at(index);
    index++;
    while(index < endIndex)
    {
        T current = list.at(index);
        if(current < value)
        {
            value = current;
            ret = index;
        }
        index++;
    }
    return ret;
}
template <class T>
static int getMaxIndex(QList<T> list,int beginIndex = 0,int endIndex = -1)
{
    if(endIndex == -1)
        endIndex = list.count();
    int ret = beginIndex, index = beginIndex;
    T value = list.at(index);
    index++;
    while(index < endIndex)
    {
        T current = list.at(index);
        if(current > value)
        {
            value = current;
            ret = index;
        }
        index++;
    }
    return ret;
}
template <class T>
static T getMinValue(QList<T> list,int beginIndex = 0,int endIndex = -1) {return list.at(getMinIndex(list,beginIndex,endIndex));}
template <class T>
static T getMaxValue(QList<T> list,int beginIndex = 0,int endIndex = -1) {return list.at(getMaxIndex(list,beginIndex,endIndex));}
template <class T>
static QList<T> sort(QList<T> list,Qt::SortOrder order,int beginIndex = 0,int endIndex = -1)
{
    if(endIndex == -1)
        endIndex = list.count();
    int index = beginIndex;
    while(index < endIndex)
    {
        T current = list.at(index);
        int i;
        if(order == Qt::DescendingOrder)
            i = getMaxIndex(list,index,endIndex);
        else
            i = getMinIndex(list,index,endIndex);
        T v = list.at(i);
        list[i] = current;
        list[index] = v;
        index++;
    }
    return list;
}
static QStringList getRowData(QTableWidget* w,int row,int beginColumnIndex = 0,int endColumnIndex = -1)
{
    QStringList list;
    if(row < 0 || row >= w->rowCount()) return list;
    if(endColumnIndex == -1) endColumnIndex = w->columnCount();
    for(int column = beginColumnIndex; column < endColumnIndex; column++)
    {
        auto item = w->item(row,column);
        list.append(item == nullptr ? QString() : item->text());
    }
    return list;
}
static QStringList getColumnData(QTableWidget* w,int column,int beginRowIndex = 0,int endRowIndex = -1)
{
    QStringList list;
    if(column < 0 || column >= w->columnCount()) return list;
    if(endRowIndex == -1) endRowIndex = w->rowCount();
    for(int row = beginRowIndex; row < endRowIndex; row++)
    {
        auto item = w->item(row,column);
        list.append(item == nullptr ? QString() : item->text());
    }
    return list;
}
static QList<QTableWidgetItem*> getRowItems(QTableWidget* w,int row,bool takeaway,int beginColumnIndex = 0,int endColumnIndex = -1)
{
    QList<QTableWidgetItem*> list;
    if(endColumnIndex == -1) endColumnIndex = w->columnCount();
    for(int column = beginColumnIndex; column < endColumnIndex; column++)
    {
        if(takeaway)
            list.append(w->takeItem(row,column));
        else
            list.append(w->item(row,column));
    }
    return list;
}
static QList<QTableWidgetItem*> getColumnItems(QTableWidget* w,int column,bool takeaway,int beginRowIndex = 0,int endRowIndex = -1)
{
    QList<QTableWidgetItem*> list;
    if(endRowIndex == -1) endRowIndex = w->rowCount();
    for(int row = beginRowIndex; row < endRowIndex; row++)
    {
        if(takeaway)
            list.append(w->takeItem(row,column));
        else
            list.append(w->item(row,column));
    }
    return list;
}
static void setRowItems(QTableWidget* w,int row,QList<QTableWidgetItem*> items,int beginColumnIndex = 0,int endColumnIndex = -1)
{
    if(endColumnIndex == -1) endColumnIndex = w->columnCount();
    int i = 0;
    for(int column = beginColumnIndex; column < endColumnIndex && i < items.count(); column++)
    {
        w->setItem(row,column,items.at(i));
        i++;
    }
}
static void setColumnItems(QTableWidget* w,int column,QList<QTableWidgetItem*> items,int beginRowIndex = 0,int endRowIndex = -1)
{
    if(endRowIndex == -1) endRowIndex = w->rowCount();
    int i = 0;
    for(int row = beginRowIndex; row < endRowIndex && i < items.count(); row++)
    {
        w->setItem(row,column,items.at(i));
        i++;
    }
}
static void swapRow(QTableWidget* w,int row1,int row2,int beginColumnIndex = 0,int endColumnIndex = -1)
{
    if(row1 == row2) return;
    auto list1 = getRowItems(w,row1,true,beginColumnIndex,endColumnIndex);
    auto list2 = getRowItems(w,row2,true,beginColumnIndex,endColumnIndex);
    setRowItems(w,row1,list2,beginColumnIndex,endColumnIndex);
    setRowItems(w,row2,list1,beginColumnIndex,endColumnIndex);
}
static void swapColumn(QTableWidget* w,int column1,int column2,int beginRowIndex = 0,int endRowIndex = -1)
{
    if(column1 == column2) return;
    auto list1 = getColumnItems(w,column1,true,beginRowIndex,endRowIndex);
    auto list2 = getColumnItems(w,column2,true,beginRowIndex,endRowIndex);
    setColumnItems(w,column1,list2,beginRowIndex,endRowIndex);
    setColumnItems(w,column2,list1,beginRowIndex,endRowIndex);
}
static int getMaxNumberIndex(QStringList list,int beginIndex = 0,int endIndex = -1)
{
    if(endIndex == -1)
        endIndex = list.count();
    int index = beginIndex, ret = -1;
    double value;
    bool flag_init = false;
    while(index < endIndex)
    {
        QString s = list.at(index);
        if(isDouble(s))
        {
            double n = s.toDouble();
            if(!flag_init || n > value)
            {
                value = n;
                ret = index;
                flag_init = true;
            }
        }
        index++;
    }
    return ret;
}
static int getMinNumberIndex(QStringList list,int beginIndex = 0,int endIndex = -1)
{
    if(endIndex == -1)
        endIndex = list.count();
    int index = beginIndex, ret = -1;
    double value;
    bool flag_init = false;
    while(index < endIndex)
    {
        QString s = list.at(index);
        if(isDouble(s))
        {
            double n = s.toDouble();
            if(!flag_init || n < value)
            {
                value = n;
                ret = index;
                flag_init = true;
            }
        }
        index++;
    }
    return ret;
}
static QList<int> getNumberIndexes(QStringList list,int beginIndex = 0,int endIndex = -1)
{
    QList<int> ret;
    if(endIndex == -1)
        endIndex = list.count();
    for(int i = beginIndex; i < endIndex; i++)
        if(isDouble(list.at(i)))
            ret.append(i);
    return ret;
}
static void sortByColumn(QTableWidget* w,int column,Qt::SortOrder order,int beginRowIndex = 0,int endRowIndex = -1)
{
    if(endRowIndex == -1)
        endRowIndex = w->rowCount();
    QStringList data = getColumnData(w,column,beginRowIndex,endRowIndex);
    int index = beginRowIndex;
    int i;
    if(order == Qt::AscendingOrder)
        i = getMinNumberIndex(data);
    else
        i = getMaxNumberIndex(data);
    while(index < endRowIndex && i != -1)
    {
        int row = i + beginRowIndex;
        swapRow(w,row,index);
        data.swapItemsAt(i,index - beginRowIndex);
        index++;
        if(order == Qt::AscendingOrder)
            i = getMinNumberIndex(data,index - beginRowIndex);
        else
            i = getMaxNumberIndex(data,index - beginRowIndex);
    }
}
static void sortByColumn(QTableWidget* w,int column,QString key,bool exactMatch = false,bool caseSensitive = false,int beginRowIndex = 0,int endRowIndex = -1)
{
    if(endRowIndex == -1)
        endRowIndex = w->rowCount();
    QStringList data = getColumnData(w,column,beginRowIndex,endRowIndex);
    QList<int> rows;
    for(int index = beginRowIndex; index < endRowIndex; index++)
    {
        QString s = data.at(index - beginRowIndex);
        if((exactMatch && caseSensitive && key == s)
        || (exactMatch && !caseSensitive && key.toLower() == s.toLower())
        || (!exactMatch && caseSensitive && s.contains(key,Qt::CaseSensitive))
        || (!exactMatch && !caseSensitive && s.contains(key,Qt::CaseInsensitive)))
        {
            //rows.append(index);
        }
        else
        {
            rows.append(index);
        }
    }
    std::reverse(rows.begin(),rows.end());
    for(int i = 0; i < rows.count(); i++)
        w->removeRow(rows.at(i));
}
static void removeGroup(QSettings* setting,QString name)
{
    if(setting->childGroups().contains(name))
    {
        setting->beginGroup(name);
        for(QString key : setting->childKeys())
            setting->remove(key);
        for(QString group : setting->childGroups())
            removeGroup(setting,group);
        setting->endGroup();
    }
}
static QStringList allChildKeys(QSettings* setting,QString groupName = QString(),QStringList names = QStringList())
{
    QStringList list;
    if(groupName.isEmpty() || setting->childGroups().contains(groupName))
    {
        bool flag_begin = false;
        if(!groupName.isEmpty())
        {
            flag_begin = true;
            setting->beginGroup(groupName);
            names.append(groupName);
        }
        QString head = names.join("/");
        for(QString key : setting->childKeys())
            list.append(head+"/"+key);
        for(QString group : setting->childGroups())
            list.append(allChildKeys(setting,group,names));
        if(flag_begin)
            setting->endGroup();
    }
    return list;
}
static void renameGroup(QSettings* setting,QString oldname,QString newname)
{
    auto list = allChildKeys(setting,oldname);
    for(int i = 0; i < list.count(); i++)
    {
        QString s = list.at(i);
        QVariant var = setting->value(s);
        setting->remove(s);

        s.remove(0,oldname.length());
        s = newname + s;
        setting->setValue(s,var);
    }
}

#endif // API_H
