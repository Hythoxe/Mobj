#include  <cstdlib>
#include  "../H_files/Instance.h"
#include  "../H_files/Term.h"
#include  "../H_files/Cell.h"
#include  "../H_files/Net.h"

namespace Netlist {

    using namespace std;

    Term::Term( Cell* owner, const string& name, Term::Direction dir ):
    owner_(owner),
    name_(name),
    direction_(dir),
    type_(External),
    net_(),
    node_(this){
        owner->add(this);
    }

    Term::Term( Instance* owner, const Term * term ):
    owner_(owner),
    name_(term->getName()),
    direction_(term->getDirection()),
    type_(Internal),
    net_(),
    node_(this){
        owner->add(this);
    }

    Term::~Term(){
        if(type_ == External)
            static_cast<Cell*>(owner_)->remove(this);
        else
            static_cast<Instance*>(owner_)->remove(this);
    }

    string Term::toString( Term::Type t ){
        string s;
        switch (t){
            case 1: s = "Internal";
            break;
            case 2: s = "External"; 
            break;
        }
        return s;
    }

    string Term::toString( Term::Direction d ){
        string s;
        switch (d){
            case 1: s = "In";
            break;
            case 2: s = "Out"; 
            break;
            case 3: s = "InOut";
            break;
            case 4: s = "Tristate";
            break;
            case 5: s = "Transcv"; 
            break;
            case 6: s = "Unknown"; 
            break;
        }
        return s;
    }

    Term::Direction Term::toDirection( string s ){
        if(s == "In")
            return Term::In;
        else if (s == "Out")
            return Term::Out;
        else if (s == "InOut")
            return Term::InOut;
        else if (s == "Tristate")
            return Term::Tristate;
        else if (s == "Transcv")
            return Term::Transcv;
        else 
            return Term::Unknown;
    }

    void Term::setNet( Net* net ){
        if (net == NULL){
            if (net->getCell()!=getOwnerCell()){
                cerr<<"[ERROR: ]Term & Net de not belong to the same Cell."<<endl;
                return;
            };
        }   
        net_ = net;
        net->add(&node_);
    }

    void Term::setNet( const string& name ){
        net_ = getOwnerCell()->getNet(name);    
    }

    void Term::toXml( ostream& stream ){
        stream << indent << "<term name=\""   << name_ 
                         << "\" direction=\"" << toString(direction_) 
                         << "\"/>\n";
    }
}