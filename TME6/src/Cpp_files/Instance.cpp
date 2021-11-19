#include <libxml/xmlreader.h>
#include "../H_files/Instance.h"
#include "../H_files/Term.h"
#include "../H_files/XmlUtil.h"


namespace Netlist {

    using namespace std;
    
    Instance::Instance( Cell* owner, Cell* model, const std::string& name ):
    owner_(owner),
    masterCell_(model),
    name_(name),
    terms_(),
    position_(){
        /*if (model != NULL){
            for(Term* iterm : model -> getTerms())
                terms_.push_back(new Term(this, iterm));
        }*/
        for (Term* t : masterCell_->getTerms())
           new Term(this,t);
        owner->add(this);    
    }
  
    Instance::~Instance(){
        for (Term* t : terms_) delete t;
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
                         << "\"/>\n";
    }

    Instance* Instance::fromXml ( Cell* owner, xmlTextReaderPtr reader ){
        const xmlChar* instanceTag = xmlTextReaderConstString( reader, (const xmlChar*)"instance" );
        
        string instanceName     = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name"));
        string masterCellName   = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"mastercell"));

        Cell* masterCell = Cell::find(masterCellName);
        Instance* instance = new Instance( owner, masterCell, instanceName );

        while ( true ) {
            int status = xmlTextReaderRead(reader);
            if (status != 1) {
                if (status != 0) {
                cerr << "[ERROR] Instance::fromXml(): Unexpected termination of the XML parser." << endl;
                }
                break;
            }

            switch ( xmlTextReaderNodeType(reader) ) {
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                continue;
            }

            const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
            
            if (Instance::fromXml(owner, reader)) continue;
            
            if ( (nodeName == instanceTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) )
                continue;

            else cerr << "[ERROR] Instance::fromXml(): Unknown or misplaced tag <" << instanceName
                      << "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
        }
        return instance;
    }

}