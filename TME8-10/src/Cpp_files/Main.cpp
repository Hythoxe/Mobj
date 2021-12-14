// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/8-10>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>

#include <QApplication>
#include <QtGui>

using namespace std;

#include "../H_files/Term.h"
#include "../H_files/Net.h"
#include "../H_files/Instance.h"
#include "../H_files/Cell.h"
#include "../H_files/CellViewer.h"
#include "../H_files/Error.h"

using namespace Netlist;


int main ( int argc, char* argv[] )
{
  cout << "Chargement des modeles..." << endl;
  Cell::load( "vdd" );
  Cell::load( "gnd" );
  Cell::load( "TransistorN" );
  Cell::load( "TransistorP" );
  Cell::load( "and2" );
  Cell::load( "or2" );
  Cell* xor2      = Cell::load( "xor2" );
  Cell* halfadder = Cell::load( "halfadder" );

  cout << "\nContenu du <xor2>:" << endl;
  xor2->toXml( cout );

  cout << "\nContenu du <halfadder>:" << endl;
  halfadder->toXml( cout );

  QApplication* qa = new QApplication( argc , argv );
  CellViewer* viewer = new CellViewer();
  viewer->setCell( halfadder );
  viewer->show();
  int rvalue = qa->exec();
  delete qa;
  return rvalue;
  return 0;
  /*
  try {
    Cell* cell = Cell::load( "halfadder" );
  }
  catch( int& e ) {
    cerr << "[ERROR] code:" << e << endl ;
    exit (1);
  }
  catch( Error& e ) {
    cerr << "[ERROR]" << e.what() << endl ;
    exit (1);
  }*/
}
