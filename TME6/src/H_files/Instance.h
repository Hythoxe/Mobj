#ifndef  NETLIST_INSTANCE_H   
#define  NETLIST_INSTANCE_H   

#include <iostream>
#include <vector>
#include <libxml/xmlreader.h>
#include "Point.h"

#pragma once

namespace Netlist{

    using namespace std;

    class Cell;
    class Term;
    class Net;

    class Instance{
        public:
                                                Instance        (Cell* owner, Cell* model, const string&);
                                                ~Instance       ();
            inline const    string&             getName         () const;
            inline          Cell*               getMasterCell   () const;
            inline          Cell*               getCell         () const;
            inline const    vector<Term*>&      getTerms        () const;
                            Term*               getTerm         (const string&) const;
            inline          Point               getPosition     () const;
                            bool                connect         (const string& name, Net*);
                            void                add             (Term*);
                            void                remove          (Term*);
            inline          void                setPosition     (const Point&);
            inline          void                setPosition     (int x, int y);
                            void                toXml           (ostream&);
                   static   Instance*           fromXml         ( Cell*, xmlTextReaderPtr );

        private:
            Cell*           owner_;
            Cell*           masterCell_;
            string          name_;
            vector<Term*>   terms_;
            Point           position_;
    };
    
    inline const string&        Instance::getName()                     const { return name_; }
    inline Cell*                Instance::getMasterCell()               const { return masterCell_; }
    inline Cell*                Instance::getCell()                     const { return owner_; }
    inline const vector<Term*>& Instance::getTerms()                    const { return terms_; }
    inline Point                Instance::getPosition()                 const { return position_; }
    inline void                 Instance::setPosition( const Point& p )       { setPosition(p.getX(), p.getY()); }
    inline void                 Instance::setPosition( int x , int y )        { position_ = Point(x,y); }
}
#endif // NETLIST_INSTANCE_H