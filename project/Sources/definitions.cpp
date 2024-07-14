#include "definitions.h"

const int   SCREEN_WIDTH = 1500;
const int   SCREEN_HEIGHT = 800;

const int   CELL_DIMENSION = 20;
const int   FIELD_WIDTH = 800;
const int   FIELD_HEIGHT = 700;

const int   FIELD_START_X = 650;
const int   FIELD_START_Y = 50;

const int   INITIAL_SNAKE_LENGTH = 3;

const int   MOVES_PER_SECOND = 5;
const int   MILLISECONDS_PER_MOVE = 1000 / MOVES_PER_SECOND;

const float MUTATION_RATE = 0.05f;

const int   HIDDEN_LAYERS = 2;
const int   HIDDEN_NODES = 16;
const bool  REPLY_BEST = false;
const bool  SEE_VISION = true;

const int   DECISION_SIZE = 4;
const int   VISION_SIZE = 24;