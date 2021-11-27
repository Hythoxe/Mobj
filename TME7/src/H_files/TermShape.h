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
        inline  Box         getBoundingBox    () const;
        inline  Term*       getTerm           () const;
        inline  int         getX              () const;
        inline  int         getY              () const;
        inline  NameAlign   getAlign          () const;
        inline  Point       getPosition       () const;
        static  string      toString          ( NameAlign );
        static  NameAlign   toNameAlign       ( string );
                void        toXml             ( ostream& ) const;
        static  TermShape*  fromXml           ( Symbol*, xmlTextReaderPtr );
    private:
        Symbol* owner_ ;
        Term* term_;
        int x1_, y1_;
        NameAlign align_;
  };

  inline Box       TermShape::getBoundingBox()  const{ return Box(x1_, y1_, x1_, y1_); }
  inline Term*     TermShape::getTerm()         const{ return term_; }
  inline int       TermShape::getX()            const{ return x1_; }
  inline int       TermShape::getY()            const{ return y1_; }
  inline TermShape::NameAlign TermShape::getAlign()        const{ return align_; }
  inline Point     TermShape::getPosition()     const{ return Point(x1_, y1_); }



}  // Netlist namespace.

#endif  // NETLIST_TERMSHAPE_H