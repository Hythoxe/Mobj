#include  <libxml/xmlreader.h>
#include "../H_files/BoxShape.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    BoxShape::BoxShape( Symbol* owner, const Box& box ):
    Shape( owner ),
    box_( box )
    {}

    BoxShape::BoxShape( Symbol* owner, int x1, int y1, int x2, int y2 ):
    Shape( owner ),
    box_( x1, y1, x2, y2 )
    {}

    BoxShape::~BoxShape(){}

    void BoxShape::toXml( ostream& stream ) const{
        stream << indent << "<box x1=\"" << box_.getX1()
                         << "\" y1=\""   << box_.getY1()
                         << "\" x2=\""   << box_.getX2()
                         << "\" y2=\""   << box_.getY2()
                         << "\"/>\n";
    }

    BoxShape* BoxShape::fromXml( Symbol* symbol, xmlTextReaderPtr reader ){
        int x1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x1")).c_str());
        int y1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1")).c_str());
        int x2 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x2")).c_str());
        int y2 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2")).c_str());
        
        BoxShape* boxShape = NULL;
        boxShape = new BoxShape( symbol, x1, y1, x2, y2 );
        return boxShape;
    }
    
}
