#include  <QMenu>
#include  <QMenuBar>
#include  <QAction>

#include "../H_files/Cell.h"
#include "../H_files/CellViewer.h"
#include "../H_files/InstancesWidget.h"

namespace Netlist{

    CellViewer::CellViewer( QWidget* parent ): 
    QMainWindow(parent), 
    cellWidget_(NULL),
    saveCellDialog_(NULL)
    {
        cellWidget_ = new CellWidget();
        saveCellDialog_ = new SaveCellDialog( this );

        setCentralWidget ( cellWidget_ );

        QMenu* fileMenu = menuBar()->addMenu( "&File" );

        QAction* action = new QAction( "&Save As", this );
        action->setStatusTip( "Save to disk (rename) the Cell" );
        action->setShortcut( QKeySequence( "CTRL+S" ) );
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL( triggered() ), this , SLOT( saveCell() ) );

        action = new QAction( "&Quit " , this );
        action->setStatusTip( "Exit the Netlist Viewer" );
        action->setShortcut( QKeySequence ( "CTRL +Q" ) );
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL ( triggered () ), this, SLOT( close () ) );
    }

    CellViewer::~CellViewer(){}
    
    void CellViewer::saveCell(){
        Cell* cell = getCell ();
        if ( cell == NULL ) return;
        QString  cellName = cell ->getName (). c_str ();
        if (saveCellDialog_ ->run(cellName )) {
            cell ->setName( cellName.toStdString () );
            cell ->save    ( cellName.toStdString () );
        }
    }

    CellViewer::~CellViewer(){}

    void CellViewer::openCell(){
        QString  cellName;
        if (openCellDialog_->run(this, cellName)) {
            Cell* cell = Cell::find(cellName.toStdString());
            if (not cell){
                cell = Cell::load(cellName.toStdString());
            }
            if (cell)
                setCell(cell);
        }
    }

    void CellViewer::showCellsLib(){ cellsLib_->show(); }

    void CellViewer::showInstancesWidget(){
        instancesWidget_->setCell(getCell());
        instancesWidget_->show();
    }

}