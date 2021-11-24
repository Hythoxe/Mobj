#ifndef NETLIST_TERMSHAPE_H
#define NETLIST_TERMSHAPE_H

#include <iostream>
#include <vector>
#include "Shape.h"
#include "Symbol.h"

namespace Netlist {

  using namespace std;

  class Shape;
  class TermShape : public Shape {
    public:
                enum        NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight };
    public:
                            TermShape         ( Symbol*, string name, int x1, int y1, NameAlign );
                            ~TermShape        ();
        inline  Term*       getTerm           () const;
        inline  int         getX              () const;
        inline  int         getY              () const;
        inline  NameAlign   getAlign          () const;
        inline  Point       getPosition       () const;
                string      toString          ( NameAlign ) 
        static  NameAlign   toNameAlign       ( string );
        inline  Box         getBoundingBox    () const;
                void        toXml             ( ostream& ) const;
        static  TermShape*  fromXml           ( Symbol*, xmlTextReaderPtr );
    private:
        Term* term_;
        int x_ , y_;
        NameAlign align_;
  };

  inline Box ArcShape::getBoundingBox() const{ return box_; }
  inline int       TermShape::getTerm()   const{ return term_; }
  inline int       TermShape::getX()      const{ return x_; }
  inline int       TermShape::getY()      const{ return y_; }
  inline NameAlign TermShape::getAlign()  const{ return align_; }
  inline Point     TermShape::getPosition()  const{ return Point(x_, y_); }



}  // Netlist namespace.

#endif  // NETLIST_TERMSHAPE_H