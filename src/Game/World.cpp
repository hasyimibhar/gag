#include <set>

#include "World.h"
#include "../Common/Common.h"

World::World()
{
}

void
World::add(Entity* e)
{
   toAdd_.push_back(e);
}

void
World::remove(Entity* e)
{
   remove_element(toRemove_, e);
   toRemove_.push_back(e);
}

void
World::reindex()
{
   std::set<int> touched;

	FOREACH(vector, Entity*, e, toRemove_)
	{
		int *id = (*e)->getIndices();

		while (*id)
		{
			touched.insert(*id);
			remove_element(getIndex(*id),*e);
			id++;
		}

		delete *e;
	}

	FOREACH(vector, Entity*, e, toAdd_)
	{
		int *id = (*e)->getIndices();

		while (*id)
		{
			touched.insert(*id);
			getIndex(*id).push_back(*e);
			(*e)->setWorld(this);
			id++;
		}
	}

	toAdd_.clear();
	toRemove_.clear();

	FOREACH(set, int, id, touched)
	{
		if ((*id == ID("rndr")) || (*id == ID("entt")))
		{
			std::vector<Entity*> &ind = getIndex(*id);
			std::stable_sort(ind.begin(), ind.end(), EntityCompare(*id));
		}
	}
}
