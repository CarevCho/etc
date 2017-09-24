#include <iostream>
#include <fstream>

#pragma warning(disable:4996)

using namespace std;

#if 1
// file write
int main(int argc, char* argv[])
{
#if 1
	/// cpp
	ofstream outfile("output.txt");

	for (int i = 0; i < 10; i++) {
		outfile << i << endl;
	}
	outfile.close();
#else
	/// c
	FILE *file;
	file = fopen("output.txt", "w");
	for (int i = 0; i < 10; i++) {
		fprintf(file, "%d", i);
	}fclose(file);

#endif
    return 0;
}


#else
// file read
int main(int argc, char*argv[]) 
{
#if 1
	/// cpp
#else
	/// c
#endif
	return 0;
}


#endif