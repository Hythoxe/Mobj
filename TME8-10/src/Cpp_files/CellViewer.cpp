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
#include "../H_files/about.h"

namespace Netlist{

    CellViewer::CellViewer( QWidget* parent ): 
    QMainWindow(parent), 
    cellWidget_(NULL),
    saveCellDialog_(NULL),
    openCellDialog_(NULL),
    cellsLib_(NULL),
    instancesWidget_(NULL),
    about_(NULL)
    {
        cellWidget_ = new CellWidget();
        saveCellDialog_ = new SaveCellDialog( this );
        openCellDialog_ = new OpenCellDialog( this );
        cellsLib_ = new CellsLib(); 
        instancesWidget_ = new InstancesWidget();
        about_ = new About();

        setCentralWidget ( cellWidget_ );
        cellsLib_->setCellViewer(this);
        instancesWidget_->setCellViewer(this);

        QMenu* fileMenu = menuBar()->addMenu( "&File" );
        QMenu* toolMenu = menuBar()->addMenu( "&Tool" );
        QMenu* AboutMenu = menuBar()->addMenu( "&About" );

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
        action->setShortcut( QKeySequence ( "CTRL+Q" ) );
        action->setVisible( true );
        fileMenu->addAction( action );
        connect( action, SIGNAL ( triggered() ), this, SLOT( close() ) );

        QDockWidget* dock = new QDockWidget( "&Cell", this );
        dock->toggleViewAction()->setShortcut( QKeySequence ( "CTRL+C" ) );
        dock->setVisible( true );
        dock->setWidget( cellsLib_ );
        addDockWidget( Qt::RightDockWidgetArea, dock );
        toolMenu->addAction( dock->toggleViewAction() );
        
        dock = new QDockWidget( "&Instance", this );
        dock->toggleViewAction()->setShortcut( QKeySequence ( "CTRL+I" ) );
        dock->setVisible( true );
        dock->setWidget( instancesWidget_ );
        addDockWidget( Qt::RightDockWidgetArea, dock );
        toolMenu->addAction( dock->toggleViewAction() );

        action = new QAction( "&About", this );
        action->setShortcut( QKeySequence( "CTRL+A" ) );
        action->setVisible( true );
        AboutMenu->addAction( action );
        connect( action, SIGNAL( triggered() ), this , SLOT( about() ) );

    }

    CellViewer::~CellViewer(){}
    
    void CellViewer::setCell( Cell* cell ){
        cellWidget_->setCell(cell);
        instancesWidget_->setCell(cell);
    }

    void CellViewer::saveCell(){
        Cell* cell = getCell ();
        if ( cell == NULL ) return;
        QString  cellName = cell->getName(). c_str();
        if (saveCellDialog_->run(cellName )) {
            cell->setName( cellName.toStdString() );
            cell->save   ( cellName.toStdString() );
        }
    }

    void CellViewer::openCell(){
        QString  cellName;
        if (openCellDialog_->run(this, cellName)) {
            emit cellLoaded();
            Cell* cell = cell->find(cellName.toStdString());
            if ( cell == NULL )
                cell->load(cellName.toStdString());
            if (cell)
                setCell(cell);
        }
    }

    void CellViewer::showInstancesWidget(){
        instancesWidget_->setCell(getCell());
        instancesWidget_->show();
    }

    void CellViewer::about(){
        about_->run(this);
    }

}