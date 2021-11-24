#include  <libxml/xmlreader.h>
#include "../H_files/TermShape.h"
#include "../H_files/Term.h"
#include "../H_files/Cell.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    TermShape::TermShape( Symbol*, string name, int x1, int y1, TermShape::NameAlign align):
    Shape( owner ),
    term_(NULL),
    x_( x1 ),
    y_( x1 )
    {}

    TermShape::TermShape( Symbol* owner, int x1, int y1, int x2, int y2, int start, int span ):
    Shape( owner ),
    box_( x1_, y1_, x2_, y2_ ),
    start_( start ),
    span_( span )
    {}

    TermShape::~TermShape(){}

    string TermShape::toString( Term::Direction dir ){
        string s;
        switch (dir){
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

    void TermShape::toXml( ostream& stream ){
        stream << indent << "<term name=\""<< term_->getName 
                         << "\" x1=\""     << x1_
                         << "\" y1=\""     << y1_
                         << "\" x2=\""     << x2_
                         << "\" y2=\""     << y2_
                         << "\" align=\""  << toString(align_)
                         << "\"/>\n";
    }

    TermShape* TermShape::fromXml( Symbol* symbol, xmlTextReaderPtr reader ){
        string termName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name"));
        string align    = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"align"));
        int x1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x1")).c_str());
        int y1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1")).c_str());
        
        TermShape* TermShape = NULL;
        TermShape = new TermShape( symbol, termName, x1, y1, toNameAlign(align) );
        return TermShape;
    }
    
}
