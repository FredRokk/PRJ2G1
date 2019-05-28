MAKEFILE      = Makefile

CXX           = /opt/poky/2.6/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++  -march=armv6 -mfpu=vfp  -mfloat-abi=hard -mtune=arm1176jzf-s -mfpu=vfp --sysroot=/opt/poky/2.6/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi
DEFINES       = -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CXXFLAGS      = -pipe -O2 -pipe -g -feliminate-unused-debug-types --sysroot=/opt/poky/2.6/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I../src -I. -I/opt/poky/2.6/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi/usr/include/QtWidgets -I/opt/poky/2.6/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi/usr/include/QtGui -I/opt/poky/2.6/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi/usr/include/QtCore -I. -I/mnt/extra/embedded/rpiwz_bb_e2018/raspberrypi0-wifi/compilation/work/arm1176jzfshf-vfp-poky-linux-gnueabi/qtbase/5.11.2+gitAUTOINC+49efea26a5-r0/recipe-sysroot/usr/include/interface/vmcs_host/linux -I/mnt/extra/embedded/rpiwz_bb_e2018/raspberrypi0-wifi/compilation/work/arm1176jzfshf-vfp-poky-linux-gnueabi/qtbase/5.11.2+gitAUTOINC+49efea26a5-r0/recipe-sysroot/usr/include/interface/vcos/pthreads -I. -I/opt/poky/2.6/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi/usr/lib/mkspecs/linux-oe-g++
LINK		  = arm-poky-linux-gnueabi-g++  --sysroot=/opt/poky/2.6/sysroots/arm1176jzfshf-vfp-poky-linux-gnueabi
LIBS          = -lQt5Widgets -lQt5Gui -lQt5Core -lGLESv2 -lbcm_host -lvcos -lvchiq_arm -lpthread -latomic

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../src/main.cpp \
		../src/idle.cpp \
		../src/mapselect.cpp \
		../src/practice.cpp \
		../src/versus.cpp \
		../src/results.cpp \
		../src/playeronehighscore.cpp \
		../src/playertwohighscore.cpp moc_idle.cpp \
		moc_mapselect.cpp \
		moc_practice.cpp \
		moc_versus.cpp \
		moc_results.cpp \
		moc_playeronehighscore.cpp \
		moc_playertwohighscore.cpp
OBJECTS       = main.o \
		idle.o \
		mapselect.o \
		practice.o \
		versus.o \
		results.o \
		playeronehighscore.o \
		playertwohighscore.o \
		moc_idle.o \
		moc_mapselect.o \
		moc_practice.o \
		moc_versus.o \
		moc_results.o \
		moc_playeronehighscore.o \
		moc_playertwohighscore.o

TARGET        = CanoneersQt


first: all

$(TARGET): ui_idle.h ui_mapselect.h ui_practice.h ui_versus.h ui_results.h ui_playeronehighscore.h ui_playertwohighscore.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

all: $(TARGET)

moc_predefs.h: /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -g -Wall -W -dM -E -o moc_predefs.h /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp

moc_idle.cpp: ../src/idle.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include ./moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/stud/PRJ3/PRJ3G2/RPI/qt/src -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/include/c++/8 -I/usr/include/x86_64-linux-gnu/c++/8 -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-linux-gnu/8/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include ../src/idle.h -o moc_idle.cpp

moc_mapselect.cpp: ../src/mapselect.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include ./moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/stud/PRJ3/PRJ3G2/RPI/qt/src -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/include/c++/8 -I/usr/include/x86_64-linux-gnu/c++/8 -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-linux-gnu/8/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include ../src/mapselect.h -o moc_mapselect.cpp

moc_practice.cpp: ../src/practice.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include ./moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/stud/PRJ3/PRJ3G2/RPI/qt/src -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/include/c++/8 -I/usr/include/x86_64-linux-gnu/c++/8 -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-linux-gnu/8/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include ../src/practice.h -o moc_practice.cpp

