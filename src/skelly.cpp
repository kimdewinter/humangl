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
						{-0.5, 0.5, 0.5},
						{-0.5, -0.5, 0.5},
						{0.5, -0.5, 0.5},
						{0.5, 0.5, 0.5},
						{-0.5, 0.5, -0.5},
						{-0.5, -0.5, -0.5},
						{0.5, -0.5, -0.5},
						{0.5, 0.5, -0.5},
					},
				}}, // Vertices
			std::vector<unsigned int>(
				{0, 1, 3,
				 1, 2, 3,
				 7, 6, 4,
				 6, 5, 4,
				 3, 2, 7,
				 2, 6, 7,
				 4, 0, 7,
				 0, 3, 7,
				 4, 5, 0,
				 5, 1, 0,
				 1, 5, 2,
				 5, 6, 2}),		   // Indices
			shader,				   // Shader
			{0.0, 0.4, -0.5},	   // Position
			{0.0, 0.0, 0.0},	   // Orientation
			{-0.8, -0.40, -0.8},   // Scale
			{1.0, 0.0, 0.0, 0.0}}; // Color
		return model;
	}
}
