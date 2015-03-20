#include <gtest/gtest.h>
#include <nmea/rmc.hpp>
#include <nmea/nmea.hpp>

namespace
{

class Test_nmea_rmc : public ::testing::Test
{
};

TEST_F(Test_nmea_rmc, contruction)
{
	nmea::rmc rmc;
}

TEST_F(Test_nmea_rmc, size)
{
	EXPECT_EQ(168u, sizeof(nmea::rmc));
}

TEST_F(Test_nmea_rmc, parse)
{
	auto s = nmea::make_sentence("$GPRMC,,V,,,,,,,300510,0.6,E,N*39");
	ASSERT_NE(nullptr, s);

	auto rmc = nmea::sentence_cast<nmea::rmc>(s);
	ASSERT_NE(nullptr, rmc);

	auto date = rmc->get_date();
	EXPECT_TRUE(date.available());
	EXPECT_EQ(10u, date.value().year());
	EXPECT_EQ(5u, date.value().month());
	EXPECT_EQ(30u, date.value().day());
}

TEST_F(Test_nmea_rmc, empty_to_string)
{
	nmea::rmc rmc;

	EXPECT_STREQ("$GPRMC,,,,,,,,,,,,*4B", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, set_lat_north)
{
	nmea::rmc rmc;
	rmc.set_lat(nmea::latitude{12, 34, 56, nmea::latitude::hemisphere::NORTH});

	EXPECT_STREQ("$GPRMC,,,1234.9333,N,,,,,,,,*25", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, set_lat_south)
{
	nmea::rmc rmc;
	rmc.set_lat(nmea::latitude{12, 34, 56, nmea::latitude::hemisphere::SOUTH});

	EXPECT_STREQ("$GPRMC,,,1234.9333,S,,,,,,,,*38", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, set_lon_east)
{
	nmea::rmc rmc;
	rmc.set_lon(nmea::longitude{123, 45, 67, nmea::longitude::hemisphere::EAST});

	EXPECT_STREQ("$GPRMC,,,,,12346.1166,E,,,,,,*12", nmea::to_string(rmc).c_str());
}

TEST_F(Test_nmea_rmc, set_lon_west)
{
	nmea::rmc rmc;
	rmc.set_lon(nmea::longitude{123, 45, 67, nmea::longitude::hemisphere::WEST});

	EXPECT_STREQ("$GPRMC,,,,,12346.1166,W,,,,,,*00", nmea::to_string(rmc).c_str());
}

}


