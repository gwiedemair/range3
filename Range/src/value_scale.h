/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   value_scale.h                                            *
 *  GROUP:  Range                                                    *
 *  TYPE:   header file (*.h)                                        *
 *  DATE:   13-th December 2016                                      *
 *                                                                   *
 *  DESCRIPTION: Value scale widget class declaration                *
 *********************************************************************/

#ifndef __VALUE_SCALE_H__
#define __VALUE_SCALE_H__

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>

#include "value_line_edit.h"

class ValueScale : public QWidget
{

    Q_OBJECT

    protected:

        static const double mantisScale;
        static const uint mantisSize;
        static const uint exponentSize;

        //! Expandable.
        bool expandable;
        //! Mantis.
        double mantis;
        //! Exponent.
        int exponent;

        //! Scale edit.
        ValueLineEdit *scaleEdit;
        //! Expand button.
        QPushButton *expandButton;
        //! Expandable widget.
        QWidget *expandWidget;
        //! Mantis slider.
        QSlider *mantisSlider;
        //! Mantis edit.
        ValueLineEdit *mantisEdit;
        //! Exponent spin box.
        QSpinBox *exponentSpinBox;

        //! Setting scale allowed.
        bool setScaleAllowed;

    public:

        //! Constructor.
        explicit ValueScale(const QString &title, QWidget *parent = 0);

        //! Return scale;
        double getValue(void) const;

        //! Set value.
        void setValue(double value);

    signals:

        //! Value has changed.
        void valueChanged(double value);

    private slots:

        //! Scale edit changed.
        void onScaleEditChanged(double value);

        //! Expand button clicked.
        void onExpandButtonClicked(void);

        //! Mantis slider changed.
        void onMantisSliderChanged(int value);

        //! Mantis edit changed.
        void onMantisEditChanged(double value);

        //! Exponent spin box changed.
        void onExponentSpinBoxChanged(int value);

};

#endif // __VALUE_SCALE_H__
