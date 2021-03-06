/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2012
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        default.cpp
// PURPOSE:     CDefault strategy.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#include "default.h"
#include "slackgine.h"
#include "core/shader_manager.h"

using namespace Renderer::Strategy;
using Core::Entity;

Default::Default ()
{
  m_program = 0;
}

Default::~Default ()
{
  if (m_program != 0)
    sgDelete m_program;
}

bool Default::initialize (Core::Slackgine* sg)
{    
    if ( m_program == 0 )
    {
        Core::Shader* sh = sg->getShaderManager().load ( "default" );
        if ( !sh )
        {
            setError ( "Unable to load the shader" );
            return false;
        }
        if ( sh->vert() == 0 && sh->frag() == 0 )
        {
            setError ( "No shaders loaded" );
            return false;
        }

        m_program = Renderer::Factory::createProgram();
        if ( sh->vert() != 0 )
            m_program->attachShader ( sh->vert() );
        if ( sh->frag() != 0 )
            m_program->attachShader ( sh->frag() );
        if ( !m_program->link() )
        {
            char errmsg [ 512 ];
            char linkerr [ 512 ];
            m_program->getError ( linkerr );
            snprintf ( errmsg, sizeof(errmsg), "Unable to link the shader: %s", linkerr );
            setError ( errmsg );
            return false;
        }
    }
    return true;
}

bool Default::beginScene (Core::Slackgine* sg, Core::Camera* cam)
{   
    if ( !initialize(sg) ) {
      return false;
    }
    
    IRenderer* renderer = sg->getRenderer();
    renderer->setProgram( m_program );
    
    m_matLookAt = LookatMatrix ( cam->transform().orientation(), cam->transform().translation() );
    
    return this->isOk();
}

bool Default::forEachEntity(Core::Slackgine* sg, Core::Entity* entity)
{
    // Manage the entity stack
    if ( mEntityStack.size() > 0 && mEntityStack.back() != entity->getParent() )
        mEntityStack.pop_back();
    mEntityStack.push_back(entity);
    Transform entityTransform = mEntityStack.getTransform ();
    
    // Render it!
    if ( entity->getModel() != 0 )
    {
        l3m::Scene* sce = l3m::Util::findScene ( entity->getModel() );
        if ( sce != 0 )
        {
            // For each geometry...
            for ( l3m::Scene::NodesVector::iterator iter = sce->geometryNodes().begin();
                iter != sce->geometryNodes().end();
                ++iter )
            {
                l3m::Scene::Node& node = *iter;
                Transform transform = entityTransform * node.transform;
                sg->getRenderer()->render( node.geometry, transform, false, getMeshHandler() );

                // Enqueue transparent stuff for later
                for ( Geometry::meshNodeVector::iterator iter2 = node.geometry->m_meshNodes.begin();
                      iter2 != node.geometry->m_meshNodes.end();
                      ++iter2 )
                {
                    Mesh* mesh = (*iter2).mesh;
                    if ( mesh->material() != 0 && mesh->material()->isTransparent() == true )
                    {
                        Vector3 pos = m_matLookAt * transform.translation();
                        m_listTransparencies.push_back(DeferredMesh(node.geometry, mesh, pos.length(), transform));
                    }
                }
            }
        }
    }
    
    return true;
}

bool Default::execute (Core::Slackgine* sg, Core::Entity* startAt)
{
    mEntityStack.clear ();
    sg->forEachEntity ( MakeDelegate(this, &Default::forEachEntity), false, startAt );
    return true;
}

bool Default::endScene ( Core::Slackgine* sg )
{
    // Now, render the transparent stuff.
    m_listTransparencies.sort();
    for ( TransparentMeshList::iterator iter = m_listTransparencies.begin();
          iter != m_listTransparencies.end();
          ++iter )
    {
        DeferredMesh& node = *iter;
        sg->getRenderer()->renderGeometryMesh ( node.geometry, node.mesh, node.transform, getMeshHandler() );
    }
    m_listTransparencies.clear ();
    
    return true;
}

Transform Default::EntityStack::getTransform()
{
    if ( size() == 0 )
        return IdentityTransform();

    Transform transform = operator[](0)->transform();
    for ( u32 i = 1; i < size(); ++i )
        transform = operator[](i)->transform() * transform;
    return transform;
}
