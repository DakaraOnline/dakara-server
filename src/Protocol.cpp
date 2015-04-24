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

#include "Protocol.h"
#include "allheaders.h"

static const char* SEPARATORC = "\0";
const std::string SEPARATOR{SEPARATORC, SEPARATORC + 1};

void WriteMultiMessage(int UserIndex, int MessageIndex, int Arg1, int Arg2, int Arg3,
		std::string StringArg1) {
	/* '*************************************************** */
	/* 'Author: Unknown */
	/* 'Last Modification: - */
	/* ' */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_MultiMessage);
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
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "Logged" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_Logged);

	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].clase);
}

/* '' */
/* ' Writes the "RemoveDialogs" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRemoveAllDialogs(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "RemoveDialogs" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_RemoveDialogs);
}

/* '' */
/* ' Writes the "RemoveCharDialog" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character whose dialog will be removed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteRemoveCharDialog(int UserIndex, int CharIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "RemoveCharDialog" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageRemoveCharDialog(CharIndex));
}

/* '' */
/* ' Writes the "NavigateToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteNavigateToggle(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "NavigateToggle" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_NavigateToggle);
}

/* '' */
/* ' Writes the "Disconnect" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteDisconnect(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "Disconnect" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_Disconnect);
}

/* '' */
/* ' Writes the "UserOfferConfirm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserOfferConfirm(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 14/12/2009 */
	/* 'Writes the "UserOfferConfirm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UserOfferConfirm);
}

/* '' */
/* ' Writes the "CommerceEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCommerceEnd(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CommerceEnd" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_CommerceEnd);
}

/* '' */
/* ' Writes the "BankEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBankEnd(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "BankEnd" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_BankEnd);
}

/* '' */
/* ' Writes the "CommerceInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCommerceInit(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CommerceInit" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_CommerceInit);
}

/* '' */
/* ' Writes the "BankInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteBankInit(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "BankInit" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_BankInit);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Stats.Banco);
}

/* '' */
/* ' Writes the "UserCommerceInit" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCommerceInit(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UserCommerceInit" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UserCommerceInit);
	UserList[UserIndex].outgoingData->WriteUnicodeString(UserList[UserIndex].ComUsu.DestNick);
}

/* '' */
/* ' Writes the "UserCommerceEnd" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCommerceEnd(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UserCommerceEnd" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UserCommerceEnd);
}

/* '' */
/* ' Writes the "ShowBlacksmithForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowBlacksmithForm(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowBlacksmithForm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowBlacksmithForm);
}

/* '' */
/* ' Writes the "ShowCarpenterForm" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowCarpenterForm(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowCarpenterForm" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowCarpenterForm);
}

/* '' */
/* ' Writes the "UpdateSta" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateSta(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UpdateMana" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateSta);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MinSta);
}

/* '' */
/* ' Writes the "UpdateMana" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateMana(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UpdateMana" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateMana);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MinMAN);
}

/* '' */
/* ' Writes the "UpdateHP" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateHP(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UpdateMana" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateHP);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MinHp);
}

/* '' */
/* ' Writes the "UpdateGold" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateGold(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UpdateGold" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateGold);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Stats.GLD);
}

/* '' */
/* ' Writes the "UpdateBankGold" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateBankGold(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 14/12/2009 */
	/* 'Writes the "UpdateBankGold" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateBankGold);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Stats.Banco);
}

/* '' */
/* ' Writes the "UpdateExp" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateExp(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UpdateExp" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateExp);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Stats.Exp);
}

/* '' */
/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateStrenghtAndDexterity(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 11/26/09 */
	/* 'Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateStrenghtAndDexterity);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza]);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad]);
}

/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateDexterity(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 11/26/09 */
	/* 'Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateDexterity);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad]);
}

/* ' Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUpdateStrenght(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 11/26/09 */
	/* 'Writes the "UpdateStrenghtAndDexterity" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateStrenght);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza]);
}

/* '' */
/* ' Writes the "ChangeMap" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    map The new map to load. */
/* ' @param    version The version of the map in the server to check if client is properly updated. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteChangeMap(int UserIndex, int Map, int version) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ChangeMap" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ChangeMap);
	UserList[UserIndex].outgoingData->WriteInteger(Map);
	UserList[UserIndex].outgoingData->WriteInteger(version);
}

/* '' */
/* ' Writes the "PosUpdate" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePosUpdate(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "PosUpdate" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_PosUpdate);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Pos.X);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Pos.Y);
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
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ChatOverHead" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(
			PrepareMessageChatOverHead(Chat, CharIndex, color));
}

/* '' */
/* ' Writes the "ConsoleMsg" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @param    FontIndex Index of the FONTTYPE structure to use. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteConsoleMsg(int UserIndex, std::string Chat, FontTypeNames FontIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ConsoleMsg" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageConsoleMsg(Chat, FontIndex));
}

void WriteCommerceChat(int UserIndex, std::string Chat, FontTypeNames FontIndex) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ConsoleMsg" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareCommerceConsoleMsg(Chat, FontIndex));
}

/* '' */
/* ' Writes the "GuildChat" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildChat(int UserIndex, std::string Chat) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "GuildChat" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageGuildChat(Chat));
}

/* '' */
/* ' Writes the "ShowMessageBox" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    Message Text to be displayed in the message box. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteShowMessageBox(int UserIndex, std::string message) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ShowMessageBox" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowMessageBox);
	UserList[UserIndex].outgoingData->WriteUnicodeString(message);
}

/* '' */
/* ' Writes the "UserIndexInServer" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserIndexInServer(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UserIndexInServer" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UserIndexInServer);
	UserList[UserIndex].outgoingData->WriteInteger(UserIndex);
}

/* '' */
/* ' Writes the "UserCharIndexInServer" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteUserCharIndexInServer(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "UserIndexInServer" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UserCharIndexInServer);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Char.CharIndex);
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
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CharacterCreate" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(
			PrepareMessageCharacterCreate(body, Head, heading, CharIndex, X, Y, weapon, shield, FX, FXLoops,
					helmet, Name, NickColor, Privileges));
}

/* '' */
/* ' Writes the "CharacterRemove" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character to be removed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteCharacterRemove(int UserIndex, int CharIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CharacterRemove" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageCharacterRemove(CharIndex));
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
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CharacterMove" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageCharacterMove(CharIndex, X, Y));
}

void WriteForceCharMove(int UserIndex, eHeading Direccion) {
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 26/03/2009 */
	/* 'Writes the "ForceCharMove" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageForceCharMove(Direccion));
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
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "CharacterChange" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(
			PrepareMessageCharacterChange(body, Head, heading, CharIndex, weapon, shield, FX, FXLoops,
					helmet));
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
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ObjectCreate" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageObjectCreate(GrhIndex, X, Y));
}

/* '' */
/* ' Writes the "ObjectDelete" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteObjectDelete(int UserIndex, int X, int Y) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "ObjectDelete" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageObjectDelete(X, Y));
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
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "BlockPosition" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_BlockPosition);
	UserList[UserIndex].outgoingData->WriteByte(X);
	UserList[UserIndex].outgoingData->WriteByte(Y);
	UserList[UserIndex].outgoingData->WriteBoolean(Blocked);
}

/* '' */
/* ' Writes the "PlayMidi" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    midi The midi to be played. */
/* ' @param    loops Number of repets for the midi. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePlayMidi(int UserIndex, int midi, int loops) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "PlayMidi" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessagePlayMidi(midi, loops));
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
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 08/08/07 */
	/* 'Last Modified by: Rapsodius */
	/* 'Added X and Y positions for 3D Sounds */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessagePlayWave(wave, X, Y));
}

