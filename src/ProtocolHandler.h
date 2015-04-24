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


#ifndef PROTOCOLHANDLER_H_
#define PROTOCOLHANDLER_H_

void HandleIncomingData(int UserIndex);

void HandleIncomingDataOnePacket(int UserIndex);

void HandleGMCommands(int UserIndex);

/* '' */
/* ' Handles the "Home" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */
void HandleHome(int UserIndex);

/* '' */
/* ' Handles the "LoginExistingChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleLoginExistingChar(int UserIndex);
/* # IF SeguridadAlkon THEN */
/* # ELSE */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # ELSE */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* '' */
/* ' Handles the "ThrowDices" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleThrowDices(int UserIndex);

/* '' */
/* ' Handles the "LoginNewChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleLoginNewChar(int UserIndex);
/* # IF SeguridadAlkon THEN */
/* # ELSE */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # ELSE */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* '' */
/* ' Handles the "Talk" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleTalk(int UserIndex);

/* '' */
/* ' Handles the "Yell" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleYell(int UserIndex);

/* '' */
/* ' Handles the "Whisper" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWhisper(int UserIndex);

/* '' */
/* ' Handles the "Walk" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWalk(int UserIndex);

/* '' */
/* ' Handles the "RequestPositionUpdate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestPositionUpdate(int UserIndex);

/* '' */
/* ' Handles the "Attack" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleAttack(int UserIndex);

/* '' */
/* ' Handles the "PickUp" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePickUp(int UserIndex);

/* '' */
/* ' Handles the "SafeToggle" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSafeToggle(int UserIndex);

/* '' */
/* ' Handles the "ResuscitationSafeToggle" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleResuscitationToggle(int UserIndex);

/* '' */
/* ' Handles the "RequestGuildLeaderInfo" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestGuildLeaderInfo(int UserIndex);

/* '' */
/* ' Handles the "RequestAtributes" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestAtributes(int UserIndex);

/* '' */
/* ' Handles the "RequestFame" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestFame(int UserIndex);

/* '' */
/* ' Handles the "RequestSkills" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestSkills(int UserIndex);

/* '' */
/* ' Handles the "RequestMiniStats" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestMiniStats(int UserIndex);

/* '' */
/* ' Handles the "CommerceEnd" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCommerceEnd(int UserIndex);

/* '' */
/* ' Handles the "UserCommerceEnd" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUserCommerceEnd(int UserIndex);

/* '' */
/* ' Handles the "UserCommerceConfirm" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */
void HandleUserCommerceConfirm(int UserIndex);

void HandleCommerceChat(int UserIndex);

/* '' */
/* ' Handles the "BankEnd" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBankEnd(int UserIndex);

/* '' */
/* ' Handles the "UserCommerceOk" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUserCommerceOk(int UserIndex);

/* '' */
/* ' Handles the "UserCommerceReject" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUserCommerceReject(int UserIndex);

/* '' */
/* ' Handles the "Drop" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleDrop(int UserIndex);

/* '' */
/* ' Handles the "CastSpell" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCastSpell(int UserIndex);

/* '' */
/* ' Handles the "LeftClick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleLeftClick(int UserIndex);

/* '' */
/* ' Handles the "DoubleClick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleDoubleClick(int UserIndex);

/* '' */
/* ' Handles the "Work" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWork(int UserIndex);

/* '' */
/* ' Handles the "InitCrafting" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleInitCrafting(int UserIndex);

/* '' */
/* ' Handles the "UseSpellMacro" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUseSpellMacro(int UserIndex);

/* '' */
/* ' Handles the "UseItem" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUseItem(int UserIndex);

/* # IF SeguridadAlkon THEN */
/* # END IF */

