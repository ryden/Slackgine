/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        slackgine.h
// PURPOSE:     Slackgine main class.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#include "renderer/renderer.h"
#include "renderer/strategies/render_strategy.h"
#include "l3m/l3m.h"
#include "shared/platform.h"
#include "shader_manager.h"
#include "model_manager.h"
#include "time.h"
#include "world.h"
#include "camera.h"

namespace Renderer { class RenderStrategy; }

namespace Core
{
    
class Slackgine
{
    //--------------------------------------------------------------------------
    // Context management
    // When a Slackgine instance gets ticket, the current thread context is set
    // to that Slackgine instance, doing the subsequent calls to the slackgine
    // use that context through getInstance().
    // TODO: Make it thread safe.
private:
    static Slackgine*           ms_context;
    static void                 setContext              ( Slackgine* );
public:
    static Slackgine*           getInstance             ()
    {
        return ms_context;
    }

public:
                                Slackgine               ();
                                ~Slackgine              ();

    bool                        initialize              ();
    
    void                        tick                    ();
    bool                        beginScene              ( Camera* cam );
    bool                        render                  ( Entity* startAt = 0 );
    bool                        endScene                ();
                
    Renderer::IRenderer*        getRenderer             () { return m_renderer; }
    ModelManager&               getModelManager         () { return m_modelManager; }
    TextureManager&             getTextureManager       () { return m_textureManager; }
    ShaderManager&              getShaderManager        () { return m_shaderManager; }
    Time&                       getTime                 () { return m_time; }
    World&                      getWorld                () { return m_world; }
    
    //--------------------------------------------------------------------------
    // Function to iterate the world entities.
    typedef FastDelegate2<Slackgine*, Entity*, bool> ForEachEntityDelegate;
    void                        forEachEntity           ( ForEachEntityDelegate delegate,
                                                          bool includeInvisible = false,
                                                          Entity* startAt = 0 );
    
    void                        getError                ( char* dest ) const;
    
    //--------------------------------------------------------------------------
    // Stuff related to the render strategy
    void                        setRenderStrategy       ( Renderer::RenderStrategy* strategy );
    Renderer::RenderStrategy*   getRenderStrategy       ();
    
private:
    Renderer::IRenderer*        m_renderer;
    Time                        m_time;
    TextureManager              m_textureManager;
    ModelManager                m_modelManager;
    ShaderManager               m_shaderManager;
    World                       m_world;
    char                        m_error [ 256 ];
    Renderer::RenderStrategy*   m_renderStrategy;
};

}
