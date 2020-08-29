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

#include "stringUtils.hpp"

#include <algorithm>
#include <array>
#include <cstring>
#include <sstream>

std::string utf16DataToUtf8(const char16_t* data, size_t size, char16_t delim = 0) {
	std::string ret;
	ret.reserve(size);
	char addChar[4] = {0};
	for (size_t i = 0; i < size; i++) {
		if (data[i] == delim) {
			return ret;
		} else if (data[i] < 0x0080) {
			addChar[0] = data[i];
			addChar[1] = '\0';
		} else if (data[i] < 0x0800) {
			addChar[0] = 0xC0 | ((data[i] >> 6) & 0x1F);
			addChar[1] = 0x80 | (data[i] & 0x3F);
			addChar[2] = '\0';
		} else {
			addChar[0] = 0xE0 | ((data[i] >> 12) & 0x0F);
			addChar[1] = 0x80 | ((data[i] >> 6) & 0x3F);
			addChar[2] = 0x80 | (data[i] & 0x3F);
			addChar[3] = '\0';
		}

		ret.append(addChar);
	}

	return ret;
}

std::u16string StringUtils::UTF8toUTF16(const std::string& src) {
	std::u16string ret;
	ret.reserve(src.size());
	for (size_t i = 0; i < src.size(); i++) {
		u16 codepoint	= 0xFFFD;
		int iMod		= 0;
		if (src[i] & 0x80 && src[i] & 0x40 && src[i] & 0x20 && !(src[i] & 0x10) && i + 2 < src.size()) {
			codepoint	= src[i] & 0x0F;
			codepoint	= codepoint << 6 | (src[i + 1] & 0x3F);
			codepoint	= codepoint << 6 | (src[i + 2] & 0x3F);
			iMod		= 2;
		} else if (src[i] & 0x80 && src[i] & 0x40 && !(src[i] & 0x20) && i + 1 < src.size()) {
			codepoint	= src[i] & 0x1F;
			codepoint	= codepoint << 6 | (src[i + 1] & 0x3F);
			iMod		= 1;
		} else if (!(src[i] & 0x80)) {
			codepoint = src[i];
		}

		ret.push_back((char16_t)codepoint);
		i += iMod;
	}

	return ret;
}

std::string StringUtils::UTF16toUTF8(const std::u16string& src) {
	return utf16DataToUtf8(src.data(), src.size());
}

std::u16string StringUtils::ReadUTF16String(u8* data, int ofs, int len) {
	return std::u16string(reinterpret_cast<char16_t *>(data + ofs), len + 1);
}

void StringUtils::WriteUTF16String(u8 *data, const std::u16string &str, u32 offset, u32 maxSize) {
	/* Do not allow a string longer as max. */
	if (str.length() > maxSize + 1) return;

	memcpy(data + offset, (u8 *)str.data(), maxSize * 2);
}