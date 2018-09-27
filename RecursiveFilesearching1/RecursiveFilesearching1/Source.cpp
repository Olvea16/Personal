#include "Exam.h"
#include <Windows.h>

using namespace std;
namespace fs = std::experimental::filesystem::v1;

int main() {
	// Get workspace directory
	char b[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, b);

	const string subdirectory = "\\data_example\\";
	fs::path path = b + subdirectory;

	// Do stuff
	Exam e1;
	vector<Result> resultA = e1.m1(path);

	Result resultB = e1.m2(path, 40000000);

	Stats stats = e1.m3(path);

	int mf = stats.mostFrequent();
	int lf = stats.leastFrequent();

	int oc = stats.occurences(123);
	int ob = stats.occurences(124);

	vector<fs::path> paths = stats.byTotals();

	return 0;
}