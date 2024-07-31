#pragma once

/*
 *  Copyright(c) 2015 Jeremiah van Oosten
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files(the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions :
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */

/**
 *  @file Query.h
 *  @date April 6, 2016
 *  @author jeremiah
 *
 *  @brief Interface for GPU query objects.
 */

#include "../EngineDefines.h"
#include "GraphicsEnums.h"

namespace Graphics
{
    class ComputeCommandQueue;

    struct ENGINE_DLL QueryResult
    {
        union
        {
            double   ElapsedTime;                   // Valid for QueryType::Timer queries. Returns the elapsed time in seconds between Query::Begin and Query::End.
            uint64_t NumSamples;                    // Valid for QueryType::Occlusion. Returns the number of samples written by the fragment shader between Query::Begin and Query::End.
            bool     AnySamples;                    // Valid for QueryType::OcclusionPredicate. Returns true if any samples were written by the fragment shader between Query::Begin and Query::End.
        };
        // Are the results of the query valid?
        // You should check this before using the value.
        bool IsValid;
    };
}