// Includes:

#include "pirates.h"
#include "mario.h"
#include "underworld.h"

// Struct:

typedef struct {
	int size;
	int *notes;
	int *duration;
	char name[11];
} song;

// Functions:

void songList(song musics[]) {
	song pirates;
	pirates.size = sizeof(piratesNotes)/sizeof(piratesNotes[0]);
	pirates.notes = &piratesNotes;
	pirates.duration = &piratesDuration;
	sprintf(pirates.name, piratesName);

	song mario;
	mario.size = sizeof(marioNotes)/sizeof(marioNotes[0]);
	mario.notes = &marioNotes;
	mario.duration = &marioDuration;
	sprintf(mario.name, marioName);

	song marioUnderworld;
	marioUnderworld.size = sizeof(underworldNotes)/sizeof(underworldNotes[0]);
	marioUnderworld.notes = &underworldNotes;
	marioUnderworld.duration = &underworldDuration;
	sprintf(marioUnderworld.name, underworldName);

	musics[0] = pirates;
	musics[1] = mario;
	musics[2] = marioUnderworld;
}