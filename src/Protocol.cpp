/******************************************************************************
    Copyright (C) 2002-2015 Argentum Online & Dakara Online Developers

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

#include "stdafx.h"

#include "Protocol.h"
#include "ProtocolNew.h"


static const char* SEPARATORC = "\0";
const std::string SEPARATOR{SEPARATORC, SEPARATORC + 1};

void WriteMultiMessage(int UserIndex, int MessageIndex, int Arg1, int Arg2, int Arg3,
		std::string StringArg1) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(dakara::protocol::server::ServerPacketID_MultiMessage);
	UserList[UserIndex].outgoingData->WriteByte(MessageIndex);

	switch (MessageIndex) {
	case eMessages_DontSeeAnything:
	case eMessages_NPCSwing:
	case eMessages_NPCKillUser:
	case eMessages_BlockedWithShieldUser:
	case eMessages_BlockedWithShieldother:
	case eMessages_UserSwing:
	case eMessages_SafeModeOn:
	case eMessages_SafeModeOff:
	case eMessages_ResuscitationSafeOff:
	case eMessages_ResuscitationSafeOn:
	case eMessages_NobilityLost:
	case eMessages_CantUseWhileMeditating:
	case eMessages_CancelHome:
	case eMessages_FinishHome:

		break;

	case eMessages_NPCHitUser:
		/* 'Target */
		UserList[UserIndex].outgoingData->WriteByte(Arg1);
		/* 'damage */
		UserList[UserIndex].outgoingData->WriteInteger(Arg2);

		break;

	case eMessages_UserHitNPC:
		/* 'damage */
		UserList[UserIndex].outgoingData->WriteLong(Arg1);

		break;

	case eMessages_UserAttackedSwing:
		UserList[UserIndex].outgoingData->WriteInteger(UserList[Arg1].Char.CharIndex);

		break;

	case eMessages_UserHittedByUser:
		/* 'AttackerIndex */
		UserList[UserIndex].outgoingData->WriteInteger(Arg1);
		/* 'Target */
		UserList[UserIndex].outgoingData->WriteByte(Arg2);
		/* 'damage */
		UserList[UserIndex].outgoingData->WriteInteger(Arg3);

		break;

	case eMessages_UserHittedUser:
		/* 'AttackerIndex */
		UserList[UserIndex].outgoingData->WriteInteger(Arg1);
		/* 'Target */
		UserList[UserIndex].outgoingData->WriteByte(Arg2);
		/* 'damage */
		UserList[UserIndex].outgoingData->WriteInteger(Arg3);

		break;

	case eMessages_WorkRequestTarget:
		/* 'skill */
		UserList[UserIndex].outgoingData->WriteByte(Arg1);

		/* '"Has matado a " & UserList(VictimIndex).name & "!" "Has ganado " & DaExp & " puntos de experiencia." */
		break;

	case eMessages_HaveKilledUser:
		/* 'VictimIndex */
		UserList[UserIndex].outgoingData->WriteInteger(UserList[Arg1].Char.CharIndex);
		/* 'Expe */
		UserList[UserIndex].outgoingData->WriteLong(Arg2);

		/* '"¡" & .name & " te ha matado!" */
		break;

	case eMessages_UserKill:
		/* 'AttackerIndex */
		UserList[UserIndex].outgoingData->WriteInteger(UserList[Arg1].Char.CharIndex);

		break;

	case eMessages_EarnExp:

		break;

	case eMessages_Home:
		UserList[UserIndex].outgoingData->WriteByte(vb6::CByte(Arg1));
		UserList[UserIndex].outgoingData->WriteInteger(vb6::CInt(Arg2));
		/* 'El cliente no conoce nada sobre nombre de mapas y hogares, por lo tanto _
		 hasta que no se pasen los dats e .INFs al cliente, esto queda así. */
		/* 'Call .WriteByte(CByte(Arg2)) */
		UserList[UserIndex].outgoingData->WriteUnicodeString(StringArg1);

		break;
	}
}