/* '' */
/* ' Writes the "GuildList" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    GuildList List of guilds to be sent. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteGuildList(int UserIndex, std::vector<std::string> & guildList) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "GuildList" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	std::string Tmp;
	int i;

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_guildList);

	/* ' Prepare guild name's list */
	for (i = 0; i < (int)guildList.size(); i++) {
		Tmp = Tmp + guildList[i] + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
}

/* '' */
/* ' Writes the "AreaChanged" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WriteAreaChanged(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "AreaChanged" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_AreaChanged);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Pos.X);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Pos.Y);
}

/* '' */
/* ' Writes the "PauseToggle" message to the given user's outgoing data buffer. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

void WritePauseToggle(int UserIndex) {
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "PauseToggle" message to the given user's outgoing data buffer */
	/* '*************************************************** */

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessagePauseToggle());
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

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageRainToggle());
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

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageCreateFX(CharIndex, FX, FXLoops));
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateUserStats);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MaxHp);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MinHp);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MaxMAN);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MinMAN);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MaxSta);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.MinSta);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Stats.GLD);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.ELV);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Stats.ELU);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Stats.Exp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_WorkRequestTarget);
	UserList[UserIndex].outgoingData->WriteByte(Skill);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ChangeInventorySlot);
	UserList[UserIndex].outgoingData->WriteByte(Slot);

	int ObjIndex;
	struct ObjData obData;

	ObjIndex = UserList[UserIndex].Invent.Object[Slot].ObjIndex;

	if (ObjIndex > 0) {
		obData = ObjData[ObjIndex];
	}

	UserList[UserIndex].outgoingData->WriteInteger(ObjIndex);
	UserList[UserIndex].outgoingData->WriteUnicodeString(obData.Name);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Invent.Object[Slot].Amount);
	UserList[UserIndex].outgoingData->WriteBoolean(UserList[UserIndex].Invent.Object[Slot].Equipped);
	UserList[UserIndex].outgoingData->WriteInteger(obData.GrhIndex);
	UserList[UserIndex].outgoingData->WriteByte(obData.OBJType);
	UserList[UserIndex].outgoingData->WriteInteger(obData.MaxHIT);
	UserList[UserIndex].outgoingData->WriteInteger(obData.MinHIT);
	UserList[UserIndex].outgoingData->WriteInteger(obData.MaxDef);
	UserList[UserIndex].outgoingData->WriteInteger(obData.MinDef);
	UserList[UserIndex].outgoingData->WriteSingle(SalePrice(ObjIndex));
}

