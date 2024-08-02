#include "myfiledialog.h"

MyFileDialog::MyFileDialog(QWidget *parent)
    : QDialog(parent)
{
#ifdef Q_Device_Mobile
    this->resize(screensize());
#else
    this->resize(500,300);
#endif
    mainwidget = new SettingWidget(this);
    backbutton = new QPushButton(this);
    closebutton = new QPushButton(this);
    commitbutton = new QPushButton(this);
    pathedit = new QLineEdit(this);
    pathbox = new QComboBox(this);
    bar = new QProgressBar(this);
    filter = new MyNativeEventFilter;

    pathedit->setClearButtonEnabled(true);
    bar->setTextVisible(false);
    bar->hide();
    bar->setStyleSheet("QProgressBar::chunk{background-color:"+toString(QColor(0,103,192))+";}");
    filter->install();
    backbutton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    closebutton->setStyleSheet(backbutton->styleSheet());
    this->initPathBox();

#ifdef Q_OS_WIN
    pathlist = QList<QString>({QDir().homePath()});
#else
#ifdef Q_OS_ANDROID
    pathlist = QList<QString>({"/sdcard"});
#else
    pathlist = QList<QString>({qApp->applicationDirPath()});
#endif
#endif

    QObject::connect(mainwidget,QOverload<int,QString>::of(&SettingWidget::itemDoubleClicked),[=](int index,QString key){
        if(this->testOption(needDoubleClick))
        {
            this->itemVaildClicked(index,key);
        }
    });
    QObject::connect(mainwidget,QOverload<int,QString>::of(&SettingWidget::itemRightButtonClicked),[=](int index,QString key){
        this->requestMenu(key);
    });
    QObject::connect(mainwidget,QOverload<int,QString>::of(&SettingWidget::itemClicked),[=](int index,QString key){
        if(!this->testOption(needDoubleClick))
        {
            this->itemVaildClicked(index,key);
        }
    });
    QObject::connect(pathedit,QOverload<>::of(&QLineEdit::returnPressed),[=](){
        pathedit->setText(toStandardFilePath(pathedit->text()));
        QString text = pathedit->text();
        QFileInfo info = QFileInfo(text);
        if(text != this->currentPath())
        {
            if(info.isDir())
            {
                this->loadPath(text);
            }
            else if(info.isFile())
            {
                if(m == OpenFile || m == SaveFile)
                {
                    selectedfile = text;
                    flag_accept = true;
                    closebutton->clicked();
                }
                else
                {
                    text = QFileInfo(text).absolutePath();
                    pathedit->setText(text);
                    this->loadPath(text);
                }
            }
            else if(m == SaveFile && hasFilePermission(text,QIODevice::WriteOnly))
            {
                selectedfile = text;
                flag_accept = true;
                closebutton->clicked();
            }
            else
            {
                pathedit->setText(this->currentPath());
            }
        }
    });
    QObject::connect(backbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        QString last = QFileInfo(this->currentPath()).absolutePath();
        last = toStandardFilePath(last);
        if(last == this->currentPath())
            closebutton->clicked();
        else
            this->loadPath(last);
    });
    QObject::connect(commitbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        if(m == OpenDir)
        {
            flag_accept = true;
            closebutton->clicked();
        }
        else if(m == SaveFile)
        {
            pathedit->returnPressed();
        }
    });
    QObject::connect(closebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        this->close();
    });
#ifdef Q_OS_WIN
    QObject::connect(filter,QOverload<MSG*,LRESULT*>::of(&MyNativeEventFilter::winDeviceArrival),[=](){
        this->initPathBox();
    });
    QObject::connect(filter,QOverload<MSG*,LRESULT*>::of(&MyNativeEventFilter::winDeviceRemove),[=](){
        this->initPathBox();
    });
