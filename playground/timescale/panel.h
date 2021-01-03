/*****************************************************************************
* Qwt Examples - Copyright (C) 2002 Uwe Rathmann
* This file may be used under the terms of the 3-clause BSD License
*****************************************************************************/

#ifndef PANEL_H
#define PANEL_H

#include "settings.h"
#include <qwidget.h>

class QDateTimeEdit;
class QSpinBox;

class Panel : public QWidget
{
    Q_OBJECT

  public:
    Panel( QWidget* parent = NULL );

    void setSettings( const Settings&);
    Settings settings() const;

  Q_SIGNALS:
    void edited();

  private:
    QDateTimeEdit* m_startDateTime;
    QDateTimeEdit* m_endDateTime;

    QSpinBox* m_maxMajorSteps;
    QSpinBox* m_maxMinorSteps;
    QSpinBox* m_maxWeeks;
};

#endif
