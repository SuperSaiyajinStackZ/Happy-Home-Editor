/*
*   This file is part of Happy-Home-Editor
*   Copyright (C) 2020 RedShyGuy, SuperSaiyajinStackZ
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "editor.hpp"
#include "overlay.hpp"
#include "Sav.hpp"
#include "screenCommon.hpp"

std::unique_ptr<Sav> save;
static std::string SaveFile;
bool changes = false;

bool Editor::loadSave() {
	save = nullptr;
	FILE* in = fopen(this->saveName.c_str(), "rb");
	if (in) {
		fseek(in, 0, SEEK_END);
		u32 size = ftell(in);
		fseek(in, 0, SEEK_SET);
		std::shared_ptr<u8[]> saveData = std::shared_ptr<u8[]>(new u8[size]);
		fread(saveData.get(), 1, size, in);
		fclose(in);
		save = Sav::getSave(saveData, size);
	}

	if (!save) {
		return false;
	}

	CoreUtils::createBackup(); // Create backup there.
	
	return true;
}

void Editor::SaveInitialize() {
	this->saveName = Overlays::SelectFile({"dat"}, "sdmc:/3ds/HappyHomeEditor/", "Select a savefile.");

	if (this->saveName != "") {
		if (!loadSave()) {

		} else {
			loadState = SaveState::Loaded;
		}
	} else {
		Gui::screenBack(false);
	}
}


void Editor::Draw(void) const {
	if (loadState == SaveState::Loaded) {
		GFX::DrawTop();
		Gui::DrawStringCentered(0, -2, 0.8f, WHITE, "Happy Home Editor - Editor", 395, 0);
		GFX::DrawBottom();
	}
}

void Editor::Saving() {
	if (!save->changesMade()) {
		return;
	}

	save->Finish();
	FILE* out = fopen(this->saveName.c_str(), "rb+");
	fwrite(save->rawData().get(), 1, save->getLength(), out);
	fclose(out);
	hasSaved = true;
}

void Editor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (loadState == SaveState::Loaded) {
		/* Navigation. */
		if (hDown & KEY_UP) {
			if (this->Selection > 0) this->Selection--;
		}
		
		if (hDown & KEY_DOWN) {
			if (this->Selection < 2) this->Selection++;
		}
		
		if (hDown & KEY_B) {
			Gui::screenBack(false);
		}
		
	} else {
		SaveInitialize(); // Display Browse.
	}
}