#endif
    this->refreshUI();
    backbutton->setFocusPolicy(Qt::NoFocus);
    closebutton->setFocusPolicy(backbutton->focusPolicy());
    commitbutton->setFocusPolicy(backbutton->focusPolicy());
    pathedit->setFocusPolicy(Qt::ClickFocus);
    backbutton->clearFocus();
    mainwidget->setFocus();
    this->installEventFilter(this);
    pathedit->installEventFilter(this);
    QTimer::singleShot(0,[=](){
        this->show();
        if(pathedit->text().isEmpty())
            this->loadPath(this->currentPath());
    });
}
bool MyFileDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            this->refreshUI();
        }
        else if(event->type() == QEvent::Close)
        {
            if(!flag_accept)
            {
                selectedfile = QString();
                pathlist.clear();
            }
            flag_accept = false;
        }
        else if(event->type() == QEvent::KeyRelease)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Back || keyEvent->key() == Qt::Key_Escape)
            {
                backbutton->clicked();
                return true;
            }
        }
    }
    else if(static_cast<QLineEdit*>(watched) != nullptr)
    {
        if(event->type() == QEvent::KeyRelease)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Back || keyEvent->key() == Qt::Key_Escape)
            {
                QGuiApplication::inputMethod()->hide();
                this->setFocus();
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}
void MyFileDialog::refreshUI()
{
    //mainwidget->resize(this->size());
    backbutton->resize(30,30);
    backbutton->move(5,5);
    closebutton->resize(backbutton->size());
    closebutton->move(this->width()-backbutton->x()-closebutton->width(),backbutton->y());
    pathbox->move(2*backbutton->x()+backbutton->width(),backbutton->y());
    pathbox->resize(closebutton->x()-pathbox->x()-backbutton->x(),backbutton->height());
    pathedit->resize(closebutton->x()+closebutton->width()-backbutton->x(),backbutton->height());
    pathedit->move(backbutton->x(),this->height()-pathedit->height()-backbutton->y());
    mainwidget->resize(pathedit->width(),pathedit->y()-3*backbutton->y()-backbutton->height());
    mainwidget->move(backbutton->x(),backbutton->height()+2*backbutton->y());
    bar->resize(mainwidget->width(),mainwidget->y()-backbutton->y()-backbutton->height());
    bar->move(backbutton->x(),backbutton->y()+backbutton->height());
#if defined(Q_OS_WIN) || defined(Q_OS_MAC) //窗口自带返回键的平台
    pathbox->resize(closebutton->x()+closebutton->width()-pathbox->x(),pathbox->height());
    closebutton->hide();
#endif
    if(m != OpenDir && m != SaveFile)
    {
        commitbutton->hide();
    }
    else
    {
        commitbutton->show();
        commitbutton->resize(mainwidget->width(),backbutton->height());
        commitbutton->move(backbutton->x(),this->height()-commitbutton->height()-backbutton->y());
        mainwidget->resize(mainwidget->width(),mainwidget->height()-(this->height()-commitbutton->y()));
        pathedit->move(pathedit->x(),pathedit->y()-(this->height()-commitbutton->y()));
    }
    if(m == SaveFile)
        commitbutton->setText("保存");
    else if(m == OpenDir)
        commitbutton->setText("选择文件夹");
    commitbutton->setStyleSheet("QPushButton{color:white;background-color:"+toString(QColor(0,103,192))+";border-radius:"+QString::number(commitbutton->height()/2)+"px}"
                                +"QPushButton:hover{color:white;background-color:"+toString(QColor(10,113,202))+";}"
                                +"QPushButton:pressed{color:white;background-color:"+toString(QColor(30,133,222))+";}");
    backbutton->setIconSize(backbutton->size());
    closebutton->setIconSize(closebutton->size());
    if(this->testOption(useDarkModeIcon))
    {
        backbutton->setIcon(QIcon(":/icon/back_white.png"));
        closebutton->setIcon(QIcon(":/icon/close_white.png"));
    }
    else
    {
        backbutton->setIcon(QIcon(":/icon/back_black.png"));
        closebutton->setIcon(QIcon(":/icon/close_black.png"));
    }
}
QString MyFileDialog::toStandardFilePath(QString path)
{
    path.replace("\\","/");
    if(path.endsWith("/") && path != "/" && path != ":/" && !(path.length() == 3 && path.endsWith(":/")))
        path.chop(1);
    if(!QFileInfo(path).isAbsolute())
    {
        QString abs = QFileInfo(path).absoluteFilePath();
        if(!abs.isEmpty())
            path = abs;
    }
    return path;
}
void MyFileDialog::loadPath(QString path)
{
    path = toStandardFilePath(path);
    QFileInfo fileinfo = QFileInfo(path);
    bool exists = true;
    if(!fileinfo.isFile() && !fileinfo.isDir() && hasFilePermission(path,QIODevice::WriteOnly))
    {
        QFile f(path);
        exists = f.exists();
        if(f.open(QIODevice::WriteOnly))
        {
            f.close();
        }
    }

    if(fileinfo.isFile())
    {
        if(!exists)
            QFile::remove(path);
        pathedit->setText(path);
        path = fileinfo.absolutePath();
        fileinfo = QFileInfo(path);
    }
    else if(fileinfo.isDir())
    {
        pathedit->setText(path);
    }

    if(fileinfo.isDir())
    {
        mainwidget->clear();
        mainwidget->hide();
        this->update();
        mainwidget->update();
        this->setFocus();
        pathedit->clearFocus();
        if(pathlist.isEmpty())
            emit currentPathChanged(QString(),path);
        else
            emit currentPathChanged(pathlist.last(),path);
        pathlist.append(path);
        QString last = fileinfo.absolutePath();
        last = toStandardFilePath(last);
        if(last != path)
        {
            mainwidget->addItem(last,"...",SettingWidget::Empty,QVariant(),QVariant(),iconprovider.icon(MyFileIconProvider::Folder));
        }
        auto list = QDir(path).entryInfoList(QDir::AllEntries | QDir::Hidden | QDir::System);
        bar->setRange(0,list.count());
        bar->setValue(0);
        bar->show();
        for(QFileInfo info : list)
        {
            bar->setValue(bar->value()+1);
            bar->update();
            qApp->processEvents();

            QIcon icon;
            QString name = info.fileName();
            SettingWidget::Mode mode = SettingWidget::Empty;
            if(!this->testOption(showDotAndDotDot) && (name == "." || name == ".."))
                continue;
            if(!this->testOption(showHideenFile) && (info.isHidden()))
                continue;
            if(this->testOption(showIcon))
            {
                if(info.isDir())
                {
                    icon = iconprovider.icon(MyFileIconProvider::Folder);
                }
                else
                {
                    if(toStringList(QImageReader::supportedImageFormats()).contains(info.suffix()) && (max_load_image_size < 0 || info.size() < max_load_image_size))
                    {
                        QPixmap p;
                        if(p.loadFromData(readfile(info.absoluteFilePath())))
                        {
                            p = p.scaled(QSize(mainwidget->itemHeight(),mainwidget->itemHeight()),Qt::KeepAspectRatio,Qt::FastTransformation);
                            icon = QIcon(p);
                        }
                    }
                    if(icon.isNull() && !info.absoluteFilePath().startsWith(":/"))
                    {
                        icon = iconprovider.icon(info);
                    }
                    else if(icon.isNull())
                    {
                        icon = iconprovider.icon(MyFileIconProvider::File);
                    }
                }
            }
            if(!this->testOption(showFile) && info.isFile())
                continue;
            if(!this->testOption(showDir) && info.isDir())
                continue;
            if(!showsuffixs.isEmpty() && !showsuffixs.contains(info.suffix()))
                continue;
            if(hiddenfiles.contains(info.absoluteFilePath()))
                continue;
            if(!this->testOption(showSuffix) && info.isFile() && name.contains("."))
                name.chop(info.suffix().length()+1);
            mainwidget->addItem(info.absoluteFilePath(),name,mode,QVariant(),QVariant(),icon);
            mainwidget->update();
        }
        mainwidget->show();
        mainwidget->setFocus();
        bar->hide();
    }
}
void MyFileDialog::itemVaildClicked(int index, QString key)
{
    if(QFileInfo(key).isDir())
    {
        this->loadPath(key);
    }
    else
    {
        if(m == Explorer)
        {
#ifndef Q_OS_ANDROID
            QDesktopServices::openUrl(QUrl::fromLocalFile(key));
#else
            Android::shareFile(Android::getUriForFile(key));
#endif
        }
        else if(m == OpenFile)
        {
            emit currentSelectedFileChanged(key);
            selectedfile = key;
            flag_accept = true;
            closebutton->clicked();
        }
        else if(m == SaveFile)
        {
            pathedit->setText(key);
        }
    }
}
void MyFileDialog::requestMenu(QString path)
{
    QFileInfo info = QFileInfo(path);
    if(info.isFile() || info.isDir())
    {
        QMenu* menu = new QMenu;
        QAction* selectaction = new QAction;
        QAction* openaction = new QAction;
        QAction* opendiraction = new QAction;
        //QAction* infoaction = new QAction;
        //QAction* deleteaction = new QAction;
        QString opendirtext;
#ifdef Q_OS_WIN
        opendirtext = "在Explorer中打开";
#else
#ifdef Q_OS_MAC
        opendirtext = "在Finder中打开";
#else
#ifdef Q_Device_Mobile
        opendirtext = "";
#else
        opendirtext = "打开文件夹";
#endif
#endif
#endif

        if(info.isDir())
        {
            openaction->setText("打开");
        }
        else
        {
#ifdef Q_Device_Desktop
            openaction->setText("打开");
#else
            openaction->setText("分享");
#endif
        }
        opendiraction->setText(opendirtext);
        selectaction->setText("选择");

        if((m == OpenFile && info.isFile()) || (m == OpenDir && info.isDir()))
            menu->addAction(selectaction);
        menu->addAction(openaction);
        if(!opendirtext.isEmpty())
            menu->addAction(opendiraction);

        QObject::connect(selectaction,QOverload<bool>::of(&QAction::triggered),[=](){
            if(info.isFile())
                selectedfile = path;
            else
                pathlist.append(path);
            flag_accept = true;
            closebutton->clicked();
        });
        QObject::connect(openaction,QOverload<bool>::of(&QAction::triggered),[=](){
            if(info.isDir())
                this->loadPath(path);
            else
            {
#ifndef Q_OS_ANDROID
                QDesktopServices::openUrl(QUrl::fromLocalFile(path));
#else
                Android::shareFile(Android::getUriForFile(path));
#endif
            }
        });
        QObject::connect(opendiraction,QOverload<bool>::of(&QAction::triggered),[=](){
            openSystemExplorer(path);
        });

        menu->exec(QCursor::pos());
    }
}
QString MyFileDialog::getOpenFileName(QObject *parent, QString caption, QString dir, bool useNativeMethod,bool isDarkMode)
{
    if(!useNativeMethod)
    {
        MyFileDialog* dlg = new MyFileDialog(static_cast<QWidget*>(parent));
        dlg->setMode(OpenFile);
        dlg->setWindowTitle(caption);
#ifdef Q_Device_Desktop
        dlg->resize(500,300);
        dlg->move(screenwidth()/2-dlg->width()/2,screenheight()/2-dlg->height()/2);
#else
        dlg->resize(screensize());
#endif
        dlg->setOption(useDarkModeIcon,isDarkMode);
        dlg->loadPath(dir);
        dlg->exec();
        return dlg->currentSelectedFile();
    }
    else
    {
#ifndef Q_OS_ANDROID
        return QFileDialog::getOpenFileName(static_cast<QWidget*>(parent),caption,dir);
#else
        return startOpenDocumentIntent_private("android.intent.action.OPEN_DOCUMENT",dir,"*/*");
#endif
    }
}
QString MyFileDialog::getExistingDirectory(QObject *parent, QString caption, QString dir, bool useNativeMethod,bool isDarkMode)
{
    if(!useNativeMethod)
    {
        MyFileDialog* dlg = new MyFileDialog(static_cast<QWidget*>(parent));
        dlg->setMode(OpenDir);
        dlg->setWindowTitle(caption);
        dlg->setOption(showFile,false);
#ifdef Q_Device_Desktop
        dlg->resize(500,300);
        dlg->move(screenwidth()/2-dlg->width()/2,screenheight()/2-dlg->height()/2);
#else
        dlg->resize(screensize());
#endif
        dlg->setOption(useDarkModeIcon,isDarkMode);
        dlg->loadPath(dir);
        dlg->exec();
        return dlg->currentPath();
    }
    else
    {
#ifndef Q_OS_ANDROID
        return QFileDialog::getExistingDirectory(static_cast<QWidget*>(parent),caption,dir);
#else
        return startOpenDocumentIntent_private("android.intent.action.OPEN_DOCUMENT_TREE",dir,"*/*");
#endif
    }
}
QString MyFileDialog::getSaveFileName(QObject *parent, QString caption, QString dir, bool useNativeMethod,bool isDarkMode)
{
    if(!useNativeMethod)
    {
        MyFileDialog* dlg = new MyFileDialog(static_cast<QWidget*>(parent));
        dlg->setMode(SaveFile);
        dlg->setWindowTitle(caption);
#ifdef Q_Device_Desktop
        dlg->resize(500,300);
        dlg->move(screenwidth()/2-dlg->width()/2,screenheight()/2-dlg->height()/2);
#else
        dlg->resize(screensize());
#endif
        dlg->setOption(useDarkModeIcon,isDarkMode);
        dlg->loadPath(dir);
        dlg->exec();
        return dlg->currentSelectedFile();
    }
    else
    {
#ifndef Q_OS_ANDROID
        return QFileDialog::getSaveFileName(static_cast<QWidget*>(parent),caption,dir);
#else
        return startOpenDocumentIntent_private("android.intent.action.CREATE_DOCUMENT",dir,"*/*");
#endif
    }
}
void MyFileDialog::initPathBox()
{
    if(!flag_pathbox_connected)
    {
        flag_pathbox_connected = true;
        QObject::connect(pathbox,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int i){
            if(i == 0)
                return;
            QString path = pathbox->itemText(i);
            if(QFileInfo(path).isDir())
            {
                pathbox->setCurrentIndex(0);
                this->loadPath(path);
            }
        });
    }
