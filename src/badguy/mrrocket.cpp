//  SuperTux
//  Copyright (C) 2008 Wolfgang Becker <uafr@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "badguy/mrrocket.hpp"

#include "audio/sound_manager.hpp"

namespace{
  static const float ROCKET_SPEED = 200;
  const std::string SPLAT_SOUND = "sounds/splat.wav";
}

MrRocket::MrRocket(const ReaderMapping& reader, const std::string& sprite_name) :
  BadGuy(reader, sprite_name)
{
  SoundManager::current()->preload(SPLAT_SOUND);
  set_action (m_dir, /* loops = */ -1);
}

void
MrRocket::initialize()
{
  m_physic.set_velocity_x(m_dir == Direction::LEFT ? -ROCKET_SPEED : ROCKET_SPEED);
  m_physic.enable_gravity(false);
  set_action(m_dir);
}

bool
MrRocket::collision_squished(GameObject& object)
{
  if (m_frozen)
    return BadGuy::collision_squished(object);
  set_action("squished", m_dir);
  kill_squished(object);
  return true;
}

void
MrRocket::collision_solid(const CollisionHit& hit)
{
  if (!m_frozen)
  {
    if (hit.top || hit.bottom) {
      m_physic.set_velocity_y(0);
    }
    if (hit.left || hit.right) {
      kill_collision();
    }
  }
  else
    BadGuy::collision_solid(hit);
}

void
MrRocket::kill_collision()
{
  set_action("collision", m_dir);
  SoundManager::current()->play(SPLAT_SOUND, get_pos());
  m_physic.set_velocity(0, 0);
  m_physic.enable_gravity(true);
  set_state(STATE_FALLING);

  run_dead_script();
}

HitResponse
MrRocket::collision_player(Player& player, const CollisionHit& hit)
{
  // Methodology to determine necessity of death.
  if (!m_frozen)
  {
    HitResponse response = BadGuy::collision_player(player, hit);
    if (response == FORCE_MOVE) {
      kill_collision();
    }
  }
  else
  {
    BadGuy::collision_player(player, hit);
    return FORCE_MOVE;
  }
  return ABORT_MOVE;
}

/* EOF */
