#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	_param=new Param();

	string folder="sound/";
	string frontname_="key/Kb_FM1_";
	string keyname[13]={"Do","Do#","Re","Re#","Mi",
		"Fa","Fa#","So","So#","La","La#","Ti","HiDo"};
	for(int i=0;i<13;++i){
		ofSoundPlayer p_;
		p_.load(folder+frontname_+keyname[i]+".wav");
		_sound_note.push_back(p_);
	}

	string hitname[2]={"hit/hihat","hit/slap"};
	for(int i=0;i<2;++i){
		ofSoundPlayer p_;
		p_.load(folder+hitname[i]+".wav");
		_sound_hit.push_back(p_);
	}

	string bellname[2]={"bell/bell1","bell/bell2"};
	for(int i=0;i<2;++i){
		ofSoundPlayer p_;
		p_.load(folder+bellname[i]+".wav");
		_sound_bell.push_back(p_);
	}
	


	_serial.listDevices();
	_serial.setup(0,9600);
	
	_mode=SMODE::KEY;

}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
	updateSerial();

}

void ofApp::updateSerial(){
	
	if(_serial.available()){

		vector<string> val=readSerialString(_serial,'#');
		if(val.size()<1) return;
		
		cout<<val[0]<<"- "<<val[1]<<endl;

		int p_=ofToInt(val[1]);
		if(val[0]=="L"|| val[0]=="R"){
			
			switch(_mode){
				case KEY:
					playNote();
					break;
				case HIT:
					playHit(val[0]);
					break;
				case BELL:
					playBell(val[0]);
					break;
			}
		}else if(val[0]=="prev"){
			if(_mode==SMODE::KEY) prevSong();
		}else if(val[0]=="next"){
			if(_mode==SMODE::KEY) nextSong();
		}else if(val[0]=="mode"){
			setMode(ofToInt(val[1]));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key>'0' && key<'9'){
		_sound_note[key-'1'].play();
	}
	switch(key){
		case 'n':
			nextSong();
			break;
		case 'p':
			prevSong();
			break;
		case 'h':
			setMode(1);
			break;
		case 'k':
			setMode(0);
			break;
		case 'b':
			setMode(2);
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::changeSong(int index_){
	if(index_<0 || index_>=_param->_msong) return;
	_index_song=index_;
	_index_note=0;

}

void ofApp::playNote(){
	playNote(_param->_song[_index_song][_index_note]);
	_index_note++;

	if(_index_note>=_param->_song[_index_song].size()) nextSong();
}

void ofApp::playNote(PNote note_){
	
	// TODO: different level
	int i=note_._id+12*(note_._lvl-4);
	if(i<_sound_note.size()) _sound_note[i].play();
	//else
}

void ofApp::nextSong(){
	changeSong((_index_song+1)%_param->_msong);	
}
void ofApp::prevSong(){
	changeSong((_index_song-1+_param->_msong)%_param->_msong);
}

void ofApp::playHit(string side_){
	if(side_=="L")
			_sound_hit[0].play();
	else _sound_hit[1].play();
}

void ofApp::playBell(string side_){
	if(side_=="L")
		_sound_bell[0].play();
	else _sound_bell[1].play();
}


void ofApp::setMode(int set_){
	ofLog()<<"Set mode= "<<set_;
	_mode=SMODE(set_);	
}