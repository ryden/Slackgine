/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        delete_unused.cpp
// PURPOSE:     Strategy to filter unused components.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#include <l3m/Components/components.h>
#include "delete_unused.h"
#include <map>
#include <vector>

bool delete_unused ( l3m::Model* model )
{
    typedef std::map < std::string, bool > CheckMap;
    CheckMap materials;
    
    // Check for the used materials
    l3m::Model::componentVector& components = model->components();
    for ( l3m::Model::componentVector::iterator iter = components.begin();
          iter != components.end();
          ++iter )
    {
        if ( (*iter)->type() == "geometry" )
        {
            l3m::Geometry* g = static_cast<l3m::Geometry*>(*iter);
            for ( Renderer::Geometry::meshList::iterator iter2 = g->geometry().meshes().begin();
                  iter2 != g->geometry().meshes().end();
                  ++iter2 )
            {
                Renderer::Mesh* m = *iter2;
                if ( m->material() != 0 )
                    materials[m->material()->name()] = true;
            }
        }
    }
    for ( l3m::Model::componentVector::iterator iter = components.begin();
          iter != components.end();
        )
    {
        if ( (*iter)->type() == "material" )
        {
            l3m::Material* m = static_cast<l3m::Material*>(*iter);
            if ( materials.find(m->material().name()) == materials.end() )
            {
                fprintf ( stderr, "Deleting unused material: %s\n", m->material().name().c_str() );
                iter = components.erase(iter);
                continue;
            }
        }
        
        ++iter;
    }    
    
}