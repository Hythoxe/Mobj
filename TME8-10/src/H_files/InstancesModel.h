#ifndef NETLIST_INSTANCE_MODEL_H
#define NETLIST_INSTANCE_MODEL_H

#include <QDialog>
#include <QLineEdit>
#include <QAbstractTableModel>

#include "Cell.h"


namespace Netlist{

    
    class InstancesModel : public QAbstractTableModel {
        Q_OBJECT ;
        public :
                                InstancesModel  ( QObject* parent = NULL );
                                ~InstancesModel ();
                    void        setCell         ( Cell* );
                    Cell*       getModel        ( int row );
            inline  int         rowCount        ( const QModelIndex& parent=QModelIndex() ) const;
            inline  int         columnCount     ( const QModelIndex& parent=QModelIndex() ) const;
                    QVariant    data            ( const QModelIndex& index , int role=Qt::DisplayRole ) const;
                    QVariant    headerData      ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
        private :
            Cell * cell_ ;
        };

    inline int InstancesModel::rowCount( const QModelIndex& parent ) const{ return (cell_)?cell_->getInstances().size():0; };

    inline int InstancesModel::columnCount( const QModelIndex& parent ) const{ return 2; }

}
#endif // NETLIST_INSTANCE_MODEL_H