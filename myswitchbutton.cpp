#include "myswitchbutton.h"

MySwitchButton::MySwitchButton(QWidget *parent)
    : QLabel{parent}
{
    setAttribute(Qt::WA_TransparentForMouseEvents,false);
    label = new QLabel(this);
    this->resize(70,30);
    this->setColor(Windows);
    this->installEventFilter(this);
    this->setAutoFillBackground(false);
    this->refreshUI();
}
bool MySwitchButton::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            this->refreshUI();
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            if(!on && this->isEnabled())
            {
                QColor c;
                c.setRed(offcolor.red()>20 ? offcolor.red()-20 : 0);
                c.setGreen(offcolor.green()>20 ? offcolor.green()-20 : 0);
                c.setBlue(offcolor.blue()>20 ? offcolor.blue()-20 : 0);
                this->setStyleSheet("background-color:"+toString(c)+";border-radius:"+QString::number(this->height()/2)+"px");
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            QPoint p = e->pos();
            if(p.x() >= 0 && p.y() >= 0 && p.x() < this->width() && p.y() < this->height() && this->isEnabled())
            {
                this->setChecked(!on);
                return true;
            }
            this->refreshUI();
        }
    }
    return QWidget::eventFilter(watched,event);
}
void MySwitchButton::refreshUI()
{
    QColor c;
    if(on)
        c = oncolor;
    else
        c = offcolor;
    this->setStyleSheet("background-color:"+toString(c)+";border-radius:"+QString::number(this->height()/2)+"px");
    label->resize(this->height()-10,this->height()-10);
    label->setStyleSheet("background-color:"+toString(labelcolor)+";border-radius:"+QString::number(label->height()/2)+"px");
    if(on)
        label->move(this->width()-this->height()/2-label->height()/2,this->height()/2-label->height()/2);
    else
        label->move(this->height()/2-label->height()/2,this->height()/2-label->height()/2);
}
void MySwitchButton::setColor(ColorStyle style)
{
    if(style == HuaweiHonor)
        this->setColor(QColor(56,113,255),QColor(228,228,228),QColor(255,255,255));
    else if(style == Apple)
        this->setColor(QColor(101,196,103),QColor(201,201,201),QColor(255,255,255));
    else if(style == NativeAndroid)
        this->setColor(QColor(0,102,135),QColor(101,108,112),QColor(255,255,255,125));
    else if(style == Windows)
        this->setColor(QColor(0,103,192),QColor(230,230,230),QColor(255,255,255));
}
void MySwitchButton::setChecked(bool check)
{
    on = check;
    emit clicked(on);
    if(animation)
    {
        int delta_x = (this->width()-this->height()/2-label->height()/2) - (this->height()/2-label->height()/2);
        int delta_red = oncolor.red()-offcolor.red();
        int delta_green = oncolor.green()-offcolor.green();
        int delta_blue = oncolor.blue()-offcolor.blue();
        int delta_alpha = oncolor.alpha()-offcolor.alpha();

        double speed_x = double(delta_x) / double(time);
        double speed_red = double(delta_red) / double(time);
        double speed_green = double(delta_green) / double(time);
        double speed_blue = double(delta_blue) / double(time);
        double speed_alpha = double(delta_alpha) / double(time);

        int step_x = speed_x * time_step;
        int step_red = speed_red * time_step;
        int step_green = speed_green * time_step;
        int step_blue = speed_blue * time_step;
        int step_alpha = speed_alpha * time_step;
        int t = time / time_step;
        int r = time % time_step;

        QEventLoop* loop = new QEventLoop(this);
        QColor c = on ? offcolor : oncolor;
        for(int i = 0; i < t; i++)
        {
            if(on)
            {
                c = QColor(c.red()+step_red,c.green()+step_green,c.blue()+step_blue,c.alpha()+step_alpha);
                label->move(label->x()+step_x,label->y());
            }
            else
            {
                c = QColor(c.red()-step_red,c.green()-step_green,c.blue()-step_blue,c.alpha()-step_alpha);
                label->move(label->x()-step_x,label->y());
            }
            this->setStyleSheet("background-color:"+toString(c)+";border-radius:"+QString::number(this->height()/2)+"px");
            QTimer::singleShot(time_step,[=](){
                loop->quit();
            });
            loop->exec();
            this->update();
        }
        QTimer::singleShot(r,[=](){
            loop->quit();
        });
        loop->exec();
        delete loop;
    }
    else
    {
        this->refreshUI();
    }
}
