#pragma once

#include "vec3.h"

class ray
{
public:
	ray(){}
	ray(const vec3& a, const vec3& b) { orig = a; dir = b; }
	vec3 origin() const { return orig; }
	vec3 direction()const { return dir; }
	vec3 point_at_parameter(double t) const { return orig + t * dir; }

	vec3 at(double t) const
	{
		return orig + t * dir;
	}
public:
	point3 orig;
	vec3 dir;
};