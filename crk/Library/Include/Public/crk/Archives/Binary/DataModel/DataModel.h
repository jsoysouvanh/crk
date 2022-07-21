/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t

#include "crk/Archives/Binary/FundamentalTypes/Formats/Integer/TwosComplementIntegerFormat.h"
#include "crk/Misc/GenericConcepts.h"

namespace crk
{
	/**
	*	@brief Struct defining the serialization encoding of fundamental types in an archive.
	*/
	//TODO: Add encoding/format as well
	template <ChildOf<IntegerFormat> IntegerFormat>
	struct DataModel
	{
		using UsedIntegerFormat = IntegerFormat;

		/**
		*	@brief Size in bits of a short (and by extension, an unsigned short).
		*/
		std::size_t	shortSize;

		/**
		*	@brief Size in bits of an int (and by extension, an unsigned int).
		*/
		std::size_t intSize;

		/**
		*	@brief Size in bits of a long (and by extension, an unsigned long).
		*/
		std::size_t	longSize;

		/**
		*	@brief Size in bits of a long long (and by extension, an unsigned long long).
		*/
		std::size_t longlongSize;
	};

	constexpr DataModel<TwosComplementIntegerFormat> LP32DataModel =
	{
		.shortSize		= 16u,
		.intSize		= 16u,
		.longSize		= 32u,
		.longlongSize	= 64u
	};

	//Equivalent to ILP32
	constexpr DataModel<TwosComplementIntegerFormat> LLP64DataModel =
	{
		.shortSize		= 16u,
		.intSize		= 32u,
		.longSize		= 32u,
		.longlongSize	= 64u
	};

	constexpr DataModel<TwosComplementIntegerFormat> LP64DataModel =
	{
		.shortSize		= 16u,
		.intSize		= 32u,
		.longSize		= 64u,
		.longlongSize	= 64u
	};
}