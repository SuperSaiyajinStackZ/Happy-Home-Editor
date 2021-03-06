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

#ifndef _HAPPY_HOME_EDITOR_PLAYER_HPP
#define _HAPPY_HOME_EDITOR_PLAYER_HPP

#include "offsets.hpp"
#include "Pattern.hpp"
#include "types.hpp"

#include <memory>

class Pattern;
class Player {
protected:
	std::shared_ptr<u8[]> pData;
public:
	~Player() {}
	Player(std::shared_ptr<u8[]> data) : pData(data) { }

	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;

	u8 hair() const;
	void hair(u8 v);
	u8 tan() const;
	void tan(u8 v);
	u8 haircolor() const;
	void haircolor(u8 v);
	u8 eyes() const;
	void eyes(u8 v);
	u8 eyecolor() const;
	void eyecolor(u8 v);

	u16 headwear() const;
	void headwear(u16 v);
	u16 accessories() const;
	void accessories(u16 v);
	u16 shirt() const;
	void shirt(u16 v);
	u16 pants() const;
	void pants(u16 v);
	u16 socks() const;
	void socks(u16 v);
	u16 shoes() const;
	void shoes(u16 v);
	u16 tools() const;
	void tools(u16 v);
	u16 playerid() const;
	void playerid(u16 v);

	std::u16string name() const;
	void name(std::u16string v);
	std::unique_ptr<Pattern> pattern(u32 slot) const;

	/* Misc. */
	void unlockAll();
	void lockAll();
	void unlockEmotions();
	void lockEmotions();
private:
	u8 *playerPointer() const {
		return this->pData.get() + PLAYER_DATA_START;
	}
};

#endif