void WriteAddSlots(int UserIndex, eMochilas Mochila) {
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 01/12/09 */
	/* 'Writes the "AddSlots" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_AddSlots);
	UserList[UserIndex].outgoingData->WriteByte(Mochila);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ChangeBankSlot);
	UserList[UserIndex].outgoingData->WriteByte(Slot);

	int ObjIndex;
	struct ObjData obData;

	ObjIndex = UserList[UserIndex].BancoInvent.Object[Slot].ObjIndex;

	UserList[UserIndex].outgoingData->WriteInteger(ObjIndex);

	if (ObjIndex > 0) {
		obData = ObjData[ObjIndex];
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(obData.Name);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].BancoInvent.Object[Slot].Amount);
	UserList[UserIndex].outgoingData->WriteInteger(obData.GrhIndex);
	UserList[UserIndex].outgoingData->WriteByte(obData.OBJType);
	UserList[UserIndex].outgoingData->WriteInteger(obData.MaxHIT);
	UserList[UserIndex].outgoingData->WriteInteger(obData.MinHIT);
	UserList[UserIndex].outgoingData->WriteInteger(obData.MaxDef);
	UserList[UserIndex].outgoingData->WriteInteger(obData.MinDef);
	UserList[UserIndex].outgoingData->WriteLong(obData.Valor);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ChangeSpellSlot);
	UserList[UserIndex].outgoingData->WriteByte(Slot);
	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.UserHechizos[Slot]);

	if (UserList[UserIndex].Stats.UserHechizos[Slot] > 0) {
		UserList[UserIndex].outgoingData->WriteUnicodeString(
				Hechizos[UserList[UserIndex].Stats.UserHechizos[Slot]].Nombre);
	} else {
		UserList[UserIndex].outgoingData->WriteUnicodeString("(None)");
	}
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_Atributes);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza]);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad]);
	UserList[UserIndex].outgoingData->WriteByte(
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia]);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma]);
	UserList[UserIndex].outgoingData->WriteByte(
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion]);
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

	int i;
	struct ObjData Obj;
	std::vector<int> validIndexes;
	int Count = 0;

	validIndexes.resize(0);
	validIndexes.resize(1 + vb6::UBound(ArmasHerrero));

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_BlacksmithWeapons);

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

	/* ' Write the number of objects in the list */
	UserList[UserIndex].outgoingData->WriteInteger(Count);

	/* ' Write the needed data of each object */
	for (i = (1); i <= (Count); i++) {
		Obj = ObjData[ArmasHerrero[validIndexes[i]]];
		UserList[UserIndex].outgoingData->WriteUnicodeString(Obj.Name);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.GrhIndex);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.LingH);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.LingP);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.LingO);
		UserList[UserIndex].outgoingData->WriteInteger(ArmasHerrero[validIndexes[i]]);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.Upgrade);
	}
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

	int i;
	struct ObjData Obj;
	std::vector<int> validIndexes;
	int Count = 0;

	validIndexes.resize(0);
	validIndexes.resize(1 + vb6::UBound(ArmadurasHerrero));

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_BlacksmithArmors);

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

	/* ' Write the number of objects in the list */
	UserList[UserIndex].outgoingData->WriteInteger(Count);

	/* ' Write the needed data of each object */
	for (i = (1); i <= (Count); i++) {
		Obj = ObjData[ArmadurasHerrero[validIndexes[i]]];
		UserList[UserIndex].outgoingData->WriteUnicodeString(Obj.Name);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.GrhIndex);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.LingH);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.LingP);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.LingO);
		UserList[UserIndex].outgoingData->WriteInteger(ArmadurasHerrero[validIndexes[i]]);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.Upgrade);
	}
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

	int i;
	struct ObjData Obj;
	std::vector<int> validIndexes;
	int Count = 0;

	validIndexes.resize(0);
	validIndexes.resize(1 + vb6::UBound(ObjCarpintero));

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_CarpenterObjects);

	for (i = (1); i <= (vb6::UBound(ObjCarpintero)); i++) {
		/* ' Can the user create this object? If so add it to the list.... */
		if (ObjData[ObjCarpintero[i]].SkCarpinteria
				<= UserList[UserIndex].Stats.UserSkills[eSkill_Carpinteria]
						/ ModCarpinteria(UserList[UserIndex].clase)) {
			Count = Count + 1;
			validIndexes[Count] = i;
		}
	}

	/* ' Write the number of objects in the list */
	UserList[UserIndex].outgoingData->WriteInteger(Count);

	/* ' Write the needed data of each object */
	for (i = (1); i <= (Count); i++) {
		Obj = ObjData[ObjCarpintero[validIndexes[i]]];
		UserList[UserIndex].outgoingData->WriteUnicodeString(Obj.Name);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.GrhIndex);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.Madera);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.MaderaElfica);
		UserList[UserIndex].outgoingData->WriteInteger(ObjCarpintero[validIndexes[i]]);
		UserList[UserIndex].outgoingData->WriteInteger(Obj.Upgrade);
	}
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_RestOK);
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

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageErrorMsg(message));
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_Blind);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_Dumb);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowSignal);
	UserList[UserIndex].outgoingData->WriteUnicodeString(ObjData[ObjIndex].texto);
	UserList[UserIndex].outgoingData->WriteInteger(ObjData[ObjIndex].GrhSecundario);
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

	struct ObjData ObjInfo;

	if (Obj.ObjIndex >= vb6::LBound(ObjData) && Obj.ObjIndex <= vb6::UBound(ObjData)) {
		ObjInfo = ObjData[Obj.ObjIndex];
	}

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ChangeNPCInventorySlot);
	UserList[UserIndex].outgoingData->WriteByte(Slot);
	UserList[UserIndex].outgoingData->WriteUnicodeString(ObjInfo.Name);
	UserList[UserIndex].outgoingData->WriteInteger(Obj.Amount);
	UserList[UserIndex].outgoingData->WriteSingle(price);
	UserList[UserIndex].outgoingData->WriteInteger(ObjInfo.GrhIndex);
	UserList[UserIndex].outgoingData->WriteInteger(Obj.ObjIndex);
	UserList[UserIndex].outgoingData->WriteByte(ObjInfo.OBJType);
	UserList[UserIndex].outgoingData->WriteInteger(ObjInfo.MaxHIT);
	UserList[UserIndex].outgoingData->WriteInteger(ObjInfo.MinHIT);
	UserList[UserIndex].outgoingData->WriteInteger(ObjInfo.MaxDef);
	UserList[UserIndex].outgoingData->WriteInteger(ObjInfo.MinDef);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UpdateHungerAndThirst);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.MaxAGU);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.MinAGU);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.MaxHam);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.MinHam);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_Fame);

	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Reputacion.AsesinoRep);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Reputacion.BandidoRep);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Reputacion.BurguesRep);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Reputacion.LadronesRep);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Reputacion.NobleRep);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Reputacion.PlebeRep);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Reputacion.Promedio);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_MiniStats);

	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Faccion.CiudadanosMatados);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Faccion.CriminalesMatados);

	/* 'TODO : Este valor es calculable, no debería NI EXISTIR, ya sea en el servidor ni en el cliente!!! */
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Stats.UsuariosMatados);

	UserList[UserIndex].outgoingData->WriteInteger(UserList[UserIndex].Stats.NPCsMuertos);

	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].clase);
	UserList[UserIndex].outgoingData->WriteLong(UserList[UserIndex].Counters.Pena);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_LevelUp);
	UserList[UserIndex].outgoingData->WriteInteger(skillPoints);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_AddForumMsg);
	UserList[UserIndex].outgoingData->WriteByte(ForumType);
	UserList[UserIndex].outgoingData->WriteUnicodeString(Title);
	UserList[UserIndex].outgoingData->WriteUnicodeString(Author);
	UserList[UserIndex].outgoingData->WriteUnicodeString(message);
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

	int Visibilidad;
	int CanMakeSticky = 0;

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowForumForm);

	Visibilidad = eForumVisibility_ieGENERAL_MEMBER;

	if (esCaos(UserIndex) || EsGm(UserIndex)) {
		Visibilidad = Visibilidad || eForumVisibility_ieCAOS_MEMBER;
	}

	if (esArmada(UserIndex) || EsGm(UserIndex)) {
		Visibilidad = Visibilidad || eForumVisibility_ieREAL_MEMBER;
	}

	UserList[UserIndex].outgoingData->WriteByte(Visibilidad);

	/* ' Pueden mandar sticky los gms o los del consejo de armada/caos */
	if (EsGm(UserIndex)) {
		CanMakeSticky = 2;
	} else if (UserTienePrivilegio(UserIndex, PlayerType_ChaosCouncil)) {
		CanMakeSticky = 1;
	} else if (UserTienePrivilegio(UserIndex, PlayerType_RoyalCouncil)) {
		CanMakeSticky = 1;
	}

	UserList[UserIndex].outgoingData->WriteByte(CanMakeSticky);
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

	UserList[UserIndex].outgoingData->WriteBinaryFixed(PrepareMessageSetInvisible(CharIndex, invisible));
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_DiceRoll);

	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza]);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad]);
	UserList[UserIndex].outgoingData->WriteByte(
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia]);
	UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma]);
	UserList[UserIndex].outgoingData->WriteByte(
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion]);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_MeditateToggle);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_BlindNoMore);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_DumbNoMore);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_SendSkills);

	for (i = (1); i <= (NUMSKILLS); i++) {
		UserList[UserIndex].outgoingData->WriteByte(UserList[UserIndex].Stats.UserSkills[i]);
		if (UserList[UserIndex].Stats.UserSkills[i] < MAXSKILLPOINTS) {
			UserList[UserIndex].outgoingData->WriteByte(
					vb6::Int(
							UserList[UserIndex].Stats.ExpSkills[i] * 100
									/ UserList[UserIndex].Stats.EluSkills[i]));
		} else {
			UserList[UserIndex].outgoingData->WriteByte(0);
		}
	}
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_TrainerCreatureList);

	for (i = (1); i <= (Npclist[NpcIndex].NroCriaturas); i++) {
		str = str + Npclist[NpcIndex].Criaturas[i].NpcName + SEPARATOR;
	}

	if (vb6::LenB(str) > 0) {
		str = vb6::Left(str, vb6::Len(str) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(str);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_guildNews);

	UserList[UserIndex].outgoingData->WriteUnicodeString(guildNews);

	/* 'Prepare enemies' list */
	for (std::string& x : enemies) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);

	Tmp = "";
	/* 'Prepare allies' list */
	for (std::string& x : allies) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_OfferDetails);
	UserList[UserIndex].outgoingData->WriteUnicodeString(details);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_AlianceProposalsList);

	/* ' Prepare guild's list */
	for (auto& x : guilds) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_PeaceProposalsList);

	/* ' Prepare guilds' list */
	for (auto& x : guilds) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_CharacterInfo);

	UserList[UserIndex].outgoingData->WriteUnicodeString(charName);
	UserList[UserIndex].outgoingData->WriteByte(race);
	UserList[UserIndex].outgoingData->WriteByte(Class);
	UserList[UserIndex].outgoingData->WriteByte(gender);

	UserList[UserIndex].outgoingData->WriteByte(level);
	UserList[UserIndex].outgoingData->WriteLong(gold);
	UserList[UserIndex].outgoingData->WriteLong(bank);
	UserList[UserIndex].outgoingData->WriteLong(reputation);

	UserList[UserIndex].outgoingData->WriteUnicodeString(previousPetitions);
	UserList[UserIndex].outgoingData->WriteUnicodeString(currentGuild);
	UserList[UserIndex].outgoingData->WriteUnicodeString(previousGuilds);

	UserList[UserIndex].outgoingData->WriteBoolean(RoyalArmy);
	UserList[UserIndex].outgoingData->WriteBoolean(CaosLegion);

	UserList[UserIndex].outgoingData->WriteLong(citicensKilled);
	UserList[UserIndex].outgoingData->WriteLong(criminalsKilled);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_GuildLeaderInfo);

	/* ' Prepare guild name's list */
	for (auto& x : guildList) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);

	/* ' Prepare guild member's list */
	Tmp = "";
	for (auto& x : MemberList) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);

	/* ' Store guild news */
	UserList[UserIndex].outgoingData->WriteUnicodeString(guildNews);

	/* ' Prepare the join request's list */
	Tmp = "";
	for (auto& x : joinRequests) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_GuildMemberInfo);

	/* ' Prepare guild name's list */
	for (auto& x : guildList) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);

	/* ' Prepare guild member's list */
	Tmp = "";
	for (auto& x : MemberList) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_GuildDetails);

	UserList[UserIndex].outgoingData->WriteUnicodeString(GuildName);
	UserList[UserIndex].outgoingData->WriteUnicodeString(founder);
	UserList[UserIndex].outgoingData->WriteUnicodeString(foundationDate);
	UserList[UserIndex].outgoingData->WriteUnicodeString(leader);
	UserList[UserIndex].outgoingData->WriteUnicodeString(URL);

	UserList[UserIndex].outgoingData->WriteInteger(memberCount);
	UserList[UserIndex].outgoingData->WriteBoolean(electionsOpen);

	UserList[UserIndex].outgoingData->WriteUnicodeString(alignment);

	UserList[UserIndex].outgoingData->WriteInteger(enemiesCount);
	UserList[UserIndex].outgoingData->WriteInteger(AlliesCount);

	UserList[UserIndex].outgoingData->WriteUnicodeString(antifactionPoints);

	for (auto& x : codex) {
		temp = temp + x + SEPARATOR;
	}

	if (vb6::Len(temp) > 1) {
		temp = vb6::Left(temp, vb6::Len(temp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(temp);

	UserList[UserIndex].outgoingData->WriteUnicodeString(guildDesc);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowGuildAlign);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowGuildFundationForm);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ParalizeOK);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowUserRequest);

	UserList[UserIndex].outgoingData->WriteUnicodeString(details);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_TradeOK);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_BankOK);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ChangeUserTradeSlot);

	UserList[UserIndex].outgoingData->WriteByte(OfferSlot);
	UserList[UserIndex].outgoingData->WriteInteger(ObjIndex);
	UserList[UserIndex].outgoingData->WriteLong(Amount);

	if (ObjIndex > 0) {
		UserList[UserIndex].outgoingData->WriteInteger(ObjData[ObjIndex].GrhIndex);
		UserList[UserIndex].outgoingData->WriteByte(ObjData[ObjIndex].OBJType);
		UserList[UserIndex].outgoingData->WriteInteger(ObjData[ObjIndex].MaxHIT);
		UserList[UserIndex].outgoingData->WriteInteger(ObjData[ObjIndex].MinHIT);
		UserList[UserIndex].outgoingData->WriteInteger(ObjData[ObjIndex].MaxDef);
		UserList[UserIndex].outgoingData->WriteInteger(ObjData[ObjIndex].MinDef);
		UserList[UserIndex].outgoingData->WriteLong(SalePrice(ObjIndex));
		UserList[UserIndex].outgoingData->WriteUnicodeString(ObjData[ObjIndex].Name);
		/* ' Borra el item */
	} else {
		UserList[UserIndex].outgoingData->WriteInteger(0);
		UserList[UserIndex].outgoingData->WriteByte(0);
		UserList[UserIndex].outgoingData->WriteInteger(0);
		UserList[UserIndex].outgoingData->WriteInteger(0);
		UserList[UserIndex].outgoingData->WriteInteger(0);
		UserList[UserIndex].outgoingData->WriteInteger(0);
		UserList[UserIndex].outgoingData->WriteLong(0);
		UserList[UserIndex].outgoingData->WriteUnicodeString("");
	}
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_SendNight);
	UserList[UserIndex].outgoingData->WriteBoolean(night);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_SpawnList);

	for (auto& x : npcNames) {
		Tmp = Tmp + x + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowSOSForm);

	for (auto& e : Ayuda) {
		Tmp = Tmp + e + SEPARATOR;
	}

	if (vb6::LenB(Tmp) != 0) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowDenounces);

	for (auto& e : Denuncias) {
		DenounceList = DenounceList + e + SEPARATOR;
	}

	if (vb6::LenB(DenounceList) != 0) {
		DenounceList = vb6::Left(DenounceList, vb6::Len(DenounceList) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(DenounceList);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowPartyForm);

	PI = UserList[UserIndex].PartyIndex;
	UserList[UserIndex].outgoingData->WriteByte(vb6::CByte(Parties[PI]->EsPartyLeader(UserIndex)));

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

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
	UserList[UserIndex].outgoingData->WriteLong(Parties[PI]->ObtenerExperienciaTotal());
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowMOTDEditionForm);

	UserList[UserIndex].outgoingData->WriteUnicodeString(currentMOTD);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_ShowGMPanelForm);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_UserNameList);

	/* ' Prepare user's names list */
	for (i = (1); i <= (cant); i++) {
		Tmp = Tmp + userNamesList[i] + SEPARATOR;
	}

	if (vb6::Len(Tmp)) {
		Tmp = vb6::Left(Tmp, vb6::Len(Tmp) - 1);
	}

	UserList[UserIndex].outgoingData->WriteUnicodeString(Tmp);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_Pong);
}

