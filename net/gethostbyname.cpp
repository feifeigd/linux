
#include <arpa/inet.h>	// inet_ntoa
#include <netdb.h>	// gethostbyname
#include <iostream>
using namespace std;

void error_handling(char const* msg) {
	cerr << msg << endl;
	exit(1);
}

#define DOMAIN2IP

int main(int argc, char* argv[]) {
	if (2 != argc)
	{
#ifdef DOMAIN2IP
		cerr << "Usage: " << argv[0] << " <addr>\n";
#else
		cerr << "Usage: " << argv[0] << " <IP>\n";
#endif
		exit(1);
	}

#ifdef DOMAIN2IP
	// 根据域名查IP
	hostent* host = gethostbyname(argv[1]);
#else
	// 根据IP查域名
	sockaddr_in addr{};
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	hostent* host = gethostbyaddr((char*)&addr.sin_addr, sizeof(addr.sin_addr), AF_INET);
#endif // 0

	if (!host)
	{
		error_handling("gethost... error");
	}
	cout << "official name: " << host->h_name << "\n";
	for (size_t i = 0; host->h_aliases[i]; i++)
	{
		cout << "Aliases " << i + 1 << ": " << host->h_aliases[i] << "\n";
	}
	cout << "Address type: " << ((host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6") << "\n";
	for (size_t i = 0; host->h_addr_list[i]; i++)
	{
		cout << "IP addr " << i + 1 << ": " << inet_ntoa(*(in_addr*)host->h_addr_list[i]) << "\n";
	}
	cout << endl;
	return 0;
}
