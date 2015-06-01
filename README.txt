/***********************Read Me**********************/
Version: 1.1
Configuration instructions:

To compile using QT 3.2, add the following alias in your ~/.cshrc_user:
alias qmake /usr/lib64/qt-3.3/bin/qmake

To define the required environment variables for Qt, add also the following lines to your ~/.cshrc_user , or you can simply run the command. bullet	setenv QMAKESPEC linux-g++-64
QMAKESPEC is used by qmake. 
It defines what is the target platform (for example: Windows or Linux) and compiler (for example: Microsoft Visual C++ or g++).
--------------------------------------------------------
Installation instructions:

After unzipping, FTP the whole directory to your linux account.

First type the following command to complie the source code.
1. qmake -project
2. qmake
3. gmake
--------------------------------------------------------
Operating instructions:

To run the program, you should "chmod" the executable:
% chmod 750 paint
After that, type "paint" on the command prompt.
--------------------------------------------------------
List of files included:
-cpp files:
	-main.cpp
	-my_pendialog.cpp
	-my_rectdialog.cpp
	-my_linedialog.cpp
	-my_eraserdialog.cpp
	-my_toolbar.cpp
	-my_widget.cpp
	-moc_my_pendialog.cpp
	-moc_my_rectdialog.cpp
	-moc_my_linedialog.cpp
	-moc_my_eraserdialog.cpp
	-moc_my_toolbar.cpp
	-moc_my_widget.cpp
-header files
	-my_pendialog.h
	-my_rectdialog.h
	-my_linedialog.h
	-my_eraserdialog.h
	-my_toolbar.h
	-my_widget.h
-pro files
	-paint.pro
-bmp files
	-bcolor_icon.bmp
	-bitmap.bmp
	-clearall_icon.bmp
	-eraser_icon.bmp
	-fcolor_icon.bmp
	-line_icon.bmp
	-new_icon.bmp
	-open_icon.bmp
	-pen_icon.bmp
	-rect_icon.bmp
	-redo_icon.bmp
	-resize_icon.bmp
	-save_icon.bmp
	-undo_icon.bmp
-Other
	-MakeFile
--------------------------------------------------------
Known bugs:
None
--------------------------------------------------------