#ifndef Q_OS_ANDROID
    QString datapath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/"+QApplication::applicationName();
#else
    QString datapath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
#endif
    if(!QFileInfo(datapath).isDir())
        QDir().mkpath(datapath);
    QStringList list = {"选择常用路径"};
#ifdef Q_OS_WIN
    list.append(Windows::getDrivers());
#endif
    list.append(datapath);
    list.append(qApp->applicationDirPath());
#ifdef Q_OS_WIN
    list.append(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    list.append(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
    list.append(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    list.append(QStandardPaths::writableLocation(QStandardPaths::MusicLocation));

    pathbox->clear();
    pathbox->addItems(list);
    for(int i = 0; i < pathbox->count(); i++)
    {
        QFileInfo info = QFileInfo(pathbox->itemText(i));
        QIcon icon;
        if(info.isRoot())
            icon = iconprovider.icon(MyFileIconProvider::Drive);
        else if(info.absoluteFilePath() == QStandardPaths::writableLocation(QStandardPaths::DesktopLocation))
            icon = iconprovider.icon(MyFileIconProvider::Desktop);
        else if(info.isDir())
            icon = iconprovider.icon(info);
        pathbox->setItemIcon(i,icon);
    }
#else
#ifdef Q_OS_ANDROID
    list.append(QDir().homePath());
    list.append("/sdcard");
    list.append("/");
    if(QFileInfo("/sdcard/Download").isDir())
        list.append("/sdcard/Download");
    if(QFileInfo("/sdcard/Documents").isDir())
        list.append("/sdcard/Documents");
    if(QFileInfo("/sdcard/Music").isDir())
        list.append("/sdcard/Music");
    if(QFileInfo("/sdcard/Pictures").isDir())
        list.append("/sdcard/Pictures");
    if(QFileInfo("/sdcard/DCIM/Camera").isDir())
        list.append("/sdcard/DCIM/Camera");
    else if(QFileInfo("/sdcard/DCIM").isDir())
        list.append("/sdcard/DCIM");
#endif
    pathbox->clear();
    pathbox->addItems(list);
#endif
}
