// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/4-5>" -*-

#include  <limits>
#include  <libxml/xmlreader.h>
#include  "../H_files/Node.h"
#include  "../H_files/Term.h"
#include  "../H_files/Net.h"
#include  "../H_files/Instance.h"
#include  "../H_files/Cell.h"
#include  "../H_files/XmlUtil.h"

namespace Netlist {

  using namespace std;


  const size_t  Node::noid = numeric_limits<size_t>::max();


  Node::Node ( Term* term, size_t id  )
    : id_      (id)
    , term_    (term)
    , position_()
  { }


  Node::~Node ()
  {
    if (getNet()) getNet()->remove( this );
  }


  inline Net* Node::getNet () const { return term_->getNet(); }


// Node::toXml() Ã  Ã©crire ici.
  void Node::toXml ( ostream& stream ) const{
    if (term_->isInternal()) {
      stream << indent << "<node term=\""  << term_->getName()
                       << "\" instance=\"" << term_->getInstance()->getName()
                       << "\" id=\""       << id_;
    } else {
      stream << indent << "<node term=\""  << term_->getName() 
                       << "\" id=\""       << id_;
    }
    stream << "\" x=\"" << position_.getX() 
           << "\" y=\"" << position_.getY() 
           << "\"/>\n";
  }

  bool Node::fromXml ( Net* owner, xmlTextReaderPtr reader ){}

}  // Netlist namespace.
