/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   rml_surface.h                                            *
 *  GROUP:  RML                                                      *
 *  TYPE:   header file (*.h)                                        *
 *  DATE:   8-th December 2011                                       *
 *                                                                   *
 *  DESCRIPTION: Surface class declaration                           *
 *********************************************************************/

#ifndef __RML_SURFACE_H__
#define __RML_SURFACE_H__

#include <vector>

#include "rml_element.h"
#include "rml_element_group.h"

//! Surface element group class
class RSurface : public RElementGroup
{

    public:

        //! Default entity name.
        const static QString defaultName;

    private:

        //! Internal initialization function.
        void _init ( const RSurface *pSurface = 0 );

    protected:

        //! Surface artificial thickness.
        double thickness;

    public:

        //! Constructor.
        RSurface ();

        //! Copy constructor.
        RSurface (const RSurface &surface);

        //! Destructor.
        ~RSurface ();

        //! Return surface group artificial thickness.
        double getThickness ( void ) const;

        //! Set surface group artificial thickness.
        void setThickness ( double thickness );

        //! Return true if point is inside the surface.
        //! Surface must be enclosed.
        bool pointInside(const std::vector<RNode> &nodes, const std::vector<RElement> &elements, const RR3Vector &point) const;

        //! Check if points are inside the surface.
        //! Surface must be enclosed.
        std::vector<bool> pointsInside(const std::vector<RNode> &nodes, const std::vector<RElement> &elements, const std::vector<RR3Vector> &points) const;

        //! Tetrahedralize surface.
        std::vector<RElement> tetrahedralize(const std::vector<RNode> &nodes, const std::vector<RElement> &elements) const;

        //! Find surface area.
        double findArea(const std::vector<RNode> &nodes, const std::vector<RElement> &elements) const;

        //! Find average normal.
        void findAverageNormal(const std::vector<RNode> &nodes, const std::vector<RElement> &elements, RR3Vector &normal) const;

        //! Assignment operator.
        RSurface & operator = ( const RSurface &surface );

        //! Allow RFileIO to access private members.
        friend class RFileIO;

};

#endif /* __RML_SURFACE_H__ */
