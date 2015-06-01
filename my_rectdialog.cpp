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

#include "my_rectdialog.h"

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

MyRectDialog::MyRectDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // For setting the line's captstyle
   // Create a button group to contain all buttons
   drawtypebgroup = new QButtonGroup( this );
   drawtypebgroup->setGeometry( 0, 0, 420, 50 );
   drawtypebgroup->setTitle ( "Draw Type" );
   connect( drawtypebgroup, SIGNAL(clicked(int)), SLOT(OnSetDrawType(int)) );

   rb_rect = new QRadioButton( "Rectangle", drawtypebgroup );
   rb_rect->setGeometry( 10, 20, 100, 20 );

   rb_roundrect = new QRadioButton( "Round Rectangle", drawtypebgroup );
   rb_roundrect->setGeometry(120, 20, 100, 20 );

   rb_circle = new QRadioButton( "Circle", drawtypebgroup );
   rb_circle->setGeometry( 240, 20, 100, 20 );

   rb_ellipse = new QRadioButton( "Ellipse", drawtypebgroup );
   rb_ellipse->setGeometry( 310, 20, 90, 20 );

   drawtype = 0;
   switch( drawtype ){
      case 0:
         rb_rect->setChecked(TRUE);
      break;
      case 1:
         rb_roundrect->setChecked( TRUE );
      break;
      case 2:
         rb_circle->setChecked( TRUE );
      break;
      case 3:
         rb_ellipse->setChecked( TRUE );
      break;
   }

   fillstylebgroup = new QButtonGroup( this );
   fillstylebgroup->setGeometry( 0, 50, 420, 120 );
   fillstylebgroup->setTitle ( "Fill Style" );
   connect( fillstylebgroup, SIGNAL(clicked(int)), SLOT(OnSetFillStyle(int)) );

   rb_solid = new QRadioButton( "Solid", fillstylebgroup );
   rb_solid->setGeometry( 10, 20, 100, 30 );

   rb_dense1 = new QRadioButton( "Dense 1", fillstylebgroup );
   rb_dense1->setGeometry( 80, 20, 100, 30 );

   rb_dense2 = new QRadioButton( "Dense 2", fillstylebgroup );
   rb_dense2->setGeometry( 160, 20, 100, 30 );

   rb_dense3 = new QRadioButton( "Dense 3", fillstylebgroup );
   rb_dense3->setGeometry( 245, 20, 100, 30 );

   rb_dense4 = new QRadioButton( "Dense 4", fillstylebgroup );
   rb_dense4->setGeometry( 330, 20, 80, 30 );


   rb_dense5 = new QRadioButton( "Dense 5", fillstylebgroup );
   rb_dense5->setGeometry( 10, 50, 100, 30 );

   rb_dense6 = new QRadioButton( "Dense 6", fillstylebgroup );
   rb_dense6->setGeometry( 80, 50, 100, 30 );

   rb_dense7 = new QRadioButton( "Dense 7", fillstylebgroup );
   rb_dense7->setGeometry( 160, 50, 100, 30 );

   rb_horizontal = new QRadioButton( "Horizontal", fillstylebgroup );
   rb_horizontal->setGeometry( 245, 50, 100, 30 );

   rb_vertical = new QRadioButton( "Vertical", fillstylebgroup );
   rb_vertical->setGeometry( 330, 50, 80, 30 );


   rb_cross = new QRadioButton( "Cross", fillstylebgroup );
   rb_cross->setGeometry( 10, 80, 100, 30 );

   rb_bdiag = new QRadioButton( "B.Diag", fillstylebgroup );
   rb_bdiag->setGeometry( 80, 80, 100, 30 );

   rb_fdiag = new QRadioButton( "F.Diag", fillstylebgroup );
   rb_fdiag->setGeometry( 160, 80, 100, 30 );

   rb_cdiag = new QRadioButton( "C.Diag", fillstylebgroup );
   rb_cdiag->setGeometry( 245, 80, 100, 30 );

   rb_nopattern = new QRadioButton( "No Pattern", fillstylebgroup );
   rb_nopattern->setGeometry( 330, 80, 85, 30 );


   brush.setStyle( Qt::NoBrush );
   switch( brush.style() ){
      case Qt::NoBrush:
	 rb_nopattern->setChecked(TRUE);
      break;
      case Qt::SolidPattern:
         rb_solid->setChecked( TRUE );
      break;
      case Qt::Dense1Pattern:
         rb_dense1->setChecked( TRUE );
      break;
      case Qt::Dense2Pattern:
         rb_dense2->setChecked( TRUE );
      break;
      case Qt::Dense3Pattern:
         rb_dense3->setChecked(TRUE);
      break;
      case Qt::Dense4Pattern:
         rb_dense4->setChecked( TRUE );
      break;
      case Qt::Dense5Pattern:
         rb_dense5->setChecked( TRUE );
      break;
      case Qt::Dense6Pattern:
         rb_dense6->setChecked( TRUE );
      break;
      case Qt::Dense7Pattern:
         rb_dense7->setChecked(TRUE);
      break;
      case Qt::HorPattern:
         rb_horizontal->setChecked( TRUE );
      break;
      case Qt::VerPattern:
         rb_vertical->setChecked( TRUE );
      break;
      case Qt::CrossPattern:
         rb_cross->setChecked( TRUE );
      break;
      case Qt::BDiagPattern:
         rb_bdiag->setChecked( TRUE );
      break;
      case Qt::FDiagPattern:
         rb_fdiag->setChecked(TRUE);
      break;
      case Qt::DiagCrossPattern:
         rb_cdiag->setChecked( TRUE );
      break;

   }


   bstylebgroup = new QButtonGroup( this );
   bstylebgroup->setGeometry( 0, 170, 300, 90 );
   bstylebgroup->setTitle ( "Boundary Style" );
   connect( bstylebgroup, SIGNAL(clicked(int)), SLOT(OnSetBoundaryStyle(int)) );

   rb_solidline = new QRadioButton( "Solid line", bstylebgroup );
   rb_solidline->setGeometry( 10, 20, 100, 30 );

   rb_dash = new QRadioButton( "Dash line", bstylebgroup );
   rb_dash->setGeometry( 100, 20, 100, 30 );

   rb_dot = new QRadioButton( "Dot line", bstylebgroup );
   rb_dot->setGeometry( 200, 20, 80, 30 );

   rb_dashdot = new QRadioButton( "Dash dot line", bstylebgroup );
   rb_dashdot->setGeometry( 10, 50, 100, 30 );

   rb_dashdotdot = new QRadioButton( "Dash dot dot line", bstylebgroup );
   rb_dashdotdot->setGeometry( 100, 50, 80, 30 );

   rb_noline = new QRadioButton( "No line", bstylebgroup );
   rb_noline->setGeometry( 200, 50, 80, 30 );

   pen.setStyle( Qt::SolidLine );
   switch( pen.style() ){
      case Qt::MPenStyle:
      case Qt::SolidLine:
        rb_solidline->setChecked(TRUE);
        break;
      case Qt::DashLine:
        rb_dash->setChecked(TRUE);
        break;
      case Qt::DotLine:
        rb_dot->setChecked(TRUE);
        break;
      case Qt::DashDotLine:
        rb_dashdot->setChecked(TRUE);
        break;
      case Qt::DashDotDotLine:
        rb_dashdotdot->setChecked(TRUE);
        break;
      case Qt::NoPen:
        rb_noline->setChecked(TRUE);
        break;
   }

   joinstylebgroup = new QButtonGroup( this );
   joinstylebgroup->setGeometry( 0,260, 300, 55 );
   joinstylebgroup->setTitle ( "Boundary Join Style" );
   connect( joinstylebgroup, SIGNAL(clicked(int)), SLOT(OnSetJoinStyle(int)) );

   rb_miterjoin = new QRadioButton( "Miter Join", joinstylebgroup );
   rb_miterjoin->setGeometry( 10, 20, 100, 30 );

   rb_beveljoin = new QRadioButton( "Bevel Join", joinstylebgroup );
   rb_beveljoin->setGeometry( 100, 20, 90, 30 );

   rb_roundjoin = new QRadioButton( "Round Join", joinstylebgroup );
   rb_roundjoin->setGeometry( 200, 20, 90, 30 );

   pen.setJoinStyle( Qt::BevelJoin);
   if(pen.joinStyle() == Qt::MiterJoin ){
        rb_beveljoin->setChecked(TRUE);
   }
   else if(pen.joinStyle() == Qt::BevelJoin ){
        rb_miterjoin->setChecked(TRUE);
   }
   else if(pen.joinStyle() == Qt::RoundJoin){
        rb_roundjoin->setChecked(TRUE);
   }

   fillcolorbgroup = new QButtonGroup( this );
   fillcolorbgroup->setGeometry( 310, 170, 110, 145 );
   fillcolorbgroup->setTitle ( "FillColor" );
   connect( fillcolorbgroup, SIGNAL(clicked(int)), SLOT(OnSetFillColor(int)) );

   rb_fcolor = new QRadioButton( "Fore-\nground", fillcolorbgroup );
   rb_fcolor->setGeometry( 10, 20, 80, 40 );

   rb_bcolor = new QRadioButton( "Back-\nground", fillcolorbgroup );
   rb_bcolor->setGeometry( 10, 80, 80, 40 );
   
   colormode = 0;
   switch( colormode){
      case 0:
        rb_fcolor->setChecked(TRUE);
        break;
      case 1:
        rb_bcolor->setChecked(TRUE);
        break;
   }





  // For setting the line width
   widthslider = new QSlider( QSlider::Horizontal, this, "width slider" );
   widthslider->setRange ( 1, 40 );
   widthslider->setLineStep ( 1 );
   widthslider->setValue ( pen.width() );
   widthslider->setGeometry  ( 130, 320, 200, 20 );
   widthslider->setTickmarks( QSlider::Below );
   widthslider->setTickInterval( 40 );

   connect( widthslider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetBoundaryWidth(int)) );

   wl = new QLabel( this );
   wl->setGeometry( 10,320,130,20 );
   wl->setText( "Boundary Width" );

   widthlabel = new QLabel( this );
   widthlabel->setGeometry( 360, 320, 20, 20 );
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",widthslider->value() );
   widthlabel->setText( widthsldrvalue );

   resize(420,350);
}

