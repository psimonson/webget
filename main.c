/*
 * main - Test webget program.
 *
 * Author: Philip R. Simonson
 * Date:   06/27/2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prs/network.h"
#include "prs/getstr.h"
#include "webget.h"

/* Entry point for main application.
 */
int main()
{
	struct WebHeader wh;
	char dnspath[4096];
	char urlpath[4096];
	char *line;
	size_t linecap;
	size_t length;

	printf("Enter hostname or IP address: ");
	length = getstr(&line, &linecap, stdin);
	if(length == 0) {
		fprintf(stderr, "Error: Could not get hostname or address...\n");
		free(line);
		return 1;
	}
	strncpy(dnspath, line, 4095);
	free(line);

	printf("Enter URL path: ");
	length = getstr(&line, &linecap, stdin);
	if(length == 0) {
		fprintf(stderr, "Error: Could not get URL path...\n");
		free(line);
		return 1;
	}
	strncpy(urlpath, line, 4095);
	free(line);

	webget_init(&wh, dnspath, 8080);
	webget_getheader(&wh, urlpath);
	if(wh.err != 0) {
		fprintf(stderr, "Error: Could not get header...\n");
		return 1;
	}

	wh.sitedata[wh.datasize] = '\0';
	printf("Header...\n-----------------\n%s\n", wh.sitedata);
	return 0;
}
