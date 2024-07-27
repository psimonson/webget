/*
 * webget - Simple web downloader.
 *
 * Author: Philip R. Simonson
 * Date:   06/27/2024
 *
 */

#define _DEFAULT_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prs/network.h"
#include "webget.h"

/* Initialise web header content.
 */
void webget_init(struct WebHeader *wh, const char *urlpath, unsigned short port)
{
	if(wh == NULL || urlpath == NULL)
		return;

	strncpy(wh->sitename, urlpath, MAXBUF-1);
	wh->sitedata[0] = '\0';
	wh->datasize = 0;
	wh->response = 0;
	wh->sitecap = 0;
	wh->port = port;
	wh->msg = "";
	wh->err = 0;
	wh->s = 0;
}
/* Gets the header from the website.
 */
void webget_getheader(struct WebHeader *wh, const char *urlpath)
{
	char request[4096];
	char *strend = NULL;

	if(wh == NULL) {
		wh->err = 1;
		wh->msg = "NULL passed";
		return;
	}

	strend = strchr(wh->sitename, '\n');
	if(strend != NULL) {
		*strend = '\0';
	}

	wh->s = socket_connect(wh->sitename, wh->port);
	if(wh->s == INVALID_SOCKET) {
		fprintf(stderr, "Error (%hu): Cannot connect to %s!\n", wh->s, wh->sitename);
		wh->err = 2;
		wh->msg = "Invalid socket";
		return;
	}

	snprintf(request, 4095, "GET %s\r\n", urlpath);
	send(wh->s, request, strlen(request), 0);
	wh->datasize = recv(wh->s, wh->sitedata, MAXHDR-1, 0);
	socket_close(wh->s);
	wh->err = 0;
	wh->msg = "Success";
}
