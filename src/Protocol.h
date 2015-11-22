/******************************************************************************
p    Copyright (C) 2002-2015 Argentum Online & Dakara Online Developers

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <vector>
#include <memory>
#include <string>
#include "vb6compat.h"
#include "enums.h"
#include "ProtocolNew.h"


extern const std::string SEPARATOR;

inline dakara::protocol::server::ChatOverHead BuildChatOverHead(const std::string& Chat, std::int16_t CharIndex, std::uint32_t color) {
	return dakara::protocol::server::BuildChatOverHead(Chat, CharIndex, color & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff);
}

void WriteMultiMessage(int UserIndex, int MessageIndex, int Arg1 = int(), int Arg2 = int(), int Arg3 = int(),
		std::string StringArg1 = std::string());

/* '' */
/* ' Writes the "Logged" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteLoggedMessage(int UserIndex);

/* '' */
/* ' Writes the "RemoveDialogs" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRemoveAllDialogs(int UserIndex);

/* '' */
/* ' Writes the "RemoveCharDialog" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character whose dialog will be removed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRemoveCharDialog(int UserIndex, int CharIndex);

/* '' */
/* ' Writes the "NavigateToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteNavigateToggle(int UserIndex);

/* '' */
/* ' Writes the "Disconnect" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDisconnect(int UserIndex);

/* '' */
/* ' Writes the "UserOfferConfirm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserOfferConfirm(int UserIndex);

/* '' */
/* ' Writes the "CommerceEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCommerceEnd(int UserIndex);

/* '' */
/* ' Writes the "BankEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBankEnd(int UserIndex);

/* '' */
/* ' Writes the "CommerceInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCommerceInit(int UserIndex);

/* '' */
/* ' Writes the "BankInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBankInit(int UserIndex);

/* '' */
/* ' Writes the "UserCommerceInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCommerceInit(int UserIndex);

/* '' */
/* ' Writes the "UserCommerceEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCommerceEnd(int UserIndex);

/* '' */
/* ' Writes the "ShowBlacksmithForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowBlacksmithForm(int UserIndex);

/* '' */
/* ' Writes the "ShowCarpenterForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowCarpenterForm(int UserIndex);

/* '' */
/* ' Writes the "UpdateSta" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateSta(int UserIndex);

/* '' */
/* ' Writes the "UpdateMana" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateMana(int UserIndex);

/* '' */
/* ' Writes the "UpdateHP" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateHP(int UserIndex);

/* '' */
/* ' Writes the "UpdateGold" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateGold(int UserIndex);

/* '' */
/* ' Writes the "UpdateBankGold" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateBankGold(int UserIndex);

/* '' */
/* ' Writes the "UpdateExp" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateExp(int UserIndex);

/* '' */
/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateStrenghtAndDexterity(int UserIndex);

/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateDexterity(int UserIndex);

/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateStrenght(int UserIndex);

