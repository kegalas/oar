#include "geometry.h"

int main(){
	//你可以在这里做一些小小的测试
	geo::vec3f v1(1.1,2.2,3.3);
	geo::vec3f v2(3.3,2.2,1.1);

	std::cout<<v1+v2<<"\n";
	std::cout<<geo::dot(v1,v2)<<"\n";
	
	return 0;
}
