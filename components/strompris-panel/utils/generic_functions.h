// GENERIC FUNCTIONS
std::string formatFloat2d(const float &value) {
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

std::string getReportStart()
{
    std::time_t now = std::time(nullptr);
    std::tm tm = *std::gmtime(&now);
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    std::time_t startOfDay = std::mktime(&tm);
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.000Z", std::gmtime(&startOfDay));
    return std::string(buffer);
}
std::string getReportEnd()
{
    std::time_t now = std::time(nullptr);
    std::tm tm = *std::gmtime(&now);
    tm.tm_hour = 23;
    tm.tm_min = 59;
    tm.tm_sec = 59;
    tm.tm_mday += 1;  // Add one day
    std::time_t endOfTomorrow = std::mktime(&tm);
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.999Z", std::gmtime(&endOfTomorrow));
    return std::string(buffer);
}

int getDaylightSavingOffset() {
    std::time_t now = std::time(nullptr);
    std::tm local = *std::localtime(&now);
    return local.tm_isdst > 0 ? 3600 : 0;
}
std::string getCurrentHourStart()
{
    std::time_t now = std::time(nullptr);
    std::tm local = *std::localtime(&now);  // Get local time
    std::tm utc = *std::gmtime(&now);  // Get UTC time
    local.tm_min = 0;
    local.tm_sec = 0;
    std::time_t startOfHour = std::mktime(&local);  // Convert back to time_t in local time
    std::time_t utcStartOfHour = startOfHour - (std::mktime(&local) - std::mktime(&utc));  // Calculate offset
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.000Z", std::gmtime(&utcStartOfHour));
    return std::string(buffer);
}
std::string getTomorrowCurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::tm local = *std::localtime(&now);  // Get local time
    std::tm utc = *std::gmtime(&now);  // Get UTC time
    local.tm_mday += 1;  // Add one day
    std::time_t tomorrow = std::mktime(&local);  // Convert back to time_t in local time
    std::time_t utcTomorrow = tomorrow - (std::mktime(&local) - std::mktime(&utc));  // Calculate offset
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.000Z", std::gmtime(&utcTomorrow));
    return std::string(buffer);
}


