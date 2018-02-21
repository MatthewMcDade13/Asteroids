#pragma once

#include <utility>
#include <vector>
#include <assert.h>

template <typename T>
class ObjectPool
{
public:

	ObjectPool(int maxSize): m_maxSize(maxSize)
	{
		m_objects.reserve(m_maxSize);
		m_objects.assign(m_maxSize, T());
		m_firstAvailable = &m_objects[0];

		for (size_t i = 0; i < m_objects.size() - 1; i++)
		{
			m_objects[i].m_next = &m_objects[i + 1];
		}

		m_objects.back().m_next = nullptr;

		m_activeObjects.reserve(m_maxSize);
	}

	T* create()
	{
		assert(m_firstAvailable);

		T* obj = m_firstAvailable;
		obj->activate();

		m_firstAvailable = obj->getNext();

		m_activeObjects.push_back(obj);

		return obj;
	}

	void destroy(T* object)
	{
		using namespace std;

		object->deactivate();
		object->setNext(m_firstAvailable);

		m_firstAvailable = object;

		auto itr = find_if(m_activeObjects.begin(), m_activeObjects.end(),
			[object](T* o) {
			return o == object;
		});

		m_activeObjects.erase(itr);
	}

	void destroy(int objectIndx)
	{
		T* obj = m_activeObjects[objectIndx];

		obj->deactivate();
		obj->setNext(m_firstAvailable);
		m_firstAvailable = obj;

		m_activeObjects.erase(m_activeObjects.begin() + objectIndx);
	}

	const std::vector<T*>& getActiveObjects() const
	{
		return m_activeObjects;
	}

	// Destroy and set all active objects to not active state
	void reset()
	{
		for (int i = (int)m_activeObjects.size() - 1; i >= 0; i--)
			destroy(i);
	}

protected:

	std::vector<T> m_objects;
	std::vector<T*> m_activeObjects;
	T* m_firstAvailable;

private:
	const int m_maxSize;
};