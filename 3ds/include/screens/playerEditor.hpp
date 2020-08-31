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

#ifndef _HAPPY_HOME_EDITOR_PLAYER_EDITOR_HPP
#define _HAPPY_HOME_EDITOR_PLAYER_EDITOR_HPP

#include "common.hpp"
#include "coreUtils.hpp"
#include "Pattern.hpp"
#include "PatternImage.hpp"
#include <citro2d.h>
#include <vector>

class PlayerEditor : public Screen {
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	PlayerEditor() { }
private:
	const std::vector<Button> mainButtons = {
		{95, 34, 130, 48, "Pattern"}
	};

	/* 15 Pattern each page. */
	 const std::vector<Structs::ButtonPos> PatternPos = {
		{17, 40, 48, 48},
		{17, 100, 48, 48},
		{17, 160, 48, 48},

		{77, 40, 48, 48},
		{77, 100, 48, 48},
		{77, 160, 48, 48},

		{137, 40, 48, 48},
		{137, 100, 48, 48},
		{137, 160, 48, 48},

		{197, 40, 48, 48},
		{197, 100, 48, 48},
		{197, 160, 48, 48},

		{257, 40, 48, 48},	
		{257, 100, 48, 48},
		{257, 160, 48, 48}
	};

	int mode = 0;
	int selection = 0;

	void DrawSub(void) const;
	void SubLogic(u32 hDown, u32 hHeld, touchPosition touch);

	void DrawPattern(void) const;
	void PatternLogic(u32 hDown, u32 hHeld, touchPosition touch);

	std::unique_ptr<Pattern> ptrn[15];
	std::unique_ptr<PatternImage> ptrnImage[15];
	C2D_Image pattern[15]; // 15 per page.
	bool loaded[15] = {false};
};

#endif