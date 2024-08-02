#ifndef MYNATIVEEVENTFILTER_H
#define MYNATIVEEVENTFILTER_H
#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QApplication>
#ifdef Q_OS_WIN
#include <windows.h>
#include <dbt.h>
#endif
class MyNativeEventFilter : public QObject , public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    MyNativeEventFilter() {}

    enum EventType
    {
        Windows_Generic_Event,
        Windows_Dispatcher_Event,
        X11_Generic_Event,
        Mac_Generic_Event,
        Invaild
    };
    void install() {qApp->installNativeEventFilter(this);}
    void remove() {qApp->removeNativeEventFilter(this);}
    static EventType toEventType(QByteArray b)
    {
        if(b == "windows_generic_MSG")
            return Windows_Generic_Event;
        else if(b == "windows_dispatcher_MSG")
            return Windows_Dispatcher_Event;
        else if(b == "xcb_generic_event_t")
            return X11_Generic_Event;
        else if(b == "mac_generic_NSEvent")
            return Mac_Generic_Event;
        else
            return Invaild;
    }
#ifndef Q_OS_WIN
typedef void MSG;
typedef qintptr LRESULT;
#endif
    static MSG* toMSG(void* message)
    {
#ifdef Q_OS_WIN
        MSG* msg = static_cast<MSG*>(message);
        return msg;
#else
        return message;
#endif
    }
    static LRESULT* toLRESULT(qintptr* ptr)
    {
#ifdef Q_OS_WIN
        LRESULT* ret = static_cast<LRESULT*>(ptr);
        return ret;
#else
        return ptr;
#endif
    }
#if QT_VERSION_MAJOR == 6
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override
    {
        qintptr* ptr = result;
#else
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override
    {
        qintptr* ptr = reinterpret_cast<qintptr*>(result);
#endif
        EventType type = toEventType(eventType);
        emit nativeEventFilterUpdated(type,message,ptr);
#ifdef Q_OS_WIN
        MSG* msg = toMSG(message);
        LRESULT* ret = toLRESULT(ptr);
        emit winEvent(msg,ret);
        if(msg->message == 563)
        {
            emit winDropEvent(msg,ret);
        }
        else if(msg->message == WM_DEVICECHANGE)
        {
            if(msg->wParam == DBT_DEVICEREMOVECOMPLETE)
            {
                emit winDeviceRemove(msg,ret);
            }
            else if(msg->wParam == DBT_DEVICEARRIVAL)
            {
                emit winDeviceArrival(msg,ret);
            }
        }
#endif
        return false;
    }

signals:
    void nativeEventFilterUpdated(EventType type,void *message,qintptr *result);
    void winEvent(MSG* msg,LRESULT* result);
    void winDropEvent(MSG* msg,LRESULT* result);
    void winDeviceRemove(MSG* msg,LRESULT* result);
    void winDeviceArrival(MSG* msg,LRESULT* result);
};

#endif // MYNATIVEEVENTFILTER_H
