/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_widget.cpp
//  Description: the source file
//  -- MyMainWindow class implementation 
/****************************************/

#include <iostream>
#include <cmath>
using namespace std;

#include "my_widget.h"

#include <qfiledialog.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qtextedit.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qprinter.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qwhatsthis.h>
#include <qsimplerichtext.h>
#include <qcolordialog.h> 

////////////////////////////////////////////////
// Constructor and Destructor
////////////////////////////////////////////////

MyMainWindow::MyMainWindow(QWidget* parent, const char* name)
:QMainWindow(parent, name)
{
   // initialize the default background color
   bgcolor = QColor( 255, 255, 255 );

   // build the menu
   CreateMenu();

   // build the tool bar 
   drawTools = new MyToolBar( this, "tool bar" );
   drawTools->setLabel( "Tool Bar" );

   connect( drawTools, SIGNAL( OnPaint() ), 
         this, SLOT( OnDockWindowPositionChanged() ) );
   
   QPixmap pix;

   pix.load( "new_icon.bmp" );
   newButton = new QToolButton( pix, "New Image", QString::null,
                                this, SLOT( OnNewImage() ), drawTools, "new image" );

   pix.load( "open_icon.bmp" );
   openButton = new QToolButton( pix, "Open Image", QString::null,
                                this, SLOT( OnLoadImage() ), drawTools, "open image" );

   pix.load( "save_icon.bmp" );
   saveButton = new QToolButton( pix, "Save Image", QString::null,
                                this, SLOT( OnSaveImage() ), drawTools, "save image" );

   pix.load( "undo_icon.bmp" );
   penButton = new QToolButton( pix, "Undo", QString::null,
                                this, SLOT( OnEditUndo() ), drawTools, "undo" );

   pix.load( "redo_icon.bmp" );
   penButton = new QToolButton( pix, "Redo", QString::null,
                                this, SLOT( OnEditRedo() ), drawTools, "redo" );

   pix.load( "clearall_icon.bmp" );
   penButton = new QToolButton( pix, "Clear All", QString::null,
                                this, SLOT( OnEditClearAll() ), drawTools, "clear all" );

   pix.load( "resize_icon.bmp" );
   penButton = new QToolButton( pix, "Resize", QString::null,
                                this, SLOT( OnEditResize() ), drawTools, "resize" );

   pix.load( "pen_icon.bmp" );
   penButton = new QToolButton( pix, "Pen", QString::null,
                                this, SLOT( OnChoosePen() ), drawTools, "pen" );

   pix.load( "line_icon.bmp" );
   lineButton = new QToolButton( pix, "Line", QString::null,
                                this, SLOT( OnChooseLine() ), drawTools, "line" );
  
   pix.load( "eraser_icon.bmp" );
   eraserButton = new QToolButton( pix, "Eraser", QString::null,
                                this, SLOT( OnChooseEraser() ), drawTools, "eraser" );
   
   pix.load( "rect_icon.bmp" );
   rectButton = new QToolButton( pix, "Rectangle", QString::null,
                                this, SLOT( OnChooseRect() ), drawTools, "rect" );
  
   pix.load( "fcolor_icon.bmp" );
   colorButton = new QToolButton( pix, "Color", QString::null,
                                this, SLOT( OnChooseColor() ), drawTools, "fcolor" );

   pix.load( "bcolor_icon.bmp" );
   bcolorButton = new QToolButton( pix, "BG Color", QString::null,
                                this, SLOT( OnChooseBGColor() ), drawTools, "bcolor" );
   // create the QPixmap image
   image = new QPixmap();

   // create the QPainter object
   paint = new QPainter( this );

   // create the pen dialog
   pendialog = new MyPenDialog( this, "Pen Dialog" );
   pendialog->setCaption( "Pen Dialog" );

   linedialog = new MyLineDialog( this, "Line Dialog" );
   linedialog->setCaption( "Line Dialog" );

   eraserdialog = new MyEraserDialog( this, "Eraser Dialog" );
   eraserdialog->setCaption( "Eraser Dialog" );

   rectdialog= new MyRectDialog( this, "Rectangle Dialog" );
   rectdialog->setCaption( "Rect Dialog" );  

   resize(800,600);

   QDockArea* leftDockWin = leftDock();
   QDockArea* topDockWin = topDock();
      
   xPos = ((QWidget*)leftDockWin)->frameSize().width();
   yPos = menuBar()->height() + ((QWidget*)topDockWin)->frameSize().height();

   // initialize the undo flag to false (i.e. disable undo)
   undoflag = false;
}

