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

#include "ProtocolNew.h"


void HandleIncomingData(int UserIndex);

void HandleIncomingDataOnePacket(int UserIndex);

class DakaraClientPacketHandler : public dakara::protocol::client::ClientPacketHandler, public dakara::protocol::clientgm::ClientGMPacketHandler {
public:
	DakaraClientPacketHandler(int UserIndex_) : UserIndex(UserIndex_) {}

    virtual ~DakaraClientPacketHandler() {}

    virtual void handleLoginExistingChar(dakara::protocol::client::LoginExistingChar* p);
    virtual void handleThrowDices(dakara::protocol::client::ThrowDices* p);
    virtual void handleLoginNewChar(dakara::protocol::client::LoginNewChar* p);
    virtual void handleTalk(dakara::protocol::client::Talk* p);
    virtual void handleYell(dakara::protocol::client::Yell* p);
    virtual void handleWhisper(dakara::protocol::client::Whisper* p);
    virtual void handleWalk(dakara::protocol::client::Walk* p);
    virtual void handleRequestPositionUpdate(dakara::protocol::client::RequestPositionUpdate* p);
    virtual void handleAttack(dakara::protocol::client::Attack* p);
    virtual void handlePickUp(dakara::protocol::client::PickUp* p);
    virtual void handleSafeToggle(dakara::protocol::client::SafeToggle* p);
    virtual void handleResuscitationSafeToggle(dakara::protocol::client::ResuscitationSafeToggle* p);
    virtual void handleRequestGuildLeaderInfo(dakara::protocol::client::RequestGuildLeaderInfo* p);
    virtual void handleRequestAtributes(dakara::protocol::client::RequestAtributes* p);
    virtual void handleRequestFame(dakara::protocol::client::RequestFame* p);
    virtual void handleRequestSkills(dakara::protocol::client::RequestSkills* p);
    virtual void handleRequestMiniStats(dakara::protocol::client::RequestMiniStats* p);
    virtual void handleCommerceEnd(dakara::protocol::client::CommerceEnd* p);
    virtual void handleUserCommerceEnd(dakara::protocol::client::UserCommerceEnd* p);
    virtual void handleUserCommerceConfirm(dakara::protocol::client::UserCommerceConfirm* p);
    virtual void handleCommerceChat(dakara::protocol::client::CommerceChat* p);
    virtual void handleBankEnd(dakara::protocol::client::BankEnd* p);
    virtual void handleUserCommerceOk(dakara::protocol::client::UserCommerceOk* p);
    virtual void handleUserCommerceReject(dakara::protocol::client::UserCommerceReject* p);
    virtual void handleDrop(dakara::protocol::client::Drop* p);
    virtual void handleCastSpell(dakara::protocol::client::CastSpell* p);
    virtual void handleLeftClick(dakara::protocol::client::LeftClick* p);
    virtual void handleDoubleClick(dakara::protocol::client::DoubleClick* p);
    virtual void handleWork(dakara::protocol::client::Work* p);
    virtual void handleUseSpellMacro(dakara::protocol::client::UseSpellMacro* p);
    virtual void handleUseItem(dakara::protocol::client::UseItem* p);
    virtual void handleCraftBlacksmith(dakara::protocol::client::CraftBlacksmith* p);
    virtual void handleCraftCarpenter(dakara::protocol::client::CraftCarpenter* p);
    virtual void handleWorkLeftClick(dakara::protocol::client::WorkLeftClick* p);
    virtual void handleCreateNewGuild(dakara::protocol::client::CreateNewGuild* p);
    virtual void handleSpellInfo(dakara::protocol::client::SpellInfo* p);
    virtual void handleEquipItem(dakara::protocol::client::EquipItem* p);
    virtual void handleChangeHeading(dakara::protocol::client::ChangeHeading* p);
    virtual void handleModifySkills(dakara::protocol::client::ModifySkills* p);
    virtual void handleTrain(dakara::protocol::client::Train* p);
    virtual void handleCommerceBuy(dakara::protocol::client::CommerceBuy* p);
    virtual void handleBankExtractItem(dakara::protocol::client::BankExtractItem* p);
    virtual void handleCommerceSell(dakara::protocol::client::CommerceSell* p);
    virtual void handleBankDeposit(dakara::protocol::client::BankDeposit* p);
    virtual void handleForumPost(dakara::protocol::client::ForumPost* p);
    virtual void handleMoveSpell(dakara::protocol::client::MoveSpell* p);
    virtual void handleMoveBank(dakara::protocol::client::MoveBank* p);
    virtual void handleClanCodexUpdate(dakara::protocol::client::ClanCodexUpdate* p);
    virtual void handleUserCommerceOffer(dakara::protocol::client::UserCommerceOffer* p);
    virtual void handleGuildAcceptPeace(dakara::protocol::client::GuildAcceptPeace* p);
    virtual void handleGuildRejectAlliance(dakara::protocol::client::GuildRejectAlliance* p);
    virtual void handleGuildRejectPeace(dakara::protocol::client::GuildRejectPeace* p);
    virtual void handleGuildAcceptAlliance(dakara::protocol::client::GuildAcceptAlliance* p);
    virtual void handleGuildOfferPeace(dakara::protocol::client::GuildOfferPeace* p);
    virtual void handleGuildOfferAlliance(dakara::protocol::client::GuildOfferAlliance* p);
    virtual void handleGuildAllianceDetails(dakara::protocol::client::GuildAllianceDetails* p);
    virtual void handleGuildPeaceDetails(dakara::protocol::client::GuildPeaceDetails* p);
    virtual void handleGuildRequestJoinerInfo(dakara::protocol::client::GuildRequestJoinerInfo* p);
    virtual void handleGuildAlliancePropList(dakara::protocol::client::GuildAlliancePropList* p);
    virtual void handleGuildPeacePropList(dakara::protocol::client::GuildPeacePropList* p);
    virtual void handleGuildDeclareWar(dakara::protocol::client::GuildDeclareWar* p);
    virtual void handleGuildNewWebsite(dakara::protocol::client::GuildNewWebsite* p);
    virtual void handleGuildAcceptNewMember(dakara::protocol::client::GuildAcceptNewMember* p);
    virtual void handleGuildRejectNewMember(dakara::protocol::client::GuildRejectNewMember* p);
    virtual void handleGuildKickMember(dakara::protocol::client::GuildKickMember* p);
    virtual void handleGuildUpdateNews(dakara::protocol::client::GuildUpdateNews* p);
    virtual void handleGuildMemberInfo(dakara::protocol::client::GuildMemberInfo* p);
    virtual void handleGuildOpenElections(dakara::protocol::client::GuildOpenElections* p);
    virtual void handleGuildRequestMembership(dakara::protocol::client::GuildRequestMembership* p);
    virtual void handleGuildRequestDetails(dakara::protocol::client::GuildRequestDetails* p);
    virtual void handleOnline(dakara::protocol::client::Online* p);
    virtual void handleQuit(dakara::protocol::client::Quit* p);
    virtual void handleGuildLeave(dakara::protocol::client::GuildLeave* p);
    virtual void handleRequestAccountState(dakara::protocol::client::RequestAccountState* p);
    virtual void handlePetStand(dakara::protocol::client::PetStand* p);
    virtual void handlePetFollow(dakara::protocol::client::PetFollow* p);
    virtual void handleReleasePet(dakara::protocol::client::ReleasePet* p);
    virtual void handleTrainList(dakara::protocol::client::TrainList* p);
    virtual void handleRest(dakara::protocol::client::Rest* p);
    virtual void handleMeditate(dakara::protocol::client::Meditate* p);
    virtual void handleResucitate(dakara::protocol::client::Resucitate* p);
    virtual void handleHeal(dakara::protocol::client::Heal* p);
    virtual void handleHelp(dakara::protocol::client::Help* p);
    virtual void handleRequestStats(dakara::protocol::client::RequestStats* p);
    virtual void handleCommerceStart(dakara::protocol::client::CommerceStart* p);
    virtual void handleBankStart(dakara::protocol::client::BankStart* p);
    virtual void handleEnlist(dakara::protocol::client::Enlist* p);
    virtual void handleInformation(dakara::protocol::client::Information* p);
    virtual void handleReward(dakara::protocol::client::Reward* p);
    virtual void handleRequestMOTD(dakara::protocol::client::RequestMOTD* p);
    virtual void handleUpTime(dakara::protocol::client::UpTime* p);
    virtual void handlePartyLeave(dakara::protocol::client::PartyLeave* p);
    virtual void handlePartyCreate(dakara::protocol::client::PartyCreate* p);
    virtual void handlePartyJoin(dakara::protocol::client::PartyJoin* p);
    virtual void handleInquiry(dakara::protocol::client::Inquiry* p);
    virtual void handleGuildMessage(dakara::protocol::client::GuildMessage* p);
    virtual void handlePartyMessage(dakara::protocol::client::PartyMessage* p);
    virtual void handleCentinelReport(dakara::protocol::client::CentinelReport* p);
    virtual void handleGuildOnline(dakara::protocol::client::GuildOnline* p);
    virtual void handlePartyOnline(dakara::protocol::client::PartyOnline* p);
    virtual void handleCouncilMessage(dakara::protocol::client::CouncilMessage* p);
    virtual void handleRoleMasterRequest(dakara::protocol::client::RoleMasterRequest* p);
    virtual void handleGMRequest(dakara::protocol::client::GMRequest* p);
    virtual void handleBugReport(dakara::protocol::client::BugReport* p);
    virtual void handleChangeDescription(dakara::protocol::client::ChangeDescription* p);
    virtual void handleGuildVote(dakara::protocol::client::GuildVote* p);
    virtual void handlePunishments(dakara::protocol::client::Punishments* p);
    virtual void handleChangePassword(dakara::protocol::client::ChangePassword* p);
    virtual void handleGamble(dakara::protocol::client::Gamble* p);
    virtual void handleInquiryVote(dakara::protocol::client::InquiryVote* p);
    virtual void handleLeaveFaction(dakara::protocol::client::LeaveFaction* p);
    virtual void handleBankExtractGold(dakara::protocol::client::BankExtractGold* p);
    virtual void handleBankDepositGold(dakara::protocol::client::BankDepositGold* p);
    virtual void handleDenounce(dakara::protocol::client::Denounce* p);
    virtual void handleGuildFundate(dakara::protocol::client::GuildFundate* p);
    virtual void handleGuildFundation(dakara::protocol::client::GuildFundation* p);
    virtual void handlePartyKick(dakara::protocol::client::PartyKick* p);
    virtual void handlePartySetLeader(dakara::protocol::client::PartySetLeader* p);
    virtual void handlePartyAcceptMember(dakara::protocol::client::PartyAcceptMember* p);
    virtual void handlePing(dakara::protocol::client::Ping* p);
    virtual void handleRequestPartyForm(dakara::protocol::client::RequestPartyForm* p);
    virtual void handleItemUpgrade(dakara::protocol::client::ItemUpgrade* p);
    virtual void handleGMCommands(dakara::protocol::client::GMCommands* p);
    virtual void handleInitCrafting(dakara::protocol::client::InitCrafting* p);
    virtual void handleHome(dakara::protocol::client::Home* p);
    virtual void handleShowGuildNews(dakara::protocol::client::ShowGuildNews* p);
    virtual void handleShareNpc(dakara::protocol::client::ShareNpc* p);
    virtual void handleStopSharingNpc(dakara::protocol::client::StopSharingNpc* p);
    virtual void handleConsultation(dakara::protocol::client::Consultation* p);
    virtual void handleMoveItem(dakara::protocol::client::MoveItem* p);

public:

