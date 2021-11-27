#include  <libxml/xmlreader.h>
#include "../H_files/Shape.h"
#include "../H_files/Term.h"
#include "../H_files/Cell.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    Shape::Shape( Symbol* owner ):
    owner_( owner ),
    shapes_( owner )
    {}

    Shape::~Shape()
    {}

    Box Symbol::BoxgetBoundingBox() const{

    Point Symbol::getTermPosition( Term* ) const{}

    TermShape* Symbol::getTermShap( Term* ) const{}
    
    void  Symbol::add ( Shape* shape ){
        if (getShape(shape->getName())) {
            cerr << "[ERROR] Attemp to add duplicated Shape <" << shape->getName() << ">." << endl;
            exit( 1 );
        }
        shapes_.push_back( shape );
    }

    void  Symbol::remove ( Shape* shape ){
        for ( vector<Shape*>::iterator ishape=shapes_.begin() ; ishape != shapes_.end() ; ++ishape ) {
            if(*ishape != NULL){
                if (*ishape == shape) shapes_.erase( ishape );
            }
        }
    }

    void Symbol::toXml ( std::ostream& ) const{}

    static Symbol* Symbol::fromXml( Cell*, xmlTextReaderPtr ){}

    

}