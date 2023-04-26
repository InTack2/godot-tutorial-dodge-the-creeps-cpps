﻿#pragma once

#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <RigidBody2D.hpp>

class Mob : public godot::RigidBody2D {
	GODOT_CLASS(Mob, godot::RigidBody2D)

	godot::AnimatedSprite *_animated_sprite;

public:
	void _init() {}
	void _ready();
	void _process(const double p_delta);
	void _on_VisibilityNotifier2D_screen_exited();

	static void _register_methods();
};