/* '' */
/* ' Handles the "CraftBlacksmith" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCraftBlacksmith(int UserIndex);

/* '' */
/* ' Handles the "CraftCarpenter" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCraftCarpenter(int UserIndex);

/* '' */
/* ' Handles the "WorkLeftClick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWorkLeftClick(int UserIndex);

/* '' */
/* ' Handles the "CreateNewGuild" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCreateNewGuild(int UserIndex);

/* '' */
/* ' Handles the "SpellInfo" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSpellInfo(int UserIndex);

/* '' */
/* ' Handles the "EquipItem" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleEquipItem(int UserIndex);

/* '' */
/* ' Handles the "ChangeHeading" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleChangeHeading(int UserIndex);

/* '' */
/* ' Handles the "ModifySkills" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleModifySkills(int UserIndex);

/* '' */
/* ' Handles the "Train" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleTrain(int UserIndex);

/* '' */
/* ' Handles the "CommerceBuy" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCommerceBuy(int UserIndex);

/* '' */
/* ' Handles the "BankExtractItem" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBankExtractItem(int UserIndex);

/* '' */
/* ' Handles the "CommerceSell" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCommerceSell(int UserIndex);

/* '' */
/* ' Handles the "BankDeposit" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBankDeposit(int UserIndex);

/* '' */
/* ' Handles the "ForumPost" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleForumPost(int UserIndex);

/* '' */
/* ' Handles the "MoveSpell" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleMoveSpell(int UserIndex);

/* '' */
/* ' Handles the "MoveBank" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleMoveBank(int UserIndex);

/* '' */
/* ' Handles the "ClanCodexUpdate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleClanCodexUpdate(int UserIndex);

/* '' */
/* ' Handles the "UserCommerceOffer" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUserCommerceOffer(int UserIndex);

/* '' */
/* ' Handles the "GuildAcceptPeace" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildAcceptPeace(int UserIndex);

/* '' */
/* ' Handles the "GuildRejectAlliance" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildRejectAlliance(int UserIndex);

/* '' */
/* ' Handles the "GuildRejectPeace" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildRejectPeace(int UserIndex);

/* '' */
/* ' Handles the "GuildAcceptAlliance" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildAcceptAlliance(int UserIndex);

/* '' */
/* ' Handles the "GuildOfferPeace" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildOfferPeace(int UserIndex);

/* '' */
/* ' Handles the "GuildOfferAlliance" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildOfferAlliance(int UserIndex);

/* '' */
/* ' Handles the "GuildAllianceDetails" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildAllianceDetails(int UserIndex);

/* '' */
/* ' Handles the "GuildPeaceDetails" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildPeaceDetails(int UserIndex);

/* '' */
/* ' Handles the "GuildRequestJoinerInfo" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildRequestJoinerInfo(int UserIndex);

/* '' */
/* ' Handles the "GuildAlliancePropList" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildAlliancePropList(int UserIndex);

/* '' */
/* ' Handles the "GuildPeacePropList" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildPeacePropList(int UserIndex);

/* '' */
/* ' Handles the "GuildDeclareWar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildDeclareWar(int UserIndex);

/* '' */
/* ' Handles the "GuildNewWebsite" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildNewWebsite(int UserIndex);

/* '' */
/* ' Handles the "GuildAcceptNewMember" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildAcceptNewMember(int UserIndex);

/* '' */
/* ' Handles the "GuildRejectNewMember" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildRejectNewMember(int UserIndex);

/* '' */
/* ' Handles the "GuildKickMember" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildKickMember(int UserIndex);

/* '' */
/* ' Handles the "GuildUpdateNews" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildUpdateNews(int UserIndex);

/* '' */
/* ' Handles the "GuildMemberInfo" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildMemberInfo(int UserIndex);

/* '' */
/* ' Handles the "GuildOpenElections" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildOpenElections(int UserIndex);

/* '' */
/* ' Handles the "GuildRequestMembership" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildRequestMembership(int UserIndex);

/* '' */
/* ' Handles the "GuildRequestDetails" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildRequestDetails(int UserIndex);

/* '' */
/* ' Handles the "Online" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleOnline(int UserIndex);

/* '' */
/* ' Handles the "Quit" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleQuit(int UserIndex);

/* '' */
/* ' Handles the "GuildLeave" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildLeave(int UserIndex);

/* '' */
/* ' Handles the "RequestAccountState" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestAccountState(int UserIndex);

/* '' */
/* ' Handles the "PetStand" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePetStand(int UserIndex);

/* '' */
/* ' Handles the "PetFollow" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePetFollow(int UserIndex);

/* '' */
/* ' Handles the "ReleasePet" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleReleasePet(int UserIndex);

/* '' */
/* ' Handles the "TrainList" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleTrainList(int UserIndex);

/* '' */
/* ' Handles the "Rest" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRest(int UserIndex);

/* '' */
/* ' Handles the "Meditate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleMeditate(int UserIndex);

/* '' */
/* ' Handles the "Resucitate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleResucitate(int UserIndex);

/* '' */
/* ' Handles the "Consultation" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleConsultation(int UserIndex);

/* '' */
/* ' Handles the "Heal" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleHeal(int UserIndex);

/* '' */
/* ' Handles the "RequestStats" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestStats(int UserIndex);

/* '' */
/* ' Handles the "Help" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleHelp(int UserIndex);

/* '' */
/* ' Handles the "CommerceStart" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCommerceStart(int UserIndex);

/* '' */
/* ' Handles the "BankStart" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBankStart(int UserIndex);

/* '' */
/* ' Handles the "Enlist" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleEnlist(int UserIndex);

/* '' */
/* ' Handles the "Information" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleInformation(int UserIndex);

/* '' */
/* ' Handles the "Reward" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleReward(int UserIndex);

/* '' */
/* ' Handles the "RequestMOTD" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestMOTD(int UserIndex);

/* '' */
/* ' Handles the "UpTime" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUpTime(int UserIndex);

/* '' */
/* ' Handles the "PartyLeave" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartyLeave(int UserIndex);

/* '' */
/* ' Handles the "PartyCreate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartyCreate(int UserIndex);

/* '' */
/* ' Handles the "PartyJoin" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartyJoin(int UserIndex);

/* '' */
/* ' Handles the "ShareNpc" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleShareNpc(int UserIndex);

/* '' */
/* ' Handles the "StopSharingNpc" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleStopSharingNpc(int UserIndex);

/* '' */
/* ' Handles the "Inquiry" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleInquiry(int UserIndex);

/* '' */
/* ' Handles the "GuildMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildMessage(int UserIndex);

/* '' */
/* ' Handles the "PartyMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartyMessage(int UserIndex);

/* '' */
/* ' Handles the "CentinelReport" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCentinelReport(int UserIndex);

/* '' */
/* ' Handles the "GuildOnline" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildOnline(int UserIndex);

/* '' */
/* ' Handles the "PartyOnline" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartyOnline(int UserIndex);

/* '' */
/* ' Handles the "CouncilMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCouncilMessage(int UserIndex);

/* '' */
/* ' Handles the "RoleMasterRequest" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRoleMasterRequest(int UserIndex);

/* '' */
/* ' Handles the "GMRequest" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGMRequest(int UserIndex);

/* '' */
/* ' Handles the "BugReport" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBugReport(int UserIndex);

/* '' */
/* ' Handles the "ChangeDescription" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleChangeDescription(int UserIndex);

/* '' */
/* ' Handles the "GuildVote" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildVote(int UserIndex);

/* '' */
/* ' Handles the "ShowGuildNews" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleShowGuildNews(int UserIndex);

/* '' */
/* ' Handles the "Punishments" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePunishments(int UserIndex);

/* '' */
/* ' Handles the "ChangePassword" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleChangePassword(int UserIndex);
/* # IF SeguridadAlkon THEN */
/* # ELSE */
/* # END IF */

