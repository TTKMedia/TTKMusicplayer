include($$PWD/../../plugins.pri)

HEADERS += decodermodplugfactory.h \
           decoder_modplug.h \
           archivereader.h \
           modplugmetadatamodel.h \
           settingsdialog.h
    
SOURCES += decodermodplugfactory.cpp \
           decoder_modplug.cpp \
           archivereader.cpp \
           modplugmetadatamodel.cpp \
           settingsdialog.cpp

FORMS += settingsdialog.ui

DESTDIR = $$PLUGINS_PREFIX/Input
TARGET = $${TARGET}

DEFINES += HAVE_STDINT_H \
           HAVE_INTTYPES_H
           
INCLUDEPATH += $$EXTRA_PREFIX/libmodplug/include

unix {
    QMAKE_CLEAN = $$DESTDIR/lib$${TARGET}.so
    LIBS += -L$$EXTRA_PREFIX/libmodplug/lib -lmodplug$$STATIC_LIBRARY_SUFFIX -lunmo3
}

win32 {
    contains(CONFIG, USE_STATIC_LIBRARY){
        DEFINES += MODPLUG_STATIC
    }
    LIBS += -L$$EXTRA_PREFIX/libmodplug/lib -lmodplug -lunmo3 -Wl,--enable-stdcall-fixup
    DEFINES -= UNICODE
}