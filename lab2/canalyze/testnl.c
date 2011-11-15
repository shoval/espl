#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "namelist.h"

int main(int argc, char **argv) {
	namelist nl = make_namelist();
	int checks = 0;
	int i;

	add_name(nl, "foo");
	add_name(nl, "bar");
	add_name(nl, "foo");

	for(i = 0; i!=nl->size; ++i) {
		if(!strcmp("foo", nl->names[i].name)) {
			assert(nl->names[i].count==2);
			checks|=1;
		} else if(!strcmp("bar", nl->names[i].name)) {
			assert(nl->names[i].count==1);
			checks|=2;
		} else {
			checks|=4;
		}
	}
	assert(checks==3);
	
	return 0;
}
		