/* # IF SeguridadAlkon THEN */
/* # ELSE */
/* # END IF */

/* '' */
/* ' Handles the "Gamble" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGamble(int UserIndex);

/* '' */
/* ' Handles the "InquiryVote" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleInquiryVote(int UserIndex);

/* '' */
/* ' Handles the "BankExtractGold" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBankExtractGold(int UserIndex);

/* '' */
/* ' Handles the "LeaveFaction" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleLeaveFaction(int UserIndex);

/* '' */
/* ' Handles the "BankDepositGold" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBankDepositGold(int UserIndex);

/* '' */
/* ' Handles the "Denounce" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleDenounce(int UserIndex);

/* '' */
/* ' Handles the "GuildFundate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildFundate(int UserIndex);

/* '' */
/* ' Handles the "GuildFundation" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildFundation(int UserIndex);

/* '' */
/* ' Handles the "PartyKick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartyKick(int UserIndex);

/* '' */
/* ' Handles the "PartySetLeader" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartySetLeader(int UserIndex);

/* '' */
/* ' Handles the "PartyAcceptMember" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartyAcceptMember(int UserIndex);

/* '' */
/* ' Handles the "GuildMemberList" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildMemberList(int UserIndex);

/* '' */
/* ' Handles the "GMMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGMMessage(int UserIndex);

/* '' */
/* ' Handles the "ShowName" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleShowName(int UserIndex);

/* '' */
/* ' Handles the "OnlineRoyalArmy" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleOnlineRoyalArmy(int UserIndex);

/* '' */
/* ' Handles the "OnlineChaosLegion" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleOnlineChaosLegion(int UserIndex);

/* '' */
/* ' Handles the "GoNearby" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGoNearby(int UserIndex);

/* '' */
/* ' Handles the "Comment" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleComment(int UserIndex);

/* '' */
/* ' Handles the "ServerTime" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleServerTime(int UserIndex);

/* '' */
/* ' Handles the "Where" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWhere(int UserIndex);

/* '' */
/* ' Handles the "CreaturesInMap" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCreaturesInMap(int UserIndex);

/* '' */
/* ' Handles the "WarpMeToTarget" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWarpMeToTarget(int UserIndex);

/* '' */
/* ' Handles the "WarpChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWarpChar(int UserIndex);

/* '' */
/* ' Handles the "Silence" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSilence(int UserIndex);

/* '' */
/* ' Handles the "SOSShowList" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSOSShowList(int UserIndex);

/* '' */
/* ' Handles the "RequestPartyForm" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandlePartyForm(int UserIndex);

/* '' */
/* ' Handles the "ItemUpgrade" message. */
/* ' */
/* ' @param    UserIndex The index of the user sending the message. */

