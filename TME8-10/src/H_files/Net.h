#ifndef  NETLIST_NET_H   
#define  NETLIST_NET_H   

#include <string>
#include <vector>
#include "Indentation.h"
#include "Term.h"

#pragma once

namespace Netlist{

    using namespace std;

    class Cell;
    class Node;

    class Net{
        public:
                                                Net( Cell *, const string&, Term::Type );
                                                ~Net();
            inline          Cell*               getCell       () const;
            inline const    string&             getName       () const;
            inline          unsigned int        getId         () const;
            inline          Term::Type          getType       () const;
            inline const    vector<Node*>&      getNodes      () const;
            inline const    vector<Line*>&      getLines      () const;
                            size_t              getFreeNodeId () const;
                            void                add           ( Node* );
                            void                add           ( Line* );
                            bool                remove        ( Node* );
                            bool                remove        ( Line* );
                            Node*               getNode       ( size_t );
                            void                toXml         ( ostream& );
                   static   Net*                fromXml       ( Cell*, xmlTextReaderPtr );
        private:
            Cell*           owner_;
            string          name_;
            unsigned int    id_;
            Term::Type      type_;
            vector<Node*>   nodes_;
            vector<Line*>   lines_;
    };


    inline Cell*                Net::getCell()  const{ return owner_; }
    inline const string&        Net::getName()  const{ return name_; }
    inline unsigned int         Net::getId()    const{ return id_; }
    inline Term::Type           Net::getType () const{ return type_; }
    inline const vector<Node*>& Net::getNodes() const{ return nodes_; }
    inline const vector<Line*>& Net::getLines() const{ return lines_; }
}

#endif // NETLIST_NET_H
