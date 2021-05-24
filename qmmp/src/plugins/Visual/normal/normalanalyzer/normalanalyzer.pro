include($$PWD/../../Visual.pri)

DESTDIR = $$PLUGINS_PREFIX/Visual
TARGET = $${TARGET}

HEADERS += normalanalyzer.h \
           visualnormalanalyzerfactory.h
           
SOURCES += normalanalyzer.cpp \
           visualnormalanalyzerfactory.cpp

unix{
    QMAKE_CLEAN = $$DESTDIR/lib$${TARGET}.so
}