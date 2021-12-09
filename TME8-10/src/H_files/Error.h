#ifndef NETLIST_ERROR_H
#define NETLIST_ERROR_H

# include <exception>

namespace Netlist{
    class Error: public std::exception {
        private:
            std::string message_ ;
        public:
            Error ( string message ) throw() { message_=message; };
        public:
            ~Error() throw () {};
        public:
            const char* what () const throw() { return message_.c_str(); };
    };

    /*while(true){
        switch (state) {
          // Reading node contents .
        } // End switch(state).
        throw Error ( "[ERROR] Cell::fromXml(): Unknown or misplaced tag." );
    } // End while(true).*/

}
#endif // NETLIST_ERROR_H