/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2012
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        texture.cpp
// PURPOSE:     OpenGL3 textures.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#include "texture.h"

using namespace Renderer;

OpenGL3_Texture::OpenGL3_Texture ( u32 width, u32 height, ITexture::Format format )
{
    m_format = convertFormat (format);
    m_handler = 0;
    m_width = width;
    m_height = height;
}

OpenGL3_Texture::~OpenGL3_Texture ()
{
    if ( m_handler != 0 )
        glDeleteTextures ( 1, &m_handler );
}

void OpenGL3_Texture::loadPixmap (const Pixmap& pix)
{
    m_pixmap = pix;
    m_pixmap.resample ( m_width, m_height );
    
    if ( m_handler != 0 )
    {
        glBindTexture ( GL_TEXTURE_2D, m_handler );
        eglGetError ();
        glTexSubImage2D ( GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_pixmap.pixels() );
        eglGetError ();
    }
}

void OpenGL3_Texture::storePixmap (Pixmap* output) const
{
    // TODO
}

bool OpenGL3_Texture::bind ()
{
    if ( m_handler == 0 )
    {
        bool ok = false;
        if ( m_format != GL_INVALID_ENUM )
        {
            glGenTextures ( 1, &m_handler );
            eglGetError ();
            if ( m_handler != 0 )
            {
                glBindTexture ( GL_TEXTURE_2D, m_handler );
                eglGetError ();
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
                eglGetError ();
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
                eglGetError ();
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
                eglGetError ();
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
                eglGetError ();
                glTexImage2D ( GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
                eglGetError ();
                
                glBindTexture ( GL_TEXTURE_2D, m_handler );
                eglGetError ();
                glTexSubImage2D ( GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_pixmap.pixels() );
                eglGetError ();
                
                ok = true;
            }
        }
        
        if ( ok == false )
            return false;
    }
    
    if ( m_handler != 0 )
    {
        glBindTexture ( GL_TEXTURE_2D, m_handler );
        return true;
    }
    return false;
}

GLenum OpenGL3_Texture::convertFormat (ITexture::Format format)
{
    GLenum ret;
    
    switch ( format )
    {
        case ALPHA4: ret = GL_ALPHA4; break;
        case ALPHA8: ret = GL_ALPHA8; break;
        case ALPHA12: ret = GL_ALPHA12; break;
        case ALPHA16: ret = GL_ALPHA16; break;
        case RGB4: ret = GL_RGB4; break;
        case RGBA4: ret = GL_RGBA4; break;
        case RGB5: ret = GL_RGB5; break;
        case RGB5_A1: ret = GL_RGB5_A1; break;
        case RGB8: ret = GL_RGB8; break;
        case RGBA8: ret = GL_RGBA8; break;
        case RGB10_A2: ret = GL_RGB10_A2; break;
        case RGBA12: ret = GL_RGBA12; break;
        case RGBA16: ret = GL_RGBA16; break;
        case RGBA: ret = GL_RGBA; break;
        default:
            ret = GL_INVALID_ENUM;
            break;
    }
    
    return ret;
}
