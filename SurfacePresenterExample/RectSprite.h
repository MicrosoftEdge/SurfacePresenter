/*=====================================================================
  Microsoft 
  ISurfacePresenter Code Sample.

  Copyright (C) 2010 Microsoft Corporation.  All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation.  See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
=====================================================================*/
#pragma once

// The rectangle sprites that are rendered store their data and logic in
// this class. Basically they just bounce around in the provided box.
struct RectSprite
{
    static const int Size = 64;

    CPoint _position;
    CPoint _velocity;

    void Reset(CSize canvasSize)
    {
        _position.x = ::rand() * (canvasSize.cx - Size) / RAND_MAX;
        _position.y = ::rand() * (canvasSize.cx - Size) / RAND_MAX;

        _velocity.x = (::rand() * Size / RAND_MAX) - Size / 2;
        _velocity.y = (::rand() * Size / RAND_MAX) - Size / 2;
    }

    void Tick(CSize canvasSize)
    {
        _position += _velocity;

        if (_position.x < 0 || (_position.x + Size) > canvasSize.cx)
        {
            _velocity.x = -_velocity.x;
        }

        if (_position.y < 0 || (_position.y + Size) > canvasSize.cy)
        {
            _velocity.y = -_velocity.y;
        }
    }
};

