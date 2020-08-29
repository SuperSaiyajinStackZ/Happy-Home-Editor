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

#ifndef _HAPPY_HOME_EDITOR_SAV_HPP
#define _HAPPY_HOME_EDITOR_SAV_HPP

#include "Pattern.hpp"
#include "Player.hpp"
#include "types.hpp"

#include <memory>

class Pattern;
class Player;
class Sav {
protected:
	std::shared_ptr<u8[]> saveData;
	u32 saveLength;
public:
	~Sav() {}
	Sav(std::shared_ptr<u8[]> data, u32 length) : saveData(data), saveLength(length) {
		this->changesMade(false); // Initialize as false here.
	}

	Sav(const Sav& save) = delete;
	Sav& operator=(const Sav& save) = delete;
	
	std::unique_ptr<Pattern> pattern(u32 slot) const;
	std::unique_ptr<Player> player() const;
	
	/* Call this when finished editing. */
	void Finish(void);

	/* Call this when getting the Save. */
	static std::unique_ptr<Sav> getSave(std::shared_ptr<u8[]> dt, u32 length);

	/* return Sav stuff. */
	u32 getLength() const { return saveLength; }
	std::shared_ptr<u8[]> rawData() const { return saveData; }

	void changesMade(bool v) { if (v != this->changes) this->changes = v; }
	bool changesMade() const { return this->changes; }

	u8 *savePointer() const {
		return this->saveData.get();
	}
private:
	bool changes = false;
};

#endif