    virtual void handleGMMessage(dakara::protocol::clientgm::GMMessage* p);
    virtual void handleShowName(dakara::protocol::clientgm::ShowName* p);
    virtual void handleOnlineRoyalArmy(dakara::protocol::clientgm::OnlineRoyalArmy* p);
    virtual void handleOnlineChaosLegion(dakara::protocol::clientgm::OnlineChaosLegion* p);
    virtual void handleGoNearby(dakara::protocol::clientgm::GoNearby* p);
    virtual void handleComment(dakara::protocol::clientgm::Comment* p);
    virtual void handleServerTime(dakara::protocol::clientgm::ServerTime* p);
    virtual void handleWhere(dakara::protocol::clientgm::Where* p);
    virtual void handleCreaturesInMap(dakara::protocol::clientgm::CreaturesInMap* p);
    virtual void handleWarpMeToTarget(dakara::protocol::clientgm::WarpMeToTarget* p);
    virtual void handleWarpChar(dakara::protocol::clientgm::WarpChar* p);
    virtual void handleSilence(dakara::protocol::clientgm::Silence* p);
    virtual void handleSOSShowList(dakara::protocol::clientgm::SOSShowList* p);
    virtual void handleSOSRemove(dakara::protocol::clientgm::SOSRemove* p);
    virtual void handleGoToChar(dakara::protocol::clientgm::GoToChar* p);
    virtual void handleInvisible(dakara::protocol::clientgm::Invisible* p);
    virtual void handleGMPanel(dakara::protocol::clientgm::GMPanel* p);
    virtual void handleRequestUserList(dakara::protocol::clientgm::RequestUserList* p);
    virtual void handleWorking(dakara::protocol::clientgm::Working* p);
    virtual void handleHiding(dakara::protocol::clientgm::Hiding* p);
    virtual void handleJail(dakara::protocol::clientgm::Jail* p);
    virtual void handleKillNPC(dakara::protocol::clientgm::KillNPC* p);
    virtual void handleWarnUser(dakara::protocol::clientgm::WarnUser* p);
    virtual void handleEditChar(dakara::protocol::clientgm::EditChar* p);
    virtual void handleRequestCharInfo(dakara::protocol::clientgm::RequestCharInfo* p);
    virtual void handleRequestCharStats(dakara::protocol::clientgm::RequestCharStats* p);
    virtual void handleRequestCharGold(dakara::protocol::clientgm::RequestCharGold* p);
    virtual void handleRequestCharInventory(dakara::protocol::clientgm::RequestCharInventory* p);
    virtual void handleRequestCharBank(dakara::protocol::clientgm::RequestCharBank* p);
    virtual void handleRequestCharSkills(dakara::protocol::clientgm::RequestCharSkills* p);
    virtual void handleReviveChar(dakara::protocol::clientgm::ReviveChar* p);
    virtual void handleOnlineGM(dakara::protocol::clientgm::OnlineGM* p);
    virtual void handleOnlineMap(dakara::protocol::clientgm::OnlineMap* p);
    virtual void handleForgive(dakara::protocol::clientgm::Forgive* p);
    virtual void handleKick(dakara::protocol::clientgm::Kick* p);
    virtual void handleExecute(dakara::protocol::clientgm::Execute* p);
    virtual void handleBanChar(dakara::protocol::clientgm::BanChar* p);
    virtual void handleUnbanChar(dakara::protocol::clientgm::UnbanChar* p);
    virtual void handleNPCFollow(dakara::protocol::clientgm::NPCFollow* p);
    virtual void handleSummonChar(dakara::protocol::clientgm::SummonChar* p);
    virtual void handleSpawnListRequest(dakara::protocol::clientgm::SpawnListRequest* p);
    virtual void handleSpawnCreature(dakara::protocol::clientgm::SpawnCreature* p);
    virtual void handleResetNPCInventory(dakara::protocol::clientgm::ResetNPCInventory* p);
    virtual void handleCleanWorld(dakara::protocol::clientgm::CleanWorld* p);
    virtual void handleServerMessage(dakara::protocol::clientgm::ServerMessage* p);
    virtual void handleNickToIP(dakara::protocol::clientgm::NickToIP* p);
    virtual void handleIPToNick(dakara::protocol::clientgm::IPToNick* p);
    virtual void handleGuildOnlineMembers(dakara::protocol::clientgm::GuildOnlineMembers* p);
    virtual void handleTeleportCreate(dakara::protocol::clientgm::TeleportCreate* p);
    virtual void handleTeleportDestroy(dakara::protocol::clientgm::TeleportDestroy* p);
    virtual void handleRainToggle(dakara::protocol::clientgm::RainToggle* p);
    virtual void handleSetCharDescription(dakara::protocol::clientgm::SetCharDescription* p);
    virtual void handleForceMIDIToMap(dakara::protocol::clientgm::ForceMIDIToMap* p);
    virtual void handleForceWAVEToMap(dakara::protocol::clientgm::ForceWAVEToMap* p);
    virtual void handleRoyalArmyMessage(dakara::protocol::clientgm::RoyalArmyMessage* p);
    virtual void handleChaosLegionMessage(dakara::protocol::clientgm::ChaosLegionMessage* p);
    virtual void handleCitizenMessage(dakara::protocol::clientgm::CitizenMessage* p);
    virtual void handleCriminalMessage(dakara::protocol::clientgm::CriminalMessage* p);
    virtual void handleTalkAsNPC(dakara::protocol::clientgm::TalkAsNPC* p);
    virtual void handleDestroyAllItemsInArea(dakara::protocol::clientgm::DestroyAllItemsInArea* p);
    virtual void handleAcceptRoyalCouncilMember(dakara::protocol::clientgm::AcceptRoyalCouncilMember* p);
    virtual void handleAcceptChaosCouncilMember(dakara::protocol::clientgm::AcceptChaosCouncilMember* p);
    virtual void handleItemsInTheFloor(dakara::protocol::clientgm::ItemsInTheFloor* p);
    virtual void handleMakeDumb(dakara::protocol::clientgm::MakeDumb* p);
    virtual void handleMakeDumbNoMore(dakara::protocol::clientgm::MakeDumbNoMore* p);
    virtual void handleDumpIPTables(dakara::protocol::clientgm::DumpIPTables* p);
    virtual void handleCouncilKick(dakara::protocol::clientgm::CouncilKick* p);
    virtual void handleSetTrigger(dakara::protocol::clientgm::SetTrigger* p);
    virtual void handleAskTrigger(dakara::protocol::clientgm::AskTrigger* p);
    virtual void handleBannedIPList(dakara::protocol::clientgm::BannedIPList* p);
    virtual void handleBannedIPReload(dakara::protocol::clientgm::BannedIPReload* p);
    virtual void handleGuildMemberList(dakara::protocol::clientgm::GuildMemberList* p);
    virtual void handleGuildBan(dakara::protocol::clientgm::GuildBan* p);
    virtual void handleBanIP(dakara::protocol::clientgm::BanIP* p);
    virtual void handleUnbanIP(dakara::protocol::clientgm::UnbanIP* p);
    virtual void handleCreateItem(dakara::protocol::clientgm::CreateItem* p);
    virtual void handleDestroyItems(dakara::protocol::clientgm::DestroyItems* p);
    virtual void handleChaosLegionKick(dakara::protocol::clientgm::ChaosLegionKick* p);
    virtual void handleRoyalArmyKick(dakara::protocol::clientgm::RoyalArmyKick* p);
    virtual void handleForceMIDIAll(dakara::protocol::clientgm::ForceMIDIAll* p);
    virtual void handleForceWAVEAll(dakara::protocol::clientgm::ForceWAVEAll* p);
    virtual void handleRemovePunishment(dakara::protocol::clientgm::RemovePunishment* p);
    virtual void handleTileBlockedToggle(dakara::protocol::clientgm::TileBlockedToggle* p);
    virtual void handleKillNPCNoRespawn(dakara::protocol::clientgm::KillNPCNoRespawn* p);
    virtual void handleKillAllNearbyNPCs(dakara::protocol::clientgm::KillAllNearbyNPCs* p);
    virtual void handleLastIP(dakara::protocol::clientgm::LastIP* p);
    virtual void handleChangeMOTD(dakara::protocol::clientgm::ChangeMOTD* p);
    virtual void handleSetMOTD(dakara::protocol::clientgm::SetMOTD* p);
    virtual void handleSystemMessage(dakara::protocol::clientgm::SystemMessage* p);
    virtual void handleCreateNPC(dakara::protocol::clientgm::CreateNPC* p);
    virtual void handleCreateNPCWithRespawn(dakara::protocol::clientgm::CreateNPCWithRespawn* p);
    virtual void handleImperialArmour(dakara::protocol::clientgm::ImperialArmour* p);
    virtual void handleChaosArmour(dakara::protocol::clientgm::ChaosArmour* p);
    virtual void handleNavigateToggle(dakara::protocol::clientgm::NavigateToggle* p);
    virtual void handleServerOpenToUsersToggle(dakara::protocol::clientgm::ServerOpenToUsersToggle* p);
    virtual void handleTurnOffServer(dakara::protocol::clientgm::TurnOffServer* p);
    virtual void handleTurnCriminal(dakara::protocol::clientgm::TurnCriminal* p);
    virtual void handleResetFactions(dakara::protocol::clientgm::ResetFactions* p);
    virtual void handleRemoveCharFromGuild(dakara::protocol::clientgm::RemoveCharFromGuild* p);
    virtual void handleRequestCharMail(dakara::protocol::clientgm::RequestCharMail* p);
    virtual void handleAlterPassword(dakara::protocol::clientgm::AlterPassword* p);
    virtual void handleAlterMail(dakara::protocol::clientgm::AlterMail* p);
    virtual void handleAlterName(dakara::protocol::clientgm::AlterName* p);
    virtual void handleToggleCentinelActivated(dakara::protocol::clientgm::ToggleCentinelActivated* p);
    virtual void handleDoBackUp(dakara::protocol::clientgm::DoBackUp* p);
    virtual void handleShowGuildMessages(dakara::protocol::clientgm::ShowGuildMessages* p);
    virtual void handleSaveMap(dakara::protocol::clientgm::SaveMap* p);
    virtual void handleChangeMapInfoPK(dakara::protocol::clientgm::ChangeMapInfoPK* p);
    virtual void handleChangeMapInfoBackup(dakara::protocol::clientgm::ChangeMapInfoBackup* p);
    virtual void handleChangeMapInfoRestricted(dakara::protocol::clientgm::ChangeMapInfoRestricted* p);
    virtual void handleChangeMapInfoNoMagic(dakara::protocol::clientgm::ChangeMapInfoNoMagic* p);
    virtual void handleChangeMapInfoNoInvi(dakara::protocol::clientgm::ChangeMapInfoNoInvi* p);
    virtual void handleChangeMapInfoNoResu(dakara::protocol::clientgm::ChangeMapInfoNoResu* p);
    virtual void handleChangeMapInfoLand(dakara::protocol::clientgm::ChangeMapInfoLand* p);
    virtual void handleChangeMapInfoZone(dakara::protocol::clientgm::ChangeMapInfoZone* p);
    virtual void handleChangeMapInfoStealNpc(dakara::protocol::clientgm::ChangeMapInfoStealNpc* p);
    virtual void handleChangeMapInfoNoOcultar(dakara::protocol::clientgm::ChangeMapInfoNoOcultar* p);
    virtual void handleChangeMapInfoNoInvocar(dakara::protocol::clientgm::ChangeMapInfoNoInvocar* p);
    virtual void handleSaveChars(dakara::protocol::clientgm::SaveChars* p);
    virtual void handleCleanSOS(dakara::protocol::clientgm::CleanSOS* p);
    virtual void handleShowServerForm(dakara::protocol::clientgm::ShowServerForm* p);
    virtual void handleNight(dakara::protocol::clientgm::Night* p);
    virtual void handleKickAllChars(dakara::protocol::clientgm::KickAllChars* p);
    virtual void handleReloadNPCs(dakara::protocol::clientgm::ReloadNPCs* p);
    virtual void handleReloadServerIni(dakara::protocol::clientgm::ReloadServerIni* p);
    virtual void handleReloadSpells(dakara::protocol::clientgm::ReloadSpells* p);
    virtual void handleReloadObjects(dakara::protocol::clientgm::ReloadObjects* p);
    virtual void handleRestart(dakara::protocol::clientgm::Restart* p);
    virtual void handleResetAutoUpdate(dakara::protocol::clientgm::ResetAutoUpdate* p);
    virtual void handleChatColor(dakara::protocol::clientgm::ChatColor* p);
    virtual void handleIgnored(dakara::protocol::clientgm::Ignored* p);
    virtual void handleCheckSlot(dakara::protocol::clientgm::CheckSlot* p);
    virtual void handleSetIniVar(dakara::protocol::clientgm::SetIniVar* p);
    virtual void handleCreatePretorianClan(dakara::protocol::clientgm::CreatePretorianClan* p);
    virtual void handleRemovePretorianClan(dakara::protocol::clientgm::RemovePretorianClan* p);
    virtual void handleEnableDenounces(dakara::protocol::clientgm::EnableDenounces* p);
    virtual void handleShowDenouncesList(dakara::protocol::clientgm::ShowDenouncesList* p);
    virtual void handleMapMessage(dakara::protocol::clientgm::MapMessage* p);
    virtual void handleSetDialog(dakara::protocol::clientgm::SetDialog* p);
    virtual void handleImpersonate(dakara::protocol::clientgm::Impersonate* p);
    virtual void handleImitate(dakara::protocol::clientgm::Imitate* p);
    virtual void handleRecordAdd(dakara::protocol::clientgm::RecordAdd* p);
    virtual void handleRecordRemove(dakara::protocol::clientgm::RecordRemove* p);
    virtual void handleRecordAddObs(dakara::protocol::clientgm::RecordAddObs* p);
    virtual void handleRecordListRequest(dakara::protocol::clientgm::RecordListRequest* p);
    virtual void handleRecordDetailsRequest(dakara::protocol::clientgm::RecordDetailsRequest* p);
    virtual void handleAlterGuildName(dakara::protocol::clientgm::AlterGuildName* p);
    virtual void handleHigherAdminsMessage(dakara::protocol::clientgm::HigherAdminsMessage* p);

private:
    const int UserIndex;
};

class DakaraPacketHandler : public dakara::protocol::PacketHandler {
public:
	DakaraPacketHandler(int UI) : UserIndex(UI), clientPacketHandler(UI) {}

    virtual ~DakaraPacketHandler() {};
    virtual dakara::protocol::client::ClientPacketHandler* getPacketHandlerClientPacket();
    virtual dakara::protocol::clientgm::ClientGMPacketHandler* getPacketHandlerClientGMPacket();
    virtual dakara::protocol::server::ServerPacketHandler* getPacketHandlerServerPacket();

private:
    const int UserIndex;
    DakaraClientPacketHandler clientPacketHandler;
};

void InitProtocolHandler();


#endif /* PROTOCOLHANDLER_H_ */
