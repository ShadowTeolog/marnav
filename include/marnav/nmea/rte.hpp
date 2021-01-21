#ifndef MARNAV_NMEA_RTE_HPP
#define MARNAV_NMEA_RTE_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief RTE - Routes
///
/// @code
///        1 2 3 4 5    6           x
///        | | | | |    |           |
/// $--RTE,x,x,a,x,c--c,c--c, ..... c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Total number of messages being transmitted
/// 2. Message Number
/// 3. Message mode c = complete route, all waypoints w = working route, the waypoint
///    you just left, the waypoint you’re heading to, then all the rest
/// 4. Route ID
/// 5+. Waypoint ID
///
/// More waypoints follow. Last field is a checksum as usual.
///
/// The Garmin 65 and possibly other units report a <tt>$GPR00</tt> in the same format.
///
class rte : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::RTE;
	constexpr static const char * TAG = "RTE";

	constexpr static int max_waypoints = 10;

	rte();
	rte(const rte &) = default;
	rte & operator=(const rte &) = default;
	rte(rte &&) = default;
	rte & operator=(rte &&) = default;

protected:
	rte(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	uint32_t n_messages_ = 1;
	uint32_t message_number_ = 1;
	route message_mode_ = route::complete; // C:complete route, W:working route
	uint32_t route_id_ = 99;
	utils::optional<waypoint>waypoint_id_[max_waypoints]; // names or numbers of the active route

public:
	uint32_t get_n_messages() const { return n_messages_; }
	uint32_t get_message_number() const { return message_number_; }
	route get_message_mode() const { return message_mode_; }
	decltype(route_id_) get_route_id() const { return route_id_; }
	utils::optional<waypoint> get_waypoint_id(int index) const;

	void set_n_messages(uint32_t t) noexcept { n_messages_ = t; }
	void set_message_number(uint32_t t) noexcept { message_number_ = t; }
	void set_message_mode(route t) noexcept { message_mode_ = t; }
	void set_route_id(const uint32_t & t) { route_id_ = t; }
	void set_waypoint_id(int index, const waypoint & id);
};
}
}

#endif
