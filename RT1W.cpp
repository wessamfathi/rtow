// RT1W.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sphere.h"
#include "hitable_list.h"
#include <float.h>

vec3 color(const ray& r, hitable* world)
{
	hit_record rec;

	if (world->hit(r, 0.0f, FLT_MAX, rec))
	{
		return 0.5f * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

void generate_image()
{
	int nx = 200;
	int ny = 100;

	std::ofstream out("out.ppm");

	out << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f);
	list[1] = new sphere(vec3(0, -100.5f, -1), 100);
	hitable* world = new hitable_list(list, 2);

	for (int j = ny - 1; j >= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 p = r.point_at_paramter(2.0f);
			vec3 col = color(r, world);

			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);
			
			out << ir << " " << ig << " " << ib << "\n";
		}
	}

	delete world;
	delete list[1];
	delete list[0];

	out.close();
}

int main()
{
	generate_image();
	
	return 0;
}