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
#include "gfx.hpp"

void GFX::DrawTop() {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 25, C2D_Color32(0, 0, 128, 255));
	Gui::Draw_Rect(0, 25, 400, 190, C2D_Color32(0, 0, 170, 255));
	Gui::Draw_Rect(0, 215, 400, 25, C2D_Color32(0, 0, 128, 255));
}

void GFX::DrawBottom() {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 25, C2D_Color32(0, 0, 128, 255));
	Gui::Draw_Rect(0, 25, 320, 190, C2D_Color32(0, 0, 170, 255));
	Gui::Draw_Rect(0, 215, 320, 25, C2D_Color32(0, 0, 128, 255));
}

void GFX::DrawFileBrowseBG(bool isTop) {
	if (isTop) {
		Gui::ScreenDraw(Top);
		Gui::Draw_Rect(0, 0, 400, 27, C2D_Color32(0, 0, 128, 255));
		Gui::Draw_Rect(0, 27, 400, 31, C2D_Color32(0, 0, 190, 255));
		Gui::Draw_Rect(0, 58, 400, 31, C2D_Color32(0, 0, 190, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 89, 400, 31, C2D_Color32(0, 0, 190, 255));
		Gui::Draw_Rect(0, 120, 400, 31, C2D_Color32(0, 0, 190, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 151, 400, 31, C2D_Color32(0, 0, 190, 255));
		Gui::Draw_Rect(0, 182, 400, 31, C2D_Color32(0, 0, 190, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 213, 400, 27, C2D_Color32(0, 0, 128, 255));
	} else {
		Gui::ScreenDraw(Bottom);
		Gui::Draw_Rect(0, 0, 320, 27, C2D_Color32(0, 0, 128, 255));
		Gui::Draw_Rect(0, 27, 320, 31, C2D_Color32(0, 0, 190, 255));
		Gui::Draw_Rect(0, 58, 320, 31, C2D_Color32(0, 0, 190, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 89, 320, 31, C2D_Color32(0, 0, 190, 255));
		Gui::Draw_Rect(0, 120, 320, 31, C2D_Color32(0, 0, 190, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 151, 320, 31, C2D_Color32(0, 0, 190, 255));
		Gui::Draw_Rect(0, 182, 320, 31, C2D_Color32(0, 0, 190, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 213, 320, 27, C2D_Color32(0, 0, 128, 255));
	}
}