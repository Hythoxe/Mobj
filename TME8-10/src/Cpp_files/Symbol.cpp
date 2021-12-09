#include  <libxml/xmlreader.h>
#include "../H_files/Shape.h"
#include "../H_files/Term.h"
#include "../H_files/Cell.h"
#include "../H_files/TermShape.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    Symbol::Symbol( Cell* owner ):
    owner_( owner ),
    shapes_()
    {}

    Symbol::~Symbol()
    {}

    Box Symbol::getBoundingBox() const{
        Box box;
        for ( vector<Shape*>::const_iterator ishape=shapes_.begin() ; ishape != shapes_.end() ; ++ishape ) {
            box.merge((*ishape)->getBoundingBox());
        }
        return box;
    }

    Point Symbol::getTermPosition( Term* term ) const{
        TermShape* termShape = getTermShape(term);
        if(termShape)
            return termShape->getPosition();
        return Point(-1, -1);
    }

    TermShape* Symbol::getTermShape( Term* term ) const{
        TermShape* termShape;
        for( vector<Shape*>::const_iterator ishape=shapes_.begin() ; ishape != shapes_.end() ; ++ishape ){
            termShape = dynamic_cast<TermShape*>(*ishape);
            if (termShape && termShape->getTerm() == term)
                    return termShape;
        }
        return NULL;
    }
    
    void  Symbol::add( Shape* shape ){
        shapes_.push_back( shape );
    }

    void  Symbol::remove( Shape* shape ){
        for ( vector<Shape*>::iterator ishape=shapes_.begin() ; ishape != shapes_.end() ; ++ishape ) {
            if(*ishape != NULL){
                if (*ishape == shape) shapes_.erase( ishape );
            }
        }
    }

    void Symbol::toXml ( ostream& stream ) const{
        stream << indent++ << "<symbol>\n";
        for ( vector<Shape*>::const_iterator ishape=shapes_.begin() ; ishape != shapes_.end() ; ++ishape ) {
            (*ishape)->toXml( stream );
        }
        stream << --indent << "</symbol>\n";
    }

    Symbol* Symbol::fromXml( Cell* owner, xmlTextReaderPtr reader ){
        const xmlChar* symbolTag = xmlTextReaderConstString( reader, (const xmlChar*)"symbol" );  // TME7
    
        Symbol* symbol = owner->getSymbol();

        while ( true ) {
            int status = xmlTextReaderRead(reader);
            if (status != 1) {
                if (status != 0) {
                    cerr << "[ERROR] Symbol::fromXml(): Unexpected termination of the XML parser." << endl;
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
            
            if (Shape::fromXml(symbol, reader)) continue;

            if ( (nodeName == symbolTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) ) {
                break;
            }
        }
        return symbol;
    }

    

}