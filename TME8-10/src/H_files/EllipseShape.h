#ifndef NETLIST_ELLIPSESHAPE_H
#define NETLIST_ELLIPSESHAPE_H

#include <iostream>
#include <vector>
#include "Shape.h"
#include "Symbol.h"

#pragma once

namespace Netlist {

    using namespace std;
    
    class Shape;
    
    class EllipseShape : public Shape {
        public:
                                    EllipseShape      ( Symbol*, const Box& );
                                    EllipseShape      ( Symbol*, int x1, int y1, int x2, int y2 );
                                    ~EllipseShape     ();
            inline  Box             getBoundingBox    () const;
                    void            toXml             ( ostream& ) const;
            static  EllipseShape*   fromXml           ( Symbol*, xmlTextReaderPtr );
        private:
            Box box_;
    };

    inline Box EllipseShape::getBoundingBox() const{ return box_; }

}  // Netlist namespace.

#endif  // NETLIST_ELLIPSESHAPE_H