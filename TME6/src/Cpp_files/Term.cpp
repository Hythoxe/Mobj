#include <cstdlib>
#include <libxml/xmlreader.h>
#include "../H_files/Term.h"
#include "../H_files/Net.h"
#include "../H_files/XmlUtil.h"

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

    Term::Term( Instance* owner, const Term * modelterm ):
    owner_(owner),
    name_(modelterm->getName()),
    direction_(modelterm->getDirection()),
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

    string Term::toString( Term::Type type ){
        string s;
        switch (type){
            case 1: s = "Internal";
            break;
            case 2: s = "External"; 
            break;
        }
        return s;
    }

    string Term::toString( Term::Direction dir ){
        string s;
        switch (dir){
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

    Term::Type Term::toType( string s ){
        if(s == "External")
            return Term::External;
        else
            return Term::Internal;
    }

    void Term::setNet( Net* net ){ 
        net_ = net;
        net->add(&node_);
    }

    void Term::toXml( ostream& stream ){
        stream << indent << "<term name=\""   << name_ 
                         << "\" direction=\"" << toString(direction_) 
                         << "\" x=\""         << this->getPosition().getX() 
                         << "\" y=\""         << this->getPosition().getY() 
                         << "\"/>\n";
    }

    Term* Term::fromXml ( Cell* owner, xmlTextReaderPtr reader ){
        const xmlChar* termTag = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
        
        string termName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name"));
        string termDir  = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"direction"));

        int x = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x")).c_str());
        int y = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y")).c_str());
        
        Term* term = NULL
        term = new Term( owner, termName, toDirection(termDir) );
        term->Term::setPosition(x,y);

        while ( true ) {
            int status = xmlTextReaderRead(reader);
            if (status != 1) {
                if (status != 0) {
                cerr << "[ERROR] Term::fromXml(): Unexpected termination of the XML parser." << endl;
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
            
            if (Term::fromXml(owner, reader)) continue;
            
            if ( (nodeName == termTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) )
                continue;

            else cerr << "[ERROR] Term::fromXml(): Unknown or misplaced tag <" << termName
                      << "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
        }
        return term;
    }
}