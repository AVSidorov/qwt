/*****************************************************************************
* Qwt Examples - Copyright (C) 2002 Uwe Rathmann
* This file may be used under the terms of the 3-clause BSD License
*****************************************************************************/

#include "mainwindow.h"
#include "plot.h"

#include <qwt_plot.h>
#include <qwt_plot_rescaler.h>
#include <qwt_interval.h>

#include <qgroupbox.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qstatusbar.h>
#include <qlabel.h>

MainWindow::MainWindow()
{
    QFrame* w = new QFrame( this );

    QWidget* panel = createPanel( w );
    panel->setFixedWidth( 2 * panel->sizeHint().width() );
    m_plot = createPlot( w );

    QHBoxLayout* layout = new QHBoxLayout( w );
    layout->setContentsMargins( QMargins() );
    layout->addWidget( panel, 0 );
    layout->addWidget( m_plot, 10 );

    setCentralWidget( w );

    setRescaleMode( 0 );

    ( void )statusBar();
}

QWidget* MainWindow::createPanel( QWidget* parent )
{
    QGroupBox* panel = new QGroupBox( "Navigation Panel", parent );

    QComboBox* rescaleBox = new QComboBox( panel );
    rescaleBox->setEditable( false );
    rescaleBox->insertItem( KeepScales, "None" );
    rescaleBox->insertItem( Fixed, "Fixed" );
    rescaleBox->insertItem( Expanding, "Expanding" );
    rescaleBox->insertItem( Fitting, "Fitting" );

    connect( rescaleBox, SIGNAL(activated(int)), SLOT(setRescaleMode(int)) );

    m_rescaleInfo = new QLabel( panel );
    m_rescaleInfo->setSizePolicy(
        QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_rescaleInfo->setWordWrap( true );

    QVBoxLayout* layout = new QVBoxLayout( panel );
    layout->addWidget( rescaleBox );
    layout->addWidget( m_rescaleInfo );
    layout->addStretch( 10 );

    return panel;
}

Plot* MainWindow::createPlot( QWidget* parent )
{
    Plot* plot = new Plot( parent, QwtInterval( 0.0, 1000.0 ) );
    plot->replot();

    m_rescaler = new QwtPlotRescaler( plot->canvas() );
    m_rescaler->setReferenceAxis( QwtPlot::xBottom );
    m_rescaler->setAspectRatio( QwtPlot::yLeft, 1.0 );
    m_rescaler->setAspectRatio( QwtPlot::yRight, 0.0 );
    m_rescaler->setAspectRatio( QwtPlot::xTop, 0.0 );

    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        m_rescaler->setIntervalHint( axis, QwtInterval( 0.0, 1000.0 ) );

    connect( plot, SIGNAL(resized(double,double)),
        SLOT(showRatio(double,double)) );
    return plot;
}

void MainWindow::setRescaleMode( int mode )
{
    bool doEnable = true;
    QString info;
    QRectF rectOfInterest;
    QwtPlotRescaler::ExpandingDirection direction = QwtPlotRescaler::ExpandUp;

    switch( mode )
    {
        case KeepScales:
        {
            doEnable = false;
            info = "All scales remain unchanged, when the plot is resized";
            break;
        }
        case Fixed:
        {
            m_rescaler->setRescalePolicy( QwtPlotRescaler::Fixed );
            info = "The scale of the bottom axis remains unchanged, "
                "when the plot is resized. All other scales are changed, "
                "so that a pixel on screen means the same distance for"
                "all scales.";
            break;
        }
        case Expanding:
        {
            m_rescaler->setRescalePolicy( QwtPlotRescaler::Expanding );
            info = "The scales of all axis are shrinked/expanded, when "
                "resizing the plot, keeping the distance that is represented "
                "by one pixel.";
            m_rescaleInfo->setText( "Expanding" );
            break;
        }
        case Fitting:
        {
            m_rescaler->setRescalePolicy( QwtPlotRescaler::Fitting );
            const QwtInterval xIntv =
                m_rescaler->intervalHint( QwtPlot::xBottom );
            const QwtInterval yIntv =
                m_rescaler->intervalHint( QwtPlot::yLeft );

            rectOfInterest = QRectF( xIntv.minValue(), yIntv.minValue(),
                xIntv.width(), yIntv.width() );
            direction = QwtPlotRescaler::ExpandBoth;

            info = "Fitting";
            break;
        }
    }

    m_plot->setRectOfInterest( rectOfInterest );

    m_rescaleInfo->setText( info );
    m_rescaler->setEnabled( doEnable );
    for ( int axis = 0; axis < QwtPlot::axisCnt; axis++ )
        m_rescaler->setExpandingDirection( direction );

    if ( doEnable )
        m_rescaler->rescale();
    else
        m_plot->replot();
}

void MainWindow::showRatio( double xRatio, double yRatio )
{
    const QString msg = QString( "%1, %2" ).arg( xRatio ).arg( yRatio );
    statusBar()->showMessage( msg );
}

#include "moc_mainwindow.cpp"
