/////////////////////////////////////////////////////////////
//
// Slackgine - Copyright (C) 2010-2011
// The Slackgine development team
//
// See the LICENSE file in the top-level directory.
//
// FILE:        geometry.h
// PURPOSE:     Base geometry functions, to be extended by the rendering engine specific data.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#include <map>
#include <list>
#include <string>
#include "mesh.h"
#include "vertex.h"
#include "math/boundingbox.h"
#include "math/boundingsphere.h"

namespace Renderer
{

class GeometryBase
{
public:
    typedef std::list<Mesh *> meshList;
    struct VertexLayer
    {
        void*   data;
        u32     elementSize;
        u32     numLevels;
    };
    typedef std::map < std::string, VertexLayer > layerMap;

private:
    std::string         m_name;
    Renderer::Vertex*   m_vertices;
    u32                 m_numVertices;
    layerMap            m_mapVertexLayers;
    meshList            m_meshes;
    BoundingBox         m_bbox;
    BoundingSphere      m_bsphere;
    Vector3             m_centroid;
    
private:
    void        FreeVertices    ();
    
public:
                GeometryBase        ();
    virtual     ~GeometryBase       ();


    void        LoadMesh        ( Mesh* mesh );
    void        Set             ( Renderer::Vertex* pVertices, u32 vertexCount );
    
    // Vertex layers
public:
    template < typename T >
    T*          CreateVertexLayer       ( const std::string& name, u32 numLevels, T* data = 0 )
    {
        return reinterpret_cast < T* > ( CreateVertexLayer ( name, data, sizeof(T) ) );
    }
    
    void*       CreateVertexLayer       ( const std::string& name, u32 numLevels, void* data, u32 elementSize )
    {
        void* destination = GetVertexLayer<void *> ( name );

        if ( destination == 0 )
        {
            VertexLayer layer;
            layer.elementSize = elementSize;
            layer.numLevels = numLevels;
            layer.data = malloc ( numLevels * elementSize * numVertices() );
            m_mapVertexLayers.insert ( layerMap::value_type ( name, layer ) );
            
            destination = layer.data;
        }
        
        if ( data != 0 )
            memcpy ( destination, data, numLevels * elementSize * numVertices() );
        
        return destination;
    }

    template < typename T >
    T*          GetVertexLayer          ( const std::string& name, u32 level = 0 )
    {
        char* layerData = 0;
        layerMap::iterator iter = m_mapVertexLayers.find ( name );
        if ( iter != m_mapVertexLayers.end() )
        {
            layerData = reinterpret_cast < char* > ( iter->second.data );
            layerData = &layerData [ level * numVertices() ];
        }
        return reinterpret_cast < T* > ( layerData );
    }
    
    u32         GetVertexLayerLevelCount( const std::string& name ) const
    {
        layerMap::const_iterator iter = m_mapVertexLayers.find ( name );
        u32 count = 0;
        if ( iter != m_mapVertexLayers.end() )
            count = iter->second.numLevels;
        return count;
    }
    
    bool        DeleteVertexLayer       ( const std::string& name )
    {
        layerMap::iterator iter = m_mapVertexLayers.find ( name );
        if ( iter != m_mapVertexLayers.end() )
        {
            free ( iter->second.data );
            m_mapVertexLayers.erase ( iter );
            return true;
        }
        return false;
    }
    
    //--------------------------------------------------------------------------
    // Accessors
public:
    const std::string&          name            () const { return m_name; }
    const Renderer::Vertex*     vertices        () const { return m_vertices; }
    const u32&                  numVertices     () const { return m_numVertices;; }
    const meshList&             meshes          () const { return m_meshes; }
    const layerMap&             vertexLayers    () const { return m_mapVertexLayers; }
    const BoundingBox&          boundingBox     () const { return m_bbox; }
    const BoundingSphere&       boundingSphere  () const { return m_bsphere; }
    const Vector3&              centroid        () const { return m_centroid; }
    
    std::string&                name            () { return m_name; }
    Renderer::Vertex*&          vertices        () { return m_vertices; }
    meshList&                   meshes          () { return m_meshes; }
    layerMap&                   vertexLayers    () { return m_mapVertexLayers; }
    BoundingBox&                boundingBox     () { return m_bbox; }
    BoundingSphere&             boundingSphere  () { return m_bsphere; }
    Vector3&                    centroid        () { return m_centroid; }
};

}

// Include the renderer selection through the renderer header to get the actual geometry definition
#include "renderer.h"