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
/// @brief Contains definition of NAV-PVT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-PVT message fields.
/// @see NavPvt
struct NavPvtFields
{
    /// @brief Value enumeration for @ref psmState field.
    enum class PsmState : std::uint8_t
    {
        Invalid, ///< invalid
        Enabled, ///< enabled
        Acquisition, ///< acquisition
        Tracking, ///< tracking
        PowerOptimisedTracking, ///< power optimised tracking
        Inactive, ///< inactive
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "year" field.
    using year = field::nav::year;

    /// @brief Definition of "month" field.
    using month = field::nav::month;

    /// @brief Definition of "day" field.
    using day = field::nav::day;

    /// @brief Definition of "hour" field.
    using hour = field::nav::hour;

    /// @brief Definition of "min" field.
    using min = field::nav::min;

    /// @brief Definition of "sec" field.
    using sec = field::nav::sec;

    /// @brief Definition of "valid" field.
    struct validBits : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(validDate, validTime, fullyResolved, validMag);
    };

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief Definition of "nano" field.
    using nano = field::nav::nano;

    /// @brief Definition of "fixType" field.
    using fixType = field::nav::gpsFix;

    /// @brief Definition of two first bits (@b gnssFixOn and @b diffSoln) in
    ///     @ref flags bitfield as separate bitmask member field.
    struct flagsLow : public
        field::common::X1T<comms::option::FixedBitLength<2> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(gnssFixOK, diffSoln);
    };

    /// @brief Definition of "psmState" member field in @ref flags bitmask field.
    using psmState =
        field::common::EnumT<
            PsmState,
            comms::option::FixedBitLength<3>,
            comms::option::ValidNumValueRange<0, (int)PsmState::NumOfValues - 1>
        >;

    /// @brief Definition of the bits in the "high" area of
    ///     @ref flags bitfield.
    struct headVehValid : public
        field::common::X1T<
            comms::option::FixedBitLength<1>,
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(bit);
    };

    /// @brief Value enumeration for @ref carrSoln field.
    using CarrSoln = field::nav::CarrSoln;

    /// @brief Definition of "carrSoln" member field in @ref flags bitmask field.
    using carrSoln = field::nav::carrSoln<comms::option::FixedBitLength<2> >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                flagsLow,
                psmState,
                headVehValid,
                carrSoln
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flagsLow, psmState, headVehValid, carrSoln);
    };

    /// @brief Definition of "flags2" field.
    struct flags2 : public
        field::common::X1T<comms::option::BitmaskReservedBits<0x1f, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(confirmedAvai=5, confirmedDate, confirmedTime);

        /// @brief Provide convenience access functions for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_ACCESS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_ACCESS(confirmedAvai, confirmedDate, confirmedTime);
    };


    /// @brief Definition of "numSV" field.
    using numSV = field::nav::numSV;

    /// @brief Definition of "lon" field.
    using lon = field::nav::lon;

    /// @brief Definition of "lat" field.
    using lat = field::nav::lat;

    /// @brief Definition of "height" field.
    using height = field::nav::height;

    /// @brief Definition of "hMSL" field.
    using hMSL = field::nav::hMSL;

    /// @brief Definition of "hAcc" field.
    using hAcc = field::nav::hAcc;

    /// @brief Definition of "vAcc" field.
    using vAcc = field::nav::vAcc;

    /// @brief Definition of "velN" field.
    using velN = field::common::I4T<comms::option::UnitsMillimetersPerSecond>;

    /// @brief Definition of "velE" field.
    using velE = velN;

    /// @brief Definition of "velD" field.
    using velD = velN;

    /// @brief Definition of "gSpeed" field.
    using gSpeed = field::common::I4T<comms::option::UnitsMillimetersPerSecond>;

    /// @brief Definition of "headMot" field.
    using headMot = field::nav::heading;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::common::U4T<comms::option::UnitsMillimetersPerSecond>;

    /// @brief Definition of "headAcc" field.
    using headAcc =
        field::common::U4T<
            comms::option::ScalingRatio<1, 100000>,
            comms::option::UnitsDegrees
        >;

    /// @brief Definition of "pDOP" field.
    using pDOP = field::nav::pDOP;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "headVeh" field.
    /// @details Defined as "optional" to allow usage with ublox-7 and earlier devices
    using headVeh =
        field::common::OptionalT<
            field::nav::heading,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "magDec" field.
    /// @details Defined as "optional" to allow usage with ublox-7 and earlier devices
    using magDec =
        field::common::OptionalT<
            field::common::I2T<
                comms::option::ScalingRatio<1, 100>,
                comms::option::UnitsDegrees
            >,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "magAcc" field.
    /// @details Defined as "optional" to allow usage with ublox-7 and earlier devices
    using magAcc =
        field::common::OptionalT<
            field::common::U2T<
                comms::option::ScalingRatio<1, 100>,
                comms::option::UnitsDegrees
            >,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        year,
        month,
        day,
        hour,
        min,
        sec,
        validBits,
        tAcc,
        nano,
        fixType,
        flags,
        flags2,
        numSV,
        lon,
        lat,
        height,
        hMSL,
        hAcc,
        vAcc,
        velN,
        velE,
        velD,
        gSpeed,
        headMot,
        sAcc,
        headAcc,
        pDOP,
        reserved1,
        reserved2,
        headVeh,
        magDec,
        magAcc
    >;
};

