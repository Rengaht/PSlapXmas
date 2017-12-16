#pragma once

#include "ofMain.h"
#include "StringUtil.h"
#include "Parameter.h"
#include "PNote.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		vector<ofSoundPlayer> _sound_note;
		vector<ofSoundPlayer> _sound_hit;
		vector<ofSoundPlayer> _sound_bell;

		ofSerial _serial;
		
		int _index_note;
		int _index_song;

		void updateSerial();

		void changeSong(int index_);
		Param* _param;
		
		void playNote();
		void playNote(PNote note_);

		void nextSong();
		void prevSong();

		enum SMODE{KEY,HIT,BELL};
		SMODE _mode;
		void setMode(int set_);

		void playHit(string side_);
		void playBell(string side_);

};
