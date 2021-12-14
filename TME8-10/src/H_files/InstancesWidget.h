#ifndef NETLIST_INSTANCE_WIDGET_H
#define NETLIST_INSTANCE_WIDGET_H

#include <QDialog>
#include <QTableView>
#include <QPushButton>

#include "Cell.h"
#include "CellViewer.h"
#include "InstancesModel.h"

#pragma once

namespace Netlist{

    class InstancesWidget : public QWidget {
            Q_OBJECT;
        public:
                          InstancesWidget ( QWidget* parent=NULL );
                    void  setCellViewer   ( CellViewer* );
                    int   getSelectedRow  () const;
            inline  void  setCell         ( Cell* );
        public slots:
                    void  load            ();
        private:
                    CellViewer*     cellViewer_;
                    InstancesModel* baseModel_;
                    QTableView*     view_;
                    QPushButton*    load_;
        };
    
    inline void InstancesWidget::setCell( Cell* cell ){ baseModel_->setCell(cell); }

}
#endif // NETLIST_INSTANCE_WIDGET_H