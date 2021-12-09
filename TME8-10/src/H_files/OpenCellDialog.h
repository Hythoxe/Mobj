#ifndef NETLIST_OPEN_CELL_DIALOG_H
#define NETLIST_OPEN_CELL_DIALOG_H

#include <QDialog>
#include <QLineEdit>

class QCheckBox;
class QLineEdit;

namespace Netlist{

    class OpenCellDialog : public QDialog {
        Q_OBJECT;
        public:
                                    OpenCellDialog ( QWidget* parent=NULL );
            virtual                 ~OpenCellDialog();
            static  bool            run            ( QWidget* parent, QString& name );
            inline  const QString   getCellName    ()  const;
            inline  void            setCellName    ( const  QString& );
        protected:
            QLineEdit*     lineEdit_;
    };

    inline const QString OpenCellDialog::getCellName()  const { return lineEdit_->text (); }

    inline void  OpenCellDialog::setCellName( const  QString& name ) { return lineEdit_->setText( name ); }

}
#endif // NETLIST_OPEN_CELL_DIALOG_H