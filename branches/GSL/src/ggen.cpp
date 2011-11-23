/*

    This file is part of GeoGen.

    GeoGen is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    GeoGen is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GeoGen.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <assert.h>

#include "ggen_support.h"
#include "ggen_amplitudes.h"
#include "ggen_data_1d.h"
#include "ggen_data_2d.h"

#include "ggen.h"

namespace GeoGen{
	Generator* Generator::instance = NULL;

	Generator::Generator(){
		assert(Generator::instance == NULL);

		Generator::instance = this;

		this->status = GGEN_NO_SCRIPT;

		/* Default map constraints to max values (given int is unsigned, -1 overflows to its max value) */	
		this->max_map_size = -1;
		this->max_map_count = -1;

		this->message_callback = NULL;
		this->return_callback = NULL;
		this->progress_callback = NULL;

		this->max_progress = this->current_progress = 0;
	}

	Generator::~Generator(){
		Generator::instance = NULL;
	}

	Generator* Generator::GetInstance(){
		return Generator::instance;
	}

	const Status Generator::GetStatus(){
		return this->status;
	}

	const void Generator::ThrowMessage(const String& message, MessageLevel level, int line, int column){
	
		if(message_callback != NULL){
			this->message_callback(message, level, line, column);
		}
		else{
			switch(level){
				case GGEN_MESSAGE:
					if(line != -1) GGen_Cout << "GGen Message: " << message << " on line " << line << "\n" << flush;
					else GGen_Cout << "GGen Message: " << message <<  "\n";
					break;
				case GGEN_NOTICE:
					if(line != -1) GGen_Cout << "GGen Notice: " << message << " on line " << line << "\n" << flush;
					else GGen_Cout << "GGen Notice: " << message <<  "\n";
					break;
				case GGEN_WARNING:
					if(line != -1) GGen_Cout << "GGen Warning: " << message << " on line " << line << "\n" << flush;
					else GGen_Cout << "GGen Warning: " << message <<  "\n";
					break;
				case GGEN_ERROR:
					if(line != -1) GGen_Cout << "GGen Error: " << message << " on line " << line << "\n" << flush;
					else GGen_Cout << "GGen Error: " << message <<  "\n" << flush;
					break;
			}
		}

	}

	void Generator::SetMessageCallback( void (*message_callback) (const String& message, MessageLevel, int line, int column) ){
		this->message_callback = message_callback;
	}

	void Generator::SetReturnCallback( void (*return_callback) (const String& name, const int16* map, int width, int height) ){
		this->return_callback = return_callback;
	}

	void Generator::SetProgressCallback( void (*progress_callback) (int current_progress, int max_progress) ){
		this->progress_callback = progress_callback;
	}

	vector<ScriptArg>* Generator::LoadArgs(){
		assert(this->status == GGEN_SCRIPT_LOADED);

		this->args.clear();

		if(GetInfoInt(StaticString("args")) == -1) return NULL;

		this->status = GGEN_READY_TO_GENERATE;

		return &this->args;
	}

	void Generator::SetMaxMapSize(Size size){
		this->max_map_size = size;
	}

	void Generator::SetMaxMapCount(uint16 count){
		this->max_map_count = count;
	}

	Size Generator::GetMaxMapSize(){
		return Generator::GetInstance()->max_map_size;
	}

	uint16 Generator::GetMaxMapCount(){
		return Generator::GetInstance()->max_map_count;
	}

	void Generator::SetSeed(unsigned seed){
		ScriptAssert(Generator::GetInstance()->GetStatus() != GGEN_GENERATING);
		ScriptAssert(Generator::GetInstance()->GetStatus() != GGEN_LOADING_MAP_INFO);

		srand(seed);
	}
}