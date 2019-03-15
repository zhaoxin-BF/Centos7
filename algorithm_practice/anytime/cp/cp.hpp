#ifndef __CP_HPP__
#define __CP_HPP__

#include<iostream>
#include<queue>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

class Lock{
	private:
		pthread_mutex_t lock unlock;
	public:
		lock()
		{
			pthread_mutex_init(&lock, NULL);
		}

		~lock()
		{
			pthread_mutex_destory(&lock);
		}
}

class BlockQueue{
	private:
		std::queue<int> bq;
		int cap;
		
	
	public:
}


#endif
