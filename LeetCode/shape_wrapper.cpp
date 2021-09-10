#include "shape_wrapper.h"

shape* creat_shape(shape_type type)
{
	switch (type)
	{
	case shape_type::circle:
		return new circle;
		break;
	case shape_type::triangle:
		return new triangle;
		break;
	case shape_type::rectangle:
		return new rectangle;
		break;
	default:
		break;
	}
	return nullptr;
}