void HandleItemUpgrade(int UserIndex);

/* '' */
/* ' Handles the "SOSRemove" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSOSRemove(int UserIndex);

/* '' */
/* ' Handles the "GoToChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGoToChar(int UserIndex);

/* '' */
/* ' Handles the "Invisible" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleInvisible(int UserIndex);

/* '' */
/* ' Handles the "GMPanel" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGMPanel(int UserIndex);

/* '' */
/* ' Handles the "GMPanel" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestUserList(int UserIndex);

/* '' */
/* ' Handles the "Working" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWorking(int UserIndex);

/* '' */
/* ' Handles the "Hiding" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleHiding(int UserIndex);

/* '' */
/* ' Handles the "Jail" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleJail(int UserIndex);

/* '' */
/* ' Handles the "KillNPC" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleKillNPC(int UserIndex);

/* '' */
/* ' Handles the "WarnUser" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleWarnUser(int UserIndex);

/* '' */
/* ' Handles the "EditChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleEditChar(int UserIndex);

/* '' */
/* ' Handles the "RequestCharInfo" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestCharInfo(int UserIndex);

/* '' */
/* ' Handles the "RequestCharStats" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestCharStats(int UserIndex);

/* '' */
/* ' Handles the "RequestCharGold" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestCharGold(int UserIndex);

/* '' */
/* ' Handles the "RequestCharInventory" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestCharInventory(int UserIndex);

/* '' */
/* ' Handles the "RequestCharBank" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestCharBank(int UserIndex);

/* '' */
/* ' Handles the "RequestCharSkills" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRequestCharSkills(int UserIndex);

/* '' */
/* ' Handles the "ReviveChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleReviveChar(int UserIndex);

/* '' */
/* ' Handles the "OnlineGM" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleOnlineGM(int UserIndex);

/* '' */
/* ' Handles the "OnlineMap" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleOnlineMap(int UserIndex);

/* '' */
/* ' Handles the "Forgive" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleForgive(int UserIndex);

/* '' */
/* ' Handles the "Kick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleKick(int UserIndex);

/* '' */
/* ' Handles the "Execute" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleExecute(int UserIndex);

/* '' */
/* ' Handles the "BanChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBanChar(int UserIndex);

/* '' */
/* ' Handles the "UnbanChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUnbanChar(int UserIndex);

/* '' */
/* ' Handles the "NPCFollow" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleNPCFollow(int UserIndex);

/* '' */
/* ' Handles the "SummonChar" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSummonChar(int UserIndex);

/* '' */
/* ' Handles the "SpawnListRequest" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSpawnListRequest(int UserIndex);

/* '' */
/* ' Handles the "SpawnCreature" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSpawnCreature(int UserIndex);

/* '' */
/* ' Handles the "ResetNPCInventory" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleResetNPCInventory(int UserIndex);

/* '' */
/* ' Handles the "CleanWorld" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCleanWorld(int UserIndex);

/* '' */
/* ' Handles the "ServerMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleServerMessage(int UserIndex);

/* '' */
/* ' Handles the "MapMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleMapMessage(int UserIndex);

/* '' */
/* ' Handles the "NickToIP" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleNickToIP(int UserIndex);

/* '' */
/* ' Handles the "IPToNick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleIPToNick(int UserIndex);

/* '' */
/* ' Handles the "GuildOnlineMembers" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildOnlineMembers(int UserIndex);

/* '' */
/* ' Handles the "TeleportCreate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleTeleportCreate(int UserIndex);

/* '' */
/* ' Handles the "TeleportDestroy" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleTeleportDestroy(int UserIndex);

/* '' */
/* ' Handles the "RainToggle" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRainToggle(int UserIndex);

/* '' */
/* ' Handles the "EnableDenounces" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleEnableDenounces(int UserIndex);

/* '' */
/* ' Handles the "ShowDenouncesList" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleShowDenouncesList(int UserIndex);

/* '' */
/* ' Handles the "SetCharDescription" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSetCharDescription(int UserIndex);

/* '' */
/* ' Handles the "ForceMIDIToMap" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HanldeForceMIDIToMap(int UserIndex);

/* '' */
/* ' Handles the "ForceWAVEToMap" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleForceWAVEToMap(int UserIndex);

/* '' */
/* ' Handles the "RoyalArmyMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRoyalArmyMessage(int UserIndex);

/* '' */
/* ' Handles the "ChaosLegionMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleChaosLegionMessage(int UserIndex);

/* '' */
/* ' Handles the "CitizenMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCitizenMessage(int UserIndex);

/* '' */
/* ' Handles the "CriminalMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCriminalMessage(int UserIndex);

/* '' */
/* ' Handles the "TalkAsNPC" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleTalkAsNPC(int UserIndex);

/* '' */
/* ' Handles the "DestroyAllItemsInArea" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleDestroyAllItemsInArea(int UserIndex);

/* '' */
/* ' Handles the "AcceptRoyalCouncilMember" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleAcceptRoyalCouncilMember(int UserIndex);

/* '' */
/* ' Handles the "ChaosCouncilMember" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleAcceptChaosCouncilMember(int UserIndex);

/* '' */
/* ' Handles the "ItemsInTheFloor" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleItemsInTheFloor(int UserIndex);

/* '' */
/* ' Handles the "MakeDumb" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleMakeDumb(int UserIndex);

/* '' */
/* ' Handles the "MakeDumbNoMore" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleMakeDumbNoMore(int UserIndex);

/* '' */
/* ' Handles the "DumpIPTables" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleDumpIPTables(int UserIndex);

/* '' */
/* ' Handles the "CouncilKick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCouncilKick(int UserIndex);

/* '' */
/* ' Handles the "SetTrigger" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleSetTrigger(int UserIndex);

/* '' */
/* ' Handles the "AskTrigger" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleAskTrigger(int UserIndex);

/* '' */
/* ' Handles the "BannedIPList" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBannedIPList(int UserIndex);

/* '' */
/* ' Handles the "BannedIPReload" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBannedIPReload(int UserIndex);

/* '' */
/* ' Handles the "GuildBan" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleGuildBan(int UserIndex);

/* '' */
/* ' Handles the "BanIP" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleBanIP(int UserIndex);

/* '' */
/* ' Handles the "UnbanIP" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleUnbanIP(int UserIndex);

/* '' */
/* ' Handles the "CreateItem" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCreateItem(int UserIndex);

/* '' */
/* ' Handles the "DestroyItems" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleDestroyItems(int UserIndex);

/* '' */
/* ' Handles the "ChaosLegionKick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleChaosLegionKick(int UserIndex);

/* '' */
/* ' Handles the "RoyalArmyKick" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRoyalArmyKick(int UserIndex);

/* '' */
/* ' Handles the "ForceMIDIAll" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleForceMIDIAll(int UserIndex);

/* '' */
/* ' Handles the "ForceWAVEAll" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleForceWAVEAll(int UserIndex);

/* '' */
/* ' Handles the "RemovePunishment" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRemovePunishment(int UserIndex);

/* '' */
/* ' Handles the "TileBlockedToggle" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleTileBlockedToggle(int UserIndex);

/* '' */
/* ' Handles the "KillNPCNoRespawn" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleKillNPCNoRespawn(int UserIndex);

/* '' */
/* ' Handles the "KillAllNearbyNPCs" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleKillAllNearbyNPCs(int UserIndex);

/* '' */
/* ' Handles the "LastIP" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleLastIP(int UserIndex);

/* '' */
/* ' Handles the "ChatColor" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleChatColor(int UserIndex);

/* '' */
/* ' Handles the "Ignored" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleIgnored(int UserIndex);

/* '' */
/* ' Handles the "CheckSlot" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleCheckSlot(int UserIndex);

/* '' */
/* ' Handles the "ResetAutoUpdate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleResetAutoUpdate(int UserIndex);

/* '' */
/* ' Handles the "Restart" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleRestart(int UserIndex);

/* '' */
/* ' Handles the "ReloadObjects" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleReloadObjects(int UserIndex);

/* '' */
/* ' Handles the "ReloadSpells" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleReloadSpells(int UserIndex);

/* '' */
/* ' Handle the "ReloadServerIni" message. */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleReloadServerIni(int UserIndex);

