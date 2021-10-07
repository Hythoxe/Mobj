#include "Bench.h"
#include "GPL_2_text.h"

using namespace std;

namespace vector_bench{

    void backInsert(){
        Timer t;
        t = t.start();

        vector<string> GPL_2_vector;
		for(int i = 0; GPL_2_text[i] != NULL; i++){
            GPL_2_vector.push_back(string(GPL_2_text[i]));
		    //cout << GPL_2_text[i] << endl;
        }
			
		sort(GPL_2_vector.begin(),GPL_2_vector.end());
	    cout << "   Nombre de mot : " << GPL_2_vector.size() << endl;
        
        t = t.stop();
        cout << "   backInsert : " << t << endl;
	}
    void frontInsert(){
        Timer t;
        t = t.start();

        vector<string> GPL_2_vector;
        for(int i = 0; GPL_2_text[i] != NULL; i++){
            GPL_2_vector.insert(GPL_2_vector.end(), GPL_2_text[i]);
		    //cout << GPL_2_text[i] << endl;
        } 
        sort(GPL_2_vector.begin(),GPL_2_vector.end());

        t = t.stop();
	    cout << "   frontInsert : " << t << endl;
    }
    void sortEachInsert(){
        Timer t;
        t = t.start();

        vector<string> GPL_2_vector;
        for(int i = 0; GPL_2_text[i] != NULL; i++){
            GPL_2_vector.insert(GPL_2_vector.end(), GPL_2_text[i]);
		    //cout << GPL_2_text[i] << endl;
            sort(GPL_2_vector.begin(),GPL_2_vector.end());
        }

        t = t.stop();
	    cout << "   sortEachInsert : " << t << endl;
            
    }

}
