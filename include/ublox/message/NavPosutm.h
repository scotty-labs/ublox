//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

using NavPosutmFields = std::tuple<
    field::nav::ITOW,
    field::nav::EAST,
    field::nav::NORTH,
    field::nav::ALT,
    field::nav::ZONE,
    field::nav::HEM
>;


template <typename TMsgBase = Message>
class NavPosutm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSUTM>,
        comms::option::FieldsImpl<NavPosutmFields>,
        comms::option::DispatchImpl<NavPosutm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSUTM>,
        comms::option::FieldsImpl<NavPosutmFields>,
        comms::option::DispatchImpl<NavPosutm<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_East,
        FieldIdx_North,
        FieldIdx_Alt,
        FieldIdx_Zone,
        FieldIdx_Hem,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavPosutm() = default;
    NavPosutm(const NavPosutm&) = default;
    NavPosutm(NavPosutm&& other) = default;
    virtual ~NavPosutm() = default;

    NavPosutm& operator=(const NavPosutm&) = default;
    NavPosutm& operator=(NavPosutm&&) = default;
};


}  // namespace message

}  // namespace ublox





