# -------------------------------------------------
# Project created by QtCreator 2010-01-09T13:17:20
# -------------------------------------------------
TARGET = DM
TEMPLATE = app
SOURCES += main.cpp \
    dmwindow.cpp \
    calculations/Tab2.cpp \
    calculations/Tab3.cpp \
    calculations/Tab4.cpp \
    calculations/Tab5.cpp \
    calculations/Tab6.cpp
HEADERS += dmwindow.h \
    defines/table2.h \
    defines/table1.h \
    defines/var.h \
    defines/table3.h \
    defines/table4.h
FORMS += dmwindow.ui
RESOURCES += chemes.qrc
win32 {
    #RC_FILE = resources/icon.rc
}
else:macx {
    RC_FILE = resources/icon.icns
}
else {
    RC_FILE = resources/icon.rc
}
