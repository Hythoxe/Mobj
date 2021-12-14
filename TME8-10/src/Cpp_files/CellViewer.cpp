#include  <QMenu>
#include  <QMenuBar>
#include  <QAction>
#include  <QDockWidget>


#include "../H_files/Cell.h"
#include "../H_files/SaveCellDialog.h"
#include "../H_files/OpenCellDialog.h"
#include "../H_files/CellWidget.h"
#include "../H_files/CellViewer.h"
#include "../H_files/InstancesModel.h"
#include "../H_files/InstancesWidget.h"
#include "../H_files/CellsLib.h"
#include "../H_files/CellsModel.h"

namespace Netlist{

    CellViewer::CellViewer( QWidget* parent ): 
    QMainWindow(parent), 
    cellWidget_(NULL),
    saveCellDialog_(NULL),
    openCellDialog_(NULL),
    cellsLib_(NULL),
    instancesWidget_(NULL)
    {
        cellWidget_ = new CellWidget();
        saveCellDialog_ = new SaveCellDialog( this );
        openCellDialog_ = new OpenCellDialog( this );
        cellsLib_ = new CellsLib(); 
        instancesWidget_ = new InstancesWidget();

        setCentralWidget ( cellWidget_ );
        cellsLib_->setCellViewer(this);
        instancesWidget_->setCellViewer(this);

        QMenu* fileMenu = menuBar()->addMenu( "&File" );

        QAction* action = new QAction( "&Save As", this );
        action->setStatusTip( "Save to disk (rename) the Cell" );
        action->setShortcut( QKeySequence( "CTRL+S" ) );
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL( triggered() ), this , SLOT( saveCell() ) );

        action = new QAction( "&Open As", this );
        action->setStatusTip( "Open to disk (rename) the Cell" );
        action->setShortcut( QKeySequence( "CTRL+O" ) );
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL( triggered() ), this , SLOT( openCell() ) );

        action = new QAction( "&Quit " , this );
        action->setStatusTip( "Exit the Netlist Viewer" );
        action->setShortcut( QKeySequence ( "CTRL +Q" ) );
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL ( triggered() ), this, SLOT( close() ) );

        QDockWidget* dock = new QDockWidget( "&Cell", this );
        dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        dock->setWidget(cellsLib_);
        addDockWidget(Qt::RightDockWidgetArea, dock);
        fileMenu->addAction( action );
        connect( action, SIGNAL ( triggered() ), cellsLib_->getBaseModel(), SLOT( updateDatas() ) );

        dock = new QDockWidget( "&Instance", this );
        dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        dock->setWidget(instancesWidget_);
        addDockWidget(Qt::RightDockWidgetArea, dock);
        fileMenu->addAction( action );
    }

    CellViewer::~CellViewer(){}
    
    void CellViewer::setCell( Cell* cell ){
        cellWidget_->setCell(cell);
        //instancesWidget_->setCell(cell);
    }

    void CellViewer::saveCell(){
        Cell* cell = getCell ();
        if ( cell == NULL ) return;
        QString  cellName = cell ->getName (). c_str ();
        if (saveCellDialog_ ->run(cellName )) {
            cell ->setName( cellName.toStdString () );
            cell ->save    ( cellName.toStdString () );
        }
    }

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

    void CellViewer::showInstancesWidget(){
        instancesWidget_->setCell(getCell());
        instancesWidget_->show();
    }

}