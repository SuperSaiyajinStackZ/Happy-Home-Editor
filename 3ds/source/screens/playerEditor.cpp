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


#include "playerEditor.hpp"
#include "Sav.hpp"
#include "screenCommon.hpp"
#include "utils.hpp"

extern std::unique_ptr<Sav> save;

void PlayerEditor::Draw(void) const {
	if (this->mode == 0) this->DrawSub();
	else if (this->mode == 1) this->DrawPattern();
}

void PlayerEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->mode == 0) this->SubLogic(hDown, hHeld, touch);
	else if (this->mode == 1) this->PatternLogic(hDown, hHeld, touch);
}

void PlayerEditor::DrawSub(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, -2, 0.8f, WHITE, "Happy Home Editor - Player Editor", 395, 0);
	GFX::DrawBottom();

	for (int i = 0; i < 1; i++) {
		GFX::DrawButton(this->mainButtons[i]);
	}
}

void PlayerEditor::SubLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack(false);
		return;
	}

	if (hDown & KEY_A) {
		/* Pattern Viewer. */
		C3D_FrameEnd(0);

		for (int i = 0; i < 15; i++) {
			this->ptrn[i] = save->player()->pattern(i);

			if (this->ptrn[i]) {
				this->ptrnImage[i] = this->ptrn[i]->image(0);
				if (this->ptrnImage[i]) {
					this->pattern[i] = CoreUtils::patternImage(this->ptrnImage[i]);
					this->loaded[i] = true;
				}
			}
		}

		this->mode = 1;
		this->selection = 0;
	}
}

void PlayerEditor::DrawPattern(void) const {
	GFX::DrawTop();
	GFX::DrawBottom();

	for (int i = 0; i < 15; i++) {
		if (this->pattern[i].tex && this->loaded[i]) {
			C2D_DrawImageAt(this->pattern[i], PatternPos[i].x, PatternPos[i].y, 0.5f, nullptr, 1.5f, 1.5f);
		}
	}
}

void PlayerEditor::PatternLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		/* Unload. */
		C3D_FrameEnd(0);

		for (int i = 0; i < 15; i++) {
			if (this->loaded[i]) C2DUtils::C2D_ImageDelete(this->pattern[i]);
		}

		this->selection = 0;
		this->mode = 0;
	}
}