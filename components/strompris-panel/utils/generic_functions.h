// GENERIC FUNCTIONS

void setUTCTimezone() {
#ifdef _WIN32
    _putenv("TZ=UTC");
#else
    setenv("TZ", "UTC", 1);
#endif
    tzset();
}

std::string formatFloat1dec(const float &value) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%.1f", value);
    return std::string(buffer);
}

std::string formatFloat2dec(const float &value) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%.2f", value);
    return std::string(buffer);
}

std::string formatHighLowTime(const int &value) {
    std::string time = std::to_string(value);
    if (time.length() == 1) {
        time = "0" + time;
    }
    std::string timeTo = std::to_string(value + 1);
    if (value == 23) {
        timeTo = "00";
    }
    if (timeTo.length() == 1) {
        timeTo = "0" + timeTo;
    }
    return time + " - " + timeTo;
}

std::string getCurrentHourStart()
{
    std::time_t now = std::time(nullptr);
    std::tm tm = *std::gmtime(&now);  // Use gmtime directly
    tm.tm_min = 0;
    tm.tm_sec = 0;
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.000Z", &tm);  // Format directly from tm structure
    return std::string(buffer);
}

std::string getTomorrowCurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::tm tm = *std::gmtime(&now);  // Use gmtime directly
    tm.tm_mday += 1;  // Add one day
    tm.tm_min = 0;
    tm.tm_sec = 0;
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.000Z", &tm);  // Format directly from tm structure
    return std::string(buffer);
}

std::string padIntWithZero(const int &value) {
    std::string result = std::to_string(value);
    if (result.length() == 1) {
        result = "0" + result;
    }
    return result;
}

std::string datetimeToDkMonth(const esphome::ESPTime &datetime)
{
    const char *danishMonths[] = {"januar", "februar", "marts", "april", "maj", "juni", "juli", "august", "september", "oktober", "november", "december"};
    char buffer[50];
    std::tm tm = *std::localtime(&datetime.timestamp);
    std::strftime(buffer, sizeof(buffer), "%d. ", &tm);
    std::string formattedDate(buffer);
    formattedDate += danishMonths[tm.tm_mon];
    std::strftime(buffer, sizeof(buffer), " %Y", &tm);
    formattedDate += buffer;
    return formattedDate;
}
std::string datetimeToDkDay(const esphome::ESPTime &datetime)
{
    const char *danishDays[] = {"søndag", "mandag", "tirsdag", "onsdag", "torsdag", "fredag", "lørdag"};
    std::tm tm = *std::localtime(&datetime.timestamp);
    return danishDays[tm.tm_wday];
}
std::string datetimeToDkText(const esphome::ESPTime &datetime)
{
    const char *danishDays[] = {"Søndag", "Mandag", "Tirsdag", "Onsdag", "Torsdag", "Fredag", "Lørdag"};
    const char *danishMonths[] = {"januar", "februar", "marts", "april", "maj", "juni", "juli", "august", "september", "oktober", "november", "december"};
    std::tm tm = *std::localtime(&datetime.timestamp);
    char buffer[50];
    std::string formattedDate = danishDays[tm.tm_wday];
    formattedDate += " den ";
    std::strftime(buffer, sizeof(buffer), "%d. ", &tm);
    formattedDate += buffer;
    formattedDate += danishMonths[tm.tm_mon];
    std::strftime(buffer, sizeof(buffer), " %Y", &tm);
    formattedDate += buffer;
    return formattedDate;
}