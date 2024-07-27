/*
 * webget - Simple web downloader.
 *
 * Author: Philip R. Simonson
 * Date:   06/27/2024
 *
 */

enum Response {
	ROKAY=400,
	RMOVEDTEMP=401,
	RMOVEDPERM=402,
	RFORBIDDEN=403,
	RNOTFOUND=404
};

#define MAXBUF 256
#define MAXHDR 4096

struct WebHeader {
	char sitename[MAXBUF];
	char sitedata[MAXHDR];
	unsigned short port;
	size_t datasize;
	size_t sitecap;
	int response;
	char *msg;
	SOCKET s;
	int err;
};

void webget_init(struct WebHeader *wh, const char *dnspath, unsigned short port);
void webget_getheader(struct WebHeader *wh, const char *urlpath);

