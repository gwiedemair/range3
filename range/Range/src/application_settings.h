/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   application_settings.h                                   *
 *  GROUP:  Range                                                    *
 *  TYPE:   header file (*.h)                                        *
 *  DATE:   12-th July 2013                                          *
 *                                                                   *
 *  DESCRIPTION: Application class class declaration                 *
 *********************************************************************/

#ifndef APPLICATION_SETTINGS_H
#define APPLICATION_SETTINGS_H

#include <QObject>
#include <QString>
#include <QColor>

#include "action_definition.h"

class ApplicationSettings : public QObject
{

    Q_OBJECT

    protected:

        //! Action definition.
        ActionDefinition *actionDefinition;

        //! Range solver path.
        QString solverPath;
        //! Path to help directory.
        QString helpDir;
        //! Number of CPUs to be used by solver.
        uint nThreads;
        //! Number of history records.
        uint nHistoryRecords;
        //! Style.
        QString style;
        //! Send usage info.
        bool sendUsageInfo;
        //! Allow range API.
        bool rangeApiAllowed;
        //! Range server.
        QString rangeApiServer;
        //! Range account.
        QString rangeAccount;
        //! Range password.
        QString rangePassword;

    public:

        //! Windows-dark style constant.
        static const QString WindowsDark;

        //! Fusion-dark style constant.
        static const QString FusionDark;

        //! Fusion-range style constant.
        static const QString FusionRange;

        //! Fusion style constant.
        static const QString Fusion;

    public:

        //! Constructor.
        explicit ApplicationSettings(QObject *parent = nullptr);

        //! Return const pointer to action definition.
        const ActionDefinition *getActionDefinition(void) const;

        //! Return pointer to action definition.
        ActionDefinition *getActionDefinition(void);

        //! Return const reference to Range solver path.
        const QString & getSolverPath(void) const;

        //! Set new Range solver path.
        void setSolverPath(const QString &solverPath);

        //! Return const reference to help directory.
        const QString & getHelpDir(void) const;

        //! Set new help directory.
        void setHelpDir(const QString &helpDir);

        //! Return number of threads to be used in calculation.
        uint getNThreads(void) const;

        //! Set number of threads to be used in calculation.
        void setNThreads(uint nThreads);

        //! Return number of history records.
        uint getNHistoryRecords(void) const;

        //! Set number of history records.
        void setNHistoryRecords(uint nHistoryRecords);

        //! Return style.
        const QString &getStyle(void) const;

        //! Set style.
        void setStyle(const QString &style);

        //! Return send usage info.
        bool getSendUsageInfo(void) const;

        //! Set send usage info.
        void setSendUsageInfo(bool sendUsageInfo);

        //! Return Range API allowed.
        bool getRangeApiAllowed(void) const;

        //! Set Range API allowed.
        void setRangeApiAllowed(bool rangeApiAllowed);

        //! Return Range API server.
        const QString &getRangeApiServer(void) const;

        //! Set Range API server.
        void setRangeApiServer(const QString &rangeApiServer);

        //! Return Range account.
        const QString &getRangeAccount(void) const;

        //! Set Range account.
        void setRangeAccount(const QString &rangeAccount);

        //! Return Range password.
        const QString &getRangePassword(void) const;

        //! Set Range password.
        void setRangePassword(const QString &rangePassword);

        //! Return maximum number of Threads.
        static uint getMaxThreads(void);

        //! Return list of styles.
        static QStringList getStyles(void);

        //! Return default range solver executable.
        static QString getDefaultRangeSolverExecutable(void);

        //! Return default help directory.
        static QString getDefaultHelpDir(void);

        //! Return default number of threads.
        static uint getDefaultNThreads(void);

        //! Return default number of history records.
        static uint getDefaultNHistoryRecords(void);

        //! Return list of styles.
        static QString getDefaultStyle(void);

        //! Return default send usage info.
        static bool getDefaultSendUsageInfo(void);

        //! Return default Range API allowed.
        static bool getDefaultRangeApiAllowed(void);

        //! Return default Range API server.
        static const QString getDefaultRangeApiServer(void);

        //! Return default Range account.
        static const QString getDefaultRangeAccount(void);

        //! Return default Range password.
        static const QString getDefaultRangePassword(void);

        //! Return default background color for style.
        static QColor getDefaultBackgroundColor(const QString &style);

    signals:

        //! Shortcut changed signal.
        void shortcutChanged(ActionType actionType, const QString &shortcut);

        //! Number of history records has changed.
        void nHistoryRecordsChanged(uint nHistoryRecords);

        //! Style has changed.
        void styleChanged(const QString &style);

    protected slots:

        //! Action definition signal shortcut changed was emited.
        void onShortcutChanged(ActionType actionType, const QString &shortcut);

};

#endif // APPLICATION_SETTINGS_H
