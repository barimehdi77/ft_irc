#include <iostream>
#include <string>
#include <vector>

class Request
{
private:

public:
	std::vector<std::string>	args;
	Request() {}
};

void	parseRequest(std::string str) {
	// std::string s = "scott>=tiger>=mushroom";
	// std::string delimiter = ">=";

	// size_t pos = 0;
	// std::string token;
	// while ((pos = s.find(delimiter)) != std::string::npos) {
	// 	token = s.substr(0, pos);
	// 	std::cout << token << std::endl;
	// 	s.erase(0, pos + delimiter.length());
	// }
	// std::cout << s << std::endl;
	
	Request	request;
	size_t	i = 0;
	size_t	j = 0;
	size_t	k = 0;

	while (str[i]) {
		if (str[i] == ' ') {
			request.args.push_back(str.substr(j, i - j));
			if (str[i] == ' ')
				i++;
			j = i;
		}
		i++;
	}
	request.args.push_back(str.substr(j, i - j));
	std::cout << str;


	// while (str[i]) {
	// 	if (str[i] == ' ')
	// 		std::cout << "Gazoinks";
	// 	i++;
	// }
}

int		main() {
	parseRequest("NICK amy");
	return 0;
}