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
#include "mainMenu.hpp"
#include "stringUtils.hpp"

#include <3ds.h>
#include <dirent.h>

bool exiting = false; // Tell, if we should exit.
touchPosition touch;

/* If Button Position pressed -> Do something. */
bool buttonTouch(touchPosition touch, Button button) {
	if (touch.px >= button.X && touch.px <= (button.X + button.XSize) && touch.py >= button.Y && touch.py <= (button.Y + button.YSize)) return true;
	else return false;
}

/* Initialize the services. */
static void init() {
	romfsInit();
	gfxInitDefault();
	Gui::init();
}

/* Deinitialize all services. */
static void exit() {
	Gui::exit();
	gfxExit();
	romfsExit();
}

int main() {
	init();
	Gui::setScreen(std::make_unique<MainMenu>(), false, true);

	/* Create directories, if not existent. */
	mkdir("sdmc:/3ds", 0777); // For DSP dump
	mkdir("sdmc:/3ds/HappyHomeEditor", 0777); // main Path.
	mkdir("sdmc:/3ds/HappyHomeEditor/Backups", 0777); // Backups path.

	while(aptMainLoop() && !exiting) {
		u32 hDown = hidKeysDown();
		hidScanInput();
		hidTouchRead(&touch);

		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, TRANSPARENT);
		C2D_TargetClear(Bottom, TRANSPARENT);
		Gui::DrawScreen(true);
		Gui::ScreenLogic(hDown, hidKeysHeld(), touch, false, true);
		C3D_FrameEnd(0);
	}

	exit();
}