moc_versus.cpp: ../src/versus.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include ./moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/stud/PRJ3/PRJ3G2/RPI/qt/src -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/include/c++/8 -I/usr/include/x86_64-linux-gnu/c++/8 -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-linux-gnu/8/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include ../src/versus.h -o moc_versus.cpp

moc_results.cpp: ../src/results.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include ./moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/stud/PRJ3/PRJ3G2/RPI/qt/src -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/include/c++/8 -I/usr/include/x86_64-linux-gnu/c++/8 -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-linux-gnu/8/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include ../src/results.h -o moc_results.cpp

moc_playeronehighscore.cpp: ../src/playeronehighscore.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include ./moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/stud/PRJ3/PRJ3G2/RPI/qt/src -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/include/c++/8 -I/usr/include/x86_64-linux-gnu/c++/8 -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-linux-gnu/8/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include ../src/playeronehighscore.h -o moc_playeronehighscore.cpp

moc_playertwohighscore.cpp: ../src/playertwohighscore.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include ./moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/stud/PRJ3/PRJ3G2/RPI/qt/src -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/include/c++/8 -I/usr/include/x86_64-linux-gnu/c++/8 -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-linux-gnu/8/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include ../src/playertwohighscore.h -o moc_playertwohighscore.cpp

ui_idle.h: ../src/idle.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic ../src/idle.ui -o ui_idle.h

ui_mapselect.h: ../src/mapselect.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic ../src/mapselect.ui -o ui_mapselect.h

ui_practice.h: ../src/practice.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic ../src/practice.ui -o ui_practice.h

ui_versus.h: ../src/versus.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic ../src/versus.ui -o ui_versus.h

ui_results.h: ../src/results.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic ../src/results.ui -o ui_results.h

ui_playeronehighscore.h: ../src/playeronehighscore.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic ../src/playeronehighscore.ui -o ui_playeronehighscore.h

ui_playertwohighscore.h: ../src/playertwohighscore.ui \
		/usr/lib/qt5/bin/uic
	/usr/lib/qt5/bin/uic ../src/playertwohighscore.ui -o ui_playertwohighscore.h


main.o: ../src/main.cpp ../src/idle.h \
		../src/mapselect.h \
		../src/practice.h \
		../src/versus.h \
		../src/results.h \
		../src/playeronehighscore.h \
		../src/playertwohighscore.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../src/main.cpp

idle.o: ../src/idle.cpp ../src/idle.h \
		ui_idle.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o idle.o ../src/idle.cpp

mapselect.o: ../src/mapselect.cpp ../src/mapselect.h \
		ui_mapselect.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mapselect.o ../src/mapselect.cpp

practice.o: ../src/practice.cpp ../src/practice.h \
		ui_practice.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o practice.o ../src/practice.cpp

versus.o: ../src/versus.cpp ../src/versus.h \
		ui_versus.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o versus.o ../src/versus.cpp

results.o: ../src/results.cpp ../src/results.h \
		ui_results.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o results.o ../src/results.cpp

playeronehighscore.o: ../src/playeronehighscore.cpp ../src/playeronehighscore.h \
		ui_playeronehighscore.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playeronehighscore.o ../src/playeronehighscore.cpp

playertwohighscore.o: ../src/playertwohighscore.cpp ../src/playertwohighscore.h \
		ui_playertwohighscore.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playertwohighscore.o ../src/playertwohighscore.cpp

moc_idle.o: moc_idle.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_idle.o moc_idle.cpp

moc_mapselect.o: moc_mapselect.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mapselect.o moc_mapselect.cpp

moc_practice.o: moc_practice.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_practice.o moc_practice.cpp

moc_versus.o: moc_versus.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_versus.o moc_versus.cpp

moc_results.o: moc_results.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_results.o moc_results.cpp

moc_playeronehighscore.o: moc_playeronehighscore.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playeronehighscore.o moc_playeronehighscore.cpp

moc_playertwohighscore.o: moc_playertwohighscore.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playertwohighscore.o moc_playertwohighscore.cpp

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OBJECTS) $(TARGET) ui_*.h moc_*.cpp moc_predefs.h 
