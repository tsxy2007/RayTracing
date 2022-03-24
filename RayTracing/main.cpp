#include <iostream>
#include <fstream>
#include <string>
#include "hitable_list.h"
#include "sphere.h"
#include "float.h"
#include "color.h"
#include "camera.h"

double hit_sphere(const vec3& center, double radius, const ray& r)
{
	vec3 oc = r.origin() - center;

	double a = dot(r.direction(), r.direction());
	double b = 2.0 * dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1.f;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

vec3 ray_color(const ray& r)
{
	double t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
	}

	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

vec3 ray_color(const ray& r, hitable* world,int depth)
{
	if (depth <=0)
	{
		return color(0, 0, 0);
	}
	hit_record rec;
	if (world->hit(r,0.01, infinity,rec))
	{
		point3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world,depth-1);
	}

	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{


	// image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int sample_per_pixel = 100;
	const int max_depth = 50;

	// file
	std::string filename = "Test.ppm";
	std::ofstream ostrm(filename);

	// Camera
	camera cam;

	// Render

	ostrm << "P3\n" << image_width << ' ' << image_height << "\n255\n";



	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);

	hitable* world = new hitable_list(list, 2);

	for (int j = image_height - 1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < sample_per_pixel; s++)
			{
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(ostrm, pixel_color, sample_per_pixel);
		}

	}
	
	return 0;
}