// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  "../H_files/CellWidget.h"
#include  "../H_files/Term.h"
#include  "../H_files/Instance.h"
#include  "../H_files/Symbol.h"
#include  "../H_files/Shape.h"
#include  "../H_files/BoxShape.h"
#include  "../H_files/LineShape.h"
#include  "../H_files/ArcShape.h"
#include  "../H_files/EllipseShape.h"
#include  "../H_files/TermShape.h"
#include  "../H_files/Cell.h"
#include  "../H_files/Line.h"
#include  "../H_files/Node.h"
#include  "../H_files/Net.h"


namespace Netlist{

  using namespace std;


  ostream& operator<< ( ostream& o, const QRect& rect )
  {
    o << "<QRect x:" << rect.x()
      <<       " y:" << rect.y()
      <<       " w:" << rect.width()
      <<       " h:" << rect.height() << ">";
    return o;
  }


  ostream& operator<< ( ostream& o, const QPoint& p )
  { o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; }



  CellWidget::CellWidget ( QWidget* parent )
  :QWidget   (parent)
    , cell_     (NULL)
    , viewport_ ( Box (0 ,0 ,500 ,500) )
  {
    setAttribute    ( Qt::WA_OpaquePaintEvent );
    setAttribute    ( Qt::WA_NoSystemBackground );
    setAttribute    ( Qt::WA_StaticContents );
    setSizePolicy   ( QSizePolicy::Expanding     // X direction.
                    , QSizePolicy::Expanding );  // Y direction.
    setFocusPolicy  ( Qt::StrongFocus );
    setMouseTracking( true );
  }

  CellWidget::~CellWidget()
  { }

  void  CellWidget::setCell ( Cell* cell )
  {
    cell_ = cell;
    repaint();
  }

  QSize  CellWidget::minimumSizeHint() const
  { return QSize(700,500); }

  void  CellWidget::resizeEvent ( QResizeEvent* event )
  { 
    const QSize& size = event->size();

    // Assume the resize is always done by drawing the bottom right corner .
    viewport_.setX2 ( viewport_.getX1() + size.width() );
    viewport_.setY1 ( viewport_.getY2() - size.height() );
    cerr << "CellWidget::resizeEvent() viewport_:" << viewport_ << endl ;
  }

  void  CellWidget::paintEvent ( QPaintEvent* event )
  {
    QFont  bigFont=QFont( "URW Bookman L", 20 );
    QFont  littleFont=QFont( "URW Bookman L", 12 );

    QString cellName = "NULL";
    if (cell_) cellName = cell_->getName().c_str();

    QPainter painter(this);
    painter.setFont      ( bigFont );
    painter.setBackground( QBrush( Qt::black ) );
    painter.eraseRect    ( QRect( QPoint(0,0), size() ) );

    int frameWidth  = 200;
    int frameHeight = 50;
    QRect nameRect ( 20
                   , 20
                   , frameWidth
                   , frameHeight
                   );

    painter.setPen( QPen( Qt::white, 1 ) );
    painter.drawRect( nameRect );
    painter.drawText( nameRect, Qt::AlignCenter, cellName );
    painter.setPen ( QPen( Qt::darkGreen, 3 ) );

    QRect rect=boxToScreenRect( Box (500 ,500 ,0 ,0) );
    painter.drawRect( rect );

    painter.setFont( littleFont );
    query(1, painter);
  }

  void CellWidget::keyPressEvent ( QKeyEvent* event ) {
    event->ignore();
    if ( event->modifiers()&( Qt::ControlModifier|Qt::ShiftModifier ))
      return ;
    switch ( event->key()) {
      case Qt::Key_Up:    goUp   (); break;
      case Qt::Key_Down:  goDown (); break;
      case Qt::Key_Left:  goLeft (); break;
      case Qt::Key_Right: goRight(); break;
      default:return ;
    }
    event->accept();
  }

  void CellWidget::goRight(){
    viewport_.translate( Point (-20, 0) );
    repaint();
  }

  void CellWidget::goUp() {
    viewport_.translate( Point (0, -20) );
    repaint();
  }

  void CellWidget::goLeft(){
    viewport_.translate( Point (20, 0) );
    repaint();
  }

  void CellWidget::goDown() {
    viewport_.translate( Point (0, 20) );
    repaint();
  }

