#include "game.hpp"

#include <cstdio>
#include <cstring>
#include "device.hpp"
#include "material.hpp"

using namespace std;

const char* DELIM = ", \t";

Game::Game(Device& dev, const string& mat_file, const string& map_file,
           const string& ch_file) {
  FILE* f;
  char buffer[1024];

  material mat;
  puts("Reading materials");
  f = fopen(mat_file.c_str(), "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", mat_file.c_str());
    exit(EXIT_FAILURE);
  }
  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    if (buffer[0] == '#') { // comment
      continue;
    }
    mat.name = strtok(buffer, DELIM);
    mat.image = dev.load_image(strtok(NULL, DELIM));
    mat.pos_x = atoi(strtok(NULL, DELIM));
    mat.pos_y = atoi(strtok(NULL, DELIM));
    mat.n_x = atoi(strtok(NULL, DELIM));
    mat.n_y = atoi(strtok(NULL, DELIM));
    mat.is_walkable = atoi(strtok(NULL, DELIM));
    materials.push_back(mat);
  }
  fclose(f);

  char* tok;
  puts("Reading map");
  f = fopen(map_file.c_str(), "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", map_file.c_str());
    exit(EXIT_FAILURE);
  }
  // read first row and determine number of columns
  fgets(buffer, sizeof(buffer), f);
  map.resize(1);
  tok = strtok(buffer, DELIM);
  while (tok != NULL) {
    map[0].push_back(atoi(tok));
    tok = strtok(NULL, DELIM);
  }

  // read rest of map, incomplete information will be filled with material 0
  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    map.resize(map.size() + 1);
    map.back().resize(map[0].size());
    tok = strtok(buffer, DELIM);
    for (size_t i = 0; i < map[0].size() && tok != NULL; ++i) {
      map.back()[i] = atoi(tok);
      tok = strtok(NULL, DELIM);
    }
  }
  fclose(f);

  puts("Reading characters");
  character ch;
  f = fopen(ch_file.c_str(), "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", ch_file.c_str());
    exit(EXIT_FAILURE);
  }
  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    if (buffer[0] == '#') { // comment
      continue;
    }
    ch.name = strtok(buffer, DELIM);
    ch.image = dev.load_image(strtok(NULL, DELIM));
    ch.is_playable = atoi(strtok(NULL, DELIM));
    ch.base_start = atof(strtok(NULL, DELIM));
    ch.base_size = atoi(strtok(NULL, DELIM));
    ch.pos.x = atoi(strtok(NULL, DELIM));
    ch.pos.y = atoi(strtok(NULL, DELIM));
    ch.stats.strength = atoi(strtok(NULL, DELIM));
    ch.stats.dexterity = atoi(strtok(NULL, DELIM));
    ch.stats.constitution = atoi(strtok(NULL, DELIM));
    ch.stats.intelligence = atoi(strtok(NULL, DELIM));
    ch.stats.wisdom = atoi(strtok(NULL, DELIM));
    ch.stats.charisma = atoi(strtok(NULL, DELIM));
    ch.move_limit = atoi(strtok(NULL, DELIM));
    characters.push_back(ch);
  }
  fclose(f);

  // populate turns
  turns.resize(characters.size());
  for (size_t i = 0; i < turns.size(); ++i) {
    turns[i] = i;
  }

  set_focus();
  move_limit = characters[turns[0]].move_limit;
}

void Game::set_focus() {
  focus_x = characters[turns[0]].pos.x;
  focus_y = characters[turns[0]].pos.y;
}

void Game::end_turn() {
  size_t temp = turns[0];
  memmove(&turns[0], &turns[1], (turns.size() - 1) * sizeof(turns[0]));
  turns.back() = temp;
  set_focus();
  move_limit = characters[turns[0]].move_limit;
}

void Game::move_up() {
  character& ch = characters[turns[0]];
  if (move_limit > 0 &&
      ch.pos.y > 0 &&
      materials[map[ch.pos.y-1][ch.pos.x]].is_walkable) {
    --move_limit;
    --ch.pos.y;
    set_focus();
  }
}

void Game::move_down() {
  character& ch = characters[turns[0]];
  if (move_limit > 0 &&
      ch.pos.y < int(map.size()) - 1 &&
      materials[map[ch.pos.y+1][ch.pos.x]].is_walkable) {
    --move_limit;
    ++ch.pos.y;
    set_focus();
  }
}

void Game::move_left() {
  character& ch = characters[turns[0]];
  if (move_limit > 0 &&
      ch.pos.x > 0 &&
      materials[map[ch.pos.y][ch.pos.x-1]].is_walkable) {
    --move_limit;
    --ch.pos.x;
    set_focus();
  }
}

void Game::move_right() {
  character& ch = characters[turns[0]];
  if (move_limit > 0 &&
      ch.pos.x < int(map[0].size()) - 1 &&
      materials[map[ch.pos.y][ch.pos.x+1]].is_walkable) {
    --move_limit;
    ++ch.pos.x;
    set_focus();
  }
}
