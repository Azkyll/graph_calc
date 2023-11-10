#include <functions.hpp>



int main()
{
	functions::func_ff cos_ = functions::compose<float>(functions::cos<float>, functions::id<float>);
	std::cout << cos_(0) << "\n"
			  << cos_(1) << std::endl;


	return 0;
}