  void CellWidget::query ( unsigned int flags, QPainter& painter ) {
    
    int InstanceShapes = 1<<0;

    if (( not cell_ ) or ( not flags )) return ;

    const vector<Instance*>& instances = cell_->getInstances();

    for ( size_t i=0; i<instances.size() ; ++ i ) {
      Point instPos = instances [i]->getPosition();
      const Symbol* symbol = instances[i]->getMasterCell()->getSymbol();
      if ( not symbol ) continue ;
      
      const vector<Shape*>& shapes = symbol->getShapes();

      if ( flags& InstanceShapes ) {
        for ( size_t j=0; j<shapes.size() ; ++ j) {
          BoxShape* boxShape = dynamic_cast<BoxShape*>( shapes[j]);
          if ( boxShape ) {
            Box box = boxShape->getBoundingBox();
            QRect rect = boxToScreenRect ( box.translate ( instPos ));
            painter.setPen ( QPen( Qt::darkGreen, 3 ) );
            painter.drawRect( rect );
          }

          LineShape* lineShape = dynamic_cast<LineShape*>( shapes[j]);
          if ( lineShape ) {
            Box box = lineShape->getBoundingBox().translate ( instPos );
            Point start = Point(box.getX1(), box.getY1());
            Point end = Point(box.getX2(), box.getY2());
            painter.setPen ( QPen( Qt::darkGreen, 3 ) );
            painter.drawLine( pointToScreenPoint( start ), pointToScreenPoint( end ));
          }

          ArcShape* arcShape = dynamic_cast<ArcShape*>( shapes[j]);
          if ( arcShape ) {
            Box box = arcShape->getBoundingBox();
            QRect rect = boxToScreenRect ( box.translate ( instPos ));
            painter.setPen ( QPen( Qt::darkGreen, 3 ) );
            painter.drawArc( rect, arcShape->getstart()*16, arcShape->getspan()*16 );
            //selon la dock qt start et span doivent être spécifiées en 1/16e de degré, c'est-à-dire qu'un cercle complet est égal à 5760 (16 * 360)
          }

          EllipseShape* ellipseShape = dynamic_cast<EllipseShape*>( shapes[j]);
          if ( ellipseShape ) {
            Box box = ellipseShape->getBoundingBox();
            QRect rect = boxToScreenRect ( box.translate ( instPos ));
            painter.setPen ( QPen( Qt::darkGreen, 3 ) );
            painter.drawEllipse( rect );
          }

          TermShape* termShape = dynamic_cast<TermShape*>( shapes[j]);
          if ( termShape ) {
            Box box = termShape->getBoundingBox().inflate(3, 3);
            QRect rect = boxToScreenRect ( box.translate ( instPos ));
            painter.setPen( QPen( Qt::darkRed, 0 ) );
            painter.setBrush( QBrush( Qt::darkRed ) );
            switch ( termShape->getAlign() ){
              case TermShape::TopLeft: 
                painter.drawText( rect.topLeft() + QPoint(-10, -10), termShape->getTerm()->getName().c_str() );
                break;
              case TermShape::TopRight:
                painter.drawText( rect.topRight() + QPoint(5, -10), termShape->getTerm()->getName().c_str() );
                break;
              case TermShape::BottomLeft:
                painter.drawText( rect.bottomLeft() + QPoint(10, 10), termShape->getTerm()->getName().c_str() );
                break;
              case TermShape::BottomRight:
                painter.drawText( rect.bottomRight() + QPoint(5, 10), termShape->getTerm()->getName().c_str() );
                break;
            }
            painter.drawRect( rect );
          }
        }
        
        const vector<Net*>& nets = cell_->getNets();
        for ( size_t i=0; i<nets.size() ; ++ i ) {
          const vector<Line*>& lines = nets[i]->getLines();
          for ( size_t j=0; j<lines.size() ; ++ j) {
            Point start = lines[j]->getSourcePosition();
            Point end = lines[j]->getTargetPosition();
            painter.setPen ( QPen( Qt::cyan, 1, Qt::DashDotLine ) );
            painter.drawLine( pointToScreenPoint( start ), pointToScreenPoint( end ));
          }
        }

        const vector<Term*>& terms = cell_->getTerms();
        for ( size_t i=0; i<terms.size() ; ++ i) {
          Point position = terms[i]->getPosition();
          QPoint positionScreen = pointToScreenPoint(position);
          painter.setPen( QPen (Qt::darkRed, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin) );
          painter.setBrush( QBrush( Qt::darkRed ) );
          QPolygon poly;
          switch ( terms[i]->getDirection() ){
            case Term::In: 
              poly << QPoint(positionScreen)+QPoint(-5, 10) 
                   << QPoint(positionScreen)+QPoint(5, 10) 
                   << QPoint(positionScreen)+QPoint(15, 0)
                   << QPoint(positionScreen)+QPoint(5, -10)
                   << QPoint(positionScreen)+QPoint(-5, -10);
              painter.drawText( pointToScreenPoint(position) + QPoint(-20, 20), terms[i]->getName().c_str() );
              break;
            case Term::Out:
              poly << QPoint(positionScreen)+QPoint(5, 10) 
                   << QPoint(positionScreen)+QPoint(-5, 10) 
                   << QPoint(positionScreen)+QPoint(-15, 0)
                   << QPoint(positionScreen)+QPoint(-5, -10)
                   << QPoint(positionScreen)+QPoint(5, -10);
              painter.drawText( pointToScreenPoint(position) + QPoint(10, 20), terms[i]->getName().c_str() );
              break;
            case Term::InOut:
              break;
            case Term::Tristate:
              break;
            case Term::Transcv:
              break;
            case Term::Unknown:
              break;
          }
          painter.drawPolygon(poly);
        }
      }
    }
  }
}  // Netlist namespace.