#include "Main.h"

#include <SceneTree.hpp>

#include "Mob.h"


void Main::_ready()
{
	_hud = get_node<HUD>("HUD");
	_player = get_node<Player>("Player");
	_start_position = get_node<godot::Node2D>("StartPosition");
	_mob_spawn_location = get_node<godot::PathFollow2D>("MobPath/MobSpawnLocation");
	_mob_timer = get_node<godot::Timer>("MobTimer");
	_score_timer = get_node<godot::Timer>("ScoreTimer");
	_start_timer = get_node<godot::Timer>("StartTimer");

	_music = get_node<godot::AudioStreamPlayer>("Music");
	_death_sound = get_node<godot::AudioStreamPlayer>("DeathSound");
	_random = static_cast<godot::Ref<godot::RandomNumberGenerator>>(godot::RandomNumberGenerator::_new());
	_random->randomize();

	// new_game();
}

void Main::game_over()
{
	_score_timer->stop();
	_mob_timer->stop();

	_hud->show_game_over();

	// Mobを削除する
	get_tree()->call_group("mobs", "queue_free");
	_music->stop();
	_death_sound->play();
}

void Main::new_game()
{
	score = 0;
	_player->start(_start_position->get_position());
	_start_timer->start();

	_hud->update_score(score);
	_hud->show_get_ready();

	_music->play();
}

void Main::_on_MobTimer_timeout()
{
	godot::Node *mob = mob_scene->instance();

	_mob_spawn_location->set_offset(static_cast<real_t>(_random->randi()));

	real_t direction = _mob_spawn_location->get_rotation() + static_cast<real_t>(Math_PI) / 2;

	mob->set("position", _mob_spawn_location->get_position());

	// TODO: デバッグ使って確認する
	direction += _random->randf_range(static_cast<real_t>(-Math_PI) / 4, static_cast<real_t>(Math_PI) / 4);
	mob->set("rotation", direction);

	godot::Vector2 velocity = godot::Vector2(_random->randf_range(150.0, 250.0), 0.0);
	mob->set("linear_velocity", velocity.rotated(direction));

	add_child(mob);
}

void Main::_on_ScoreTimer_timeout()
{
	score += 1;
	_hud->update_score(score);
}

void Main::_on_StartTimer_timeout()
{
	_mob_timer->start();
	_score_timer->start();
}


void Main::_register_methods()
{
	godot::register_method("_ready", &Main::_ready);
	godot::register_method("game_over", &Main::game_over);
	godot::register_method("new_game", &Main::new_game);
	godot::register_method("_on_MobTimer_timeout", &Main::_on_MobTimer_timeout);
	godot::register_method("_on_ScoreTimer_timeout", &Main::_on_ScoreTimer_timeout);
	godot::register_method("_on_StartTimer_timeout", &Main::_on_StartTimer_timeout);
	
	// TODO: ここ複雑。
	godot::register_property("mob_scene", &Main::mob_scene, static_cast<godot::Ref<godot::PackedScene>>(nullptr));

	// 一旦tutorialここまで！！
	// https://docs.godotengine.org/ja/stable/getting_started/first_2d_game/05.the_main_game_scene.html
}
