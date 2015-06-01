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

#ifndef _MY_LINE_DIALOG_H
#define _MY_LINE_DIALOG_H

// MyPenDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyLineDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyLineDialog(QWidget* parent = 0, const char* name = 0);
      ~MyLineDialog();

      /** for storing the pen settings */
      QPen pen;
      int linetype;
      int count;
   /** user defined slots */
   public slots:
      void OnSetPenWidth(int w);
      void OnSetCapStyle(int type);
      void OnSetLineStyle(int type);
      void OnSetConnectStyle(int type);
      void ChangeSetChecked();
   private:
      // Slider pointer
      QSlider* widthslider;
      // Slider labels
      QLabel* wl;
      QLabel* widthlabel;

      // Style button pointers
      QButtonGroup* capstylebgroup;
      QRadioButton *rb_flatcap;
      QRadioButton *rb_squarecap;
      QRadioButton *rb_roundcap;
      
      QButtonGroup* linestylebgroup;
      QRadioButton *rb_solidline;
      QRadioButton *rb_dashline;
      QRadioButton *rb_dotline;
      QRadioButton *rb_dashdotline;
      QRadioButton *rb_dashdotdotline;
      
      QButtonGroup* connectbgroup;
      QRadioButton *rb_singleline;
      QRadioButton *rb_polyline;
};

#endif
