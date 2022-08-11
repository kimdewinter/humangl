#include "env.h"

InputHandler::InputHandler()
{
	this->keys = {
		new Unrepeatable(GLFW_KEY_ESCAPE, [&]()
						 { glfwSetWindowShouldClose(this->window, true); }),
		new Unrepeatable(GLFW_KEY_SPACE, [&]()
						 { this->world->select(); }),
		// Keypresses that change translation
		new Repeatable(GLFW_KEY_Q, [&]()
					   { this->world->get_selected()->modify_position({0.0, -MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_W, [&]()
					   { this->world->get_selected()->modify_position({0.0, 0.0, -MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_E, [&]()
					   { this->world->get_selected()->modify_position({0.0, MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_A, [&]()
					   { this->world->get_selected()->modify_position({-MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_S, [&]()
					   { this->world->get_selected()->modify_position({0.0, 0.0, MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_D, [&]()
					   { this->world->get_selected()->modify_position({MOVEMENT_SPEED, 0.0, 0.0}); }),
		// Keypresses that change orientation
		new Repeatable(GLFW_KEY_R, [&]()
					   { this->world->get_selected()->modify_orientation({0.0, 0.0, MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_T, [&]()
					   { this->world->get_selected()->modify_orientation({-MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_Y, [&]()
					   { this->world->get_selected()->modify_orientation({0.0, 0.0, -MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_F, [&]()
					   { this->world->get_selected()->modify_orientation({0.0, -MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_G, [&]()
					   { this->world->get_selected()->modify_orientation({MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_H, [&]()
					   { this->world->get_selected()->modify_orientation({0.0, MOVEMENT_SPEED, 0.0}); }),
		// Keypresses that change scale
		new Repeatable(GLFW_KEY_U, [&]()
					   { this->world->get_selected()->modify_scale({0.0, -MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_I, [&]()
					   { this->world->get_selected()->modify_scale({0.0, 0.0, MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_O, [&]()
					   { this->world->get_selected()->modify_scale({0.0, MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_J, [&]()
					   { this->world->get_selected()->modify_scale({-MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_K, [&]()
					   { this->world->get_selected()->modify_scale({0.0, 0.0, -MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_L, [&]()
					   { this->world->get_selected()->modify_scale({MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_C, [&]()
					   {
						std::shared_ptr<Model> model = this->world->get_selected();
						model->reset_position();
						model->reset_orientation();
						model->reset_scale();
						model->reset_color(); }),
#if DEBUG_MODELS == 1
		new Unrepeatable(GLFW_KEY_ENTER, [&]()
						 {
							std::shared_ptr<Model> model = world->get_selected();
							 if (model)
								 model->debug_model_data(); }),
#endif
	};
}

InputHandler::~InputHandler()
{
	for (auto key : this->keys)
		delete key;
}

void InputHandler::handle_input(GLFWwindow *window, World *world)
{
	this->window = window;
	this->world = world;

	for (auto key : this->keys)
		key->handle_input(window);

	this->window = NULL;
	this->world = NULL;
}

bool InputHandler::Key::is_currently_pressed(GLFWwindow *window) const
{
	return glfwGetKey(window, this->key) == GLFW_PRESS;
}

void InputHandler::Repeatable::handle_input(GLFWwindow *window)
{
	if (this->is_currently_pressed(window))
		this->action();
}

void InputHandler::Unrepeatable::handle_input(GLFWwindow *window)
{
	if (is_currently_pressed(window))
	{
		if (!this->previously_pressed)
		{
			this->action();
			this->previously_pressed = true;
		}
	}
	else
	{
		this->previously_pressed = false;
	}
}
