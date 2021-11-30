#include  <libxml/xmlreader.h>
#include "../H_files/TermShape.h"
#include "../H_files/Term.h"
#include "../H_files/Cell.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    TermShape::TermShape( Symbol* owner, string name, int x1, int y1, NameAlign align):
    Shape( owner ),
    term_(NULL),
    x1_( x1 ),
    y1_( y1 ),
    align_( align )
    {
        Cell* cell = owner->getCell();
        term_ = cell->getTerm( name );
    }

    TermShape::~TermShape(){}

    string TermShape::toString( TermShape::NameAlign name ){
        string s;
        switch (name){
            case 1: s = "top_left";
            break;
            case 2: s = "top_right"; 
            break;
            case 3: s = "Bottom_left";
            break;
            case 4: s = "Bottom_right";
            break;
        }
        return s;
    }

    TermShape::NameAlign TermShape::toNameAlign( string s ){
        if(s == "top_left")
            return TermShape::TopLeft;
        else if (s == "top_right")
            return TermShape::TopRight;
        else if (s == "Bottom_left")
            return TermShape::BottomLeft;
        else 
            return TermShape::BottomRight;
    }

    void TermShape::toXml( ostream& stream ) const{
        stream << indent << "<term name=\""<< term_->getName() 
                         << "\" x1=\""     << x1_
                         << "\" y1=\""     << y1_
                         << "\" align=\""  << toString(align_)
                         << "\"/>\n";
    }

    TermShape* TermShape::fromXml( Symbol* symbol, xmlTextReaderPtr reader ){
        string termName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name"));
        string align    = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"align"));
        int x1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x1")).c_str());
        int y1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1")).c_str());
        
        TermShape* termShape = NULL;
        termShape = new TermShape( symbol, termName, x1, y1, toNameAlign(align) );
        return termShape;
    }
    
}