/* '' */
/* ' Flushes the outgoing data buffer of the user. */
/* ' */
/* ' @param    UserIndex User whose outgoing data buffer will be flushed. */

void FlushBuffer(int UserIndex) {
	if (UserList[UserIndex].sockctx) {
		FlushBuffer(UserList[UserIndex].sockctx);
	} else {
		throw std::runtime_error("integrity error: UserList[UserIndex].sockctx == nullptr UserIndex=" + vb6::CStr(UserIndex));
	}
}

/* '' */
/* ' Prepares the "SetInvisible" message and returns it. */
/* ' */
/* ' @param    CharIndex The char turning visible / invisible. */
/* ' @param    invisible True if the char is no longer visible, False otherwise. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The message is written to no outgoing buffer, but only prepared in a single string to be easily sent to several clients. */

std::string PrepareMessageSetInvisible(int CharIndex, bool invisible) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "SetInvisible" message and returns it. */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_SetInvisible);

	auxiliarBuffer.WriteInteger(CharIndex);
	auxiliarBuffer.WriteBoolean(invisible);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

std::string PrepareMessageCharacterChangeNick(int CharIndex, std::string newNick) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Budi */
	/* 'Last Modification: 07/23/09 */
	/* 'Prepares the "Change Nick" message and returns it. */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_CharacterChangeNick);

	auxiliarBuffer.WriteInteger(CharIndex);
	auxiliarBuffer.WriteUnicodeString(newNick);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "ChatOverHead" message and returns it. */
