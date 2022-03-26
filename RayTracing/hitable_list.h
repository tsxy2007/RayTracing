#pragma once
#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable_list() {}
	hitable_list(hitable** l, int n)
	{
		list = l;
		list_size = n;
	}

	hitable_list(shared_ptr<hitable> object)
	{
		add(object);
	}

	void clear() { objects.clear(); }

	void add(shared_ptr<hitable> object)
	{
		objects.push_back(object);
	}

	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;

public:
	hitable** list;
	int list_size;

	std::vector<shared_ptr<hitable>> objects;
};
