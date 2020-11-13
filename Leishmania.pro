include("Moonfit/moonfit.pri")

#name of the executable file generated
TARGET = LeishmaniaExe

#put += console to run in a separate terminal
#CONFIG += console

#bundles might be required for MAC OS ??
#CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    Leishmania/Models/modeleLeishmaniaMajor.h \
    Leishmania/expLeishmania.h

SOURCES += \
    Leishmania/Script13Jan2017.cpp \
    Leishmania/Models/modeleLeishmaniaMajor.cpp

DISTFILES += \
    TasosLMajor/DATA/configLMajor.txt \
    TasosLMajor/DATA/Data_new.txt \
    TasosLMajor/DATA/DataStd_new.txt
