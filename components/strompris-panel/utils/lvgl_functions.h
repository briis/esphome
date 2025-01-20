// LVGL FUNCTIONS - REUIRES LVGL TO BE LOADED IN ESPHOME
lv_color_t getColorFromValue(float value)
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
