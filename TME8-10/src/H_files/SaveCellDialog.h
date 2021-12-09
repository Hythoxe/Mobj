#ifndef NETLIST_SAVE_CELL_DIALOG_H
#define NETLIST_SAVE_CELL_DIALOG_H

#include <QDialog>
#include <QLineEdit>

class QCheckBox;
class QLineEdit;

namespace Netlist{

    class SaveCellDialog : public QDialog {
        Q_OBJECT;
        public:
                                    SaveCellDialog ( QWidget* parent=NULL );
            virtual                 ~SaveCellDialog();
                    bool            run            ( QString& name );
            inline  const QString   getCellName    ()  const;
            inline  void            setCellName    ( const  QString& );
        protected:
            QLineEdit*     lineEdit_;
    };

    inline const QString SaveCellDialog::getCellName()  const { return lineEdit_->text (); }

    inline void  SaveCellDialog::setCellName( const  QString& name ) { return lineEdit_->setText( name ); }

}
#endif // NETLIST_SAVE_CELL_DIALOG_H