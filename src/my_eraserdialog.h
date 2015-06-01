/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_pendialog.h
//  Description: the header file
//  -- MyPenDialog class definition
//     customizing the QDialog class for the Pen tool
/****************************************/

#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qpen.h>
#include <qslider.h> 
#include <qdialog.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>

#ifndef _MY_ERASER_DIALOG_H
#define _MY_ERASER_DIALOG_H

// The QDialog class provides a dialog window for communications with user

class MyEraserDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyEraserDialog(QWidget* parent = 0, const char* name = 0);
      ~MyEraserDialog();

      /** for storing the pen settings */
      int size;

   /** user defined slots */
   public slots:
      void OnSetEraserSize(int s);
   
   private:
      // Slider pointer
      QSlider* sizeslider;
      // Slider labels
      QLabel* sl;
      QLabel* sizelabel;
      
};

#endif
