#pragma once

typedef struct _win_st WINDOW;

enum class Color
{
    BLACK = 1,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    GOLD,
    SILVER,
    PINK,
    CRIMSON,
    APRICOT,
    YELLOW,
    ORANGE,
    CORAL,
    DARK_GREEN,
    DEEP_CHESTNUT,
    DESERT,
    ELECTRIC_LIME,
    DENIM,
    FLAX,
    FUZZY_WUZZY,
    BEIGE,
    AZURE,
    AMETHYST,
    COOL_GREY,
    COPPER,
    BRONZE,
    COSMIC_LATTE,
    FANDANGO,
    FLIRT,
    FRENCH_SKY_BLUE,
    FRENCH_RASPBERRY
};

static short r, g, b;

static short rgb2Debilno(short rgb)
{
    return 999 * ((float)rgb / 255);
}

extern bool initColors();

extern void activateColor(Color color, WINDOW* win);

extern void deactivateColor(Color color, WINDOW* win);
