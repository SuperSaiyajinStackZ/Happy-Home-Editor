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
#include "msg.hpp"
#include "structs.hpp"

#include <vector>

static const std::vector<Button> promptBtn = {
	{10, 100, 140, 40, "Yes"},
	{170, 100, 140, 40, "No"},
	{100, 100, 140, 40, "OK"}
};

extern touchPosition touch;
extern bool buttonTouch(touchPosition touch, Button button);

/* Display a Message, which needs to be confirmed with A/B. */
bool Msg::promptMsg(std::string promptMsg) {
	s32 selection = 0;
	while(1) {
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		GFX::DrawTop();
		Gui::Draw_Rect(0, 80, 400, 80, C2D_Color32(0, 128, 128, 255));
		Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.7f, promptMsg))/2, 0.7f, WHITE, promptMsg, 390, 70);
		GFX::DrawBottom();
		
		for (int i = 0; i < 2; i++) {
			GFX::DrawButton(promptBtn[i]);
		}

		C3D_FrameEnd(0);

		/* Selection part. */
		gspWaitForVBlank();
		hidScanInput();
		hidTouchRead(&touch);

		if (hidKeysDown() & KEY_LEFT) {
			selection = 0;
		}
		
		if(hidKeysDown() & KEY_RIGHT) {
			selection = 1;
		}

		if (hidKeysDown() & KEY_A) {
			if (selection == 0) {
				return true;
			} else {
				return false;
			}
		}

		if (hidKeysDown() & KEY_TOUCH && buttonTouch(touch, promptBtn[0])) {
			return true;
		}

		if (hidKeysDown() & KEY_TOUCH && buttonTouch(touch, promptBtn[1])) {
			return false;
		}
	}
}

/* Displays a Warn Message. */
void Msg::DisplayWarnMsg(std::string Text) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
	GFX::DrawTop();
	Gui::Draw_Rect(0, 80, 400, 80, C2D_Color32(0, 128, 128, 255));
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.8f, Text))/2, 0.8f, WHITE, Text, 395, 70);
	GFX::DrawBottom();
	C3D_FrameEnd(0);

	for (int i = 0; i < 60*2; i++) {
		gspWaitForVBlank();
	}
}

/* Displays a Warn Message. This is mostly be used for things with more text. */
void Msg::DisplayWarnMsg2(std::string Text) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
	GFX::DrawTop();
	Gui::Draw_Rect(0, 80, 400, 80, C2D_Color32(0, 128, 128, 255));
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.7f, Text))/2, 0.7f, WHITE, Text, 395, 70);
	GFX::DrawBottom();
	C3D_FrameEnd(0);

	for (int i = 0; i < 60*2; i++) {
		gspWaitForVBlank();
	}
}

/* Display a Message, which can be skipped with A. */
void Msg::DisplayWaitMsg(std::string waitMsg, ...) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
	GFX::DrawTop();
	Gui::Draw_Rect(0, 80, 400, 80, C2D_Color32(0, 128, 128, 255));
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.7f, waitMsg))/2, 0.7f, WHITE, waitMsg, 390, 70);
	Gui::DrawStringCentered(0, 214, 0.8f, WHITE, "Press \uE000 to continue.", 390);
	GFX::DrawBottom();
	GFX::DrawButton(promptBtn[2]);
	C3D_FrameEnd(0);

	while(1) {
		gspWaitForVBlank();
		hidScanInput();
		hidTouchRead(&touch);
		if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH && buttonTouch(touch, promptBtn[2]))) break;
	}
}

void Msg::NotImplementedYet(void) { Msg::DisplayWaitMsg("This is not implemented yet."); }