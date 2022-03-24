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

	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;

public:
	hitable** list;
	int list_size;
};
