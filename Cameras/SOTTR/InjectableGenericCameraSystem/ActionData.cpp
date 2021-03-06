////////////////////////////////////////////////////////////////////////////////////////////////////////
// Part of Injectable Generic Camera System
// Copyright(c) 2019, Frans Bouma
// All rights reserved.
// https://github.com/FransBouma/InjectableGenericCameraSystem
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
//  * Redistributions of source code must retain the above copyright notice, this
//	  list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and / or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ActionData.h"
#include "Utils.h"

using namespace std;

namespace IGCS
{
	ActionData::ActionData(string name, int keyCode, bool altRequired, bool ctrlRequired, bool shiftRequired, bool available)
		: _name{ name }, _keyCode{ keyCode }, _altRequired{ altRequired }, _ctrlRequired{ ctrlRequired }, _shiftRequired{ shiftRequired },
		  _available {available}
	{
	}

	ActionData::~ActionData() {}

	// altCtrlOptional is only effective for actions which don't have alt/ctrl as a required key. Actions which do have one or more of these
	// keys as required, will ignore altCtrlOptional and always test for these keys. 
	bool ActionData::isActive(bool altCtrlOptional)
	{
		bool toReturn = (_available && Utils::keyDown(_keyCode)) && (_shiftRequired== Utils::shiftPressed());
		if((_altRequired || _ctrlRequired) || !altCtrlOptional)
		{
			toReturn = toReturn && (Utils::altPressed() == _altRequired) && (Utils::ctrlPressed() == _ctrlRequired);
		}
		return toReturn;
	}

	void ActionData::setKeyCode(int newKeyCode)
	{
		// if we have a keycode set and this is a different one, we will reset alt/ctrl/shift key requirements as it's a different key altogether.
		if (_keyCode > 0 && newKeyCode > 0 && newKeyCode != _keyCode)
		{
			clear();
		}
		_keyCode = newKeyCode;
	}

	void ActionData::clear()
	{
		_altRequired = false;
		_ctrlRequired = false;
		_shiftRequired = false;
		_keyCode = 0;
	}

	void ActionData::update(uint8_t newKeyCode, bool altRequired, bool ctrlRequired, bool shiftRequired)
	{
		_keyCode = (int)newKeyCode;
		_altRequired = altRequired;
		_ctrlRequired = ctrlRequired;
		_shiftRequired = shiftRequired;
	}
}