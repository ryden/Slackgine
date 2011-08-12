#pragma once

#include "shared/pixmap.h"
#include "../component.h"

namespace l3m
{

class Texture : public IComponent
{
public:
    static IComponent* Create ()
    {
        return new Texture ();
    }
    
public:
                Texture         ();
                ~Texture        ();
    
    bool        Load            ( l3m::IStream& stream, float version );
    bool        Save            ( l3m::OStream& stream );
    
    
    // Accessors
    std::string&        id      () { return m_id; }
    Pixmap&             pixmap  () { return m_image; }
    
    const std::string&  id      () const { return m_id; }
    const Pixmap&       pixmap  () const { return m_image; }
    
private:
    std::string         m_id;
    Pixmap              m_image;
};

}