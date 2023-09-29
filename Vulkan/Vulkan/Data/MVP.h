#pragma once

#include<glm/glm.hpp>

inline namespace VK
{
	struct MVP
	{
		glm::mat4 mtxWorld;
		glm::mat4 mtxView;
		glm::mat4 mtxProj;
	};
}


