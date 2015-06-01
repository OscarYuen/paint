/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_pendialog.cpp
//  Description: the source file
//  -- MyPenDialog class implementation 
//     customizing the QDialog class for the Pen tool
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_eraserdialog.h"

#include <qpainter.h>
#include <qmessagebox.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qtextedit.h>
#include <qmessagebox.h>
#include <qprinter.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>

MyEraserDialog::MyEraserDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // For setting the line's captstyle
   // Create a button group to contain all buttons
   // For setting the line width
   size = 10;
   sizeslider = new QSlider( QSlider::Horizontal, this, "size slider" );
   sizeslider->setRange ( 10, 100 );
   sizeslider->setLineStep ( 1 );
   sizeslider->setValue ( size );
   sizeslider->setGeometry  ( 50, 0, 190,30 );
   sizeslider->setTickmarks( QSlider::Below );
   sizeslider->setTickInterval( 15 );

   connect( sizeslider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetEraserSize(int)) );

   sl = new QLabel( this );
   sl->setGeometry( 10,0,40,30 );
   sl->setText( "Size" );

   sizelabel = new QLabel( this );
   sizelabel->setGeometry( 250, 0, 30, 30 );
   char sizesldrvalue[1024];
   sprintf( sizesldrvalue,"%d",sizeslider->value() );
   sizelabel->setText( sizesldrvalue );

   resize(280,40);
}

MyEraserDialog::~MyEraserDialog()
{
   delete sizeslider;
   delete sizelabel;
   delete sl;
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the eraser size
void MyEraserDialog::OnSetEraserSize(int s)
{
   char sizesldrvalue[1024];
   sprintf( sizesldrvalue,"%d",s );
   sizelabel->setText( sizesldrvalue );

   size = s;
}

