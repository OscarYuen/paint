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
#include <qbrush.h>
#include <qslider.h> 
#include <qdialog.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>

#ifndef _MY_RECT_DIALOG_H
#define _MY_RECT_DIALOG_H

// The QDialog class provides a dialog window for communications with user

class MyRectDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyRectDialog(QWidget* parent = 0, const char* name = 0);
      ~MyRectDialog();

      /** for storing the pen settings */
      QPen pen;
      QBrush brush;
      int drawtype;
      int colormode;
      QColor fcolor;
   /** user defined slots */
   public slots:
      void OnSetBoundaryWidth(int w);
      void OnSetDrawType(int type);
      void OnSetFillStyle(int type);
      void OnSetBoundaryStyle(int type);
      void OnSetJoinStyle(int type);
      void OnSetFillColor(int type);
   
   private:
      // Slider pointer
      QSlider* widthslider;
      // Slider labels
      QLabel* wl;
      QLabel* widthlabel;

      // Style button pointers
      QButtonGroup* drawtypebgroup;
      QRadioButton *rb_rect;
      QRadioButton *rb_roundrect;
      QRadioButton *rb_circle;
      QRadioButton *rb_ellipse;
      
      QButtonGroup* fillstylebgroup;
      QRadioButton *rb_solid;
      QRadioButton *rb_dense1;
      QRadioButton *rb_dense2;
      QRadioButton *rb_dense3;
      QRadioButton *rb_dense4;
      QRadioButton *rb_dense5;
      QRadioButton *rb_dense6;
      QRadioButton *rb_dense7;
      QRadioButton *rb_horizontal;
      QRadioButton *rb_vertical;
      QRadioButton *rb_cross;
      QRadioButton *rb_bdiag;
      QRadioButton *rb_fdiag;
      QRadioButton *rb_cdiag;
      QRadioButton *rb_nopattern;

      QButtonGroup* bstylebgroup;
      QRadioButton *rb_solidline;
      QRadioButton *rb_dash;
      QRadioButton *rb_dot;
      QRadioButton *rb_dashdot;
      QRadioButton *rb_dashdotdot;
      QRadioButton *rb_noline;

      QButtonGroup* joinstylebgroup;
      QRadioButton *rb_miterjoin;
      QRadioButton *rb_beveljoin;
      QRadioButton *rb_roundjoin;

      QButtonGroup* fillcolorbgroup;
      QRadioButton *rb_fcolor;
      QRadioButton *rb_bcolor;

};

#endif