/// @brief Definition of NAV-PVT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavPvtFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavPvt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_PVT>,
        comms::option::FieldsImpl<NavPvtFields::All>,
        comms::option::MsgType<NavPvt<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavPvtFields::iTOW field
    ///     @li @b year for @ref NavPvtFields::year field
    ///     @li @b month for @ref NavPvtFields::month field
    ///     @li @b day for @ref NavPvtFields::day field
    ///     @li @b hour for @ref NavPvtFields::hour field
    ///     @li @b min for @ref NavPvtFields::min field
    ///     @li @b sec for @ref NavPvtFields::sec field
    ///     @li @b valid for @ref NavPvtFields::validBits field
    ///     @li @b tAcc for @ref NavPvtFields::tAcc field
    ///     @li @b nano for @ref NavPvtFields::nano field
    ///     @li @b fixType for @ref NavPvtFields::fixType field
    ///     @li @b flags for @ref NavPvtFields::flags field
    ///     @li @b flags2 for @ref NavPvtFields::flags2 field
    ///     @li @b numSV for @ref NavPvtFields::numSV field
    ///     @li @b lon for @ref NavPvtFields::lon field
    ///     @li @b lat for @ref NavPvtFields::lat field
    ///     @li @b height for @ref NavPvtFields::height field
    ///     @li @b hMSL for @ref NavPvtFields::hMSL field
    ///     @li @b hAcc for @ref NavPvtFields::hAcc field
    ///     @li @b vAcc for @ref NavPvtFields::vAcc field
    ///     @li @b velN for @ref NavPvtFields::velN field
    ///     @li @b velE for @ref NavPvtFields::velE field
    ///     @li @b velD for @ref NavPvtFields::velD field
    ///     @li @b gSpeed for @ref NavPvtFields::gSpeed field
    ///     @li @b headMot for @ref NavPvtFields::headMot field
    ///     @li @b sAcc for @ref NavPvtFields::sAcc field
    ///     @li @b headAcc for @ref NavPvtFields::headAcc field
    ///     @li @b pDOP for @ref NavPvtFields::pDOP field
    ///     @li @b reserved1 for @ref NavPvtFields::reserved1 field
    ///     @li @b reserved2 for @ref NavPvtFields::reserved2 field
    ///     @li @b headVeh for @ref NavPvtFields::headVeh field
    ///     @li @b magDec for @ref NavPvtFields::magDec field
    ///     @li @b magAcc for @ref NavPvtFields::magAcc field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        year,
        month,
        day,
        hour,
        min,
        sec,
        valid,
        tAcc,
        nano,
        fixType,
        flags,
        flags2,
        numSV,
        lon,
        lat,
        height,
        hMSL,
        hAcc,
        vAcc,
        velN,
        velE,
        velD,
        gSpeed,
        headMot,
        sAcc,
        headAcc,
        pDOP,
        reserved1,
        reserved2,
        headVeh,
        magDec,
        magAcc
    );

    /// @brief Default constructor
    NavPvt() = default;

    /// @brief Copy constructor
    NavPvt(const NavPvt&) = default;

    /// @brief Move constructor
    NavPvt(NavPvt&& other) = default;

    /// @brief Destructor
    ~NavPvt() = default;

    /// @brief Copy assignment
    NavPvt& operator=(const NavPvt&) = default;

    /// @brief Move assignment
    NavPvt& operator=(NavPvt&&) = default;

    /// @brief Provides custom read functionality.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::template readFieldsUntil<FieldIdx_headVeh>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        static const auto ReqLen =
            NavPvtFields::headVeh::Field::maxLength() +
            NavPvtFields::magDec::Field::maxLength() +
            NavPvtFields::magAcc::Field::maxLength();

        if (len < ReqLen) {
            field_headVeh().setMissing();
            field_magDec().setMissing();
            field_magAcc().setMissing();
            return es;
        }

        field_headVeh().setExists();
        field_magDec().setExists();
        field_magAcc().setExists();

        return Base::template readFieldsFrom<FieldIdx_headVeh>(iter, len);
    }

    bool doValid() const
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        if (!Base::doValid()) {
            return false;
        }

        // 3 last fields must have the same mode
        auto mode = field_headVeh().getMode();
        return
            (field_magDec().getMode() == mode) &&
            (field_magAcc().getMode() == mode);
    }

};


}  // namespace message

}  // namespace ublox





