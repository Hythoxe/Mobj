#include "Bench.h"

using namespace std;

int main ( int argc, char* argv[] ){

    // VECTOR
    cout << "Vector Bench Test" << endl;
    vector_bench::backInsert();
	vector_bench::frontInsert();
	vector_bench::sortEachInsert();
    cout << endl;
	
    // LIST
    cout << "List Bench Test" << endl;
    list_bench::backInsert();
	list_bench::frontInsert();
	list_bench::sortEachInsert();
    cout << endl;

    // MAP
    cout << "Map Bench Test" << endl;
	map_bench::insert();

    return 0;
}