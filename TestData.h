#include <vector>
#include <string>
#include <fstream>

static class TestData
{
public:
	static std::vector<std::string> getTestList();
	static void addNewTest(std::string);
	static void eraseTest(std::string);
};

