/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011 - Alberto Alonso
//
// Redistribution of this software, including any of its
// files, in either binary or source code form is totally
// forbidden without the permission of its owners.
//
// Owners reserve their right to legal action against any
// person or company that fails to do so.
//
// For more detailed information, see the LICENSE file in
// the top-level directory.
//
// FILE:        entity.h
// PURPOSE:     Entity base class. Component management.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#include "math/matrix.h"
#include "l3m/l3m.h"
#include "entity_components/component.h"
#include "entity_components/model_renderer.h"
#include "renderer/renderer.h"
#include "transformable.h"

namespace Core {

class Entity : public Transformable
{
    friend class World;
    
public:
    typedef std::vector < Entities::IComponent* > ComponentVector;
    typedef std::vector < Entity* > EntityVector;
    
public:
                                Entity          ( l3m::Model* pModel = 0, Entity* parent = 0 );
                                Entity          ( Entity* parent );
    virtual                     ~Entity         ();
    
    void                        setParent       ( Entity* parent );
    
    l3m::Model*                 getModel        () const { return m_model; }
    void                        setModel        ( l3m::Model* pModel );
    
    void                        tick            ();
    void                        render          ( Renderer::IRenderer* renderer );
    
    bool                        addComponent    ( Entities::IComponent* component );
    
private:
    //--------------------------------------------------------------------------
    // Child entities linkage.
    void                        linkChild       ( Entity* entity );
    void                        unlinkChild     ( Entity* entity );

private:
    Entity*                     m_parent;
    EntityVector                m_children;
    l3m::Model*                 m_model;
    
    ComponentVector             m_tickableComponents;
    ComponentVector             m_renderableComponents;
    Entities::ModelRenderer*    m_modelRenderer;
};

}
