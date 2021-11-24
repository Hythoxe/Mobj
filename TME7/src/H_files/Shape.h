#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include <iostream>
#include <vector>
#include "Box.h"
#include "Symbol.h"

namespace Netlist {

  class Shape;

  class Shape {
    public:
                        Shape           ( Symbol* );
                        ~Shape          ();
        inline  Symbol* getSymbol       () const; 
                Box     getBoundingBox  () const;
                void    toXml           ( ostream& ) const;
        static  Shape*  fromXml         ( Net*, xmlTextReaderPtr );
    private:
        Symbol* symbol_;
  };

  inline Symbol* Shape::getSymbol()const{ return symbol_; }

}  // Netlist namespace.

#endif  // NETLIST_SHAPE_H