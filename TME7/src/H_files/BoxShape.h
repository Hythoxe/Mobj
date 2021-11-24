#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include <iostream>
#include <vector>
#include "Shape.h"
#include "Symbol.h"

namespace Netlist {

  class Shape;
  class BoxShape : public Shape {
    public:
                            BoxShape          ( Symbol*, const Box& );
                            BoxShape          ( Symbol*, int x1, int y1, int x2, int y2 );
                            ~BoxShape         ();
        inline  Box         getBoundingBox    () const;
                void        toXml             ( ostream& ) const;
        static  BoxShape*   fromXml           ( Symbol*, xmlTextReaderPtr );
    private:
        Box box_;
  };

  inline Box BoxShape::getBoundingBox() const{ return box_; }


}  // Netlist namespace.

#endif  // NETLIST_BOXSHAPE_H