#include "colors.h"
#include <ncurses.h>

bool initColors()
{
    if (!has_colors()) {
        //chatDebug("Terminal doesn't support color");
        return false;
    }

    use_default_colors();
    start_color();

    // Init default colors
    init_pair((short)Color::BLACK, COLOR_BLACK, -1);                                // Black
    init_pair((short)Color::BLUE, COLOR_BLUE, -1);                                  // Blue
    init_pair((short)Color::GREEN, COLOR_GREEN, -1);                                // Green
    init_pair((short)Color::CYAN, COLOR_CYAN, -1);                                  // Cyan
    init_pair((short)Color::RED, COLOR_RED, -1);                                    // Red
    init_pair((short)Color::MAGENTA, COLOR_MAGENTA, -1);                            // Magenta
    init_pair((short)Color::GOLD, COLOR_YELLOW, -1);                                // Yellow
    init_pair((short)Color::SILVER, COLOR_WHITE, -1);                               // White

    // Init custom colors
    if (can_change_color()) {
        init_color((short)Color::PINK, rgb2Debilno(255),
                                       rgb2Debilno(145),
                                       rgb2Debilno(175));
        init_pair((short)Color::PINK, (short)Color::PINK, -1);                      // Baker-Miller pink
        init_color((short)Color::CRIMSON, rgb2Debilno(158),
                                          rgb2Debilno(27),
                                          rgb2Debilno(50));
        init_pair((short)Color::CRIMSON, (short)Color::CRIMSON, -1);                // Crimson (UA)
        init_color((short)Color::APRICOT, rgb2Debilno(248),
                                          rgb2Debilno(184),
                                          rgb2Debilno(120));
        init_pair((short)Color::APRICOT, (short)Color::APRICOT, -1);                // Mellow Apricot
        init_color((short)Color::YELLOW, rgb2Debilno(255),
                                         rgb2Debilno(211),
                                         rgb2Debilno(0));
        init_pair((short)Color::YELLOW, (short)Color::YELLOW, -1);                  // Canary yellow
        init_color((short)Color::ORANGE, rgb2Debilno(237),
                                         rgb2Debilno(135),
                                         rgb2Debilno(45));
        init_pair((short)Color::ORANGE, (short)Color::ORANGE, -1);                  // Cadmium orange
        init_color((short)Color::CORAL, rgb2Debilno(240),
                                        rgb2Debilno(128),
                                        rgb2Debilno(128));
        init_pair((short)Color::CORAL, (short)Color::CORAL, -1);                    // Light coral pink
        init_color((short)Color::DARK_GREEN, rgb2Debilno(0),
                                             rgb2Debilno(100),
                                             rgb2Debilno(0));
        init_pair((short)Color::DARK_GREEN, (short)Color::DARK_GREEN, -1);          // Dark Green
        init_color((short)Color::DEEP_CHESTNUT, rgb2Debilno(185),
                                                rgb2Debilno(78),
                                                rgb2Debilno(72));
        init_pair((short)Color::DEEP_CHESTNUT, (short)Color::DEEP_CHESTNUT, -1);    // Deep chestnut
        init_color((short)Color::DESERT, rgb2Debilno(193),
                                         rgb2Debilno(154),
                                         rgb2Debilno(107));
        init_pair((short)Color::DESERT, (short)Color::DESERT, -1);                  // Desert
        init_color((short)Color::ELECTRIC_LIME, rgb2Debilno(158),
                                                rgb2Debilno(253),
                                                rgb2Debilno(56));
        init_pair((short)Color::ELECTRIC_LIME, (short)Color::ELECTRIC_LIME, -1);    // French lime
        init_color((short)Color::DENIM, rgb2Debilno(21),
                                        rgb2Debilno(96),
                                        rgb2Debilno(189));
        init_pair((short)Color::DENIM, (short)Color::DENIM, -1);                    // Denim
        init_color((short)Color::FLAX, rgb2Debilno(238),
                                       rgb2Debilno(220),
                                       rgb2Debilno(130));
        init_pair((short)Color::FLAX, (short)Color::FLAX, -1);                      // Flax
        init_color((short)Color::FUZZY_WUZZY, rgb2Debilno(135),
                                              rgb2Debilno(66),
                                              rgb2Debilno(31));
        init_pair((short)Color::FUZZY_WUZZY, (short)Color::FUZZY_WUZZY, -1);        // Fuzzy wuzzy
        init_color((short)Color::BEIGE, rgb2Debilno(245),
                                        rgb2Debilno(245),
                                        rgb2Debilno(220));
        init_pair((short)Color::BEIGE, (short)Color::BEIGE, -1);                    // Beige
        init_color((short)Color::AZURE, rgb2Debilno(0),
                                        rgb2Debilno(128),
                                        rgb2Debilno(255));
        init_pair((short)Color::AZURE, (short)Color::AZURE, -1);                    // Azure
        init_color((short)Color::AMETHYST, rgb2Debilno(153),
                                           rgb2Debilno(102),
                                           rgb2Debilno(204));
        init_pair((short)Color::AMETHYST, (short)Color::AMETHYST, -1);              // Amethyst
    }
    else {
        //chatDebug("Terminal doesn't support color change");
        return false;
    }

    return true;
}

void activateColor(Color color, WINDOW* win)
{
    if (color == Color::BLACK || color == Color::SILVER)
        wattron(win, A_BOLD);

    wattron(win, COLOR_PAIR((int)color));
}

void deactivateColor(Color color, WINDOW* win) {
    if (color == Color::BLACK || color == Color::SILVER)
        wattroff(win, A_BOLD);

    wattroff(win, COLOR_PAIR((int)color));
}