#ifndef NETLIST_CELLSLIB_H
#define NETLIST_CELLSLIB_H

#include <QDialog>
#include <QTableView>
#include <QPushButton>

//#include "CellViewer.h"
#include "CellsModel.h"

#pragma once

namespace Netlist{
    
    class CellViewer;
    //class CellsModel;

    class CellsLib : public QWidget {
    Q_OBJECT;
    public:
                            CellsLib       ( QWidget* parent=NULL );
                void        setCellViewer  ( CellViewer* );
                int         getSelectedRow () const;
        inline  CellsModel* getBaseModel   ();
    public slots:
                void        load           ();
    private:
        CellViewer*  cellViewer_;
        CellsModel*  baseModel_;
        QTableView*  view_;
        QPushButton* load_;
    };
    
    inline CellsModel* CellsLib::getBaseModel(){ return baseModel_; }

}

#endif // NETLIST_CELLSLIB_H

