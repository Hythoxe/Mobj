#ifndef NETLIST_CELL_VIEWER_H
#define NETLIST_CELL_VIEWER_H

#include <QMainWindow>
#include "CellWidget.h"
#include "SaveCellDialog.h"
#include "OpenCellDialog.h"
//#include "InstancesWidget.h"
#include "CellsLib.h"

#pragma once

namespace Netlist {

    class InstancesWidget;

    class CellViewer : public QMainWindow {
        Q_OBJECT;
    public:
                          CellViewer          ( QWidget* parent=NULL );
        virtual          ~CellViewer          ();
        inline  Cell*     getCell             () const;
        inline  CellsLib* getCellsLib         ();  // TME9+.
    public slots:
                void      setCell             ( Cell* );
                void      saveCell            ();
                void      openCell            ();
        inline  void      showCellsLib        ();  // TME9+.
                void      showInstancesWidget ();  // TME9+.
        virtual void      cellLoaded          (){};
    private:
        CellWidget*      cellWidget_;
        CellsLib*        cellsLib_;         // TME9+.
        InstancesWidget* instancesWidget_;  // TME9+.
        SaveCellDialog*  saveCellDialog_;
        OpenCellDialog*  openCellDialog_;
    };


    inline Cell*     CellViewer::getCell() const{ return cellWidget_->getCell(); }
    inline CellsLib* CellViewer::getCellsLib(){ return cellsLib_;}
    inline void      CellViewer::showCellsLib(){ cellsLib_->show(); }

}
    
#endif  // NETLIST_CELL_VIEWER_H