MyRectDialog::~MyRectDialog()
{
   delete drawtypebgroup;
   delete rb_rect;
   delete rb_roundrect;
   delete rb_circle;
   delete rb_ellipse;

   delete fillstylebgroup;
   delete rb_solid;
   delete rb_dense1;
   delete rb_dense2;
   delete rb_dense3;
   delete rb_dense4;
   delete rb_dense5;
   delete rb_dense7;
   delete rb_horizontal;
   delete rb_vertical;
   delete rb_cross;
   delete rb_bdiag;
   delete rb_fdiag;
   delete rb_cdiag;
   delete rb_nopattern;
   delete rb_ellipse;

   delete bstylebgroup;
   delete rb_solidline;
   delete rb_dash;
   delete rb_dot;
   delete rb_dashdot;
   delete rb_dashdotdot;
   delete rb_noline;

   delete joinstylebgroup;
   delete rb_miterjoin;
   delete rb_beveljoin;
   delete rb_roundjoin;

   delete fillcolorbgroup;
   delete rb_fcolor;
   delete rb_bcolor;

   delete widthslider;
   delete widthlabel;
   delete wl;
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the pen width
void MyRectDialog::OnSetBoundaryWidth(int w)
{
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",w );
   widthlabel->setText( widthsldrvalue );

   pen.setWidth( w );
}

// slot to set the style
void MyRectDialog::OnSetFillStyle(int type)
{
   switch( type ){
      case 0:
         brush.setStyle( Qt::SolidPattern );
         break;
      case 1:
         brush.setStyle( Qt::Dense1Pattern );
         break;
      case 2:
         brush.setStyle( Qt::Dense2Pattern );
         break;
      case 3:
         brush.setStyle( Qt::Dense3Pattern );
         break;
      case 4:
         brush.setStyle( Qt::Dense4Pattern );
         break;
      case 5:
         brush.setStyle( Qt::Dense5Pattern );
         break;
      case 6:
         brush.setStyle( Qt::Dense6Pattern );
         break;
      case 7:
         brush.setStyle( Qt::Dense7Pattern );
         break;
      case 8:
         brush.setStyle( Qt::HorPattern );
         break;
      case 9:
         brush.setStyle( Qt::VerPattern );
         break;
      case 10:
         brush.setStyle( Qt::CrossPattern );
         break;
      case 11:
         brush.setStyle( Qt::BDiagPattern );
         break;
      case 12:
         brush.setStyle( Qt::FDiagPattern );
         break;
      case 13:
         brush.setStyle( Qt::DiagCrossPattern );
         break;
      case 14:
         brush.setStyle( Qt::NoBrush );
         break;

   }
}

void MyRectDialog::OnSetBoundaryStyle(int type)
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
         pen.setStyle( Qt::DashDotDotLine );
         break;
      case 5:
         pen.setStyle( Qt::NoPen );
         break;
   }
}

void MyRectDialog::OnSetJoinStyle(int type)
{
   switch( type ){
      case 0:
         pen.setJoinStyle( Qt::MiterJoin );
         break;
      case 1:
         pen.setJoinStyle( Qt::BevelJoin );
         break;
      case 2:
         pen.setJoinStyle( Qt::RoundJoin );
         break;

   }
}

void MyRectDialog::OnSetDrawType(int type)
{
   switch( type ) {
      case 0:
         drawtype = 0;
         break;
      case 1:
         drawtype = 1;
         break;
      case 2:
         drawtype = 2;
         break;
      case 3:
         drawtype = 3;
         break;
    }
}

void MyRectDialog::OnSetFillColor(int type)
{
   switch( type ) {
      case 0:
         colormode = 0;
         break;
      case 1:
         colormode = 1;
         break;
    }
}


