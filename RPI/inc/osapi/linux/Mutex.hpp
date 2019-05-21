#ifndef OSAPI_LINUX_MUTEX_HPP
#define OSAPI_LINUX_MUTEX_HPP

#include <osapi/Utility.hpp>
#include <pthread.h>

namespace osapi
{
	class Conditional;

	class Mutex
	{
	public:
		Mutex();
		void lock();
		void unlock();
		~Mutex();
	private:
		friend class Conditional;

		pthread_mutex_t mut_;
	};
}

#endif