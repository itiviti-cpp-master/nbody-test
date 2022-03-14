#include <gtest/gtest.h>
#include <cmath>
#include <memory>
#include "nbody.h"

template <typename T>
class TrackerTest : public ::testing::Test {
    private:
        const double deviation_percentage = 0.05;
    public:
        void load_data(const std::string fn) {
            m_tracker = std::make_unique<T> (fn);
        }

        bool check(const Cartesian & val, const Cartesian & reference) {
            auto dx = val.x - reference.x;
            auto dy = val.y - reference.y;
            auto dist = std::sqrt(dx * dx + dy * dy);
            auto n = std::sqrt(reference.x * reference.x + reference.y * reference.y);
            return dist / n < deviation_percentage;
        }

        std::unique_ptr<T> m_tracker;
};

using TestTypes = ::testing::Types<BasicPositionTracker, FastPositionTracker>;
TYPED_TEST_SUITE(TrackerTest, TestTypes);

TYPED_TEST(TrackerTest, EarthPosition)
{
    this->load_data("test/etc/planets.txt");

    Track t = this->m_tracker->track("Earth", 1000, 1);
    ASSERT_TRUE(this->check(t.back(), {1.49601e+11, 2.98e+07}));
}

TYPED_TEST(TrackerTest, SunPosition)
{
    this->load_data("test/etc/planets.txt");

    Track t = this->m_tracker->track("Sun", 1000, 1);
    ASSERT_TRUE(this->check(t.back(), {-8.84959, -0.000753247}));
}

TYPED_TEST(TrackerTest, VenusPosition)
{
    this->load_data("test/etc/planets.txt");

    Track t = this->m_tracker->track("Venus", 1000, 1);
    ASSERT_TRUE(this->check(t.back(), {1.08202e+11, 3.50002e+07}));
}

TYPED_TEST(TrackerTest, EarthPosition2)
{
    this->load_data("test/etc/planets2.txt");

    Track t = this->m_tracker->track("Earth", 1000, 1);
    ASSERT_TRUE(this->check(t.back(), {-6.30704e+10, -5.67287e+08}));
}

TYPED_TEST(TrackerTest, VenusPosition2)
{
    this->load_data("test/etc/planets2.txt");

    Track t = this->m_tracker->track("Venus", 1000, 1);
    ASSERT_TRUE(this->check(t.back(), {5.67287e+08, -6.30704e+10}));
}
