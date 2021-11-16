#include "collections.h"

#include <cstdio>
#include <algorithm>


// Not really a test, I'll do that later
int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
	float c_array[] = {6.2f, 4.3f, 1.4f, 0.5f};

	rsl::Array<float> a = {};
	rsl::Array<float> b{};

	a = rsl::make_array_from_memory<float>(c_array, sizeof(c_array));

	for(auto f : a){
		printf("%f, ", f);
	}
	printf("\n");

	std::sort(begin(a), end(a));

	for(auto f : a){
		printf("%f, ", f);
	}
	printf("\n");


	{
		auto back_itr = back(a);
		if(back_itr){
			printf("back(a) = %f\n", *back_itr);
		} else {
			printf("back(a) = nullptr\n");
		}
	}


	{
		auto back_itr = back(b);
		if(back_itr){
			printf("back(b) = %f\n", *back_itr);
		} else {
			printf("back(b) = nullptr\n");
		}
	}

	{
		float default_value = 0;

		for(int i = -2; i < 10; i++){ // NOTE: This can be anything, it will always be well defined.
			printf("%f, ", at_or(a, i, default_value));
		}
		printf("\n");
	}



	return 0;
}