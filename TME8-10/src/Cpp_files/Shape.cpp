#include  <libxml/xmlreader.h>
#include "../H_files/Shape.h"
#include "../H_files/LineShape.h"
#include "../H_files/BoxShape.h"
#include "../H_files/ArcShape.h"
#include "../H_files/EllipseShape.h"
#include "../H_files/TermShape.h"
#include "../H_files/Symbol.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    Shape::Shape( Symbol* owner ):
    owner_( owner )
    { owner_->add( this ); }

    Shape::~Shape()
    { owner_->remove( this ); }
    
    Shape* Shape::fromXml ( Symbol* owner, xmlTextReaderPtr reader ){
        // Factory-like method.
        const xmlChar* boxTag     = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
        const xmlChar* ellipseTag = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
        const xmlChar* arcTag     = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
        const xmlChar* lineTag    = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
        const xmlChar* termTag    = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
        const xmlChar* nodeName   = xmlTextReaderConstLocalName( reader );

        Shape* shape = NULL;
        if (boxTag == nodeName)
            shape = BoxShape::fromXml( owner, reader );
        if (ellipseTag == nodeName)
            shape = EllipseShape::fromXml( owner, reader );
        if (arcTag == nodeName)
            shape = ArcShape::fromXml( owner, reader );
        if (lineTag == nodeName)
            shape = LineShape::fromXml( owner, reader );
        if (termTag == nodeName)
            shape = TermShape::fromXml( owner, reader );

        if (shape == NULL)
            cerr << "[ERROR] Unknown or misplaced tag <" << nodeName << "> (line:"
                 << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;

        return shape;
    }


}
