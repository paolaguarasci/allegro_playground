
const int SCREEN_W = 800;
const int SCREEN_H = 608;
const float FPS = 60.00;
const std::string TITLE = "Super Mario Brok(en)";
const std::string TITLE_line01 = "Super Mario";
const std::string TITLE_line02 = "Brok(en)";

// PG //
const int PASSO = 2;
const int PASSO_RUN = 15;

// MAP //
const int offset_top = 0;
const int MAP_W = 25;
const int MAP_H = 19;
const int BLOCK_SIZE = 32;
const int tiled[MAP_W][MAP_H] = { // farlo meglio!
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};