/* ' */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @param    CharIndex The character uppon which the chat will be displayed. */
/* ' @param    Color The color to be used when displaying the chat. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The message is written to no outgoing buffer, but only prepared in a single string to be easily sent to several clients. */

std::string PrepareMessageChatOverHead(std::string Chat, int CharIndex, int color) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "ChatOverHead" message and returns it. */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_ChatOverHead);
	auxiliarBuffer.WriteUnicodeString(Chat);
	auxiliarBuffer.WriteInteger(CharIndex);

	/* ' Write rgb channels and save one byte from long :D */
	auxiliarBuffer.WriteByte(color & 0xFF);
	auxiliarBuffer.WriteByte((color & 0xFF00) / 0x100);
	auxiliarBuffer.WriteByte((color & 0xFF0000) / 0x10000);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "ConsoleMsg" message and returns it. */
/* ' */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @param    FontIndex Index of the FONTTYPE structure to use. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageConsoleMsg(std::string Chat, FontTypeNames FontIndex) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "ConsoleMsg" message and returns it. */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_ConsoleMsg);
	auxiliarBuffer.WriteUnicodeString(Chat);
	auxiliarBuffer.WriteByte(FontIndex);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

std::string PrepareCommerceConsoleMsg(std::string & Chat, FontTypeNames FontIndex) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 03/12/2009 */
	/* 'Prepares the "CommerceConsoleMsg" message and returns it. */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_CommerceChat);
	auxiliarBuffer.WriteUnicodeString(Chat);
	auxiliarBuffer.WriteByte(FontIndex);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "CreateFX" message and returns it. */
