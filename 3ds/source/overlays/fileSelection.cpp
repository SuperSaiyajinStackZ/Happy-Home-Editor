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
#include "fileBrowse.hpp"
#include "overlay.hpp"
#include <dirent.h>
#include <unistd.h>

// Draw the Top (File) browse.
static void DrawTop(uint Selection, std::vector<DirEntry> dirContents, const std::string Text) {
	std::string files;

	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, BLACK);
	C2D_TargetClear(Bottom, BLACK);

	GFX::DrawFileBrowseBG(true);
	Gui::DrawStringCentered(0, -2, 0.8f, WHITE, Text, 395, 0);
	Gui::DrawStringCentered(0, 215, 0.7f, WHITE, "Press START to refresh the filelist.", 395, 0);

	for (uint i = (Selection < 5) ? 0 : Selection - 5; i < dirContents.size() && i < ((Selection < 5) ? 6 : Selection + 1); i++) {
		if (i == Selection) files += "> " + dirContents[i].name + "\n\n";
		else files += dirContents[i].name + "\n\n";
	}

	for (uint i = 0; i < ((dirContents.size() < 6) ? 6 - dirContents.size() : 0); i++) {
		files += "\n\n";
	}

	Gui::DrawString(26, 32, 0.53f, WHITE, files, 360, 0);
}

static void DrawBottom() {
	GFX::DrawFileBrowseBG(false);
	C3D_FrameEnd(0);
}

std::string Overlays::SelectFile(const std::vector<std::string> fileType, const std::string initialPath, const std::string Text) {
	s32 selectedFile = 0;
	int keyRepeatDelay = 4;
	bool dirChanged = false;
	std::vector<DirEntry> dirContents;

	// Initial dir change.
	dirContents.clear();
	chdir(initialPath.c_str());
	std::vector<DirEntry> dirContentsTemp;
	getDirectoryContents(dirContentsTemp, fileType);
	for(uint i = 0; i < dirContentsTemp.size(); i++) {
		dirContents.push_back(dirContentsTemp[i]);
	}

	while (1) {
		// Screen draw part.
		DrawTop(selectedFile, dirContents, Text);
		DrawBottom();

		// The input part.
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hHeld = hidKeysHeld();
		if (keyRepeatDelay)	keyRepeatDelay--;

		// if directory changed -> Refresh it.
		if (dirChanged) {
			dirContents.clear();
			std::vector<DirEntry> dirContentsTemp;
			getDirectoryContents(dirContentsTemp, fileType);
			for(uint i = 0; i < dirContentsTemp.size(); i++) {
				dirContents.push_back(dirContentsTemp[i]);
			}

			dirChanged = false;
		}

		if (hDown & KEY_A) {
			if (dirContents[selectedFile].isDirectory) {
				chdir(dirContents[selectedFile].name.c_str());
				selectedFile = 0;
				dirChanged = true;
			} else {
				char path[PATH_MAX];
				getcwd(path, PATH_MAX);
				std::string output = path + dirContents[selectedFile].name;
				return output;
			}
		}

		if (hHeld & KEY_UP) {
			if (selectedFile > 0 && !keyRepeatDelay) {
				selectedFile--;
				keyRepeatDelay = 6;
			}
		}
		
		if (hHeld & KEY_DOWN && !keyRepeatDelay) {
			if ((uint)selectedFile < dirContents.size()-1) {
				selectedFile++;
				keyRepeatDelay = 6;
			}
		}
		
		if (hDown & KEY_B) {
			char path[PATH_MAX];
			getcwd(path, PATH_MAX);
			if (strcmp(path, "sdmc:/") == 0 || strcmp(path, "/") == 0) {
				return "";
			} else {
				chdir("..");
				selectedFile = 0;
				dirChanged = true;
			}
		}
		
		if (hDown & KEY_START) {
			dirChanged = true;
		}
	}
}