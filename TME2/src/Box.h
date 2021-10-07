#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

namespace tme2{
    class Box
    {
        public:
        //constructeur 
                    Box();
                    Box( string name, long x1, long y1, long x2, long y2 );
                    Box( const Box& );
        //destructeur
                   ~Box();
        //accesseurs
            inline string  getName() const;
            inline long    getX1() const;
            inline long    getY1() const;
            inline long    getX2() const;
            inline long    getY2() const;
            inline long    getWidth() const;
            inline long    getHeight() const;
            inline static size_t  getAllocateds();
            bool    isEmpty() const;
            bool    intersect(const Box&) const;
            inline void    print(std::ostream&) const;
        //modificateur
            Box&    makeEmpty();
            inline Box&    inflate(long dxy);
            inline Box&    inflate(long dx, long dy);
            Box&    inflate(long dx1, long dy1, long dx2, long dy2);
            Box     getIntersection(const Box&);
        private:
            string name_;
            long x1_;
            long y1_;
            long x2_;
            long y2_;
            long x_;
            long y_;
            long wight_;
            long Height_;
            static size_t Allocateds_;
    };

    inline string  Box::getName() const{ return name_; };

    inline long    Box::getX1() const{ return x1_; };

    inline long    Box::getY1() const{ return y1_; };

    inline long    Box::getX2() const{ return x2_; };

    inline long    Box::getY2() const{ return y2_; };

    inline long    Box::getWidth() const{ return (!isEmpty()? x2_ - x1_:0); };

    inline long    Box::getHeight() const{ return (!isEmpty()? y2_ - y1_:0); };

    inline size_t  Box::getAllocateds() { return Allocateds_; };

    inline bool    Box::isEmpty() const{ return (x1_ > x2_) or (y1_ > y2_); };

    inline Box&    Box::inflate(long dxy){ return inflate( dxy, dxy, dxy, dxy ); };

    inline Box&    Box::inflate(long dx, long dy){ return inflate( dx, dy, dx, dy ); };

    inline void    Box::print(ostream&) const{cout <<"<\"" << getName() << "\" [ " << getX1() << " " << getY1() << " " << getX2() << " " << getY2() << " ]>" << endl;}
}