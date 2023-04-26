#include "player.hpp"

#include <SceneTree.hpp>

void Player::_ready() {
  _animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
  _collision_shape = get_node<godot::CollisionShape2D>("CollisionShape2D");
  _input = godot::Input::get_singleton();
  _screen_size = get_viewport_rect().size;

  hide();
}

/**
 * \brief UnityでいうUpdate関数
 * \param p_delta おそらくdelta timeのこと
 */
void Player::_process(const double p_delta) { 
  godot::Vector2 velocity(0, 0);


  velocity.x = _input->get_action_strength("move_right") - _input->get_action_strength("move_left");
  velocity.y = _input->get_action_strength("move_down") - _input->get_action_strength("move_up");

  if (velocity.length() > 0) {
    velocity = velocity.normalized() * speed;
    _animated_sprite->play();
  } else {
    _animated_sprite->stop();
  }
    
  godot::Vector2 position = get_position();
  position += velocity * static_cast<real_t>(p_delta);
  position.x = godot::Math::clamp(position.x, static_cast<real_t>(0.0), _screen_size.x);
  position.y = godot::Math::clamp(position.y, static_cast<real_t>(0.0), _screen_size.y);
  set_position(position);

  if (velocity.x != 0) {
      _animated_sprite->set_animation("walk");
      _animated_sprite->set_flip_v(false);
      // See the note below about boolean assignment.
      _animated_sprite->set_flip_h(velocity.x < 0);
  }
  else if (velocity.y != 0) {
      _animated_sprite->set_animation("up");
      _animated_sprite->set_flip_v(velocity.y > 0);
  }

  if (_input->get_action_strength("exit"))
  {
    exit_game();
  }
}

void Player::_on_Player_body_entered(godot::Node2D* _body)
{
  hide();
  emit_signal("hit");

  // 一回のみ
  _collision_shape->set_deferred("disabled", true);
}



/**
 * \brief ゲームを終了する
 */
void Player::exit_game() const
{
  godot::Node::get_tree()->quit();
}

void Player::start(const godot::Vector2 p_position)
{
  set_position(p_position);
  show();
  // TODO: ここのset_disabled意味わからないかも
  _collision_shape->set_disabled(false);
}

/**
 * \brief 登録関数。この関数経由でGodotへ登録
 */
void Player::_register_methods() {
  godot::register_method("_ready", &Player::_ready);
  godot::register_method("_process", &Player::_process);
  godot::register_method("start", &Player::start);
  godot::register_method("_on_Player_body_entered", &Player::_on_Player_body_entered);
  godot::register_property("speed", &Player::speed, static_cast<real_t>(400.0));
  godot::register_signal<Player>("hit", godot::Dictionary());
}
