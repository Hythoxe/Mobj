// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/4-5>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <libxml/xmlreader.h>
using namespace std;

#include "../H_files/Term.h"
#include "../H_files/Net.h"
#include "../H_files/Instance.h"
#include "../H_files/Cell.h"
#include "../H_files/XmlUtil.h"
using namespace Netlist;


/*int main ( int argc, char* argv[] )
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
  Instance* fu_or2  = new Instance ( fulladder, Cell::find("or2")     , "or2_1");
  fulladder->connect( "a"   , fu_a    );  //connection du term a au a du fulladder
  fulladder->connect( "b"   , fu_b    );  //connection du term b au b du fulladder
  fulladder->connect( "cin" , fu_cin  );  //connection du term cin au cin du fulladder
  fulladder->connect( "sout", fu_sout );  //connection du term sout au sout du fulladder
  fulladder->connect( "cout", fu_cout );  //connection du term cout au cout du fulladder
  fu_ha1->connect( "a", fu_a );           //connection de l'entrée a au a du ha1
  fu_ha1->connect( "b", fu_b );           //connection de l'entrée b au b du ha1
  fu_ha1->connect( "sout", fu_sout_1 );   //connection de la sortie sout du ha1 a la connecton intermediaire sout_1
  fu_ha1->connect( "cout", fu_carry_1);   //connection de la sortie cout du ha1 a la connecton intermediaire carry_1
  fu_ha2->connect( "a", fu_cin );         //connection de l'entrée cin au a du ha2
  fu_ha2->connect( "b", fu_sout_1 );      //connection de la connecton intermediaire sout_1 au b du ha2
  fu_ha2->connect( "sout", fu_sout );     //connection de la sorti sout au sout du ha2
  fu_ha2->connect( "cout", fu_carry_2 );  //connection de la sortie cout du ha1 a la connecton intermediaire carry_2
  fu_or2->connect( "i0", fu_carry_1 );    //connection de la connecton intermediaire carry_1 au i0 du or2
  fu_or2->connect( "i1", fu_carry_2 );    //connection de la connecton intermediaire carry_2 au i1 du or2
  fu_or2->connect(  "q", fu_cout );       //connection de la sorti cout au q du or2
  fulladder->toXml( cout );

  return 0;

}*/

int main ( int argc, char* argv[] )
{
  cout << "Chargement des modeles:" << endl;
  cout << "- <and2> ..." << endl;
  Cell::load( "and2" );

  cout << "- <or2> ..." << endl;
  Cell::load( "or2" );

  cout << "- <xor2> ..." << endl;
  Cell::load( "xor2" );

  cout << "- <halfadder> ..." << endl;
  Cell* halfadder = Cell::load( "halfadder" );

  cout << "\nContenu du <halfadder>:" << endl;
  halfadder->toXml( cout );

  return 0;
}