#include<iostream>
#include<list>
#include<cfloat> // FLT_MIN
#include<cmath> // abs

template <typename T>
void print (std::list<T>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size; ++i) {
		std::list<float>::iterator it = std::next(points.begin(), i);
		std::cout << *it << " \t";	
	}
	std::cout << std::endl;
	
}

template <typename T>
void fun (std::list<T>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size; ++i) {
		std::list<float>::iterator it = std::next(points.begin(), i);
		std::list<float>::iterator prev = std::next(it, -1);
		std::list<float>::iterator next = std::next(it, 1);
		*it = (*prev + *next) / 2.0;

		if (i == size-1) {
			*it = (*prev + 1.0) / 2.0;
		}
	}
	
}


template <typename T>
void fun2 (std::list<T>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size-1; ++i) {
		std::list<float>::iterator it = std::next(points.begin(), i);
		std::list<float>::iterator prev = std::next(it, -1);
		std::list<float>::iterator next = std::next(it, 1);
		*it = (*prev + *next) / 2.0;
		if (std::abs(*it - *prev) < std::abs(*it - *next)) {
			*it += FLT_MIN;
		} else {
			*it -= FLT_MIN;
		}
/*
		if (i == 9) {
			if (std::abs(*it - *prev) < 1.0-*it) {
				*it += FLT_MIN;
			} else {
				*it -= FLT_MIN;
			}
		}
*/	}
	
}


int main() {
	std::list<float> points = {0,0.11,0.2,0.34, 0.36,0.3666,0.77,0.78,0.788,1.0};
	print(points);
	fun2(points);
	print(points);
	for (std::size_t i = 1; i < 300; ++i) {
		fun2(points);
	//	print(points);
	}
	print(points);

	std::cout << FLT_MIN << std::endl;
}
