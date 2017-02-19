/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   gl_texture.h                                             *
 *  GROUP:  Range                                                    *
 *  TYPE:   header file (*.h)                                        *
 *  DATE:   9-th May 2013                                            *
 *                                                                   *
 *  DESCRIPTION: OpenGL texture class declaration                    *
 *********************************************************************/

#ifndef __GL_TEXTURE_H__
#define __GL_TEXTURE_H__

#include <QOpenGLTexture>

#include <QString>
#include <QImage>

class GLTexture
{
    private:

        //! Texture.
        QOpenGLTexture *texture;
        //! Texture loaded flag.
        bool loaded;

    public:

        //! Constructor.
        GLTexture();

        //! Destructor.
        ~GLTexture();

        //! Load texture
        void load(const QString &file);

        //! Unload texture
        void unload(void);
};

#endif // __GL_TEXTURE_H__
