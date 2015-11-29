#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include <cassert>

template<typename T>
class Singleton
{
	public:
		Singleton();
		~Singleton();

		static T& getInstance();
		static T* getInstancePointer();

	protected:

	private:
		static T* instance_;

};



template<typename T> T* Singleton<T>::instance_ = 0;



template<typename T>
inline
Singleton<T>::Singleton()
{
   assert(instance_ == 0 && "Trying to initialize an already initalized Singleton");
   uintptr_t offset = (uintptr_t)(T*)1 - (uintptr_t)(Singleton <T>*)(T*)1;
   instance_ = (T*)((uintptr_t)this + offset);
}



template<typename T>
inline
Singleton<T>::~Singleton()
{
   assert(instance_ != 0 && "Trying to destroy a Singleton that has not been intialized");
   instance_ = 0;
}



template<typename T>
inline
T& Singleton<T>::getInstance()
{
   assert(instance_ != 0 && "Trying to get a Singleton that has not been intialized");
   return *instance_;
}



template<typename T>
inline
T* Singleton<T>::getInstancePointer()
{
   assert(instance_ != 0 && "Trying to get a Singleton that has not been intialized");
   return instance_;
}

#endif // SINGLETON_H_INCLUDED
