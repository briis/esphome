class StromPrisUtils : public Component
{
public:
    void setup() override
    {
        // This will be called by ESPHome when the component is set up
    }
    static float adjustHour(int hour);
    static std::string datetimeToDanishString(const esphome::ESPTime &datetime);
    static int extractAndAdjustHour(const std::string &dateTime);
    static std::array<std::string, 2> findHighestValueIndex(const std::vector<std::string> &dataPoints);
    static std::array<std::string, 2> findLowestValueIndex(const std::vector<std::string> &dataPoints);
    static std::string formatFloat(const std::string &value);
    static std::string formatFloat2d(const float &value);
    static lv_color_t getColorFromValue(float value);
    static std::string getReportStart();
    static bool isArrayNotEmpty(const std::vector<std::string> &array);
};

std::string StromPrisUtils::getReportStart()
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

int StromPrisUtils::extractAndAdjustHour(const std::string &dateTime)
{
    // Extract the hour part from the dateTime string
    int hour = std::stoi(dateTime.substr(11, 2));

    // Adjust the hour
    if (hour == 23)
    {
        hour = 0;
    }
    else
    {
        hour += 1;
    }

    return hour;
}
float StromPrisUtils::adjustHour(int hour)
{
    // Adjust the hour
    if (hour == 23)
    {
        hour = 0;
    }
    else
    {
        hour += 1;
    }

    return hour;
}

std::array<std::string, 2> StromPrisUtils::findLowestValueIndex(const std::vector<std::string> &dataPoints)
{
    int minIndex = -1;
    double minValue = std::numeric_limits<double>::max();

    for (size_t i = 0; i < dataPoints.size(); ++i)
    {
        double value = std::stod(dataPoints[i]);
        if (value != 0 && value < minValue)
        {
            minValue = value;
            minIndex = i;
        }
    }

    if (minIndex == -1)
    {
        return {"No valid data", "No valid data"};
    }

    std::string minIndexStr = std::to_string(minIndex);
    if (minIndexStr.length() == 1)
    {
        minIndexStr = "0" + minIndexStr;
    }

    int minToIndex = minIndex + 1;
    std::string minToIndexStr = std::to_string(minToIndex);
    if (minToIndex > 23)
    {
        minToIndexStr = "00";
    }
    if (minToIndexStr.length() == 1)
    {
        minToIndexStr = "0" + minToIndexStr;
    }
    return {minIndexStr + " - " + minToIndexStr, std::to_string(minValue)};
}

std::array<std::string, 2> StromPrisUtils::findHighestValueIndex(const std::vector<std::string> &dataPoints)
{
    int maxIndex = -1;
    double maxValue = std::numeric_limits<double>::lowest();

    for (size_t i = 0; i < dataPoints.size(); ++i)
    {
        double value = std::stod(dataPoints[i]);
        if (value != 0 && value > maxValue)
        {
            maxValue = value;
            maxIndex = i;
        }
    }

    if (maxIndex == -1)
    {
        return {"No valid data", "No valid data"};
    }

    std::string maxIndexStr = std::to_string(maxIndex);
    if (maxIndexStr.length() == 1)
    {
        maxIndexStr = "0" + maxIndexStr;
    }

    int maxToIndex = maxIndex + 1;

    std::string maxToIndexStr = std::to_string(maxToIndex);
    if (maxToIndex > 23)
    {
        maxToIndexStr = "00";
    }
    if (maxToIndexStr.length() == 1)
    {
        maxToIndexStr = "0" + maxToIndexStr;
    }
    return {maxIndexStr + " - " + maxToIndexStr, std::to_string(maxValue)};
}

bool StromPrisUtils::isArrayNotEmpty(const std::vector<std::string> &array)
{
    return !array.empty();
}

std::string StromPrisUtils::datetimeToDanishString(const esphome::ESPTime &datetime)
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

lv_color_t StromPrisUtils::getColorFromValue(float value)
{
    if (value < 2.0)
    {
        return lv_color_make(76, 175, 80); // Green
    }
    else if (value >= 2.0 && value < 3)
    {
        return lv_color_make(255, 193, 8); // Amber
    }
    else if (value >= 3 && value < 4)
    {
        return lv_color_make(255, 87, 33); // Orange
    }
    else if (value >= 4 && value < 5)
    {
        return lv_color_make(245, 67, 54); // Red
    }
    else
    {
        return lv_color_make(156, 39, 176); // Purple
    }
}

// These functions below are only necessary as the current ESPHome LVGL implementation
// does not support formatting a floating point number with a fixed number of decimals
std::string StromPrisUtils::formatFloat(const std::string &value) {
    float f = std::stof(value);
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%.1f", f);
    return std::string(buffer);
}

std::string StromPrisUtils::formatFloat2d(const float &value) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%.2f", value);
    return std::string(buffer);
}