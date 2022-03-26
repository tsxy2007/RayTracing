#pragma once

#include "hitable.h"

class sphere : public hitable
{
public:
	sphere(){}
	sphere(vec3 cen, double r,shared_ptr<material> m) : 
		center(cen),
		radius(r),
		mat_ptr(m) 
	{};

	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;
public:
	vec3 center;
	double radius;
	shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double half_b = dot(oc, r.direction());
	double c = oc.squared_length() - radius * radius;
	
	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		return false;
	}

	auto sqrtd = sqrt(discriminant);

	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	return true;
}
