#ifndef INC_NMEA_GPRMB_H
#define INC_NMEA_GPRMB_H
#define NMEA_GPRMB_TEXT_SIZE 32

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <nmea.h>

typedef struct {
	nmea_s base;
	//bool active_status;
	double xte_nm;
	char steering;
	char wp_from_id[NMEA_GPRMB_TEXT_SIZE];
	char wp_to_id[NMEA_GPRMB_TEXT_SIZE];
	nmea_position to_longitude;
	char to_longitude_cardinal;
	nmea_position to_latitude;
	char to_latitude_cardinal;
	double range_to_dest;
	double bearing_to_dest;
	double closing_velocity;
	//bool arrival_status;
	//bool valid_status;
	bool valid;
} nmea_gprmb_s;

/* Value indexes */
#define NMEA_GPRMB_STATUS			0 // A = Active, V = Void
#define NMEA_GPRMB_XTE_NM			1 // Cross Track Error -Nautical Miles
#define NMEA_GPRMB_STEERING_DIR			2 // Direction to steer, L or R
#define NMEA_GPRMB_FROM_WP_ID			3 
#define NMEA_GPRMB_TO_WP_ID			4 
#define NMEA_GPRMB_DEST_LATITUDE		5
#define NMEA_GPRMB_DEST_LATITUDE_CARDINAL	6 // N or S
#define NMEA_GPRMB_DEST_LONGITUDE		7
#define NMEA_GPRMB_DEST_LONGITUDE_CARDINAL	8 // E or W
#define NMEA_GPRMB_RANGE_TO_DEST		9 // Range to destination in nautical miles
#define NMEA_GPRMB_BEARING_TO_DEST		10 // Bearing to destination in degrees True
#define NMEA_GPRMB_DEST_CLOSING_VEL		11 // Destination closing velocity in knots
#define NMEA_GPRMB_ARRIVAL_STATUS		12 // Arrival Status, A = Arrival Circle Entered
#define NMEA_GPRMB_VALID_STATUS			13 // Status A - Data Valid, V - Data Invalid, FAA mode indicator (NMEA 2.3 and later)
#endif  /* INC_NMEA_GPRMB_H */
