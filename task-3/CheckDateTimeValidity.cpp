#include <array>
#include <string>
#include <stdexcept>

using namespace std;

namespace detail {
    
void CheckDatePartInSegment(int value, int min, int max, const string &part_name) {
    if (value < min) {
        throw domain_error(part_name + " is too small"s);
    }
    if (value > max) {
        throw domain_error(part_name + " is too big"s);
    }
}

}

void CheckDateTimeValidity(const DateTime& dt) {
    using namespace detail;
    
    CheckDatePartInSegment(dt.year, 1, 9999, "year");
    CheckDatePartInSegment(dt.month, 1, 12, "month");

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array<int,12> month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    CheckDatePartInSegment(dt.day, 1, month_lengths[dt.month - 1], "day");

    CheckDatePartInSegment(dt.hour, 0, 23, "hour");
    CheckDatePartInSegment(dt.minute, 0, 59, "minute");
    CheckDatePartInSegment(dt.second, 0, 59, "second");
}

