/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        main.cpp
// PURPOSE:     Main test file.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include "slackgine.h"
#include "l3m/l3m.h"
#include "renderer/strategies/default.h"

void display ( void );

using namespace Core;

static Entity* entity = 0;
static l3m::Model* model = 0;
static Slackgine* sg = 0;
static Camera* cam = 0;

static void cleanup ()
{
    if ( sg != 0 )
        delete sg;
}

int main(int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitWindowSize (1920/2, 1080/2);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutCreateWindow ("Slackgine test");
    
    glutDisplayFunc ( display );
    atexit ( cleanup );
    glViewport(0, 0, 1920/2, 1080/2);

    glutMainLoop ();
    
    delete entity;
    
    return EXIT_SUCCESS;
}


void display ( void )
{
    if ( sg == 0 )
    {
        sg = new Slackgine ();
        sg->initialize ();
        sg->getModelManager().addLookupPath ( ".." );
        sg->getShaderManager().addLookupPath( "../shaders" );
        sg->setRenderStrategy < Renderer::Strategy::Default > ();
    }

    if ( model == 0 )
    {
        model = sg->getModelManager().requestBlocking ("spherecube.l3m");
        l3m::Scene* sce = l3m::Util::findScene(model);
        if ( sce != 0 )
            glutReshapeWindow( sce->width(), sce->height() );
    }
    if ( entity == 0 )
    {
        entity = new Entity ( model );
        entity->setParent( &sg->getWorld() );
        l3m::Scene* sce = l3m::Util::findScene ( model );
        if ( sce != 0 )
        {
            cam = new Camera ( sce->camera() );
        }
    }
    
    sg->tick ();
    if ( !sg->render(cam) )
    {
        char error [ 1024 ];
        sg->getError ( error );
        fprintf ( stderr, "Error rendering the scene: %s\n", error );
    }
    
    glutSwapBuffers ();
    
    glutPostRedisplay ();
}
