#include <vector>
#include <string>
#include <fstream>

static class TestController
{
public:
	static std::vector<std::string> getTestList();
	static void addNewTest(std::string);
	static void eraseTest(std::string);
};

