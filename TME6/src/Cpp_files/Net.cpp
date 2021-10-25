#include  <cstdlib>
#include  <libxml/xmlreader.h>
#include  "../H_files/Net.h"
#include  "../H_files/Cell.h"
#include  "../H_files/Node.h"
#include  "../H_files/XmlUtil.h"

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
        size_t size = getFreeNodeId();
        nodes_.push_back(node);
        node->setId(size);
    }

    bool Net::remove(Node* node){
        if (node){
            for (vector<Node* > ::iterator inode = nodes_.begin() ; inode != nodes_.end() ; ++inode){
                if (*inode == node){
                    nodes_.erase(inode);
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

    void Net::toXml( ostream& stream ){
        stream << indent++ << "<net name=\"" << name_ 
                           <<"\" type=\""    << Term::toString(type_) 
                           << "\"/>\n";
        for (vector<Node*>::iterator inode=nodes_.begin() ; inode != nodes_.end() ; ++inode) {
            if(*inode != NULL)
                (*inode)->toXml(stream);
        }
        stream << --indent << "</net>\n";
    }

    Net* Net::fromXml ( Cell* owner, xmlTextReaderPtr reader ){}

}