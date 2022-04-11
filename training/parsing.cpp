#include <iostream>
#include <string>
#include <vector>

class Request
{
private:

public:
	std::vector<std::string>	args;
	std::string					command;
	Request() {}
};

Request	parseRequest(std::string str) {
	Request	request;
	size_t	i = 0;
	size_t	j = 0;

	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	while (str[i]) {
		if (str[i] == ' ') {
			request.args.push_back(str.substr(j, i - j));
			while (str[i] == ' ')
				i++;
			j = i;
		}
		if (str[i] == ':') {
			request.args.push_back(str.substr(i + 1, str.length() - i));
			request.command = request.args[0];
			request.args.erase(request.args.begin());
			return request;
		}
		i++;
	}
	request.args.push_back(str.substr(j, i - j));
	request.command = request.args[0];
	request.args.erase(request.args.begin());
	return request;
}

int		main() {
	Request	request;
	request = parseRequest("      NICK amy      fhdsjkfew hjkds fewjkfw");
	std::cout << "COMMAND: " << request.command << std::endl;
	std::cout << "ARGS:\n";
		for (size_t i = 0; i < request.args.size(); i++)
		std::cout << i + 1 <<") " << request.args[i] << std::endl;
	return 0;
}