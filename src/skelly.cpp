#include "model.h"
#include <map>
#include <string>

namespace Skelly
{
	Model *create_skelly(std::shared_ptr<Shader> const shader)
	{
		Model *model = new Model{
			"torso",					  // Name
			std::forward_list<Model *>(), // Children
			std::vector<std::vector<vec3>>{
				{
					{
						{0.5, 0.5, 0.0},
						{0.5, -0.5, 0.0},
						{-0.5, -0.5, 0.0},
						{-0.5, 0.5, 0.0},
					},
				}}, // Vertices
			std::vector<unsigned int>(
				{0, 1, 3,
				 1, 2, 3}),		   // Indices
			shader,				   // Shader
			{0.0, 0.0, 0.0},	   // Position
			{0.0, 0.0, 0.0},	   // Orientaiton
			{0.0, 0.0, 0.0},	   // Scaling
			{1.0, 0.0, 0.0, 0.0}}; // Color
		return model;
	}
}
