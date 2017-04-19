//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of CFG-TP5 (<b>poll selected</b>) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{
/// @brief Accumulates details of all the CFG-TP5 (<b>poll selected</b>) message fields.
/// @see CfgTp5PollSelect
struct CfgTp5PollSelectFields
{
    /// @brief Value enumeration for @ref tpIdx field
    using TpIdx = field::cfg::TpIdx;

    /// @brief Definition of "tpIdx" field.
    using tpIdx = field::cfg::tpIdx;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        tpIdx
    >;
};

/// @brief Definition of CFG-TP5 (<b>poll selected</b>) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgTp5PollSelectFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTp5PollSelect : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP5>,
        comms::option::FieldsImpl<CfgTp5PollSelectFields::All>,
        comms::option::MsgType<CfgTp5PollSelect<TMsgBase> >
    >
{
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b tpIdx for @ref CfgTp5PollSelectFields::tpIdx field
    COMMS_MSG_FIELDS_ACCESS(tpIdx);

    /// @brief Default constructor
    CfgTp5PollSelect() = default;

    /// @brief Copy constructor
    CfgTp5PollSelect(const CfgTp5PollSelect&) = default;

    /// @brief Move constructor
    CfgTp5PollSelect(CfgTp5PollSelect&& other) = default;

    /// @brief Destructor
    ~CfgTp5PollSelect() = default;

    /// @brief Copy assignment
    CfgTp5PollSelect& operator=(const CfgTp5PollSelect&) = default;

    /// @brief Move assignment
    CfgTp5PollSelect& operator=(CfgTp5PollSelect&&) = default;
};


}  // namespace message

}  // namespace ublox