/* '' */
/* ' Writes the "Logged" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteLoggedMessage(int UserIndex) {
	dakara::protocol::server::Logged p;

	p.Clase = UserList[UserIndex].clase;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "RemoveDialogs" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRemoveAllDialogs(int UserIndex) {
	dakara::protocol::server::RemoveDialogs p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "RemoveCharDialog" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character whose dialog will be removed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRemoveCharDialog(int UserIndex, int CharIndex) {
	dakara::protocol::server::RemoveCharDialog p;

	p.CharIndex = CharIndex;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "NavigateToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteNavigateToggle(int UserIndex) {
	dakara::protocol::server::NavigateToggle p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "Disconnect" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDisconnect(int UserIndex) {
	dakara::protocol::server::Disconnect p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UserOfferConfirm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserOfferConfirm(int UserIndex) {
	dakara::protocol::server::UserOfferConfirm p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "CommerceEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCommerceEnd(int UserIndex) {
	dakara::protocol::server::CommerceEnd p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "BankEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBankEnd(int UserIndex) {
	dakara::protocol::server::BankEnd p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "CommerceInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCommerceInit(int UserIndex) {
	dakara::protocol::server::CommerceInit p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "BankInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBankInit(int UserIndex) {
	dakara::protocol::server::BankInit p;

	p.Banco = UserList[UserIndex].Stats.Banco;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UserCommerceInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCommerceInit(int UserIndex) {
	dakara::protocol::server::UserCommerceInit p;

	p.DestUserName = UserList[UserIndex].ComUsu.DestNick;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UserCommerceEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCommerceEnd(int UserIndex) {
	dakara::protocol::server::UserCommerceEnd p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowBlacksmithForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowBlacksmithForm(int UserIndex) {
	dakara::protocol::server::ShowBlacksmithForm p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowCarpenterForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowCarpenterForm(int UserIndex) {
	dakara::protocol::server::ShowCarpenterForm p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateSta" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateSta(int UserIndex) {
	dakara::protocol::server::UpdateSta p;

	p.Value = UserList[UserIndex].Stats.MinSta;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateMana" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateMana(int UserIndex) {
	dakara::protocol::server::UpdateMana p;

	p.Value = UserList[UserIndex].Stats.MinMAN;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateHP" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateHP(int UserIndex) {
	dakara::protocol::server::UpdateHP p;

	p.Value = UserList[UserIndex].Stats.MinHp;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateGold" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateGold(int UserIndex) {
	dakara::protocol::server::UpdateGold p;

	p.Value = UserList[UserIndex].Stats.GLD;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateBankGold" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateBankGold(int UserIndex) {
	dakara::protocol::server::UpdateBankGold p;

	p.Value = UserList[UserIndex].Stats.Banco;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateExp" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateExp(int UserIndex) {
	dakara::protocol::server::UpdateExp p;

	p.Value = UserList[UserIndex].Stats.Exp;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateStrenghtAndDexterity(int UserIndex) {
	dakara::protocol::server::UpdateStrenghtAndDexterity p;

	p.Fuerza = UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza];
	p.Agilidad = UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad];

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateDexterity(int UserIndex) {
	dakara::protocol::server::UpdateDexterity p;

	p.Agilidad = UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad];

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateStrenght(int UserIndex) {
	dakara::protocol::server::UpdateStrenght p;

	p.Fuerza = UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza];

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ChangeMap" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    map The new map to load. */
/* ' @param    version The version of the map in the server to check if client is properly updated. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeMap(int UserIndex, int Map, int version) {
	dakara::protocol::server::ChangeMap p;

	p.Map = Map;
	p.Version = version;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "PosUpdate" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePosUpdate(int UserIndex) {
	dakara::protocol::server::PosUpdate p;

	p.X = UserList[UserIndex].Pos.X;
	p.Y = UserList[UserIndex].Pos.Y;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ChatOverHead" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @param    CharIndex The character uppon which the chat will be displayed. */
/* ' @param    Color The color to be used when displaying the chat. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChatOverHead(int UserIndex, std::string Chat, int CharIndex, int color) {
	dakara::protocol::server::ChatOverHead p;

	p.CharIndex = CharIndex;
	p.Chat = Chat;
	p.R = (color) & 0xFF;
	p.G = (color >> 8) & 0xFF;;
	p.B = (color >> 16) & 0xFF;;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ConsoleMsg" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @param    FontIndex Index of the FONTTYPE structure to use. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteConsoleMsg(int UserIndex, std::string Chat, FontTypeNames FontIndex) {
	dakara::protocol::server::ConsoleMsg p;

	p.Chat = Chat;
	p.FontIndex = FontIndex;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

void WriteCommerceChat(int UserIndex, std::string Chat, FontTypeNames FontIndex) {
	dakara::protocol::server::CommerceChat p;

	p.Chat = Chat;
	p.FontIndex = FontIndex;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "GuildChat" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildChat(int UserIndex, std::string Chat) {
	dakara::protocol::server::GuildChat p;

	p.Chat = Chat;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowMessageBox" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Message Text to be displayed in the message box. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowMessageBox(int UserIndex, std::string message) {
	dakara::protocol::server::ShowMessageBox p;

	p.Chat = message;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UserIndexInServer" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserIndexInServer(int UserIndex) {
	dakara::protocol::server::UserIndexInServer p;

	p.UserIndex = UserIndex;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UserCharIndexInServer" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCharIndexInServer(int UserIndex) {
	dakara::protocol::server::UserCharIndexInServer p;

	p.CharIndex = UserList[UserIndex].Char.CharIndex;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

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
		int Privileges) {
	dakara::protocol::server::CharacterCreate p;

	p.Body = body;
	p.Head = Head;
	p.Heading = heading;
	p.CharIndex = CharIndex;
	p.X = X;
	p.Y = Y;
	p.Weapon = weapon;
	p.Shield = shield;
	p.FX = FX;
	p.FXLoops = FXLoops;
	p.Helmet = helmet;
	p.Name = Name;
	p.NickColor = NickColor;
	p.Privileges = Privileges;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "CharacterRemove" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character to be removed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCharacterRemove(int UserIndex, int CharIndex) {
	dakara::protocol::server::CharacterRemove p;

	p.CharIndex = CharIndex;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "CharacterMove" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character which is moving. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCharacterMove(int UserIndex, int CharIndex, int X, int Y) {
	dakara::protocol::server::CharacterMove p;

	p.CharIndex = CharIndex;
	p.X = X;
	p.Y = Y;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

void WriteForceCharMove(int UserIndex, eHeading Direccion) {
	dakara::protocol::server::ForceCharMove p;

	p.Direction = Direccion;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

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
		int shield, int FX, int FXLoops, int helmet) {
	dakara::protocol::server::CharacterChange p;

	p.Body = body;
	p.Head = Head;
	p.Heading = heading;
	p.CharIndex = CharIndex;
	p.Weapon = weapon;
	p.Shield = shield;
	p.FX = FX;
	p.FXLoops = FXLoops;
	p.Helmet = helmet;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ObjectCreate" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    GrhIndex Grh of the object. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteObjectCreate(int UserIndex, int GrhIndex, int X, int Y) {
	dakara::protocol::server::ObjectCreate p;

	p.GrhIndex = GrhIndex;
	p.X = X;
	p.Y = Y;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ObjectDelete" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteObjectDelete(int UserIndex, int X, int Y) {
	dakara::protocol::server::ObjectDelete p;

	p.X = X;
	p.Y = Y;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "BlockPosition" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @param    Blocked True if the position is blocked. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlockPosition(int UserIndex, int X, int Y, bool Blocked) {
	dakara::protocol::server::BlockPosition p;

	p.X = X;
	p.Y = Y;
	p.Blocked = Blocked;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "PlayMidi" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    midi The midi to be played. */
