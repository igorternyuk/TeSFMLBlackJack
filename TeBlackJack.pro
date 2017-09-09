TEMPLATE = app
CONFIG += c++1z
CONFIG -= app_bundle
CONFIG -= qt

DEFINES -= DEBUG

LIBS += `pkg-config --libs sfml-all`

SOURCES += main.cpp \
    card.cpp \
    hand.cpp \
    abstractplayer.cpp \
    deck.cpp \
    dealer.cpp \
    player.cpp \
    model.cpp \
    controller.cpp \
    view.cpp \
    random.cpp

HEADERS += \
    card.h \
    hand.h \
    abstractplayer.h \
    deck.h \
    dealer.h \
    player.h \
    model.h \
    controller.h \
    view.h \
    modellistener.h \
    random.h \
    utils.h \
    constantmodelinterface.h
