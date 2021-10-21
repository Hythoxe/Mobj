// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/4-5>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "../H_files/Term.h"
#include "../H_files/Net.h"
#include "../H_files/Instance.h"
#include "../H_files/Cell.h"
using namespace Netlist;


int main ( int argc, char* argv[] )
{
  cout << "\nConstruction du modele <and2>." << endl;
  Cell* and2 = new Cell ( "and2" );
  new Term( and2, "i0", Term::In  );
  new Term( and2, "i1", Term::In  );
  new Term( and2,  "q", Term::Out );
  //and2->toXml( cout );

  cout << "\nConstruction du modele <or2>." << endl;
  Cell* or2 = new Cell ( "or2" );
  new Term( or2, "i0", Term::In  );
  new Term( or2, "i1", Term::In  );
  new Term( or2,  "q", Term::Out );
  //or2->toXml( cout );

  cout << "\nConstruction du modele <xor2>." << endl;
  Cell* xor2 = new Cell ( "xor2" );
  new Term( xor2, "i0", Term::In  );
  new Term( xor2, "i1", Term::In  );
  new Term( xor2,  "q", Term::Out );
  //xor2->toXml( cout );

  cout << "\nConstruction du modele <halfadder>." << endl;
  Cell* halfadder = new Cell ( "halfadder" );
  new Term( halfadder, "a"   , Term::In  );
  new Term( halfadder, "b"   , Term::In  );
  new Term( halfadder, "sout", Term::Out );
  new Term( halfadder, "cout", Term::Out );
  Net*      ha_a    = new Net      ( halfadder, "a"   , Term::External );
  Net*      ha_b    = new Net      ( halfadder, "b"   , Term::External );
  Net*      ha_sout = new Net      ( halfadder, "sout", Term::External );
  Net*      ha_cout = new Net      ( halfadder, "cout", Term::External );
  Instance* ha_xor2 = new Instance ( halfadder, Cell::find("xor2"), "xor2_1" );
  Instance* ha_and2 = new Instance ( halfadder, Cell::find("and2"), "and2_1" );
  halfadder->connect( "a"   , ha_a    );
  halfadder->connect( "b"   , ha_b    );
  halfadder->connect( "sout", ha_sout );
  halfadder->connect( "cout", ha_cout );
  ha_xor2->connect( "i0", ha_a    );
  ha_xor2->connect( "i1", ha_b    );
  ha_xor2->connect(  "q", ha_sout );
  ha_and2->connect( "i0", ha_a    );
  ha_and2->connect( "i1", ha_b    );
  ha_and2->connect(  "q", ha_cout );
  //halfadder->toXml( cout );

  cout << "\nConstruction du modele <fulladder>." << endl;
  Cell* fulladder = new Cell ( "fulladder" );
  new Term( fulladder, "a"   , Term::In  );
  new Term( fulladder, "b"   , Term::In  );
  new Term( fulladder, "cin" , Term::In  );
  new Term( fulladder, "sout", Term::Out );
  new Term( fulladder, "cout", Term::Out );
  Net*      fu_a    = new Net      ( fulladder, "a"   , Term::External );
  Net*      fu_b    = new Net      ( fulladder, "b"   , Term::External );
  Net*      fu_cin  = new Net      ( fulladder, "cin" , Term::External );
  Net*      fu_sout = new Net      ( fulladder, "sout", Term::External );
  Net*      fu_cout = new Net      ( fulladder, "cout", Term::External );
  Net*      fu_sout_1 = new Net    ( fulladder, "sout_1", Term::Internal );
  Net*      fu_carry_1 = new Net   ( fulladder, "carry_1", Term::Internal );
  Net*      fu_carry_2 = new Net   ( fulladder, "carry_2", Term::Internal );
  Instance* fu_ha1  = new Instance ( fulladder, Cell::find("halfadder"), "ha_1" );
  Instance* fu_ha2  = new Instance ( fulladder, Cell::find("halfadder"), "ha_2" );
  Instance* fu_or2   = new Instance ( fulladder, Cell::find("or2")     , "or2_1");
  fulladder->connect( "a"   , fu_a    );
  fulladder->connect( "b"   , fu_b    );
  fulladder->connect( "cin" , fu_cin  );
  fulladder->connect( "sout", fu_sout );
  fulladder->connect( "cout", fu_cout );
  fu_ha1->connect( "a", fu_a );
  fu_ha1->connect( "b", fu_b );
  fu_ha1->connect( "sout", fu_sout_1 );
  fu_ha1->connect( "cout", fu_carry_1);
  fu_ha2->connect( "a", fu_cin );
  fu_ha2->connect( "b", fu_sout_1 );
  fu_ha2->connect( "sout", fu_sout );
  fu_ha2->connect( "cout", fu_carry_2 );
  fu_or2->connect( "i0", fu_carry_1 );
  fu_or2->connect( "i1", fu_carry_2 );
  fu_or2->connect(  "q", fu_cout );
  fulladder->toXml( cout );

  return 0;
}
