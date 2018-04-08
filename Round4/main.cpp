#include <iostream>


int count_possibilities(int n)
{
	// Start Here.
	return 0;
}

void check_results(int n, int correct_result)
{
	// DO NOT EDIT THIS FUNCTION!!!
	if(count_possibilities(n) != correct_result)
	{
		std::cout << "\033[0;31mWrong answer for n=" << n << std::endl;
		throw 1;
	}
	else{
		std::cout << "\033[1;34mCorrect answer for n=" << n << std::endl;
	}
}	

int main()
{
	// DO NOT EDIT THIS FUNCTION!!!
	try
	{
		check_results(1, 2);
		check_results(2, 4);
		check_results(3, 6);
		check_results(4, 10);
		check_results(10, 178);
		check_results(28, 1028458);
		check_results(45, 3672623806);
		std::cout 
            << "\033[33;5m\033[1;32mWINNER WINNER WINNER WINNER WINNER!!!!!" 
            << std::endl;
		return 0;
	}
	catch(int e){
		return 1;
	}
}
