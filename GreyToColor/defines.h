#ifndef DEFINES_H
#define DEFINES_H

// Size of different elements on Main Window
// Size of Main Window
#define X_WINDOW				300
#define Y_WINDOW				300
#define W_WINDOW				906
#define H_WINDOW				420

// Offsets for images on Main Window
#define X_FIRST_IMG_OFFSET		3
#define Y_IMG_OFFSET			25

// Size of images
#define W_IMG					300
#define H_IMG					300

// Offsets for buttons on Main Window
#define Y_BUTT_OFFSET			5
#define X_FIRST_BUTT_OFFSET		60

// Size of buttons
#define W_BUTT					180
#define H_1LINE_BUTT			40
#define H_2LINE_BUTT			60
#define H_3LINE_BUTT			80

// Size of line SKO
#define W_LINE_SKO				140
#define H_LINE_SKO				30


// All menus
#define MENU_FILE				tr("File")
#define MENU_COLORIZATION		tr("Colorization")
#define MENU_DATABASE			tr("Image Database")

// MENU_FILE has this actions
#define ACTION_OPEN_GRAY		tr("Open gray image...")
#define ACTION_OPEN_COLOR		tr("Open color image...")
#define ACTION_EXIT				tr("Exit")

// MENU_COLORIZATION has this actions
#define ACTION_MW_SIMPLE		tr("Method Walsh: Simple")
#define ACTION_MW_NEIGHBOR		tr("Method Walsh: Neighbor")

// MENU_DATABASE has this actions
#define ACTION_ADD_NEW_PICS_IDB	tr("Add new pictures to database...")
#define ACTION_UPDATE_IDB		tr("Update database...")

// Names of buttons on Main window
#define BUTTON_GREY_IMG			tr("Load grey\nimage")
#define BUTTON_COLOR_IMG		tr("Load color\nimage")
#define BUTTON_START			tr("Colorize")
#define BUTTON_COLOR_IDB_IMG	tr("Load color\nimage\nfrom database")

// Label names
#define LABEL_SKO				tr("SKO:")

// Type of images
#define TARGET					0
#define RESULT					1
#define ORIGINAL				2
#define DATABASE				3

// Names of mass dimensions
#define Lab						0
#define lAb						1
#define laB						2
#define SKO						3
#define COL						4

#define FIRST_PASSPORT			0
#define LAST_PASSPORT			3

#define ERROR -1

#define PROJECT_IMG_PATH		"/img/"
#define PROJECT_DB_NAME			"/idb/idb.sqlite"

#endif // DEFINES_H
