#include "Bench.h"
#include "GPL_2_text.h"

using namespace std;

namespace map_bench{
    void insert(){
        Timer t;
	    t = t.start();

		string str;
		map<string,int> GPL_2_map;
		map<string,int>::iterator it;
		for(int i = 0; GPL_2_text[i] != NULL; i++){
			str = string(GPL_2_text[i]);
			it = GPL_2_map.find(str);
			if (it != GPL_2_map.end())
			{
				it->second++;

			}
			else
			{
				GPL_2_map.insert(pair<string,int>(str,1));
			}
		}
        
        t = t.stop();
	    cout << "   insert exec. time : " << t << endl << endl;
	}
}