/* '' */
/* ' Handle the "ReloadNPCs" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleReloadNPCs(int UserIndex);

/* '' */
/* ' Handle the "KickAllChars" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleKickAllChars(int UserIndex);

/* '' */
/* ' Handle the "Night" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleNight(int UserIndex);

/* '' */
/* ' Handle the "ShowServerForm" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleShowServerForm(int UserIndex);

/* '' */
/* ' Handle the "CleanSOS" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleCleanSOS(int UserIndex);

/* '' */
/* ' Handle the "SaveChars" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleSaveChars(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoBackup" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoBackup(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoPK" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoPK(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoRestricted" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoRestricted(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoNoMagic" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoNoMagic(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoNoInvi" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoNoInvi(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoNoResu" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoNoResu(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoLand" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoLand(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoZone" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoZone(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoStealNp" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoStealNpc(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoNoOcultar" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoNoOcultar(int UserIndex);

/* '' */
/* ' Handle the "ChangeMapInfoNoInvocar" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMapInfoNoInvocar(int UserIndex);

/* '' */
/* ' Handle the "SaveMap" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleSaveMap(int UserIndex);

/* '' */
/* ' Handle the "ShowGuildMessages" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleShowGuildMessages(int UserIndex);

/* '' */
/* ' Handle the "DoBackUp" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleDoBackUp(int UserIndex);

/* '' */
/* ' Handle the "ToggleCentinelActivated" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleToggleCentinelActivated(int UserIndex);

/* '' */
/* ' Handle the "AlterName" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleAlterName(int UserIndex);

/* '' */
/* ' Handle the "AlterName" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleAlterMail(int UserIndex);

/* '' */
/* ' Handle the "AlterPassword" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleAlterPassword(int UserIndex);

/* '' */
/* ' Handle the "HandleCreateNPC" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleCreateNPC(int UserIndex);

/* '' */
/* ' Handle the "CreateNPCWithRespawn" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleCreateNPCWithRespawn(int UserIndex);

/* '' */
/* ' Handle the "ImperialArmour" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleImperialArmour(int UserIndex);

/* '' */
/* ' Handle the "ChaosArmour" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChaosArmour(int UserIndex);

/* '' */
/* ' Handle the "NavigateToggle" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleNavigateToggle(int UserIndex);

/* '' */
/* ' Handle the "ServerOpenToUsersToggle" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleServerOpenToUsersToggle(int UserIndex);

/* '' */
/* ' Handle the "TurnOffServer" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleTurnOffServer(int UserIndex);

/* '' */
/* ' Handle the "TurnCriminal" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleTurnCriminal(int UserIndex);

/* '' */
/* ' Handle the "ResetFactions" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleResetFactions(int UserIndex);

/* '' */
/* ' Handle the "RemoveCharFromGuild" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleRemoveCharFromGuild(int UserIndex);

/* '' */
/* ' Handle the "RequestCharMail" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleRequestCharMail(int UserIndex);

/* '' */
/* ' Handle the "SystemMessage" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleSystemMessage(int UserIndex);

/* '' */
/* ' Handle the "SetMOTD" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleSetMOTD(int UserIndex);

/* '' */
/* ' Handle the "ChangeMOTD" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleChangeMOTD(int UserIndex);

/* '' */
/* ' Handle the "Ping" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandlePing(int UserIndex);

/* '' */
/* ' Handle the "SetIniVar" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleSetIniVar(int UserIndex);

/* '' */
/* ' Handle the "CreatePretorianClan" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleCreatePretorianClan(int UserIndex);

/* '' */
/* ' Handle the "CreatePretorianClan" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleDeletePretorianClan(int UserIndex);

/* '' */
/* ' Handles the "SetDialog" message. */
/* ' */
/* ' @param UserIndex The index of the user sending the message */

