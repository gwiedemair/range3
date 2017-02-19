/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   file_chooser_button.h                                    *
 *  GROUP:  Range                                                    *
 *  TYPE:   header file (*.h)                                        *
 *  DATE:   28-st August 2013                                        *
 *                                                                   *
 *  DESCRIPTION: File chooser button class declaration               *
 *********************************************************************/

#ifndef __FILE_CHOOSER_BUTTON_H__
#define __FILE_CHOOSER_BUTTON_H__

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class FileChooserButton : public QWidget
{

    Q_OBJECT

    protected:

        bool saveFile;
        QString caption;
        QString path;
        QString filter;
        QPushButton *pushButton;
        QLabel *label;

    public:

        //! Constructor.
        explicit FileChooserButton(const QString &labelText,
                                   bool saveFile,
                                   QWidget *parent = 0,
                                   const QString &caption = QString(),
                                   const QString &path = QString(),
                                   const QString &filter = QString());

        //! Return selected file name.
        QString getFileName(void) const;

        //! Set file name.
        void setFileName(const QString &fileName);

        //! Set filter.
        void setFilter(const QString &filter);

        //! Set show label.
        void setShowLabel(bool showLabel);

    signals:

        //! File changed signal.
        void fileNameChanged(const QString &fileName);
        
    public slots:

        //! On push button clicked.
        void onPushButtonClicked(void);
        
};

#endif // __FILE_CHOOSER_BUTTON_H__
