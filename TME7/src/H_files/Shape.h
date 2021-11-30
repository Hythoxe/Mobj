#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include <iostream>
#include <vector>
#include "Box.h"
#include "Symbol.h"

#pragma once

namespace Netlist {
  
    using namespace std;
    
    class Shape {
        public:
                            Shape           ( Symbol* );
            virtual         ~Shape          ();
            inline  Symbol* getSymbol       () const;
            virtual Box     getBoundingBox  () const = 0;
            virtual void    toXml           ( ostream& ) const = 0;
            static  Shape*  fromXml         ( Symbol*, xmlTextReaderPtr );
        private:
            Symbol* owner_;
    };

    inline Symbol* Shape::getSymbol()const{ return owner_; }

}  // Netlist namespace.

#endif  // NETLIST_SHAPE_H