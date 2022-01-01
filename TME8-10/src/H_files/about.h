#ifndef NETLIST_ABOUT_H
#define NETLIST_ABOUT_H

#include <QDialog>

class QCheckBox;
class QLineEdit;

#pragma once

namespace Netlist{

    class About : public QDialog {
        Q_OBJECT;
        public:
                     About ( QWidget* parent=NULL );
            virtual ~About();
            bool     run   ( QWidget* parent );
    };

}
#endif // NETLIST_ABOUT_H