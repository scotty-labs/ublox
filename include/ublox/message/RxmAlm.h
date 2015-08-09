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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

using RxmAlmFields = std::tuple<
    field::rxm::SVID_Ext,
    field::rxm::WEEK_Ext,
    comms::field::Optional<
        comms::field::ArrayList<
            field::common::FieldBase,
            field::rxm::DWORD,
            comms::option::SequenceFixedSize<8>
        >
    >
>;

template <typename TMsgBase = Message>
class RxmAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmFields>,
        comms::option::DispatchImpl<RxmAlm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmFields>,
        comms::option::DispatchImpl<RxmAlm<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Svid,
        FieldIdx_Week,
        FieldIdx_Data,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    RxmAlm()
    {
        auto& allFields = Base::fields();
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        dataField.setMode(comms::field::OptionalMode::Missing);
    }
    RxmAlm(const RxmAlm&) = default;
    RxmAlm(RxmAlm&& other) = default;
    virtual ~RxmAlm() = default;

    RxmAlm& operator=(const RxmAlm&) = default;
    RxmAlm& operator=(RxmAlm&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_Data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& weekField = std::get<FieldIdx_Week>(allFields);
        auto dataMode = comms::field::OptionalMode::Exists;
        if (weekField.value() == 0U) {
            dataMode = comms::field::OptionalMode::Missing;
        }

        auto& dataField = std::get<FieldIdx_Data>(allFields);
        dataField.setMode(dataMode);
        return Base::template readFieldsFrom<FieldIdx_Data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& weekField = std::get<FieldIdx_Week>(allFields);
        auto expectedMode = comms::field::OptionalMode::Exists;
        if (weekField.value() == 0U) {
            expectedMode = comms::field::OptionalMode::Missing;
        }

        auto& dataField = std::get<FieldIdx_Data>(allFields);
        if (dataField.getMode() == expectedMode) {
            return false;
        }

        dataField.setMode(expectedMode);
        return true;
    }

};


}  // namespace message

}  // namespace ublox