MyMainWindow::~MyMainWindow()
{
   delete newButton;
   delete openButton;
   delete saveButton;
   delete undoButton;
   delete redoButton;
   delete clearallButton;
   delete resizeButton;
   delete rectButton;
   delete penButton;
   delete lineButton;
   delete eraserButton;
   delete colorButton;
   delete bcolorButton;
   delete drawTools;

   delete image;
   if(undo != NULL) delete undo;
   if(redo != NULL) delete redo;
   delete paint;

   delete pendialog;

   delete file;
   delete edit;
   delete view;
   delete help;
}

////////////////////////////////////////////////
// Create the menu
////////////////////////////////////////////////

void MyMainWindow::CreateMenu()
{
   // create the "File" popup menu
   file = new QPopupMenu( this );

   file->insertItem( "New image", this, SLOT( OnNewImage() ) );
   file->insertItem( "Load image", this, SLOT( OnLoadImage() ) );
   file->insertItem( "Save image", this, SLOT( OnSaveImage() ) );
   file->insertSeparator();
   file->insertItem( "Foregound Color", this, SLOT( OnChooseColor() ) );
   file->insertItem( "Backgound Color", this, SLOT( OnChooseBGColor() ) );
   file->insertSeparator();
   file->insertItem( "Exit", this, SLOT( OnExit() ) );
   
   menuBar()->insertItem( "File", file );

   // create the "Edit" popup menu
   edit = new QPopupMenu( this );
   edit->insertItem( "Undo", this, SLOT( OnEditUndo() ) );
   edit->insertItem( "Redo", this, SLOT( OnEditRedo() ) );
   file->insertSeparator();
   edit->insertItem( "Clear All", this, SLOT( OnEditClearAll() ) );
   file->insertSeparator();
   edit->insertItem( "Resize", this, SLOT( OnEditResize() ) );
   menuBar()->insertItem( "Edit", edit );

   view = new QPopupMenu( this );
   view->insertItem( "Tool Bar", this, SLOT( OnViewToolBar() ) );
   menuBar()->insertItem( "View", view );

   help = new QPopupMenu( this );
   help->insertItem( "About", this, SLOT( OnAbout() ) );
   menuBar()->insertItem( "Help", help );
}

////////////////////////////////////////////////
// Paint the image onto the widget 
////////////////////////////////////////////////

void MyMainWindow::paintbmp() const
{
   // close active painter
   if(paint->isActive () )
   {
      paint->end();
   }

   paint->begin( this );
   if ( ! image->isNull() ) 
   {
      paint->drawPixmap( xPos, yPos, (*image) );
   }
   paint->end();
}

////////////////////////////////////////////////
// Handle Paint Event
////////////////////////////////////////////////

