#include <gtest\gtest.h>

#ifdef TESTING

extern void readAllMultiplicationElementsFromFiles();

int main(int argc, char** argv) {
	printf("Running main() from %s\n", __FILE__);

	printf("Loading all matrices...\n");
	readAllMultiplicationElementsFromFiles();
	printf("Matrices are loaded.\n");

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

#endif