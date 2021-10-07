#include <iostream>
#include "Box.h"

using namespace std;
using namespace tme2;

Box testFunction ( Box ab ){ 
    cerr << "  + testFunction() called." << endl;
    cerr << "Construction de "; Box area ( "area", 0, 0, 15, 50);
    cerr << "  | Intersection between:" << endl;
    cerr << "  |   "; area.print(cerr);
    cerr << "  |   "; ab.print(cerr)  ;
    cerr << "  | Gives:\n";
    if ( area.intersect(ab) ) {
      cerr << "  |   "; area.getIntersection(ab);
    } else
      cout << "  |   No Intersection" << endl;  
    return ab;
}

int main(int argc, char* argv[]){
    Box b0;
    cerr << "Construction de "; Box b1 ( "b1", 15, 10, 30, 20 );

    cerr << "Allocated boxes: " << Box::getAllocateds() << endl;
    
    cerr << "\nTest 1: \n"; b1.print(cerr);
    testFunction(b1);
    
    b1.inflate( 5, 5, 5, 5 );
    cerr << "\nTest 2: \n"; b1.print(cerr);
    testFunction(b1);
    
    cerr << "\nTest 3: " << endl;
    cerr << "+ Box \"" << b1.getName() << "\" empty: " << boolalpha << b1.isEmpty() << endl;
    cerr << "| Box \"" << b1.getName() << "\" width: " << b1.getWidth() << endl;
    cerr << "| Box \"" << b1.getName() << "\" height: " << b1.getHeight() << endl;
    
    b1.inflate( -11 );
    cerr << "+ Box \"" << b1.getName() << "\" empty: " << boolalpha << b1.isEmpty() <<" (inflated -11)"<< endl;
    cerr << "| Box \"" << b1.getName() << "\" width: " << b1.getWidth() << endl;
    cerr << "| Box \"" << b1.getName() << "\" height: " << b1.getHeight() << endl << endl;

    cerr << "Allocated boxes: " << Box::getAllocateds() << endl;
    
    return 0;
}