/* ' */
/* ' @param    UserIndex User to which the message is intended. */
/* ' @param    CharIndex Character upon which the FX will be created. */
/* ' @param    FX FX index to be displayed over the new character. */
/* ' @param    FXLoops Number of times the FX should be rendered. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageCreateFX(int CharIndex, int FX, int FXLoops) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "CreateFX" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_CreateFX);
	auxiliarBuffer.WriteInteger(CharIndex);
	auxiliarBuffer.WriteInteger(FX);
	auxiliarBuffer.WriteInteger(FXLoops);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "PlayWave" message and returns it. */
/* ' */
/* ' @param    wave The wave to be played. */
/* ' @param    X The X position in map coordinates from where the sound comes. */
/* ' @param    Y The Y position in map coordinates from where the sound comes. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessagePlayWave(int wave, int X, int Y) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 08/08/07 */
	/* 'Last Modified by: Rapsodius */
	/* 'Added X and Y positions for 3D Sounds */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_PlayWave);
	auxiliarBuffer.WriteByte(wave);
	auxiliarBuffer.WriteByte(X);
	auxiliarBuffer.WriteByte(Y);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "GuildChat" message and returns it. */
/* ' */
/* ' @param    Chat Text to be displayed over the char's head. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageGuildChat(std::string Chat) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "GuildChat" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_GuildChat);
	auxiliarBuffer.WriteUnicodeString(Chat);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "ShowMessageBox" message and returns it. */
