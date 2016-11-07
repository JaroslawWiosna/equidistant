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
	}
/*
	std::list<float>::iterator it = std::next(points.end(), -1);
	std::list<float>::iterator prev = std::next(it, -1);
	//std::list<float>::iterator next = std::next(it, 1);

	if (std::abs(*it - *prev) < (1.0 - *it)) {
		*it += FLT_MIN;
	} else {
		*it -= FLT_MIN;
	}
*/
}

class Spherepoint{
	public:
	float theta, phi;
	float x,y,z;
	void setCoord();	
	Spherepoint(float THETA = 0, float PHI = 0) : theta(THETA), phi(PHI) {} 
};

void Spherepoint::setCoord () {
	x = cos(theta) * cos(phi);
	y = cos(theta) * sin(phi);
	z = sin(theta);
}



void fun3 (std::list<Spherepoint>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size-1; ++i) {
		float tmp;
		std::list<Spherepoint>::iterator it = std::next(points.begin(), i);
		std::list<Spherepoint>::iterator prev = std::next(it, -1);
		std::list<Spherepoint>::iterator next = std::next(it, 1);
//		tmp = ((*prev).phi + (*next).phi) / 2.0;
		if (std::abs(it->phi - prev->phi) < std::abs(it->phi - next->phi)) {
			it->phi += FLT_MIN;
		} else {
			it->phi -= FLT_MIN;
		}
	}
}

void Sphereprint (std::list<Spherepoint>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size; ++i) {
		std::list<Spherepoint>::iterator it = std::next(points.begin(), i);
		std::cout << it->phi << " \t";	
	}
	std::cout << std::endl;
	
}



int main() {
	std::list<float> points = {0,0.11,0.14442,0.3,1.0};

	print(points);
	fun2(points);
	print(points);
	for (std::size_t i = 1; i < 30000; ++i) {
		fun2(points);
	//	print(points);
	}
	print(points);

	Spherepoint * test= new Spherepoint();
	Spherepoint * obj1= new Spherepoint(0,0.1);
	Spherepoint * obj2= new Spherepoint(0,0.25);
	Spherepoint * obj3= new Spherepoint(0,0.26);
	Spherepoint * obj4= new Spherepoint(0,0.44);
	Spherepoint * obj5= new Spherepoint(0,0.5);

//	std::list<Spherepoint> Spoints = {(0.1,0.1),(0.25,0.25),(0.26,0.26),(0.44,0.44),(0.5,0.5)};
	std::list<Spherepoint> Spoints = {*obj1, *obj2, *obj3, *obj4, *obj5};
	
	Sphereprint(Spoints);
	for (std::size_t i = 1; i < 400000; ++i) {
		fun3(Spoints);
		Sphereprint(Spoints);
	}
	Sphereprint(Spoints);
}
