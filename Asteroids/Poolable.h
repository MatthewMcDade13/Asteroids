#pragma once

template <typename T>
class ObjectPool;

template<typename T>
class Poolable : public T
{
	friend ObjectPool<Poolable<T>>;

	Poolable<T>* m_next;

	Poolable() {}

	Poolable<T>* getNext() { return m_next; }
	void setNext(Poolable<T>* next) { m_next = next; }
};
