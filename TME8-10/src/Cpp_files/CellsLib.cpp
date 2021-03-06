#include  <QHeaderView>
#include  <QPushButton>
#include  <QBoxLayout>


#include "../H_files/CellsLib.h"
#include "../H_files/CellViewer.h"

namespace Netlist{

    CellsLib::CellsLib( QWidget * parent ): 
    QWidget( parent ), 
    cellViewer_( NULL ), 
    baseModel_( new CellsModel( this )), 
    view_( new QTableView( this )), 
    load_( new QPushButton( this ))
    {
        setAttribute( Qt::WA_QuitOnClose, false );
        setAttribute( Qt::WA_DeleteOnClose, false );
        setContextMenuPolicy( Qt::ActionsContextMenu );

        view_->setShowGrid( false );
        view_->setAlternatingRowColors( true );
        view_->setSelectionBehavior( QAbstractItemView::SelectRows );
        view_->setSelectionMode( QAbstractItemView::SingleSelection );
        view_->setSortingEnabled( true );
        view_->setModel( baseModel_ ); // On associe le modele .

        QHeaderView * horizontalHeader = view_->horizontalHeader();
        horizontalHeader->setDefaultAlignment( Qt::AlignHCenter );
        horizontalHeader->setMinimumSectionSize( 300 );
        horizontalHeader->setStretchLastSection( true );
        QHeaderView * verticalHeader = view_->verticalHeader();
        verticalHeader->setVisible( false );
        load_->setText( " Load " );
        load_->setDefault( true );
        connect( load_, SIGNAL(clicked()), this, SLOT( load()) );

        QVBoxLayout* vbox = new QVBoxLayout();
        vbox->addWidget( view_ );
        vbox->addStretch();

        QHBoxLayout* hbox = new QHBoxLayout();
        hbox->addStretch();
        hbox->addWidget( load_ );
        hbox->addStretch();

        vbox->addLayout(hbox);
        setLayout(vbox);

    }

    int CellsLib::getSelectedRow() const{
        QModelIndexList selecteds = view_->selectionModel()->selection().indexes();
        if (selecteds.empty()) return -1;
        return selecteds.first().row();
    }
    
    void CellsLib::load(){
        int selectedRow = getSelectedRow();
        if (selectedRow<0) return ;
        cellViewer_->setCell( baseModel_->getModel(selectedRow) );
    }
    
    void CellsLib::setCellViewer( CellViewer* cell ){
        cellViewer_ = cell;
    }

}