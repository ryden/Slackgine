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
// FILE:        scene.cpp
// PURPOSE:     Component controlling the scene type entities.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#include "scene.h"
#include "l3m/Components/camera.h"
#include "l3m/Components/scene.h"
#include "../entity.h"
#include "math/matrix.h"
#include "math/transform.h"

using namespace Core::Entities;

Scene::Scene ()
: IComponent ( 0, false, true )
, m_model ( 0 )
, m_camera ( 0 )
{
}

Scene::~Scene()
{
    DestroyTheCamera ();
}

void Scene::DestroyTheCamera ()
{
    if ( m_camera != 0 )
    {
        delete m_camera;
        m_camera = 0;
    }
}

void Scene::FindTheModelCamera ( const l3m::Model* model )
{
    if ( m_model == model )
        return;
    
    m_model = model;
    if ( !m_model )
        return DestroyTheCamera ();
    
    // Find the scene component
    l3m::Scene* scene = 0;
    const l3m::Model::componentVector& components = m_model->components();
    for ( l3m::Model::componentVector::const_iterator iter = components.begin();
          iter != components.end();
          ++iter )
    {
        if ( (*iter)->type() == "scene" )
        {
            scene = static_cast < l3m::Scene* > ( *iter );
            break;
        }
    }
    
    // Make sure that there is a scene
    if ( !scene )
        return DestroyTheCamera ();

    // Find the scene camera
    if ( scene->camera() != "" )
    {
        // Find the referenced camera
        for ( l3m::Model::componentVector::const_iterator iter = components.begin();
              iter != components.end();
              ++iter )
        {
            if ( (*iter)->type() == "camera" )
            {
                l3m::Camera* cam = static_cast<l3m::Camera *>(*iter);
                if ( cam->name() == scene->camera() )
                {
                    switch ( cam->type() )
                    {
                        case l3m::Camera::CAMERA_ORTHOGRAPHIC:
                            m_camera = new Camera ();
                            m_camera->SetOrthographic( cam->orthographicData().left,
                                                       cam->orthographicData().right,
                                                       cam->orthographicData().top,
                                                       cam->orthographicData().bottom,
                                                       cam->orthographicData().near,
                                                       cam->orthographicData().far );
                            break;
                        case l3m::Camera::CAMERA_PERSPECTIVE:
                            m_camera = new Camera ();
                            m_camera->SetPerspective( cam->perspectiveData().fov,
                                                      cam->perspectiveData().aspect,
                                                      cam->perspectiveData().near,
                                                      cam->perspectiveData().far );
                            break;
                        default:
                            break;
                    }
                    
                    // If it was a valid camera, copy its transform
                    if ( m_camera )
                        m_camera->transform() = cam->transform();
                    
                    break;
                }
            }
        }
    }
}

void Scene::PreRender ( Renderer::IRenderer* renderer )
{
    if ( !parent() )
        return;
    
    FindTheModelCamera ( parent()->GetModel() );
    if ( m_camera != 0 )
    {
        Matrix projection = m_camera->GetProjection();
        LookatMatrix lookAt ( m_camera->transform().orientation(), m_camera->transform().translation() );
        renderer->SetCamera ( projection, lookAt );
    }
}