#pragma once

#include <cstdint>
#include <concepts>

namespace util {
	using u8_t = std::uint8_t;

	// Basic int->float, float->int functions
	constexpr u8_t rgb_float_to_int(float channel) {
		return static_cast<u8_t>(channel * 255);
	}

	constexpr float rgb_int_to_float(u8_t channel) {
		return static_cast<float>(channel) / 255;
	}


	// Utility concept
	template <class T>
	concept UnsignedIntegral = std::is_integral<T>::value && !std::is_signed<T>::value;

	// RGB colors
	struct rgb_i8
	{
		u8_t r{};
		u8_t g{};
		u8_t b{};

		// Constructor for pretty much everything except floating
		template <UnsignedIntegral T>
		constexpr rgb_i8(
			T r_channel,
			T g_channel,
			T b_channel
		) :
			r{ static_cast<u8_t>(r_channel) },
			g{ static_cast<u8_t>(g_channel) },
			b{ static_cast<u8_t>(b_channel) }
		{}

		constexpr rgb_i8(
			float r_channel,
			float g_channel,
			float b_channel
		) :
			r{ rgb_float_to_int(r_channel) },
			g{ rgb_float_to_int(g_channel) },
			b{ rgb_float_to_int(b_channel) }
		{}
	};

	struct rgb_float
	{
		float r{};
		float g{};
		float b{};

		// Constructor for integers
		template <UnsignedIntegral T>
		constexpr rgb_float(
			T r_channel,
			T g_channel,
			T b_channel
		) :
			r{ rgb_int_to_float(static_cast<u8_t>(r_channel)) },
			g{ rgb_int_to_float(static_cast<u8_t>(g_channel)) },
			b{ rgb_int_to_float(static_cast<u8_t>(b_channel)) }
		{}

		constexpr rgb_float(float r_channel, float g_channel, float b_channel)
			: r{ r_channel }, g{ g_channel }, b{ b_channel }
		{}
	};
}
