/*
*   This file is part of Happy-Home-Editor
*   Copyright (C) 2020 SuperSaiyajinStackZ
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

#include "offsets.hpp"
#include "Player.hpp"
#include "saveUtils.hpp"
#include "stringUtils.hpp"

/* (ranges from 0 to 0x1F). */
u8 Player::hair() const {
	return this->playerPointer()[0xC];
}
void Player::hair(u8 v) {
	if (v >= 0x0 && v <= 0x1F) this->playerPointer()[0xC] = v;
}

/* (ranges from 0 to 7). */
u8 Player::tan() const {
	return this->playerPointer()[0xD];
}
void Player::tan(u8 v) {
	if (v >= 0x0 && v <= 0x7) this->playerPointer()[0xD] = v;
}

/* (ranges from 0 to 0xF). */
u8 Player::haircolor() const {
	return this->playerPointer()[0xE];
}
void Player::haircolor(u8 v) {
	if (v >= 0x0 && v <= 0xF) this->playerPointer()[0xE] = v;
}

/*  (ranges from 0 to 0xC). */
u8 Player::eyes() const {
	return this->playerPointer()[0xF];
}
void Player::eyes(u8 v) {
	if (v >= 0x0 && v <= 0xC) this->playerPointer()[0xF] = v;
}

/* (ranges from 0 to 5). */
u8 Player::eyecolor() const {
	return this->playerPointer()[0x10];
}
void Player::eyecolor(u8 v) {
	if (v >= 0x0 && v <= 0x5) this->playerPointer()[0x10] = v;
}

/* (ranges from 0x266A to 0x273E). */
u16 Player::headwear() const {
	return SaveUtils::Read<u16>(this->playerPointer(), 0x12);
}
void Player::headwear(u16 v) {
	if (v >= 0x266A && v <= 0x273E) SaveUtils::Write<u16>(this->playerPointer(), 0x12, v);
}

/* (ranges from 0x273F to 0x2794). */
u16 Player::accessories() const {
	return SaveUtils::Read<u16>(this->playerPointer(), 0x16);
}
void Player::accessories(u16 v) {
	if (v >= 0x273F && v <= 0x2794) SaveUtils::Write<u16>(this->playerPointer(), 0x16, v);
}

/* (ranges from 0x2324 to 0x2566). */
u16 Player::shirt() const {
	return SaveUtils::Read<u16>(this->playerPointer(), 0x1A);
}
void Player::shirt(u16 v) {
	if (v >= 0x2324 && v <= 0x2566) SaveUtils::Write<u16>(this->playerPointer(), 0x1A, v);
}

/*  (ranges from 0x2567 to 0x25E2). */
u16 Player::pants() const {
	return SaveUtils::Read<u16>(this->playerPointer(), 0x1E);
}
void Player::pants(u16 v) {
	if (v >= 0x2567 && v <= 0x25E2) SaveUtils::Write<u16>(this->playerPointer(), 0x1E, v);
}

/* (ranges from 0x25E3 to 0x2606). */
u16 Player::socks() const {
	return SaveUtils::Read<u16>(this->playerPointer(), 0x22);
}
void Player::socks(u16 v) {
	if (v >= 0x25E3 && v <= 0x2606) SaveUtils::Write<u16>(this->playerPointer(), 0x22, v);
}

/* (ranges from 0x2607 to 0x2644). */
u16 Player::shoes() const {
	return SaveUtils::Read<u16>(this->playerPointer(), 0x26);
}
void Player::shoes(u16 v) {
	if (v >= 0x2607 && v <= 0x2644) SaveUtils::Write<u16>(this->playerPointer(), 0x26, v);
}

/* (ranges from 0x3221 to 0x3277). */
u16 Player::tools() const {
	return SaveUtils::Read<u16>(this->playerPointer(), 0x2A);
}
void Player::tools(u16 v) {
	if (v >= 0x3221 && v <= 0x3277) SaveUtils::Write<u16>(this->playerPointer(), 0x2A, v);
}

u16 Player::playerid() const {
	return SaveUtils::Read<u16>(this->playerPointer(), 0x3F528);
}
void Player::playerid(u16 v) {
	SaveUtils::Write<u16>(this->playerPointer(), 0x3F528, v);
}

std::u16string Player::name() const {
	return StringUtils::ReadUTF16String(this->playerPointer(), 0x3F52A, 7);
}

void Player::name(std::u16string v) {
	StringUtils::WriteUTF16String(this->playerPointer(), v, 0x3F52A, 7);
}