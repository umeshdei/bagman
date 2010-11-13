/*
 * test.h
 *
 *  Created on: 13-11-2010
 *      Author: qba
 */

#ifndef TEST_H_
#define TEST_H_

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


#endif /* TEST_H_ */
