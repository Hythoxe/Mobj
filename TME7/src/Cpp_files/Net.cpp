#include <libxml/xmlreader.h>
#include "../H_files/Net.h"
#include "../H_files/Cell.h"
#include "../H_files/Node.h"
#include "../H_files/Line.h"
#include "../H_files/XmlUtil.h"

namespace Netlist {

    using namespace std;

    Net::Net(Cell* owner, const string& name, Term::Type type):
    owner_(owner),
    name_(name),
    id_(owner->newNetId()),
    type_(type),
    nodes_(){
        owner_->add(this);
    }

    Net::~Net(){
        owner_->remove(this);
    }

    void Net::add(Node* node){
        /*size_t size = getFreeNodeId();
        nodes_.push_back(node);
        node->setId(size);*/
        if(not node) return;
        size_t id = node->getId();
        if(id==Node::noid){
            id=getFreeNodeId();
            node->setId(id);
        }
        if(id < nodes_.size()){
            if(nodes_[id]!=NULL)
                nodes_[id]->setId(Node::noid);
            nodes_[id]=node;
        }
        else{
            for(size_t i=nodes_.size();i<id;i++)
                nodes_.push_back(NULL);
            nodes_.push_back(node);
        }
    }

    void  Net::add ( Line* line ){ 
        if (line) lines_.push_back( line ); 
    }

    bool Net::remove(Node* node){
        for ( vector<Node*>::iterator inode=nodes_.begin() ; inode != nodes_.end() ; ++inode ) {
            if(*inode != NULL){
                if (*inode == node) nodes_.erase( inode );
                return true;
            }
        }
        return false;
    }

    bool  Net::remove ( Line* line ){
        if (line) {
            for ( vector<Line*>::iterator il = lines_.begin()
                ; il != lines_.end() ; ++il ) {
                if (*il == line) {
                    lines_.erase( il );
                    return true;
                }
            }
        }
        return false;
    }

    size_t Net::getFreeNodeId() const{
        for (size_t i=0; i<nodes_.size(); i++){
            if(nodes_[i]==NULL)
                return i;
        }
        return nodes_.size();
    }

    Node* Net::getNode ( size_t id ){
        for (vector<Node*>::iterator inodeid = nodes_.begin() ; inodeid != nodes_.end() ; ++inodeid) {
            if(*inodeid != NULL)
                if((*inodeid)->getId() == id ) return *inodeid;
        }
        return NULL;
    }

    void Net::toXml( ostream& stream ){
        stream << indent++ << "<net name=\"" << name_ 
                           << "\" type=\""   << Term::toString(type_) 
                           << "\"/>\n";
        for (vector<Node*>::iterator inode = nodes_.begin() ; inode != nodes_.end() ; ++inode) {
            if(*inode != NULL)
                (*inode)->toXml(stream);
        }
        for (vector<Line*>::iterator iline = lines_.begin() ; iline != lines_.end() ; ++iline) {
            if(*iline != NULL)
                (*iline)->toXml(stream);
        }
        stream << --indent << "</net>\n";
    }

    Net* Net::fromXml( Cell* owner, xmlTextReaderPtr reader ){
        const xmlChar* netTag = xmlTextReaderConstString( reader, (const xmlChar*)"net" );

        string netName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name"));
        string netType = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"type"));

        Term::Type type = Term::toType(netType);
        Net* net = NULL;
        net = new Net( owner, netName, type );

        while ( true ) {
            int status = xmlTextReaderRead(reader);
            if (status != 1) {
                if (status != 0) {
                    cerr << "[ERROR] Net::fromXml(): Unexpected termination of the XML parser." << endl;
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
            
            if (Node::fromXml(net,reader)) continue;

            else if (Line::fromXml(net,reader)) continue;
            
            if ( (nodeName == netTag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) )
                break;
                
        }
        return net;
    }

}