#include "settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent)
    : QWidget{parent}
{
    area = new QScrollArea(this);
    mainwidget = new QWidget(this);
    mainwidget->resize(this->width()-20,(widgetlist.count()+1)*h);
    area->setWidget(mainwidget);
    area->setGeometry(0,0,this->width(),this->height());
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller::grabGesture(area->viewport(),QScroller::TouchGesture);
    mainwidget->show();
    this->installEventFilter(this);
}
bool SettingWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            this->refreshUI();
        }
    }
    else if(widgetlist.contains((QWidget*)watched) && (QWidget*)watched != nullptr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            time = QTime::currentTime();
            p1 = e->pos();
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            //int interval = -1;
            if(time.isValid() && !p1.isNull())
            {
                //interval = time.msecsTo(QTime::currentTime());
                if(e->pos() == p1)
                {
                    if(e->button() == Qt::LeftButton || e->button() == Qt::NoButton)
                    {
                        int index = widgetlist.indexOf((QWidget*)watched);
                        QString key = keylist.at(index);
                        emit itemClicked(index,key);
                    }
                    else if(e->button() == Qt::RightButton)
                    {
                        int index = widgetlist.indexOf((QWidget*)watched);
                        QString key = keylist.at(index);
                        emit itemRightButtonClicked(index,key);
                    }
                }
            }
            time = QTime();
            p1 = QPoint();
        }
        else if(event->type() == QEvent::MouseButtonDblClick)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            if(e->button() == Qt::LeftButton || e->button() == Qt::NoButton)
            {
                int index = widgetlist.indexOf((QWidget*)watched);
                QString key = keylist.at(index);
                emit itemDoubleClicked(index,key);
            }
            time = QTime();
            p1 = QPoint();
        }
    }
    else if(qobject_cast<QSlider*>(watched) != nullptr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QSlider* s = qobject_cast<QSlider*>(watched);
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(s->isEnabled() && mouseEvent->button() != Qt::RightButton)
                s->setValue(s->minimum()+float(mouseEvent->x())/float(s->width())*float(s->maximum()-s->minimum()));
        }
    }
    return QWidget::eventFilter(watched,event);
}
void SettingWidget::refreshUI()
{
    mainwidget->resize(this->width()-20,(widgetlist.count()+1)*h);
    area->setGeometry(0,0,this->width(),this->height());
    for(int i = 0;i < widgetlist.count();i++)
    {
        QWidget* w = widgetlist.at(i);
        QLabel* namelabel = namelabellist.at(i);
        QPushButton* pushbutton = pushbuttonlist.at(i);
        QComboBox* combobox = comboboxlist.at(i);
        QRadioButton* radiobutton = radiobuttonlist.at(i);
        QLineEdit* lineedit = lineeditlist.at(i);
        QSpinBox* spinbox = spinboxlist.at(i);
        QSlider* slider = sliderlist.at(i);
        QProgressBar* progressbar = progressbarlist.at(i);
        MySwitchButton* switchbutton = switchbuttonlist.at(i);
        int delta = mainwidget->width() - w->width();
        w->resize(mainwidget->width(),w->height());
        namelabel->resize(namelabel->width()+delta,namelabel->height());

        for(QWidget* w : QList<QWidget*>({pushbutton,combobox,radiobutton,lineedit,spinbox,slider,progressbar,switchbutton}))
            w->move(w->x()+delta,w->y());
    }
}
bool SettingWidget::addItem(QString key, QString name, Mode mode, QVariant content, QVariant defaultValue,QIcon icon, QString tooltip,QVariant min_value,QVariant max_value,bool enable)
{
    if(!key.isEmpty() && !keylist.contains(key) && !name.isEmpty() && mode != InVaild)
    {
        QStringList combobox_items;
        QString text;
        if(content.canConvert<QStringList>())
            combobox_items = content.value<QStringList>();
        if(content.canConvert<QString>())
            text = content.value<QString>();

        QWidget* w = new QWidget(mainwidget);
        QLabel* iconlabel = new QLabel(w);
        QLabel* namelabel = new QLabel(w);
        QPushButton* pushbutton = new QPushButton(w);
        QComboBox* combobox = new QComboBox(w);
        QRadioButton* radiobutton = new QRadioButton(w);
        QLineEdit* lineedit = new QLineEdit(w);
        QSpinBox* spinbox = new QSpinBox(w);
        QSlider* slider = new QSlider(w);
        QProgressBar* progressbar = new QProgressBar(w);
        MySwitchButton* switchbutton = new MySwitchButton(w);

        mainwidget->resize(this->width()-20,(widgetlist.count()+1)*h);
        w->resize(mainwidget->width(),h);
        w->move(0,widgetlist.count()*h);
        iconlabel->setAlignment(Qt::AlignCenter);
        namelabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        namelabel->setToolTip(tooltip);
        namelabel->setOpenExternalLinks(true);

        QSize s1 = QSize((h-10.0)/3.0*5.0,h-10);
        if(mode == RadioButton)
        {
            s1.setWidth(s1.height());
        }
        else if(mode == ComboBox || mode == PushButton)
        {
            int w1 = 0;
            if(mode == ComboBox && !combobox_items.isEmpty())
            {
                w1 = nativeLabelSize(combobox_items.at(getLongestStringIndex(combobox_items))).width();
            }
            else
            {
                w1 = nativeLabelSize(text).width();
            }
            if(w1 > w->width()/2.0)
                s1.setWidth(w->width()/2);
            else if(w1 > s1.width())
                s1.setWidth(w1);
        }

        QWidget* target = nullptr;
        if(mode == PushButton)
            target = pushbutton;
        else if(mode == ComboBox)
            target = combobox;
        else if(mode == RadioButton)
            target = radiobutton;
        else if(mode == LineEdit)
            target = lineedit;
        else if(mode == SpinBox)
            target = spinbox;
        else if(mode == Slider)
            target = slider;
        else if(mode == ProgressBar)
            target = progressbar;
        else if(mode == SwitchButton)
            target = switchbutton;

        for(QWidget* widget : QList<QWidget*>({pushbutton,combobox,radiobutton,lineedit,spinbox,slider,progressbar,switchbutton}))
        {
            widget->hide();
            widget->resize(s1);
            widget->move(w->width()-5-widget->width(),w->height()/2.0-widget->height()/2.0);
        }

        QSize s2 = QSize(h-10,h-10);
        if(icon.isNull())
        {
            iconlabel->hide();
            namelabel->move(5,5);
        }
        else
        {
            iconlabel->resize(s2);
            iconlabel->move(5,5);
            //namelabel->resize(w->width()/2-iconlabel->x()-iconlabel->width(),iconlabel->width());
            namelabel->move(iconlabel->width()+iconlabel->x(),iconlabel->y());
            QPixmap p = icon.pixmap(1000,1000);
            if(!p.isNull())
            {
                p = p.scaled(s2,Qt::KeepAspectRatio,Qt::SmoothTransformation);
                iconlabel->setPixmap(p);
            }
        }
        if(target != nullptr)
            namelabel->resize(target->x()-namelabel->x(),iconlabel->height());
        else
            namelabel->resize(w->width()-namelabel->x(),iconlabel->height());

        namelabel->setText(name);
        pushbutton->setText(text);
        combobox->addItems(combobox_items);
        lineedit->setText(text);
        slider->setOrientation(Qt::Horizontal);
        slider->installEventFilter(this);
        progressbar->setTextVisible(false);
        for(QWidget* w : QList<QWidget*>({pushbutton,combobox,radiobutton,lineedit,spinbox,slider,progressbar,switchbutton}))
            w->setEnabled(enable);
        if(max_value.isValid() && max_value.canConvert<int>() && min_value.isValid() && min_value.canConvert<int>())
        {
            spinbox->setRange(min_value.toInt(),max_value.toInt());
            slider->setRange(min_value.toInt(),max_value.toInt());
            progressbar->setRange(min_value.toInt(),max_value.toInt());
        }


        if(target != nullptr)
            target->show();

        w->installEventFilter(this);
        w->show();

        if(mode == ComboBox)
        {
            if(defaultValue.canConvert<int>())
                combobox->setCurrentIndex(defaultValue.value<int>());
            else if(defaultValue.canConvert<QString>())
                combobox->setCurrentText(defaultValue.value<QString>());
        }
        else if(mode == RadioButton || mode == SwitchButton)
        {
            if(defaultValue.canConvert<bool>())
            {
                switchbutton->setChecked(defaultValue.value<bool>());
                radiobutton->setChecked(defaultValue.value<bool>());
            }
        }
        else if(mode == SpinBox || mode == Slider || mode == ProgressBar)
        {
            if(defaultValue.canConvert<int>())
            {
                slider->setValue(defaultValue.toInt());
                spinbox->setValue(defaultValue.toInt());
                progressbar->setValue(defaultValue.toInt());
            }
        }

        QObject::connect(pushbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
            int i = pushbuttonlist.indexOf(pushbutton);
            emit pushButtonClicked(i,key);
        });
        QObject::connect(combobox,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
            int i = comboboxlist.indexOf(combobox);
            defaultvaluelist[i] = index;
            emit comboBoxChanged(i,key,index,combobox->currentText());
        });
        QObject::connect(radiobutton,QOverload<bool>::of(&QRadioButton::clicked),[=](){
            int i = radiobuttonlist.indexOf(radiobutton);
            defaultvaluelist[i] = radiobutton->isChecked();
            emit radioButtonClicked(i,key,radiobutton->isChecked());
        });
        QObject::connect(lineedit,QOverload<const QString&>::of(&QLineEdit::textChanged),[=](const QString& s){
            int i = lineeditlist.indexOf(lineedit);
            contentlist[i] = lineedit->text();
            emit lineEditTextChanged(i,key,s);
        });
        QObject::connect(spinbox,QOverload<int>::of(&QSpinBox::valueChanged),[=](){
            int i = spinboxlist.indexOf(spinbox);
            defaultvaluelist[i] = spinbox->value();
            emit spinboxValueChanged(i,key,spinbox->value());
        });
        QObject::connect(slider,QOverload<int>::of(&QSlider::valueChanged),[=](){
            int i = sliderlist.indexOf(slider);
            defaultvaluelist[i] = slider->value();
            emit sliderValueChanged(i,key,slider->value());
        });
        QObject::connect(progressbar,QOverload<int>::of(&QProgressBar::valueChanged),[=](){
            int i = progressbarlist.indexOf(progressbar);
            defaultvaluelist[i] = progressbar->value();
            emit progressbarValueChanged(i,key,progressbar->value());
        });
        QObject::connect(switchbutton,QOverload<bool>::of(&MySwitchButton::clicked),[=](){
            int i = switchbuttonlist.indexOf(switchbutton);
            defaultvaluelist[i] = switchbutton->isChecked();
            emit switchButtonClicked(i,key,switchbutton->isChecked());
        });

        keylist.append(key);
        namelist.append(name);
        modelist.append(mode);
        contentlist.append(content);
        defaultvaluelist.append(defaultValue);
        minvaluelist.append(min_value);
        maxvaluelist.append(max_value);
        tooltiplist.append(tooltip);
        iconlist.append(icon);
        enablelist.append(enable);

        widgetlist.append(w);
        pushbuttonlist.append(pushbutton);
        comboboxlist.append(combobox);
        radiobuttonlist.append(radiobutton);
        namelabellist.append(namelabel);
        iconlabellist.append(iconlabel);
        lineeditlist.append(lineedit);
        spinboxlist.append(spinbox);
        sliderlist.append(slider);
        progressbarlist.append(progressbar);
        switchbuttonlist.append(switchbutton);
        return true;
    }
    else
    {
        return false;
    }
}
void SettingWidget::setItemHeight(int height)
{
    if(height > 0)
    {
        if(height == h)
            return;

        for(int i = 0;i < widgetlist.count();i++)
        {
            QWidget* w = widgetlist.at(i);
            QLabel* iconlabel = iconlabellist.at(i);
            QLabel* namelabel = namelabellist.at(i);
            QPushButton* pushbutton = pushbuttonlist.at(i);
            QComboBox* combobox = comboboxlist.at(i);
            QRadioButton* radiobutton = radiobuttonlist.at(i);
            Mode mode = modelist.at(i);
            QIcon icon = iconlist.at(i);
            QLineEdit* lineedit = lineeditlist.at(i);
            QSpinBox* spinbox = spinboxlist.at(i);
            QSlider* slider = sliderlist.at(i);
            QProgressBar* progressbar = progressbarlist.at(i);
            MySwitchButton* switchbutton = switchbuttonlist.at(i);
            w->resize(mainwidget->width(),height);
            w->move(0,height*i);

            QSize s1 = QSize((height-10.0)/3.0*5.0,height-10);
            if(mode == RadioButton)
            {
                s1.setWidth(s1.height());
            }
            else if(mode == ComboBox || mode == PushButton)
            {
                int w1 = 0;
                if(mode == ComboBox)
                {
                    w1 = combobox->width();
                }
                else
                {
                    w1 = pushbutton->width();
                }
                if(w1 > w->width()/2.0)
                    s1.setWidth(w->width()/2);
                else if(w1 > s1.width())
                    s1.setWidth(w1);
            }

            QWidget* target = nullptr;
            if(mode == PushButton)
                target = pushbutton;
            else if(mode == ComboBox)
                target = combobox;
            else if(mode == RadioButton)
                target = radiobutton;
            else if(mode == LineEdit)
                target = lineedit;
            else if(mode == SpinBox)
                target = spinbox;
            else if(mode == Slider)
                target = slider;
            else if(mode == ProgressBar)
                target = progressbar;
            else if(mode == SwitchButton)
                target = switchbutton;
            if(target != nullptr)
            {
                target->resize(s1);
                target->move(w->width()-5-target->width(),w->height()/2.0-target->height()/2.0);
            }

            QSize s2 = QSize(height-10,height-10);
            if(icon.isNull())
            {
                iconlabel->hide();
                namelabel->resize(w->width()/2-5,height-10);
                namelabel->move(5,5);
            }
            else
            {
                iconlabel->resize(s2);
                iconlabel->move(5,5);
                namelabel->resize(w->width()/2-iconlabel->x()-iconlabel->width(),iconlabel->width());
                namelabel->move(iconlabel->width()+iconlabel->x(),iconlabel->y());
                QPixmap p = icon.pixmap(s1);
                p = p.scaled(s1,Qt::KeepAspectRatio,Qt::SmoothTransformation);
                iconlabel->setPixmap(p);
            }
        }
        h = height;
    }
}
SettingWidget::Mode SettingWidget::mode(int index)
{
    if(index >= 0 && index < modelist.count())
        return modelist.at(index);
    else
        return InVaild;
}
void SettingWidget::setMode(int index, Mode newmode)
{
    if(index >= 0 && index < modelist.count() && newmode != InVaild)
    {
        QPushButton* pushbutton = pushbuttonlist.at(index);
        QComboBox* combobox = comboboxlist.at(index);
        QRadioButton* radiobutton = radiobuttonlist.at(index);
        QLineEdit* lineedit = lineeditlist.at(index);
        QSpinBox* spinbox = spinboxlist.at(index);
        QSlider* slider = sliderlist.at(index);
        QProgressBar* progressbar = progressbarlist.at(index);
        MySwitchButton* switchbutton = switchbuttonlist.at(index);
        modelist[index] = newmode;
        QWidget* target = nullptr;
        if(newmode == PushButton)
            target = pushbutton;
        else if(newmode == ComboBox)
            target = combobox;
        else if(newmode == RadioButton)
            target = radiobutton;
        else if(newmode == LineEdit)
            target = lineedit;
        else if(newmode == SpinBox)
            target = spinbox;
        else if(newmode == Slider)
            target = slider;
        else if(newmode == ProgressBar)
            target = progressbar;
        else if(newmode == SwitchButton)
            target = switchbutton;
        for(QWidget* w : QList<QWidget*>({pushbutton,combobox,radiobutton,lineedit,spinbox,slider,progressbar,switchbutton}))
            w->hide();
        if(target != nullptr)
            target->show();
        this->refreshUI();
    }
}
QString SettingWidget::name(int index)
{
    if(index >= 0 && index < keylist.count())
        return keylist.at(index);
    else
        return QString();
}
void SettingWidget::setName(int index, QString newname)
{
    if(index >= 0 && index < namelist.count())
    {
        QLabel* namelabel = namelabellist.at(index);
        namelabel->setText(newname);
        namelist[index] = newname;
    }
}
QIcon SettingWidget::icon(int index)
{
    if(index >= 0 && index < iconlist.count())
        return iconlist.at(index);
    else
        return QIcon();
}
void SettingWidget::setIcon(int index,QIcon icon)
{
    if(index >= 0 && index < iconlist.count())
    {
        iconlist[index] = icon;
        QLabel* iconlabel = iconlabellist.at(index);
        QLabel* namelabel = namelabellist.at(index);
        QSize s2 = QSize(h-10,h-10);
        if(icon.isNull())
        {
            iconlabel->hide();
            namelabel->move(5,5);
        }
        else
        {
            iconlabel->resize(s2);
            iconlabel->move(5,5);
            namelabel->move(iconlabel->width()+iconlabel->x(),iconlabel->y());
            QPixmap p = icon.pixmap(1000,1000);
            if(!p.isNull())
            {
                p = p.scaled(s2,Qt::KeepAspectRatio,Qt::SmoothTransformation);
                iconlabel->setPixmap(p);
                iconlabel->show();
            }
        }
    }
}
void SettingWidget::setItemEnabled(int index, bool on)
{
    if(index >= 0 && index < widgetlist.count())
    {
        QPushButton* pushbutton = pushbuttonlist.at(index);
        QComboBox* combobox = comboboxlist.at(index);
        QRadioButton* radiobutton = radiobuttonlist.at(index);
        QLineEdit* lineedit = lineeditlist.at(index);
        QSpinBox* spinbox = spinboxlist.at(index);
        QSlider* slider = sliderlist.at(index);
        QProgressBar* progressbar = progressbarlist.at(index);
        MySwitchButton* switchbutton = switchbuttonlist.at(index);

        for(QWidget* w : QList<QWidget*>({pushbutton,combobox,radiobutton,lineedit,spinbox,slider,progressbar,switchbutton}))
            w->setEnabled(on);
        enablelist[index] = on;
    }
}
bool SettingWidget::isItemEnabled(int index)
{
    if(index >= 0 && index < widgetlist.count())
    {
        QPushButton* pushbutton = pushbuttonlist.at(index);
        return pushbutton->isEnabled();
    }
    else
    {
        return false;
    }
}
void SettingWidget::removeItem(int index)
{
    if(index < 0 || index >= keylist.count())
        return;

    QWidget* widget = widgetlist.at(index);
    widget->close();
    for(int i = index + 1; i < widgetlist.count(); i++)
    {
        QWidget* w = widgetlist.at(i);
        w->move(w->x(),w->y()-h);
    }

    if(true)
    {
        keylist.removeAt(index);
        namelist.removeAt(index);
        modelist.removeAt(index);
        contentlist.removeAt(index);
        defaultvaluelist.removeAt(index);
        maxvaluelist.removeAt(index);
        minvaluelist.removeAt(index);
        tooltiplist.removeAt(index);
        iconlist.removeAt(index);
        widgetlist.removeAt(index);
        iconlabellist.removeAt(index);
        namelabellist.removeAt(index);
        pushbuttonlist.removeAt(index);
        comboboxlist.removeAt(index);
        radiobuttonlist.removeAt(index);
        spinboxlist.removeAt(index);
        lineeditlist.removeAt(index);
        enablelist.removeAt(index);
        sliderlist.removeAt(index);
        progressbarlist.removeAt(index);
        switchbuttonlist.removeAt(index);
    }
}
void SettingWidget::clear()
{
    for(QWidget* w : widgetlist)
        w->close();
    keylist.clear();
    namelist.clear();
    modelist.clear();
    contentlist.clear();
    defaultvaluelist.clear();
    maxvaluelist.clear();
    minvaluelist.clear();
    tooltiplist.clear();
    iconlist.clear();
    widgetlist.clear();
    iconlabellist.clear();
    namelabellist.clear();
    pushbuttonlist.clear();
    comboboxlist.clear();
    radiobuttonlist.clear();
    spinboxlist.clear();
    lineeditlist.clear();
    enablelist.clear();
    sliderlist.clear();
    progressbarlist.clear();
    switchbuttonlist.clear();
}
QPushButton* SettingWidget::pushButton(int index)
{
    if(index >= 0 && index < pushbuttonlist.count())
        return pushbuttonlist.at(index);
    else
        return nullptr;
}
QComboBox* SettingWidget::comboBox(int index)
{
    if(index >= 0 && index < comboboxlist.count())
        return comboboxlist.at(index);
    else
        return nullptr;
}
QRadioButton* SettingWidget::radioButton(int index)
{
    if(index >= 0 && index < radiobuttonlist.count())
        return radiobuttonlist.at(index);
    else
        return nullptr;
}
QLineEdit* SettingWidget::lineEdit(int index)
{
    if(index >= 0 && index < lineeditlist.count())
        return lineeditlist.at(index);
    else
        return nullptr;
}
QSpinBox* SettingWidget::spinBox(int index)
{
    if(index >= 0 && index < spinboxlist.count())
        return spinboxlist.at(index);
    else
        return nullptr;
}
QSlider* SettingWidget::slider(int index)
{
    if(index >= 0 && index < sliderlist.count())
        return sliderlist.at(index);
    else
        return nullptr;
}
QProgressBar* SettingWidget::progressbar(int index)
{
    if(index >= 0 && index < progressbarlist.count())
        return progressbarlist.at(index);
    else
        return nullptr;
}
MySwitchButton* SettingWidget::switchbutton(int index)
{
    if(index >= 0 && index < switchbuttonlist.count())
        return switchbuttonlist.at(index);
    else
        return nullptr;
}
