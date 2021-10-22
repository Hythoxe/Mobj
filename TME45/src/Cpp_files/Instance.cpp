#include  "../H_files/Instance.h"
#include  "../H_files/Term.h"

namespace Netlist {

    using namespace std;
    
    Instance::Instance( Cell* owner, Cell* model, const std::string& name ):
    owner_(owner),
    masterCell_(model),
    name_(name),
    terms_(),
    position_(){
        if (model != NULL){
            for(Term* iterm : model -> getTerms()){
                terms_.push_back(new Term(this, iterm));
            }
        }
        owner->add(this);    
    }
  
    Instance::~Instance(){
        owner_->remove(this);
    }

    Term* Instance::getTerm( const string& name ) const{
        for (vector<Term*>::const_iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm) {
            if(*iterm != NULL){
                if((*iterm)->getName() == name)  return *iterm;  
            }
        }
        return NULL;
    }

    bool Instance::connect( const std::string& name, Net * net ){
        Term* term = getTerm( name );
        if (term == NULL) return false;
    
        term->setNet( net );
        return true;
    }

    void Instance::add( Term * term ){
        if (getTerm(term->getName())){
            cerr << "[ERROR] Attemp to add duplicated terminal <" << term->getName() << ">." << endl;
            exit( 1 );
        }
        terms_.push_back( term );
    }

    void Instance::remove( Term * term ){
        for (vector<Term*>::iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm) {
            if(*iterm != NULL){
                if (*iterm == term) terms_.erase(iterm);   
            }
        }
    }

    void Instance::toXml( ostream& stream ){
        stream << indent << "<instance name=\"" << name_ 
                         << "\" mastercell=\""  << masterCell_->getName()
                         << "\" x=\""           << position_.getX() 
                         << "\" y=\""           << position_.getY() << "\"/>\n";
    }
}