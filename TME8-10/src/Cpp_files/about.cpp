#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../H_files/about.h"

namespace Netlist{

    About::About( QWidget* parent ): 
    QDialog  (parent)
    {
        setWindowTitle( tr("About") );
        
        QLabel* label = new QLabel();
        label->setText( tr("MOBJ - Modélisation Objet pour la VLSI") );
        QLabel* label2 = new QLabel();
        label2->setText( tr("Projet de Queric Yann version 2021/2022") );
        
        QPushButton* quitButton = new QPushButton();
        quitButton->setText ( " Quit " );

        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addStretch();
        hLayout->addWidget( quitButton );
        hLayout->addStretch();

        QFrame* separator = new  QFrame  ();
        separator ->setFrameShape ( QFrame :: HLine );
        separator ->setFrameShadow( QFrame :: Sunken );

        QVBoxLayout* vLayout = new  QVBoxLayout  ();
        vLayout->setSizeConstraint( QLayout :: SetFixedSize  );
        vLayout->addStretch();
        vLayout->addWidget( label );
        vLayout->addStretch();
        vLayout->addStretch();
        vLayout->addWidget( label2 );
        vLayout->addStretch();
        vLayout->addLayout( hLayout );
        setLayout( vLayout );

        connect( quitButton, SIGNAL(clicked ()), this, SLOT(accept ()) );
    }

    About::~About(){}

    bool About::run( QWidget* parent ){
        About* dialog = new About(parent);
        int dialogResult = dialog->exec();
        return ( dialogResult == Accepted );
        delete dialog;
    }

}
