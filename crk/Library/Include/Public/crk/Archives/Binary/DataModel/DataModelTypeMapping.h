/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "crk/Archives/Binary/DataModel/DataModel.h"
#include "crk/Archives/Binary/FundamentalTypes/IntegerTraits.h"
#include "crk/Misc/GenericConcepts.h"
#include "crk/Misc/TypeConcepts.h"

namespace crk
{
	template <DataModel DataModel>
	struct DataModelTypeMapping
	{
		template <Integer T>
		static auto getMappedType();

        //short
        template <Integer T>
        static auto getMappedType() -> IntegerType_t<DataModel.shortSize, std::is_same_v<T, unsigned short>>
            requires SameAs<T, short> || SameAs<T, unsigned short>;

        //int
        template <Integer T>
        static auto getMappedType() -> IntegerType_t<DataModel.intSize, std::is_same_v<T, unsigned int>>
            requires SameAs<T, int> || SameAs<T, unsigned int>;

        //long
        template <Integer T>
        static auto getMappedType() -> IntegerType_t<DataModel.longSize, std::is_same_v<T, unsigned long>>
            requires SameAs<T, long> || SameAs<T, unsigned long>;

        //long long
        template <Integer T>
        static auto getMappedType() -> IntegerType_t<DataModel.longlongSize, std::is_same_v<T, unsigned long long>>
            requires SameAs<T, long long> || SameAs<T, unsigned long long>;
	};
}