/* '' */
/* ' Writes the "ChangeMap" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    map The new map to load. */
/* ' @param    version The version of the map in the server to check if client is properly updated. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeMap(int UserIndex, int Map, int version);

/* '' */
/* ' Writes the "PosUpdate" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePosUpdate(int UserIndex);

/* '' */
/* ' Writes the "ChatOverHead" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @param    CharIndex The character uppon which the chat will be displayed. */
/* ' @param    Color The color to be used when displaying the chat. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChatOverHead(int UserIndex, std::string Chat, int CharIndex, int color);

/* '' */
/* ' Writes the "ConsoleMsg" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @param    FontIndex Index of the FONTTYPE structure to use. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteConsoleMsg(int UserIndex, std::string Chat, FontTypeNames FontIndex);

void WriteCommerceChat(int UserIndex, std::string Chat, FontTypeNames FontIndex);

/* '' */
/* ' Writes the "GuildChat" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildChat(int UserIndex, std::string Chat);

/* '' */
/* ' Writes the "ShowMessageBox" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Message Text to be displayed in the message box. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowMessageBox(int UserIndex, std::string message);

/* '' */
/* ' Writes the "UserIndexInServer" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserIndexInServer(int UserIndex);

/* '' */
/* ' Writes the "UserCharIndexInServer" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCharIndexInServer(int UserIndex);

/* '' */
/* ' Writes the "CharacterCreate" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    body Body index of the new character. */
/* ' @param    head Head index of the new character. */
/* ' @param    heading Heading in which the new character is looking. */
/* ' @param    CharIndex The index of the new character. */
/* ' @param    X X coord of the new character's position. */
/* ' @param    Y Y coord of the new character's position. */
/* ' @param    weapon Weapon index of the new character. */
/* ' @param    shield Shield index of the new character. */
/* ' @param    FX FX index to be displayed over the new character. */
/* ' @param    FXLoops Number of times the FX should be rendered. */
/* ' @param    helmet Helmet index of the new character. */
/* ' @param    name Name of the new character. */
/* ' @param    criminal Determines if the character is a criminal or not. */
/* ' @param    privileges Sets if the character is a normal one or any kind of administrative character. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCharacterCreate(int UserIndex, int body, int Head, eHeading heading, int CharIndex, int X, int Y,
		int weapon, int shield, int FX, int FXLoops, int helmet, std::string Name, int NickColor,
		int Privileges);

/* '' */
/* ' Writes the "CharacterRemove" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character to be removed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCharacterRemove(int UserIndex, int CharIndex);

/* '' */
/* ' Writes the "CharacterMove" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character which is moving. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCharacterMove(int UserIndex, int CharIndex, int X, int Y);

void WriteForceCharMove(int UserIndex, eHeading Direccion);

/* '' */
/* ' Writes the "CharacterChange" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    body Body index of the new character. */
/* ' @param    head Head index of the new character. */
/* ' @param    heading Heading in which the new character is looking. */
/* ' @param    CharIndex The index of the new character. */
/* ' @param    weapon Weapon index of the new character. */
/* ' @param    shield Shield index of the new character. */
/* ' @param    FX FX index to be displayed over the new character. */
/* ' @param    FXLoops Number of times the FX should be rendered. */
/* ' @param    helmet Helmet index of the new character. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCharacterChange(int UserIndex, int body, int Head, eHeading heading, int CharIndex, int weapon,
		int shield, int FX, int FXLoops, int helmet);

/* '' */
/* ' Writes the "ObjectCreate" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    GrhIndex Grh of the object. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteObjectCreate(int UserIndex, int GrhIndex, int X, int Y);

/* '' */
/* ' Writes the "ObjectDelete" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteObjectDelete(int UserIndex, int X, int Y);

/* '' */
/* ' Writes the "BlockPosition" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @param    Blocked True if the position is blocked. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlockPosition(int UserIndex, int X, int Y, bool Blocked);

/* '' */
/* ' Writes the "PlayMidi" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    midi The midi to be played. */
/* ' @param    loops Number of repets for the midi. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePlayMidi(int UserIndex, int midi, int loops = -1);

/* '' */
/* ' Writes the "PlayWave" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    wave The wave to be played. */
/* ' @param    X The X position in map coordinates from where the sound comes. */
/* ' @param    Y The Y position in map coordinates from where the sound comes. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePlayWave(int UserIndex, int wave, int X, int Y);

/* '' */
/* ' Writes the "GuildList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    GuildList List of guilds to be sent. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildList(int UserIndex, std::vector<std::string> & guildList);

/* '' */
/* ' Writes the "AreaChanged" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAreaChanged(int UserIndex);

/* '' */
/* ' Writes the "PauseToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePauseToggle(int UserIndex);

/* '' */
/* ' Writes the "RainToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRainToggle(int UserIndex);

/* '' */
/* ' Writes the "CreateFX" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character upon which the FX will be created. */
/* ' @param    FX FX index to be displayed over the new character. */
/* ' @param    FXLoops Number of times the FX should be rendered. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCreateFX(int UserIndex, int CharIndex, int FX, int FXLoops);

/* '' */
/* ' Writes the "UpdateUserStats" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateUserStats(int UserIndex);

/* '' */
/* ' Writes the "WorkRequestTarget" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Skill The skill for which we request a target. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteWorkRequestTarget(int UserIndex, eSkill Skill);

/* '' */
/* ' Writes the "ChangeInventorySlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    slot Inventory slot which needs to be updated. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeInventorySlot(int UserIndex, int Slot);

void WriteAddSlots(int UserIndex, eMochilas Mochila);

/* '' */
/* ' Writes the "ChangeBankSlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    slot Inventory slot which needs to be updated. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeBankSlot(int UserIndex, int Slot);

/* '' */
/* ' Writes the "ChangeSpellSlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    slot Spell slot to update. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeSpellSlot(int UserIndex, int Slot);

/* '' */
/* ' Writes the "Atributes" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAttributes(int UserIndex);

/* '' */
/* ' Writes the "BlacksmithWeapons" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlacksmithWeapons(int UserIndex);

/* '' */
/* ' Writes the "BlacksmithArmors" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlacksmithArmors(int UserIndex);

/* '' */
/* ' Writes the "CarpenterObjects" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCarpenterObjects(int UserIndex);

/* '' */
/* ' Writes the "RestOK" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRestOK(int UserIndex);

/* '' */
/* ' Writes the "ErrorMsg" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    message The error message to be displayed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteErrorMsg(int UserIndex, std::string message);

/* '' */
/* ' Writes the "Blind" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlind(int UserIndex);

/* '' */
/* ' Writes the "Dumb" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDumb(int UserIndex);

/* '' */
/* ' Writes the "ShowSignal" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    objIndex Index of the signal to be displayed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowSignal(int UserIndex, int ObjIndex);

/* '' */
/* ' Writes the "ChangeNPCInventorySlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex   User to which the message is intended. */
/* ' @param    slot        The inventory slot in which this item is to be placed. */
/* ' @param    obj         The object to be set in the NPC's inventory window. */
/* ' @param    price       The value the NPC asks for the object. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeNPCInventorySlot(int UserIndex, int Slot, struct Obj & Obj, float price);

/* '' */
/* ' Writes the "UpdateHungerAndThirst" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateHungerAndThirst(int UserIndex);

/* '' */
/* ' Writes the "Fame" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteFame(int UserIndex);

/* '' */
/* ' Writes the "MiniStats" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteMiniStats(int UserIndex);

/* '' */
/* ' Writes the "LevelUp" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    skillPoints The number of free skill points the player has. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteLevelUp(int UserIndex, int skillPoints);

/* '' */
/* ' Writes the "AddForumMsg" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    title The title of the message to display. */
/* ' @param    message The message to be displayed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAddForumMsg(int UserIndex, eForumMsgType ForumType, std::string & Title, std::string & Author,
		std::string & message);

/* '' */
/* ' Writes the "ShowForumForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowForumForm(int UserIndex);

/* '' */
/* ' Writes the "SetInvisible" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex The char turning visible / invisible. */
/* ' @param    invisible True if the char is no longer visible, False otherwise. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteSetInvisible(int UserIndex, int CharIndex, bool invisible);

/* '' */
/* ' Writes the "DiceRoll" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDiceRoll(int UserIndex);

/* '' */
/* ' Writes the "MeditateToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteMeditateToggle(int UserIndex);

/* '' */
/* ' Writes the "BlindNoMore" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlindNoMore(int UserIndex);

/* '' */
/* ' Writes the "DumbNoMore" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDumbNoMore(int UserIndex);

/* '' */
/* ' Writes the "SendSkills" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteSendSkills(int UserIndex);

/* '' */
/* ' Writes the "TrainerCreatureList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    npcIndex The index of the requested trainer. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteTrainerCreatureList(int UserIndex, int NpcIndex);

/* '' */
/* ' Writes the "GuildNews" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guildNews The guild's news. */
/* ' @param    enemies The list of the guild's enemies. */
/* ' @param    allies The list of the guild's allies. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildNews(int UserIndex, std::string guildNews, std::vector<std::string> & enemies,
		std::vector<std::string> & allies);

/* '' */
/* ' Writes the "OfferDetails" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    details Th details of the Peace proposition. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteOfferDetails(int UserIndex, std::string details);

/* '' */
/* ' Writes the "AlianceProposalsList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guilds The list of guilds which propossed an alliance. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAlianceProposalsList(int UserIndex, std::vector<std::string> guilds);

/* '' */
/* ' Writes the "PeaceProposalsList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guilds The list of guilds which propossed peace. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePeaceProposalsList(int UserIndex, std::vector<std::string> guilds);

/* '' */
/* ' Writes the "CharacterInfo" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    charName The requested char's name. */
/* ' @param    race The requested char's race. */
/* ' @param    class The requested char's class. */
/* ' @param    gender The requested char's gender. */
/* ' @param    level The requested char's level. */
/* ' @param    gold The requested char's gold. */
/* ' @param    reputation The requested char's reputation. */
/* ' @param    previousPetitions The requested char's previous petitions to enter guilds. */
/* ' @param    currentGuild The requested char's current guild. */
/* ' @param    previousGuilds The requested char's previous guilds. */
/* ' @param    RoyalArmy True if tha char belongs to the Royal Army. */
/* ' @param    CaosLegion True if tha char belongs to the Caos Legion. */
/* ' @param    citicensKilled The number of citicens killed by the requested char. */
/* ' @param    criminalsKilled The number of criminals killed by the requested char. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCharacterInfo(int UserIndex, std::string charName, eRaza race, eClass Class, eGenero gender,
		int level, int gold, int bank, int reputation, std::string previousPetitions,
		std::string currentGuild, std::string previousGuilds, bool RoyalArmy, bool CaosLegion,
		int citicensKilled, int criminalsKilled);

/* '' */
/* ' Writes the "GuildLeaderInfo" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guildList The list of guild names. */
/* ' @param    memberList The list of the guild's members. */
/* ' @param    guildNews The guild's news. */
/* ' @param    joinRequests The list of chars which requested to join the clan. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildLeaderInfo(int UserIndex, std::vector<std::string> & guildList,
		std::vector<std::string> & MemberList, std::string guildNews,
		std::vector<std::string> & joinRequests);

/* '' */
/* ' Writes the "GuildLeaderInfo" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guildList The list of guild names. */
/* ' @param    memberList The list of the guild's members. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildMemberInfo(int UserIndex, std::vector<std::string> & guildList,
		std::vector<std::string> & MemberList);

/* '' */
/* ' Writes the "GuildDetails" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guildName The requested guild's name. */
/* ' @param    founder The requested guild's founder. */
/* ' @param    foundationDate The requested guild's foundation date. */
/* ' @param    leader The requested guild's current leader. */
/* ' @param    URL The requested guild's website. */
/* ' @param    memberCount The requested guild's member count. */
/* ' @param    electionsOpen True if the clan is electing it's new leader. */
/* ' @param    alignment The requested guild's alignment. */
/* ' @param    enemiesCount The requested guild's enemy count. */
/* ' @param    alliesCount The requested guild's ally count. */
/* ' @param    antifactionPoints The requested guild's number of antifaction acts commited. */
/* ' @param    codex The requested guild's codex. */
/* ' @param    guildDesc The requested guild's description. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildDetails(int UserIndex, std::string GuildName, std::string founder, std::string foundationDate,
		std::string leader, std::string URL, int memberCount, bool electionsOpen, std::string alignment,
		int enemiesCount, int AlliesCount, std::string antifactionPoints, std::vector<std::string> & codex,
		std::string guildDesc);

/* '' */
/* ' Writes the "ShowGuildAlign" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowGuildAlign(int UserIndex);

/* '' */
/* ' Writes the "ShowGuildFundationForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowGuildFundationForm(int UserIndex);

/* '' */
/* ' Writes the "ParalizeOK" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteParalizeOK(int UserIndex);

/* '' */
/* ' Writes the "ShowUserRequest" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    details DEtails of the char's request. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowUserRequest(int UserIndex, std::string details);

/* '' */
/* ' Writes the "TradeOK" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteTradeOK(int UserIndex);

/* '' */
/* ' Writes the "BankOK" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBankOK(int UserIndex);

/* '' */
/* ' Writes the "ChangeUserTradeSlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    ObjIndex The object's index. */
/* ' @param    amount The number of objects offered. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeUserTradeSlot(int UserIndex, int OfferSlot, int ObjIndex, int Amount);

/* '' */
/* ' Writes the "SendNight" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteSendNight(int UserIndex, bool night);

/* '' */
/* ' Writes the "SpawnList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    npcNames The names of the creatures that can be spawned. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteSpawnList(int UserIndex, std::vector<std::string> & npcNames);

/* '' */
/* ' Writes the "ShowSOSForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowSOSForm(int UserIndex);

/* '' */
/* ' Writes the "ShowDenounces" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowDenounces(int UserIndex);

/* '' */
/* ' Writes the "ShowSOSForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowPartyForm(int UserIndex);

/* '' */
/* ' Writes the "ShowMOTDEditionForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    currentMOTD The current Message Of The Day. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowMOTDEditionForm(int UserIndex, std::string currentMOTD);

/* '' */
/* ' Writes the "ShowGMPanelForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowGMPanelForm(int UserIndex);

/* '' */
/* ' Writes the "UserNameList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    userNameList List of user names. */
/* ' @param    Cant Number of names to send. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserNameList(int UserIndex, std::vector<std::string> & userNamesList, int cant);

/* '' */
/* ' Writes the "Pong" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePong(int UserIndex);

/* '' */
/* ' Flushes the outgoing data buffer of the user. */
/* ' */
/* ' @param    UserIndex User whose outgoing data buffer will be flushed. */

void FlushBuffer(int UserIndex);


/* '' */
/* ' Writes the "StopWorking" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */

void WriteStopWorking(int UserIndex);

/* '' */
/* ' Writes the "CancelOfferItem" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Slot      The slot to cancel. */

void WriteCancelOfferItem(int UserIndex, int Slot);

/* '' */
/* ' Writes the "RecordDetails" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRecordDetails(int UserIndex, int RecordIndex);

/* '' */
/* ' Writes the "RecordList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRecordList(int UserIndex);

#endif
