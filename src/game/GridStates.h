/*
 * Copyright (C) 2010 DiamondCore <http://easy-emu.de/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef DIAMOND_GRIDSTATES_H
#define DIAMOND_GRIDSTATES_H

#include "Map.h"

class DIAMOND_DLL_DECL GridState
{
    public:

        virtual void Update(Map &, NGridType&, GridInfo &, const uint32 &x, const uint32 &y, const uint32 &t_diff) const = 0;
};

class DIAMOND_DLL_DECL InvalidState : public GridState
{
    public:

        void Update(Map &, NGridType &, GridInfo &, const uint32 &x, const uint32 &y, const uint32 &t_diff) const;
};

class DIAMOND_DLL_DECL ActiveState : public GridState
{
    public:

        void Update(Map &, NGridType &, GridInfo &, const uint32 &x, const uint32 &y, const uint32 &t_diff) const;
};

class DIAMOND_DLL_DECL IdleState : public GridState
{
    public:

        void Update(Map &, NGridType &, GridInfo &, const uint32 &x, const uint32 &y, const uint32 &t_diff) const;
};

class DIAMOND_DLL_DECL RemovalState : public GridState
{
    public:

        void Update(Map &, NGridType &, GridInfo &, const uint32 &x, const uint32 &y, const uint32 &t_diff) const;
};

#endif
