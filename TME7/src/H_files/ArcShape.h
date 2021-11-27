#ifndef NETLIST_ARCSHAPE_H
#define NETLIST_ARCSHAPE_H

#include <iostream>
#include <vector>
#include "Shape.h"
#include "Symbol.h"

namespace Netlist {

  class Shape;
  class ArcShape : public Shape {
    public:
                            ArcShape         ( Symbol*, const Box&, int start, int span );
                            ArcShape         ( Symbol*, int x1, int y1, int x2, int y2, int start, int span );
                            ~ArcShape        ();
        inline  int         getstart         () const;
        inline  int         getspan          () const;
        inline  Box         getBoundingBox   () const;
                void        toXml            ( ostream& ) const;
        static  ArcShape*   fromXml          ( Symbol*, xmlTextReaderPtr );
    private:
        Box box_;
        int start_, span_;
  };

  inline Box ArcShape::getBoundingBox() const{ return box_; }
  inline int ArcShape::getstart()       const{ return start_; }
  inline int ArcShape::getspan()        const{ return span_; }

}  // Netlist namespace.

#endif  // NETLIST_ARCSHAPE_H