void HandleSetDialog(int UserIndex);

/* '' */
/* ' Handles the "Impersonate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleImpersonate(int UserIndex);

/* '' */
/* ' Handles the "Imitate" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleImitate(int UserIndex);

/* '' */
/* ' Handles the "RecordAdd" message. */
/* ' */
/* ' @param UserIndex The index of the user sending the message */

void HandleRecordAdd(int UserIndex);

/* '' */
/* ' Handles the "RecordAddObs" message. */
/* ' */
/* ' @param UserIndex The index of the user sending the message. */

void HandleRecordAddObs(int UserIndex);

/* '' */
/* ' Handles the "RecordRemove" message. */
/* ' */
/* ' @param UserIndex The index of the user sending the message. */

void HandleRecordRemove(int UserIndex);

/* '' */
/* ' Handles the "RecordListRequest" message. */
/* ' */
/* ' @param UserIndex The index of the user sending the message. */

void HandleRecordListRequest(int UserIndex);

/* '' */
/* ' Handles the "RecordDetailsRequest" message. */
/* ' */
/* ' @param UserIndex The index of the user sending the message. */

void HandleRecordDetailsRequest(int UserIndex);

void HandleMoveItem(int UserIndex);

/* '' */
/* ' Handles the "HigherAdminsMessage" message. */
/* ' */
/* ' @param    userIndex The index of the user sending the message. */

void HandleHigherAdminsMessage(int UserIndex);

/* '' */
/* ' Handle the "AlterName" message */
/* ' */
/* ' @param userIndex The index of the user sending the message */

void HandleAlterGuildName(int UserIndex);

#endif /* PROTOCOLHANDLER_H_ */
