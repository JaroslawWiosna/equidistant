#include <gtest/gtest.h>

#include "../../Spherepoint/Spherepoint.hpp"


TEST(SphereTest, Rotate)
{
	Spherepoint * obj1  = new Spherepoint(1, 1);
	Spherepoint * obj2  = new Spherepoint(2,-1);

	float thetaMovement = 1.5f;
	float eps = 0.1f;

	obj1 -> rotate( -1 * thetaMovement );
	obj2 -> rotate( -1 * thetaMovement );

	ASSERT_TRUE( std::abs(obj1->phi - 1) 			< eps );
	ASSERT_TRUE( std::abs(obj1->theta - (-0.5)) 		< eps );
	std::cout << obj2->phi << std::endl;
	// TODO: below ... Is PI added correctly?
	ASSERT_TRUE( std::abs(obj2->phi - (2 + 3.14)) 		< eps );
	ASSERT_TRUE( std::abs(obj2->theta < 2*3.14 - (-1 -1.5f)) < eps );

	ASSERT_FALSE(false);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

