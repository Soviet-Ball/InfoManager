#include "widget.h"
#include <QSet>
void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    Widget* w = Widget::getCurrentWindow();
    if(w != nullptr)
    {
        w->qtMessageUpdated(type,context,msg);
    }
}
void androidConfigurationChanged_native()
{
    Widget* w = Widget::getCurrentWindow();
    if(w != nullptr)
    {
        w->androidConfigurationChanged();
    }
}
void Widget::initSettings(bool clear)
{
    if(settingpath.isEmpty())
    {
        settingpath = datapath + "/settings.ini";
    }
    if(settings != nullptr)
    {
        settings->sync();
        settings = nullptr;
    }
    if(clear && QFileInfo(settingpath).isFile())
    {
        if(!QFile::remove(settingpath))
            emit error("删除文件"+settingpath+"失败");
    }
    bool exists = QFileInfo(settingpath).isFile();
    settings = new QSettings(settingpath,QSettings::IniFormat,this);
    if(settings->status() == QSettings::NoError)
    {
        settings = new QSettings(settingpath,QSettings::IniFormat,this);
        QStringList keylist;
        QStringList valuelist;
        if(true)
        {
            keylist.append("x");
            valuelist.append("-1");
            keylist.append("y");
            valuelist.append("-1");
            keylist.append("width");
            valuelist.append("-1");
            keylist.append("height");
            valuelist.append("-1");
            keylist.append("appTheme");
            valuelist.append("system");
            keylist.append("loadGeometry");
            valuelist.append("false");
            keylist.append("staysOnTop");
            valuelist.append("false");
            keylist.append("useSplashScreen");
            valuelist.append("true");
            keylist.append("requestAdminOrRoot");
            valuelist.append("false");
            keylist.append("showConsoleWindow");
            valuelist.append("false");
            keylist.append("writeMessageToLog");
            valuelist.append("false");
            keylist.append("useMessageContext");
            valuelist.append("false");
            keylist.append("showMessageToast");
            valuelist.append("true");
            keylist.append("appFileDialog");
            valuelist.append("qfiledialog");
            keylist.append("defaultProjectPath");
            valuelist.append("default");
            keylist.append("defaultImagePath");
            valuelist.append("default");
            keylist.append("keepScreenOn");
            valuelist.append("true");
            keylist.append("clearFilterOnClose");
            valuelist.append("true");
            keylist.append("exactMatch");
            valuelist.append("false");
            keylist.append("caseSensitive");
            valuelist.append("false");
            keylist.append("fontSize");
            valuelist.append(QString::number(defaultFont.pixelSize() < 0 ? defaultFont.pointSize() : defaultFont.pixelSize()));
        }
        for(int i = 0;i < keylist.size();i++)
        {
            if(!settings->allKeys().contains(keylist.at(i)))
            {
                settings->setValue(keylist.at(i),valuelist.at(i));
                if(exists)
                {
                    emit error("在文件"+settingpath+"中无法找到键"+keylist.at(i));
                }
            }
        }
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    settings->setIniCodec(QTextCodec::codecForName("utf-8"));
#endif
    settings->sync();
    }
    else
    {
        emit error("初始化配置文件时出错:\nQSettings::status() != QSettings::NoError");
    }
}
void Widget::readSettings()
{
    if(!isBool(settings->value("loadGeometry").toString()))
    {
        settings->setValue("loadGeometry","false");
    }
    if(settings->value("loadGeometry").toString() == "true")
    {
        if(settings->value("width").toInt() == -1 && settings->value("height") == -1)
        {
            this->showMaximized();
        }
        else if(settings->value("width").toInt() > 0 && settings->value("height").toInt() > 0)
        {
            this->move(settings->value("x").toInt(),settings->value("y").toInt());
            this->resize(settings->value("width").toInt(),settings->value("height").toInt());
        }
    }

    if(!isBool(settings->value("staysOnTop").toString()))
        settings->setValue("staysOnTop","false");
    if(toBool(settings->value("staysOnTop").toString()))
    {
        staysOnTop(this);
    }

    if(!QList<QString>({"system","light","dark"}).contains(settings->value("appTheme").toString()))
    {
        settings->setValue("appTheme","system");
    }

    if(!isBool(settings->value("showConsoleWindow").toString()))
        settings->setValue("showConsoleWindow","false");

    if(!isBool(settings->value("writeMessageToLog").toString()))
        settings->setValue("writeMessageToLog","false");

    if(!isBool(settings->value("useMessageContext").toString()))
        settings->setValue("useMessageContext","false");

    if(!isBool(settings->value("showMessageToast").toString()))
        settings->setValue("showMessageToast","true");

    if(!isBool(settings->value("requestAdminOrRoot").toString()))
        settings->setValue("requestAdminOrRoot","false");
    if(settings->value("requestAdminOrRoot").toString() == "true")
    {
#ifdef Q_OS_ANDROID
        if(!hasFilePermission("/system/build.prop",QIODevice::ReadOnly))
            QProcess::execute("su");
#else
#ifdef Q_OS_WIN
        //qtcreator.exe
        bool env_ok = true;
        if(QFile::exists("Makefile") && QList<QString>({"debug","release"}).contains(QDir(qApp->applicationDirPath()).dirName()))
            env_ok = false;
#if QT_VERSION_MAJOR == 5
        if(env_ok && !QFile::exists("Qt5Core.dll"))
            env_ok = false;
#endif
#if QT_VERSION_MAJOR == 6
        if(env_ok && !QFile::exists("Qt6Core.dll"))
            env_ok = false;
#endif
        if(!env_ok && !Windows::isAdmin())
        {
            QMessageBox dlg = QMessageBox(QMessageBox::Warning,"警告","当前环境可能存在异常，仍然尝试以管理员权限启动？",QMessageBox::NoButton);
            dlg.addButton("确定", QMessageBox::AcceptRole);
            dlg.setDefaultButton(dlg.addButton("取消",QMessageBox::RejectRole));
            auto r = dlg.exec();
            if (r == QMessageBox::AcceptRole)
            {
                env_ok = true;
            }
        }
        if(env_ok && !Windows::isAdmin())
        {
            if(Windows::runAsAdmin(qApp->applicationFilePath()))
            {
                QApplication::closeAllWindows();
                QApplication::exit();
                Windows::killExecute(QFileInfo(qApp->applicationFilePath()).fileName());
            }
        }
#endif
#endif
    }

    if(!isBool(settings->value("keepScreenOn").toString()))
        settings->setValue("keepScreenOn","true");
    Android::setKeepScreenOn(settings->value("keepScreenOn").toBool());

    exactbutton->setChecked(settings->value("exactMatch").toString() == "true");
    casebutton->setChecked(settings->value("caseSensitive").toString() == "true");

    QFont f = qApp->font();
    int size = settings->value("fontSize").toInt();
    if(defaultFont.pixelSize() < 0)
        f.setPointSize(size);
    else
        f.setPixelSize(size);
    qApp->setFont(f);

    settings->sync();
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    defaultFont = qApp->font();
    QObject::connect(this,QOverload<QtMsgType,const QMessageLogContext&,const QString&>::of(&Widget::qtMessageUpdated),[=](QtMsgType type, const QMessageLogContext& context, const QString& msg){
        QString text = toString(type);
        QString fileName = QFileInfo(QString(context.file)).fileName();
        QString functionName = QString(context.function);
        functionName.replace(" __cdecl "," ");
        QString line = QString::number(context.line);

        if(settings->value("useMessageContext").toString() == "true")
        {
            text = text + " at ";
            text = text + "File(" + fileName + ") ";
            text = text + "Function(" + functionName + ") ";
            text = text + "Line(" + line + ")";
            text = text + ":\n" + msg;
        }
        else
        {
            text = text + ":" + msg;
        }
        qtMsgList.append(text);
        if(settings->value("writeMessageToLog").toString() == "true")
        {
            writetextfileappend(text+"\n\n",datapath+"/log.txt");
        }
        if(defaultMessageHandler)
        {
            defaultMessageHandler(type,context,text);
        }
    #ifdef Q_OS_ANDROID
        if(settings->value("showMessageToast").toString() == "true")
            Android::showNativeToast(msg);
    #endif
    });
    defaultMessageHandler = qInstallMessageHandler((QtMessageHandler)customMessageHandler);
    QObject::connect(this,QOverload<QString>::of(&Widget::error),[=](QString message){
        QMessageBox::critical(nullptr,"错误",message,"确定");
        qWarning() << message;
    });
#ifndef Q_OS_ANDROID
    datapath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/"+QApplication::applicationName();
#else
    datapath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
#endif
    QFile::remove(datapath+"/log.txt");
    this->initSettings();

    this->setWindowTitle("组织信息管理系统");
    this->setAcceptDrops(true);
#ifndef Q_Device_Desktop
    this->resize(screensize());
#else
    this->resize(this->size());
#endif

    welcomewidget = new QWidget(this);
    mainwidget = new QWidget(this);
    settingwidget = new SettingWidget(this);
    welcomebutton = new QPushButton(this);
    mainbutton = new QPushButton(this);
    settingbutton = new QPushButton(this);
    fullscreenbutton = new QPushButton(this);
    openbutton = new QPushButton(welcomewidget);
    newbutton = new QPushButton(welcomewidget);
    closebutton = new QPushButton(welcomewidget);
    typebutton = new QPushButton(mainwidget);
    filelist = new SettingWidget(welcomewidget);
    showglobalbutton = new QPushButton(mainwidget);
    showpersonbutton = new QPushButton(mainwidget);
    closeprojectbutton = new QPushButton(mainwidget);
    infotable = new QTableWidget(mainwidget);
    filteredit = new QLineEdit(mainwidget);
    casebutton = new QRadioButton(mainwidget);
    exactbutton = new QRadioButton(mainwidget);
    autochangebutton = new QPushButton(mainwidget);
    outputbutton = new QPushButton(mainwidget);
    minimizebutton = new QPushButton(welcomewidget);

    welcomebutton->resize(50,50);
    mainbutton->resize(welcomebutton->size());
    settingbutton->resize(welcomebutton->size());
    fullscreenbutton->resize(welcomebutton->size());
    fullscreenbutton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    fullscreenbutton->setIconSize(fullscreenbutton->size()/2);
    openbutton->resize(80,50);
    newbutton->resize(openbutton->size());
    typebutton->resize(openbutton->size());
    closebutton->resize(newbutton->height(),newbutton->height());
    closebutton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    closebutton->setIconSize(closebutton->size()/2);
    minimizebutton->resize(closebutton->size());
    minimizebutton->setStyleSheet(closebutton->styleSheet());
    minimizebutton->setIconSize(closebutton->iconSize());
    showglobalbutton->resize(openbutton->size());
    showpersonbutton->resize(openbutton->size());
    closeprojectbutton->resize(openbutton->size());
    welcomebutton->setText("欢迎");
    mainbutton->setText("编辑");
    settingbutton->setText("设置");
    openbutton->setText("打开");
    newbutton->setText("新建");
    typebutton->setText("编辑类型");
    showglobalbutton->setText("组织信息");
    showpersonbutton->setText("个人信息");
    closeprojectbutton->setText("关闭项目");
    exactbutton->setText("完全匹配");
    casebutton->setText("区分大小写");
    filteredit->setPlaceholderText("查找");
    autochangebutton->setText("批量管理");
    outputbutton->setText("导出表格");
    filteredit->addAction(QIcon(":/icon/search.png"),QLineEdit::LeadingPosition);
    filteredit->setClearButtonEnabled(true);
    exactbutton->setAutoExclusive(false);
    casebutton->setAutoExclusive(casebutton->autoExclusive());
    infotable->horizontalHeader()->setVisible(false);
    infotable->verticalHeader()->setVisible(false);
    infotable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QScroller::grabGesture(infotable->viewport(),QScroller::TouchGesture);

    settingwidget->addItem("clearFilterOnClose","关闭项目时重置过滤器",SettingWidget::SwitchButton,QVariant(),(settings->value("clearFilterOnClose").toString() == "true"));
    settingwidget->addItem("sep0"," ",SettingWidget::Empty);

    settingwidget->addItem("appTheme","应用主题",SettingWidget::ComboBox,QVariant::fromValue(QList<QString>({"系统","浅色","深色"})));
    auto type = this->getApplicationTheme();
    if(type == System) settingwidget->comboBox(0)->setCurrentIndex(0);
    else if(type == Light) settingwidget->comboBox(0)->setCurrentIndex(1);
    else if(type == Dark) settingwidget->comboBox(0)->setCurrentIndex(2);
    settingwidget->addItem("appFileDialog","文件对话框",SettingWidget::ComboBox,QVariant::fromValue(QList<QString>({"系统","自写"})));
    if(this->getApplicationFileDialogType() == QtDialog)
        settingwidget->comboBox(1)->setCurrentIndex(0);
    else
        settingwidget->comboBox(1)->setCurrentIndex(1);
    settingwidget->addItem("loadGeometry","保存窗口位置",SettingWidget::SwitchButton,QVariant(),(settings->value("loadGeometry").toString() == "true"));
    settingwidget->addItem("fontSize","字体大小",SettingWidget::SpinBox,QVariant(),settings->value("fontSize").toInt());
    settingwidget->addItem("staysOnTop","置顶窗口",SettingWidget::SwitchButton,QVariant(),(settings->value("staysOnTop").toString() == "true"));
    settingwidget->addItem("useSplashScreen","开屏动画",SettingWidget::SwitchButton,QVariant(),(settings->value("useSplashScreen").toString() == "true"));
    QString name = "启动时提权";
#if defined(Q_OS_WIN) || defined(Q_OS_ANDROID)
#ifdef Q_OS_ANDROID
    if(!Android::isRootedDevice())
        name = name + "(" + "非Root设备不可用" + ")";
#endif
#else
    name = name + "(" + "当前平台不受支持" + ")";
#endif
    settingwidget->addItem("requestAdminOrRoot",name,SettingWidget::SwitchButton,QVariant(),(settings->value("requestAdminOrRoot").toString() == "true"));
    settingwidget->addItem("showConsoleWindow","显示命令行窗口(仅Windows)",SettingWidget::SwitchButton,QVariant(),(settings->value("showConsoleWindow").toString() == "true"));
    settingwidget->addItem("writeMessageToLog","将调试信息写入日志文件",SettingWidget::SwitchButton,QVariant(),(settings->value("writeMessageToLog").toString() == "true"));
    settingwidget->addItem("useMessageContext","在调试信息中附加代码位置",SettingWidget::SwitchButton,QVariant(),(settings->value("useMessageContext").toString() == "true"));
    settingwidget->addItem("showMessageToast","以Toast显示调试信息(仅Android)",SettingWidget::SwitchButton,QVariant(),(settings->value("showMessageToast").toString() == "true"));
    settingwidget->addItem("keepScreenOn","在前台时阻止屏幕休眠(仅Android)",SettingWidget::SwitchButton,QVariant(),(settings->value("keepScreenOn").toString() == "true"));
    settingwidget->addItem("runCommand","执行命令",SettingWidget::Empty);
    settingwidget->addItem("showMessage","查看调试信息",SettingWidget::Empty);
    settingwidget->addItem("programmer",toLinkedString("Soviet-Ball","https://github.com/Soviet-Ball/")+"制作",SettingWidget::Empty,QVariant(),QVariant(),QIcon(":/icon/face.png"));
    settingwidget->addItem("application",qApp->applicationName()+" v"+qApp->applicationVersion(),SettingWidget::PushButton,"Github",QVariant(),QIcon(QPixmap::fromImage(getApplicationIcon())));

#ifdef Q_Device_Desktop
    closebutton->hide();
    minimizebutton->hide();
#endif
    mainwidget->hide();
    settingwidget->hide();
    mainbutton->setEnabled(false);

    if(Windows::isAdmin() && this->acceptDrops())
    {
        Windows::setUACAcceptNativeDrops(this);
    }
#ifdef Q_OS_ANDROID
    if(!Android::isQtDefaultActivity())
    {
        bool ok = Android::registerNativeMethod("onConfigurationChanged_native","(Landroid/content/res/Configuration;)V",(void*)androidConfigurationChanged_native);
        if(!ok)
        {
            emit error("fail to register native method");
        }
    }
#endif

    QObject::connect(this,QOverload<>::of(&Widget::androidConfigurationChanged),[=](){
        if(isSystemDarkMode() != currentThemeisDark)
        {
            this->systemThemeChanged();
        }
    });
    QObject::connect(this,QOverload<>::of(&Widget::systemThemeChanged),[=](){
        //process theme changed
        ThemeType type = this->getApplicationTheme();
        bool mode = isSystemDarkMode();
        QString icontype;
        if(type == Light)
        {
            icontype = "black";
            setApplicationDarkMode(false,this);
        }
        else if(type == Dark)
        {
            icontype = "white";
            setApplicationDarkMode(true,this);
        }
        else
        {
            icontype = mode ? "white" : "black";
            setApplicationDarkMode(mode,this);
        }
        currentThemeisDark = mode;
        fullscreenbutton->setIcon(QIcon(":/icon/fullscreen_"+icontype+".png"));
        closebutton->setIcon(QIcon(":/icon/close_"+icontype+".png"));
        minimizebutton->setIcon(QIcon(":/icon/minimize_"+icontype+".png"));
    });
    QObject::connect(welcomebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        welcomewidget->show();
        mainwidget->hide();
        settingwidget->hide();
        this->update();
    });
    QObject::connect(mainbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        mainwidget->show();
        welcomewidget->hide();
        settingwidget->hide();
        this->update();
    });
    QObject::connect(settingbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        settingwidget->show();
        mainwidget->hide();
        welcomewidget->hide();
        this->update();
    });
    QObject::connect(minimizebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
#ifndef Q_OS_ANDROID
        this->showMinimized();
#else
        Android::moveTaskToBack();
#endif
    });
    QObject::connect(closebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        settings->setValue("x",QString::number(this->x()));
        settings->setValue("y",QString::number(this->y()));
        if(this->isMaximized() || this->isFullScreen())
        {
            settings->setValue("width",QString::number(-1));
            settings->setValue("height",QString::number(-1));
        }
        else
        {
            settings->setValue("width",QString::number(this->width()));
            settings->setValue("height",QString::number(this->height()));
        }
        this->closeCurrentProject();
        settings->sync();
        QApplication::exit();
    });
    QObject::connect(typebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        this->showTypeManager();
    });
    QObject::connect(newbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
#ifdef Q_OS_ANDROID
        if(!Android::hasStroagePermission())
        {
            int ret = OkCancelBox(this,QMessageBox::NoIcon,"","若要正常使用本程序，需要授予文件的访问权限，否则部分功能无法正常使用","现在不要","请求权限");
            if(ret == 2 || ret == 0)
            {
                Android::requestStroagePermission();
            }
        }
#endif
        this->createProject();
    });
    QObject::connect(openbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
#ifdef Q_OS_ANDROID
        if(!Android::hasStroagePermission())
        {
            int ret = OkCancelBox(this,QMessageBox::NoIcon,"","若要正常使用本程序，需要授予文件的访问权限，否则部分功能无法正常使用","现在不要","请求权限");
            if(ret == 2 || ret == 0)
            {
                Android::requestStroagePermission();
            }
        }
#endif
        this->openProject();
    });
    QObject::connect(showglobalbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        this->showEditDialog(Global);
    });
    QObject::connect(showpersonbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        auto item = infotable->item(infotable->currentRow(),0);
        if(item != nullptr)
            this->showEditDialog(Personal,item->text().toInt());
        else
            this->showEditDialog(Personal);
    });
    QObject::connect(closeprojectbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        this->closeCurrentProject();
    });
    QObject::connect(fullscreenbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        if(this->isFullScreen())
        {
#ifdef Q_Device_Desktop
            closebutton->hide();
            minimizebutton->hide();
#endif
            if(isMaximizedBeforeFullScreen)
                this->showMaximized();
            else
                this->showNormal();
        }
        else
        {
#ifdef Q_Device_Desktop
            closebutton->show();
            minimizebutton->show();
#endif
            isMaximizedBeforeFullScreen = this->isMaximized();
            this->showFullScreen();
        }
    });
    QObject::connect(filelist,QOverload<int,QString>::of(&SettingWidget::itemClicked),[=](int index,QString key){
        this->openProject(key);
    });
    QObject::connect(filelist,QOverload<int,QString,int,QString>::of(&SettingWidget::comboBoxChanged),[=](int index,QString key,int currentIndex,QString currentText){
        if(currentIndex == 0)
            return;
        else if(currentIndex == 1)
            filelist->itemClicked(index,key);
        else if(currentIndex == 2)
        {
#ifdef Q_OS_ANDROID
            Android::shareFile(key);
#else
            openSystemExplorer(key);
#endif
        }
        else if(currentIndex == 3 || currentIndex == 4)
        {
            QStringList list = settings->value("filelist").toStringList();
            int i = list.indexOf(key);
            if(i >= 0)
                list.removeAt(i);
            if(currentIndex == 4)
            {
                QMessageBox dlg = QMessageBox(QMessageBox::Warning,"警告","是否删除文件 "+key+" ？",QMessageBox::NoButton);
                dlg.addButton("确定", QMessageBox::AcceptRole);
                dlg.setDefaultButton(dlg.addButton("取消",QMessageBox::RejectRole));
                auto r = dlg.exec();
                if (r == QMessageBox::AcceptRole)
                {
                    if(!QFile::remove(key))
                    {
                        emit error("移除文件 "+key+" 失败");
                    }
                    if(project != nullptr && project->fileName() == key)
                    {
                        this->closeCurrentProject();
                    }
                    settings->setValue("filelist",list);
                    settings->sync();
                    this->loadFileList();
                }
            }
            else
            {
                settings->setValue("filelist",list);
                settings->sync();
                this->loadFileList();
            }
        }
        filelist->comboBox(index)->setCurrentIndex(0);
    });
    QObject::connect(infotable,QOverload<int,int>::of(&QTableWidget::cellClicked),[=](int y,int x){
#ifdef Q_Device_Mobile
        this->infoTableClicked(y,x);
#endif
    });
    QObject::connect(infotable,QOverload<int,int>::of(&QTableWidget::cellDoubleClicked),[=](int y,int x){
#ifdef Q_Device_Desktop
        this->infoTableClicked(y,x);
#endif
    });
    QObject::connect(settingwidget,QOverload<int,QString,int,QString>::of(&SettingWidget::comboBoxChanged),[=](int index,QString key,int currentIndex,QString currentText){
        if(key == "appTheme")
        {
            if(currentIndex == 0)
                settings->setValue(key,"system");
            else if(currentIndex == 1)
                settings->setValue(key,"light");
            else if(currentIndex == 2)
                settings->setValue(key,"dark");
            emit systemThemeChanged();
        }
        else if(key == "appFileDialog")
        {
            if(currentIndex == 0)
                settings->setValue(key,"qfiledialog");
            else
                settings->setValue(key,"myfiledialog");
        }
        settings->sync();
    });
    QObject::connect(settingwidget,QOverload<int,QString,bool>::of(&SettingWidget::switchButtonClicked),[=](int index,QString key,bool value){
        settings->setValue(key,value);
        if(key == "staysOnTop")
        {
            if(value)
                staysOnTop(this);
            else
                staysNotOnTop(this);
        }
        else if(key == "keepScreenOn")
        {
            Android::setKeepScreenOn(value);
        }
        settings->sync();
    });
    QObject::connect(settingwidget,QOverload<int,QString>::of(&SettingWidget::itemClicked),[=](int index,QString key){
        if(key == "showMessage")
        {
            showTextDialog("QtMessageList:\n"+qtMsgList.join(",\n")+"\n\n"+GetDebugInfo(this),nullptr,"调试信息");
            this->show();
            settingwidget->show();
            this->update();
            settingwidget->update();
        }
        else if(key == "runCommand")
        {
            QInputDialog* dlg = new QInputDialog();
            dlg->setWindowTitle(" ");
            dlg->setLabelText("输入命令");
            dlg->setOkButtonText("确定");
            dlg->setCancelButtonText("取消");
            if(dlg->exec() != QDialog::Accepted)
                return;
            QString s = dlg->textValue();
            if(s.isEmpty())
                return;
            showTextDialog(runCommand(s),nullptr,"运行结果");
        }
        else if(settingwidget->mode(index) == SettingWidget::SwitchButton)
        {
            auto button = settingwidget->switchbutton(index);
            button->setChecked(!button->isChecked());
        }
    });
    QObject::connect(settingwidget,QOverload<int,QString>::of(&SettingWidget::pushButtonClicked),[=](int index,QString key){
        if(key == "application")
        {
            QString link;
            link = "https://github.com/Soviet-Ball/"+qApp->applicationName();
            if(!link.isEmpty())
            {
                QDesktopServices::openUrl(QUrl(link));
            }
        }
    });
    QObject::connect(settingwidget,QOverload<int,QString,int>::of(&SettingWidget::spinboxValueChanged),[=](int index,QString key,int currentValue){
        if(key == "fontSize")
        {
            QFont f = qApp->font();
            if(defaultFont.pixelSize() < 0)
                f.setPointSize(currentValue);
            else
                f.setPixelSize(currentValue);
            qApp->setFont(f);
            settings->setValue(key,currentValue);
        }
    });
    QObject::connect(filteredit,QOverload<const QString&>::of(&QLineEdit::textChanged),[=](){
        QString text = filteredit->text();
        int y = infotable->currentRow();
        int x = infotable->currentColumn();
        if(!text.isEmpty() && y != -1 && x != -1 && x != 0 && infotable->selectedRanges().count() == 1 && infotable->selectedRanges().first().leftColumn() == infotable->selectedRanges().first().rightColumn())
        {
            QString name = infotable->item(0,x)->text();
            int index = this->getTypeIndexFromName(name);
            if(index != -1)
            {
                this->removeProjectFilter();
                project->setValue("Filter/key",project->value("Types/type"+QString::number(index)+"/key"));
                project->setValue("Filter/text",text);
                this->loadInfoTable();
                infotable->setCurrentCell(y,x);
            }
        }
        else if(text.isEmpty())
        {
            this->removeProjectFilter();
            this->loadInfoTable();
            infotable->setCurrentCell(y,x);
        }
    });
    QObject::connect(exactbutton,QOverload<bool>::of(&QRadioButton::clicked),[=](){
        if(!filteredit->text().isEmpty())
            filteredit->textChanged(filteredit->text());
        settings->setValue("exactMatch",exactbutton->isChecked());
    });
    QObject::connect(casebutton,QOverload<bool>::of(&QRadioButton::clicked),[=](){
        if(!filteredit->text().isEmpty())
            filteredit->textChanged(filteredit->text());
        settings->setValue("caseSensitive",casebutton->isChecked());
    });
    QObject::connect(autochangebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        this->showAutoChangeDialog();
    });
    QObject::connect(outputbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        if(project == nullptr) return;

        QString dir;
#ifndef Q_OS_ANDROID
        dir = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#else
        if(hasPathPermission("/sdcard/Download",QIODevice::WriteOnly))
            dir = "/sdcard/Download";
        else
            dir = datapath + "/" + "output" + "/";
#endif
        if(!QFileInfo(dir).isDir())
            QDir().mkpath(dir);

        if(hasPathPermission(dir))
        {
            QString suffix = "xlsx";
            QString name = project->value("Project/name").toString();
            QString filePath = dir+"/"+name+"."+suffix;
            if(QFileInfo(filePath).isFile())
            {
                int i = 1;
                while(QFileInfo(dir+"/"+name+"_"+QString::number(i)+"."+suffix).isFile())
                    i++;
                filePath = dir+"/"+name+"_"+QString::number(i)+"."+suffix;
            }

            QXlsx::Document document;
            QXlsx::Format format;
            format.setTextWrap(true);
            format.setFontColor(Qt::black);
            format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
            for(int row = 0; row < infotable->rowCount(); row++)
            {
                for(int col = 0; col < infotable->colorCount(); col++)
                {
                    auto item = infotable->item(row,col);
                    if(item != nullptr)
                    {
                        document.write(row+1,col+1,item->text(),format);
                    }
                }
            }
            if(document.saveAs(filePath))
            {
#ifndef Q_OS_ANDROID
                openSystemExplorer(filePath);
#else
                Android::showNativeToast("表格已保存到"+filePath);
                Android::shareFile(filePath);
#endif
            }
            else
            {
                emit error("保存表格失败");
            }
        }
    });
    this->installEventFilter(this);
    this->loadFileList();
    this->refreshUI();
    QTimer::singleShot(0,[=](){
        emit systemThemeChanged();
        this->readSettings();
        this->processArguments();
    });
}
Widget::~Widget()
{
}
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
bool Widget::nativeEvent(const QByteArray &eventType, void *message,qintptr* result) {
#else
bool Widget::nativeEvent(const QByteArray &eventType, void *message,long* result) {
#endif
#ifdef Q_OS_WIN
    MSG* msg = static_cast<MSG*>(message);
    if(msg->message == 563 && Windows::isAdmin())
    {
         Windows::processNativeDropEvent(msg);
    }
#if (QT_VERSION < QT_VERSION_CHECK(6,5,0))
    if(msg->message == 15)
    {
        if(isSystemDarkMode() != currentThemeisDark)
        {
            this->systemThemeChanged();
        }
    }
#endif
#endif
    return false;
}
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(static_cast<QWidget*>(watched) != nullptr)
    {
        if(event->type() == QEvent::DragEnter)
        {
            QDragEnterEvent* dragEnterEvent = static_cast<QDragEnterEvent*>(event);
            dragEnterEvent->accept();
        }
        else if(event->type() == QEvent::Drop)
        {
            QDropEvent* dropEvent = static_cast<QDropEvent*>(event);
            if(watched == this && !dropEvent->mimeData()->urls().isEmpty() && dropEvent->mimeData()->hasFormat("text/uri-list"))
            {
                for(auto url : dropEvent->mimeData()->urls())
                {
                    QString s = url.toLocalFile();
                    if(QFileInfo(s).isFile() && hasFilePermission(s,QIODevice::ReadWrite) && (s.endsWith("ini") || s.endsWith("INI")))
                    {
                        this->openProject(s);
                        break;
                    }
                }
            }
            dropEvent->accept();
        }
    }
    if(watched == this)
    {
        if(event->type() == QEvent::ThemeChange)
        {
            emit systemThemeChanged();
        }
        else if(event->type() == QEvent::KeyPress)
        {
            //process key press event
            QKeyEvent* e = static_cast<QKeyEvent*>(event);
            if(e->key() == Qt::Key_Back || e->key() == Qt::Key_Escape)
            {
                if(filteredit->hasFocus())
                {
                    filteredit->setText(QString());
                    filteredit->clearFocus();
                    QGuiApplication::inputMethod()->hide();
                }
                else if(!mainwidget->isHidden() && infotable != nullptr && project != nullptr && !infotable->selectedRanges().isEmpty())
                {
                    infotable->clearSelection();
                    infotable->clearFocus();
                    infotable->setCurrentCell(-1,-1);
                    this->setFocus();
                }
                else if(this->isFullScreen())
                {
                    fullscreenbutton->clicked();
                }
                else if(welcomewidget->isHidden())
                {
                    welcomebutton->clicked();
                }
                else
                {
#ifndef Q_OS_ANDROID
                    closebutton->clicked();
#else
                    if(e->key() == Qt::Key_Escape)
                        closebutton->clicked();
                    else
                    {
                        if(!back_press_timelist.isEmpty()
                           && Abs(QTime::currentTime().msecsTo(back_press_timelist.last())) <= back_close_interval)
                        {
                            closebutton->clicked();
                        }
                        else
                        {
                            back_press_timelist.append(QTime::currentTime());
                            Android::showNativeToast("再按一次退出");
                        }
                    }
#endif
                }
                return true;
            }
            else if(e->key() == Qt::Key_F && e->modifiers() == Qt::ControlModifier)
            {
                if(infotable != nullptr && !mainwidget->isHidden() && project != nullptr)
                {
                    int row = infotable->currentRow();
                    int col = infotable->currentColumn();
                    if(row != -1 && col != -1 && col != 0 && infotable->selectedRanges().count() == 1
                    && infotable->selectedRanges().first().leftColumn() == infotable->selectedRanges().first().rightColumn()
                    && infotable->selectedRanges().first().topRow() == infotable->selectedRanges().first().bottomRow())
                    {
                        QString name = infotable->item(0,col)->text();
                        int index = this->getTypeIndexFromName(name);
                        if(index != -1)
                        {
                            QString type = project->value("Types/type"+QString::number(index)+"/type").toString();
                            if(row == 0 && QList<QString>({"String","Bool"}).contains(type))
                                this->infoTableClicked(row,col);
                            else if(row == 0 && type == "Int")
                            {
                                filteredit->setFocus();
                                QGuiApplication::inputMethod()->show();
                            }
                            else if(row != 0 && QList<QString>({"Int","String","Bool"}).contains(type))
                            {
                                auto item = infotable->item(row,col);
                                if(item != nullptr)
                                {
                                    filteredit->setFocus();
                                    QGuiApplication::inputMethod()->show();
                                    filteredit->setText(item->text());
                                }
                            }
                        }
                    }
                }
            }
            else if(e->key() == Qt::Key_S && e->modifiers() == Qt::ControlModifier)
            {
                outputbutton->clicked();
            }
        }
        else if(event->type() == QEvent::KeyRelease)
        {
            //process key release event
            QKeyEvent* e = static_cast<QKeyEvent*>(event);
        }
        else if(event->type() == QEvent::Close)
        {
            closebutton->clicked();
        }
        else if(event->type() == QEvent::Resize)
        {
            this->refreshUI();
        }
    }
    else if(qobject_cast<QSlider*>(watched) != nullptr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QSlider* s = qobject_cast<QSlider*>(watched);
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(s->isEnabled() && mouseEvent->button() != Qt::RightButton && mouseEvent->button() != Qt::MiddleButton)
            {
                s->setValue(s->minimum()+float(mouseEvent->x())/float(s->width())*float(s->maximum()-s->minimum()));
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}
Widget* Widget::getCurrentWindow()
{
    QList<QWidget*> list;
    QList<QWidget*> widgets = qApp->topLevelWidgets();
    for(QWidget* widget : widgets)
    {
        if(QString(widget->metaObject()->className()) == "Widget" && !list.contains(widget))
        {
            list << widget;
        }
    }

    if(list.count() == 1)
    {
        return (Widget*)list.at(0);
    }
    return nullptr;
}
Widget::ThemeType Widget::getApplicationTheme()
{
    if(!QList<QString>({"system","light","dark"}).contains(settings->value("appTheme").toString()))
    {
        settings->setValue("appTheme","system");
    }
    if(settings->value("appTheme").toString() == "light")
        return Light;
    else if(settings->value("appTheme").toString() == "dark")
        return Dark;
    else
        return System;
}
Widget::FileDialogType Widget::getApplicationFileDialogType()
{
    if(!QList<QString>({"qfiledialog","myfiledialog"}).contains(settings->value("appFileDialog").toString()))
    {
        settings->setValue("appFileDialog","qfiledialog");
    }
    if(settings->value("appFileDialog").toString() == "myfiledialog")
        return MyDialog;
    else
        return QtDialog;
}
void Widget::refreshUI()
{
    welcomebutton->move(0,0);
    mainbutton->move(welcomebutton->x(),welcomebutton->y()+welcomebutton->height());
    settingbutton->move(welcomebutton->x(),mainbutton->y()+mainbutton->height());
    fullscreenbutton->move(welcomebutton->x(),this->height()-fullscreenbutton->height());
    welcomewidget->resize(this->width()-welcomebutton->x()-welcomebutton->width(),this->height());
    mainwidget->resize(welcomewidget->size());
    settingwidget->resize(welcomewidget->size());
    welcomewidget->move(welcomebutton->x()+welcomebutton->width(),welcomebutton->y());
    mainwidget->move(welcomewidget->pos());
    settingwidget->move(welcomewidget->pos());

    int h = openbutton->height();
    QList<QPushButton*> buttonlist1 = {newbutton,openbutton,typebutton,closeprojectbutton,showpersonbutton,showglobalbutton,autochangebutton,outputbutton};
    for(auto button : buttonlist1)
        button->resize(mainwidget->width()/9.0,h);

    openbutton->move(5,5);
    newbutton->move(2*openbutton->x()+openbutton->width(),openbutton->y());
    typebutton->move(openbutton->pos());
    showglobalbutton->move(2*typebutton->x()+typebutton->width(),typebutton->y());
    showpersonbutton->move(showglobalbutton->x()+showglobalbutton->width()+typebutton->x(),typebutton->y());
    outputbutton->move(showpersonbutton->x()+closeprojectbutton->width()+typebutton->x(),typebutton->y());
    autochangebutton->move(outputbutton->x()+outputbutton->width()+typebutton->x(),typebutton->y());
    closeprojectbutton->move(autochangebutton->x()+autochangebutton->width()+typebutton->x(),typebutton->y());
    filelist->move(openbutton->x(),2*openbutton->y()+openbutton->height());
    filelist->resize(welcomewidget->width()-2*filelist->x(),welcomewidget->height()-filelist->y()-(filelist->y()-openbutton->y()-openbutton->height()));
    closebutton->move(filelist->x()+filelist->width()-closebutton->width(),openbutton->y());
    minimizebutton->move(closebutton->x()-minimizebutton->width(),closebutton->y());

    infotable->resize(mainwidget->width()-2*typebutton->x(),mainwidget->height()-3*typebutton->y()-typebutton->height());
    infotable->move(typebutton->x(),typebutton->height()+2*typebutton->y());

    filteredit->resize(mainwidget->width()-closeprojectbutton->x()-closeprojectbutton->width()-2*typebutton->x(),typebutton->height()/2);
    casebutton->resize(filteredit->width()/2,filteredit->height());
    exactbutton->resize(casebutton->size());
    filteredit->move(mainwidget->width()-typebutton->x()-filteredit->width(),typebutton->y());
    casebutton->move(filteredit->x(),filteredit->y()+filteredit->height());
    exactbutton->move(casebutton->x()+casebutton->width(),casebutton->y());
}
void Widget::showTypeManager()
{
    QDialog* dlg = new QDialog(this);
    QPushButton* newtypebutton = new QPushButton(dlg);
    QPushButton* removetypebutton = new QPushButton(dlg);
    QPushButton* moveupbutton = new QPushButton(dlg);
    QPushButton* movedownbutton = new QPushButton(dlg);
    QPushButton* commitbutton = new QPushButton(dlg);
    QPushButton* cancelbutton = new QPushButton(dlg);
    QTableWidget* table = new QTableWidget(dlg);
    dlg->setWindowTitle("数据类型管理器");
    newtypebutton->setText("新建");
    removetypebutton->setText("移除");
    commitbutton->setText("确定");
    cancelbutton->setText("取消");
    moveupbutton->setText("上移");
    movedownbutton->setText("下移");
    commitbutton->setFocus();
#ifdef Q_Device_Desktop
    dlg->resize(this->size()/2);
#else
    dlg->resize(screensize());
#endif
    table->resizeRowsToContents();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QScroller::grabGesture(table->viewport(),QScroller::TouchGesture);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    newtypebutton->resize(60,40);
    newtypebutton->move(openbutton->pos());
    removetypebutton->resize(newtypebutton->size());
    removetypebutton->move(2*newtypebutton->x()+newtypebutton->width(),newtypebutton->y());
    moveupbutton->resize(newtypebutton->size());
    moveupbutton->move(removetypebutton->x()+removetypebutton->width()+newtypebutton->x(),newtypebutton->y());
    movedownbutton->resize(newtypebutton->size());
    movedownbutton->move(moveupbutton->x()+moveupbutton->width()+newtypebutton->x(),newtypebutton->y());
    cancelbutton->resize(50,30);
    commitbutton->resize(cancelbutton->size());
    cancelbutton->move(dlg->width()-cancelbutton->width()-newtypebutton->x(),dlg->height()-cancelbutton->height()-newtypebutton->y());
    commitbutton->move(cancelbutton->x()-newtypebutton->x()-commitbutton->width(),cancelbutton->y());
    table->move(newtypebutton->x(),2*newtypebutton->y()+newtypebutton->height());
    table->resize(dlg->width()-2*table->x(),commitbutton->y()-table->y()-newtypebutton->y());
    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);
    table->setColumnCount(5);

    int count = 0;
    while(project->contains("Types/type"+QString::number(count)+"/name"))
        count++;
    table->setRowCount(count+1);

    int width = table->viewport()->width()/5;
    for(int y = 0; y < table->rowCount(); y++)
    {
        for(int x = 0; x < table->columnCount(); x++)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            if(y == 0)
            {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                table->setColumnWidth(x,width);
                if(x == 0)
                    item->setText("代码");
                else if(x == 1)
                    item->setText("名称");
                else if(x == 2)
                    item->setText("范围");
                else if(x == 3)
                    item->setText("类型");
                else if(x == 4)
                    item->setText("加密");
            }
            else
            {
                if(x == 0)
                    item->setText(project->value("Types/type"+QString::number(y-1)+"/key").toString());
                else if(x == 1)
                    item->setText(project->value("Types/type"+QString::number(y-1)+"/name").toString());
                else if(x == 2)
                    item->setText(project->value("Types/type"+QString::number(y-1)+"/range").toString() == "personal" ? "个人" : "全局");
                else if(x == 3)
                {
                    QString str = project->value("Types/type"+QString::number(y-1)+"/type").toString();
                    QString type = "字符串";
                    if(str == "Image") type = "图像";
                    else if(str == "Bool") type = "布尔";
                    else if(str == "Int") type = "整数";
                    else if(str == "StringList") type = "字符串列表";
                    item->setText(type);
                }
                else if(x == 4)
                    item->setText(project->value("Types/type"+QString::number(y-1)+"/encryption").toString() == "true" ? "是" : "否");
            }
            table->setItem(y,x,item);
        }
    }

    QObject::connect(newtypebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        QDialog* dialog = new QDialog(dlg);
        SettingWidget* w = new SettingWidget(dialog);
        bool* accept = new bool;
        *accept = false;
        dialog->move(dlg->pos());
        dialog->resize(dlg->size());
        w->resize(dialog->size());
        w->addItem("Key","代码",SettingWidget::LineEdit);
        w->addItem("Name","名称",SettingWidget::LineEdit);
        w->addItem("Range","范围",SettingWidget::ComboBox,QVariant::fromValue(QList<QString>({"个人","全局"})));
        w->addItem("Type","类型",SettingWidget::ComboBox,QVariant::fromValue(QList<QString>({"字符串","字符串列表","整数","布尔","图像"})));
        w->addItem("Encryption","加密",SettingWidget::RadioButton,QVariant(),false,QIcon(),"","","",false);
        w->addItem("Button"," ",SettingWidget::PushButton,"确定");
        QObject::connect(w,QOverload<int,QString>::of(&SettingWidget::pushButtonClicked),[=](){
            QString str1 = w->lineEdit(0)->text();
            QString str2 = w->lineEdit(1)->text();
            bool flag_1 = true;
            bool flag_2 = true;
            if(str1.isEmpty()) flag_1 = false;
            if(str2.isEmpty()) flag_2 = false;
            for(QChar c : str1)
                if(!c.isLower() && !c.isUpper() && !c.isNumber())
                {
                    flag_1 = false;
                    break;
                }
            if(flag_1)
                for(int i = 1; i < table->rowCount(); i++)
                {
                    if(str1 == table->item(i,0)->text())
                    {
                        flag_1 = false;
                        break;
                    }
                }
            if(!flag_1)
            {
                w->lineEdit(0)->setFocus();
                w->lineEdit(0)->selectAll();
                return;
            }
            if(flag_2)
                for(int i = 1; i < table->rowCount(); i++)
                {
                    if(str2 == table->item(i,1)->text())
                    {
                        flag_2 = false;
                        break;
                    }
                }
            if(!flag_2)
            {
                w->lineEdit(1)->setFocus();
                w->lineEdit(1)->selectAll();
                return;
            }
            *accept = true;
            dialog->close();
        });
        dialog->exec();

        if(*accept)
        {
            table->setRowCount(table->rowCount()+1);
            for(int x = 0; x < table->columnCount(); x++)
            {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setTextAlignment(Qt::AlignCenter);
                if(x == 0)
                    item->setText(w->lineEdit(0)->text());
                else if(x == 1)
                    item->setText(w->lineEdit(1)->text());
                else if(x == 2)
                    item->setText(w->comboBox(2)->currentText());
                else if(x == 3)
                    item->setText(w->comboBox(3)->currentText());
                else if(x == 4)
                    item->setText(w->radioButton(4)->isChecked() ? "是" : "否");
                table->setItem(table->rowCount()-1,x,item);
            }
        }
    });
    QObject::connect(removetypebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        QList<int> rows;
        if(!table->selectedRanges().isEmpty())
        {
            for(auto range : table->selectedRanges())
            {
                for(int i = range.topRow(); i <= range.bottomRow(); i++)
                {
                    rows.append(i);
                }
            }
        }
        else
        {
            rows.append(table->currentRow());
        }

        for(int i = rows.count() - 1; i >= 0; i--)
        {
            int row = rows.at(i);
            if(row != 0 && row != -1)
            {
                table->removeRow(row);
            }
        }
    });
    QObject::connect(cancelbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        dlg->close();
    });
    QObject::connect(commitbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        commitbutton->setEnabled(false);
        QProgressBar* bar = new QProgressBar;
        QProgressDialog* pdlg = new QProgressDialog(dlg);
        bar->setRange(0,0);
        bar->setStyleSheet("QProgressBar::chunk{background-color:"+toString(QColor(0,103,192))+";}");
        setCloseButton(pdlg,false);
        pdlg->setCancelButton(nullptr);
        pdlg->setBar(bar);
        pdlg->setLabelText("保存数据类型...");

        QFuture<void> r = QtConcurrent::run([=,&count,&table,&pdlg](){
            for(int i = 1; i < Max(count+1,table->rowCount()); i++)
            {
                if(i < table->rowCount())
                {
                    project->setValue("Types/type"+QString::number(i-1)+"/key",table->item(i,0)->text());
                    project->setValue("Types/type"+QString::number(i-1)+"/name",table->item(i,1)->text());
                    project->setValue("Types/type"+QString::number(i-1)+"/range",table->item(i,2)->text() == "个人" ? "personal" : "global");
                    QString type = "String";
                    QString str = table->item(i,3)->text();
                    if(str == "图像") type = "Image";
                    else if(str == "布尔") type = "Bool";
                    else if(str == "整数") type = "Int";
                    else if(str == "字符串列表") type = "StringList";
                    project->setValue("Types/type"+QString::number(i-1)+"/type",type);
                    project->setValue("Types/type"+QString::number(i-1)+"/encryption",table->item(i,4)->text() == "是" ? "true" : "false");
                }
                else
                {
                    project->remove("Types/type"+QString::number(i-1)+"/key");
                    project->remove("Types/type"+QString::number(i-1)+"/name");
                    project->remove("Types/type"+QString::number(i-1)+"/range");
                    project->remove("Types/type"+QString::number(i-1)+"/type");
                    project->remove("Types/type"+QString::number(i-1)+"/encryption");
                }
            }
            project->sync();
            pdlg->close();
        });
        //r.waitForFinished();
        if(table->rowCount()-1 > 20)
            pdlg->exec();
        else
            r.waitForFinished();
        dlg->close();
    });
    QObject::connect(moveupbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        int row = table->currentRow();
        int c = table->currentColumn();
        if(row >= 0 && row != 0 && row != 1)
        {
            moveRow(table,row,row-1);
            table->setCurrentCell(row-1,c >= 0 ? c : 0);
        }
    });
    QObject::connect(movedownbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        int row = table->currentRow();
        int c = table->currentColumn();
        if(row >= 0 && row != 0 && row != table->rowCount()-1)
        {
            moveRow(table,row,row+1);
            table->setCurrentCell(row+1,c >= 0 ? c : 0);
        }
    });

    fixSize(dlg);
    if(isTopMostWindow(this))
        staysOnTop(dlg);
    dlg->exec();
    this->loadInfoTable();
}
void Widget::createProject()
{
    QDialog* dlg = new QDialog(this);
    QLabel* namelabel = new QLabel(dlg);
    QLabel* pathlabel = new QLabel(dlg);
    QLabel* iconlabel = new QLabel(dlg);
    QLabel* pwlabel = new QLabel(dlg);
    QLabel* rpwlabel = new QLabel(dlg);
    QLineEdit* nameedit = new QLineEdit(dlg);
    QLineEdit* pathedit = new QLineEdit(dlg);
    QLineEdit* iconedit = new QLineEdit(dlg);
    QLineEdit* pwedit = new QLineEdit(dlg);
    QLineEdit* rpwedit = new QLineEdit(dlg);
    QPushButton* commitbutton = new QPushButton(dlg);
    QPushButton* cancelbutton = new QPushButton(dlg);
    QPushButton* pathbutton = new QPushButton(dlg);
    QPushButton* iconbutton = new QPushButton(dlg);
    QRadioButton* defaultbutton = new QRadioButton(dlg);
#ifdef Q_Device_Desktop
    dlg->resize(this->width()/2,this->height()/2 > 250 ? 250 : this->height()/2);
#else
    dlg->resize(screensize());
#endif
    dlg->setWindowTitle("创建新项目");
    namelabel->setText("项目名称");
    pathlabel->setText("项目路径");
    iconlabel->setText("项目图标");
    pwlabel->setText("项目密码");
    rpwlabel->setText("重复密码");
    iconedit->setPlaceholderText("可不添加");
    pwedit->setPlaceholderText("可不填");
    commitbutton->setText("确定");
    cancelbutton->setText("取消");
    pathbutton->setText("浏览");
    iconbutton->setText("浏览");
    defaultbutton->setText("设为默认路径");

    namelabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    pathlabel->setAlignment(namelabel->alignment());
    iconlabel->setAlignment(namelabel->alignment());
    pwlabel->setAlignment(namelabel->alignment());
    rpwlabel->setAlignment(namelabel->alignment());
    pwedit->setEchoMode(QLineEdit::Password);
    rpwedit->setEchoMode(pwedit->echoMode());

    namelabel->move(5,5);
    //namelabel->resize(50,30);
    namelabel->resize(50,(dlg->height()-8*namelabel->y())/7 > 30 ? 30 : (dlg->height()-8*namelabel->y())/7);
    pathlabel->resize(namelabel->size());
    iconlabel->resize(namelabel->size());
    pwlabel->resize(namelabel->size());
    rpwlabel->resize(namelabel->size());
    defaultbutton->resize(dlg->width()-2*namelabel->x(),namelabel->height());
    pathlabel->move(namelabel->x(),2*namelabel->y()+namelabel->height());
    iconlabel->move(namelabel->x(),pathlabel->y()+pathlabel->height()+namelabel->y());
    pwlabel->move(namelabel->x(),iconlabel->y()+iconlabel->height()+namelabel->y());
    rpwlabel->move(namelabel->x(),pwlabel->y()+pwlabel->height()+namelabel->y());
    defaultbutton->move(namelabel->x(),rpwlabel->y()+rpwlabel->height()+namelabel->y());

    nameedit->resize(dlg->width()-3*namelabel->x()-namelabel->width(),namelabel->height());
    pathedit->resize(nameedit->size());
    iconedit->resize(nameedit->size());
    pwedit->resize(nameedit->size());
    rpwedit->resize(nameedit->size());
    nameedit->move(2*namelabel->x()+namelabel->width(),namelabel->y());
    pathedit->move(nameedit->x(),2*namelabel->y()+namelabel->height());
    iconedit->move(nameedit->x(),pathedit->y()+pathedit->height()+nameedit->y());
    pwedit->move(nameedit->x(),iconedit->y()+iconedit->height()+nameedit->y());
    rpwedit->move(nameedit->x(),pwedit->y()+pwedit->height()+nameedit->y());

    iconbutton->resize(iconlabel->height(),iconlabel->height());
    pathbutton->resize(iconbutton->size());
    iconbutton->move(iconedit->x()+iconedit->width()-iconbutton->width(),iconedit->y());
    pathbutton->move(pathedit->x()+pathedit->width()-pathbutton->width(),pathedit->y());
    iconedit->resize(iconedit->width()-iconbutton->width()-iconlabel->x(),iconedit->height());
    pathedit->resize(iconedit->size());

    cancelbutton->resize(namelabel->size());
    commitbutton->resize(cancelbutton->size());
    cancelbutton->move(dlg->width()-cancelbutton->width()-namelabel->x(),dlg->height()-cancelbutton->height()-namelabel->y());
    commitbutton->move(cancelbutton->x()-namelabel->x()-commitbutton->width(),cancelbutton->y());

    QString defpath = settings->value("defaultProjectPath").toString();
    if(QFileInfo(defpath).isDir())
        pathedit->setText(defpath);

    QObject::connect(pathbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        auto type = this->getApplicationFileDialogType();
        QString dir;
        if(QFileInfo(pathedit->text()).isDir()) dir = pathedit->text();
        else if(QFileInfo(defpath).isDir()) dir = defpath;
        else dir = datapath+"/project";
        if(!QFileInfo(dir).isDir()) QDir().mkpath(dir);
        QString path = MyFileDialog::getExistingDirectory(dlg,"选择项目路径",dir,(type == QtDialog),currentThemeisDark);
#ifdef Q_OS_ANDROID
        path = Android::getRealPathFromUri(path);
#endif
        if(!path.isEmpty())
            pathedit->setText(path);
    });
    QObject::connect(iconbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        auto type = this->getApplicationFileDialogType();
        QString dir;
        if(QFileInfo(iconedit->text()).isDir()) dir = iconedit->text();
        else if(QFileInfo(iconedit->text()).isFile()) dir = QFileInfo(iconedit->text()).absolutePath();
        else if(QFileInfo(settings->value("defaultImagePath").toString()).isDir()) dir = settings->value("defaultImagePath").toString();
        else
        {
#ifdef Q_OS_ANDROID
                dir = "/sdcard";
#else
                dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
#endif
        }
        if(!QFileInfo(dir).isDir()) QDir().mkpath(dir);
        QString path = MyFileDialog::getOpenFileName(dlg,"选择项目图标",dir,(type == QtDialog),currentThemeisDark);
#ifdef Q_OS_ANDROID
        path = Android::getRealPathFromUri(path);
#endif
        QPixmap pix;
        pix.loadFromData(readfile(path));
        if(!pix.isNull())
        {
            iconedit->setText(path);
            settings->setValue("defaultImagePath",QFileInfo(path).absolutePath());
        }
        else if(!path.isEmpty())
        {
            QString msg = "加载图片失败";
            emit error(msg);
        }
    });
    QObject::connect(cancelbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        dlg->close();
    });
    QObject::connect(commitbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        pathedit->setText(pathedit->text().replace("\\","/"));
        iconedit->setText(iconedit->text().replace("\\","/"));
        QString path = pathedit->text();
        QString name = nameedit->text();
        QString pwd = pwedit->text();
        if(path.isEmpty() || name.isEmpty())
            return;
        if(pwd != rpwedit->text())
        {
            emit error("密码不一致");
            return;
        }
        for(QChar c : pwd)
            if(!c.isLower() && !c.isUpper() && !c.isNumber())
            {
                emit error("密码只能含有英文字母和数字");
                return;
            }
        if(!QFileInfo(path).isDir() || !QFileInfo(path).isAbsolute())
        {
            emit error("路径 "+path+" 不合法");
            //content://com.android.externalstorage.documents/tree/primary%3ADocuments
            return;
        }
        if(path.endsWith("/") && path != "/" && path != ":/" && !(path.length() == 3 && path.endsWith(":/")))
            path.chop(1);
        QString filePath = path + "/" + name + ".ini";
        if(QFileInfo(filePath).isFile())
        {
            QMessageBox dlg = QMessageBox(QMessageBox::Information,"提示","文件 "+filePath+" 已存在，是否替换？",QMessageBox::NoButton);
            dlg.addButton("确定",QMessageBox::AcceptRole);
            dlg.addButton("取消",QMessageBox::RejectRole);
            auto ret = dlg.exec();
            if(ret == QMessageBox::RejectRole)
                return;
            else
                QFile::remove(filePath);
        }
        if(!hasFilePermission(filePath,QIODevice::ReadWrite))
        {
            emit error("无法访问文件 "+filePath);
            return;
        }
        QSettings* setting = new QSettings(filePath,QSettings::IniFormat,this);
        if(setting->status() != QSettings::NoError)
        {
            emit error("QSettings::status() != QSettings::NoError");
            return;
        }
        setting->setValue("Project/name",name);
        if(defaultbutton->isChecked())
            settings->setValue("defaultProjectPath",path);
        if(!pwd.isEmpty())
        {
            QByteArray byte = qCompress(pwd.toLocal8Bit().toBase64());
            pwd = QString();
            if(!byte.isEmpty())
                setting->setValue("Project/password",byte);
        }
        QPixmap pix;
        if(QFileInfo(iconedit->text()).isFile() && pix.loadFromData(readfile(iconedit->text())))
            setting->setValue("Project/icon",pix);
        setting->sync();
        delete setting;
        dlg->close();
        if(project != nullptr && filePath == project->fileName())
            this->closeCurrentProject();
        this->openProject(filePath,false);
    });

    fixSize(dlg);
    if(isTopMostWindow(this))
        staysOnTop(dlg);
    dlg->exec();
    QGuiApplication::inputMethod()->hide();
}
void Widget::openProject(QString filePath, bool needPassword)
{
    if(filePath.isEmpty())
    {
        QString dir;
        QString defpath = settings->value("defaultProjectPath").toString();
        if(QFileInfo(defpath).isDir()) dir = defpath;
        else dir = datapath+"/project";
        filePath = MyFileDialog::getOpenFileName(this,"打开项目",dir,(this->getApplicationFileDialogType() == QtDialog),currentThemeisDark);
#ifdef Q_OS_ANDROID
        filePath = Android::getRealPathFromUri(filePath);
#endif
    }
    if(filePath.isEmpty())
        return;
    if(!QFileInfo(filePath).isFile())
    {
        emit error("文件 "+filePath+" 不存在");
        return;
    }
    else if(!hasFilePermission(filePath,QIODevice::ReadWrite))
    {
        emit error("无法访问文件 "+filePath);
        return;
    }
    else if(!filePath.endsWith("ini") && !filePath.endsWith("INI"))
    {
        emit error("文件格式不受支持");
        return;
    }
    if(project != nullptr && filePath == project->fileName())
    {
#ifndef Q_OS_ANDROID
        QMessageBox::information(this,"提示","该项目已经打开","确定");
#else
        Android::showNativeToast("该项目已经打开");
#endif
        mainbutton->clicked();
        return;
    }
    QSettings* setting = new QSettings(filePath,QSettings::IniFormat,this);
    if(!setting->contains("Project/name"))
    {
        emit error("项目文件 "+filePath+" 不合法");
        return;
    }
    if(needPassword && setting->contains("Project/password"))
    {
        //QString s = QInputDialog::getText(this,"输入密码","",QLineEdit::Password,"",ok);
        QInputDialog* dlg = new QInputDialog(this);
        dlg->setWindowTitle(" ");
        dlg->setTextEchoMode(QLineEdit::Password);
        dlg->setLabelText("输入密码");
        dlg->setOkButtonText("确定");
        dlg->setCancelButtonText("取消");
        if(dlg->exec() != QDialog::Accepted)
            return;
        QString s = dlg->textValue();
        if(s.isEmpty())
            return;
        else if(qCompress(s.toLocal8Bit().toBase64()) != setting->value("Project/password").value<QByteArray>())
        {
            emit error("密码错误");
            return;
        }
    }
    this->closeCurrentProject();
    project = setting;
    mainbutton->setEnabled(true);
    mainbutton->clicked();
    QStringList list;
    if(settings->contains("filelist") && settings->value("filelist").canConvert<QStringList>())
        list = settings->value("filelist").toStringList();
    int index = list.indexOf(filePath);
    if(index == -1)
        list.push_front(filePath);
    else
        list.move(index,0);
    settings->setValue("filelist",list);
    this->loadFileList();
    this->loadInfoTable();
}
void Widget::loadFileList()
{
    filelist->clear();
    if(settings->contains("filelist") && settings->value("filelist").canConvert<QStringList>())
    {
        QStringList list = settings->value("filelist").toStringList();
        for(QString path : list)
        {
            QSettings* setting = new QSettings(path,QSettings::IniFormat,this);
            if(!QFileInfo(path).isFile() || settings->status() != QSettings::NoError)
                continue;
            QIcon icon = QIcon();
            //QFileInfo info = QFileInfo(path);
            if(setting->contains("Project/icon"))
            {
                QPixmap pix = setting->value("Project/icon").value<QPixmap>();
                if(!pix.isNull())
                {
                    pix = pix.scaled(QSize(256,256),Qt::KeepAspectRatio,Qt::FastTransformation);
                    icon = QIcon(pix);
                }
            }
#ifdef Q_Device_Desktop
            filelist->addItem(path,setting->value("Project/name").toString(),SettingWidget::ComboBox,
                              QVariant::fromValue(QList<QString>({"","打开","打开文件夹","从列表移除","删除"})),QVariant(),icon);
#else
            filelist->addItem(path,setting->value("Project/name").toString(),SettingWidget::ComboBox,
                              QList<QString>({"","打开","分享","从列表移除","删除"}),QVariant(),icon);
#endif
        }
    }
}
void Widget::closeCurrentProject()
{
    if(project != nullptr)
    {
        if(settings != nullptr && settings->value("clearFilterOnClose").toString() == "true")
        {
            this->removeProjectFilter();
        }
        project->sync();
        project = nullptr;
    }
    mainbutton->setEnabled(false);
    welcomebutton->clicked();
}
void Widget::showEditDialog(InfoType type, int personIndex)
{
    QDialog* dlg = new QDialog(this);
    QComboBox* modebox = new QComboBox(dlg);
    QPushButton* closebutton = new QPushButton(dlg);
    QPushButton* iconbutton = new QPushButton(dlg);
    QLabel* namelabel = new QLabel(dlg);
    SettingWidget* infolist = new SettingWidget(dlg);
    QLineEdit* nameedit = new QLineEdit(dlg);
    QPushButton* namebutton = new QPushButton(dlg);
    QPushButton* removeiconbutton = new QPushButton(dlg);
    QList<int> indexlist;

#ifdef Q_Device_Desktop
    int w = this->height()/16*9;
    dlg->resize(w > this->width() ? this->width() : w ,this->height());
#else
    dlg->resize(screensize());
#endif

    closebutton->resize(30,30);
    closebutton->move(5,5);
    modebox->resize(closebutton->height()/3.0*5.0,closebutton->height());
    modebox->move(dlg->width()-closebutton->x()-modebox->width(),closebutton->y());
    if(dlg->width()/2 > 80)
        iconbutton->resize(80,80);
    else
        iconbutton->resize(dlg->width()/2,dlg->width()/2);
    iconbutton->move(dlg->width()/2-iconbutton->width()/2,closebutton->y()+closebutton->height());
    namelabel->resize(dlg->width(),closebutton->height());
    namelabel->move(0,iconbutton->y()+iconbutton->height());
    infolist->resize(namelabel->width(),dlg->height()-namelabel->y()-namelabel->height());
    infolist->move(namelabel->x(),namelabel->y()+namelabel->height());
    namebutton->resize(modebox->size());
    namebutton->move(namelabel->x()+namelabel->width()-closebutton->x()-namebutton->width(),namelabel->y());
    nameedit->resize(namelabel->size());
    nameedit->move(namelabel->pos());
    removeiconbutton->resize(namebutton->size());
    removeiconbutton->move(namebutton->x(),iconbutton->y()+iconbutton->height()/2-removeiconbutton->height()/2);

    modebox->addItems(QList<QString>({"编辑模式","展示模式"}));
    namelabel->setAlignment(Qt::AlignCenter);
    QFont f = namelabel->font();
    f.setBold(true);
    namelabel->setFont(f);
    iconbutton->setIconSize(iconbutton->size());
    closebutton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    closebutton->setIconSize(closebutton->size());
    namebutton->setText("编辑");
    removeiconbutton->setText("清除");
    nameedit->hide();
    QString icontype;
    if(currentThemeisDark)
        icontype = "white";
    else
        icontype = "black";
    closebutton->setIcon(QIcon(":/icon/back_"+icontype+".png"));

    int i = 0, j = 0;
    QString head;
    project->beginGroup("People");
    if(type == Global)
        head = "Global";
    else if(type == Personal && personIndex >= 0 && project->childGroups().contains("person"+QString::number(personIndex)))
        head = "People/person"+QString::number(personIndex);
    else if(type == Personal)
    {
        while(project->childGroups().contains("person"+QString::number(j)))
        {
            j++;
        }
        personIndex = j;
    }
    project->endGroup();
    while(project->contains("Types/type"+QString::number(i)+"/key"))
    {
        if((type == Global && project->value("Types/type"+QString::number(i)+"/range").toString() == "global")
           || (type == Personal && project->value("Types/type"+QString::number(i)+"/range").toString() == "personal"))
        {
            QString infotype = project->value("Types/type"+QString::number(i)+"/type").toString();
            QString name = project->value("Types/type"+QString::number(i)+"/name").toString();;
            QString key = project->value("Types/type"+QString::number(i)+"/key").toString();;
            indexlist.append(i);
            if(infotype == "StringList")
            {
                infolist->addItem(key,name,SettingWidget::PushButton,"编辑");
            }
            else if(infotype == "Image")
            {
                infolist->addItem(key,name,SettingWidget::ComboBox,QVariant::fromValue(QList<QString>({"","浏览","清除","查看","导出"})));
                if(!head.isEmpty() && project->contains(head+"/"+key))
                {
                    QPixmap pix = project->value(head+"/"+key).value<QPixmap>();
                    if(!pix.isNull())
                    {
                        infolist->setIcon(infolist->count()-1,QIcon(pix));
                    }
                }
            }
            else if(infotype == "Bool")
            {
                infolist->addItem(key,name,SettingWidget::SwitchButton);
                if(!head.isEmpty() && project->contains(head+"/"+key))
                {
                    if(project->value(head+"/"+key).toString() == "true")
                        infolist->switchbutton(infolist->count()-1)->setChecked(true);
                    else
                        infolist->switchbutton(infolist->count()-1)->setChecked(false);
                }
            }
            else if(infotype == "Int")
            {
                infolist->addItem(key,name,SettingWidget::SpinBox);
                if(!head.isEmpty() && project->contains(head+"/"+key) && project->value(head+"/"+key).canConvert<int>())
                {
                    infolist->spinBox(infolist->count()-1)->setValue(project->value(head+"/"+key).toInt());
                    infolist->spinBox(infolist->count()-1)->setRange(INT_MIN,INT_MAX);
                }
            }
            else if(infotype == "String")
            {
                QString text;
                if(!head.isEmpty() && project->contains(head+"/"+key))
                {
                    text = project->value(head+"/"+key).toString();
                    //infolist->lineEdit(i)->setText(text);
                }
                infolist->addItem(key,name,SettingWidget::LineEdit,text);
            }
        }
        i++;
    }

    if(type == Global)
    {
        dlg->setWindowTitle("全局信息管理器");
        infolist->addItem("password","修改密码",SettingWidget::Empty);
        namelabel->setText(project->value("Project/name").toString());
        if(project->contains("Project/icon"))
        {
            QPixmap pix = project->value("Project/icon").value<QPixmap>();
            if(!pix.isNull())
            {
                pix = pix.scaled(iconbutton->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                iconbutton->setIcon(QIcon(pix));
            }
        }
    }
    else
    {
        if(!head.isEmpty())
        {
            infolist->addItem("removeperson","移除个人",SettingWidget::Empty);
            dlg->setWindowTitle("个人信息管理器");
        }
        else
        {
            head = "People/person"+QString::number(personIndex);
            dlg->setWindowTitle("个人信息管理器 - 新建");
        }
        iconbutton->hide();
        removeiconbutton->hide();
        namelabel->hide();
        nameedit->hide();
        namebutton->hide();
        infolist->resize(infolist->width(),infolist->height()+(infolist->y()-iconbutton->y()));
        infolist->move(infolist->x(),iconbutton->y());
    }

    if(iconbutton->icon().isNull())
        iconbutton->setText("选择图标");
    modebox->hide();

    QObject::connect(closebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        dlg->close();
    });
    QObject::connect(namebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        if(namebutton->text() == "编辑")
        {
            namelabel->hide();
            nameedit->show();
            nameedit->setText(namelabel->text());
            nameedit->selectAll();
            namebutton->setText("确定");
        }
        else
        {
            QString name = nameedit->text();
            if(!name.isEmpty())
            {
                project->setValue("Project/name",name);
                namelabel->setText(name);
            }
            namebutton->setText("编辑");
            nameedit->hide();
            namelabel->show();
        }
    });
    QObject::connect(nameedit,QOverload<>::of(&QLineEdit::returnPressed),[=](){
        namebutton->clicked();
    });
    QObject::connect(removeiconbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        iconbutton->setIcon(QIcon());
        iconbutton->setText("选择图标");
        if(project->contains("Project/icon"))
            project->remove("Project/icon");
    });
    QObject::connect(iconbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        auto type = this->getApplicationFileDialogType();
        QString dir;
        if(QFileInfo(settings->value("defaultImagePath").toString()).isDir())
            dir = settings->value("defaultImagePath").toString();
        else
        {
#ifdef Q_OS_ANDROID
                dir = "/sdcard";
#else
                dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
#endif
        }
        if(!QFileInfo(dir).isDir()) QDir().mkpath(dir);
        QString path = MyFileDialog::getOpenFileName(dlg,"选择图片",dir,(type == QtDialog),currentThemeisDark);
#ifdef Q_OS_ANDROID
        path = Android::getRealPathFromUri(path);
#endif
        if(!path.isEmpty())
        {
            if(QFileInfo(path).isFile())
            {
                QPixmap pix;
                if(pix.loadFromData(readfile(path)))
                {
                    project->setValue("Project/icon",pix);
                    iconbutton->setText("");
                    iconbutton->setIcon(QIcon(pix));
                }
                else
                {
                    emit error("无法加载图片 "+path);
                }
            }
            else
            {
                emit error(path+" 不是文件");
            }
        }
    });
    QObject::connect(infolist,QOverload<int,QString,QString>::of(&SettingWidget::lineEditTextChanged),[=](int index,QString key,QString text){
        project->setValue(head+"/"+key,text);
    });
    QObject::connect(infolist,QOverload<int,QString,int>::of(&SettingWidget::spinboxValueChanged),[=](int index,QString key,int value){
        project->setValue(head+"/"+key,value);
    });
    QObject::connect(infolist,QOverload<int,QString,bool>::of(&SettingWidget::switchButtonClicked),[=](int index,QString key,bool value){
        project->setValue(head+"/"+key,value);
    });
    QObject::connect(infolist,QOverload<int,QString,int,QString>::of(&SettingWidget::comboBoxChanged),[=](int index,QString key,int currentIndex,QString currentText){
        //int typeindex = indexlist.at(index);
        //QString type = project->value("Types/type"+QString::number(typeindex)+"/type").toString();
        //QVariant var = project->value(head+"/"+key);
        if(currentIndex == 0) return;
        else if(currentIndex == 1)
        {
            auto type = this->getApplicationFileDialogType();
            QString dir;
            if(QFileInfo(settings->value("defaultImagePath").toString()).isDir())
                dir = settings->value("defaultImagePath").toString();
            else
            {
    #ifdef Q_OS_ANDROID
                    dir = "/sdcard";
    #else
                    dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    #endif
            }
            if(!QFileInfo(dir).isDir()) QDir().mkpath(dir);
            QString path = MyFileDialog::getOpenFileName(dlg,"选择图片",dir,(type == QtDialog),currentThemeisDark);
#ifdef Q_OS_ANDROID
        path = Android::getRealPathFromUri(path);
#endif
            if(!path.isEmpty())
            {
                if(QFileInfo(path).isFile())
                {
                    QPixmap pix;
                    if(pix.loadFromData(readfile(path)))
                    {
                        project->setValue(head+"/"+key,pix);
                        pix = pix.scaled(QSize(256,256),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                        infolist->setIcon(index,QIcon(pix));
                    }
                    else
                    {
                        emit error("无法加载图片 "+path);
                    }
                }
                else
                {
                    emit error(path+" 不是文件");
                }
            }
        }
        else if(currentIndex == 2)
        {
            if(project->contains(head+"/"+key))
                project->remove(head+"/"+key);
            if(!infolist->icon(index).isNull())
                infolist->setIcon(index,QIcon());
        }
        else if(currentIndex == 3)
        {
            if(!infolist->icon(index).isNull())
            {
                showPixmapDialog(infolist->icon(index).pixmap(1000,1000),dlg,key);
            }
        }
        else if(currentIndex == 4)
        {
            QPixmap pix;
            if(project->contains(head+"/"+key))
            {
                pix = project->value(head+"/"+key).value<QPixmap>();
                qDebug() << head+"/"+key << pix.size();
            }
            if(!pix.isNull())
            {
                auto type = this->getApplicationFileDialogType();
                QString dir;
                if(QFileInfo(settings->value("defaultImagePath").toString()).isDir())
                    dir = settings->value("defaultImagePath").toString();
                else
                {
        #ifdef Q_OS_ANDROID
                        dir = "/sdcard";
        #else
                        dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        #endif
                }
                if(!QFileInfo(dir).isDir()) QDir().mkpath(dir);
                QString path = MyFileDialog::getSaveFileName(dlg,"保存图片",dir,(type == QtDialog),currentThemeisDark);
#ifdef Q_OS_ANDROID
        path = Android::getRealPathFromUri(path);
#endif
                if(QFileInfo(path).suffix().isEmpty())
                {
                    if(path.endsWith("."))
                        path.chop(1);
                    path += ".png";
                }
                if(!pix.save(path))
                {
                    emit error("保存图片到 "+path+" 失败");
                }
            }
        }
        infolist->comboBox(index)->setCurrentIndex(0);
    });
    QObject::connect(infolist,QOverload<int,QString>::of(&SettingWidget::pushButtonClicked),[=](int index,QString key){
        QStringList list;
        if(project->contains(head+"/"+key))
            list = project->value(head+"/"+key).toStringList();
        list = this->showEditStringListDialog(list);
        project->setValue(head+"/"+key,list);
    });
    QObject::connect(infolist,QOverload<int,QString>::of(&SettingWidget::itemDoubleClicked),[=](int index,QString key){
        if(!infolist->icon(index).isNull())
        {
            showPixmapDialog(infolist->icon(index).pixmap(1000,1000),dlg,key);
        }
    });
    QObject::connect(infolist,QOverload<int,QString>::of(&SettingWidget::itemClicked),[=](int index,QString key){
        if(key == "password")
        {
            QInputDialog* dlg = new QInputDialog(this);
            dlg->setTextEchoMode(QLineEdit::Password);
            dlg->setWindowTitle(" ");
            dlg->setOkButtonText("确定");
            dlg->setCancelButtonText("取消");

            if(project->contains("Project/password"))
            {
                dlg->setLabelText("输入旧密码");
                if(dlg->exec() != QDialog::Accepted)
                    return;
                QString s = dlg->textValue();
                if(s.isEmpty())
                    return;
                if(qCompress(s.toLocal8Bit().toBase64()) != project->value("Project/password").value<QByteArray>())
                {
                    emit error("密码错误");
                    return;
                }
            }

            dlg->setLabelText("输入新密码");
            dlg->setTextValue("");
            if(dlg->exec() != QDialog::Accepted)
                return;
            QString s1 = dlg->textValue();
            dlg->setLabelText("确认新密码");
            dlg->setTextValue("");
            if(dlg->exec() != QDialog::Accepted)
                return;
            QString s2 = dlg->textValue();
            if(s1 != s2)
            {
                emit error("密码不一致");
                return;
            }
            else
            {
                if(!s1.isEmpty())
                    project->setValue("Project/password",qCompress(s1.toLocal8Bit().toBase64()));
                else
                    project->remove("Project/password");
                s1 = QString();
                s2 = QString();
            }
        }
        else if(key == "removeperson")
        {
            project->beginGroup("People");
            removeGroup(project,"person"+QString::number(personIndex));
            int n = personIndex + 1;
            while(project->childGroups().contains("person"+QString::number(n)))
            {
                renameGroup(project,"person"+QString::number(n),"person"+QString::number(n-1));
                n++;
            }
            removeGroup(project,"person"+QString::number(n-1));
            project->endGroup();
            dlg->close();
        }
    });

    fixSize(dlg);
    if(isTopMostWindow(this))
        staysOnTop(dlg);
    dlg->exec();
    this->setFocus();
    project->sync();
    this->loadInfoTable();
}
QStringList Widget::showEditStringListDialog(QStringList list, bool isEditMode,bool hideModeBox)
{
    QDialog* dlg = new QDialog(this);
    QTableWidget* table = new QTableWidget(dlg);
    QPushButton* newbutton = new QPushButton(dlg);
    QPushButton* removebutton = new QPushButton(dlg);
    QComboBox* modebox = new QComboBox(dlg);
    QPushButton* closebutton = new QPushButton(dlg);
    QTextBrowser* browser = new QTextBrowser(dlg);
    QTextBrowser* sumlabel = new QTextBrowser(dlg);

    std::function refreshSum = [=](){
        int column = 1;
        QList<int> selectionlist;
        QList<double> valuelist;
        for(int row = 1; row < table->rowCount(); row++)
        {
            auto item = table->item(row,column);
            if(item != nullptr)
            {
                if(item->isSelected()) selectionlist.append(row);
                if(isDouble(item->text())) valuelist.append(item->text().toDouble());
                else valuelist.append(0);
            }
            else
            {
                valuelist.append(0);
            }
        }

        double sum = 0;
        if(selectionlist.count() < 2)
        {
            for(double d : valuelist)
                sum += d;
        }
        else
        {
            for(int index : selectionlist)
            {
                auto item = table->item(index,column);
                if(item != nullptr)
                    sum += item->text().toDouble();
            }
        }
        sumlabel->setText("求和: "+QString::number(sum));
    };

#ifdef Q_Device_Desktop
    int w = this->height()/16*9;
    dlg->resize(w > this->width() ? this->width() : w ,this->height());
#else
    dlg->resize(screensize());
#endif

    if(isEditMode)
        dlg->setWindowTitle("编辑字符串列表");
    else
        dlg->setWindowTitle("查看字符串列表");
    modebox->addItems(QList<QString>({"编辑模式","展示模式"}));
    newbutton->setText("新建");
    removebutton->setText("移除");
    closebutton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    closebutton->setIconSize(closebutton->size());
    QString icontype;
    if(currentThemeisDark)
        icontype = "white";
    else
        icontype = "black";
    closebutton->setIcon(QIcon(":/icon/back_"+icontype+".png"));

    closebutton->resize(30,30);
    closebutton->move(5,5);
    modebox->resize(closebutton->height()/3.0*5.0,closebutton->height());
    modebox->move(dlg->width()-closebutton->x()-modebox->width(),closebutton->y());
    newbutton->resize((dlg->width()-5*closebutton->x()-closebutton->width()-modebox->width())/2,closebutton->height());
    newbutton->move(2*closebutton->x()+closebutton->width(),closebutton->y());
    removebutton->resize(newbutton->size());
    removebutton->move(newbutton->x()+newbutton->width()+closebutton->x(),newbutton->y());
    table->resize(dlg->width(),dlg->height()-closebutton->y()-closebutton->height());
    table->move(0,closebutton->y()+closebutton->height());
    browser->resize(table->size());
    browser->move(table->pos());
    sumlabel->resize(dlg->width(),modebox->height());
    sumlabel->move(dlg->width()-sumlabel->width(),dlg->height()-sumlabel->height());
    sumlabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    table->resize(table->width(),table->height()-sumlabel->height());

    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);
    table->resizeRowsToContents();
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    QScroller::grabGesture(table->viewport(),QScroller::TouchGesture);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setColumnCount(2);
    table->setRowCount(list.count()+1);

    double sum = 0;
    for(int y = 0; y < table->rowCount(); y++)
    {
        for(int x = 0; x < table->columnCount(); x++)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            if(x == 0)
            {
                item->setTextAlignment(Qt::AlignCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                if(y != 0)
                    item->setText(QString::number(y-1));
                else
                {
                    item->setText("索引");
                    table->setColumnWidth(x,table->viewport()->width()/5);
                }
            }
            else
            {
                item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                if(y != 0)
                {
                    item->setText(list.at(y-1));
                    if(isDouble(item->text()))
                    {
                        sum += item->text().toDouble();
                    }
                }
                else
                {
                    item->setText("内容");
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    table->setColumnWidth(x,table->viewport()->width()*0.8);
                }
            }
            table->setItem(y,x,item);
        }
    }
    sumlabel->setText("求和: "+QString::number(sum));

    QObject::connect(modebox,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
        if(index == 0)
        {
            browser->hide();
            table->show();
            newbutton->setEnabled(true);
            removebutton->setEnabled(true);
        }
        else
        {
            table->hide();
            browser->show();
            QStringList ret;
            for(int y = 1; y < table->rowCount(); y++)
                ret.append(table->item(y,1)->text());
            browser->setText(ret.join(",\n"));
            newbutton->setEnabled(false);
            removebutton->setEnabled(false);
        }
    });
    QObject::connect(closebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        dlg->close();
    });
    QObject::connect(newbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        table->setRowCount(table->rowCount()+1);
        for(int x = 0; x < table->columnCount(); x++)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            if(x == 0)
            {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                item->setText(QString::number(table->rowCount()-2));
                item->setTextAlignment(Qt::AlignCenter);
            }
            else
            {
                item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            }
            table->setItem(table->rowCount()-1,x,item);
        }
        table->editItem(table->item(table->rowCount()-1,1));
    });
    QObject::connect(removebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        int current = table->currentRow();
        if(current != -1 && current != 0)
        {
            bool flag_refresh = isDouble(table->item(current,1)->text());
            table->removeRow(current);
            for(int i = current; i < table->rowCount(); i++)
                table->item(i,0)->setText(QString::number(i-1));
            if(flag_refresh) refreshSum();
        }
    });
    QObject::connect(table,QOverload<int,int>::of(&QTableWidget::cellChanged),[=](){
        refreshSum();
    });
    QObject::connect(table,QOverload<>::of(&QTableWidget::itemSelectionChanged),[=](){
        //qDebug() << table->selectedRanges().count();
        refreshSum();
    });

    if(!isEditMode)
        modebox->setCurrentIndex(1);
    else
        browser->hide();
    if(hideModeBox)
    {
        modebox->hide();
        if(!isEditMode)
        {
            newbutton->hide();
            removebutton->hide();
        }
    }

    fixSize(dlg);
    if(isTopMostWindow(this))
        staysOnTop(dlg);
    dlg->exec();
    QStringList ret;
    for(int y = 1; y < table->rowCount(); y++)
        ret.append(table->item(y,1)->text());
    return ret;
}
void Widget::loadInfoTable()
{
    infotable->clear();
    QList<int> indexlist;
    int i = 0;
    while(project->contains("Types/type"+QString::number(i)+"/range"))
    {
        if(project->value("Types/type"+QString::number(i)+"/range").toString() == "personal")
        {
            indexlist.append(i);
        }
        i++;
    }
    project->beginGroup("People");
    int peopleCount = project->childGroups().count();
    project->endGroup();
    infotable->setColumnCount(indexlist.count()+1);
    infotable->setRowCount(peopleCount+1);
    for(int y = 0; y < infotable->rowCount(); y++)
    {
        for(int x = 0; x < infotable->columnCount(); x++)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            if(y == 0)
            {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                if(x == 0)
                    item->setText("索引");
                else
                {
                    int typeindex = indexlist.at(x-1);
                    item->setText(project->value("Types/type"+QString::number(typeindex)+"/name").toString());
                }
            }
            else
            {
                if(x == 0)
                {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    item->setText(QString::number(y-1));
                }
                else
                {
                    int personindex = y-1;
                    int typeindex = indexlist.at(x-1);
                    QString key = project->value("Types/type"+QString::number(typeindex)+"/key").toString();
                    QString type = project->value("Types/type"+QString::number(typeindex)+"/type").toString();
                    QString head = "People/person" + QString::number(personindex);
                    if(project->contains(head+"/"+key))
                    {
                        QVariant var = project->value(head+"/"+key);
                        if(type == "Int" || type == "String")
                            item->setText(var.toString());
                        else if(type == "Bool")
                            item->setText(var.toString() == "true" ? "是" : "否");
                        else if((type == "StringList" && var.canConvert<QStringList>()) || (type == "Image" && var.canConvert<QPixmap>()))
                            item->setText("查看");
                    }
                }
            }
            infotable->setItem(y,x,item);
        }
    }

    if(project->contains("Filter/key"))
    {
        QString key = project->value("Filter/key").toString();
        int index = this->getTypeIndexFromKey(key);
        project->beginGroup("Types");
        if(index != -1 && project->childGroups().contains("type"+QString::number(index)))
        {
            project->endGroup();
            QString type = project->value("Types/type"+QString::number(index)+"/type").toString();
            QString name = project->value("Types/type"+QString::number(index)+"/name").toString();
            int col = -1;
            for(int i = 1; i < infotable->columnCount(); i++)
            {
                if(infotable->item(0,i)->text() == name)
                {
                    col = i;
                    break;
                }
            }

            if(col != -1)
            {
                if(type == "Int" && project->contains("Filter/order"))
                {
                    QString order = project->value("Filter/order").toString();
                    if(order == "Qt::DescendingOrder")
                        sortByColumn(infotable,col,Qt::DescendingOrder,1);
                    else if(order == "Qt::AscendingOrder")
                        sortByColumn(infotable,col,Qt::AscendingOrder,1);
                }
                else if((type == "String" || type == "Int" || type == "Bool") && project->contains("Filter/text"))
                {
                    sortByColumn(infotable,col,project->value("Filter/text").toString(),exactbutton->isChecked(),casebutton->isChecked(),1);
                }
            }
        }
        else
        {
            project->endGroup();
        }
    }
    else if(project->contains("Filter/order"))
    {
        QString order = project->value("Filter/order").toString();
        if(order == "Qt::DescendingOrder")
            sortByColumn(infotable,0,Qt::DescendingOrder,1);
    }
}
void Widget::processArguments()
{
    QPoint p = QPoint(0,0);
    QMimeData* data = new QMimeData;
    QList<QUrl> list;
    for(QString s : qApp->arguments())
    {
        list.append(QUrl::fromLocalFile(s));
    }
    data->setUrls(list);
    QDragEnterEvent event1(p,Qt::DropAction::CopyAction,data,Qt::LeftButton,Qt::NoModifier);
    QDropEvent event2(p,Qt::DropAction::CopyAction,data,Qt::LeftButton,Qt::NoModifier,QEvent::Drop);
    QApplication::sendEvent(this,&event1);
    QApplication::sendEvent(this,&event2);
}
int Widget::getTypeIndexFromKey(QString key)
{
    int i = 0;
    int index = -1;
    while(project->contains("Types/type"+QString::number(i)+"/key"))
    {
        if(project->value("Types/type"+QString::number(i)+"/key").toString() == key)
        {
            index = i;
            break;
        }
        i++;
    }
    return index;
}
int Widget::getTypeIndexFromName(QString name)
{
    int i = 0;
    int index = -1;
    while(project->contains("Types/type"+QString::number(i)+"/name"))
    {
        if(project->value("Types/type"+QString::number(i)+"/name").toString() == name)
        {
            index = i;
            break;
        }
        i++;
    }
    return index;
}
void Widget::removeProjectFilter()
{
    if(project != nullptr && project->childGroups().contains("Filter"))
    {
        removeGroup(project,"Filter");
    }
}
void Widget::infoTableClicked(int y, int x)
{
    if(x != 0)
    {
        QString name = infotable->item(0,x)->text();
        int index = getTypeIndexFromName(name);
        if(index != -1)
        {
            QString head = "People/person" + infotable->item(y,0)->text();
            QString key = project->value("Types/type"+QString::number(index)+"/key").toString();
            QString type = project->value("Types/type"+QString::number(index)+"/type").toString();
            QVariant var = project->value(head+"/"+key);
            if(y != 0)
            {
                if(type == "StringList")
                {
                    auto list = var.toStringList();
                    bool isEditMode = false;
                    if(list.isEmpty()) isEditMode = true;
                    auto newlist = this->showEditStringListDialog(list,isEditMode);
                    project->setValue(head+"/"+key,newlist);
                }
                else if(type == "Image")
                {
                    QPixmap pix = var.value<QPixmap>();
                    if(!pix.isNull())
                        showPixmapDialog(pix.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation),this);
                }
                else if(type == "String")
                {
                    QInputDialog* dlg = new QInputDialog(this);
                    dlg->setWindowTitle(" ");
                    dlg->setLabelText("编辑字符串");
                    dlg->setOkButtonText("确定");
                    dlg->setCancelButtonText("取消");
                    dlg->setTextValue(infotable->item(y,x)->text());
                    if(dlg->exec() == QDialog::Accepted)
                    {
                        QString s = dlg->textValue();
                        if(s != infotable->item(y,x)->text())
                        {
                            project->setValue(head+"/"+key,s);
                            this->loadInfoTable();
                        }
                    }
                }
                else if(type == "Int")
                {
                    QInputDialog* dlg = new QInputDialog(this);
                    dlg->setWindowTitle(" ");
                    dlg->setInputMode(QInputDialog::IntInput);
                    dlg->setLabelText("编辑整数");
                    dlg->setOkButtonText("确定");
                    dlg->setCancelButtonText("取消");
                    dlg->setIntMaximum(INT_MAX);
                    dlg->setIntMinimum(INT_MIN);
                    dlg->setIntValue(infotable->item(y,x)->text().isEmpty() ? 0 : infotable->item(y,x)->text().toInt());
                    if(dlg->exec() == QDialog::Accepted)
                    {
                        int n = dlg->intValue();
                        if((!infotable->item(y,x)->text().isEmpty() && n != infotable->item(y,x)->text().toInt())
                        || infotable->item(y,x)->text().isEmpty())
                        {
                            project->setValue(head+"/"+key,n);
                            this->loadInfoTable();
                        }
                    }
                }
            }
            else
            {
                if(type == "Int")
                {
                    if((project->contains("Filter/key") && project->value("Filter/key").toString() != key)
                    || (!project->contains("Filter/key") && project->contains("Filter/order")))
                    {
                        this->removeProjectFilter();
                    }
                    if(!project->childGroups().contains("Filter"))
                    {
                        project->setValue("Filter/key",key);
                        project->setValue("Filter/order","Qt::DescendingOrder");
                        this->loadInfoTable();
                    }
                    else if(project->value("Filter/key") == key)
                    {
                        if(project->value("Filter/order") == "Qt::DescendingOrder")
                        {
                            project->setValue("Filter/order","Qt::AscendingOrder");
                        }
                        else
                        {
                            this->removeProjectFilter();
                        }
                        this->loadInfoTable();
                    }
                }
                else if(type == "String" || type == "Bool")
                {
                    filteredit->setFocus();
                    QGuiApplication::inputMethod()->show();
                }
            }
        }
    }
    else if(x == 0 && y == 0)
    {
        if(project->contains("Filter/key") || project->contains("Filter/order") || project->contains("Filter/text"))
            this->removeProjectFilter();
        else
            project->setValue("Filter/order","Qt::DescendingOrder");
        this->loadInfoTable();
    }
    project->sync();
}
QStringList Widget::getTypeInfo(QString key)
{
    QStringList list;
    if(project != nullptr)
    {
        int i = 0;
        while(project->contains("Types/type"+QString::number(i)+"/"+key))
        {
            list.append(project->value("Types/type"+QString::number(i)+"/"+key).toString());
            i++;
        }
    }
    return list;
}
int Widget::getPeopleCount()
{
    int ret = 0;
    if(project != nullptr)
    {
        project->beginGroup("People");
        QStringList groups = project->childGroups();
        project->endGroup();
        while(groups.contains("person"+QString::number(ret)))
            ret++;
    }
    return ret;
}
void Widget::showAutoChangeDialog()
{
    QDialog* dlg = new QDialog(this);
    QPushButton* closebutton = new QPushButton(dlg);
    SettingWidget* list = new SettingWidget(dlg);
    bool* flag_refresh = new bool;
    QStringList* stringlist = new QStringList;
    QPixmap* pixmap = new QPixmap;
    *flag_refresh = false;

#ifdef Q_Device_Desktop
    dlg->resize(this->size()/2);
#else
    dlg->resize(screensize());
#endif
    closebutton->resize(30,30);
    closebutton->move(5,5);
    closebutton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    closebutton->setIconSize(closebutton->size());
    //commitbutton->resize(50,30);
    //commitbutton->move(dlg->width()-closebutton->x()-commitbutton->width(),dlg->height()-closebutton->y()-commitbutton->height());
    list->resize(dlg->width(),dlg->height()-closebutton->height()-2*closebutton->y());
    list->move(dlg->width()-list->width(),dlg->height()-list->height());

    QString icontype;
    if(currentThemeisDark)
        icontype = "white";
    else
        icontype = "black";
    closebutton->setIcon(QIcon(":/icon/back_"+icontype+".png"));
    dlg->setWindowTitle("批量管理");
    //commitbutton->setText("确定");

    int peopleCount = this->getPeopleCount();
    list->addItem("type","选择类型",SettingWidget::ComboBox,QVariant::fromValue(QList<QString>({"不限","整数","布尔","字符串","字符串列表","图像"}))); //0
    list->addItem("name","选择名称",SettingWidget::ComboBox); //1
    list->addItem("mode","模式",SettingWidget::ComboBox); //2
    list->addItem("value"," ",SettingWidget::Empty); //3
    list->addItem("beginIndex","起始索引",SettingWidget::SpinBox,QVariant(),0,QIcon(),"",0,peopleCount); //4
    list->addItem("endIndex","终止索引(不含)",SettingWidget::SpinBox,QVariant(),peopleCount,QIcon(),"",0,peopleCount); //5
    list->addItem("commitbutton"," ",SettingWidget::PushButton,"确定"); //6

    std::function refreshNameBox = [=](){
        QString text = list->comboBox(0)->currentText();
        QStringList targetlist;
        if(text == "整数") targetlist.append("Int");
        else if(text == "布尔") targetlist.append("Bool");
        else if(text == "字符串") targetlist.append("String");
        else if(text == "字符串列表") targetlist.append("StringList");
        else if(text == "图像") targetlist.append("Image");
        else if(text == "不限") targetlist = QList<QString>({"Int","Bool","String","StringList","Image"});

        if(!targetlist.isEmpty())
        {
            QStringList names = this->getTypeInfo("name");
            QStringList types = this->getTypeInfo("type");
            if(targetlist.count() == 1)
            {
                QList<int> indexlist;
                for(int i = 0; i < types.count(); i++)
                {
                    if(!targetlist.contains(types.at(i)))
                        indexlist.append(i);
                }
                std::reverse(indexlist.begin(),indexlist.end());
                for(int i = 0; i < indexlist.count(); i++)
                    names.removeAt(indexlist.at(i));
            }
            list->comboBox(1)->clear();
            list->comboBox(1)->addItems(names);
            if(names.isEmpty())
            {
                list->comboBox(2)->clear();
                list->setMode(3,SettingWidget::Empty);
                list->setName(3,"");
            }
        }
    };

    std::function refreshMode = [=](){
        int index = this->getTypeIndexFromName(list->comboBox(1)->currentText());
        if(index != -1)
        {
            QString type = this->getTypeInfo("type").at(index);
            QStringList modelist;
            if(type == "Int")
            {
                modelist.append("增加");
                modelist.append("乘积");
            }
            else if(type == "StringList")
            {
                modelist.append("追加");
            }
            modelist.append("设为");
            modelist.append("清除");
            list->comboBox(2)->clear();
            list->comboBox(2)->addItems(modelist);
        }
    };

    std::function refreshValueItem = [=](){
        int index = this->getTypeIndexFromName(list->comboBox(1)->currentText());
        QString mode = list->comboBox(2)->currentText();
        if(index != -1 && !mode.isEmpty())
        {
            QString type = this->getTypeInfo("type").at(index);
            if(mode == "清除")
            {
                list->setMode(3,SettingWidget::Empty);
                list->setName(3,"");
            }
            else if(type == "Int")
            {
                list->setMode(3,SettingWidget::SpinBox);
                if(mode == "增加")
                    list->setName(3,"变化量");
                else if(mode == "乘积")
                    list->setName(3,"乘数");
                else
                    list->setName(3,"设置整数");
            }
            else if(type == "String")
            {
                list->setMode(3,SettingWidget::LineEdit);
                list->setName(3,"设置字符串");
                list->lineEdit(3)->clear();
            }
            else if(type == "StringList")
            {
                if(mode == "追加")
                {
                    list->setMode(3,SettingWidget::LineEdit);
                    list->setName(3,"追加字符串");
                    list->lineEdit(3)->clear();
                }
                else
                {
                    list->setMode(3,SettingWidget::PushButton);
                    list->setName(3,"设置字符串列表");
                    list->pushButton(3)->setText("编辑");
                }
            }
            else if(type == "Image")
            {
                list->setMode(3,SettingWidget::PushButton);
                list->setName(3,"设置图像");
                list->pushButton(3)->setText("浏览");
            }
            else if(type == "Bool")
            {
                list->setMode(3,SettingWidget::SwitchButton);
                list->setName(3,"设置布尔");
            }
        }
    };

    refreshNameBox();
    refreshMode();
    refreshValueItem();
    list->spinBox(3)->setRange(INT_MIN,INT_MAX);

    QObject::connect(closebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        dlg->close();
    });
    QObject::connect(list,QOverload<int,QString,int,QString>::of(&SettingWidget::comboBoxChanged),[=](int index,QString key,int currentIndex,QString currentText){
        if(currentText.isEmpty() || *flag_refresh)
            return;
        *flag_refresh = true;
        if(index == 0)
        {
            refreshNameBox();
            refreshMode();
            refreshValueItem();
        }
        else if(index == 2)
        {
            refreshValueItem();
        }
        *flag_refresh = false;
    });
    QObject::connect(list,QOverload<int,QString>::of(&SettingWidget::pushButtonClicked),[=](int index,QString key){
        if(key == "value")
        {
            QString text = list->pushButton(index)->text();
            if(text == "编辑")
            {
                *stringlist = this->showEditStringListDialog(*stringlist);
            }
            else if(text == "浏览")
            {
                auto type = this->getApplicationFileDialogType();
                QString dir;
                if(QFileInfo(settings->value("defaultImagePath").toString()).isDir())
                    dir = settings->value("defaultImagePath").toString();
                else
                {
        #ifdef Q_OS_ANDROID
                        dir = "/sdcard";
        #else
                        dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        #endif
                }
                if(!QFileInfo(dir).isDir()) QDir().mkpath(dir);
                QString path = MyFileDialog::getOpenFileName(dlg,"选择图片",dir,(type == QtDialog),currentThemeisDark);
        #ifdef Q_OS_ANDROID
                path = Android::getRealPathFromUri(path);
        #endif
                if(!path.isEmpty())
                {
                    if(QFileInfo(path).isFile())
                    {
                        QPixmap pix;
                        if(pix.loadFromData(readfile(path)))
                        {
                            *pixmap = pix;
                        }
                        else
                        {
                            emit error("无法加载图片 "+path);
                        }
                    }
                    else
                    {
                        emit error(path+" 不是文件");
                    }
                }
            }
        }
        else if(key == "commitbutton")
        {
            QString name = list->comboBox(1)->currentText();
            QString mode = list->comboBox(2)->currentText();
            int index = this->getTypeIndexFromName(name);
            int beginIndex = list->spinBox(4)->value();
            int endIndex = list->spinBox(5)->value();
            if(beginIndex >= endIndex)
            {
                list->spinBox(5)->setFocus();
                list->spinBox(5)->selectAll();
                QGuiApplication::inputMethod()->show();
                return;
            }
            else if(index != -1)
            {
                QString key = this->getTypeInfo("key").at(index);
                QString type = this->getTypeInfo("type").at(index);
                if(type == "Image" && (pixmap == nullptr || (*pixmap).isNull()) && mode == "设为")
                {
                    list->pushButton(3)->setFocus();
                    return;
                }
                else if(type == "StringList" && (stringlist == nullptr || (*stringlist).isEmpty()) && mode == "设为")
                {
                    list->pushButton(3)->setFocus();
                    return;
                }
                else if(mode == "清除")
                {
                    for(int i = beginIndex; i < endIndex; i++)
                    {
                        project->remove("People/person"+QString::number(i)+"/"+key);
                    }
                }
                else if(mode == "设为")
                {
                    QVariant var;
                    if(type == "Int")
                        var = list->spinBox(3)->value();
                    else if(type == "String")
                        var = list->lineEdit(3)->text();
                    else if(type == "Image")
                        var = *pixmap;
                    else if(type == "StringList")
                        var = *stringlist;
                    else if(type == "Bool")
                        var = list->switchbutton(3)->isChecked();
                    for(int i = beginIndex; i < endIndex; i++)
                    {
                        project->setValue("People/person"+QString::number(i)+"/"+key,var);
                    }
                }
                else if(type == "StringList" && mode == "追加")
                {
                    QString text = list->lineEdit(3)->text();
                    if(text.isEmpty())
                    {
                        list->lineEdit(5)->setFocus();
                        QGuiApplication::inputMethod()->show();
                        return;
                    }
                    else
                    {
                        for(int i = beginIndex; i < endIndex; i++)
                        {
                            QStringList list = project->value("People/person"+QString::number(i)+"/"+key).toStringList();
                            list.append(text);
                            project->setValue("People/person"+QString::number(i)+"/"+key,list);
                        }
                    }
                }
                else if(type == "Int" && (mode == "增加" || mode == "乘积"))
                {
                    bool flag_delta = (mode == "增加");
                    int value = list->spinBox(3)->value();
                    for(int i = beginIndex; i < endIndex; i++)
                    {
                        int n = project->value("People/person"+QString::number(i)+"/"+key).toInt();
                        if(flag_delta)
                            n += value;
                        else
                            n *= value;
                        project->setValue("People/person"+QString::number(i)+"/"+key,n);
                    }
                }
                dlg->close();
                this->loadInfoTable();
            }
        }
    });

    fixSize(dlg);
    if(isTopMostWindow(this))
        staysOnTop(dlg);
    dlg->exec();
}
