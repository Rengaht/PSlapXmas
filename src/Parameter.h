#pragma once
#ifndef PARMAMETR_H
#define PARAMETER_H

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "PNote.h"

class Param{

	static Param* _instance;	
	
public:
	static string ParamFilePath;	
   
	
	int _msong;
	vector<vector<PNote>> _song;

	Param(){
		readParam();

	}
	static Param* GetInstance(){
		if(!_instance)
			_instance=new Param();
		return _instance;
	}
	void readParam(){

		_song.clear();		


		ofxXmlSettings _param;
		bool file_exist=true;
		if(_param.loadFile(ParamFilePath) ){
			ofLog()<<ParamFilePath<<" loaded!";
		}else{
			ofLog()<<"Unable to load xml"<<ParamFilePath;
			file_exist=false;
		}


	
		
        _msong=_param.getNumTags("SONG");
		ofLog()<<"found "<<_msong<<" song"<<endl;

		for(int i=0;i<_msong;++i){
			loadSongFile(_param.getValue("SONG","",i));
		}

		if(!file_exist) saveParameterFile();

	
	}

	void saveParameterFile(){


		ofxXmlSettings _param;
		_param.save(ParamFilePath);


	}
	void loadSongFile(string file_path_){
		
		ofxXmlSettings psong_;
		bool exist_=true;
		if(psong_.loadFile(file_path_)){
			ofLog()<<file_path_<<" loaded!";
		}else{
			ofLog()<<"Unable to load xml"<<file_path_;
			return;
		}
		psong_.pushTag("SONG");

		vector<PNote> song_;
		int mnote_=psong_.getNumTags("NOTE");
		for(int i=0;i<mnote_;++i){
			song_.push_back(PNote(psong_.getAttribute("NOTE","n","",i),
								  psong_.getAttribute("NOTE","lvl",4,i)));
		}

		_song.push_back(song_);

	}

};





#endif

