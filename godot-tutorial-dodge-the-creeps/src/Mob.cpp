#include "Mob.h"

#include <RandomNumberGenerator.hpp>
#include <SpriteFrames.hpp>

void Mob::_ready()
{
  godot::Ref<godot::RandomNumberGenerator> random = godot::RandomNumberGenerator::_new();
  random->randomize();
  
  _animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
  _animated_sprite->set_playing(true);
  
  godot::PoolStringArray mob_types = _animated_sprite->get_sprite_frames()->get_animation_names();
  _animated_sprite->set_animation(mob_types[random->randi() % mob_types.size()]);
}

void Mob::_process(const double p_delta)
{

}

void Mob::_on_VisibilityNotifier2D_screen_exited()
{
  queue_free();
}

void Mob::_register_methods()
{
  godot::register_method("_ready", &Mob::_ready);
  godot::register_method("_process", &Mob::_process);
  // godot::register_method("start", &Player::start);
  godot::register_method("_on_VisibilityNotifier2D_screen_exited", &Mob::_on_VisibilityNotifier2D_screen_exited);
 
  // godot::register_property("speed", &Player::speed, static_cast<real_t>(400.0));
  // godot::register_signal<Player>("hit", godot::Dictionary());
}
