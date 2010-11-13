/**
 * tsplib.h
 *
 * Copyright (C) 2003 Crutcher Dunnavant <crutcher@dunnavant.com>
 *
 * \if maintainer \code
 * $Id: c_header_file.h,v 1.6 2002/10/15 22:03:14 crutcher Exp $
 * Doc-State:	NEW
 * Code-State:	NEW
 * \endcode \endif
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ========================================================================== */
/* Multi-include wrapper */
#ifndef __TSPLIB_H__
#define __TSPLIB_H__

/* ========================================================================== */
/* Includes */

/* ========================================================================== */
/* Standard Includes */

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

struct tsplib_tsp_struct *
tsplib_read_tsp
	(FILE *file);

void
tsplib_write_tsp
	(struct tsplib_tsp_struct *tsp,
	 FILE *file);

/* ========================================================================== */
/* Inlined Functions */

/* ========================================================================== */
/* Multi-include wrapper */
#endif/*__TSPLIB_H__*/
