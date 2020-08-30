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

#include "common.hpp"
#include "editor.hpp"
#include "mainMenu.hpp"
#include "offsets.hpp"
#include "overlay.hpp"
#include "Sav.hpp"

extern bool exiting;

extern std::unique_ptr<Sav> save;
#define SAV_PATH "sdmc:/3ds/Checkpoint/saves/0x014F2 Happy Home Designer/HHD/takumi.dat" // Define your path here for testing.

static void doStuff() {
	/* Here we open the file and get the save. */
	save = nullptr;
	FILE* in = fopen(SAV_PATH, "rb");
	if (in) {
		fseek(in, 0, SEEK_END);
		u32 size = ftell(in);
		fseek(in, 0, SEEK_SET);
		std::shared_ptr<u8[]> saveData = std::shared_ptr<u8[]>(new u8[size]);
		fread(saveData.get(), 1, size, in);
		fclose(in);
		save = Sav::getSave(saveData, size);
	}

	/* Could not open file or save invalid, exit. */
	if (!save) {
		exiting = true;
		return;
	}

	/* Your testing stuff here. */
	save->player()->unlockAll();

	/* And now we update the checksum at the end and write to file. */
	save->Finish();
	FILE* out = fopen(SAV_PATH, "rb+");
	fwrite(save->rawData().get(), 1, save->getLength(), out);
	fclose(out);

	exiting = true;
}

MainMenu::MainMenu() {
	//doStuff();
}

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.8f, WHITE, "Happy Home Editor - MainMenu");
	GFX::DrawBottom();
}

void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_START) exiting = true;

	if (hDown & KEY_X) {
		Gui::setScreen(std::make_unique<Editor>(), false, true);
	}
}