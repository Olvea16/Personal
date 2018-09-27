#include "ProcessData.h"

#include <vector>
#include <string>


using namespace std;

int main() {

	ProcessData process_data;

	vector<AudioSessionData> session_data = process_data.get_session_data();

	return 0;
}