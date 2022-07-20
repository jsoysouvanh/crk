/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the crk library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstdint>	//std::int8_t, std::int16_t...

namespace crk
{
	template <typename T>
	class ObjectWrapper
	{
		private:
			T _wrappedObject;

		public:
			using WrappedType = T;

			ObjectWrapper(T wrappedObject) noexcept:
				_wrappedObject{wrappedObject}
			{}

			operator T() const noexcept
			{
				return _wrappedObject;
			}
	};

	using int8 = ObjectWrapper<std::int8_t>;
	using uint8 = ObjectWrapper<std::uint8_t>;
	using int16 = ObjectWrapper<std::int16_t>;
	using uint16 = ObjectWrapper<std::uint16_t>;
	using int32 = ObjectWrapper<std::int32_t>;
	using uint32 = ObjectWrapper<std::uint32_t>;
	using int64 = ObjectWrapper<std::int64_t>;
	using uint64 = ObjectWrapper<std::uint64_t>;
}