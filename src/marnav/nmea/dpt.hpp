#ifndef MARNAV__NMEA__DPT__HPP
#define MARNAV__NMEA__DPT__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief DPT - Depth of Water
///
/// Water depth relative to the transducer and offset of the measuring transducer.
///
/// @code
///        1   2   3
///        |   |   |
/// $--DPT,x.x,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Depth meters
/// 2. Offset from transducer
///    - positive value means distance from tansducer to water line
///    - negative value means distance from transducer to keel
/// 3. Max depth in meters, might be empty. This field exists allegedly since NMEA 3.0
///
class dpt : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::DPT;
	constexpr static const char * TAG = "DPT";

	dpt();
	dpt(talker talk);
	dpt(const dpt &) = default;
	dpt & operator=(const dpt &) = default;
	dpt(dpt &&) = default;
	dpt & operator=(dpt &&) = default;

protected:
	dpt(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	double depth_meter = 0.0;
	double transducer_offset = 0.0;
	utils::optional<double> max_depth;

public:
	decltype(depth_meter) get_depth_meter() const noexcept { return depth_meter; }
	decltype(transducer_offset) get_transducer_offset() const noexcept
	{
		return transducer_offset;
	}
	decltype(max_depth) get_max_depth() const noexcept { return max_depth; }

	void set_depth_meter(double t) noexcept { depth_meter = t; }
	void set_transducer_offset(double t) noexcept { transducer_offset = t; }
	void set_max_depth(double t) noexcept { max_depth = t; }
};
}
}

#endif