void MyMainWindow::paintEvent(QPaintEvent* e)
{
   paintbmp();
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////

// Create a new image
void MyMainWindow::OnNewImage()
{
   bool ok;

   // get the user input of width from the input diaplog
   int width = QInputDialog::getInteger( "New Image", "Enter the bitmap width:", 400, 0, 10000, 1,
            &ok, this );

   if ( !ok || width <= 0 ) 
      return;

   // get the user input of height from the input diaplog
   int height = QInputDialog::getInteger( "New Image", "Enter the bitmap height:", 300, 0, 10000, 1,
            &ok, this );

   if ( !ok || height <= 0 ) 
      return;
    
   if ( image->isNull() )
   {
      delete image;   
   }

   // create an image with the input width & height
   image = new QPixmap( width, height );
   // fill it with default background
   image->fill( bgcolor );

   undoflag = false;

   this->erase();
   paintbmp();
}

// Load an image
void MyMainWindow::OnLoadImage()
{
   QString s = QFileDialog::getOpenFileName( "", "*.bmp", this, "", "Load image..." );
   if ( ! s.isNull() ) 
   {
      if( image->load( s ) ){
         this->erase();
         undoflag = false;
         paintbmp();
      }
   }
}

// Save the image as a bitmap
void MyMainWindow::OnSaveImage()
{
   QString s = QFileDialog::getSaveFileName( "", "*.bmp", this, "", "Save image..." );
   if (! s.isNull() )
   {
      image->save( s, "BMP" );
   }
}

// Change the foreground color
void MyMainWindow::OnChooseColor()
{
   QColor windowcolor = QColorDialog::getColor( pendialog->pen.color(), this );
   if( windowcolor.isValid() ){
      pendialog->pen.setColor( windowcolor );  
      linedialog->pen.setColor( windowcolor);
      rectdialog->pen.setColor( windowcolor);
      rectdialog->fcolor = windowcolor;
   }

}

// Change the background color
void MyMainWindow::OnChooseBGColor()
{
   QColor windowcolor = QColorDialog::getColor( bgcolor, this );
   if( windowcolor.isValid() ){
      bgcolor = windowcolor;
   }
}

// Undo the last action
void MyMainWindow::OnEditUndo()
{
   // TODO!
   if(undoflag && undo!=NULL){
      QPixmap* temp = image;
      image = undo;
      redo = temp; 
      undoflag = false;
      paintbmp();
   }
}

// Redo the last action
void MyMainWindow::OnEditRedo()
{
   // TODO!
   if(!undoflag && redo!= NULL){
     QPixmap* temp = image;
     image = redo;
     undo = temp;
     undoflag = true;
     paintbmp();
   }
}

// Clear the drawing
void MyMainWindow::OnEditClearAll()
{
   // TODO!
   undo = new QPixmap(*image);
   image->fill(bgcolor);
   undoflag = true;
   paintbmp();
}

// Resize the image
void MyMainWindow::OnEditResize()
{
   // TODO!
   bool okay;

   int width2 = QInputDialog::getInteger( "New Image", "Enter the bitmap width:", image->width(), 0, 10000, 1,&okay, this );

   if( !okay || width2 <= 0 ){
      return;
   }

   // get the user input of height from the input diaplog
   int height2 = QInputDialog::getInteger( "New Image", "Enter the bitmap height:", image->height(), 0, 10000, 1,&okay, this );

   if( !okay || height2 <= 0 ){
      return;
   }
   this->erase();
   QPixmap* old = new QPixmap(*image);
   image->resize(width2,height2);
   image->fill(bgcolor);
   paint->begin(image);
   paint->drawPixmap(0,0,*old);
   paint->end();
   undoflag = false;
   redo = NULL;
   paintbmp();
   delete old;
}

// Show the tool bar
void MyMainWindow::OnViewToolBar()
{
   drawTools->show();
}

// Close the application
void MyMainWindow::OnExit()
{
   // qApp is a global pointer points to
   // our application object (QApplication)
   qApp->quit(); // quit this application program
}

// About Paint
void MyMainWindow::OnAbout()
{
   QMessageBox::about( this, "About", "CS2012 Spring 2015 Paint" );
}

// Activate the Pen tool
void MyMainWindow::OnChoosePen()
{
   selectedbutton = DPen;
   mouseevent = 0;
}

// Activate the other drawing tools
// TODO: other OnChooseXX()
void MyMainWindow::OnChooseLine() {
   selectedbutton = DLine;
   mouseevent = 0;
   linedialog->count = 0;
}

void MyMainWindow::OnChooseEraser() {
   selectedbutton = DEraser;
   mouseevent = 0;
}

void MyMainWindow::OnChooseRect() {
   selectedbutton = Drect;
   mouseevent = 0;
}
////////////////////////////////////////////////
// Handle Mouse Event
////////////////////////////////////////////////
// Mouse press event handler
void MyMainWindow::mousePressEvent(QMouseEvent* e)
{
   // User presses the left button -- start drawing
   if ( e->button() == Qt::LeftButton )
   {
      // updating the images for undo and redo
      // if( undo != NULL ) delete undo;     
      undo = new QPixmap( *image );
      undoflag = true;
      // if( redo != NULL ) delete redo;
      redo = NULL;

      mouseevent = 1;

      // Create a new image if necessary
      if ( image->isNull() ) 
      { 
         OnNewImage(); 
      } 
      else 
      { 
         if( paint->isActive() )
         {
            paint->end();
         }
         QPen tpen;
         QBrush tbrush;

         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               // update the cursor positions
               px = e->x(); py = e->y();
               dx = e->x(); dy = e->y();
               break;
            case DLine: // drawing with the Line tool
               // TODO: 
	       if( linedialog->count == 0){
                px = e->x(); py = e->y();
               	dx = e->x(); dy = e->y();
		linedialog->count++;
               }
	       else {
                px = e->x(); py = e->y();

               }
	       break;
            case DEraser: // drawing with the Eraser tool
               // TODO
               px = e->x(); py = e->y();
	       paint->begin(image);
 	       tpen = QPen(Qt::NoPen);
	       paint->setPen(tpen);
	       tbrush = QBrush(bgcolor,Qt::SolidPattern);
	       paint->setBrush(tbrush);
               paint->setClipRect(0,0,image->width(),image->height());
               paint->drawRect(px- xPos -int((eraserdialog->size)/2),py -yPos -int((eraserdialog->size)/2),eraserdialog->size,eraserdialog->size);
	       paint->end();

	       paint->begin(this);
               paint->setClipRect(xPos,yPos,image->width(),image->height());
 	       tpen = QPen(Qt::SolidLine);
	       paint->setPen(tpen);
	       paint->setBrush(tbrush);
               paint->drawRect(px-int((eraserdialog->size)/2),py-int((eraserdialog->size)/2),eraserdialog->size,eraserdialog->size);
	       paint->end();
	       break;
            case Drect:  // drawing witth the Rectangle tool
               // TODO
               
	       px = e->x(); py = e->y();
               dx = e->x(); dy = e->y();
               break;
         }
      }
   }
   // User presses the right button -- show the tools' dialogs 
   else if( e->button() == Qt::RightButton )
   {
      mouseevent = 2;

      switch( selectedbutton ){
         case DPen:
            pendialog->show();
            break;
         case DLine:
            linedialog->count = 0;
            linedialog->show();
            break;
         case DEraser:
            eraserdialog->show();
            break;
         case Drect:
            rectdialog->show();
            break;
      }
   }
}

