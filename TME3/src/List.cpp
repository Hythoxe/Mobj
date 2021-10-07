#include "Bench.h"
#include "GPL_2_text.h"

using namespace std;

namespace list_bench{

    void backInsert(){
        Timer t;
        t = t.start();

        list<string> GPL_2_list;
        for(int i = 0; GPL_2_text[i] != NULL; i++){
            GPL_2_list.push_back(GPL_2_text[i]);
		    //cout << GPL_2_text[i] << endl;
        }
		GPL_2_list.sort();

        t = t.stop();
        cout << "   backInsert : " << t << endl;
    }
    void frontInsert(){
        Timer t;
        t = t.start();

        list<string> GPL_2_list;
        for(int i = 0; GPL_2_text[i] != NULL; i++){
            GPL_2_list.push_front(GPL_2_text[i]);
		    //cout << GPL_2_text[i] << endl;
        }
		GPL_2_list.sort();

        t = t.stop();
	    cout << "   frontInsert : " << t << endl;
    }
    void sortEachInsert(){
        Timer t;
        t = t.start();

        list<string> GPL_2_list;
        for(int i = 0; GPL_2_text[i] != NULL; i++){
            GPL_2_list.push_front(GPL_2_text[i]);
		    //cout << GPL_2_text[i] << endl;
		    GPL_2_list.sort();
        }
        
        t = t.stop();
	    cout << "   sortEachInsert : " << t << endl;
    }
}

