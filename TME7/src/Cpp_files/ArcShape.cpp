#include  <libxml/xmlreader.h>
#include "../H_files/ArcShape.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    ArcShape::ArcShape( Symbol* owner, const Box& box, int start, int span ):
    Shape( owner ),
    box_( box ),
    start_( start ),
    span_( span )
    {}

    ArcShape::ArcShape( Symbol* owner, int x1, int y1, int x2, int y2, int start, int span ):
    Shape( owner ),
    box_( x1, y1, x2, y2 ),
    start_( start ),
    span_( span )
    {}

    ArcShape::~ArcShape(){}

    void ArcShape::toXml( ostream& stream ) const{
        stream << indent << "<box x1=\"" << box_.getX1()
                         << "\" y1=\""   << box_.getY1()
                         << "\" x2=\""   << box_.getX2()
                         << "\" y2=\""   << box_.getY2()
                         << "\" start=\""<< getstart()
                         << "\" span=\"" << getspan()
                         << "\"/>\n";
    }

    ArcShape* ArcShape::fromXml( Symbol* symbol, xmlTextReaderPtr reader ){
        int x1    = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x1")).c_str());
        int y1    = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1")).c_str());
        int x2    = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "x2")).c_str());
        int y2    = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2")).c_str());
        int start = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader,(const xmlChar*) "start")).c_str());
        int span  = atoi(xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"span")).c_str());
        
        ArcShape* arcShape = NULL;
        arcShape = new ArcShape( symbol, x1, y1, x2, y2, start, span );
        return arcShape;
    }
    
}
