/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   rml_problem.h                                            *
 *  GROUP:  RML                                                      *
 *  TYPE:   header file (*.h)                                        *
 *  DATE:   23-rd December 2011                                      *
 *                                                                   *
 *  DESCRIPTION: Problem class declaration                           *
 *********************************************************************/

#ifndef __RML_PROBLEM_H__
#define __RML_PROBLEM_H__

#include <QString>
#include <vector>

#include "rml_problem_setup.h"
#include "rml_problem_task_item.h"
#include "rml_problem_type.h"
#include "rml_time_solver.h"
#include "rml_matrix_solver_conf.h"
#include "rml_monitoring_point_manager.h"

//! Problem class.
class RProblem
{

    private:

        //! Internal initialization function.
        void _init ( const RProblem *pProblem = 0 );

    protected:

        //! Problem task tree.
        RProblemTaskItem taskTree;
        //! Time-Solver.
        RTimeSolver timeSolver;
        //! Materix solver.
        RMatrixSolverConf matrixSolver;
        //! Monitoring points.
        RMonitoringPointManager monitoringPointManager;
        //! Problem setup.
        RProblemSetup problemSetup;

    public:

        //! Constructor.
        RProblem ();

        //! Copy constructor.
        RProblem ( const RProblem & problem );

        //! Destructor.
        ~RProblem ();

        //! Return const reference to problem task tree.
        const RProblemTaskItem &getProblemTaskTree ( void ) const;

        //! Return reference to problem task tree.
        RProblemTaskItem &getProblemTaskTree ( void );

        //! Set problem task tree.
        void setProblemTaskTree ( const RProblemTaskItem &taskTree );

        //! Return const reference to time-solver.
        const RTimeSolver & getTimeSolver ( void ) const;

        //! Return reference to time-solver.
        RTimeSolver & getTimeSolver ( void );

        //! Set new time-solver.
        void setTimeSolver ( const RTimeSolver &timeSolver );

        //! Return const reference to matrix solver.
        const RMatrixSolverConf & getMatrixSolverConf ( void ) const;

        //! Return reference to matrix solver.
        RMatrixSolverConf & getMatrixSolverConf ( void );

        //! Set new matrix solver.
        void setMatrixSolver ( const RMatrixSolverConf &matrixSolver );

        //! Return const reference to monitoring point manager.
        const RMonitoringPointManager & getMonitoringPointManager(void) const;

        //! Return reference to monitoring point manager.
        RMonitoringPointManager & getMonitoringPointManager(void);

        //! Set monitoring point manager.
        void setMonitoringPointManager(const RMonitoringPointManager &monitoringPointManager);

        //! Return const reference to problem setup.
        const RProblemSetup &getProblemSetup(void) const;

        //! Return reference to problem setup.
        RProblemSetup &getProblemSetup(void);

        //! Set problem setup.
        void setProblemSetup(const RProblemSetup &problemSetup);

        //! Assignment operator.
        RProblem & operator = ( const RProblem & problem );

        //! Return problem type for given problem ID.
        static RProblemType getTypeFromId(const QString &problemId);

        //! Return problem ID for specified problem type.
        static QString getId ( RProblemType type );

        //! Return problem name for specified problem type.
        static QString getName ( RProblemType type );

        //! Return problem description for specified problem type.
        static QString getDesc ( RProblemType type );

        //! Return time-solver is enabled for specified problem type.
        static bool getTimeSolverEnabled ( RProblemTypeMask typeMask );

        //! Return required problem type mask.
        static RProblemTypeMask getRequiredProblemTypeMask ( RProblemTypeMask typeMask );

        //! Return excluded problem type mask.
        static RProblemTypeMask getExcludedProblemTypeMask ( RProblemTypeMask typeMask );

        //! Return list of problem names for specified problem type mask.
        static std::vector<RProblemType> getTypes ( RProblemTypeMask typeMask );

        //! Return list of possible result variable types for specific problem type mask.
        static std::vector<RVariableType> getVariableTypes ( RProblemTypeMask typeMask );

};

#endif /* __RML_PROBLEM_H__ */
