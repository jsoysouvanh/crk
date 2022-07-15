/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t

namespace crk
{
	//TODO: Add encoding/format as well
	//template <IntegerFormat, FloatFormat, DoubleFormat, LongDoubleFormat>
	struct DataModel
	{
		/**
		*	@brief Size in bytes of a short.
		*/
		std::size_t	shortSize;

		/**
		*	@brief Size in bytes of an int.
		*/
		std::size_t intSize;

		/**
		*	@brief Size in bytes of a long.
		*/
		std::size_t	longSize;

		/**
		*	@brief Size in bytes of a long long.
		*/
		std::size_t longlongSize;
	};

	constexpr DataModel LP32DataModel =
	{
		.shortSize		= 2u,
		.intSize		= 2u,
		.longSize		= 4u,
		.longlongSize	= 8u
	};

	//Equivalent to ILP32
	constexpr DataModel LLP64DataModel =
	{
		.shortSize		= 2u,
		.intSize		= 4u,
		.longSize		= 4u,
		.longlongSize	= 8u
	};

	constexpr DataModel LP64DataModel =
	{
		.shortSize		= 2u,
		.intSize		= 4u,
		.longSize		= 8u,
		.longlongSize	= 8u
	};
}