#ifndef  NETLIST_TERM_H   
#define  NETLIST_TERM_H 

#include <string>
#include <libxml/xmlreader.h>
#include "Indentation.h"
#include "Node.h"
#include "Point.h"
#include "Instance.h"
#include "Cell.h"

#pragma once

namespace Netlist{

    using namespace std;
    
    class Net;

    class Term {
        public:
            enum            Type      { Internal = 1, External = 2 };
            enum            Direction { In = 1, Out = 2, InOut = 3, Tristate = 4, Transcv = 5, Unknown = 6 }; 
                                            Term        ( Cell*, const string& name, Direction );
                                            Term        ( Instance*, const Term * modelterm );
                                            ~Term       ();
            static          string          toString    ( Type );
            static          string          toString    ( Direction );
            static          Direction       toDirection ( string );
            inline          bool            isInternal  () const;
            inline          bool            isExternal  () const;
            inline const    string&         getName     () const;
            inline          Node *          getNode     ();
            inline          Net *           getNet      () const;
            inline          Cell *          getCell     () const;   
            inline          Cell *          getOwnerCell() const;   
            inline          Instance *      getInstance () const;   
            inline          Direction       getDirection() const;
            inline          Point           getPosition () const;
            inline          Type            getType     () const;
                            void            setNet      ( Net* );
            inline          void            setNet      ( const string& );
            inline          void            setDirection( Direction );
            inline          void            setPosition ( const Point& );
            inline          void            setPosition ( int x, int y );
                            void            toXml       ( ostream& );
                            Term*           fromXml     ( Cell*, xmlTextReaderPtr );
        private:
            void *          owner_;
            string          name_;
            Direction       direction_;
            Type            type_;
            Net*            net_;
            Node            node_;
    };
    

    inline bool             Term::isInternal()                const { return (type_ == Internal); }
    inline bool             Term::isExternal()                const { return (type_ == External); }
    inline const string&    Term::getName()                   const { return name_; }
    inline Node*            Term::getNode()                         { return &node_; }
    inline Net*             Term::getNet()                    const { return net_; }
    inline Cell*            Term::getCell()                   const { return (type_ == External ? static_cast<Cell*>(owner_) : NULL); }
    inline Instance*        Term::getInstance()               const { return (type_ == Internal ? static_cast<Instance*>(owner_) : NULL); }
    inline Cell*            Term::getOwnerCell()              const { return (type_ == External ? static_cast<Cell*>(owner_) : static_cast<Instance*>(owner_)->getCell()); }
    inline Term::Direction  Term::getDirection()              const { return direction_; }
    inline Point            Term::getPosition()               const { return node_.getPosition(); }
    inline Term::Type       Term::getType()                   const { return type_; }
    inline void             Term::setNet( const string& name )      { net_ = getOwnerCell()->getNet(name); }
    inline void             Term::setDirection( Term::Direction d ) { direction_ = d ; }
    inline void             Term::setPosition( const Point& p )     { node_.setPosition(p); }
    inline void             Term::setPosition( int x, int y )       { node_.setPosition(x,y); }
}

#endif // NETLIST_TERM_H