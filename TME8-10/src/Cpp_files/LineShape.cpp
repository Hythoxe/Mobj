#include  <libxml/xmlreader.h>
#include "../H_files/LineShape.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    LineShape::LineShape( Symbol* owner, int x1, int y1, int x2, int y2 ):
    Shape( owner ),
    x1_( x1 ),
    y1_( y1 ),
    x2_( x2 ),
    y2_( y2 )
    {}

    LineShape::~LineShape(){}

    void LineShape::toXml( ostream& stream ) const{
        stream << indent << "<line x1=\"" << x1_ 
                         << "\" y1=\""    << y1_ 
                         << "\" x2=\""    << x2_
                         << "\" y2=\""    << y2_
                         << "\"/>\n";
    }

    LineShape* LineShape::fromXml( Symbol* symbol, xmlTextReaderPtr reader ){
        int x1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x1")).c_str());
        int y1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1")).c_str());
        int x2 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x2")).c_str());
        int y2 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2")).c_str());
        
        LineShape* lineShape = NULL;
        lineShape = new LineShape( symbol, x1, y1, x2, y2 );
        return lineShape;
    }
}
