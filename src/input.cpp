#include "env.h"

// Constructor which sets up all the possible hotkeys
InputHandler::InputHandler()
{
	this->keys = {
		// Keypress to end proram
		new Unrepeatable(GLFW_KEY_ESCAPE, [&]()
						 { glfwSetWindowShouldClose(this->window, true); }),
		// Keypress that allows you to select a world object
		new Unrepeatable(GLFW_KEY_SPACE, [&]()
						 { this->world->select_animation(); }),
		// Keypresses that change translation
		new Repeatable(GLFW_KEY_Q, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_position({0.0, -MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_W, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_position({0.0, 0.0, -MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_E, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_position({0.0, MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_A, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_position({-MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_S, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_position({0.0, 0.0, MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_D, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_position({MOVEMENT_SPEED, 0.0, 0.0}); }),
		// Keypresses that change orientation
		new Repeatable(GLFW_KEY_R, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
						model->modify_orientation({0.0, 0.0, MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_T, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
						model->modify_orientation({-MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_Y, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
						model->modify_orientation({0.0, 0.0, -MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_F, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
						model->modify_orientation({0.0, -MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_G, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
						model->modify_orientation({MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_H, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
						model->modify_orientation({0.0, MOVEMENT_SPEED, 0.0}); }),
		// Keypresses that change scale
		new Repeatable(GLFW_KEY_U, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_scale({0.0, -MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_I, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_scale({0.0, 0.0, MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_O, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_scale({0.0, MOVEMENT_SPEED, 0.0}); }),
		new Repeatable(GLFW_KEY_J, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_scale({-MOVEMENT_SPEED, 0.0, 0.0}); }),
		new Repeatable(GLFW_KEY_K, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_scale({0.0, 0.0, -MOVEMENT_SPEED}); }),
		new Repeatable(GLFW_KEY_L, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
							model->modify_scale({MOVEMENT_SPEED, 0.0, 0.0}); }),
		// Keypress to reset selected Model
		new Repeatable(GLFW_KEY_C, [&]()
					   {
						if (std::shared_ptr<Model> model = this->world->get_selected())
						{
						model->reset_position();
						model->reset_orientation();
						model->reset_scale();
						model->reset_color();
	 					} }),
		// Keypress to print selected Model's data
		new Unrepeatable(GLFW_KEY_ENTER, [&]()
						 {
							if (std::shared_ptr<Model> model = world->get_selected())
								model->debug_model_data(); }),
	};
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

InputHandler::~InputHandler()
{
	for (auto key : this->keys)
		delete key;
}

InputHandler::Key::Key(int const key, std::function<void()> const action) : key{key}, action{action}
{
}

InputHandler::Repeatable::Repeatable(int const key, std::function<void()> const action)
	: Key{key, action}
{
}

void InputHandler::Repeatable::handle_input(GLFWwindow *window)
{
	if (this->is_currently_pressed(window))
		this->action();
}

InputHandler::Unrepeatable::Unrepeatable(int const key, std::function<void()> const action)
	: Key{key, action}
{
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
