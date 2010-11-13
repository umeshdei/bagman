/*
 * bagman.h
 *
 *  Created on: 11-11-2010
 *      Author: qba
 */

#ifndef BAGMAN_H_
#define BAGMAN_H_

#define GREEDY 0x01
#define STEEPEST 0x02
#define RANDOM 0x04
#define OWNSOLUTION 0x08

#include <time.h>
#include <stdlib.h>

#include <stdio.h>

/* ========================================================================== */
/* Defines */

/* ========================================================================== */
/* Types */

typedef enum {
	TSP
} tsplib_type;

struct tsplib_node_coord_struct {
	double x;
	double y;
};

typedef enum {
	UNKNOWN = -1,
	EXPLICIT,
	EUC_2D,
	EUC_3D,
	MAX_2D,
	MAX_3D,
	MAN_2D,
	MAN_3D,
	CEIL_2D,
	GEOM,
	ATT,
	XRAY_1,
	XRAY_2,
	SPECIAL
} tsplib_edge_weight_type;


typedef enum {
	FUNCTION,
	FULL_MATRIX,
	UPPER_ROW,
	LOWER_ROW,
	UPPER_DIAG_ROW,
	LOWER_DIAG_ROW,
	UPPER_COL,
	LOWER_COL,
	UPPER_DIAG_COL,
	LOWER_DIAG_COL
} tsplib_edge_weight_format;

struct {
	char *str;
	size_t len;
	tsplib_edge_weight_type type;
} tsplib_edge_weight_type_strings[] = {
	{ "EXPLICIT", 8, EXPLICIT},
	{ "EUC_2D", 6, EUC_2D},
	{ "EUC_3D", 6, EUC_3D},
	{ "MAX_2D", 6, MAX_2D},
	{ "MAX_3D", 6, MAX_3D},
	{ "MAN_2D", 6, MAN_2D},
	{ "MAN_3D", 6, MAN_3D},
	{ "CEIL_2D", 7, CEIL_2D},
	{ "GEOM", 4, GEOM},
	{ "ATT", 3, ATT},
	{ "XRAY_1", 6, XRAY_1},
	{ "XRAY_2", 6, XRAY_2},
	{ "SPECIAL", 7, SPECIAL},
	{ NULL, 0, UNKNOWN}
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

/* ========================================================================== */
/* Extern Globals */

/* ========================================================================== */
/* Macros and Prototypes */

/* ================================== */
/* Lifecycle functions */

struct tsplib_tsp_struct *
tsplib_tsp_new
	(char *name,
	 size_t name_len,
	 unsigned int dimension,
	 tsplib_edge_weight_type edge_weight_type);

void
tsplib_tsp_free
	(struct tsplib_tsp_struct *tsp);

void
tsplib_tsp_construct_distance_map
	(struct tsplib_tsp_struct *tsp);

tsplib_edge_weight_type
tsplib_str_to_edge_weight_type
	(char *type_str,
	 size_t type_str_len);
/* ================================== */
/* IO functions */

//struct tsplib_tsp_struct *
//tsplib_read_tsp
//	(FILE *file);

struct tsplib_tsp_struct *
tsplib_read_striped_tsp
	(FILE *file);

//void
//tsplib_write_tsp
//	(struct tsplib_tsp_struct *tsp,
//	 FILE *file);




#endif /* BAGMAN_H_ */
