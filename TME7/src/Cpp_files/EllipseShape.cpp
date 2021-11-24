#include  <libxml/xmlreader.h>
#include "../H_files/EllipseShape.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    EllipseShape::EllipseShape( Symbol* owner, const Box& box ):
    Shape( owner ),
    box_( box )
    {}

    EllipseShape::EllipseShape( Symbol* owner, int x1, int y1, int x2, int y2 ):
    Shape( owner ),
    box_( x1_, y1_, x2_, y2_ )
    {}

    EllipseShape::~EllipseShape(){}

    void EllipseShape::toXml( ostream& stream ){
        stream << indent << "<box x1=\"" << x1_.getX1()
                         << "\" y1=\""   << y1_.getY1()
                         << "\" x2=\""   << x2_.getX2()
                         << "\" y2=\""   << y2_.getY2()
                         << "\"/>\n";
    }

    EllipseShape* EllipseShape::fromXml( Symbol* symbol, xmlTextReaderPtr reader ){
        int x1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x1")).c_str());
        int y1 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1")).c_str());
        int x2 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x2")).c_str());
        int y2 = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2")).c_str());
        
        EllipseShape* EllipseShape = NULL;
        EllipseShape = new EllipseShape( symbol, x1, y1, x2, x2 );
        return EllipseShape;
    }
    
}