// Mouse move event handler
void MyMainWindow::mouseMoveEvent(QMouseEvent* e)
{
   // dragging by left button click
   if( mouseevent == 1 )
   {
      if ( image->isNull() ) 
      { 
      }
      else 
      { 
         QPointArray a;

         // For any temporary pen and brush settings
         QPen tpen;
         QBrush tbrush;

         // close active painter
         if( paint->isActive() )
         {
            paint->end();
         }

         int mx, my;  // displacements of user moving the mouse

         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               paint->begin( image ); // begin painting onto the picture

               paint->setClipRect ( 0, 0, image->width(), image->height() );  // clipping
               paint->setPen( pendialog->pen );  // set the painter settings from the pen dialog
               // Set the array of points 
               a.setPoints( 3, dx - xPos, dy - yPos,
                               px - xPos, py - yPos,
                               e->x() - xPos, e->y() - yPos );
               paint->drawPolyline( a, 0, 3 );
 
               // update the cursor positions
               dx = px; dy = py; 
               px = e->x(); py = e->y();

               paint->end(); // end painting onto the picture
               paintbmp();
               break;

            case DLine:  // drawing with the Line tool
               // TODO
	       //paint->begin(image);
               paintbmp();
	       if(linedialog->linetype == 0){

	       	paint->begin(this);
               	paint->setPen(linedialog->pen);
               	paint->setBrush(tbrush);
               	paint->setClipRect(xPos,yPos,image->width(),image->height());
               	paint->drawLine(px,py,e->x(),e->y());
               	paint->end();
	       }
	       else {
		
	       	paint->begin(this);
               	paint->setPen(linedialog->pen);
               	paint->setBrush(tbrush);
               	paint->setClipRect(xPos,yPos,image->width(),image->height());
               	paint->drawLine(dx,dy,e->x(),e->y());
               	paint->end();
	       }
               break;

            case DEraser:  // drawing with the Eraser tool
               // TODO
	       paint->begin(image);
	       tpen = QPen(Qt::NoPen);
               paint->setPen(tpen);
	       tbrush = QBrush(bgcolor,Qt::SolidPattern);
               paint->setBrush(tbrush);
               paint->setClipRect(0,0,image->width(),image->height());
	       paint->drawRect(e->x() - xPos - int((eraserdialog->size)/2),e->y()-yPos - int((eraserdialog->size)/2),eraserdialog->size,eraserdialog->size);
	       paint->end();
	                   
  	       this->repaint();
	       paint->begin(this);
               paint->setClipRect(xPos,yPos,image->width(),image->height());
	       tpen = QPen(Qt::SolidLine);
               paint->setPen(tpen);
	       paint->drawRect(e->x()-int((eraserdialog->size)/2),e->y()-int((eraserdialog->size)/2),eraserdialog->size,eraserdialog->size);
	       paint->end();
               break;

            case Drect:  // drawing with the Rectangle tool
               // TODO
               paintbmp();
	       this->repaint();
	       paint->begin(this);
               paint->setPen(rectdialog->pen);
               switch( rectdialog->colormode) {
		 case 0:
 		   rectdialog->brush.setColor(rectdialog->fcolor);
                   break;
                 case 1:
 		   rectdialog->brush.setColor(bgcolor);
                   break;
                }  
               paint->setBrush(rectdialog->brush);
               paint->setClipRect(xPos,yPos,image->width(),image->height());
	       switch(rectdialog->drawtype){
 		  case 0:
	            paint->drawRect(px ,py ,e->x()-px,e->y()-py);
	          break;
                  case 1:
	            paint->drawRoundRect(px ,py ,e->x()-px,e->y()-py,20,15);
                  break;
                  case 2:
	            paint->drawEllipse(px ,py ,e->x()-px,e->x()-px);
                  break;
                  case 3:
	            paint->drawEllipse(px ,py ,e->x()-px,e->y()-py);
                  break;
               }
                    
               paint->end();
               break;
         }                      
      }
   }
}

