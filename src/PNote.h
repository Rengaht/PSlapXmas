#pragma once
#ifndef  PNOTE_H
#define PNOTE_H

class PNote{
	public:
		PNote(string name_,int lvl_){
			_id=getNoteId(name_);
			_lvl=lvl_;
		}
		int _id;
		int _lvl;
		static int getNoteId(string name_){
			if(name_=="C") return 0;
			if(name_=="C#") return 1;

			if(name_=="D") return 2;
			if(name_=="D#") return 3;
			
			if(name_=="E") return 4;

			if(name_=="F") return 5;
			if(name_=="F#") return 6;
			
			if(name_=="G") return 7;
			if(name_=="G#") return 8;

			if(name_=="A") return 9;
			if(name_=="A#") return 10;

			if(name_=="B") return 11;
			
		}
};


#endif // ! NOTE_H