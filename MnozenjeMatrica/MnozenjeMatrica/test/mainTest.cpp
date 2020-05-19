#include <gtest\gtest.h>

#include <iostream>
#include <string>

#ifdef TESTING

extern void readAllMultiplicationElementsFromFiles();

bool shouldReadMultiplicationElements(int argc, char** argv)
{
	if (const bool haveMoreThenOneArgc = argc > 1; haveMoreThenOneArgc)
	{
		for (int i = 1; i < argc; ++i)
		{
			std::string argument(argv[i]);

			if (argument.find("-*MultiplierTest*") != std::string::npos)
			{
				return false;
			}
		}
	}

	return true;
}

int main(int argc, char** argv) {
	std::cout << "Running main() from " << __FILE__ << '\n';

	if (shouldReadMultiplicationElements(argc, argv)) // --gtest_filter=-*MultiplierTest*
	{
		std::cout << "Loading all matrices...\n";
		readAllMultiplicationElementsFromFiles();
		std::cout << "Matrices are loaded.\n";
	}

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

#endif