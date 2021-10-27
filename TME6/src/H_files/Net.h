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
                            size_t              getFreeNodeId () const;
                            void                add           ( Node* );
                            bool                remove        ( Node* );
                            void                toXml         ( ostream& );
                            Net*                fromXml       ( Cell*, xmlTextReaderPtr );
        private:
            Cell*           owner_;
            string          name_;
            unsigned int    id_;
            Term::Type      type_;
            vector<Node*>   nodes_;
    };


    inline Cell*                Net::getCell()  const{ return owner_; }
    inline const string&        Net::getName()  const{ return name_; }
    inline unsigned int         Net::getId()    const{ return id_; }
    inline Term::Type           Net::getType () const{ return type_; }
    inline const vector<Node*>& Net::getNodes() const{ return nodes_; }
}

#endif // NETLIST_NET_H
