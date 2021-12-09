#ifndef NETLIST_CELLSLIB_H
#define NETLIST_CELLSLIB_H


#include "CellViewer.h"

namespace Netlist{
    
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

}

#endif // NETLIST_CELLSLIB_H

