#ifndef NETLIST_LINESHAPE_H
#define NETLIST_LINESHAPE_H

#include <iostream>
#include <vector>
#include "Shape.h"
#include "Net.h"
#include "Symbol.h"

namespace Netlist {

  using namespace std;

  class Shape;

  class LineShape : public Shape {
    public:
                            LineShape         ( Symbol*, int x1, int y1, int x2, int y2 );
                            ~LineShape        ();
                Box         getBoundingBox    () const;
                void        toXml             ( ostream& ) const;
        static  LineShape*  fromXml           ( Symbol*, xmlTextReaderPtr );
    private:
        int x1_, y1_, x2_, y2_;
  };

}  // Netlist namespace.

#endif  // NETLIST_LINESHAPE_H