#ifndef NETLIST_LINESHAPE_H
#define NETLIST_LINESHAPE_H

#include <iostream>
#include <vector>
#include "Shape.h"
#include "Symbol.h"

#pragma once

namespace Netlist {

    using namespace std;

    class Shape;

    class LineShape : public Shape {
        public:
                                LineShape         ( Symbol*, int x1, int y1, int x2, int y2 );
                                ~LineShape        ();
            inline  Box         getBoundingBox    () const;
                    void        toXml             ( ostream& ) const;
            static  LineShape*  fromXml           ( Symbol*, xmlTextReaderPtr );
        private:
            int x1_, y1_, x2_, y2_;
    };

    inline Box LineShape::getBoundingBox() const{ return Box(x1_, y1_, x2_, y2_); };

}  // Netlist namespace.

#endif  // NETLIST_LINESHAPE_H