/* ' @param    loops Number of repets for the midi. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePlayMidi(int UserIndex, int midi, int loops) {
	dakara::protocol::server::PlayMidi p;

	p.MidiID = midi;
	p.Loops = loops;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "PlayWave" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    wave The wave to be played. */
/* ' @param    X The X position in map coordinates from where the sound comes. */
/* ' @param    Y The Y position in map coordinates from where the sound comes. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePlayWave(int UserIndex, int wave, int X, int Y) {
	dakara::protocol::server::PlayWave p;

	p.WaveID = wave;
	p.X = X;
	p.Y = Y;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "GuildList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    GuildList List of guilds to be sent. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildList(int UserIndex, std::vector<std::string> & guildList) {
	std::string Tmp;
	int i;

	/* ' Prepare guild name's list */
	for (i = 0; i < (int)guildList.size(); i++) {
		Tmp = Tmp + guildList[i] + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	dakara::protocol::server::GuildList p;

	p.Data = Tmp;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "AreaChanged" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAreaChanged(int UserIndex) {
	dakara::protocol::server::AreaChanged p;

	p.X = UserList[UserIndex].Pos.X;
	p.Y = UserList[UserIndex].Pos.Y;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "PauseToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePauseToggle(int UserIndex) {
	dakara::protocol::server::PauseToggle p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "RainToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRainToggle(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "RainToggle" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::RainToggle p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "CreateFX" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character upon which the FX will be created. */
/* ' @param    FX FX index to be displayed over the new character. */
/* ' @param    FXLoops Number of times the FX should be rendered. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCreateFX(int UserIndex, int CharIndex, int FX, int FXLoops) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CreateFX" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::CreateFX p;
	p.CharIndex = CharIndex;
	p.FX =FX;
	p.FXLoops = FXLoops;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateUserStats" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateUserStats(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UpdateUserStats" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::UpdateUserStats p;
	p.MaxHp = UserList[UserIndex].Stats.MaxHp;
	p.MaxMan = UserList[UserIndex].Stats.MaxMAN;
	p.MinHp = UserList[UserIndex].Stats.MinHp;
	p.MinMan = UserList[UserIndex].Stats.MinMAN;
	p.MaxSta = UserList[UserIndex].Stats.MaxSta;
	p.MinSta = UserList[UserIndex].Stats.MinSta;
	p.Gld = UserList[UserIndex].Stats.GLD;
	p.Elv = UserList[UserIndex].Stats.ELV;
	p.Elu = UserList[UserIndex].Stats.ELU;
	p.Exp = UserList[UserIndex].Stats.Exp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "WorkRequestTarget" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Skill The skill for which we request a target. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteWorkRequestTarget(int UserIndex, eSkill Skill) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "WorkRequestTarget" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::WorkRequestTarget p;
	p.Skill = Skill;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ChangeInventorySlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    slot Inventory slot which needs to be updated. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeInventorySlot(int UserIndex, int Slot) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 3/12/09 */
	/* 'Writes the "ChangeInventorySlot" message to the given user's outgoing data buffer */
	/* '3/12/09: Budi - Ahora se envia MaxDef y MinDef en lugar de Def */
	/* '*************************************************** */

	dakara::protocol::server::ChangeInventorySlot p;
	p.Slot = Slot;

	int ObjIndex;
	struct ObjData obData;

	ObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;

	if (ObjIndex > 0) {
		obData = ObjData[ObjIndex];
	}

	p.ObjIndex = ObjIndex;
	p.ObjName = obData.Name;
	p.Amount = UserList[UserIndex].Invent.Object[Slot].Amount;
	p.Equiped = UserList[UserIndex].Invent.Object[Slot].Equipped;
	p.GrhIndex = obData.GrhIndex;
	p.ObjType = obData.OBJType;
	p.MaxHit = obData.MaxHIT;
	p.MinHit = obData.MinHIT;
	p.MaxDef = obData.MaxDef;
	p.MinDef = obData.MinDef;
	p.ObjSalePrice = SalePrice(ObjIndex);

	p.serialize(UserList[UserIndex].outgoingData.get());
}

void WriteAddSlots(int UserIndex, eMochilas Mochila) {
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 01/12/09 */
	/* 'Writes the "AddSlots" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::AddSlots p;
	p.Mochila = Mochila;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ChangeBankSlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    slot Inventory slot which needs to be updated. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeBankSlot(int UserIndex, int Slot) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 12/03/09 */
	/* 'Writes the "ChangeBankSlot" message to the given user's outgoing data buffer */
	/* '12/03/09: Budi - Ahora se envia MaxDef y MinDef en lugar de sólo Def */
	/* '*************************************************** */

	dakara::protocol::server::ChangeBankSlot p;
	p.Slot = Slot;

	int ObjIndex;
	struct ObjData obData;

	ObjIndex = UserList[UserIndex].BancoInvent.Object[Slot].ObjIndex;

	if (ObjIndex > 0) {
		obData = ObjData[ObjIndex];
	}

	p.ObjIndex = ObjIndex;
	p.ObjName = obData.Name;
	p.Amount = UserList[UserIndex].BancoInvent.Object[Slot].Amount;
	p.GrhIndex = obData.GrhIndex;
	p.ObjType = obData.OBJType;
	p.MaxHit = obData.MaxHIT;
	p.MinHit = obData.MinHIT;
	p.MaxDef = obData.MaxDef;
	p.MinDef = obData.MinDef;
	p.ObjSalePrice = obData.Valor;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ChangeSpellSlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    slot Spell slot to update. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeSpellSlot(int UserIndex, int Slot) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ChangeSpellSlot" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::ChangeSpellSlot p;
	p.Slot = Slot;
	p.SpellID = UserList[UserIndex].Stats.UserHechizos[Slot];

	if (UserList[UserIndex].Stats.UserHechizos[Slot] > 0) {
		p.Name = Hechizos[UserList[UserIndex].Stats.UserHechizos[Slot]].Nombre;
	} else {
		p.Name = "(None)";
	}
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "Atributes" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAttributes(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "Atributes" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::Atributes p;

	p.Fuerza = UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza];
	p.Agilidad = UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad];
	p.Inteligencia = UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia];
	p.Carisma = UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma];
	p.Constitucion = UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion];
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "BlacksmithWeapons" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlacksmithWeapons(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 04/15/2008 (NicoNZ) Habia un error al fijarse los skills del personaje */
	/* 'Writes the "BlacksmithWeapons" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::BlacksmithWeapons p;
	int i;
	struct ObjData Obj;
	std::vector<int> validIndexes;
	int Count = 0;

	validIndexes.resize(0);
	validIndexes.resize(1 + vb6::UBound(ArmasHerrero));

	for (i = (1); i <= (vb6::UBound(ArmasHerrero)); i++) {
		/* ' Can the user create this object? If so add it to the list.... */
		if (ObjData[ArmasHerrero[i]].SkHerreria
				<= vb6::Round(
						UserList[UserIndex].Stats.UserSkills[eSkill_Herreria]
								/ ModHerreriA(UserList[UserIndex].clase), 0)) {
			Count = Count + 1;
			validIndexes[Count] = i;
		}
	}


	/* ' Write the needed data of each object */
	for (i = (1); i <= (Count); i++) {
		Obj = ObjData[ArmasHerrero[validIndexes[i]]];
		p.addItem(Obj.Name,Obj.GrhIndex,Obj.LingH,Obj.LingP,Obj.LingO,ArmasHerrero[validIndexes[i]],Obj.Upgrade);
	}
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "BlacksmithArmors" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlacksmithArmors(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 04/15/2008 (NicoNZ) Habia un error al fijarse los skills del personaje */
	/* 'Writes the "BlacksmithArmors" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::BlacksmithArmors p;
	int i;
	struct ObjData Obj;
	std::vector<int> validIndexes;
	int Count = 0;

	validIndexes.resize(0);
	validIndexes.resize(1 + vb6::UBound(ArmadurasHerrero));


	for (i = (1); i <= (vb6::UBound(ArmadurasHerrero)); i++) {
		/* ' Can the user create this object? If so add it to the list.... */
		if (ObjData[ArmadurasHerrero[i]].SkHerreria
				<= vb6::Round(
						UserList[UserIndex].Stats.UserSkills[eSkill_Herreria]
								/ ModHerreriA(UserList[UserIndex].clase), 0)) {
			Count = Count + 1;
			validIndexes[Count] = i;
		}
	}


	/* ' Write the needed data of each object */
	for (i = (1); i <= (Count); i++) {
		Obj = ObjData[ArmadurasHerrero[validIndexes[i]]];
		p.addItem(Obj.Name,Obj.GrhIndex,Obj.LingH,Obj.LingP,Obj.LingO,ArmadurasHerrero[validIndexes[i]],Obj.Upgrade);
	}
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "CarpenterObjects" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCarpenterObjects(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CarpenterObjects" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::CarpenterObjects p;
	int i;
	struct ObjData Obj;
	std::vector<int> validIndexes;
	int Count = 0;

	validIndexes.resize(0);
	validIndexes.resize(1 + vb6::UBound(ObjCarpintero));



	for (i = (1); i <= (vb6::UBound(ObjCarpintero)); i++) {
		/* ' Can the user create this object? If so add it to the list.... */
		if (ObjData[ObjCarpintero[i]].SkCarpinteria
				<= UserList[UserIndex].Stats.UserSkills[eSkill_Carpinteria]
						/ ModCarpinteria(UserList[UserIndex].clase)) {
			Count = Count + 1;
			validIndexes[Count] = i;
		}
	}

	/* ' Write the needed data of each object */
	for (i = (1); i <= (Count); i++) {
		Obj = ObjData[ObjCarpintero[validIndexes[i]]];
		p.addItem(Obj.Name, Obj.GrhIndex, Obj.Madera, Obj.MaderaElfica,
				ObjCarpintero[validIndexes[i]], Obj.Upgrade);
	}
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "RestOK" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRestOK(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "RestOK" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::RestOK p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ErrorMsg" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    message The error message to be displayed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteErrorMsg(int UserIndex, std::string message) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ErrorMsg" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::ErrorMsg p;
	p.Message = message;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "Blind" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlind(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "Blind" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::Blind p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "Dumb" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDumb(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "Dumb" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::Dumb p;

	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowSignal" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    objIndex Index of the signal to be displayed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowSignal(int UserIndex, int ObjIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowSignal" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::ShowSignal p;

	p.Texto = ObjData[ObjIndex].texto;
	p.Grh = ObjData[ObjIndex].GrhSecundario;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ChangeNPCInventorySlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex   User to which the message is intended. */
/* ' @param    slot        The inventory slot in which this item is to be placed. */
/* ' @param    obj         The object to be set in the NPC's inventory window. */
/* ' @param    price       The value the NPC asks for the object. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeNPCInventorySlot(int UserIndex, int Slot, struct Obj & Obj, float price) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 12/03/09 */
	/* 'Last Modified by: Budi */
	/* 'Writes the "ChangeNPCInventorySlot" message to the given user's outgoing data buffer */
	/* '12/03/09: Budi - Ahora se envia MaxDef y MinDef en lugar de sólo Def */
	/* '*************************************************** */

	dakara::protocol::server::ChangeNPCInventorySlot p;

	struct ObjData ObjInfo;

	if (Obj.ObjIndex >= vb6::LBound(ObjData) && Obj.ObjIndex <= vb6::UBound(ObjData)) {
		ObjInfo = ObjData[Obj.ObjIndex];
	}


	p.Slot = Slot;
	p.ObjName = ObjInfo.Name;
	p.Amount = Obj.Amount;
	p.Price = price;
	p.GrhIndex = ObjInfo.GrhIndex;
	p.ObjIndex = Obj.ObjIndex;
	p.ObjType = ObjInfo.OBJType;
	p.MaxHit = ObjInfo.MaxHIT;
	p.MinHit = ObjInfo.MinHIT;
	p.MaxDef = ObjInfo.MaxDef;
	p.MinDef = ObjInfo.MinDef;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UpdateHungerAndThirst" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateHungerAndThirst(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UpdateHungerAndThirst" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::UpdateHungerAndThirst p;

	p.MaxAgu = UserList[UserIndex].Stats.MaxAGU;
	p.MinAgu = UserList[UserIndex].Stats.MinAGU;
	p.MaxHam = UserList[UserIndex].Stats.MaxHam;
	p.MinHam = UserList[UserIndex].Stats.MinHam;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "Fame" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteFame(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "Fame" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::Fame p;


	p.Asesino = UserList[UserIndex].Reputacion.AsesinoRep;
	p.Bandido = UserList[UserIndex].Reputacion.BandidoRep;
	p.Burgues = UserList[UserIndex].Reputacion.BurguesRep;
	p.Ladron = UserList[UserIndex].Reputacion.LadronesRep;
	p.Noble = UserList[UserIndex].Reputacion.NobleRep;
	p.Plebe = UserList[UserIndex].Reputacion.PlebeRep;
	p.Promedio = UserList[UserIndex].Reputacion.Promedio;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "MiniStats" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteMiniStats(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "MiniStats" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::MiniStats p;


	p.CiudadanosMatados= UserList[UserIndex].Faccion.CiudadanosMatados;
	p.CriminalesMatados= UserList[UserIndex].Faccion.CriminalesMatados;

	/* 'TODO : Este valor es calculable, no debería NI EXISTIR, ya sea en el servidor ni en el cliente!!! */
	p.UsuariosMatados = UserList[UserIndex].Stats.UsuariosMatados;

	p.NpcsMuertos = UserList[UserIndex].Stats.NPCsMuertos;

	p.Clase = UserList[UserIndex].clase;
	p.Pena = UserList[UserIndex].Counters.Pena;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "LevelUp" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    skillPoints The number of free skill points the player has. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteLevelUp(int UserIndex, int skillPoints) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "LevelUp" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::LevelUp p;

	p.SkillPoints = skillPoints;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "AddForumMsg" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    title The title of the message to display. */
/* ' @param    message The message to be displayed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAddForumMsg(int UserIndex, eForumMsgType ForumType, std::string & Title, std::string & Author,
		std::string & message) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 02/01/2010 */
	/* 'Writes the "AddForumMsg" message to the given user's outgoing data buffer */
	/* '02/01/2010: ZaMa - Now sends Author and forum type */
	/* '*************************************************** */
	dakara::protocol::server::AddForumMsg p;

	p.ForumType = ForumType;
	p.Title = Title;
	p.Author = Author;
	p.Message = message;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowForumForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowForumForm(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowForumForm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::ShowForumForm p;
	int Visibilidad;
	int CanMakeSticky = 0;


	Visibilidad = eForumVisibility_ieGENERAL_MEMBER;

	if (esCaos(UserIndex) || EsGm(UserIndex)) {
		Visibilidad = Visibilidad | eForumVisibility_ieCAOS_MEMBER;
	}

	if (esArmada(UserIndex) || EsGm(UserIndex)) {
		Visibilidad = Visibilidad | eForumVisibility_ieREAL_MEMBER;
	}

	p.Visibilidad = Visibilidad;

	/* ' Pueden mandar sticky los gms o los del consejo de armada/caos */
	if (EsGm(UserIndex)) {
		CanMakeSticky = 2;
	} else if (UserTienePrivilegio(UserIndex, PlayerType_ChaosCouncil)) {
		CanMakeSticky = 1;
	} else if (UserTienePrivilegio(UserIndex, PlayerType_RoyalCouncil)) {
		CanMakeSticky = 1;
	}

	p.CanMakeSticky = CanMakeSticky;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "SetInvisible" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex The char turning visible / invisible. */
/* ' @param    invisible True if the char is no longer visible, False otherwise. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteSetInvisible(int UserIndex, int CharIndex, bool invisible) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "SetInvisible" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	dakara::protocol::server::SetInvisible p;
	p.charIndex = CharIndex;
	p.invisible = invisible;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "DiceRoll" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDiceRoll(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "DiceRoll" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::DiceRoll p;
	p.Fuerza = UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza];
	p.Agilidad = UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad];
	p.Inteligencia = UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia];
	p.Carisma = UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma];
	p.Constitucion = UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion];
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "MeditateToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteMeditateToggle(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "MeditateToggle" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::MeditateToggle p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "BlindNoMore" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBlindNoMore(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "BlindNoMore" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::BlindNoMore p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "DumbNoMore" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDumbNoMore(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "DumbNoMore" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::DumbNoMore p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "SendSkills" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteSendSkills(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 11/19/09 */
	/* 'Writes the "SendSkills" message to the given user's outgoing data buffer */
	/* '11/19/09: Pato - Now send the percentage of progress of the skills. */
	/* '*************************************************** */

	int i;
	dakara::protocol::server::SendSkills p;
	for (i = (1); i <= (NUMSKILLS); i++) {
		// Skills contiene pares de numero de skill y su porcentaje
		p.Skills.emplace_back(UserList[UserIndex].Stats.UserSkills[i]);
		if (UserList[UserIndex].Stats.UserSkills[i] < MAXSKILLPOINTS) {
			p.Skills.emplace_back(vb6::Int(
							UserList[UserIndex].Stats.ExpSkills[i] * 100
									/ UserList[UserIndex].Stats.EluSkills[i]));
		} else {
			p.Skills.emplace_back(0);
		}
	}
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "TrainerCreatureList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    npcIndex The index of the requested trainer. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteTrainerCreatureList(int UserIndex, int NpcIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "TrainerCreatureList" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	int i;
	std::string str;
	dakara::protocol::server::TrainerCreatureList p;


	for (i = (1); i <= (Npclist[NpcIndex].NroCriaturas); i++) {
		str = str + Npclist[NpcIndex].Criaturas[i].NpcName + SEPARATOR;
	}

	if (vb6::LenB(str) > 0) {
		str = vb6::Left(str, vb6::Len(str) - 1);
	}

	p.Data = str;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "GuildNews" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guildNews The guild's news. */
/* ' @param    enemies The list of the guild's enemies. */
/* ' @param    allies The list of the guild's allies. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildNews(int UserIndex, std::string guildNews, std::vector<std::string> & enemies,
		std::vector<std::string> & allies) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "GuildNews" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string Tmp;
	dakara::protocol::server::GuildNews p;


	p.News = guildNews;

	/* 'Prepare enemies' list */
	for (std::string& x : enemies) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.EnemiesList = Tmp;

	Tmp = "";
	/* 'Prepare allies' list */
	for (std::string& x : allies) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.AlliesList = Tmp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "OfferDetails" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    details Th details of the Peace proposition. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteOfferDetails(int UserIndex, std::string details) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "OfferDetails" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::OfferDetails p;
	p.Details= details;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "AlianceProposalsList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guilds The list of guilds which propossed an alliance. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAlianceProposalsList(int UserIndex, std::vector<std::string> guilds) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "AlianceProposalsList" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string Tmp;
	dakara::protocol::server::AlianceProposalsList p;


	/* ' Prepare guild's list */
	for (auto& x : guilds) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.Data = Tmp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "PeaceProposalsList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guilds The list of guilds which propossed peace. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePeaceProposalsList(int UserIndex, std::vector<std::string> guilds) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "PeaceProposalsList" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string Tmp;

	dakara::protocol::server::PeaceProposalsList p;
	/* ' Prepare guilds' list */
	for (auto& x : guilds) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.Data = Tmp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

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
		int citicensKilled, int criminalsKilled) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CharacterInfo" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::CharacterInfo p;
	p.CharName = charName;
	p.Race = race;
	p.Class = Class;
	p.Gender = gender;
	p.Level = level;
	p.Gold = gold;
	p.Bank = bank;
	p.Reputation = reputation;

	p.PreviousPetitions = previousPetitions;
	p.CurrentGuild = currentGuild;
	p.PreviousGuilds = previousGuilds;

	p.RoyalArmy = RoyalArmy;
	p.ChaosLegion = CaosLegion;

	p.CiudadanosMatados = citicensKilled;
	p.CriminalesMatados = criminalsKilled;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

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
		std::vector<std::string> & joinRequests) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "GuildLeaderInfo" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string Tmp;

	dakara::protocol::server::GuildLeaderInfo p;

	/* ' Prepare guild name's list */
	for (auto& x : guildList) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.GuildList = Tmp;

	/* ' Prepare guild member's list */
	Tmp = "";
	for (auto& x : MemberList) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.MemberList  = Tmp;

	/* ' Store guild news */
	p.GuildNews = guildNews;

	/* ' Prepare the join request's list */
	Tmp = "";
	for (auto& x : joinRequests) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.JoinRequests = Tmp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "GuildLeaderInfo" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    guildList The list of guild names. */
/* ' @param    memberList The list of the guild's members. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildMemberInfo(int UserIndex, std::vector<std::string> & guildList,
		std::vector<std::string> & MemberList) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 21/02/2010 */
	/* 'Writes the "GuildMemberInfo" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string Tmp;
	dakara::protocol::server::GuildMemberInfo p;


	/* ' Prepare guild name's list */
	for (auto& x : guildList) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.GuildList = Tmp;

	/* ' Prepare guild member's list */
	Tmp = "";
	for (auto& x : MemberList) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.MemberList = Tmp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

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
		std::string guildDesc) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "GuildDetails" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string temp;
	dakara::protocol::server::GuildDetails p;

	p.GuildName = GuildName;
	p.Founder = founder;
	p.FoundationDate = foundationDate;
	p.Leader = leader;
	p.URL = URL;
	p.MemberCount = memberCount;
	p.ElectionsOpen = electionsOpen;
	p.Aligment = alignment;
	p.EnemiesCount = enemiesCount;
	p.AlliesCount = AlliesCount;
	p.AntifactionPoints = antifactionPoints;

	for (auto& x : codex) {
		temp = temp + x + SEPARATOR;
	}

	if (vb6::Len(temp) > 1) {
		temp = vb6::Left(temp, vb6::Len(temp) - 1);
	}
	p.Codex = temp;
	p.GuildDesc = guildDesc;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowGuildAlign" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowGuildAlign(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 14/12/2009 */
	/* 'Writes the "ShowGuildAlign" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::ShowGuildAlign p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowGuildFundationForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowGuildFundationForm(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowGuildFundationForm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::ShowGuildFundationForm p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ParalizeOK" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteParalizeOK(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 08/12/07 */
	/* 'Last Modified By: Lucas Tavolaro Ortiz (Tavo) */
	/* 'Writes the "ParalizeOK" message to the given user's outgoing data buffer */
	/* 'And updates user position */
	/* '*************************************************** */

	dakara::protocol::server::ParalizeOK p;
	p.serialize(UserList[UserIndex].outgoingData.get());
	WritePosUpdate(UserIndex);
}

/* '' */
/* ' Writes the "ShowUserRequest" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    details DEtails of the char's request. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowUserRequest(int UserIndex, std::string details) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowUserRequest" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::ShowUserRequest p;
	p.Details = details;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "TradeOK" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteTradeOK(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "TradeOK" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::TradeOK p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "BankOK" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBankOK(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "BankOK" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::BankOK p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ChangeUserTradeSlot" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    ObjIndex The object's index. */
/* ' @param    amount The number of objects offered. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeUserTradeSlot(int UserIndex, int OfferSlot, int ObjIndex, int Amount) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 12/03/09 */
	/* 'Writes the "ChangeUserTradeSlot" message to the given user's outgoing data buffer */
	/* '25/11/2009: ZaMa - Now sends the specific offer slot to be modified. */
	/* '12/03/09: Budi - Ahora se envia MaxDef y MinDef en lugar de sólo Def */
	/* '*************************************************** */

	dakara::protocol::server::ChangeUserTradeSlot p;
	p.OfferSlot =OfferSlot;
	p.ObjIndex=ObjIndex;
	p.Amount=Amount;

	if (ObjIndex > 0) {
		p.GrhIndex=ObjData[ObjIndex].GrhIndex;
		p.ObjType=ObjData[ObjIndex].OBJType;
		p.MaxHit=ObjData[ObjIndex].MaxHIT;
		p.MinHit=ObjData[ObjIndex].MinHIT;
		p.MaxDef=ObjData[ObjIndex].MaxDef;
		p.MinDef=ObjData[ObjIndex].MinDef;
		p.Price=SalePrice(ObjIndex);
		p.ObjName=ObjData[ObjIndex].Name;
		/* ' Borra el item */
	} else {
		p.GrhIndex=0;
		p.ObjType=0;
		p.MaxHit=0;
		p.MinHit=0;
		p.MaxDef=0;
		p.MinDef=0;
		p.Price=0;
		p.ObjName="";
	}
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "SendNight" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteSendNight(int UserIndex, bool night) {
	/* '*************************************************** */
	/* 'Author: Fredy Horacio Treboux (liquid) */
	/* 'Last Modification: 01/08/07 */
	/* 'Writes the "SendNight" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::SendNight p;
	p.Night= night;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "SpawnList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    npcNames The names of the creatures that can be spawned. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteSpawnList(int UserIndex, std::vector<std::string> & npcNames) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "SpawnList" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string Tmp;
	dakara::protocol::server::SpawnList p;


	for (auto& x : npcNames) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.Data = Tmp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowSOSForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowSOSForm(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowSOSForm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string Tmp;
	dakara::protocol::server::ShowSOSForm p;


	for (auto& e : Ayuda) {
		Tmp = Tmp + e + SEPARATOR;
	}

	if (vb6::LenB(Tmp) != 0) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.Data = Tmp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowDenounces" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowDenounces(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 14/11/2010 */
	/* 'Writes the "ShowDenounces" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	//int DenounceIndex;
	std::string DenounceList;
	dakara::protocol::server::ShowDenounces p;


	for (auto& e : Denuncias) {
		DenounceList = DenounceList + e + SEPARATOR;
	}

	if (vb6::LenB(DenounceList) != 0) {
		DenounceList = vb6::Left(DenounceList, vb6::Len(DenounceList) - 1);
	}

	p.Data = DenounceList;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowSOSForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowPartyForm(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 11/26/09 */
	/* 'Writes the "ShowPartyForm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	size_t i;
	std::string Tmp;
	int PI;
	std::vector<int> members;
	dakara::protocol::server::ShowPartyForm p;


	PI = UserList[UserIndex].PartyIndex;
	p.EsLider = vb6::CByte(Parties[PI]->EsPartyLeader(UserIndex));

	if (PI > 0) {
		Parties[PI]->ObtenerMiembrosOnline(members);
		for (i = (0); i < members.size(); i++) {
			if (members[i] > 0) {
				Tmp = Tmp + UserList[members[i]].Name + " ("
						+ vb6::CStr(vb6::Fix(Parties[PI]->MiExperiencia(members[i]))) + ")" + SEPARATOR;
			}
		}
	}

	if (vb6::LenB(Tmp) != 0) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.Data= Tmp;
	p.Exp= Parties[PI]->ObtenerExperienciaTotal();
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowMOTDEditionForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    currentMOTD The current Message Of The Day. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowMOTDEditionForm(int UserIndex, std::string currentMOTD) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowMOTDEditionForm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::ShowMOTDEditionForm p;
	p.Data=currentMOTD;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "ShowGMPanelForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowGMPanelForm(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowGMPanelForm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::ShowGMPanelForm p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "UserNameList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    userNameList List of user names. */
/* ' @param    Cant Number of names to send. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserNameList(int UserIndex, std::vector<std::string> & userNamesList, int cant) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 NIGO: */
	/* 'Writes the "UserNameList" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	int i;
	std::string Tmp;
	dakara::protocol::server::UserNameList p;


	/* ' Prepare user's names list */
	for (i = (1); i <= (cant); i++) {
		Tmp = Tmp + userNamesList[i] + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	p.Data = Tmp;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "Pong" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePong(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "Pong" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	dakara::protocol::server::Pong p;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Flushes the outgoing data buffer of the user. */
/* ' */
/* ' @param    UserIndex User whose outgoing data buffer will be flushed. */

void FlushBuffer(int UserIndex) {
	if (UserList[UserIndex].sockctx) {
		FlushBuffer(UserList[UserIndex].sockctx);
		/*
	} else {
		throw std::runtime_error("integrity error: UserList[UserIndex].sockctx == nullptr UserIndex=" + vb6::CStr(UserIndex));
		*/
	}
}


/* '' */
/* ' Writes the "StopWorking" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */

void WriteStopWorking(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 21/02/2010 */
	/* ' */
	/* '*************************************************** */

	dakara::protocol::server::StopWorking p;
	p.serialize(UserList[UserIndex].outgoingData.get());

}

/* '' */
/* ' Writes the "CancelOfferItem" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Slot      The slot to cancel. */

void WriteCancelOfferItem(int UserIndex, int Slot) {
	/* '*************************************************** */
	/* 'Author: Torres Patricio (Pato) */
	/* 'Last Modification: 05/03/2010 */
	/* ' */
	/* '*************************************************** */

	dakara::protocol::server::CancelOfferItem p;
	p.Slot = Slot;
	p.serialize(UserList[UserIndex].outgoingData.get());

}

/* '' */
/* ' Writes the "RecordDetails" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRecordDetails(int UserIndex, int RecordIndex) {
	/* '*************************************************** */
	/* 'Author: Amraphen */
	/* 'Last Modification: 29/11/2010 */
	/* 'Writes the "RecordDetails" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	int i;
	int tIndex;
	std::string tmpStr;
	boost::posix_time::time_duration TempDate;
	dakara::protocol::server::RecordDetails p;


	/* 'Creador y motivo */
	p.Creador = Records[RecordIndex].Creador;
	p.Motivo = Records[RecordIndex].Motivo;

	tIndex = NameIndex(Records[RecordIndex].Usuario);

	/* 'Status del pj (online?) */
	p.Online = (tIndex > 0);

	/* 'Escribo la IP según el estado del personaje */
	if (tIndex > 0) {
		/* 'La IP Actual */
		tmpStr = UserList[tIndex].ip;
		/* 'String nulo */
	} else {
		tmpStr = "";
	}
	p.IP = tmpStr;

	/* 'Escribo tiempo online según el estado del personaje */
	if (tIndex > 0) {
		/* 'Tiempo logueado. */
		TempDate = vb6::Now() - UserList[tIndex].LogOnTime;
		//tmpStr = vb6::Hour(TempDate) + ":" + vb6::Minute(TempDate) + ":" + vb6::Second(TempDate);
		tmpStr = boost::posix_time::to_simple_string(TempDate);
	} else {
		/* 'Envío string nulo. */
		tmpStr = "";
	}
	p.OnlineTime = tmpStr;

	/* 'Escribo observaciones: */
	tmpStr = "";
	if (Records[RecordIndex].NumObs) {
		for (i = (1); i <= (Records[RecordIndex].NumObs); i++) {
			tmpStr = tmpStr + Records[RecordIndex].Obs[i].Creador + "> "
					+ Records[RecordIndex].Obs[i].Detalles + vbCrLf;
		}

		tmpStr = vb6::Left(tmpStr, vb6::Len(tmpStr) - 1);
	}
	p.Obs = tmpStr;
	p.serialize(UserList[UserIndex].outgoingData.get());
}

/* '' */
/* ' Writes the "RecordList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRecordList(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Amraphen */
	/* 'Last Modification: 29/11/2010 */
	/* 'Writes the "RecordList" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	int i;

	dakara::protocol::server::RecordList p;
	for (i = (1); i <= (NumRecords); i++) {
		p.addItem(Records[i].Usuario);
	}
	p.serialize(UserList[UserIndex].outgoingData.get());
}

