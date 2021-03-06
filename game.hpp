#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "character.hpp"
#include "material.hpp"

class Device;

class Game {
public:
  int focus_x;
  int focus_y;
  int move_limit;
  int diag_moves;
  std::vector<material> materials;
  std::vector<std::vector<size_t> > map;
  std::vector<character> characters;
  std::vector<size_t> turns;
  std::vector<character> enemies;

  Game(Device& dev, const std::string& mat_file, const std::string& map_file,
       const std::string& ch_file, const std::string& en_file);
  void load_map(const std::string& file);
  character generate_enemy(size_t enemy_idx, int x, int y);
  size_t create_enemy(size_t enemy_idx, int x, int y);
  void delete_character(size_t idx);
  bool is_tile_occupied(int x, int y);
  void set_focus();
  void end_turn();
  bool can_move(int dx, int dy, bool obstacles = true);
  bool move(int dx, int dy);
  std::vector<size_t> attack_range();
  void attack(size_t i);
};

#endif // GAME_HPP
