// -*- explicit-buffer-name: "Symbol.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_SYMBOL_H
#define NETLIST_SYMBOL_H

#include  <libxml/xmlreader.h>
#include  <string>
#include  <vector>
#include  "Box.h"

#pragma once

namespace Netlist {

  using namespace std;

  class Term;
  class Cell;
  class Shape;
  class TermShape;


  class Symbol {
    public:
                                        Symbol          ( Cell* );
                                       ~Symbol          ();
      inline Cell*                      getCell         () const;
             Box                        getBoundingBox  () const;
             Point                      getTermPosition ( Term* ) const;
             TermShape*                 getTermShape    ( Term* ) const;
      inline const vector<Shape*>       getShapes       () const;
             void                       add             ( Shape* );
             void                       remove          ( Shape* );
             void                       toXml           ( ostream& ) const;
             static Symbol*             fromXml         ( Cell*, xmlTextReaderPtr );
    private:                                            
                                        Symbol          ( const Symbol& );
             Symbol&                    operator=       ( const Symbol& );
    private:
      Cell*           owner_;
      vector<Shape*>  shapes_;
  };


  inline Cell* Symbol::getCell () const { return owner_; }
  inline const vector<Shape*>  Symbol::getShapes () const { return shapes_; }


}  // Netlist namespace.

#endif  // NETLIST_SYMBOL_H
