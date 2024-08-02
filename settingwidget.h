#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include "api.h"
#include "myswitchbutton.h"

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);
    enum Mode
    {
        Empty,
        PushButton,
        ComboBox,
        RadioButton,
        LineEdit,
        SpinBox,
        Slider,
        ProgressBar,
        SwitchButton,
        InVaild
    };
    bool eventFilter(QObject *watched, QEvent *event);
    bool addItem(QString key, QString name, Mode mode, QVariant content = QVariant(), QVariant defaultValue = QVariant(), QIcon icon = QIcon(), QString tooltip = QString(), QVariant min_value = QVariant(), QVariant max_value = QVariant(), bool enable = true);
    void removeItem(QString key) {return removeItem(keylist.indexOf(key));}
    void removeItem(int index);
    void clear();
    void setItemHeight(int height);
    int itemHeight() {return h;}
    QStringList allkeys() {return keylist;}
    int count() {return keylist.count();}
    QString name(int index);
    QString name(QString key){return name(keylist.indexOf(key));}
    void setName(int index,QString newname);
    void setName(QString key,QString newname) {return setName(keylist.indexOf(key),newname);}
    Mode mode(int index);
    Mode mode(QString key) {return mode(keylist.indexOf(key));}
    void setMode(int index,Mode newmode);
    void setMode(QString key,Mode newmode) {return setMode(keylist.indexOf(key),newmode);}
    QIcon icon(int index);
    QIcon icon(QString key) {return icon(keylist.indexOf(key));}
    void setIcon(int index,QIcon icon);
    void setIcon(QString key,QIcon icon) {return setIcon(keylist.indexOf(key),icon);}
    QPushButton* pushButton(int index);
    QPushButton* pushButton(QString key) {return pushButton(keylist.indexOf(key));}
    QComboBox* comboBox(int index);
    QComboBox* comboBox(QString key) {return comboBox(keylist.indexOf(key));}
    QRadioButton* radioButton(int index);
    QRadioButton* radioButton(QString key) {return radioButton(keylist.indexOf(key));}
    QLineEdit* lineEdit(int index);
    QLineEdit* lineEdit(QString key) {return lineEdit(keylist.indexOf(key));}
    QSpinBox* spinBox(int index);
    QSpinBox* spinBox(QString key) {return spinBox(keylist.indexOf(key));}
    QSlider* slider(int index);
    QSlider* slider(QString key) {return slider(keylist.indexOf(key));}
    QProgressBar* progressbar(int index);
    QProgressBar* progressbar(QString key) {return progressbar(keylist.indexOf(key));}
    MySwitchButton* switchbutton(int index);
    MySwitchButton* switchbutton(QString key) {return switchbutton(keylist.indexOf(key));}
    void setItemEnabled(int index,bool on);
    void setItemEnabled(QString key,bool on) {return setItemEnabled(keylist.indexOf(key),on);}
    bool isItemEnabled(int index);
    bool isItemEnabled(QString key) {return isItemEnabled(keylist.indexOf(key));}
signals:
    void itemClicked(int index,QString key);
    void itemDoubleClicked(int index,QString key);
    void itemRightButtonClicked(int index,QString key);
    void pushButtonClicked(int index,QString key);
    void radioButtonClicked(int index,QString key,bool check);
    void comboBoxChanged(int index,QString key,int currentIndex,QString currentText);
    void lineEditTextChanged(int index,QString key,QString currentText);
    void sliderValueChanged(int index,QString key,int currentValue);
    void spinboxValueChanged(int index,QString key,int currentValue);
    void progressbarValueChanged(int index,QString key,int currentValue);
    void switchButtonClicked(int index,QString key,bool check);
private slots:
    void refreshUI();
private:
    QTime time;
    QPoint p1;
    int h = 40;

    QScrollArea* area;
    QWidget* mainwidget;
    QList<QString> keylist;
    QList<QString> namelist;
    QList<Mode> modelist;
    QList<QIcon> iconlist;
    QList<QVariant> contentlist;
    QList<QVariant> defaultvaluelist;
    QList<QVariant> minvaluelist;
    QList<QVariant> maxvaluelist;
    QList<QString> tooltiplist;
    QList<bool> enablelist;

    QList<QWidget*> widgetlist;
    QList<QLabel*> iconlabellist;
    QList<QLabel*> namelabellist;
    QList<QPushButton*> pushbuttonlist;
    QList<QComboBox*> comboboxlist;
    QList<QRadioButton*> radiobuttonlist;
    QList<QLineEdit*> lineeditlist;
    QList<QSpinBox*> spinboxlist;
    QList<QSlider*> sliderlist;
    QList<QProgressBar*> progressbarlist;
    QList<MySwitchButton*> switchbuttonlist;
};

#endif // SETTINGWIDGET_H