// Mouse release event handler
void MyMainWindow::mouseReleaseEvent(QMouseEvent* e)
{
   if( e->button() == Qt::LeftButton )
   {
      if ( image->isNull() ) 
      { 
         //OnLoadImage(); 
      }
      else 
      { 
         QPointArray a;

         // For any temporary pen and brush settings
         QPen tpen;
         QBrush tbrush;

         int mx, my;  // displacements of user moving the mouse

         // close active painter
         if( paint->isActive () )
         {
            paint->end();
         }
         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               paint->begin( image );  // begin painting onto picture   
               paint->setClipRect ( 0, 0, image->width(), image->height() ); // clipping
               paint->setPen( pendialog->pen ); // set the painter settings from the pen dialog
              
               // Set the array of points 
               a.setPoints( 3, dx - xPos, dy - yPos,
                               px - xPos, py - yPos,
                               e->x() - xPos, e->y() - yPos );
               paint->drawPolyline( a, 0, 3 );

               // update the cursor positions
               dx = px; dy = py;
               px = e->x(); py = e->y();

               paint->end();
               break;

            case DLine:  // drawing with the Line tool 
               // TODO 
	       if(linedialog->linetype == 0){
	       	paint->begin(image);
               	paint->setPen(linedialog->pen);
               	paint->setBrush(tbrush);
               	paint->setClipRect(0,0,image->width(),image->height());
               	paint->drawLine(px -xPos, py - yPos, e->x()-xPos , e->y()-yPos);
               	paint->end();
	       }
               else{
	       	paint->begin(image);
               	paint->setPen(linedialog->pen);
               	paint->setBrush(tbrush);
               	paint->setClipRect(0,0,image->width(),image->height());
               	paint->drawLine(dx -xPos, dy - yPos, e->x()-xPos , e->y()-yPos);
		dx = e->x();
		dy = e->y();

               	paint->end();
               }
               break;

            case DEraser:  // drawing with the Eraser tool
               // TODO
               dx = px; dy =py;
               break;

            case Drect:  // drawing with the Rectangle tool
               // TODO
	       //this->repaint();
	       paint->begin(image);
               paint->setPen(rectdialog->pen);
               paint->setBrush(rectdialog->brush);
               paint->setClipRect(0,0,image->width(),image->height());
               //paint->setBackgroundMode(OpaqueMode);
               switch(rectdialog->drawtype){
   		   case 0:
            	      paint->drawRect(px- xPos, py-yPos, e->x()-px , e->y()-py);
                   break;
                   case 1:
                      paint->drawRoundRect(px- xPos, py-yPos, e->x()-px , e->y()-py,20.0,15.0);
                   break;
                   case 2:
            	      paint->drawEllipse(px- xPos, py-yPos, e->x()-px , e->x()-px);
                   break;
                   case 3:
            	      paint->drawEllipse(px- xPos, py-yPos, e->x()-px , e->y()-py);
    		   break;
               }
	       paint->end();
               break;
         }     
                 
         paintbmp();
      }
   }
   mouseevent = 0; // reset the mouse event type
}

// Mouse double click event handler
void MyMainWindow::mouseDoubleClickEvent(QMouseEvent* e)
{
   linedialog->linetype = 0;
   linedialog->ChangeSetChecked();
   mouseevent = 0; 
   
}

////////////////////////////////////////////////
// Other user defined slots 
////////////////////////////////////////////////

void MyMainWindow::OnDockWindowPositionChanged()
{
   QDockArea* leftDockWin = leftDock();
   QDockArea* topDockWin = topDock();
      
   xPos = ((QWidget*)leftDockWin)->frameSize().width();
   yPos = menuBar()->height() + ((QWidget*)topDockWin)->frameSize().height();

   this->erase();
   paintbmp();
}
