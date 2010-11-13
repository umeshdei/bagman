/*
 * tsplib.h
 *
 *  Created on: 13-11-2010
 *      Author: qba
 */

#ifndef TSPLIB_H_
#define TSPLIB_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>

#undef M_PI
#define M_PI 3.14159265358979323846264

typedef enum {
	TSP
} tsplib_type;


struct tsplib_node_coord_struct {
	double x;
	double y;
};

typedef enum {
	UNKNOWN = -1, EXPLICIT, EUC_2D, EUC_3D, MAX_2D, MAX_3D, MAN_2D, MAN_3D, CEIL_2D, GEOM, ATT, XRAY_1, XRAY_2, SPECIAL
} tsplib_edge_weight_type;

typedef enum {
	FUNCTION, FULL_MATRIX, UPPER_ROW, LOWER_ROW, UPPER_DIAG_ROW, LOWER_DIAG_ROW, UPPER_COL, LOWER_COL, UPPER_DIAG_COL, LOWER_DIAG_COL
} tsplib_edge_weight_format;

struct tsplib_edge_type {
	char *str;
	size_t len;
	tsplib_edge_weight_type type;
};

struct tsplib_data_struct {
	char *name;
	char **comments;

	tsplib_type type;

	union {
		struct {
			unsigned int dimension;
			tsplib_edge_weight_type edge_weight_type;
			struct tsplib_node_coord_struct *node_coords;
			unsigned int *distance_map;
		} tsp;
	} u;
};

struct tsplib_tsp_struct {
	char *name;

	char **comments;

	unsigned int dimension;

	tsplib_edge_weight_type edge_weight_type;

	struct tsplib_node_coord_struct *node_coords;

	unsigned int *distance_map;
};


class tsplib {
public:
	tsplib();
	virtual ~tsplib();
	struct tsplib_tsp_struct *tsplib_read_tsp(FILE *file);
//private:
	struct tsplib_edge_type *tsplib_edge_weight_type_strings;
	void tsplib_tsp_construct_distance_map(struct tsplib_tsp_struct *tsp);
	unsigned int geom_distance_func(struct tsplib_node_coord_struct a, struct tsplib_node_coord_struct b);
	unsigned int euc_2d_distance_func(struct tsplib_node_coord_struct a, struct tsplib_node_coord_struct b);
	tsplib_edge_weight_type tsplib_str_to_edge_weight_type(char *type_str, size_t type_str_len);
	void tsplib_tsp_free(struct tsplib_tsp_struct *tsp);
	struct tsplib_tsp_struct *tsplib_tsp_new(char *name, size_t name_len, unsigned int dimension, tsplib_edge_weight_type edge_weight_type);
};

typedef
unsigned int
(tsplib::*distance_func_type)(struct tsplib_node_coord_struct a, struct tsplib_node_coord_struct b);


#endif /* TSPLIB_H_ */