/* ' */
/* ' @param    Message Text to be displayed in the message box. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageShowMessageBox(std::string Chat) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Fredy Horacio Treboux (liquid) */
	/* 'Last Modification: 01/08/07 */
	/* 'Prepares the "ShowMessageBox" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_ShowMessageBox);
	auxiliarBuffer.WriteUnicodeString(Chat);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "PlayMidi" message and returns it. */
/* ' */
/* ' @param    midi The midi to be played. */
/* ' @param    loops Number of repets for the midi. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessagePlayMidi(int midi, int loops) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "GuildChat" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_PlayMidi);
	auxiliarBuffer.WriteInteger(midi);
	auxiliarBuffer.WriteInteger(loops);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "PauseToggle" message and returns it. */
/* ' */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessagePauseToggle() {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "PauseToggle" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_PauseToggle);
	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "RainToggle" message and returns it. */
/* ' */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageRainToggle() {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "RainToggle" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_RainToggle);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "ObjectDelete" message and returns it. */
/* ' */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageObjectDelete(int X, int Y) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "ObjectDelete" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_ObjectDelete);
	auxiliarBuffer.WriteByte(X);
	auxiliarBuffer.WriteByte(Y);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "BlockPosition" message and returns it. */
/* ' */
/* ' @param    X X coord of the tile to block/unblock. */
/* ' @param    Y Y coord of the tile to block/unblock. */
/* ' @param    Blocked Blocked status of the tile */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageBlockPosition(int X, int Y, bool Blocked) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Fredy Horacio Treboux (liquid) */
	/* 'Last Modification: 01/08/07 */
	/* 'Prepares the "BlockPosition" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_BlockPosition);
	auxiliarBuffer.WriteByte(X);
	auxiliarBuffer.WriteByte(Y);
	auxiliarBuffer.WriteBoolean(Blocked);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());

	return retval;
}

/* '' */
/* ' Prepares the "ObjectCreate" message and returns it. */
/* ' */
/* ' @param    GrhIndex Grh of the object. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageObjectCreate(int GrhIndex, int X, int Y) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'prepares the "ObjectCreate" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_ObjectCreate);
	auxiliarBuffer.WriteByte(X);
	auxiliarBuffer.WriteByte(Y);
	auxiliarBuffer.WriteInteger(GrhIndex);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "CharacterRemove" message and returns it. */
/* ' */
/* ' @param    CharIndex Character to be removed. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageCharacterRemove(int CharIndex) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "CharacterRemove" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_CharacterRemove);
	auxiliarBuffer.WriteInteger(CharIndex);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "RemoveCharDialog" message and returns it. */
/* ' */
/* ' @param    CharIndex Character whose dialog will be removed. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageRemoveCharDialog(int CharIndex) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Writes the "RemoveCharDialog" message to the given user's outgoing data buffer */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_RemoveCharDialog);
	auxiliarBuffer.WriteInteger(CharIndex);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Writes the "CharacterCreate" message to the given user's outgoing data buffer. */
/* ' */
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
/* ' @param    NickColor Determines if the character is a criminal or not, and if can be atacked by someone */
/* ' @param    privileges Sets if the character is a normal one or any kind of administrative character. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageCharacterCreate(int body, int Head, eHeading heading, int CharIndex, int X, int Y,
		int weapon, int shield, int FX, int FXLoops, int helmet, std::string Name, int NickColor,
		int Privileges) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "CharacterCreate" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_CharacterCreate);

	auxiliarBuffer.WriteInteger(CharIndex);
	auxiliarBuffer.WriteInteger(body);
	auxiliarBuffer.WriteInteger(Head);
	auxiliarBuffer.WriteByte(heading);
	auxiliarBuffer.WriteByte(X);
	auxiliarBuffer.WriteByte(Y);
	auxiliarBuffer.WriteInteger(weapon);
	auxiliarBuffer.WriteInteger(shield);
	auxiliarBuffer.WriteInteger(helmet);
	auxiliarBuffer.WriteInteger(FX);
	auxiliarBuffer.WriteInteger(FXLoops);
	auxiliarBuffer.WriteUnicodeString(Name);
	auxiliarBuffer.WriteByte(NickColor);
	auxiliarBuffer.WriteByte(Privileges);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "CharacterChange" message and returns it. */
/* ' */
/* ' @param    body Body index of the new character. */
/* ' @param    head Head index of the new character. */
/* ' @param    heading Heading in which the new character is looking. */
/* ' @param    CharIndex The index of the new character. */
/* ' @param    weapon Weapon index of the new character. */
/* ' @param    shield Shield index of the new character. */
/* ' @param    FX FX index to be displayed over the new character. */
/* ' @param    FXLoops Number of times the FX should be rendered. */
/* ' @param    helmet Helmet index of the new character. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageCharacterChange(int body, int Head, eHeading heading, int CharIndex, int weapon,
		int shield, int FX, int FXLoops, int helmet) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "CharacterChange" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_CharacterChange);

	auxiliarBuffer.WriteInteger(CharIndex);
	auxiliarBuffer.WriteInteger(body);
	auxiliarBuffer.WriteInteger(Head);
	auxiliarBuffer.WriteByte(heading);
	auxiliarBuffer.WriteInteger(weapon);
	auxiliarBuffer.WriteInteger(shield);
	auxiliarBuffer.WriteInteger(helmet);
	auxiliarBuffer.WriteInteger(FX);
	auxiliarBuffer.WriteInteger(FXLoops);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "CharacterMove" message and returns it. */
