/*
 * tsplib.cpp
 *
 *  Created on: 13-11-2010
 *      Author: qba
 */

#include "tsplib.h"

tsplib::tsplib() {
	struct tsplib_edge_type tmp[] = { { "EXPLICIT", 8, EXPLICIT }, { "EUC_2D", 6, EUC_2D }, { "EUC_3D", 6, EUC_3D }, { "MAX_2D", 6, MAX_2D }, { "MAX_3D", 6, MAX_3D }, { "MAN_2D", 6, MAN_2D }, {
			"MAN_3D", 6, MAN_3D }, { "CEIL_2D", 7, CEIL_2D }, { "GEOM", 4, GEOM }, { "ATT", 3, ATT }, { "XRAY_1", 6, XRAY_1 }, { "XRAY_2", 6, XRAY_2 }, { "SPECIAL", 7, SPECIAL }, { NULL, 0, UNKNOWN } };
	tsplib_edge_weight_type_strings = (struct tsplib_edge_type *) malloc(sizeof(struct tsplib_edge_type) * 13);
	memcpy(tsplib_edge_weight_type_strings, tmp, sizeof(struct tsplib_edge_type) * 13);
}

tsplib::~tsplib() {
	// TODO Auto-generated destructor stub
}

struct tsplib_tsp_struct *
tsplib::tsplib_read_tsp(FILE *file) { //striped_
	int ret;
	struct tsplib_tsp_struct *tsp;
	unsigned int j, n, dimension;
	float x, y;
	char name_buf[32], type_buf[32];
	tsplib_edge_weight_type edge_weight_type;

	tsp = NULL;

	ret = fscanf(file, "NAME : %s\n", name_buf);
	if (ret != 1) {
		goto error;
	}

	//skipp comment tag
	while ((fgetc(file)) != '\n');

	/*ret = fscanf(file, "COMMENT : %s\n", name_buf);
	if (ret != 1) {
		goto error;
	}*/


	ret = fscanf(file, "TYPE : %s\n", name_buf);
	if (ret != 1) {
		goto error;
	}

	ret = fscanf(file, "DIMENSION : %u\n", &dimension);
	if (ret != 1) {
		goto error;
	}

	ret = fscanf(file, "EDGE_WEIGHT_TYPE : %s\n", type_buf);
	if (ret != 1) {
		goto error;
	}

	edge_weight_type = tsplib_str_to_edge_weight_type(type_buf, strlen(type_buf));

	tsp = tsplib_tsp_new(name_buf, strlen(name_buf), dimension, edge_weight_type);
	if (tsp == NULL) {
		goto error;
	}

	ret = fscanf(file, "NODE_COORD_SECTION\n");
	if (ret != 0) {
		goto error;
	}

	for (j = 1; j <= dimension; j++) {
		ret = fscanf(file, "%u %f %f\n", &n, &x, &y);
		if ((ret != 3) | (n != j)) {
			goto error;
		}

		tsp->node_coords[j].x = x;
		tsp->node_coords[j].y = y;
	}

	tsplib_tsp_construct_distance_map(tsp);

	return tsp;

	error: if (tsp) {
		tsplib_tsp_free(tsp);
	}
	return NULL;
}

struct tsplib_tsp_struct *
tsplib::tsplib_tsp_new(char *name, size_t name_len, unsigned int dimension, tsplib_edge_weight_type edge_weight_type) {
	struct tsplib_tsp_struct *tsp;

	tsp = (tsplib_tsp_struct *) malloc(sizeof *tsp);

	tsp->name = (char *) malloc(name_len + 1);
	strncpy(tsp->name, name, name_len);
	tsp->name[name_len] = '\0';

	tsp->comments = (char **) malloc(sizeof *tsp->comments);
	tsp->comments[0] = NULL;

	tsp->dimension = dimension;

	tsp->edge_weight_type = edge_weight_type;

	tsp->node_coords = (tsplib_node_coord_struct *) calloc(sizeof *tsp->node_coords, dimension);

	tsp->distance_map = NULL;

	return tsp;
}

