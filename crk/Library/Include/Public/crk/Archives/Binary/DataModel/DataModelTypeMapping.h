/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <concepts>

#include "crk/Archives/Binary/DataModel/DataModel.h"
#include "crk/Archives/Binary/FundamentalTypes/IntegerTraits.h"
#include "crk/Misc/TypeTraits.h"

namespace crk
{
	template <DataModel DataModel>
	struct DataModelTypeMapping
	{
		template <IsInteger T>
		static auto getMappedType();

        //short
        template <IsInteger T>
        static auto getMappedType() -> IntegerType_t<DataModel.shortSize, std::is_same_v<T, unsigned short>>
            requires std::same_as<T, short> || std::same_as<T, unsigned short>;

        //int
        template <IsInteger T>
        static auto getMappedType() -> IntegerType_t<DataModel.intSize, std::is_same_v<T, unsigned int>>
            requires std::same_as<T, int> || std::same_as<T, unsigned int>;

        //long
        template <IsInteger T>
        static auto getMappedType() -> IntegerType_t<DataModel.longSize, std::is_same_v<T, unsigned long>>
            requires std::same_as<T, long> || std::same_as<T, unsigned long>;

        //long long
        template <IsInteger T>
        static auto getMappedType() -> IntegerType_t<DataModel.longlongSize, std::is_same_v<T, unsigned long long>>
            requires std::same_as<T, long long> || std::same_as<T, unsigned long long>;
	};
}