/* ' */
/* ' @param    CharIndex Character which is moving. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageCharacterMove(int CharIndex, int X, int Y) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "CharacterMove" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_CharacterMove);
	auxiliarBuffer.WriteInteger(CharIndex);
	auxiliarBuffer.WriteByte(X);
	auxiliarBuffer.WriteByte(Y);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

std::string PrepareMessageForceCharMove(eHeading Direccion) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: ZaMa */
	/* 'Last Modification: 26/03/2009 */
	/* 'Prepares the "ForceCharMove" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_ForceCharMove);
	auxiliarBuffer.WriteByte(Direccion);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "UpdateTagAndStatus" message and returns it. */
/* ' */
/* ' @param    CharIndex Character which is moving. */
/* ' @param    X X coord of the character's new position. */
/* ' @param    Y Y coord of the character's new position. */
/* ' @return   The formated message ready to be writen as is on outgoing buffers. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageUpdateTagAndStatus(int UserIndex, int NickColor, std::string Tag) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Alejandro Salvo (Salvito) */
	/* 'Last Modification: 04/07/07 */
	/* 'Last Modified By: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Prepares the "UpdateTagAndStatus" message and returns it */
	/* '15/01/2010: ZaMa - Now sends the nick color instead of the status. */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_UpdateTagAndStatus);

	auxiliarBuffer.WriteInteger(UserList[UserIndex].Char.CharIndex);
	auxiliarBuffer.WriteByte(NickColor);
	auxiliarBuffer.WriteUnicodeString(Tag);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
}

/* '' */
/* ' Prepares the "ErrorMsg" message and returns it. */
/* ' */
/* ' @param    message The error message to be displayed. */
/* ' @remarks  The data is not actually sent until the buffer is properly flushed. */

std::string PrepareMessageErrorMsg(std::string message) {
	std::string retval;
	/* '*************************************************** */
	/* 'Author: Juan Martín Sotuyo Dodero (Maraxus) */
	/* 'Last Modification: 05/17/06 */
	/* 'Prepares the "ErrorMsg" message and returns it */
	/* '*************************************************** */
	clsByteQueue auxiliarBuffer;
	auxiliarBuffer.WriteByte(ServerPacketID_ErrorMsg);
	auxiliarBuffer.WriteUnicodeString(message);

	retval = auxiliarBuffer.ReadBinaryFixed(auxiliarBuffer.length());
	return retval;
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_StopWorking);

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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_CancelOfferItem);
	UserList[UserIndex].outgoingData->WriteByte(Slot);

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
	vb6::Date TempDate;

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_RecordDetails);

	/* 'Creador y motivo */
	UserList[UserIndex].outgoingData->WriteUnicodeString(Records[RecordIndex].Creador);
	UserList[UserIndex].outgoingData->WriteUnicodeString(Records[RecordIndex].Motivo);

	tIndex = NameIndex(Records[RecordIndex].Usuario);

	/* 'Status del pj (online?) */
	UserList[UserIndex].outgoingData->WriteBoolean(tIndex > 0);

	/* 'Escribo la IP según el estado del personaje */
	if (tIndex > 0) {
		/* 'La IP Actual */
		tmpStr = UserList[tIndex].ip;
		/* 'String nulo */
	} else {
		tmpStr = "";
	}
	UserList[UserIndex].outgoingData->WriteUnicodeString(tmpStr);

	/* 'Escribo tiempo online según el estado del personaje */
	if (tIndex > 0) {
		/* 'Tiempo logueado. */
		TempDate = vb6::Now() - UserList[tIndex].LogOnTime;
		//tmpStr = vb6::Hour(TempDate) + ":" + vb6::Minute(TempDate) + ":" + vb6::Second(TempDate);
		tmpStr = vb6::CStr(TempDate);
	} else {
		/* 'Envío string nulo. */
		tmpStr = "";
	}
	UserList[UserIndex].outgoingData->WriteUnicodeString(tmpStr);

	/* 'Escribo observaciones: */
	tmpStr = "";
	if (Records[RecordIndex].NumObs) {
		for (i = (1); i <= (Records[RecordIndex].NumObs); i++) {
			tmpStr = tmpStr + Records[RecordIndex].Obs[i].Creador + "> "
					+ Records[RecordIndex].Obs[i].Detalles + vbCrLf;
		}

		tmpStr = vb6::Left(tmpStr, vb6::Len(tmpStr) - 1);
	}
	UserList[UserIndex].outgoingData->WriteUnicodeString(tmpStr);
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

	UserList[UserIndex].outgoingData->WriteByte(ServerPacketID_RecordList);

	UserList[UserIndex].outgoingData->WriteByte(NumRecords);
	for (i = (1); i <= (NumRecords); i++) {
		UserList[UserIndex].outgoingData->WriteUnicodeString(Records[i].Usuario);
	}
}

