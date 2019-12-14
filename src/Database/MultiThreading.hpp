#pragma once
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../guid.h"

//This file contains all of the objects required for the 
//multithreading used within this project

class ThreadManager {
	std::unordered_map<Guid, std::thread> threads;

public:

	//Singleton
	static auto Get() {
		ThreadManager t;
		return t;
	}

	Guid OpenThread();

	template <typename Object>
	bool OpenThreadForWork(std::function<void(Object& objectToWorkOn)>& predicate);
};
