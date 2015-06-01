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

#include "my_linedialog.h"

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

MyLineDialog::MyLineDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // For setting the line's captstyle
   // Create a button group to contain all buttons
   linestylebgroup = new QButtonGroup( this );
   linestylebgroup->setGeometry( 10, 0, 160, 200 );
   linestylebgroup->setTitle ( "Line Style" );
   connect( linestylebgroup, SIGNAL(clicked(int)), SLOT(OnSetLineStyle(int)) );
  
   rb_solidline = new QRadioButton( "Solid Line", linestylebgroup );
   rb_solidline->setGeometry( 10, 30, 140, 20 );

   rb_dashline = new QRadioButton( "Dashed Line", linestylebgroup );
   rb_dashline->setGeometry( 10, 60, 140, 20 );

   rb_dotline = new QRadioButton( "Dotted Line", linestylebgroup );
   rb_dotline->setGeometry( 10, 90, 140, 20 );

   rb_dashdotline = new QRadioButton( "Dash Dot Line", linestylebgroup );
   rb_dashdotline->setGeometry( 10, 120, 140, 20 );

   rb_dashdotdotline = new QRadioButton( "Dash Dot Dot Line", linestylebgroup );
   rb_dashdotdotline->setGeometry( 10, 150, 140, 20 );

   pen.setStyle( Qt::SolidLine );
   switch( pen.style() ){
      
      case Qt::MPenStyle:
      case Qt::SolidLine:
	rb_solidline->setChecked(TRUE);
        break;
      case Qt::DashLine:
	rb_dashline->setChecked(TRUE);
        break;
      case Qt::DotLine:
	rb_dotline->setChecked(TRUE);
        break;
      case Qt::DashDotLine:
	rb_dashdotline->setChecked(TRUE);
        break;
      case Qt::DashDotDotLine:
	rb_dashdotdotline->setChecked(TRUE);
        break;
       
      break; 
   }

   capstylebgroup = new QButtonGroup( this );
   capstylebgroup->setGeometry( 180, 0, 150, 110 );
   capstylebgroup->setTitle ( "Cap Style" );
   connect( capstylebgroup, SIGNAL(clicked(int)), SLOT(OnSetCapStyle(int)) );

   rb_flatcap = new QRadioButton( "Flat", capstylebgroup );
   rb_flatcap->setGeometry( 10, 20, 80, 20 );

   rb_squarecap = new QRadioButton( "Square", capstylebgroup );
   rb_squarecap->setGeometry( 10, 50, 80, 20 );

   rb_roundcap = new QRadioButton( "Round", capstylebgroup );
   rb_roundcap->setGeometry( 10, 80, 80, 20 );

   pen.setCapStyle( Qt::FlatCap );
   pen.setJoinStyle( Qt::BevelJoin );
   switch( pen.capStyle() ){
      case Qt::MPenCapStyle:
      case Qt::FlatCap:
         rb_flatcap->setChecked( TRUE );
      break;
      case Qt::SquareCap:
         rb_squarecap->setChecked( TRUE );
      break;
      case Qt::RoundCap:
         rb_roundcap->setChecked( TRUE );
      break;
   }

   connectbgroup = new QButtonGroup( this );
   connectbgroup->setGeometry( 180, 120, 150, 80 );
   connectbgroup->setTitle ( "Line type" );
   connect( connectbgroup, SIGNAL(clicked(int)), SLOT(OnSetConnectStyle(int)) );
   rb_singleline = new QRadioButton( "Single", connectbgroup );
   rb_singleline->setGeometry( 10, 20, 80, 20 );
   rb_polyline = new QRadioButton( "Poly", connectbgroup );
   rb_polyline->setGeometry( 10, 50, 80, 20 );
   linetype = 0;
   switch( linetype ){
      case 0:
	rb_singleline->setChecked( TRUE);
      break;
      case 1:
	rb_polyline->setChecked(TRUE);
      break;
   }


   // For setting the line width
   widthslider = new QSlider( QSlider::Horizontal, this, "width slider" );
   widthslider->setRange ( 1, 40 );
   widthslider->setLineStep ( 1 );
   widthslider->setValue ( pen.width() );
   widthslider->setGeometry  ( 80, 200, 190, 20 );
   widthslider->setTickmarks( QSlider::Below );
   widthslider->setTickInterval( 1 );

   connect( widthslider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetPenWidth(int)) );

   wl = new QLabel( this );
   wl->setGeometry( 20,200,70,20 );
   wl->setText( "Pen Width" );

   widthlabel = new QLabel( this );
   widthlabel->setGeometry( 270, 200, 20, 20 );
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",widthslider->value() );
   widthlabel->setText( widthsldrvalue );

   resize(350,230);
}

MyLineDialog::~MyLineDialog()
{
   delete rb_flatcap;
   delete rb_squarecap;
   delete rb_roundcap;
   delete rb_solidline;
   delete rb_dashline;
   delete rb_dotline;
   delete rb_dashdotline;
   delete rb_dashdotdotline;
   delete rb_singleline;
   delete rb_polyline;
   delete capstylebgroup;
   delete linestylebgroup;
   delete connectbgroup;
   delete widthslider;
   delete widthlabel;
   delete wl;
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the pen width
void MyLineDialog::OnSetPenWidth(int w)
{
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",w );
   widthlabel->setText( widthsldrvalue );

   pen.setWidth( w );
}

// slot to set the cap style
void MyLineDialog::OnSetCapStyle(int type)
{
   switch( type ){
      case 0:
         pen.setCapStyle( Qt::FlatCap );
         pen.setJoinStyle( Qt::BevelJoin );
         break;
      case 1:
         pen.setCapStyle( Qt::SquareCap );
         pen.setJoinStyle( Qt::MiterJoin );
         break;
      case 2:
         pen.setCapStyle( Qt::RoundCap );
         pen.setJoinStyle( Qt::RoundJoin );
         break;
   }
}
void MyLineDialog::OnSetLineStyle(int type)
{
   switch( type ){
      case 0:
         pen.setStyle( Qt::SolidLine );
         break;
      case 1:
         pen.setStyle( Qt::DashLine );
         break;
      case 2:
         pen.setStyle( Qt::DotLine );
         break;
      case 3:
         pen.setStyle( Qt::DashDotLine );
         break;
      case 4:
         pen.setStyle( Qt::DashDotLine );
         break;
   }
}
void MyLineDialog::OnSetConnectStyle(int type)
{
    switch(type) {
      case 0:
	linetype = 0;
	break;
      case 1:
	linetype = 1;
	break;
    }
}

void MyLineDialog::ChangeSetChecked()
{
      rb_singleline->setChecked( TRUE);
}   
