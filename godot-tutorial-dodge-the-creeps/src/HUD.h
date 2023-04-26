#pragma once

#include <Button.hpp>
#include <CanvasLayer.hpp>
#include <Godot.hpp>
#include <Label.hpp>
#include <Timer.hpp>

class HUD : public godot::CanvasLayer {
	GODOT_CLASS(HUD, godot::CanvasLayer)

	godot::Label *_score_label;
	godot::Label *_message_label;
	godot::Timer *_message_timer;
	// godot::Timer *_get_ready_message_timer;
	godot::Button *_start_button;
	// godot::Timer *_start_button_timer;

public:
	void _init() {}
	void _ready();
	void show_get_ready();
	void show_game_over();
	void update_score(const int score);
	void _on_StartButton_pressed();
	void _on_MessageTimer_timeout();
	// void _on_GetReadyMessageTimer_timeout();

	static void _register_methods();
};
