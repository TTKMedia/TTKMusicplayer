include($$PWD/../zed.pri)
include($$PWD/../common/common.pri)

DESTDIR = $$PLUGINS_PREFIX/Input
TARGET = $${TARGET}

HEADERS += decoderdcafactory.h \
           decoder_dca.h \
           dcahelper.h
    
SOURCES += decoderdcafactory.cpp \
           decoder_dca.cpp \
           dcahelper.cpp

INCLUDEPATH += $$EXTRA_PREFIX/libdca/include

unix{
    QMAKE_CLEAN = $$DESTDIR/lib$${TARGET}.so
    LIBS += -L$$EXTRA_PREFIX/libdca/lib -ldca$$STATIC_LIBRARY_SUFFIX
}

win32{
    LIBS += -L$$EXTRA_PREFIX/libdca/lib -ldca
}
