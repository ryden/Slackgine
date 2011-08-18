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
// FILE:        thread.h
// PURPOSE:     Thread encapsulation.
// AUTHORS:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#include <pthread.h>
#include "platform.h"
#include "FastDelegate.h"

using namespace fastdelegate;

class Thread
{
public:
    enum
    {
        THREAD_JOINABLE = 0x01,
        THREAD_CREATED  = 0x02,
        THREAD_STARTED  = 0x04
    };
    typedef FastDelegate2<Thread*, void*, void*> MainFn;
    
public:
                Thread          () : m_flags(0) {}
                Thread          ( MainFn fn, u32 flags = 0 );
                ~Thread         ();
                
    void        Create          ( MainFn fn, u32 flags = 0 );
    void        CreateStarted   ( MainFn fn, void* data = 0, u32 flags = 0 );
    void        Start           ( void* data = 0 );
    void        Stop            ();
    void        Join            ( void** ret );
    void        Detach          ();
    
    bool        IsOk            () const { return IsCreated(); }
    bool        IsCreated       () const { return ( m_flags & THREAD_CREATED ) == THREAD_CREATED; }
    bool        IsStarted       () const { return ( m_flags & THREAD_STARTED ) == THREAD_STARTED; }

private:
    struct ThreadInitStruct
    {
        void*   data;
    } m_initStruct;
    static void* __thread_init ( void* );
    
private:
    u32                 m_flags;
    pthread_t           m_handler;
    pthread_attr_t      m_attributes;
    MainFn              m_mainFn;
};