void tsplib::tsplib_tsp_free(struct tsplib_tsp_struct *tsp) {
	int j;

	if (tsp->distance_map) {
		free(tsp->distance_map);
	}
	free(tsp->node_coords);

	for (j = 0; tsp->comments[j]; j++) {
		free(tsp->comments[j]);
	}
	free(tsp->comments);

	free(tsp->name);

	free(tsp);
}

tsplib_edge_weight_type tsplib::tsplib_str_to_edge_weight_type(char *type_str, size_t type_str_len) {
	int j;

	for (j = 0; tsplib_edge_weight_type_strings[j].str; j++) {
		if (tsplib_edge_weight_type_strings[j].len == type_str_len) {
			if (!strncmp(tsplib_edge_weight_type_strings[j].str, type_str, type_str_len)) {

				return tsplib_edge_weight_type_strings[j].type;
			}

		}
	}
	return tsplib_edge_weight_type_strings[j].type;

}

/* ================================== */
/* Distance Functions */

unsigned int tsplib::euc_2d_distance_func(struct tsplib_node_coord_struct a, struct tsplib_node_coord_struct b) {
	double xd, yd;
	xd = b.x - a.x;
	yd = b.y - a.y;

	return (unsigned int) sqrt(xd * xd + yd * yd);
}

#undef M_PI
#define M_PI 3.14159265358979323846264

unsigned int tsplib::geom_distance_func(struct tsplib_node_coord_struct a, struct tsplib_node_coord_struct b) {
	double lati, latj, longi, longj;
	double q1, q2, q3, q4, q5;
	lati = M_PI * a.x / 180.0;
	latj = M_PI * b.x / 180.0;
	longi = M_PI * a.y / 180.0;
	longj = M_PI * b.y / 180.0;
	q1 = cos(latj) * sin(longi - longj);
	q3 = sin((longi - longj) / 2.0);
	q4 = cos((longi - longj) / 2.0);
	q2 = sin(lati + latj) * q3 * q3 - sin(lati - latj) * q4 * q4;
	q5 = cos(lati - latj) * q4 * q4 - cos(lati + latj) * q3 * q3;
	return (unsigned int) (6378388.0 * atan2(sqrt(q1 * q1 + q2 * q2), q5) + 1.0);
}

void tsplib::tsplib_tsp_construct_distance_map(struct tsplib_tsp_struct *tsp) {
	unsigned int j, k, s, dimension;
	unsigned int *distance_map;

	struct tsplib_node_coord_struct *node_coords;
	distance_func_type distance_func;

	node_coords = tsp->node_coords;
	dimension = tsp->dimension;

	if (tsp->distance_map) {
		free(tsp->distance_map);
		tsp->distance_map = NULL;
	}

	printf("%d\t%d\n",sizeof (unsigned int), (dimension - 1) * dimension / 2.0);
	distance_map = (unsigned int *) calloc(sizeof (unsigned int *), (dimension - 1) * dimension / 2.0);

	/* select the distance function */
	switch (tsp->edge_weight_type) {
	case EUC_2D:
		s = 0;
		for (j = 0; j < dimension; j++) {
			for (k = j + 1; k < dimension; k++) {
				distance_map[s] = euc_2d_distance_func(node_coords[j], node_coords[k]);
				printf("%d\t",distance_map[s] );
				s++;
			}
			printf("\n");
		}
		break;

	case GEOM:
		s = 0;
		for (j = 0; j < dimension; j++) {
			for (k = j + 1; k < dimension; k++) {
				distance_map[s] = geom_distance_func(node_coords[j], node_coords[k]);
				printf("%d\t",distance_map[s] );
				s++;
			}
			printf("\n");
		}
		break;

	default:
		return;
	}

	tsp->distance_map = distance_map;
}
