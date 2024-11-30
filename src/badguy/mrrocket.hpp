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

#ifndef HEADER_SUPERTUX_BADGUY_MRROCKET_HPP
#define HEADER_SUPERTUX_BADGUY_MRROCKET_HPP

#include "badguy/badguy.hpp"

/** Mr Rocket will fly in one direction until he hits something.
    On impact he is destroyed, trying to kill what he hit or hit him. */
class MrRocket : public BadGuy
{
public:
  MrRocket(const ReaderMapping& reader,
                   const std::string& sprite_name = "images/creatures/miscbadguys/mr_rocket/mr_rocket.sprite");

  virtual void initialize() override;
  virtual void collision_solid(const CollisionHit& hit) override;
  static std::string class_name() { return "mrrocket"; }
  virtual std::string get_class_name() const override { return class_name(); }
  static std::string display_name() { return _("Mr Rocket"); }
  virtual std::string get_display_name() const override { return display_name(); }
  virtual GameObjectClasses get_class_types() const override { return BadGuy::get_class_types().add(typeid(MrRocket)); }
  virtual bool is_snipable() const override { return true; }

protected:
  virtual bool collision_squished(GameObject& object) override;
  virtual HitResponse collision_player(Player& player, const CollisionHit& hit) override;
  virtual void kill_collision();

private:
  MrRocket(const MrRocket&) = delete;
  MrRocket& operator=(const MrRocket&) = delete;
};

#endif

/* EOF */
