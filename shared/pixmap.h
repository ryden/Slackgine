#pragma once

#include <iostream>
#include "color.h"

class Pixmap
{
public:
                        Pixmap          ();
                        Pixmap          ( u32 width, u32 height );
                        Pixmap          ( const Pixmap& other );
                        ~Pixmap         ();
private:
    void                CleanupData     ();
    
public:
    Pixmap&             operator=       ( const Pixmap& other );
    bool                operator==      ( const Pixmap& other ) const;
    bool                operator!=      ( const Pixmap& other ) const;
    
    void                Create          ( u32 width, u32 height, const Color* data = 0 );

    bool                Load            ( const char* filename );
    bool                Load            ( std::istream& stream );
    bool                SavePNG         ( const char* filename );
    bool                SavePNG         ( std::ostream& stream );

    const char*         error           () const { return m_error; }
    const u32&          width           () const { return m_width; }
    const u32&          height          () const { return m_height; }
    const Color*        pixels          () const { return m_pixels; }
    Color*              pixels          () { return m_pixels; }
    
private:
    bool                LoadPNG         ( std::istream& stream );

private:
    u32         m_width;
    u32         m_height;
    Color*      m_pixels;
    char        m_error [ 512 ];
};