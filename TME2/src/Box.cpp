#include <iostream>
#include "Box.h"
using namespace std;

namespace tme2{

    size_t Box::Allocateds_= 0;

    Box::Box():name_("no"), x1_(1), y1_(1), x2_(1), y2_(1){
        cerr << "Debug: Box::Box() <\"" << getName() << "\" [ " << getX1() << " " << getY1() << " " << getX2() << " " << getY2() << " ]>" << endl;
        ++Allocateds_;
    }//Debug: Box::Box() <"NAME" [x1 y1 x2 y2]>

    Box::Box(string name, long x1, long y1, long x2, long y2):
        name_(name), x1_(x1), y1_(y1), x2_(x2), y2_(y2){
        cerr << "\"" << name << "\" [ " << x1 << " " << y1 << " " << x2 << " " << y2 << " ]" << endl;
        cerr << "Debug: Box::Box(string, ...) <" << getName() << " [ " << getX1() << " " << getY1() << " " << getX2() << " " << getY2() << " ]>" << endl; 
        if (x1_ > x2_) swap (x1_, x2_);
        if (y1_ > y2_) swap (y1_, y2_);


    }//Debug: Box::Box(string, ...) <"NAME" [x1 y1 x2 y2]>

    Box::Box ( const Box& b ): 
        name_(b.name_), x1_(b.x1_), y1_(b.y1_), x2_(b.x2_), y2_(b.y2_){
            cerr << "Debug: Box::Box(const Box&) <\"" << getName() << "\" [ " << getX1() << " " << getY1() << " " << getX2() << " " << getY2() << " ]>" << endl;
    }//Debug: Box::Box(const Box&) <"NAME" [x1 y1 x2 y2]>

    Box::~Box(){
        cerr << "Destruction de \"" << name_ << "\"" << endl;
        cerr << "Debug: Box::~Box() <\"" << getName() << "\" [ " << getX1() << " " << getY1() << " " << getX2() << " " << getY2() << " ]>" << endl;
        if (Allocateds_ > 0) --Allocateds_;
    }//Debug: Box::~Box() <"NAME" [x1 y1 x2 y2]>

    

    bool    Box::intersect(const Box& b) const{
        if ( isEmpty() or  b.isEmpty()) return false;
        if (((x2_ <= b.x1_) or (x1_ >= b.x2_)) and ((y2_ <= b.y1_) or (y1_ >= b.y2_))) return false;
        return true;
    }

    
    
    Box&    Box::inflate(long dx1, long dy1, long dx2, long dy2){
        x1_ -= dx1;
        y1_ -= dy1;
        x2_ += dx2;
        y2_ += dy2;
    
        return *this;
    }

    Box     Box::getIntersection(const Box& b){
        if (not intersect(b)) return Box();
        return Box (  name_+"."+b.name_
                    , max(x1_,b.x1_)
                    , max(y1_,b.y1_)
                    , min(x2_,b.x2_)
                    , min(y2_,b.y2_));
    }

    Box&    Box::makeEmpty(){
        x1_ = 1;
        y1_ = 1;
        x2_ = -1;
        y2_ = -1;
        ++Allocateds_;

        return *this;
    }
}

