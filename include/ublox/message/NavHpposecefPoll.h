//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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

/// @file
/// @brief Contains definition of NAV-HPPOSECEF (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-HPPOSECEF (@b poll) message fields.
/// @see NavHpposecefPoll
struct NavHpposecefPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of NAV-HPPOSECEF (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavHpposecefPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavHpposecefPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_HPPOSECEF>,
        comms::option::FieldsImpl<NavHpposecefPollFields::All>,
        comms::option::MsgType<NavHpposecefPoll<TMsgBase> >
    >
{
public:

    /// @brief Default constructor
    NavHpposecefPoll() = default;

    /// @brief Copy constructor
    NavHpposecefPoll(const NavHpposecefPoll&) = default;

    /// @brief Move constructor
    NavHpposecefPoll(NavHpposecefPoll&& other) = default;

    /// @brief Destructor
    ~NavHpposecefPoll() = default;

    /// @brief Copy assignment
    NavHpposecefPoll& operator=(const NavHpposecefPoll&) = default;

    /// @brief Move assignment
    NavHpposecefPoll& operator=(NavHpposecefPoll&&) = default;
};


}  // namespace message

}  // namespace ublox




