#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#include "acdb_data.h"

typedef char* (*platform_get_snd_device_name_t)(int);
typedef int (*platform_get_snd_device_index_t)(char*);
typedef int (*platform_get_snd_device_acdb_id_t)(int);

int main(int argc, char** argv) {
	void *handle;
	platform_get_snd_device_name_t platform_get_snd_device_name;
	platform_get_snd_device_index_t platform_get_snd_device_index;
	platform_get_snd_device_acdb_id_t platform_get_snd_device_acdb_id;

	if (argc != 2) {
		printf("%s: [audio hal path]\n", argv[0]);
		exit(1);
	}

	handle = dlopen(argv[1], RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		return 1;
	}

	platform_get_snd_device_name = (platform_get_snd_device_name_t) dlsym(handle, "platform_get_snd_device_name");

	if (!platform_get_snd_device_name)  {
		fprintf(stderr, "%s\n", dlerror());
		return 1;
	}

	platform_get_snd_device_index = (platform_get_snd_device_index_t) dlsym(handle, "platform_get_snd_device_index");

	if (!platform_get_snd_device_index)  {
		fprintf(stderr, "%s\n", dlerror());
		return 1;
	}

	platform_get_snd_device_acdb_id = (platform_get_snd_device_acdb_id_t) dlsym(handle, "platform_get_snd_device_acdb_id");

	if (!platform_get_snd_device_acdb_id)  {
		fprintf(stderr, "%s\n", dlerror());
		return 1;
	}

	int dev, idx;

	int named_indexes[SND_DEVICE_MAX] = {};

	printf("    <acdb_ids>\n");
	for (dev = 0, idx = 0; dev < SND_DEVICE_MAX; dev++) {
		idx = platform_get_snd_device_index(faux_device_table[dev]);
		if(idx >= 0){
			named_indexes[dev] = idx;
			printf("        <device name=\"%s\" acdb_id=\"%i\"/>\n", faux_device_table[dev], platform_get_snd_device_acdb_id(idx));
		}
	}
	printf("    </acdb_ids>\n");

	printf("\n");

	printf("    <device_names>\n");
	for (dev = 0, idx = 0; dev < SND_DEVICE_MAX; dev++) {
		idx = platform_get_snd_device_index(faux_device_table[dev]);
		if(idx >= 0) printf("        <device name=\"%s\" alias=\"%s\"/>\n", faux_device_table[dev], platform_get_snd_device_name(idx));
	}
	printf("    </device_names>\n");

	printf("\n");

	printf("    <unknown_devices>\n");
	for (idx = 0; idx < 1000; idx++) {
		char found = 0;
		for(dev = 0; dev < SND_DEVICE_MAX; dev++){
			if (named_indexes[dev] == idx) found = 1;
		}
		if (!found) {
			char* name = platform_get_snd_device_name(idx);
			if(name && name[0]) printf("        <device name=\"UNKNOWN\" index=\"%d\" alias=\"%s\" acdb_id=\"%d\"/>\n", idx, platform_get_snd_device_name(idx), platform_get_snd_device_acdb_id(idx));
		}
	}
	printf("    </unknown_devices>\n");

	dlclose(handle);
	return 0;
}
