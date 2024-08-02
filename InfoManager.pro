QT       += core gui core-private gui-private concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(QXlsx/QXlsx.pri)
CONFIG += resources_big
DEFINES += QT_MESSAGELOGCONTEXT
msvc {
      QMAKE_CFLAGS += /utf-8
      QMAKE_CXXFLAGS += /utf-8
}
windows {
RC_ICONS = icon.ico
}
linux {
}
unix {
}
android {
ANDROID_TARGET_SDK_VERSION = 31
LIBS += -ljnigraphics
DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/xml/qtprovider_paths.xml \
    android/src/com/MainActivity.java
}
CONFIG += c++17
SOURCES += \
    main.cpp \
    myfiledialog.cpp \
    myswitchbutton.cpp \
    settingwidget.cpp \
    widget.cpp
HEADERS += \
    api.h \
    myfiledialog.h \
    mynativeeventfilter.h \
    myswitchbutton.h \
    settingwidget.h \
    widget.h
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
RESOURCES += \
    resource.qrc
