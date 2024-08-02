#ifndef MYSWITCHBUTTON_H
#define MYSWITCHBUTTON_H

#include <QWidget>
#include "api.h"

class MySwitchButton : public QLabel
{
    Q_OBJECT
public:
    explicit MySwitchButton(QWidget *parent = nullptr);
    enum ColorStyle
    {
        Apple,
        HuaweiHonor,
        NativeAndroid,
        Windows,
        Invaild
    };
    bool eventFilter(QObject *watched, QEvent *event);
    void setChecked(bool check);
    bool isChecked() {return on;}
    void setAnimationEnabled(bool enable) {animation = enable;}
    bool isAnimationEnabled() {return animation;}
    void setColor(QColor on_color,QColor off_color,QColor center_color) {oncolor=on_color;offcolor=off_color;labelcolor=center_color;}
    void setColor(QList<QColor> list) {return setColor(list.at(0),list.at(1),list.at(2));}
    void setColor(ColorStyle style);
    QList<QColor> color() {return QList<QColor>({oncolor,offcolor,labelcolor});}
    void setOnColor(QColor c) {oncolor = c;}
    QColor onColor() {return oncolor;}
    void setOffColor(QColor c) {offcolor = c;}
    QColor offColor() {return offcolor;}
    void setCenterColor(QColor c) {labelcolor = c;}
    QColor centerColor() {return labelcolor;}
signals:
    void clicked(bool check);
private slots:
    void refreshUI();
private:
    QColor oncolor = QColor(56,113,255);
    QColor offcolor = QColor(228,228,228);
    QColor labelcolor = QColor(255,255,255);
    QLabel* label;
    int time = 100;
    int time_step = 20;
    bool on = false;
    bool animation = true;
};

#endif // MYSWITCHBUTTON_H
