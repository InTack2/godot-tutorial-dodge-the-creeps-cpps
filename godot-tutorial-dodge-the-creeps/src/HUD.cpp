#include "HUD.h"


void HUD::_ready()
{
  _score_label = get_node<godot::Label>("ScoreLabel");
  _message_label = get_node<godot::Label>("Message");
  _message_timer = get_node<godot::Timer>("MessageTimer");
  // _get_ready_message_timer = get_node<godot::Timer>("GetReadyMessageTimer");
  _start_button = get_node<godot::Button>("StartButton");
  // _start_button_timer = get_node<godot::Timer>("StartButtonTimer");
}

void HUD::show_get_ready()
{
  _message_label->set_text("");
  _message_label->show();
  // _get_ready_message_timer->start();
}

void HUD::show_game_over()
{
  _message_label->set_text("Game Over");
  _message_label->show();
  _message_timer->start();
}

void HUD::update_score(const int score)
{
  // TODO: ここふつうにstring変換じゃだめ？
  _score_label->set_text(godot::Variant(score));
}

void HUD::_on_StartButton_pressed()
{
  // _start_button_timer->stop();
  _start_button->hide();
  emit_signal("start_game");
}

void HUD::_on_MessageTimer_timeout()
{
  _message_label->set_text("Doge the\nCreeps");
  _message_label->show();
  _start_button->show();

  // _message_label->hide();
}

// void HUD::_on_GetReadyMessageTimer_timeout()
// {
//   _message_label->hide();
// }


void HUD::_register_methods()
{
  godot::register_method("_ready", &HUD::_ready);
  godot::register_method("show_get_ready", &HUD::show_get_ready);
  godot::register_method("show_game_over", &HUD::show_game_over);
  godot::register_method("update_score", &HUD::update_score);
  godot::register_method("_on_StartButton_pressed", &HUD::_on_StartButton_pressed);
  godot::register_method("_on_MessageTimer_timeout", &HUD::_on_MessageTimer_timeout);
  // godot::register_method("_on_GetReadyMessageTimer_timeout", &HUD::_on_GetReadyMessageTimer_timeout);
  godot::register_signal<HUD>("start_game", godot::Dictionary());
}
