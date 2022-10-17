#include "../nmea/parser_types.h"
#include "gprmb.h"
#include "parse.h"

int
init(nmea_parser_s *parser)
{
	/* Declare what sentence type to parse */
	NMEA_PARSER_TYPE(parser, NMEA_GPRMB);
	NMEA_PARSER_PREFIX(parser, "GPRMB");
	return 0;
}

int
allocate_data(nmea_parser_s *parser)
{
	parser->data = malloc(sizeof (nmea_gprmb_s));
	if (NULL == parser->data) {
		return -1;
	}

	return 0;
}

int
set_default(nmea_parser_s *parser)
{
	memset(parser->data, 0, sizeof (nmea_gprmb_s));
	return 0;
}

int
free_data(nmea_s *data)
{
	free(data);
	return 0;
}

int
parse(nmea_parser_s *parser, char *value, int val_index)
{
	nmea_gprmb_s *data = (nmea_gprmb_s *) parser->data;

	switch (val_index) {

	case NMEA_GPRMB_STATUS:
		/* Parse status */
		if (*value == 'A') {
			data->valid = true;
		} else if (*value == 'V') {
			data->valid = false;
		} else {
			return -1;
		}
		break;
		
	case NMEA_GPRMB_XTE_NM:
		/* Parse the Cross Track Error (XTE), nautical miles */
		data->xte_nm = strtod(value, NULL);
		break;
		
	case NMEA_GPRMB_STEERING_DIR:
		/* Parse the Steering Direction, degrees */
		data->steering = strtod(value, NULL);
		break;
	
	case NMEA_GPRMB_FROM_WP_ID:
		strncpy(data->wp_from_id, value, NMEA_GPRMB_TEXT_SIZE);
		data->wp_from_id[NMEA_GPRMB_TEXT_SIZE - 1] = '\0';
		break;
		
	case NMEA_GPRMB_TO_WP_ID:
		strncpy(data->wp_to_id, value, NMEA_GPRMB_TEXT_SIZE);
		data->wp_to_id[NMEA_GPRMB_TEXT_SIZE - 1] = '\0';
		break;
	
	case NMEA_GPRMB_DEST_LATITUDE:
		/* Parse destination latitude */
		if (-1 == nmea_position_parse(value, &data->to_latitude)) {
			return -1;
		}
		break;

	case NMEA_GPRMB_DEST_LATITUDE_CARDINAL:
		/* Parse detination cardinal direction */
		data->to_latitude.cardinal = nmea_cardinal_direction_parse(value);
		if (NMEA_CARDINAL_DIR_UNKNOWN == data->to_latitude.cardinal) {
			return -1;
		}
		break;
		
	case NMEA_GPRMB_DEST_LONGITUDE:
		/* Parse destination longitude */
		if (-1 == nmea_position_parse(value, &data->to_longitude)) {
			return -1;
		}
		break;
		
	case NMEA_GPRMB_DEST_LONGITUDE_CARDINAL:
		/* Parse destinationcardinal direction */
		data->to_longitude.cardinal = nmea_cardinal_direction_parse(value);
		if (NMEA_CARDINAL_DIR_UNKNOWN == data->to_longitude.cardinal) {
			return -1;
		}
		break;
		
	case NMEA_GPRMB_RANGE_TO_DEST:
		/* Parse the Range to destination, nautical miles */
		data->range_to_dest = strtod(value, NULL);
		break;
		
	case NMEA_GPRMB_BEARING_TO_DEST:
		/* Parse the Bearing to destination, degrees */
		data->bearing_to_dest = strtod(value, NULL);
		break;
		
	case NMEA_GPRMB_DEST_CLOSING_VEL:
		/* Parse Destination Closing Velocity, knots */
		data->closing_velocity = strtod(value, NULL);
		break;
		
	case NMEA_GPRMB_ARRIVAL_STATUS:
		/* Parse status */
		if (*value == 'A') {
			data->valid = true;
		} else if (*value == 'V') {
			data->valid = false;
		} else {
			return -1;
		}
		break;
		
	case NMEA_GPRMB_VALID_STATUS:
		/* Parse status */
		if (*value == 'A') {
			data->valid = true;
		} else if (*value == 'V') {
			data->valid = false;
		} else {
			return -1;
		}
		break;

	default:
		break;
	}

	return 0;
}
