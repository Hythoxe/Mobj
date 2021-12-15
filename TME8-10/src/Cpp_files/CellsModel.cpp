# include "../H_files/CellsModel.h"

namespace Netlist{

    CellsModel::CellsModel( QObject* parent ): 
    QAbstractTableModel(parent), 
    cell_(NULL)
    {}

    CellsModel::~CellsModel(){}

    void CellsModel::setCell( Cell* cell ){
        emit layoutAboutToBeChanged();
        cell_=cell ;
        emit layoutChanged();
    }

    QVariant CellsModel::data( const QModelIndex& index, int role ) const{
        if ( not index . isValid ()) return QVariant ();
        if ( role == Qt :: DisplayRole ) {
            int row = index . row ();
            switch ( index . column () ) {
                case 0: return cell_->getAllCells()[row]->getName().c_str();
            }
        }
        return QVariant ();
    }

    QVariant CellsModel::headerData( int section, Qt::Orientation orientation, int role ) const{
        if ( orientation == Qt :: Vertical ) return QVariant ();
        if ( role != Qt :: DisplayRole ) return QVariant ();
        switch ( section ) {
            case 0: return " Cell " ;
        }
        return QVariant ();
    }

    Cell * CellsModel::getModel ( int row ){
        if ( not cell_ ) return NULL ;
        if ( row >= (int) cell_->getAllCells().size()) return NULL ;
        return cell_->getAllCells()[row];
    }

    void CellsModel::updateDatas(){
        emit layoutAboutToBeChanged();
        emit layoutChanged();
    }


}

