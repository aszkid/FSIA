#include <iostream>
#include <vector>

#define OUT(x) std::cout << x << std::endl

typedef unsigned int uint;

int main()
{
	using std::cout;
	using std::endl;
	using std::vector;
	
	vector<float> data = {.2f, .25f, .3f, .35f, .4f};
	vector<float> growths;
	
	size_t i;
	
	float last = .0f;
	float curr;
	
	for(i = 0; i < data.size(); i++)
	{
		curr = data[i];
		growths.push_back(curr-last);
		last = curr;
	}
	
	float growth;
	
	for(i = 0; i < growths.size(); i++)
	{
		growth = growths[i];
		OUT("(" << i << ") Growth: " << growth);
	}
	
	return 0;
}
