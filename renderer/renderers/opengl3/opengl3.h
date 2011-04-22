#ifndef OPENGL3_H
#define	OPENGL3_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#if defined(DEBUG)
// This code Copyright (c) Max Rupp
#define eglError( Error )\
{\
fprintf(stderr, "OpenGL Error: %s\n", Error );\
\
exit( -1 );\
}

#define eglGetError( )\
{\
for ( GLenum Error = glGetError( ); ( GL_NO_ERROR != Error ); Error = glGetError( ) )\
{\
switch ( Error )\
{\
case GL_INVALID_ENUM:      eglError( "GL_INVALID_ENUM"      ); break;\
case GL_INVALID_VALUE:     eglError( "GL_INVALID_VALUE"     ); break;\
case GL_INVALID_OPERATION: eglError( "GL_INVALID_OPERATION" ); break;\
case GL_STACK_OVERFLOW:    eglError( "GL_STACK_OVERFLOW"    ); break;\
case GL_STACK_UNDERFLOW:   eglError( "GL_STACK_UNDERFLOW"   ); break;\
case GL_OUT_OF_MEMORY:     eglError( "GL_OUT_OF_MEMORY"     ); break;\
default:                                                       break;\
}\
}\
}
// End of (c) Max Rupp code.
#else
#define eglGetError()
#endif

#include "../../shader.h"
#include "../../program.h"
#include "../../renderer.h"
#include "shader.h"
#include "program.h"
#include "renderer.h"

class Renderer
{
public:
    static IRenderer* Instance ()
    {
        static IRenderer* instance = 0;
        if ( instance == 0 )
            instance = new OpenGL3_Renderer ();
        return instance;
    }
    
    static IProgram* CreateProgram ()
    {
        return new OpenGL3_Program ();
    }
    
    static IShader* CreateShader ( IShader::Type type, const char* file )
    {
        IShader* shader = new OpenGL3_Shader ( type );
        shader->Load ( file );
        return shader;
    }
    
    static IShader* CreateShader ( IShader::Type type, std::istream& fp )
    {
        IShader* shader = new OpenGL3_Shader ( type );
        shader->Load ( fp );
        return shader;
    }
};

#endif
