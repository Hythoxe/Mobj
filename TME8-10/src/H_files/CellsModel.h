#ifndef NETLIST_CELLS_MODEL_H
#define NETLIST_CELLS_MODEL_H

#include <QDialog>
#include <QLineEdit>
#include <QAbstractTableModel>

#include "Cell.h"

#pragma once

namespace Netlist{

    
    class CellsModel : public QAbstractTableModel {
        Q_OBJECT ;
        public :
                                CellsModel      ( QObject* parent = NULL );
                                ~CellsModel     ();
                    void        setCell         ( Cell* );
                    Cell*       getModel        ( int row );
            inline  int         rowCount        ( const QModelIndex& parent=QModelIndex() ) const;
            inline  int         columnCount     ( const QModelIndex& parent=QModelIndex() ) const;
                    QVariant    data            ( const QModelIndex& index , int role=Qt::DisplayRole ) const;
                    QVariant    headerData      ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
                    void        updateDatas     ();
        private :
            Cell * cell_ ;
        };

    inline int CellsModel::rowCount( const QModelIndex& parent ) const{ return cell_->getAllCells().size(); };

    inline int CellsModel::columnCount( const QModelIndex& parent ) const{ return 1; }

    
}
#endif // NETLIST_CELLS_MODEL_H
